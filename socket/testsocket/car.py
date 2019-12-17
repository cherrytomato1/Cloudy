#!/usr/bin/env python
# -*- coding: utf-8 -*-

import RPi.GPIO as GPIO         # GPIO 모듈을 import
from time import sleep          # time 모듈의 sleep()함수 사용

# 모터 상태
STOP  = 0
FORWARD  = 1
BACKWARD = 2
RIGHT = 3
LEFT = 4

# 모터 채널(CH1: 오른쪽, CH2: 왼쪽)
CH1 = 0
CH2 = 1

# PIN 입출력 설정
OUTPUT = 1
INPUT = 0

# PIN 설정
HIGH = 1
LOW = 0

#PWM PIN 정의
ENA = 16  
ENB = 20   

# GPIO 핀 정의
IN1 = 17  
IN2 = 27  
IN3 = 5   
IN4 = 6  



def setPinConfig(EN, INA, INB):                         # 핀 설정 함수 
    GPIO.setup(EN, GPIO.OUT)                            # EN핀을 출력으로 설정
    GPIO.setup(INA, GPIO.OUT)                           # INA핀을 출력으로 설정
    GPIO.setup(INB, GPIO.OUT)                           # INB핀을 출력으로 설정
    pwm = GPIO.PWM(EN, 100)                             # EN핀의 pwm설정(100)
    pwm.start(0)                                        # PWM 시작
    return pwm                                          # 모터의 pwm 설정        


def setMotorContorl(pwm, INA, INB, speed, stat):        # 모터 제어 함수
    pwm.ChangeDutyCycle(speed)                          # 모터 속도 제어 pwm
    if stat == FORWARD:                                 # 직진
        GPIO.output(INA, HIGH)                          # INA핀을 HIGH
        GPIO.output(INB, LOW)                           # INB핀을 LOW
    
    elif stat == BACKWARD:                              # 후진
        GPIO.output(INA, LOW)                           # INA핀을 LOW
        GPIO.output(INB, HIGH)                          # INB핀을 HIGH

    elif stat == STOP:                                  # 정지
        GPIO.output(INA, LOW)                           # INA핀을 LOW
        GPIO.output(INB, LOW)                           # INB핀을 LOW

        
def setMotor(ch, speed, stat):                          # 모터 제어 함수를 간단하게 사용
    if ch == CH1:                                       # 오른쪽 바퀴
        setMotorContorl(pwmA, IN1, IN2, speed, stat)    # 모터 동작
    else:                                               # 왼쪽 바퀴
        speed = speed * 0.9
        setMotorContorl(pwmB, IN3, IN4, speed, stat)    # 모터 동작
  
def setcar(stat):                                       # 소켓 통신에 사용하는 모터 제어 함수
    if(stat=="FORWARD"):                                # 받은 데이터가 "FORWARD"일 경우
        setMotor(CH1, 100, FORWARD)                     # 모터 직진
        setMotor(CH2, 100, FORWARD)

    elif(stat=="BACKWARD"):                             # 받은 데이터가 "BACKWARD"일 경우
        setMotor(CH1, 100, BACKWARD)                    # 모터 후진
        setMotor(CH2, 100, BACKWARD)
        
    elif(stat=="RIGHT"):                                # 받은 데이터가 "RIGHR"일 경우
        setMotor(CH1, 100, BACKWARD)                    # 모터 우회전
        setMotor(CH2, 100, FORWARD)

    elif(stat=="LEFT"):                                 # 받은 데이터가 "LEFT"일 경우
        setMotor(CH1, 100, FORWARD)                     # 모터 좌회전
        setMotor(CH2, 100, BACKWARD)

    elif(stat=="STOP"):                                 # 받은 데이터가 "STOP"일 경우
        setMotor(CH1, 0, STOP)                          # 모터 정지
        setMotor(CH2, 0, STOP)
    
GPIO.setmode(GPIO.BCM)                                  # 라즈베리파이의 핀 번호를 BCM 모드로 설정
GPIO.setwarnings(False)                                 # 에러 방지

pwmA = setPinConfig(ENA, IN1, IN2)                      # 모터 설정
pwmB = setPinConfig(ENB, IN3, IN4)                      # 모터 설정
