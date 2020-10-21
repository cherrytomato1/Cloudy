#!/usr/bin/env python
# -*- coding: utf-8 -*-
import serial           #시리얼 통신
import os
import socket               # sockect 모듈 import
import obj_detection as dtct
import threading
from time import sleep      # time 모듈의 sleep() 함수 사용

mod= 0
state = 7
pos = size = 0
data = "test"

def serWrite() :
    while True :
        global data,pos,mod,state
        #if(state == 7) :
        #    data = '1'+str(size)+str(pos)
        #else :
        #    data = '0000'+str(state)
        sleep(0.1)
        ser.write(data.encode('utf-8'))
        print("serWrite : " + data)
        


def recvSock() :
    while True :
        global state,conn
        #state = conn.recv(1024)
        #conn.recv(1024)
        #state+=1
        # Client에서 받은 데이터를 data변수에 저장
        #state = state.decode("utf8").strip()
        try :
            state=conn.recv(1024)
            state = state[len(state) - 1]-48
            sleep(0.1)
        #if (state == '7') :
            #mod = ~mod
            print("recvSock : ")
            print(state)
        except socket.timeout :
            print("timeout")
        #print(state)
        

def getDtct() :
    while True :
        global pos, size
        
        
        sleep(0.1)
        pos, size = dtct.obj_dtct();

        pos = int(pos)
        size= int(size)
        
        pos= int(pos) + 500
        if(size>200) :
            size = '9'
        else :
            size = str(size/20)
            size = size[0]

#HOST = os.popen('ip addr show wlan0 | grep "\<inet\>" | awk \'{ print $2 }\' | awk -F "/" \'{ print $1 }\'').read().strip()
number = 10                            # 소켓 통신 IP 지정(wlan0 자동으로 가져오기)
#PORT = 8080                 # 소켓 통신 PORT 지정
#s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)       # 소켓 객체 생성


sw = threading.Thread(target=serWrite)
#rs = threading.Thread(target=recvSock)
#gd = threading.Thread(target=getDtct)


#rs.daemon =True
sw.daemon =True
#gd.daemon =True



ser = serial.Serial('/dev/ttyUSB0')
print("START!! ")


#print ('Socket created')                                    # 소켓 생성 시 출력문
#s.bind((HOST, PORT))                                        # 소켓 주소 정보 할당
#print ('Socket bind complete')                              # 소켓 바인드 성공 시 출력문
#s.listen(1)                                                 # 소켓 연결 수신 대기 상태
#print ('Socket now listening')                              # 소켓 리스닝 시 출력문
#print ('IP address:' + HOST)    
while True:                                                 # 무한 루프
    #conn, addr = s.accept()                                 # Client에서 연결 요청이 들어올 경우 연결 수락
    #print("Connected by ", addr)                            # 연결된 Client의 addr 출력
    #conn.settimeout(1)
    #rs.start()
    sw.start()
    #gd.start()
                                                            # 무한 루프
        #state = conn.recv(1024)                              # Client에서 받은 데이터를 data변수에 저장
        #state = state.decode("utf8").strip()
        #if not state: break                                  # 데이터 수신이 안되는 경우 무한 루프를 벗어남
  
        #print(str(state) + ', ' + str(size) +', '+str(pos))

    while True :
        #state=conn.recv(1024)
        #if not state :
        #    print("no data")
            
        #if (state == '7') :
            #mod = ~mod
        #print("recvSock : ")
        pos, size = dtct.obj_dtct()

        pos = int(pos)
        size= int(size)
        
        pos= int(pos) + 500
        if(size>200) :
            size = '9'
        else :
            size = str(size/20)
            size = size[0]
            
        data = '1'+str(size)+str(pos)
        
    #conn.close()                                            # 연결 끊기
    dtct.stop_dtct()
#s.close()                                                   # 소켓 종료
#GPIO.cleanup()                                              # GPIO 모듈의 점유 리소스 해제

