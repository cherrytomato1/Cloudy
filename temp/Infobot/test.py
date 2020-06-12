#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import RPi.GPIO as GPIO     # GPIO 모듈 import
from sonic import *
from time import sleep      # time 모듈의 sleep() 함수 사용

presonic()
print ('HI')                              # 소켓 리스닝 시 출력문

while True:                                                 # 무한 루프
        print('1:',printsonic(1),'cm')
        time.sleep(0.1)
   
GPIO.cleanup()                                              # GPIO 모듈의 점유 리소스 해제
