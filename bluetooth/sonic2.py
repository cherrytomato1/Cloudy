#-*- coding: utf-8 -*-
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
so = 0
trig = 12
echo = 26

GPIO.setup(trig, GPIO.OUT)
GPIO.setup(echo, GPIO.IN)
def sendsonic(dis):
    so = 0
    if dis < 5:
        so = 1
    elif 5 <= dis < 10:
        so = 2
    elif 10 <= dis < 15:
        so = 3
    elif 15 <= dis < 20:
        so = 4
    elif 20 <= dis < 25:
        so = 5
    return so
try:
    while True:
        GPIO.output(trig, False) # trig핀 low로 유지
        time.sleep(0.5)
          
        ## trig핀 high로 만들어서 초음파 보냄. 10ms동안 유지
        GPIO.output(trig, True)
        time.sleep(0.00001)
        GPIO.output(trig, False)
          
        while GPIO.input(echo) == False: # echo핀 low일 때 시간 출력
            pulse_start = time.time()
              
        while GPIO.input(echo) == True: # echo핀 high일 때 시간 출력
            pulse_end = time.time()
              
        pulse_duration = pulse_end - pulse_start # high로 유지한 시간 (거리)
        distance = pulse_duration * 17000
        distance = round(distance, 2)
          ##소수점 둘째자리까지
          
        print("Distance : ", distance, "cm")
          
except:
    GPIO.cleanup()