from bluetooth import *

client_socket=BluetoothSocket(RFCOMM)

client_socket.connect(("98:D3:41:FD:4F:78", 1))
print("bluetooth connected!")

while True:
    msg = client_socket.recv(1024)
    print("recived message : {}".format(msg))

print("Finished")
client_socket.close()