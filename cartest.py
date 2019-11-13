import RPi.GPIO as IO
import time

STOP  = 0
FORWARD  = 1
BACKWORD = 2
RIGHT = 3
LEFT = 4
WheelL = 0
WheelR = 1

def MotorInit():
    motorA1 = 17  # left Wheel
    motorA2 = 27
    pwmA = 23
    motorB1 = 5  # right Wheel
    motorB2 = 7
    pwmB = 24
    IO.setmode(IO.BCM)                     # 핀 넘버 부르는 방식 -> GPIO핀 번호로 사용
    IO.setwarnings(False)                  # 오류 방지
    IO.setup(motorA1, IO.out)              # 인풋 아웃풋 설정 (pinMode())
    IO.setup(motorA2, IO.out)
    IO.setup(motorB1, IO.out)
    IO.setup(motorB2, IO.out)
    pwm1 = IO.PWM(pwmA, 100)
    pwm2 = IO.PWM(pwmB, 100)
    pwm1.start(0) 
    pwm2.start(0)
    
def MotorStop():
    IO.output(motorA1, IO.LOW)
    IO.output(motorA2, IO.LOW)
    IO.output(motorB1, IO.LOW)
    IO.output(motorB2, IO.LOW)

def forward():
    IO.output(motorA1, IO.HIGH)
    IO.output(motorA2, IO.LOW)
    IO.output(motorB1, IO.HIGH)
    IO.output(motorB2, IO.LOW)


def backward():
    IO.output(motorA1, IO.LOW)
    IO.output(motorA2, IO.HIGH)
    IO.output(motorB1, IO.LOW)
    IO.output(motorB2, IO.HIGH)


def rot_L():
    IO.output(motorA1, IO.HIGH)
    IO.output(motorA2, IO.LOW)
    IO.output(motorB1, IO.LOW)
    IO.output(motorB2, IO.HIGH)


def rot_R():
    IO.output(motorA1, IO.LOW)
    IO.output(motorA2, IO.HIGH)
    IO.output(motorB1, IO.HIGH)
    IO.output(motorB2, IO.LOW)
    
def setMotor(stat, speed):
    pwm1.ChangeDutyCycle(speed)
    pwm2.ChangeDutyCycle(speed)
    if stat == STOP:
        MotorStop()
    else if stat == FORWARD:
        forward()
    else if stat == BACKWARD:
        backward()
    else if stat == RIGHT:
        rot_R()
    else:
        rot_L()
            
if __name__ == "__main__":
    MotorInit()
    try:
        while True:
            setMotor(FORWARD, 30)
            time.sleep(2)                          # 2초동안
            setMotor(BACKWARD, 30)
            time.sleep(2)
            setMotor(LEFT, 30)
            time.sleep(2)
            setMotor(RIGHT, 30)
            time.sleep(2)
    finally:
        IO.cleanup()
