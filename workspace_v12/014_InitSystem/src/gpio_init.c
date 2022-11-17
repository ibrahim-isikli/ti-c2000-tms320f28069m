#include "F2806x_Device.h"
#include "F2806x_Examples.h"

#include "gpio_init.h"
#include "main.h"

void gpio_init(void)
{
    asm(" EALLOW");

    GpioCtrlRegs.GPBCTRL.all = 0x00000000;  // QUALPRD = SYSCLKOUT for all group B GPIO
    GpioCtrlRegs.GPBQSEL1.all = 0x00000000; // No qualification for all group B GPIO32-44
    GpioCtrlRegs.GPBQSEL2.all = 0x00000000; // No qualification for all group B GPIO50-58
    GpioCtrlRegs.GPBDIR.all = 0x00000000;   // All group B GPIOs are inputs
    GpioCtrlRegs.GPBPUD.all = 0x00000000;   // All group B pull-ups enabled

    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;    // 0=GPIO               1=COMP2OUT  2=rsvd       3=COMP3OUT

    //
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;     // Set the GPIO34 as output
    GpioDataRegs.GPBSET.bit.GPIO34 = 1;     // GPIO34 pin is set to 1


/*    GpioCtrlRegs.GPAPUD.bit.GPIO34 = 0;     // Enable pull-up on GPIO pin
    GpioDataRegs.GPASET.bit.GPIO34 = 0;     // Load 0 to output latch
    GpioCtrlRegs.GPAMUX2.bit.GPIO34 = 0;    // 0 to pass the latch value to the output
                                            // 1 to configure as EPWM
    GpioCtrlRegs.GPADIR.bit.GPIO34 = 1;     // set the pin as output
*/

    asm(" EDIS");

}



