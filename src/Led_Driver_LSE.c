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
* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
*  File Name    : Led_Driver_LSE.c
*  Description  : Main Program
*  Creation Date: 2024-06-14
*  This file was generated by Smart Configurator.
***********************************************************************************************************************/
#include "r_smc_entry.h"

#include "stdint.h"

#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "r_cg_tau.h"
#include "r_cg_tau_common.h"

#include "Config_TAU0_0.h"
#include "Config_INTC.h"
#include "Config_rtc.h"
/*****************Typedef*********************/
typedef enum
{
	Disable,
	Enable
}e_mode_t;
typedef enum
{
	IT_Disable,
	IT_Enable,

}e_it_state_t;
typedef enum
{
	 Output,
	 Input
}e_pin_mode_t;
typedef enum
{
	 Low,
	 High
}e_pin_state_t;
typedef enum
{
	Normal,
	Open_Drian
}e_pin_type_t;
typedef enum
{
	Digital,
	Analog
}e_pin_type1_t;
/********************************************/


/*****************Defines********************/
#define LED_DRIVER_STATE(X) P0_bit.no1=X
#define TRIGGER_LED_STATE(X) P2_bit.no1=X
/********************************************/


/*****************Macros*********************/
#define TRIGGER__DURATION_TIME     10
#define ON__DURATION_TIME          420 // 420=60 *60 * 7 --> 7Hours
#define RTC_MAX_TIME               1440 //24 hours
#define TRIGGER_MAX                2
#define HOUR__RTC                  1
#define MINUTE__RTC                0
#define SECOND__RTC                0
#define MAX_DAYS                   2//160 days
#define TWO_HOURS                  120 //120=60 *60 * 2 --> 2Hours
/*******************************************/

/**************Global_Declaraton************/


 extern uint8_t gTriggerCount;
 extern uint8_t gDurTimeFlag;
 extern uint8_t gDuraCount;
 extern uint8_t gDurMilliCount;
 extern uint32_t gRtcMinCount;

 uint8_t gRtcRunStatus=0;
 uint8_t gLedBlinkFlag=0;
 uint8_t gLedDriverStatus=0;
 uint8_t gRtcWakeupRun=0;
 uint32_t gRtcTimCount=0;
 uint8_t days=0;
 uint8_t gdayscountFlag=0;

/*******************************************/
/**************Function_Declaration**********/
 int main (void);
 void Trigger_Process(void);
 void Delay(void);
 void Peripheral_Init(void);
/*******************************************/

int main(void)
{
//	R_Config_RTC_Create();
	Peripheral_Init();            // Initialize Required PORTS and Peripherals
	STOP();                        // MCU ENTER STOP MODE
		while(1)
		{
		 	if(gdayscountFlag==1)
			{
				LED_DRIVER_STATE(Low);      // Disable led driver
				gLedDriverStatus=0;
				gRtcRunStatus=0;
				R_Config_TAU0_0_Stop();
			}
		 	else if(gdayscountFlag==0)
		 	{
              Trigger_Process();
		 	}
		 	else
		 	{
		 		NOP();
		 	}

			if(gRtcWakeupRun==1)
			{
				if(RTC_MAX_TIME==gRtcMinCount)
				{
					gRtcRunStatus=1;
				}
			}
		}
}

void Peripheral_Init(void)
{

	R_Config_PORT_Create();
//	R_Config_RTC_Create();
	gLedDriverStatus=0;           // Default LED State is OFF
    R_Config_INTC_INTP0_Start();  // Initialize the External Interrupt
	EI();                         // Enable Interrupt
}

void  Trigger_Process(void)
{

	if(gLedDriverStatus==0 && gRtcRunStatus==1) //if Valid trigger occurs while LED IS OFF State
	{
		EI();
		LED_DRIVER_STATE(High);   // LED Driver output ON
		gLedDriverStatus=1;
		if(gRtcWakeupRun==1)
		{
			gRtcMinCount=0;
			R_Config_RTC_Stop();
		}
		gRtcWakeupRun=0;
		gRtcMinCount=0;
		R_Config_TAU0_0_Stop();   // Stop  100ms Timer
		R_Config_RTC_Create();    // Initailize rtc timer value (24 HOURS FORMAT)
		R_Config_RTC_Start();     // Start RTC

	}
	if(TRIGGER__DURATION_TIME==gDuraCount&& gDurTimeFlag==1)  // Check Duration is exceeds the duration count
	{
		gTriggerCount=0; // Clear trigger counts
		R_Config_TAU0_0_Stop();
		gDurTimeFlag=0;
		gDurMilliCount=0;
		gDuraCount=0;
		STOP();                      // MCU ENTER STOP MODE
	}
	if(gTriggerCount>=TRIGGER_MAX && gDuraCount<=TRIGGER__DURATION_TIME)
	{
		/* if valid trigger count occurs with in Defined Time interval */

		gLedBlinkFlag=1;             // LED Blink Count Flag will be set
		gDurTimeFlag=0;
		gDurMilliCount=0;
		gDuraCount=0;
		gTriggerCount=0;
	}

	if((ON__DURATION_TIME==gRtcMinCount && gRtcWakeupRun==0) ||(gLedDriverStatus==1 && gRtcRunStatus==0))
	{
		/* If  RTC timer reaches predefined time or  Valid Tigger count occurs with in time interval
				 * while LED driver is on state
				 * */

		  if(gRtcRunStatus==0)
		  {
			  gRtcMinCount=0;
			  R_Config_RTC_Stop();
		  }
		  else
		  {

			  gRtcWakeupRun=1;
		  }
		  LED_DRIVER_STATE(Low);      // Disable led driver
		  gLedDriverStatus=0;
		  gRtcRunStatus=0;
		  R_Config_TAU0_0_Stop();     // Stop Timer
		  Peripheral_Init();
		  STOP();
	}


   if(gRtcMinCount==TWO_HOURS && gLedDriverStatus==1 && gRtcMinCount<121)
    {
	days++;
	gRtcMinCount=121;

    }

   /* if(days>=MAX_DAYS)
    {
    	gdayscountFlag=1;
    } */

    if(days>= MAX_DAYS&& ON__DURATION_TIME==gRtcMinCount)
    {
    	gdayscountFlag=1;
    }
}

void Delay(void)
{
	for(uint16_t i=0;i<200;i++)
	{
		for(uint16_t j=0;j<200;j++)
		{
			NOP();
		}
	}
}



