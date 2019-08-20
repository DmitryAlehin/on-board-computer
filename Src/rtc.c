/**
  ******************************************************************************
  * File Name          : RTC.c
  * Description        : This file provides code for the configuration
  *                      of the RTC instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "rtc.h"

/* USER CODE BEGIN 0 */
#define RTC_STATUS_TIME_OK              0xF1D1
/* USER CODE END 0 */

RTC_HandleTypeDef hrtc;

/* RTC init function */
void MX_RTC_Init(void)
{
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /** Initialize RTC Only 
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  
	if (HAL_RTC_Init(&hrtc) != HAL_OK)
		{
			Error_Handler();
		}
  /* USER CODE BEGIN Check_RTC_BKUP */
	HAL_PWR_EnableBkUpAccess();
	if(HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR19 ) == RTC_STATUS_TIME_OK)
	{
		
	}
	else
	{
	
  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date 
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_MARCH;
  sDate.Date = 0x2;
  sDate.Year = 0x19;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable the WakeUp 
  */
  
	
	if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 59, RTC_WAKEUPCLOCK_CK_SPRE_16BITS) != HAL_OK)
  {
    Error_Handler();
  }
//	__HAL_RCC_RTC_ENABLE();
	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR19, RTC_STATUS_TIME_OK);
}
}


void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspInit 0 */
		
  /* USER CODE END RTC_MspInit 0 */
    /* RTC clock enable */
    __HAL_RCC_RTC_ENABLE();
		
    /* RTC interrupt Init */
    HAL_NVIC_SetPriority(RTC_WKUP_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(RTC_WKUP_IRQn);
  /* USER CODE BEGIN RTC_MspInit 1 */

  /* USER CODE END RTC_MspInit 1 */
  }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspDeInit 0 */
	
  /* USER CODE END RTC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();

    /* RTC interrupt Deinit */
    HAL_NVIC_DisableIRQ(RTC_WKUP_IRQn);
  /* USER CODE BEGIN RTC_MspDeInit 1 */

  /* USER CODE END RTC_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
void RTC_Interrupt(void)
{
	__HAL_RTC_WAKEUPTIMER_DISABLE(&hrtc);
	
	/* Disable RTC interrupt flag */
	__HAL_RTC_WAKEUPTIMER_DISABLE_IT(&hrtc, RTC_IT_WUT);
	
	/* Clear pending bit */
	__HAL_RTC_WAKEUPTIMER_EXTI_CLEAR_FLAG();
	
	/* Clear flag */
	__HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&hrtc, RTC_FLAG_WUTF);
	HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0x3BFFF, RTC_WAKEUPCLOCK_RTCCLK_DIV8); //1 минута
		
		/* Set NVIC */
	HAL_NVIC_SetPriority(RTC_WKUP_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(RTC_WKUP_IRQn);
}

__weak void RTC_WakeupCallback(void) {
	/* If user needs this function, then they should be defined separatelly in your project */
}

void RTC_Fix_Date(RTC_DateTypeDef *sDate)
{
	if(sDate->Date == 0)
	{
		sDate->Date = 1;
	}
	
	if(sDate->Date <= 28)
	{
		return;
	}
	if((sDate->Month == 4) || (sDate->Month == 6)|| (sDate->Month == 9)|| (sDate->Month == 11))
	{
		if(sDate->Date > 30)
		{
			sDate->Date = 30;
		}	
	}
	else if(sDate->Month == 2)
	{
		if((sDate->Year % 4) == 0)
		{
			if(sDate->Date > 29)
			{
				sDate->Date = 29;
			}
		}
		else
		{
			if(sDate->Date > 28)
			{
				sDate->Date = 28;
			}
		}
	}
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
