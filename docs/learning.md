# Running document of ideas learned, explored, and thoughts

## 2026-06-09 - FPGA Architecture
### Source(s)
- FPGA Acceleration in HFT: Architecture and Implementation: https://medium.com/@shailamie/fpga-acceleration-in-hft-architecture-and-implementation-68adab59f7af

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
#### 
