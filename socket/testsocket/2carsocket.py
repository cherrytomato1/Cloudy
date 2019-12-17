import socket               # sockect 모듈 import
import RPi.GPIO as GPIO     # GPIO 모듈 import
from time import sleep      # time 모듈의 sleep() 함수 사용
from car import *           # car 모듈의 모든 함수 사용

GPIO.setmode(GPIO.BCM)      # 라즈베리파이의 핀모드를 BCM 모드로 설정
GPIO.setwarnings(False)     # 오류 방지

HOST = "192.168.0.211"      # 소켓 통신 IP 지정
PORT = 8080                 # 소켓 통신 PORT 지정
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)       # 소켓 객체 생성
print ('Socket created')                                    # 소켓 생성 시 출력문
s.bind((HOST, PORT))                                        # 소켓 주소 정보 할당
print ('Socket bind complete')                              # 소켓 바인드 성공 시 출력문
s.listen(1)                                                 # 소켓 연결 수신 대기 상태
print ('Socket now listening')                              # 소켓 리스닝 시 출력문

def do_some_stuffs_with_input(input_string):                # 수신 데이터에 따른 데이터 변환 함수
    if input_string == "1":                                 # 수신 데이터가 "1" 일 경우
        input_string = "FORWARD"                            # 데이터를 "FORWARD"로 변환
    elif input_string == "2":                               # 수신 데이터가 "2" 일 경우
        input_string = "BACKWARD"                           # 데이터를 "BACKWARD"로 변환
    elif input_string == "3":                               # 수신 데이터가 "3" 일 경우
        input_string = "LEFT"                               # 데이터를 "LEFT"로 변환
    elif input_string == "4":                               # 수신 데이터가 "4" 일 경우                      
        input_string = "RIGHT"                              # 데이터를 "RIGHT"로 변환
    elif input_string == "0":                               # 수신 데이터가 "0" 일 경우
        input_string = "STOP"                               # 데이터를 "STOP"로 변환
    else :                                                  # 그 외의 데이터를 수신 받을 경우
        input_string = input_string + ""                    # 변환하지 않고 데이터 출력
    return input_string                                     # 변환한 데이터를 리턴

while True:                                                 # 무한 루프

    conn, addr = s.accept()                                 # Client에서 연결 요청이 들어올 경우 연결 수락
    print("Connected by ", addr)                            # 연결된 Client의 addr 출력         
    while True:                                             # 무한 루프
        data = conn.recv(1024)                              # Client에서 받은 데이터를 data변수에 저장
        data = data.decode("utf8").strip()                  # data를 utf8형식으로 디코딩 후 공백 제거
        if not data: break                                  # 데이터 수신이 안되는 경우 무한 루프를 벗어남

        print("Received: " + data)                          # 받은 데이터 출력
        
        res = do_some_stuffs_with_input(data)               # 수신 데이터에 따라 데이터 변환
        setcar(res)                                         # 변환된 데이터에 따라 모터 동작
            
        print("pi :" + res)                                 # 어떤 동작을 하는지 출력
        conn.sendall(res.encode("utf-8"))                   # 데이터를 utf-8형식으로 인코딩하여 전달

    conn.close()                                            # 연결 끊기
s.close()                                                   # 소켓 종료
GPIO.cleanup()                                              # GPIO 모듈의 점유 리소스 해제
