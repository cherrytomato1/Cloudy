import RPi.GPIO as GPIO
import time


STOP  = 0
FORWARD  = 1
BACKWORD = 2
RIGHT = 3
LEFT = 4
WheelL = 0
WheelR = 1

def MotorInit():
    GPIO.setmode(GPIO.BCM)  
    motorA1 = 17  # left Wheel
    motorA2 = 27
    pwmA = 23
    motorB1 = 5  # right Wheel
    motorB2 = 6
    pwmB = 24                   
    GPIO.setwarnings(False)                  
    GPIO.setup(motorA1, GPIO.OUT)             
    GPIO.setup(motorA2, GPIO.OUT)
    GPIO.setup(motorB1, GPIO.OUT)
    GPIO.setup(motorB2, GPIO.OUT)
    pwm1 = GPIO.PWM(pwmA, 100)
    pwm2 = GPIO.PWM(pwmB, 100)
    pwm1.start(0) 
    pwm2.start(0)
    
def MotorStop():
    GPIO.output(motorA1, GPIO.LOW)
    GPIO.output(motorA2, GPIO.LOW)
    GPIO.output(motorB1, GPIO.LOW)
    GPIO.output(motorB2, GPIO.LOW)

def forward():
    GPIO.output(motorA1, GPIO.HIGH)
    GPIO.output(motorA2, GPIO.LOW)
    GPIO.output(motorB1, GPIO.HIGH)
    GPIO.output(motorB2, GPIO.LOW)


def backward():
    GPIO.output(motorA1, GPIO.LOW)
    GPIO.output(motorA2, GPIO.HIGH)
    GPIO.output(motorB1, GPIO.LOW)
    GPIO.output(motorB2, GPIO.HIGH)


def rot_L():
    GPIO.output(motorA1, GPIO.HIGH)
    GPIO.output(motorA2, GPIO.LOW)
    GPIO.output(motorB1, GPIO.LOW)
    GPIO.output(motorB2, GPIO.HIGH)


def rot_R():
    GPIO.output(motorA1, GPIO.LOW)
    GPIO.output(motorA2, GPIO.HIGH)
    GPIO.output(motorB1, GPIO.HIGH)
    GPIO.output(motorB2, GPIO.LOW)
    
def setMotor(stat, speed):
    pwm1.ChangeDutyCycle(speed)
    pwm2.ChangeDutyCycle(speed)
    if stat == STOP:
        MotorStop()
    elif stat == FORWARD:
        forward()
    elif stat == BACKWARD:
        backward()
    elif stat == RIGHT:
        rot_R()
    else:
        rot_L()
            
if __name__ == "__main__":
    MotorInit()
    try:
        while True:
            setMotor(FORWARD, 30)
            time.sleep(2)                        
            setMotor(BACKWARD, 30)
            time.sleep(2)
            setMotor(LEFT, 30)
            time.sleep(2)
            setMotor(RIGHT, 30)
            time.sleep(2)
    finally:
        GPIO.cleanup()
