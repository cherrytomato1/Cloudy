#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import socket               # sockect 모듈 import
import setDir
import RPi.GPIO as GPIO     # GPIO 모듈 import
from time import sleep      # time 모듈의 sleep() 함수 사용
from motor import *           # car 모듈의 모든 함수 사용

STOP = 0
FORWARD = 1
BACKWARD = 2
LEFT = 3
RIGHT = 4

GPIO.setmode(GPIO.BCM)      # 라즈베리파이의 핀모드를 BCM 모드로 설정
GPIO.setwarnings(False)     # 오류 방지

print ('HI')                              # 소켓 리스닝 시 출력문

while True:                                                 # 무한 루프
        
        drct
        print("Received: " + drct)                          # 받은 데이터 출력
        
        setcar(drct)                                         # 변환된 데이터에 따라 모터 동작
            
        print("pi :" + drct)                                 # 어떤 동작을 하는지 출력
        
GPIO.cleanup()                                              # GPIO 모듈의 점유 리소스 해제
