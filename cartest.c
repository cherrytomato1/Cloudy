#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>


#define M1_N 17		// left Wheel
#define M1_P 27		// right wheel

#define M2_N 5		// right Wheel
#define M2_P 7		// right Wheel

#define L_ROTATE 1 	// rotate left
#define R_ROTATE 2 	// rotate right

#define wheelL 0
#define wheelR	1	


void MotorStop()
{
	softPwmWrite(M1_N_PIN,0);
	softPwmWrite(M1_P_PIN,0);
	softPwmWrite(M1_N_PIN,0);
	softPwmWrite(M1_P_PIN,0);
}


void mtrCtrl(unsigned char speed, unsigned char rot, unsighed char wheel)
{
	unsigned char rot,whl;
	if(wheel==wheelL)
	{
		if(rot==L_ROTATE)
		{
			digitalWrite(M1_P,LOW);
			softPwmWrite(M1_N,speed);
		}
		else if(rot==R_ROTATE)
		{
			digitalWrite(M1_N,LOW);
			softPwmWrite(M1_P,speed);
		}
	}
	else
	{
		if(rot==L_ROTATE)
		{
			digitalWrite(M2_P,LOW);
			softPwmWrite(M2_N,speed);
		}
		else if(rot==R_ROTATE)
		{
			digitalWrite(M2_N,LOW);
			softPwmWrite(M2_P,speed);
		}
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

void foward(unsigned char speed)
{
	mtrCtrl(speed,L_rotate,wheelL);
	mtrCtrl(speed,L_rotate,wheelR);
}
void rot_L(unsigned char speed)
{
	mtrCtrl(speed,R_rotate,wheelL);
	mtrCtrl(speed,L_rotate,wheelR);
}

void rot_R(unsigned char speed)
{
	mtrCtrl(speed,L_rotate,wheelL);
	mtrCtrl(speed,R_rotate,wheelR);
}

int main()
{
	int i,j;
	if(wiringPiSetupGpio()==-1)
		return 1;

	pinMode(M1_P, OUTPUT);
	pinMode(M1_N, OUTPUT);
	pinMode(M2_P, OUTPUT);
	pinMode(M2_N_PIN, OUTPUT);
	softPwmCreate(M1_P, 0, 100);
	softPwmCreate(M1_N, 0, 100);
	softPwmCreate(M2_P, 0, 100);
	softPwmCreate(M2_N, 0, 100);
	while(1)
	{
		forward(50);
		delay(1000);
		rot_L(50);
		delay(1000);
		rot_R(50);
		delay(1000);
	}
	return 0;
}
