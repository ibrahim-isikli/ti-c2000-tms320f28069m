/**********************************************************************
* File: SysCtrl.c -- File for Labs 5, 6, 7, 8, 9, 10 and 12
* Devices: TMS320F2806x
* Author: Technical Training Organization (TTO), Texas Instruments
**********************************************************************/

#include "Lab.h"						// Main include file


/**********************************************************************
* Function: InitSysCtrl()
* Description: Initializes the F2806x CPU
**********************************************************************/
void InitSysCtrl(void)
{
	asm(" EALLOW");						// Enable EALLOW protected register access

//--- Call the Device_cal() function located in reserved OTP.
//    Device_cal_func_ptr is a macro defined in the file example_nonBIOS.h or
//    example_BIOS.h (as may be the case for the example being used).  This
//    macro simply defines Device_cal_func_ptr to be a function pointer to
//    the correct address in the reserved OTP.  Note that the device cal function
//    is automatically called by the bootloader.  A call to this function is
//    included here just in case the bootloader is bypassed during development.

	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;	// Enable ADC peripheral clock
	(*Device_cal_func_ptr)();				// Call the device calibration routine
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 0; 	// Disable ADC peripheral clock

//--- Memory Protection Configuration
	DevEmuRegs.DEVICECNF.bit.ENPROT = 1;	// Enable write/read protection

//--- Configure the clock sources
	SysCtrlRegs.CLKCTL.all = 0x6400;		// Configure the clock control register
// bit 15        0:      NMIRESETSEL, NMI reset select for missing clock detect, 0=direct reset, 1=NMI WD causes reset
// bit 14        1:      XTALOSCOFF, Crystal oscillator off, 0=on, 1=off
// bit 13        1:      XCLKINOFF, XCLKIN input off, 0=on, 1=off
// bit 12        0:      WDHALTI, WD halt ignore, 0=WD turned off by HALT, 1=WD ignores HALT
// bit 11        0:      INTOSC2HALTI, OSC2 halt ignore, 0=OSC2 turned off by HALT, 1=OSC2 ignores HALT
// bit 10        1:      INTOSC2OFF, OSC2 off, 0=on, 1=off
// bit 9         0:      INTOSC1HALTI, OSC1 halt ignore, 0=OSC1 turned off by HALT, 1=OSC1 ignores HALT
// bit 8         0:      INTOSC1OFF, OSC1 off, 0=on, 1=off
// bit 7-5       000:    TMR2CLKPRESCALE, Timer2 prescale, 000=/1
// bit 4-3       00:     TMR2CLKSCRSEL, Timer2 source, 00=SYSCLKOUT, 01=ext. OSC, 10=OSC1, 11=OSC2
// bit 2         0:      WDCLKSRCSEL, WD source, 0=OSC1, 1=ext. OSC or OSC2
// bit 1         0:      OSCCLKSRC2SEL, clock src2 select, 0=ext OSC, 1=OSC2
// bit 0         0:      OSCCLKSRCSEL, clock src1 select, 0=OSC1, 1=ext. OSC or OSC2

	SysCtrlRegs.XCLK.all = 0x0040;			// Configure the clocking register
// bit 15-7    0's:      reserved
// bit 6         1:      XCLKINSEL, XCLKIN source, 0=GPIO38, 1=GPIO19 (default) (Note: GPIO38 is JTAG TCK!)
// bit 5-2     0's:      reserved
// bit 1-0      00:      XCLKOUTDIV, XCLKOUT divide ratio, 00=SYSCLKOUT/4, 01=SYSCLKOUT/2, 10=SYSCLKOUT, 11=off

//--- Configure the PLL
// Note: The DSP/BIOS configuration tool can also be used to initialize the PLL
// instead of doing the initialization here.

	// Make sure the PLL is not running in limp mode
	if (SysCtrlRegs.PLLSTS.bit.MCLKSTS != 1)
	{													// PLL is not running in limp mode
		SysCtrlRegs.PLLSTS.bit.MCLKOFF = 1;				// Turn off missing clock detect before changing PLLCR
		SysCtrlRegs.PLLSTS.bit.DIVSEL = 0;				// DIVSEL must be 0 or 1 (/4 CLKIN mode) before changing PLLCR
		SysCtrlRegs.PLLCR.bit.DIV = 0x0012;				// PLLx18/4 (because DIVSEL is /4)
   
		// Wait for PLL to lock.
		// During this time the CPU will run at OSCCLK/4 until the PLL is stable.
		// Once the PLL is stable the CPU will automatically switch to the new PLL value.
		// Code is not required to sit and wait for the PLL to lock.  However, 
		// if the code does anything that is timing critical (e.g. something that
		// relies on the CPU clock frequency to be at speed), then it is best to wait
		// until PLL lock is complete.  The watchdog should be disabled before this loop
		// (e.g., as was done above), or fed within the loop.
		while(SysCtrlRegs.PLLSTS.bit.PLLLOCKS != 1)		// Wait for PLLLOCKS bit to set
		{
			SysCtrlRegs.WDKEY = 0x0055;					// Service the watchdog while waiting
			SysCtrlRegs.WDKEY = 0x00AA;					//   in case the user enabled it.
		}

		// After the PLL has locked, we are running in PLLx18/4 mode (since DIVSEL is /4).
		// We can now enable the missing clock detect circuitry, and also change DIVSEL
		// to /2.  In this example, I will wait a bit of time to let inrush currents settle,
		// and then change DIVSEL from /4 to /2.  This is only an example.  The amount of
		// time you need to wait depends on the power supply feeding the DSP (i.e., how much
		// voltage droop occurs due to the inrush currents, and how long it takes the
		// voltage regulators to recover).
		SysCtrlRegs.PLLSTS.bit.MCLKOFF = 0;				// Enable missing clock detect circuitry
		DelayUs(20/2);									// Wait 20 us (just an example).  Remember we're running
														// at half-speed here, so divide function argument by 2.
		SysCtrlRegs.PLLSTS.bit.DIVSEL = 0x2;			// Change to /2 mode
	}
	else
	{													// PLL is running in limp mode
	// User should replace the below with a call to an appropriate function,
	// for example shutdown the system (since something is very wrong!).
		asm(" ESTOP0");
	}

//--- Configure the clocks
	SysCtrlRegs.LOSPCP.all = 0x????;			// Lo-speed periph clock prescaler, LSPCLK=SYSCLKOUT/4

	SysCtrlRegs.PCLKCR3.bit.USB0ENCLK = ?;		// SYSCLKOUT to USB0 enabled
	SysCtrlRegs.PCLKCR3.bit.CLA1ENCLK = ?;		// SYSCLKOUT to CLA1 enabled
	SysCtrlRegs.PCLKCR3.bit.DMAENCLK = ?;		// SYSCLKOUT to DMA enabled
	SysCtrlRegs.PCLKCR3.bit.CPUTIMER2ENCLK = ?;	// SYSCLKOUT to CPU Timer2 enabled
	SysCtrlRegs.PCLKCR3.bit.CPUTIMER1ENCLK = ?;	// SYSCLKOUT to CPU Timer1 enabled
	SysCtrlRegs.PCLKCR3.bit.CPUTIMER0ENCLK = ?;	// SYSCLKOUT to CPU Timer0 enabled
	SysCtrlRegs.PCLKCR3.bit.COMP3ENCLK = ?;		// SYSCLKOUT to COMP3 enabled
	SysCtrlRegs.PCLKCR3.bit.COMP2ENCLK = ?;		// SYSCLKOUT to COMP2 enabled
	SysCtrlRegs.PCLKCR3.bit.COMP1ENCLK = ?;		// SYSCLKOUT to COMP1 enabled

	SysCtrlRegs.PCLKCR2.bit.HRCAP4ENCLK = ?;	// SYSCLKOUT to HRCAP4 enabled
	SysCtrlRegs.PCLKCR2.bit.HRCAP3ENCLK = ?;	// SYSCLKOUT to HRCAP4 enabled
	SysCtrlRegs.PCLKCR2.bit.HRCAP2ENCLK = ?;	// SYSCLKOUT to HRCAP4 enabled
	SysCtrlRegs.PCLKCR2.bit.HRCAP1ENCLK = ?;	// SYSCLKOUT to HRCAP4 enabled

	SysCtrlRegs.PCLKCR1.bit.EQEP2ENCLK = ?;		// SYSCLKOUT to eQEP2 enabled
	SysCtrlRegs.PCLKCR1.bit.EQEP1ENCLK = ?;		// SYSCLKOUT to eQEP1 enabled
	SysCtrlRegs.PCLKCR1.bit.ECAP3ENCLK = ?;		// SYSCLKOUT to eCAP3 enabled
	SysCtrlRegs.PCLKCR1.bit.ECAP2ENCLK = ?;		// SYSCLKOUT to eCAP2 enabled
	SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = ?;		// SYSCLKOUT to eCAP1 enabled
	SysCtrlRegs.PCLKCR1.bit.EPWM8ENCLK = ?;		// SYSCLKOUT to ePWM8 enabled
	SysCtrlRegs.PCLKCR1.bit.EPWM7ENCLK = ?;		// SYSCLKOUT to ePWM7 enabled
	SysCtrlRegs.PCLKCR1.bit.EPWM6ENCLK = ?;		// SYSCLKOUT to ePWM6 enabled
	SysCtrlRegs.PCLKCR1.bit.EPWM5ENCLK = ?;		// SYSCLKOUT to ePWM5 enabled
	SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = ?;		// SYSCLKOUT to ePWM4 enabled
	SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = ?;		// SYSCLKOUT to ePWM3 enabled
	SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = ?;		// SYSCLKOUT to ePWM2 enabled
	SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = ?;		// SYSCLKOUT to ePWM1 enabled

	SysCtrlRegs.PCLKCR0.bit.ECANAENCLK = ?;		// SYSCLKOUT/2 to ECAN-A enabled
	SysCtrlRegs.PCLKCR0.bit.MCBSPAENCLK = ?;	// LSPCLK to MCBSP-A enabled
	SysCtrlRegs.PCLKCR0.bit.SCIBENCLK = ?;		// LSPCLK to SCI-B enabled
	SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = ?;		// LSPCLK to SCI-A enabled
	SysCtrlRegs.PCLKCR0.bit.SPIBENCLK = ?;		// LSPCLK to SPI-B enabled
	SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = ?;		// LSPCLK to SPI-A enabled
	SysCtrlRegs.PCLKCR0.bit.I2CAENCLK = ?;		// SYSCLKOUT to I2C-A enabled
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = ?;		// SYSCLKOUT to ADC enabled
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;		// TBCLKSYNC bit is handled separately in InitEPwm() since it affects ePWM synchronization
	SysCtrlRegs.PCLKCR0.bit.HRPWMENCLK = ?;		// SYSCLKOUT to HRPWM enabled

//--- Configure the low-power modes
	SysCtrlRegs.LPMCR0.all = 0x????;	// LPMCR0 set to default value

//--- Finish up
	asm(" EDIS");						// Disable EALLOW protected register access

} // end InitSysCtrl()


//--- end of file -----------------------------------------------------
