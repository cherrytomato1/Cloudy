import socket
import RPi.GPIO as GPIO
from time import sleep
from car import *

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
t=1
HOST = "192.168.0.211"
PORT = 8080
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print ('Socket created')
s.bind((HOST, PORT))
print ('Socket bind complete')
s.listen(1)
print ('Socket now listening')

def do_some_stuffs_with_input(input_string):
    if input_string == "1":
        input_string = "FORWARD"
    elif input_string == "2":
        input_string = "BACKWARD"
    elif input_string == "3":
        input_string = "LEFT"
    elif input_string == "4":
        input_string = "RIGHT"
    elif input_string == "0":
        input_string = "STOP"
    else :
        input_string = input_string + ""
    return input_string

while True:

    conn, addr = s.accept()
    print("Connected by ", addr)
    print("1: FORWARD, 2:BACKWARD, 3:LEFT, 4:RIGHT")
    while True:
        data = conn.recv(1024)
        data = data.decode("utf8").strip()
        if not data: break

        print("Received: " + data)
        
        res = do_some_stuffs_with_input(data)
        setcar(res)
            
        print("pi :" + res)
        conn.sendall(res.encode("utf-8"))

    conn.close()
s.close()
GPIO.cleanup()
