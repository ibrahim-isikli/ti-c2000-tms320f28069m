#if 1
#include "F2806x_device.h"
#include "F2806x_Examples.h"


void main(){
InitSysCtrl(); // sistem config
Gpio_sec();     // gpio config
DINT; // CPU interruptlar disable
InitPieCtrl(); // PIE config
InitPieVectTable();

for(;;){

    if(GpioDataRegs.GPADAT.bit.GPIO3 == 1){
    GpioDataRegs.GPASET.bit.GPIO1=1;
    GpioDataRegs.GPASET.bit.GPIO2=1;
    //GpioDataRegs.GPADAT.bit.GPIO1=1;

    DELAY_US(1000000);
    //GpioDataRegs.GPADAT.bit.GPIO2=0;
    //GpioDataRegs.GPADAT.bit.GPIO1=0;
    GpioDataRegs.GPACLEAR.bit.GPIO1=1;
    GpioDataRegs.GPACLEAR.bit.GPIO2=1;
    DELAY_US(1000000);
    }
}
}


void delay_deneme(int time){
    while(time --);
}


void
delay_loop()
{
    double i;
    for (i = 0; i < 400000; i++)
    {

    }
}

void Gpio_sec(void){
    EALLOW;
    GpioCtrlRegs.GPAMUX1.all = 0x00000000; // hepsi general purpouse i/o selected
    GpioCtrlRegs.GPADIR.bit.GPIO1 = 1; //OUTPUT selected
    GpioCtrlRegs.GPADIR.bit.GPIO2 = 1; // output
    GpioCtrlRegs.GPADIR.bit.GPIO3 = 0; // input
    EDIS;
}
#if 0



void InitPieCtrl(void){

    // PIE -> Peripheral Interrupt Expansion
    DINT; // bu bir define makro bu CPU seviyesinde interruptlari önce kapatiyor

    PieCtrlRegs.PIECTRL.bit.ENPIE=0;
    // Burada ne yapiyoruz ?
    /*
     *  PIE Interrupt Registerlar var bunlari config etmemiz lazim
     *  Oncelikle Bu baslikta PIECTRL Register var (syf182)
     *  bu registerda PIEVECT ve ENPPIE adinda iki bit var
     *  PIEVECT read only, isimiz ENPIE ile
     *  ENPIE reset -> disable PIE
     */

    // PIE Interrupt Flag Register
    //  PIEIFR
    /*
     *  INTx.1 -> INTx.8 e kadar 8 li
     *  1.x -> 12.x 'e kadar 12
     *  12*8 = 96 interruptimiz vardi
     *   PIEFR ile INTx.2 nin flagini degistir
     *  PieCtrlRegs.PIEIFR2----
     */

    PieCtrlRegs.PIEIFR2.bit.INTx1 =1
     // F2806x PIE Interrupt Assignment Table'a ulas
     /*
      * Bu tabloya bak EPWM8_TZINIT flagini set ettiim
      */


      // PIE  Interrupt Enable Register
      // PIEIER
            PieCtrlRegs.PIEIER3.bit.INTx2 = 1;
    // table'a bak
    //enable EPWM2_INT in PIE group 3


    // PIE Interrupt Acknowledge Register
    // PIEACK
    PieCtrlRegs.PIEACK.all = 0x0004;
    //acknowledge the PIE group 3


}

#endif


#endif
