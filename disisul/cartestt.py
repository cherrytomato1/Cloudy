
import RPi.GPIO as GPIO
from time import sleep
from bluetooth import *


STOP  = 0
FORWARD  = 1
BACKWARD = 2
RIGHT = 3
LEFT = 4

CH1 = 0
CH2 = 1


OUTPUT = 1
INPUT = 0


HIGH = 1
LOW = 0

ENA = 16  #37 pin
ENB = 20   #27 pin


IN1 = 17  #37 pin
IN2 = 27  #35 pin
IN3 = 5   #31 pin
IN4 = 6   #29 pin


def setPinConfig(EN, INA, INB):        
    GPIO.setup(EN, GPIO.OUT)
    GPIO.setup(INA, GPIO.OUT)
    GPIO.setup(INB, GPIO.OUT)

    pwm = GPIO.PWM(EN, 100) 
   
    pwm.start(0) 
    return pwm


def setMotorContorl(pwm, INA, INB, speed, stat):


    pwm.ChangeDutyCycle(speed)  
    
    if stat == FORWARD:
        GPIO.output(INA, HIGH)
        GPIO.output(INB, LOW)

    elif stat == BACKWARD:
        GPIO.output(INA, LOW)
        GPIO.output(INB, HIGH)

    elif stat == STOP:
        GPIO.output(INA, LOW)
        GPIO.output(INB, LOW)

        

def setMotor(ch, speed, stat):
    if ch == CH1:
        setMotorContorl(pwmA, IN1, IN2, speed, stat)
    else:
        setMotorContorl(pwmB, IN3, IN4, speed, stat)
  
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)          

pwmA = setPinConfig(ENA, IN1, IN2)
pwmB = setPinConfig(ENB, IN3, IN4)
spd=[20, 50, 70, 100]



client_socket=BluetoothSocket(RFCOMM)

client_socket.connect(("98:D3:41:FD:4F:78", 1))
print("bluetooth connected!")

while True:
    msg = client_socket.recv(1024)
    print("recived message : {}".format(str(msg)))
    setMotor(CH1, 100, FORWARD)
    setMotor(CH2, 100, BACKWARD)
    sleep(0.5)
    setMotor(CH1, 100, BACKWARD)
    setMotor(CH2, 100, FORWARD)
    sleep(0.5)
    setMotor(CH1, 0, FORWARD)
    setMotor(CH2, 0, FORWARD)

print("Finished")

sleep(2)
#for i in spd:
#    setMotor(CH1, i, FORWARD)
#    setMotor(CH2, i, FORWARD)
#    sleep(3)



print("LEFT")
setMotor(CH1, 50, FORWARD)
setMotor(CH2, 50, BACKWORD)
sleep(0.5)
setMotor(CH1, 100, FORWARD)
setMotor(CH2, 100, FORWARD)
sleep(1)

print("RIGHT")
setMotor(CH1, 50, BACKWORD)
setMotor(CH2, 50, FORWARD)
sleep(0.5)
setMotor(CH1, 100, FORWARD)
setMotor(CH2, 100, FORWARD)
sleep(1)


GPIO.cleanup()
