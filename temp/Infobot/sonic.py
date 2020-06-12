#-*- coding: utf-8 -*-
import RPi.GPIO as GPIO
import time
import sys

SONIC_COUNT = 3
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

SS = {
    'SS1': {"trig": 12, "echo": 26},
    'SS2': {"trig": 12, "echo": 26},
    'SS3': {"trig": 12, "echo": 26}
}
def presonic():
    for i in range(1, SONIC_COUNT + 1):
        GPIO.setup(SS['SS{}'.format(i)]["trig"], GPIO.OUT)
        GPIO.setup(SS['SS{}'.format(i)]["echo"], GPIO.IN)
        GPIO.output(SS['SS{}'.format(i)]["trig"], False) # trig핀 low로 유지

def printsonic(num):  # 인자에 1~3 숫자 넣기 (1 -> 1번 센서)
    if num:
        trig = SS['SS{}'.format(num)]["trig"]
        echo = SS['SS{}'.format(num)]["echo"]
    elif not num or str(type(num)) != "<class 'int'>": # 인자에 1~3이 아닌거 썼을때 나가버림
        return sys.exit()
    GPIO.output(trig, False) # trig핀 low로 유지                                            
    GPIO.output(trig, True)  # trig핀 high로 만들어서 초음파 보냄. 10ms동안 유지
    time.sleep(0.000001)
    GPIO.output(trig, False)
                  
    while GPIO.input(echo) == False: # echo핀 low일 때 시간 출력
        pulse_start = time.time()
                      
    while GPIO.input(echo) == True: # echo핀 high일 때 시간 출력
        pulse_end = time.time()
                      
    pulse_duration = pulse_end - pulse_start # high로 유지한 시간 (거리)
    distance = pulse_duration * 17000
    distance = round(distance, 2)
                 ##소수점 둘째자리까지
    if distance >= 20:
        distance = 0;
    print("dis : ",distance)
    return distance      
      

GPIO.cleanup()