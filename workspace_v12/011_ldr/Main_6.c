/**********************************************************************
* File: Main_6.c -- File for Lab 6
* Devices: TMS320F2806x
* Author: Technical Training Organization (TTO), Texas Instruments
**********************************************************************/

#include "Lab.h"						// Main include file

//--- Global Variables
Uint16 AdcBuf[ADC_BUF_LEN];					// ADC buffer allocation
Uint16 DEBUG_TOGGLE = 1;					// Used for realtime mode investigation test


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
	InitPieCtrl();						// Initialize and enable the PIE (FILE: PieCtrl.c)
	InitWatchdog();						// Initialize the Watchdog Timer (FILE: WatchDog.c)
	InitAdc(); // ADC config init
	InitEPwm(); // EPwm config init
//--- Peripheral Initialization
	          							// Initialize the ADC (FILE: Adc.c)
	           							// Initialize the EPwm (FILE: EPwm.c)

//--- Enable global interrupts
	asm(" CLRC INTM, DBGM");			// Enable global interrupts and realtime debug

//--- Main Loop
	while(1)							// endless loop - wait for an interrupt
	{
		asm(" NOP");
	}


} //end of main()


/*** end of file *****************************************************/
