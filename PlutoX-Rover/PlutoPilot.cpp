/* Name: PlutoX Rover

 Author: DronaAviation */


// Do not remove the include below
#include  "PlutoPilot.h"
#include  "Control.h"
#include  "Motor.h"
#include  "Print.h"
#include  "Angle.h"
#include  "Led.h"

#define ABS(x) ((x) > 0 ? (x) : -(x))

int16_t roll_value;
int16_t throttle_value;
int16_t m1m2Value;
int16_t m3m4Value;

bool isAutoStablised=false;
int16_t setHeading=0;
int16_t heading_error=0;
int16_t k=15;

int constrain(int amt, int low, int high);
int generatePWM(int amt);

//The setup function is called once at Pluto's hardware startup
void plutoInit()
{
// Add your hardware initialization code here
}



//The function is called once before plutoFly when you activate UserCode
void onPilotStart()
{
  // do your one time stuffs here



	roll_value=0;
	throttle_value=0;
	Control.disableFlightStatus(true);
	ledOp(L_MID, OFF);
	ledOp(L_LEFT, OFF);
	ledOp(L_RIGHT, OFF);



}



// The loop function is called in an endless loop
void plutoPilot()
{

//Add your repeated code here

if(Control.getRC(RC_PITCH)>=1930)
	{
		isAutoStablised=true;
		setHeading=Angle.get(AG_YAW);
		ledOp(L_LEFT, ON);
		ledOp(L_RIGHT, OFF);

	}

else if(Control.getRC(RC_PITCH)<1070)
	{
		isAutoStablised=false;
		ledOp(L_LEFT, OFF);
		ledOp(L_RIGHT, ON);
	}



if(isAutoStablised)
{


	if(ABS(Control.getRC(RC_ROLL)-1500)<30)
	{
		heading_error=setHeading-Angle.get(AG_YAW);


		if(heading_error>180)
			heading_error=heading_error-360;

		else if(heading_error<-180)
			heading_error=heading_error+360;

		roll_value=1500 +k*heading_error;
	}
	else
	{
		roll_value=Control.getRC(RC_ROLL);
		setHeading=Angle.get(AG_YAW);
	}

}
else
{

	 roll_value=Control.getRC(RC_ROLL);
}


throttle_value=Control.getRC(RC_THROTTLE);




m1m2Value=(throttle_value-1500)+(roll_value-1500)/2;

m1m2Value=constrain(m1m2Value, -500, 500);

m3m4Value=(throttle_value-1500)-(roll_value-1500)/2;


m3m4Value=constrain(m3m4Value, -500, 500);



if(m1m2Value<0)
{

	Motor.setDirection(M1, FORWARD);
	Motor.setDirection(M2, FORWARD);


}
else
{
	Motor.setDirection(M1, BACKWARD);
	Motor.setDirection(M2, BACKWARD);

}



Motor.set(M1, generatePWM(m1m2Value));
Motor.set(M2, generatePWM(m1m2Value));



if(m3m4Value<0)
{


	 Motor.setDirection(M3, BACKWARD);
	 Motor.setDirection(M4, BACKWARD);


}
else
{

	 Motor.setDirection(M3, FORWARD);
	 Motor.setDirection(M4, FORWARD);


}


Motor.set(M3, generatePWM(m3m4Value));
Motor.set(M4, generatePWM(m3m4Value));


}



//The function is called once after plutoFly when you deactivate UserCode
void onPilotFinish()
{

	 // do your cleanup stuffs here



	Control.disableFlightStatus(false);
	  Motor.set(M1, 1000);
	  Motor.set(M2, 1000);
	  Motor.set(M3, 1000);
	  Motor.set(M4, 1000);


}




int constrain(int amt, int low, int high)
{
    if (amt < low)
        return low;
    else if (amt > high)
        return high;
    else
        return amt;
}

int generatePWM(int amt)
{

	amt= ABS(amt);

	amt=1000+(amt*2);

	return amt;




}
