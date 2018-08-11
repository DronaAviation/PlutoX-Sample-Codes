/* Name: PlutoX ClapSensor

 Author: DronaAviation */




// Do not remove the include below
#include "PlutoPilot.h"
#include "Peripheral.h"
#include "Print.h"
#include "Control.h"
#include "Althold.h"
#include "Led.h"

int16_t sensorValue13=0;

//The setup function is called once at Pluto's hardware startup
void plutoInit()
{
// Add your hardware initialization code here
	ADC.Init(Pin13); //ADC initialization
}



//The function is called once before plutoFly when you activate UserCode
void onPilotStart()
{
  // do your one time stuffs here
	 Control.disableFlightStatus(true); //Disable flight status LED

}



// The loop function is called in an endless loop

void plutoPilot()
{

//Add your repeated code here

	sensorValue13=(ADC.Read(Pin13)*340)/4096;	//Convert the input value to voltage

	Print.monitor("ADC13:",sensorValue13 );		//Print the sensor value
	Print.monitor("\n");

	if(sensorValue13>=15) //threshold detection for clap
	{

		ledOp(L_LEFT, ON);	//LED indication
		ledOp(L_RIGHT, OFF);

		//take off
		Control.arm();
		Althold.setRelativeAltholdHeight(200);


	}
}



//The function is called once after plutoFly when you deactivate UserCode
void onPilotFinish()
{
	 Control.disableFlightStatus(false); //Enable flight status LED

	 // do your cleanup stuffs here

}
