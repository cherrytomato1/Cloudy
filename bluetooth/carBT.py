
from bluetooth import *
from car import *

def do_some_stuffs_with_input(input_string):
    if input_string == "0":
        input_string = "STOP"
    if input_string == "1":
        input_string = "FORWARD"
    elif input_string == "2":
        input_string = "BACKWARD"
    elif input_string == "3":
        input_string = "LEFT"
    elif input_string == "4":
        input_string = "RIGHT"
    elif input_string == "5":
        input_string = "L_FORWARD"
    elif input_string == "6":
        input_string = "R_FORWARD"
    else :
        input_string = input_string + ""
    return input_string

client_socket=BluetoothSocket(RFCOMM)

client_socket.connect(("98:D3:41:FD:4F:78", 1))
print("bluetooth connected!")

while True:
    msg = client_socket.recv(1024)
    res = do_some_stuffs_with_input(msg)
    setcar(res)
    print("recived message : {}".format(msg))

print("Finished")
client_socket.close()
