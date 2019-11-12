import RPi.GPIO as IO
import time

def MotorInit():
    motorA1 = 17  # left Wheel
    motorA2 = 27
    motorB1 = 5  # right Wheel
    motorB2 = 7
    IO.setmode(IO.BCM)                     # 핀 넘버 부르는 방식 -> GPIO핀 번호로 사용
    IO.setwarnings(False)                  # 오류 방지
    IO.setup(motorA1, IO.out)              # 인풋 아웃풋 설정 (pinMode())
    IO.setup(motorA2, IO.out)
    IO.setup(motorB1, IO.out)
    IO.setup(motorB2, IO.out)
    
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

if __name__ == "__main__":
    MotorInit()
    try:
        while True:
            forward()
            time.sleep(2)                          # 2초동안
            backward()
            time.sleep(2)
            rot_L()
            time.sleep(2)
            rot_R()
            time.sleep(2)
    finally:
        IO.cleanup()
