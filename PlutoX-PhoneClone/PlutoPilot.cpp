// Do not remove the include below
#include "PlutoPilot.h"
#include "App.h"
#include "Control.h"
#include "Led.h"


int16_t appheading=0;

//The setup function is called once at Pluto's hardware startup
void plutoInit()
{
// Add your hardware initialization code here
}



//The function is called once before plutoPilot when you activate UserCode
void onPilotStart()
{
  // do your one time stuffs here
  Control.disableFlightStatus(true); 		//disable the led
  ledOp(L_RIGHT, ON);
  ledOp(L_MID, OFF);
  ledOp(L_LEFT, ON);



}



// The loop function is called in an endless loop
void plutoPilot()
{

//Add your repeated code here


	   appheading=App.getAppHeading(); 		//Get the heading of phone





		appheading+=90; 		//Error correction

		if(appheading>360)
			appheading-=360;








		Control.setHeading(appheading); 		//Set the drone heading as the phones


}



//The function is called once after plutoPilot when you deactivate UserCode
void onPilotFinish()
{

// do your cleanup stuffs here
	Control.disableFlightStatus(false); //Enable the Led

}




