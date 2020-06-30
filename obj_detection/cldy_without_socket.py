#!/usr/bin/env python
# -*- coding: utf-8 -*-
import serial           #시리얼 통신
import os
import socket               # sockect 모듈 import
import obj_detection as dtct
import threading
from time import sleep      # time 모듈의 sleep() 함수 사용


state = '1'
pos = size = 10
data = "test"

def serWrite() :
    while True :
        global data
        sleep(0.1)
        ser.write(data.encode('utf-8'))
        print(data)
        
def getDtct() :
    while True :
        global pos, size
        pos, size = dtct.obj_dtct();
        pos = int(pos)
        size= int(size)
        
        pos= int(pos) + 500
        if(size>200) :
            size = '9'
        else :
            size = str(size/20)
            size = size[0]
        


sw = threading.Thread(target=serWrite)
gd = threading.Thread(target=getDtct)

sw.daemon =True
gd.daemon =True



ser = serial.Serial('/dev/ttyUSB0')


while True:                                                 # 무한 루프
                         # 연결된 Client의 addr 출력         
    #rs.start()
    sw.start()
    gd.start()

    while True:
                                                            # 무한 루프
        #state = conn.recv(1024)                              # Client에서 받은 데이터를 data변수에 저장
        #state = state.decode("utf8").strip()
        #if not state: break                                  # 데이터 수신이 안되는 경우 무한 루프를 벗어남

        state = '7'
        #sleep(0.1)
        


        #print(str(state) + ', ' + str(size) +', '+str(pos))

        if(state == '7') :
            data = '1'+str(size)+str(pos)
        else :
            data = '0000'+str(state)
        
        
    conn.close()                                            # 연결 끊기
    dtct.stop_dtct()
s.close()                                                   # 소켓 종료
#GPIO.cleanup()                                              # GPIO 모듈의 점유 리소스 해제

