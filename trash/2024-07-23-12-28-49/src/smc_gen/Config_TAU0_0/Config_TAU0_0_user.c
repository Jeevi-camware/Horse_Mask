/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2021, 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : Config_TAU0_0_user.c
* Component Version: 1.4.0
* Device(s)        : R7F102G6CxSP
* Description      : This file implements device driver for Config_TAU0_0.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Config_TAU0_0.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt r_Config_TAU0_0_interrupt(vect=INTTM00)
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
#define TRIGGER_LED_STATE(X) P2_bit.no1=X // Blinking LED

#define BLINK_INT_MS    2  // Blinking Intervel in 100ms

#define BLINK_MIN       1
#define BLINK_MAX       3  // Maximum no of Blinking


extern uint8_t gTriggerCount;
extern uint8_t gDurTimeFlag;
extern uint8_t gLedBlinkFlag;
extern uint8_t gLedDriverStatus;
extern uint8_t gRtcRunStatus;
uint8_t gToggleState=0;
uint8_t gToggleCount=0;
uint8_t gToggleMilliCount=0;
uint8_t gDuraCount=0;
uint8_t gDurMilliCount=0;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_0_Create_UserInit
* Description  : This function adds user code after initializing the TAU0 channel 0.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_0_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_TAU0_0_interrupt
* Description  : This function is INTTM00 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_Config_TAU0_0_interrupt(void)
{
    /* Start user code for r_Config_TAU0_0_interrupt. Do not edit comment generated here */
	if(gLedBlinkFlag==1)
			{
				gToggleMilliCount++;

				if(gToggleMilliCount % BLINK_INT_MS==0)
				{
				   gToggleCount++;
				   gToggleState=(gToggleState==0) ?  1:0;
				   TRIGGER_LED_STATE(gToggleState);
				   if((((gLedDriverStatus==0) ? BLINK_MIN :BLINK_MAX)*2)<=gToggleCount)
				   {
					   TRIGGER_LED_STATE(0);
					   gRtcRunStatus=(gLedDriverStatus==0) ? 1:0 ;
					   gToggleMilliCount=0;
					   gToggleCount=0;
					   gLedBlinkFlag=0;
					   gToggleState=0;

				   }
				}
			}

			if(gDurTimeFlag==1)
			{
				gDurMilliCount++;
				if(gDurMilliCount%10==0)
				{
				  gDuraCount++;
				}

			}

    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
