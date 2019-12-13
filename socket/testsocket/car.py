import RPi.GPIO as GPIO
from time import sleep
STOP  = 0
FORWARD  = 1
BACKWORD = 2
RIGHT = 3
LEFT = 4

CH1 = 0
CH2 = 1


OUTPUT = 1
INPUT = 0


HIGH = 1
LOW = 0

ENA = 16  #37 pin
ENB = 20   #27 pin


IN1 = 17  #37 pin
IN2 = 27  #35 pin
IN3 = 5   #31 pin
IN4 = 6   #29 pin




def setPinConfig(EN, INA, INB):        
    GPIO.setup(EN, GPIO.OUT)
    GPIO.setup(INA, GPIO.OUT)
    GPIO.setup(INB, GPIO.OUT)

    pwm = GPIO.PWM(EN, 100) 
   
    pwm.start(0) 
    return pwm


def setMotorContorl(pwm, INA, INB, speed, stat):


    pwm.ChangeDutyCycle(speed)  
    
    if stat == FORWARD:
        GPIO.output(INA, HIGH)
        GPIO.output(INB, LOW)

    elif stat == BACKWORD:
        GPIO.output(INA, LOW
                    )
        GPIO.output(INB, HIGH)

    elif stat == STOP:
        GPIO.output(INA, LOW)
        GPIO.output(INB, LOW)

        

def setMotor(ch, speed, stat):
    if ch == CH1:
        setMotorContorl(pwmA, IN1, IN2, speed, stat)
    else:
        setMotorContorl(pwmB, IN3, IN4, speed, stat)
  
def setcar(stat):
    t=0.2
    if(stat=="FORWARD"):
        setMotor(CH1, 100, FORWARD)
        setMotor(CH2, 100, FORWARD)
        #sleep(t)
        #setMotor(CH1, 0, STOP)
        #setMotor(CH2, 0, STOP)
    elif(stat=="BACKWARD"):
        setMotor(CH1, 100, BACKWORD)
        setMotor(CH2, 100, BACKWORD)
        #sleep(t)
        #setMotor(CH1, 0, STOP)
        #setMotor(CH2, 0, STOP)
    elif(stat=="RIGHT"):
        setMotor(CH1, 100, BACKWORD)
        setMotor(CH2, 100, FORWARD)
        #sleep(t)
        #setMotor(CH1, 0, STOP)
        #setMotor(CH2, 0, STOP)
    elif(stat=="LEFT"):
        setMotor(CH1, 100, FORWARD)
        setMotor(CH2, 100, BACKWORD)
        #sleep(t)
    elif(stat=="STOP"):
        setMotor(CH1, 0, STOP)
        setMotor(CH2, 0, STOP)
        
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)          

pwmA = setPinConfig(ENA, IN1, IN2)
pwmB = setPinConfig(ENB, IN3, IN4)

'''
print("UP")
setMotor(CH1, 100, FORWARD)
setMotor(CH2, 100, FORWARD)

print("DOWN")
setMotor(CH1, 100, BACKWORD)
setMotor(CH2, 100, BACKWORD)



print("LEFT")
setMotor(CH1, 50, FORWARD)
setMotor(CH2, 50, BACKWORD)
setMotor(CH1, 100, FORWARD)
setMotor(CH2, 100, FORWARD)


print("RIGHT")
setMotor(CH1, 50, BACKWORD)
setMotor(CH2, 50, FORWARD)
setMotor(CH1, 100, FORWARD)
setMotor(CH2, 100, FORWARD)
'''



