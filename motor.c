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

#define ENA 16
#define ENB	20	
void mtrStop()
{
	softPwmWrite(ENA,0);
	softPwmWrite(ENB,0);
}


void mtrCtrl(unsigned char speed, unsigned char rot, unsigned char wheel)
{
	if(wheel==wheelL)
	{
		if(rot==L_ROT)
		{
			digitalWrite(M1_P,LOW);
		//	softPwmWrite(ENA,speed);
		}
		else if(rot==R_ROT)
		{
			digitalWrite(M1_N,LOW);
		//	softPwmWrite(ENA,speed);
		}
	}
	else
	{
		if(rot==L_ROT)
		{
			digitalWrite(M2_P,LOW);
			softPwmWrite(ENA,speed);
		}
		else if(rot==R_ROT)
		{
			digitalWrite(M2_N,LOW);
			softPwmWrite(ENA,speed);
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
	pinMode(ENA, OUTPUT);
	pinMode(ENB, OUTPUT);
	softPwmCreate(ENA, 0, 100);
	softPwmCreate(ENB, 0, 100);
	while(1)
	{
		digitalWrite(M1_P, HIGH);
		digitalWrite(M1_N, LOW);
		softPwmWrite(ENA, 50);
		digitalWrite(M2_P, HIGH);
		digitalWrite(M2_N, LOW);
		softPwmWrite(ENB, 50);
	}
	return 0;
}
