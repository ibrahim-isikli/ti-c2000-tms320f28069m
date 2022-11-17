/**********************************************************************
* File: lab.h
* Device: TMS320F2806x
* Author: Technical Training Organization (TTO), Texas Instruments
* Description: Include file for C28x workshop labs.  Include this
* file in all C-source files.
**********************************************************************/

#ifndef LAB_H
#define LAB_H


//---------------------------------------------------------------------------
// Include Standard C Language Header Files
//
#include <string.h>


//---------------------------------------------------------------------------
// Include any other Header Files
//
#include "F2806x_Device.h"              // F2806x header file peripheral address definitions
#include "F2806x_DefaultIsr.h"          // ISR definitions - used in Labs 5 - 12
//#include "IQmathLib.h"                // used in Labs 8, 9, 10, and 12


//---------------------------------------------------------------------------
// Constant Definitions
//
#define ADC_BUF_LEN         50              // ADC buffer length
#define ADC_SAMPLE_PERIOD   1799            // 1799 = 50 kHz sampling w/ 90 MHz SYSCLKOUT
#define PWM_HALF_PERIOD     22500           // period/2 for 2 kHz symmetric PWM w/ 90 MHz SYSCLKOUT
#define PWM_DUTY_CYCLE      16875           // 25% duty cycle
#define PWM_MIN_DUTY		20250			// 10% duty cycle for PWM modulation
#define PWM_MAX_DUTY		2250			// 90% duty cycle for PWM modulation
#define PWM_STEP			10				// Step size change for PWM modulation
#define FILTER_LEN          5               // filter length

#if MATH_TYPE == IQ_MATH
    #define ADC_FS_VOLTAGE  _IQ(3.3)        // ADC full scale voltage
#else        // MATH_TYPE is FLOAT_MATH
    #define ADC_FS_VOLTAGE  _IQ(3.3/4096.0) // ADC full scale voltage, scaled for 12 bit ADC
#endif


//---------------------------------------------------------------------------
// Function Prototypes
//
extern void DelayUs(Uint16);
extern void InitAdc(void);
extern void InitCla(void);
extern void InitDma(void);
extern void InitECap(void);
extern void InitEPwm(void);
extern void InitFlash(void);
extern void InitGpio(void);
extern void InitPieCtrl(void);
extern void InitSysCtrl(void);
extern void InitWatchdog(void);
extern void SetDBGIER(Uint16);
extern void UserInit(void);
//extern  _iq _IQssfir(_iq*, _iq*, Uint16);    // used in Filter.c


//---------------------------------------------------------------------------
// CLA Function Prototypes
//
extern interrupt void Cla1Task1();
extern interrupt void Cla1Task2();
extern interrupt void Cla1Task3();
extern interrupt void Cla1Task4();
extern interrupt void Cla1Task5();
extern interrupt void Cla1Task6();
extern interrupt void Cla1Task7();
extern interrupt void Cla1Task8();


//---------------------------------------------------------------------------
// Global symbols defined in the linker command file
//
extern Uint16 cla1Funcs_loadstart;
extern Uint16 cla1Funcs_loadsize;
extern Uint16 cla1Funcs_runstart;
extern Uint16 secureRamFuncs_loadstart;
extern Uint16 secureRamFuncs_loadsize;
extern Uint16 secureRamFuncs_runstart;
extern Uint16 hwi_vec_loadstart;
extern Uint16 hwi_vec_loadsize;
extern Uint16 hwi_vec_runstart;
extern Uint16 trcdata_loadstart;
extern Uint16 trcdata_loadsize;
extern Uint16 trcdata_runstart;
extern Uint16 Cla1Prog_Start;


//---------------------------------------------------------------------------
// Global Variables References
//
//extern _iq AdcBufIQ[ADC_BUF_LEN];             // used in Lab 8
//extern _iq AdcBufFilteredIQ[ADC_BUF_LEN];     // used in Lab 8
//extern _iq xDelayIQ[FILTER_LEN];              // used in Lab 8
//extern _iq coeffsIQ[FILTER_LEN];              // used in Lab 8
extern float32 xDelay[FILTER_LEN];              // used in Lab 10
extern float32 coeffs[FILTER_LEN];              // used in Lab 10
extern Uint16 AdcBuf[ADC_BUF_LEN];              // used in Labs 6, 7 and 10
extern Uint16 AdcBufFiltered[ADC_BUF_LEN];      // used in Lab 10
extern Uint16 AdcBufRaw[2*ADC_BUF_LEN];         // used in Lab 9
extern Uint16 ClaFilteredOutput;
extern Uint32 PwmDuty;
extern Uint32 PwmPeriod;
extern Uint16 DEBUG_TOGGLE;
extern Uint16 PWM_MODULATE;
extern Uint16 DEBUG_FILTER;
extern const struct PIE_VECT_TABLE PieVectTableInit;    // PieVectTableInit is always extern


//---------------------------------------------------------------------------
// Macros
//
#define Device_cal_func_ptr (void (*)(void))0x3D7C80


//---------------------------------------------------------------------------
#endif  // end of LAB_H definition


//--- end of file -----------------------------------------------------
