/* Name: PlutoX Hybrid

 Author: DronaAviation */




// Do not remove the include below
#include "PlutoPilot.h"
#include "Control.h"
#include "Motor.h"
#include "Print.h"
#include "Angle.h"
#include "Led.h"
#include "Althold.h"
#include "App.h"
#include "Servo.h"

#define ABS(x) ((x) > 0 ? (x) : -(x))

bool isAutoStablised=false;
bool isArmed=false;
int16_t setHeading=0;
int16_t heading_error=0;
int16_t k=10;

int16_t M3_Value;
int16_t M2_Value;

int16_t M2_Valuef;
int16_t M3_Valuef;

int16_t Roll_value;
int16_t Throttle_value;

int constrain(int amt, int low, int high);
int generatePWM(int amt);

//The setup function is called once at Pluto's hardware startup
void plutoInit()
{

// Add your hardware initialization code here
	Servo.set(S1, 1900);  
}



//The function is called once before plutoPilot when you activate UserCode
void onPilotStart()
{

	Control.disableFlightStatus(true);

	Roll_value=0;
	Throttle_value=0;

  // do your one time stuffs here

}



// The loop function is called in an endless loop
void plutoPilot()
{
	if(!App.isArmSwitchOn())

		{
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

					Roll_value=1500 +k*heading_error;
				}
				else
				{
					Roll_value=Control.getRC(RC_ROLL);
					setHeading=Angle.get(AG_YAW);
				}

			}
			else
			{

				 Roll_value=Control.getRC(RC_ROLL);
			}


			Throttle_value = Control.getRC(RC_THROTTLE);


			M3_Value =  (Throttle_value-1500)*2-(Roll_value-1500)/2;
			M3_Value =  constrain(M3_Value, -500, 500);
			M2_Value =  (Throttle_value-1500)*2+(Roll_value-1500)/2;
			M2_Value =  constrain(M2_Value, -500, 500);

			if(M2_Value<0)
			{


				Motor.setDirection(M2, FORWARD);


			}
			else
			{

				Motor.setDirection(M2, BACKWARD);

			}
			if(M3_Value<0)
			{


				 Motor.setDirection(M3, BACKWARD);



			}
			else
			{

				 Motor.setDirection(M3, FORWARD);



			}

			M2_Valuef =generatePWM(M2_Value);
			M3_Valuef =generatePWM(M3_Value);

			Motor.set(M3,M3_Valuef);
			Motor.set(M2,M2_Valuef);
			Print.monitor("M2:", M2_Valuef);
			Print.monitor("M3:",M3_Valuef );


		}
	else
	{
		Motor.set(M2, 1000);
		Motor.set(M3, 1000);

        if(!isArmed)
        {

        	isArmed=Control.arm();

           if(isArmed)
           {
        	   Althold.setRelativeAltholdHeight(200);
        	   Servo.set(S1, 600);


           }

        }


	}


//Add your repeated code here



}



//The function is called once after plutoPilot when you deactivate UserCode
void onPilotFinish()
{
	   isArmed=false;
	   Control.disableFlightStatus(false);
	   Servo.set(S1, 1900);
	   Motor.set(M2, 1000);
	   Motor.set(M3, 1000);

// do your cleanup stuffs here

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
