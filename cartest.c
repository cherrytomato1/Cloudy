#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>


#define M1_N 17		// left Wheel
#define M1_P 27		// right wheel

#define M2_N 5		// right Wheel
#define M2_P 6		// right Wheel

#define L_ROT 1 	// rotate left
#define R_ROT 2 	// rotate right

#define wheelL 0
#define wheelR	1	


void mtrStop()
{
	softPwmWrite(M1_N,0);
	softPwmWrite(M1_P,0);
	softPwmWrite(M2_N,0);
	softPwmWrite(M2_P,0);
}


void mtrCtrl(unsigned char speed, unsigned char rot, unsigned char wheel)
{
	if(wheel==wheelL)
	{
		if(rot==L_ROT)
		{
			digitalWrite(M1_P,LOW);
			softPwmWrite(M1_N,speed);
		}
		else if(rot==R_ROT)
		{
			digitalWrite(M1_N,LOW);
			softPwmWrite(M1_P,speed);
		}
	}
	else
	{
		if(rot==L_ROT)
		{
			digitalWrite(M2_P,LOW);
			softPwmWrite(M2_N,speed);
		}
		else if(rot==R_ROT)
		{
			digitalWrite(M2_N,LOW);
			softPwmWrite(M2_P,speed);
		}
	}
}

void foward(unsigned char speed)
{
	mtrCtrl(speed,L_ROT,wheelL);
	mtrCtrl(speed,L_ROT,wheelR);
}
void rot_L(unsigned char speed)
{
	mtrCtrl(speed,R_ROT,wheelL);
	mtrCtrl(speed,L_ROT,wheelR);
}

void rot_R(unsigned char speed)
{
	mtrCtrl(speed,L_ROT,wheelL);
	mtrCtrl(speed,R_ROT,wheelR);
}

int main()
{
	int i,j;
	if(wiringPiSetupGpio()==-1)
		return 1;

	pinMode(M1_P, OUTPUT);
	pinMode(M1_N, OUTPUT);
	pinMode(M2_P, OUTPUT);
	pinMode(M2_N, OUTPUT);
	softPwmCreate(M1_P, 0, 100);
	softPwmCreate(M1_N, 0, 100);
	softPwmCreate(M2_P, 0, 100);
	softPwmCreate(M2_N, 0, 100);
	while(1)
	{
		foward(10);
		delay(2000);
		mtrStop();
		
		delay(2000);
		
		
		rot_L(10);
		delay(2000);
		mtrStop();
		
		rot_R(10);
		delay(1000);
		
		mtrStop();
		delay(1000);
		digitalWrite(M2_N,LOW);
		softPwmWrite(M2_P,100);
		delay(1500);
	}
	return 0;
}
