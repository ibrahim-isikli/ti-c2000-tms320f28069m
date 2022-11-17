/** main.c **/
#include "F2806x_Device.h"
#include "F2806x_Examples.h"

#include "main.h"
#include "gpio_init.h"

/*************TYPEDEF STRUCT*******************/
typedef struct{
    volatile struct EPWM_REGS *EPwmRegHandle;
    Uint16 EPwm_CMPA_Direction;
    Uint16 Epwm_CMPB_Direction;
    Uint16 EPwmTimerIntCount;
    Uint16 EPwmMaxCMPA;
    Uint16 EPwmMinCMPA;
    Uint16 EPwmMaxCMPB;
    Uint16 EPwmMinCMPB;
}EPWM_INFO;
/***********************************************/

/*************************Func Protip**********************/
void InitEPwm1Example(void);
    __interrupt void epwm1_isr(void);
/***********************************************************/

/******************Global Var******************/
EPWM_INFO  epwm1_info;
/*********************************************/



void main(void)
{
    // STEP 1: Initialize System Control: PLL, Watchdog, enable Peripheral Clocks
    InitSysCtrl();

#ifdef FLASH_LINK
    // Copy the time critical and Flash setup code to RAM
    MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
    InitFlash();
#endif

    /*************************INIT PWM GPIO********************************/
        InitEPwmGpio();
    /*********************************************************************/

   // Set the High-Speed Peripheral Clock Prescaler (HISPCP) such that HSPCLK=25MHz
   // HSPCLK = SYSCLKOUT/(HISPCP x 2)
   asm(" EALLOW");
/*
 * #if CPU_FRQ_150MHZ
   SysCtrlRegs.HISPCP.all = 3;
#else
   SysCtrlRegs. = 2;
#endif
*/
   asm(" EDIS");

   // STEP 2: Initialize GPIO:
   gpio_init();

   // STEP 3: Clear all interrupts and initialize PIE vector table: Disable CPU interrupts
   DINT;

   // Initialize the PIE control registers to their default state
   // Default state is all PIE interrupts disabled and flags are cleared
   InitPieCtrl();

   // Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

   // Initialize the PIE vector table with pointers to the ISR
   InitPieVectTable();

   /***********************PWM Interrupt Enable**************/
   EALLOW;
   PieVectTable.EPWM1_INT = &epwm1_isr;
   EDIS;
   /********************************************************/
   /**************ePWM module clocks are started************/
   EALLOW;
   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC =0; //ePWM module clock disable
   EDIS;

   InitEPwm1Example();   /**INIT EPWM EXPAMLE**/

   EALLOW;
   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC =1; // ePWM module clock enable
   EDIS;

   /***********************************************************/



   /*****************ENABLE INTERRUPT********************/
   IER |= M_INT3;
   PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
   PieCtrlRegs.PIEIER3.bit.INTx2 = 1;
   PieCtrlRegs.PIEIER3.bit.INTx3 = 1;
   EINT;
   ERTM;
   /****************************************************
    */

   for(;;)
       {
           __asm("          NOP");
       }
}

void InitEPwmGpio(void){
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO0 =;
    GpioCtrlRegs.GPAPUD.bit.GPIO1=;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0= ;
    GpioCtrlRegs.GPAMUX1.bit.GPIO1= ;
    EDIS;
}

__interrupt void epwm1_isr(void){
    // update CMPA and CMPB values
    update_compare();
}
/***************************EPWM Config*****************************************************/
void InitEPwmExample(void){

    // Setup TBCLK
    EPwm1Regs.TBCTL.bit.CTRMODE = 0; // pwm counter mode -> up count
    EPwm1Regs.TBPRD = 2000; // time base period
    EPwm1Regs.TBCTL.bit.PHSEN = 0; // phase loading diasble
    EPwm1Regs.TBPHS.half = 0x0000; // faz 0
    EPwm1Regs.TBCTR = 0x0000; // timer base counterý temizle
    EPwm1Regs.TBCTL.bit.CLKDIV = 0x1; // TB clock = system clock /2
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0x1; // hihgh speed TB clock = system clock /2

    // setup shadow register load on Zero
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = 0;//cift buffer calisir. shadow registire erisim acik
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = 0;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = 0; //Time-base counter = 0
    EPwm1Regs.CMPCTL.bit.LOADBMODE = 0;

    // set compare values
    EPwm1Regs.CMPA.half.CMPA = 50; //CMPA = 50
    EPwm1Regs.CMPB= 50;            //CMPB = 50

    //set actions
    // Action-Qualifier Output A Control Register (AQCTLA)
    EPwm1Regs.AQCTLA.bit.ZRO = 0x2; // Set: force EPWMxA output high
    EPwm1Regs.AQCTLA.bit.CAU = 0x1; //Clear: force EPWMxA output low
    EPwm1Regs.AQCTLB.bit.ZRO= 0x2;
    EPwm1Regs.AQCTLA.bit.CAU= 0x1;

    // interrupt compare dgerlerimizi nerde degistiricek
    EPwm1Regs.ETSEL.bit.INTSEL =;
    EPwm1Regs.ETSEL.bit.INTEN =;
    EPwm1Regs.ETPS.bit.INTPRD =;

}
/********************************************************************************************/

