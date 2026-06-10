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

