#include <stdio.h>
#include <wiringPi.h>
#include <softTone.h>
#include <softPwm.h>

#define KEY_1 20	// up
#define KEY_2 25	// down
#define KEY_3 21	// right 
#define KEY_4 16	// left
#define M1_N_PIN 17	// left Wheel
#define M1_P_PIN 27	// left Wheel
#define M2_N_PIN 5	// right Wheel
#define M2_P_PIN 7	// right Wheel

#define MAX_KEY 4
#define LEFT_ROTATE 	1
#define RIGHT_ROTATE	2
const int KEYTable[MAX_KEY] =	{KEY_1,KEY_2,KEY_3,KEY_4,};					 
//const char KEYChar[MAX_KEY] =	{'1', '2', '3', '4', '5', '6', '7', '8', '9', '*','0','#',};
int kRead()
{
	int i,kStat=0;	
	for(i=0;i<MAX_KEY;i++)
		if( !digitalRead(KEYTable[i]) )
			kStat |=(1<<i);
	return kStat;
}

void MotorStop()
{
	softPwmWrite(M1_N_PIN,0);
	softPwmWrite(M1_P_PIN,0);
}
void MotorStop2()
{
	softPwmWrite(M2_N_PIN,0);
	softPwmWrite(M2_P_PIN,0);
}

void MotorControl(unsigned char speed, unsigned char rotate)
{
	if(rotate == LEFT_ROTATE)
	{
		digitalWrite(M1_P_PIN,LOW);
		softPwmWrite(M1_N_PIN,speed);
	}

	else if(rotate == RIGHT_ROTATE)
	{
		digitalWrite(M1_N_PIN,LOW);
		softPwmWrite(M1_P_PIN,speed);
	}
}
void MotorControl2(unsigned char speed, unsigned char rotate)
{
	if(rotate == LEFT_ROTATE)
	{
		digitalWrite(M2_P_PIN,LOW);
		softPwmWrite(M2_N_PIN,speed);
	}

	else if(rotate == RIGHT_ROTATE)
	{
		digitalWrite(M2_N_PIN,LOW);
		softPwmWrite(M2_P_PIN,speed);
	}
}

int main()
{
	int i,j=0,kStat,speed=0;
	if(wiringPiSetupGpio()==-1)
		return 1;
	for(i=0; i<MAX_KEY;i++)
		pinMode(KEYTable[i], INPUT);
	pinMode(M1_P_PIN, OUTPUT);
	pinMode(M1_N_PIN, OUTPUT);
	pinMode(M2_P_PIN, OUTPUT);
	pinMode(M2_N_PIN, OUTPUT);
	softPwmCreate(M1_P_PIN, 0, 100);
	softPwmCreate(M1_N_PIN, 0, 100);
	softPwmCreate(M2_P_PIN, 0, 100);
	softPwmCreate(M2_N_PIN, 0, 100);
	while(1)
	{
		kStat=kRead();

		for(i=0; i<MAX_KEY;i++)
		{
			if( ( kStat & ( 1<<i ) ) )			// 0000  0001 << 0~2 0000 0010 & 0000 0010 
			{
				switch(i)
				{
					case 0:
						MotorControl(10, RIGHT_ROTATE);
						MotorControl2(10, RIGHT_ROTATE);
						printf("UP!! \n");
						delay(2000);
						MotorStop();
						MotorStop2();
						break;
					case 1:
						MotorControl(10, LEFT_ROTATE);
						MotorControl2(10, LEFT_ROTATE);
						printf("DOWN!! \n");
						delay(2000);
						MotorStop();
						MotorStop2();
						break;
					case 2:
						MotorControl(10, RIGHT_ROTATE);
						MotorControl2(10, LEFT_ROTATE);
						printf("RIGHT!! \n");
						delay(2000);
						MotorStop();
						MotorStop2();
						break;
					case 3:
						MotorControl(10, LEFT_ROTATE);
						MotorControl2(10, RIGHT_ROTATE);
						printf("LEFT!! \n");
						delay(2000);
						MotorStop();
						MotorStop2();
				}
			}
		}
	}
	return 0;
}
