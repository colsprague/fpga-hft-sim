# Running document of ideas learned, explored, and thoughts

## 2026-06-09 - FPGA Architecture
### Source(s)
- FPGA Acceleration in HFT: Architecture and Implementation: https://medium.com/@shailamie/fpga-acceleration-in-hft-architecture-and-implementation-68adab59f7af
- Gemini

### Notes
#### Faults of CPU
- Sequential Processing (one instruction at a time, whereas FPGA is parallel)
- Context Switching (adds many CPU cycles)
- Cache Misses (high-frequency packets cause expensive cache coherency)
- Unpredictable Timing (memory management introduces random timing spikes)
#### Benefits of FPGA
- Nanosecond-level latency
- FPGAs run in parallel (not sequentially)
- Zero Context Switching (data flows smoothly without kernel involvement)
- Deterministic Timing (timing is predictable for each cycle)
- Power Efficiency (use less power than other options)
- Ultimately, FPGA characteristics fit live market needs much better
#### FPGA System Architecture (Top -> Bottom)
- ...
#### Network Interface Layer - Kernel Bypass
- Market data arrives as Ethernet packets at 10+ Gbps
- Typically arrives as UDP, TCP, or Direct Ethernet for FPGA
#### Market Data Parser (ITCH/FAST Protocol)
- NASDAQ sends market data in ITCH protocl (fixed-length binary format describing order book changes)
- Order Book: data of what buyers are willing to pay and sellers are willing to accept
- much more information...
#### Overview
- Market Data Input
- Network Interface (Kernel Bypass - gets raw data instantly)
- Packet Parser (Slices raw bytes into Stock ID, Price, Size)
- Order Book Engine (Updates 'market' in memory)
- Signal Generator (Calculates if price is weird/profitable)
- Risk Manager (Double-checks compliance rules to ensure safety)
- Order Gateway (Formulates "Buy" or "Sell" message to send back)
- All of these run under 'Pipeline Parallelism' (Every pipeline is constantly working)
#### Next Steps (C++ Code)
- Create a program that simulates an order book. Starts with x number of buy and sell orders, then randomly adds buy, sell, or execute orders. Orders will be written to an external file. At y lines, the file becomes static and will be used as input for the HFT system. Important: Code/output should be efficient, use ITCH protocol
### 2026-06-12 - ITCH & Coding
#### Source(s)
- https://www.nasdaqtrader.com/content/technicalsupport/specifications/dataproducts/NQTVITCHspecification.pdf
#### Notes
- Three ITCH protocols, for FPGA, UDP is used
- Formatted in big endian (most significant byte stored at lowest memory address)
- Alpha fields are ASCII, left justified, padded with spaces
- Will focus on Add Order, no MPID Attribution
- 36-Byte (288-bit) message, format found on nasdaqtrader site
#### Application
- Generation code will initialize some amount of buy and sell orders
- Then code will randomly add buy, sell, execute orders
### Coding Progress / Thoughts
- Message Type defines the type of message. Program simulates add orders (value of 'A')
- Stock Locate varies day by day (constant for the day, though). Simulation will pick a value (0x00'01). Seems like another program parses pre-market data.
- Tracking Number is not used for trading logic, set to 0x00'00
- Currently unsure of how to simulate Time Stamp, but it represents the number of nanoseconds since midnight
- Order Reference Number iterates for each trade (first trade is 1, second is 2, etc)
- B/S Indicator informs whether order is to buy ('B') or sell ('S')
- Shares is the number of shares per order (100 used for pre-market setup)
- Stock is the stock ticker symbol ("AAPL" used, left justified, padded by spaces)
- Price is the order price with 4 decimals of precision ($100.25 -> 1002500)
- ITCH Structure complete. Since results will be printed to a binary file, data is printed completely (16 bit value, even if stores a single bit, still prints 16 bits), #pragma is used to prevent unecessary padding.
- IMPORTANT LEARN: each memory address stores a single byte (8-bits). If we have some x-byte integer, the endianness (big or little) determines where the effected bytes of the integer end up IN MEMORY. CPU runs on little-endian, NASDAQ runs on big-endian, so to make it realistic, C++ code needs some manipulation to match (__builtin_bswapX, where X is the number of bits).

