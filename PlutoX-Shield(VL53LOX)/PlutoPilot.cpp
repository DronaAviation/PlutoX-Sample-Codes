/* Name: PlutoX Shield(VL53LOX)

 Author: DronaAviation */




// Do not remove the include below
#include "PlutoPilot.h"
#include "Xshield.h"
#include "Control.h"
#include "Led.h"
#include "Print.h"


//The setup function is called once at Pluto's hardware startup
void plutoInit()
{
// Add your hardware initialization code here

	Xshield.init(); //Initialize the shield
}



//The function is called once before plutoFly when you activate UserCode
void onPilotStart()
{
  // do your one time stuffs here
	Control.disableExternalRC(RC_ROLL);
	Xshield.startRanging();  // start LASER ranging
	Control.disableFlightStatus(true);
	ledOp(L_MID, OFF);
	ledOp(L_LEFT, OFF);
	ledOp(L_RIGHT, OFF);

}



// The loop function is called in an endless loop
void plutoPilot()
{




//Add your repeated code here
if(Xshield.getRange(LEFT)<300)
{

Control.setRC(RC_ROLL, 2000);
ledOp(L_LEFT, ON);
ledOp(L_RIGHT, OFF);

}

if(Xshield.getRange(RIGHT)<300)
{

Control.setRC(RC_ROLL, 1000);
ledOp(L_LEFT, OFF);
ledOp(L_RIGHT, ON);
}


}




//The function is called once after plutoFly when you deactivate UserCode
void onPilotFinish()
{

	 // do your cleanup stuffs here
	Control.enableAllExternalRC();
	Xshield.stopRanging();
	Control.disableFlightStatus(false);

}




