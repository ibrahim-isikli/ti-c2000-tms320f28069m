***********************************************************************
* File: CodeStartBranch.asm
* Devices: TMS320F2806x
* Author: Technical Training Organization (TTO), Texas Instruments
***********************************************************************

WD_DISABLE	.set	1		;set to 1 to disable WD, else set to 0

    .ref _c_int00

***********************************************************************
* Function: codestart section
*
* Description: Branch to code starting point
***********************************************************************
    .sect "codestart"

    .if WD_DISABLE == 1
        LB wd_disable       ;Branch to watchdog disable code
    .else
        LB _c_int00         ;Branch to start of boot.asm in RTS library
    .endif

;end codestart section


***********************************************************************
* Function: wd_disable
*
* Description: Disables the watchdog timer
***********************************************************************
    .if WD_DISABLE == 1

	.text
wd_disable:
	EALLOW					;Enable EALLOW protected register access
    MOVZ DP, #7029h>>6      ;Set data page for WDCR register
    MOV @7029h, #0068h      ;Set WDDIS bit in WDCR to disable WD
	EDIS					;Disable EALLOW protected register access
    LB _c_int00             ;Branch to start of boot.asm in RTS library

    .endif

;end wd_disable
***********************************************************************


	.end                    ; end of file CodeStartBranch.asm