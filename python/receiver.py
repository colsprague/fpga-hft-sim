import socket
import struct

# Network Configuration (Must match the simulator)
UDP_IP = "127.0.0.1"
UDP_PORT = 5001

# Setup UDP Socket and Bind it to the port
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

print(f"Receiver listening on {UDP_IP}:{UDP_PORT}...")
print("Waiting for packets...")

try:
    while True:
        # Receive packet (16 bytes of data)
        data, addr = sock.recvfrom(16)
        
        # Unpack the binary data using the exact same format specifier:
        # !  = Network byte order (Big-Endian)
        # I  = 4-byte unsigned int
        # 4s = 4-byte string
        # d  = 8-byte float
        seq, symbol, price = struct.unpack("!I4sd", data)
        
        # Decode the byte string back to normal text
        symbol = symbol.decode().strip()
        
        print(f"--> Received Packet #{seq} | Stock: {symbol} | Price: ${price:.2f}")

except KeyboardInterrupt:
    print("\nShutting down Receiver.")
finally:
    sock.close()