#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import RPi.GPIO as GPIO     # GPIO 모듈 import
import threading

from setDir import *
from sonic import *
from time import sleep      # time 모듈의 sleep() 함수 사용
from motor import *           # car 모듈의 모든 함수 사용

STOP = 0
FORWARD = 1
BACKWARD = 2
LEFT = 3
RIGHT = 4


presonic()

print ('HI')                              # 소켓 리스닝 시 출력문

while True:                                                 # 무한 루프

#        th=threading.Thread(target=setDir, args=())
#        th.start()
        drct=setDirTest()
        
        motor(drct)                                         # 변환된 데이터에 따라 모터 동작
            
        print("pi :" ,drct)                                 # 어떤 동작을 하는지 출력
        
GPIO.cleanup()                                              # GPIO 모듈의 점유 리소스 해제
