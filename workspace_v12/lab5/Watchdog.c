/**********************************************************************
* File: Watchdog.c -- File for Labs 5, 6, 7, 8, 9, 10 and 12
* Devices: TMS320F2806x
* Author: Technical Training Organization (TTO), Texas Instruments
**********************************************************************/

#include "Lab.h"						// Main include file


/**********************************************************************
* Function: InitWatchdog()
*
* Description: Initializes Watchdog Timer for the F2806x
**********************************************************************/
void InitWatchdog(void)
{
	asm(" EALLOW");						// Enable EALLOW protected register access

//--- Disable the Watchdog Timer
	SysCtrlRegs.WDCR = 0x????;
// bit 15-8      0's:    reserved
// bit 7         ?:      WDFLAG
// bit 6         ?:      WDDIS
// bit 5-3       ???:    WDCHK
// bit 2-0       ???:    WDPS

//--- System and Control Register
	SysCtrlRegs.SCSR = 0x????;
// bit 15-3      0's:    reserved
// bit 2         ?:      WDINTS
// bit 1         ?:      WDENINT
// bit 0         ?:      WDOVERRIDE

	asm(" EDIS");						// Disable EALLOW protected register access

//--- Enable the Watchdog interrupt
	                                  	// Enable WAKEINT (LPM/WD) in PIE group #1
	              						// Enable INT1 in IER to enable PIE group 1

} // end of InitWatchdog()


//--- end of file -----------------------------------------------------
