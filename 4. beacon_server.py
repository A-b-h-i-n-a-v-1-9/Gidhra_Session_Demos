# save as server.py
import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("0.0.0.0", 8080))
s.listen(1)

print("Server listening on port 8080...")

conn, addr = s.accept()
print(f"Connection from {addr}")

while True:
    data = conn.recv(1024)
    if not data:
        break
    print("Received:", data.decode().strip())
