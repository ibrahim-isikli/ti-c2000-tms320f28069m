/**********************************************************************
* File: Main_5.c -- File for Lab 5
* Devices: TMS320F2806x
* Author: Technical Training Organization (TTO), Texas Instruments
**********************************************************************/

#include "Lab.h"						// Main include file


/**********************************************************************
* Function: main()
*
* Description: Main function for C28x workshop labs
**********************************************************************/
void main(void)
{
//--- CPU Initialization
	InitSysCtrl();						// Initialize the CPU (FILE: SysCtrl.c)
	InitGpio();							// Initialize the shared GPIO pins (FILE: Gpio.c)
	              						// Initialize and enable the PIE (FILE: PieCtrl.c)
	InitWatchdog();						// Initialize the Watchdog Timer (FILE: WatchDog.c)

//--- Enable global interrupts
	                  					// Enable global interrupts

//--- Main Loop
	while(1)							// endless loop - wait for an interrupt
	{
		asm(" NOP");
	}


} //end of main()


/*** end of file *****************************************************/
