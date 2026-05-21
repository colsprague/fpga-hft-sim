import socket
import struct
import time
import random

# Network Configuration
TARGET_IP = "127.0.0.1"  # Localhost
TARGET_PORT = 5001       # The port your future FPGA (or client script) will listen to

# Setup UDP Socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print(f"Starting Exchange Simulator... Broadcasting on {TARGET_IP}:{TARGET_PORT}")
print("Press Ctrl+C to stop.")

# Initial simulated stock state (Let's trade 'AAPL')
stock_symbol = b"AAPL"  # 4 bytes
price = 180.00         # Floating point (8 bytes)
sequence_number = 0    # Packet counter (4 bytes)

try:
    while True:
        # 1. Simulate some price movement (random walk)
        price += round(random.uniform(-0.5, 0.5), 2)
        price = max(1.0, price) # Ensure price doesn't go negative
        sequence_number += 1
        
        # 2. Pack the data into a binary payload (simulating an exchange packet protocol)
        # Format specifier 'I 4s d' means:
        # I  = 4-byte unsigned integer (Sequence Number)
        # 4s = 4-byte character array (Stock Symbol)
        # d  = 8-byte float (Price)
        # Total packet size = 16 bytes. Pure, raw binary. No heavy JSON.
        packet = struct.pack("!I4sd", sequence_number, stock_symbol, price)
        
        # 3. Blast it over UDP
        sock.sendto(packet, (TARGET_IP, TARGET_PORT))
        
        print(f"Sent Packet #{sequence_number} | {stock_symbol.decode()} Price: ${price:.2f}")
        
        # Simulate time between market ticks (e.g., every 100ms)
        time.sleep(0.1)

except KeyboardInterrupt:
    print("\nShutting down Exchange Simulator.")
finally:
    sock.close()