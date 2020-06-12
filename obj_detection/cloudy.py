#!/usr/bin/env python
# -*- coding: utf-8 -*-
import serial           #시리얼 통신
import os
import socket               # sockect 모듈 import
import RPi.GPIO as GPIO     # GPIO 모듈 import
from time import sleep      # time 모듈의 sleep() 함수 사용

GPIO.setmode(GPIO.BCM)      # 라즈베리파이의 핀모드를 BCM 모드로 설정
GPIO.setwarnings(False)     # 오류 방지

HOST = os.popen('ip addr show wlan0 | grep "\<inet\>" | awk \'{ print $2 }\' | awk -F "/" \'{ print $1 }\'').read().strip()
number = 10                            # 소켓 통신 IP 지정(wlan0 자동으로 가져오기)
PORT = 8080                 # 소켓 통신 PORT 지정
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)       # 소켓 객체 생성

ser = serial.Serial('/dev/ttyACM0')
print("START!!")

print ('Socket created')                                    # 소켓 생성 시 출력문
s.bind((HOST, PORT))                                        # 소켓 주소 정보 할당
print ('Socket bind complete')                              # 소켓 바인드 성공 시 출력문
s.listen(1)                                                 # 소켓 연결 수신 대기 상태
print ('Socket now listening')                              # 소켓 리스닝 시 출력문
        
while True:                                                 # 무한 루프
    conn, addr = s.accept()                                 # Client에서 연결 요청이 들어올 경우 연결 수락
    print("Connected by ", addr)                            # 연결된 Client의 addr 출력         
    while True:                                             # 무한 루프
        data = conn.recv(1024)                              # Client에서 받은 데이터를 data변수에 저장
        data = data.decode("utf8").strip()
        if not data: break                                  # 데이터 수신이 안되는 경우 무한 루프를 벗어남
        ser.write(data)
        ser.write("HI")
        print("Received: " + data)                          # 받은 데이터 출력
        
    conn.close()                                            # 연결 끊기
s.close()                                                   # 소켓 종료
GPIO.cleanup()                                              # GPIO 모듈의 점유 리소스 해제

