/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2019 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "GUI.h"
#include "TouchPanel.h"
#include "DIALOG.h"
#include "OBDII.h"
#include "BK8000L.h"
#include "MVH_08UB.h"
#include "W25Q.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define HIDE_FF 0
#define DISPLAYSIZE 40// Amount of data to display by default
#define STORESIZE 80 // Amount of data to store
//GUI_PID_STATE PState;
GUI_PID_STATE TS_State;
WM_MESSAGE msg;

OBD_General_States_Typedef OBD_General_State = NOP;
CarParameters_Typedef CarParameters;
OBD_Sign_States_Typedef OBD_Sign_State = OBD_OK;
OBD_Data_States_Typedef OBD_Data_State = WAIT_DATA;
BT_General_States_Typedef BT_General_State = WAIT_BT_INIT;
BT_States_Typedef BT_State = WAIT;
BT_Values_Typedef BT_Value;
MVH_Values_Typedef MVH_Value;
MVH_States_Typedef MVH_States = MVH_INIT_STATE;
volatile uint8_t count;
extern uint8_t DMA_BUFFER_OBD[DMA_BUFFER_OBD_SIZE];
extern uint8_t OBD_BUFFER[DMA_BUFFER_OBD_SIZE];
extern uint8_t DMA_BUFFER_BT[DMA_BUFFER_BT_SIZE];
extern uint8_t BT_BUFFER[DMA_BUFFER_BT_SIZE];
uint8_t MVH_BUFFER[STORESIZE];
CarValues_Typedef Car_Param;
Saved_parameters_Typedef Saved_Parameters;
//extern RTC_TimeTypeDef time;
//extern RTC_DateTypeDef date;
extern GUIHandles GuiHandles;


volatile uint8_t currentMOSI;
uint8_t bitsFilled = 0;
uint8_t overSized = 0; // Safety margin for memory allocation
uint8_t mosi[STORESIZE];
volatile uint16_t displayPosition = 0;
volatile uint8_t mosiPrint[STORESIZE];
volatile uint16_t oldDisplayPosition;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
xQueueHandle QueueCarParam;
xQueueHandle QueueMVHFromISR;
xQueueHandle QueueODBFromISR;
xQueueHandle QueueBTFromISR;
/* USER CODE END Variables */
osThreadId GUIHandle;
osThreadId ParserHandle;
osThreadId OBDHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void UART_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    char buffer[256];

    vsnprintf(buffer, 256, format, args);

    HAL_UART_Transmit(&huart3, buffer, strlen(buffer), HAL_MAX_DELAY);

    va_end(args);
}

inline static void printOneChar(uint8_t character, uint8_t isMOSI) {
#if (HIDE_FF == 1)
	if (character == 0xff) {
		UART_printf("  ");
	} else {
		UART_printf("%02x", character);
	}
#elif (HIDE_FF == 2)
	if (character == 0xff) {
		if (isMOSI) {
			UART_printf("\e[34m%02x\e[33m", character);
		} else {
			UART_printf("\e[34m%02x\e[36m", character);
		}
	} else {
		UART_printf("%02x", character);
	}
#else
	UART_printf("%02x", character);
#endif
}
/* USER CODE END FunctionPrototypes */

void _GUI(void const * argument);
void _Parser(void const * argument);
void _OBD(void const * argument);

extern void MX_FATFS_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
   	Touch_Cal_Read(&matrix);
	__HAL_RCC_CRC_CLK_ENABLE();
	
	
	GUI_Init();
	Car_Param.K_MAP = 60.0;
	 
	for (int i = 0; i < 8; i++) 
	HAL_GPIO_EXTI_Callback(CLK_MVH_Pin);
//	OBD_General_State = NOP;
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of GUI */
  osThreadDef(GUI, _GUI, osPriorityNormal, 0, 4096);
  GUIHandle = osThreadCreate(osThread(GUI), NULL);

  /* definition and creation of Parser */
  osThreadDef(Parser, _Parser, osPriorityNormal, 0, 2048);
  ParserHandle = osThreadCreate(osThread(Parser), NULL);

  /* definition and creation of OBD */
  osThreadDef(OBD, _OBD, osPriorityNormal, 0, 2048);
  OBDHandle = osThreadCreate(osThread(OBD), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
//	QueueCarParam = xQueueCreate(1, sizeof(CarParam));
	QueueMVHFromISR = xQueueCreate(1, sizeof(MVH_BUFFER));
	QueueODBFromISR = xQueueCreate(1, sizeof(DMA_BUFFER_OBD));
	QueueBTFromISR = xQueueCreate(1, sizeof(DMA_BUFFER_BT));
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* USER CODE BEGIN Header__GUI */
/**
  * @brief  Function implementing the GUI thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header__GUI */
void _GUI(void const * argument)
{
  /* init code for FATFS */
  MX_FATFS_Init();

  /* USER CODE BEGIN _GUI */
//	OBD_Init();
	CreateMainWindow();
//	CreateWindow();
  /* Infinite loop */
  for(;;)
  {
    Touch_Update();
		GUI_Exec();
		switch(msg.MsgId)
		{
			case WM_UPDATE_MIN:
//				OBD_Update();
				WM_SendMessage(GuiHandles.hMainWindow, &msg);
				msg.MsgId = WM_UPDATE_MIN;
				WM_SendMessage(GuiHandles.hAudioWindow, &msg);				
				break;
			case WM_UPDATE_CAR:
				WM_SendMessage(GuiHandles.hMainWindow, &msg);
				msg.MsgId = WM_UPDATE_CAR;				
				WM_SendMessage(GuiHandles.hAudioWindow, &msg);
				break;
			case WM_UPDATE_BT:
				WM_SendMessage(GuiHandles.hAudioWindow, &msg);
				break;
			case WM_UPDATE_MVH:
				WM_SendMessage(GuiHandles.hAudioWindow, &msg);
				break;			
		}
			
		
  }
  /* USER CODE END _GUI */
}

/* USER CODE BEGIN Header__Parser */
/**
* @brief Function implementing the Parser thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header__Parser */
void _Parser(void const * argument)
{
  /* USER CODE BEGIN _Parser */
	  /* Infinite loop */
  for(;;)
  {		
		if(uxQueueMessagesWaitingFromISR(QueueODBFromISR)>0)
		{
			xQueueReceive(QueueODBFromISR, &OBD_BUFFER, 100);
			OBD_CheckState(OBD_BUFFER, &CarParameters);
		}
		if(uxQueueMessagesWaitingFromISR(QueueBTFromISR)>0)
			{
				xQueueReceive(QueueBTFromISR, &BT_BUFFER, 100);
				BTCheckState(BT_BUFFER, &BT_Value);			
			}    		
  }
  /* USER CODE END _Parser */
}

/* USER CODE BEGIN Header__OBD */
/**
* @brief Function implementing the OBD thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header__OBD */
void _OBD(void const * argument)
{
  /* USER CODE BEGIN _OBD */
	float VSS, MAP, IAT, RPM, LONGFT, SHRTFT, Fb, Ft;
	uint32_t lastTime = HAL_GetTick();
  uint32_t lastSeparatorTime = HAL_GetTick();
  /* Infinite loop */
  for(;;)
  {
//		if(uxQueueMessagesWaitingFromISR(QueueMVHFromISR)>0)
//			{
//				xQueueReceive(QueueMVHFromISR, &mosiuart, 100);							
//				
//				for (int i = 0; i < 40; i++) 
//				{					
//					printOneChar(mosiuart[i], 1);
//					UART_printf(" ");
//					if(mosiuart[i] == 0x03)
//					{
//						UART_printf("\r\n");
//					}
//				}				
//			}
//			}  
		if (displayPosition >= DISPLAYSIZE || HAL_GetTick() - lastTime >= 100) {
  		oldDisplayPosition = displayPosition; // Make sure it doesn't change
  		// Copy the data so no one writes on it
  		memcpy(mosiPrint, mosi, oldDisplayPosition);
			MVH_CheckState(mosiPrint, &MVH_Value);
  		if (displayPosition != oldDisplayPosition) {
  			UART_printf("!!!COW\r\n"); // copy overwrite
  		}

  		displayPosition = 0; // Lose data instead of printing corrupt data
  		

//				if (oldDisplayPosition > 0) {
//  			// Data exists
////  			UART_printf("\e[33m");
//				
				for (int i = 0; i < oldDisplayPosition; i++) {
					
					printOneChar(mosiPrint[i], 1);
					UART_printf(" ");
					if(mosiPrint[i] == 0x03)
					{
						UART_printf("\r\n");
					}
				}
//			}
////				UART_printf("\e[39m\r\n\e[36m");
//				
////				UART_printf("\e[39m\r\n");
//				
//				lastSeparatorTime = HAL_GetTick();
//  		}

//  		if (HAL_GetTick() - lastTime >= 100){
//  			if (oldDisplayPosition > 0) {
//  				UART_printf("\r\n"); // Print a newline to separate old data
//  			}
//  			if (bitsFilled != 0) {
//  				UART_printf("!!!IR\r\n");
//  				bitsFilled = 0;
//  			}
//  		}  		
//  		if (overSized) {
//  			UART_printf("!!!OS\r\n");
//  			overSized = 0;
//  		}

			lastTime = HAL_GetTick();
////				
			}
		
		OBD_Init();
		BT_Init();
		if(OBD_General_State == OBD_INIT)
		{	
			OBD_Update();
		
		if(OBD_Data_State == COMPLETE_ALL_DATA)
		{			
			Car_Param.Voltage = CarParameters.Voltage;
			Car_Param.ECT = CarParameters.ECT - 40.0;
			Car_Param.FUEL = ((CarParameters.FUEL) * 100.0) / 255.0;
			VSS = CarParameters.VSS;
			if(VSS == 0)
			{
				VSS = 1;
			}
			IAT = CarParameters.IAT - 40.0;
			LONGFT = ((CarParameters.LONGFT - 128.0) * 100.0) / 128.0;
			SHRTFT = ((CarParameters.SHRTFT - 128.0) * 100.0) / 128.0;
			MAP = CarParameters.MAP;
			RPM = (CarParameters.RPM_A * 256.0 + CarParameters.RPM_B)/4;
			Fb = (Car_Param.K_MAP / 100.0) * (RPM / 60.0) * MAP * 0.8 * 28.98 / (8.31441 * (IAT + 273.15));
			Ft = 1000.0 * (1 + 0.001 * (IAT - 20.0)) * 3600.0 * Fb * 1 + ((SHRTFT + LONGFT) / 100.0) / (14.7 * 750.0);
			Car_Param.Fuel_consumption = Ft / (VSS * 1000000.0);
			Car_Param.LH_consumption = Ft;
			OBD_Data_State = CALCULATE_END;
			msg.MsgId = WM_UPDATE_CAR;			
		}
	}
}
  
  /* USER CODE END _OBD */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
{	
	msg.MsgId = WM_UPDATE_MIN;	
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
//	uint32_t lastTime = HAL_GetTick();
//  uint32_t lastSeparatorTime = HAL_GetTick();
//	uint8_t mosiPrint[STORESIZE];
	static BaseType_t xHigherPriorityTaskWoken;
	if (GPIO_Pin == CLK_MVH_Pin) {		
		// CLK asserted		
		currentMOSI = ((currentMOSI << 1) & 0xff) | HAL_GPIO_ReadPin(MOSI_MVH_GPIO_Port, MOSI_MVH_Pin);
		if (++bitsFilled == 8) {
			// An entire byte has been filled. Push it back on the display arrays
			mosi[displayPosition] = currentMOSI;
			displayPosition++;
			bitsFilled = 0;
//			printOneChar(mosi[0], 1);
//			UART_printf(" ");
//			mosi[0] = 0;
			
//			if (displayPosition >= DISPLAYSIZE || HAL_GetTick() - lastTime >= 100) {
//  		uint16_t oldDisplayPosition = displayPosition; // Make sure it doesn't change
//  		// Copy the data so no one writes on it
//  		memcpy(mosiPrint, mosi, oldDisplayPosition);
//				displayPosition = 0;
//			xHigherPriorityTaskWoken = pdFALSE;	
//if (oldDisplayPosition > 0) {				
//			xQueueSendFromISR(QueueMVHFromISR, &mosiPrint, &xHigherPriorityTaskWoken);
//}
//		}		
	}	
if (displayPosition >= STORESIZE) {
				// Back to the beginning
//				for (int i = 0; i < displayPosition; i++) {
//					printOneChar(mosi[i], 1);
//					UART_printf(" ");
//				}
//				memcpy(MVH_BUFFER, mosi, displayPosition);
//				xHigherPriorityTaskWoken = pdFALSE;
//				xQueueSendFromISR(QueueMVHFromISR, &MVH_BUFFER, &xHigherPriorityTaskWoken);				
				displayPosition = 0;
				overSized = 1;
			}		
	} else {
		
//		Error_Handler();
	}
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
