/**********************************************************************
* File: PieCtrl.c -- File for Lab 5, 6, 7, 8, 9, 10 and 12
* Devices: TMS320F2806x
* Author: Technical Training Organization (TTO), Texas Instruments
**********************************************************************/

#include "Lab.h"						// Main include file


/**********************************************************************
* Function: InitPieCtrl()
*
* Description: Initializes and enables the PIE interrupts on the F2806x
**********************************************************************/
void InitPieCtrl(void)
{
//--- Disable interrupts
	asm(" SETC INTM, DBGM");			// Disable global interrupts

//--- Initialize the PIE_RAM

	PieCtrlRegs.PIECTRL.bit.ENPIE = 0;	// Disable the PIE
	asm(" EALLOW");						// Enable EALLOW protected register access

	// Step around the first three 32-bit locations (six 16-bit locations).
	// These locations are used by the ROM bootloader during debug, and also
	// by the Flash API algorithms.
	memcpy((Uint16 *)&PieVectTable+6, (Uint16 *)&PieVectTableInit+6, 256-6);

	asm(" EDIS");						// Disable EALLOW protected register access

//--- Disable all PIE interrupts
	PieCtrlRegs.PIEIER1.all =  0x0000;
	PieCtrlRegs.PIEIER2.all =  0x0000;
	PieCtrlRegs.PIEIER3.all =  0x0000;
	PieCtrlRegs.PIEIER4.all =  0x0000;
	PieCtrlRegs.PIEIER5.all =  0x0000;
	PieCtrlRegs.PIEIER6.all =  0x0000;
	PieCtrlRegs.PIEIER7.all =  0x0000;
	PieCtrlRegs.PIEIER8.all =  0x0000;
	PieCtrlRegs.PIEIER9.all =  0x0000;
	PieCtrlRegs.PIEIER10.all = 0x0000;
	PieCtrlRegs.PIEIER11.all = 0x0000;
	PieCtrlRegs.PIEIER12.all = 0x0000;

//--- Clear any potentially pending PIEIFR flags
	PieCtrlRegs.PIEIFR1.all  = 0x0000;
	PieCtrlRegs.PIEIFR2.all  = 0x0000;
	PieCtrlRegs.PIEIFR3.all  = 0x0000;	
	PieCtrlRegs.PIEIFR4.all  = 0x0000;
	PieCtrlRegs.PIEIFR5.all  = 0x0000;
	PieCtrlRegs.PIEIFR6.all  = 0x0000;
	PieCtrlRegs.PIEIFR7.all  = 0x0000;
	PieCtrlRegs.PIEIFR8.all  = 0x0000;
	PieCtrlRegs.PIEIFR9.all  = 0x0000;
	PieCtrlRegs.PIEIFR10.all = 0x0000;
	PieCtrlRegs.PIEIFR11.all = 0x0000;
	PieCtrlRegs.PIEIFR12.all = 0x0000;

//--- Acknowlege all PIE interrupt groups
	PieCtrlRegs.PIEACK.all = 0xFFFF;

//--- Enable the PIE
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;		// Enable the PIE

} // end of InitPieCtrl()


//--- end of file -----------------------------------------------------
