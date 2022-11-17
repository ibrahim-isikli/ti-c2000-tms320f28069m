/**********************************************************************
* File: PieVect.c -- File for Lab 5, 6, 7, 8, 9, 10 and 12
* Devices: TMS320F2806x
* Author: Technical Training Organization (TTO), Texas Instruments
**********************************************************************/

#include "Lab.h"						// Main include file


/**********************************************************************
* The PIE vector initialization table for the F2806x
**********************************************************************/
const struct PIE_VECT_TABLE PieVectTableInit = {

//--- Base vectors
    rsvd_ISR,                       // 0x000D00  reserved
    rsvd_ISR,                       // 0x000D02  reserved
    rsvd_ISR,                       // 0x000D04  reserved
    rsvd_ISR,                       // 0x000D06  reserved
    rsvd_ISR,                       // 0x000D08  reserved
    rsvd_ISR,                       // 0x000D0A  reserved
    rsvd_ISR,                       // 0x000D0C  reserved
    rsvd_ISR,                       // 0x000D0E  reserved
    rsvd_ISR,                       // 0x000D10  reserved
    rsvd_ISR,                       // 0x000D12  reserved
    rsvd_ISR,                       // 0x000D14  reserved
    rsvd_ISR,                       // 0x000D16  reserved
    rsvd_ISR,                       // 0x000D18  reserved
    INT13_ISR,                      // 0x000D1A  INT13 - CPU Timer1
    INT14_ISR,                      // 0x000D1C  INT14 - CPU Timer2
    DATALOG_ISR,                    // 0x000D1E  DATALOG - CPU data logging interrupt
    RTOSINT_ISR,                    // 0x000D20  RTOSINT - CPU RTOS interrupt
    EMUINT_ISR,                     // 0x000D22  EMUINT - CPU emulation interrupt
    NMI_ISR,                        // 0x000D24  NMI - XNMI interrupt
    ILLEGAL_ISR,                    // 0x000D26  ILLEGAL - illegal operation trap
    USER1_ISR,                      // 0x000D28  USER1 - software interrupt #1
    USER2_ISR,                      // 0x000D2A  USER2 - software interrupt #2
    USER3_ISR,                      // 0x000D2C  USER3 - software interrupt #3
    USER4_ISR,                      // 0x000D2E  USER4 - software interrupt #4
    USER5_ISR,                      // 0x000D30  USER5 - software interrupt #5
    USER6_ISR,                      // 0x000D32  USER6 - software interrupt #6
    USER7_ISR,                      // 0x000D34  USER7 - software interrupt #7
    USER8_ISR,                      // 0x000D36  USER8 - software interrupt #8
    USER9_ISR,                      // 0x000D38  USER9 - software interrupt #9
    USER10_ISR,                     // 0x000D3A  USER10 - software interrupt #10
    USER11_ISR,                     // 0x000D3C  USER11 - software interrupt #11
    USER12_ISR,                     // 0x000D3E  USER12 - software interrupt #12

//--- Core interrupt #1 re-map
    ADCINT1_ISR,                    // 0x000D40  ADCINT1
    ADCINT2_ISR,                    // 0x000D42  ADCINT2
    rsvd_ISR,                       // 0x000D44  reserved
    XINT1_ISR,                      // 0x000D46  XINT1
    XINT2_ISR,                      // 0x000D48  XINT2
    ADCINT9_ISR,                    // 0x000D4A  ADCINT9
    TINT0_ISR,                      // 0x000D4C  TINT0 - CPU TIMER 0
    WAKEINT_ISR,                    // 0x000D4E  WAKEINT - LPM/WD

//--- Core interrupt #2 re-map
    EPWM1_TZINT_ISR,                // 0x000D50  EPWM1_TZINT
    EPWM2_TZINT_ISR,                // 0x000D52  EPWM2_TZINT
    EPWM3_TZINT_ISR,                // 0x000D54  EPWM3_TZINT
    EPWM4_TZINT_ISR,                // 0x000D56  EPWM4_TZINT
    EPWM5_TZINT_ISR,                // 0x000D58  EPWM5_TZINT
    EPWM6_TZINT_ISR,                // 0x000D5A  EPWM6_TZINT
    EPWM7_TZINT_ISR,                // 0x000D5C  EPWM7_TZINT
    EPWM8_TZINT_ISR,                // 0x000D5E  EPWM8_TZINT

//--- Core interrupt #3 re-map
    EPWM1_INT_ISR,                  // 0x000D60  EPWM1_INT
    EPWM2_INT_ISR,                  // 0x000D62  EPWM2_INT
    EPWM3_INT_ISR,                  // 0x000D64  EPWM3_INT
    EPWM4_INT_ISR,                  // 0x000D66  EPWM4_INT
    EPWM5_INT_ISR,                  // 0x000D68  EPWM5_INT
    EPWM6_INT_ISR,                  // 0x000D6A  EPWM6_INT
    EPWM7_INT_ISR,                  // 0x000D6C  EPWM7_INT
    EPWM8_INT_ISR,                  // 0x000D6E  EPWM8_INT

//--- Core interrupt #4 re-map
    ECAP1_INT_ISR,                  // 0x000D70  ECAP1_INT
    ECAP2_INT_ISR,                  // 0x000D72  ECAP2_INT
    ECAP3_INT_ISR,                  // 0x000D74  ECAP3_INT
    rsvd_ISR,                       // 0x000D76  reserved
    rsvd_ISR,                       // 0x000D78  reserved
    rsvd_ISR,                       // 0x000D7A  reserved
    HRCAP1_INT_ISR,                 // 0x000D7C  HRCAP1_INT
    HRCAP2_INT_ISR,                 // 0x000D7E  HRCAP2_INT

//--- Core interrupt #5 re-map
    EQEP1_INT_ISR,                  // 0x000D80  EQEP1_INT
    EQEP2_INT_ISR,                  // 0x000D82  EQEP2_INT
    rsvd_ISR,                       // 0x000D84  reserved
    HRCAP3_INT_ISR,                 // 0x000D86  HRCAP3_INT
    HRCAP4_INT_ISR,                 // 0x000D88  HRCAP4_INT
    rsvd_ISR,                       // 0x000D8A  reserved
    rsvd_ISR,                       // 0x000D8C  reserved
    USB0_INT_ISR,                   // 0x000D8E  USB0_INT

//--- Core interrupt #6 re-map
    SPIRXINTA_ISR,                  // 0x000D90  SPIRXINTA
    SPITXINTA_ISR,                  // 0x000D92  SPIRXINTA
    SPIRXINTB_ISR,                  // 0x000D94  SPIRXINTB
    SPITXINTB_ISR,                  // 0x000D96  SPIRXINTB
    MRINTA_ISR,                     // 0x000D98  MRINTA
    MXINTA_ISR,                     // 0x000D9A  MXINTA
    rsvd_ISR,                       // 0x000D9C  reserved
    rsvd_ISR,                       // 0x000D9E  reserved

//--- Core interrupt #7 re-map
    DINTCH1_ISR,                    // 0x000DA0  DINTCH1
    DINTCH2_ISR,                    // 0x000DA2  DINTCH2
    DINTCH3_ISR,                    // 0x000DA4  DINTCH3
    DINTCH4_ISR,                    // 0x000DA6  DINTCH4
    DINTCH5_ISR,                    // 0x000DA8  DINTCH5
    DINTCH6_ISR,                    // 0x000DAA  DINTCH6
    rsvd_ISR,                       // 0x000DAC  reserved
    rsvd_ISR,                       // 0x000DAE  reserved

//--- Core interrupt #8 re-map
    I2CINT1A_ISR,                   // 0x000DB0  I2CINT1A
    I2CINT2A_ISR,                   // 0x000DB2  I2CINT2A
    rsvd_ISR,                       // 0x000DB4  reserved
    rsvd_ISR,                       // 0x000DB6  reserved
    rsvd_ISR,                       // 0x000DB8  reserved
    rsvd_ISR,                       // 0x000DBA  reserved
    rsvd_ISR,                       // 0x000DBC  reserved
    rsvd_ISR,                       // 0x000DBE  reserved

//--- Core interrupt #9 re-map
    SCIRXINTA_ISR,                  // 0x000DC0  SCIRXINTA
    SCITXINTA_ISR,                  // 0x000DC2  SCITXINTA
    SCIRXINTB_ISR,                  // 0x000DC4  SCIRXINTB
    SCITXINTB_ISR,                  // 0x000DC6  SCITXINTB
    ECAN0INTA_ISR,                  // 0x000DC8  ECAN0_INTA
    ECAN1INTA_ISR,                  // 0x000DCA  ECAN1_INTA
    rsvd_ISR,                       // 0x000DCC  reserved
    rsvd_ISR,                       // 0x000DCE  reserved

//--- Core interrupt #10 re-map
    rsvd_ISR,                       // 0x000DD0  reserved, If this is ADCINT1_ISR, then INT1.1 should be rsvd_ISR
    rsvd_ISR,                       // 0x000DD2  reserved, If this is ADCINT2_ISR, then INT1.2 should be rsvd_ISR
    ADCINT3_ISR,                    // 0x000DD4  ADCINT3
    ADCINT4_ISR,                    // 0x000DD6  ADCINT4
    ADCINT5_ISR,                    // 0x000DD8  ADCINT5
    ADCINT6_ISR,                    // 0x000DDA  ADCINT6
    ADCINT7_ISR,                    // 0x000DDC  ADCINT7
    ADCINT8_ISR,                    // 0x000DDE  ADCINT8

//--- Core interrupt #11 re-map
    CLA1_INT1_ISR,                  // 0x000DE0  CLA1_INT1
    CLA1_INT2_ISR,                  // 0x000DE2  CLA2_INT1
    CLA1_INT3_ISR,                  // 0x000DE4  CLA3_INT1
    CLA1_INT4_ISR,                  // 0x000DE6  CLA4_INT1
    CLA1_INT5_ISR,                  // 0x000DE8  CLA5_INT1
    CLA1_INT6_ISR,                  // 0x000DEA  CLA6_INT1
    CLA1_INT7_ISR,                  // 0x000DEC  CLA7_INT1
    CLA1_INT8_ISR,                  // 0x000DEE  CLA8_INT1

//--- Core interrupt #12 re-map
    XINT3_ISR,                      // 0x000DF0  XINT3
    rsvd_ISR,                       // 0x000DF2  reserved
    rsvd_ISR,                       // 0x000DF4  reserved
    rsvd_ISR,                       // 0x000DF6  reserved
    rsvd_ISR,                       // 0x000DF8  reserved
    rsvd_ISR,                       // 0x000DFA  reserved
    LVF_ISR,                        // 0x000DFC  LVF - CLA
    LUF_ISR,                        // 0x000DFE  LUF - CLA

}; // end PieVectTableInit{}


//--- end of file -----------------------------------------------------
