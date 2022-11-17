/**********************************************************************
* File: Adc.c -- File for Lab 6, 7, 8, 9, 10 and 12 (not used in Lab 5)
* Devices: TMS320F2806x
* Author: Technical Training Organization (TTO), Texas Instruments
**********************************************************************/

#include "Lab.h"				// Main include file


/**********************************************************************
* Function: InitAdc()
*
* Description: Initializes the ADC on the F2806x
**********************************************************************/
void InitAdc(void)
{
	asm(" EALLOW");						// Enable EALLOW protected register access

//--- Power-up and configure the ADC
	AdcRegs.ADCCTL1.all = 0x00E4;		// Power-up reference and main ADC
// bit 15        0:      RESET, ADC software reset, 0=no effect, 1=resets the ADC
// bit 14        0:      ADCENABLE, ADC enable, 0=disabled, 1=enabled
// bit 13        0:      ADCBSY, ADC busy, read-only
// bit 12-8      0's:    ADCBSYCHN, ADC busy channel, read-only
// bit 7         1:      ADCPWDN, ADC power down, 0=powered down, 1=powered up
// bit 6         1:      ADCBGPWD, ADC bandgap power down, 0=powered down, 1=powered up 
// bit 5         1:      ADCREFPWD, ADC reference power down, 0=powered down, 1=powered up 
// bit 4         0:      reserved
// bit 3         0:      ADCREFSEL, ADC reference select, 0=internal, 1=external
// bit 2         1:      INTPULSEPOS, INT pulse generation, 0=start of conversion, 1=end of conversion
// bit 1         0:      VREFLOCONV, VREFLO convert, 0=VREFLO not connected, 1=VREFLO connected to B5
// bit 0         0:      TEMPCONV, Temperature sensor convert.  0=ADCINA5 is pin, 1=ADCINA5 is temp sensor

	AdcRegs.ADCCTL2.all = 0x0001;		// ADC clock configuration
// bit 15-3      0's:    reserved
// bit 2         0:      CLKDIV4EN, ADC clock divider.  0=no effect, 1=CPUCLK/4 if CLKDIV2EN=1 (else no effect)
// bit 1         0:      ADCNONOVERLAP, 0=overlap sample and conversion, 1=no overlap 
// bit 0         1:      CLKDIV2EN, ADC clock divider.  0=CPUCLK, 1=CPUCLK/2

	DelayUs(1000);						// Wait 1 ms after power-up before using the ADC

//--- SOC0 configuration
	AdcRegs.ADCSAMPLEMODE.bit.SIMULEN0 = 0;		// SOC sample mode

	AdcRegs.ADCSOC0CTL.bit.TRIGSEL = 7;			// Trigger -> ADCTRIG7 – ePWM2, ADCSOCA selected
	AdcRegs.ADCSOC0CTL.bit.CHSEL = 0;			// Convert channel -> ADCINA0
	AdcRegs.ADCSOC0CTL.bit.ACQPS = 6;			// Acquisition window ->Sample window is 7 cycles long (6 + 1 clock cycles).

	AdcRegs.ADCINTSOCSEL1.bit.SOC0 = 0;			// ADCINT triggers -> No ADCINT will trigger SOCx.

	AdcRegs.SOCPRICTL.bit.SOCPRIORITY = 0;		// SOC priority mode -> all robin mode

//--- ADCINT1 configuration
	AdcRegs.INTSEL1N2.bit.INT1CONT = 1;			// ADCINT pulses -> EOC pulse is generated
	AdcRegs.INTSEL1N2.bit.INT1E = 1;			// Enable ADCINT -> ADCINT1 is enabled
	AdcRegs.INTSEL1N2.bit.INT1SEL = 0;			// EOC triggers ->EOC0 is trigger for ADCINTx

//--- Enable the ADC interrupt
	 PieCtrlRegs.PIEIER1.bit.INTx1=1;                           // Enable ADCINT1 in PIE group 1
	 IER |= 0x0001;             								// Enable INT1 in IER to enable PIE group

//--- Finish up
	AdcRegs.ADCCTL1.bit.ADCENABLE = 1;	// Enable the ADC
	asm(" EDIS");						// Disable EALLOW protected register access

} // end InitAdc()


//--- end of file -----------------------------------------------------
