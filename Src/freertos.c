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
#include "W25Q.h"
#include "bmp280.h"
#include "TDA7318.h"
#include "RDA5807m.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
GUI_PID_STATE TS_State;
WM_MESSAGE msg;

OBD_General_States_Typedef OBD_General_State = NOP;
CarParameters_Typedef CarParameters;
OBD_Sign_States_Typedef OBD_Sign_State = OBD_OK;
OBD_Data_States_Typedef OBD_Data_State = WAIT_DATA;
OBD_Average_Cons_States_Typedef OBD_Average_Cons_State = CONSUMPTION_WAIT_RECEIVE;
BT_General_States_Typedef BT_General_State = WAIT_BT_INIT;
TDA7318_States_Typedef TDA7318_General_State = TDA7318_WAIT_INIT;
TDA7318_Volume_States_Typedef TDA7318_Volume_State = TDA7318_UNMUTE;
Audio_Switch_States_Typedef Audio_Switch = INPUT_1_SWITCH;
BT_States_Typedef BT_State = WAIT;
BT_Values_Typedef BT_Value;
BT_PowerMode_Typedef BT_PowerMode = OFF;
volatile uint8_t count;
extern uint8_t DMA_BUFFER_OBD[DMA_BUFFER_OBD_SIZE];
extern uint8_t OBD_BUFFER[DMA_BUFFER_OBD_SIZE];
extern uint8_t DMA_BUFFER_BT[DMA_BUFFER_BT_SIZE];
extern uint8_t BT_BUFFER[DMA_BUFFER_BT_SIZE];
CarValues_Typedef Car_Param;
Saved_parameters_Typedef Saved_Parameters;
extern GUIHandles GuiHandles;
BMP280_HandleTypedef BMP280;
TnP Temp_Pres;
//bmp280_params_t BMP280_param;
volatile uint8_t buf[50];

uint8_t TX_BUFFER[256];
uint8_t RX_BUFFER[256];
float Current_Consumption[30];
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
osThreadId AudioHandle;
osThreadId TouchHandle;
osThreadId MeteoHandle;
osThreadId SaveReadParametHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void _GUI(void const * argument);
void _Parser(void const * argument);
void _OBD(void const * argument);
void _Audio(void const * argument);
void _Touch(void const * argument);
void _Meteo(void const * argument);
void _SaveReadParameters(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  Touch_Cal_Read(&matrix);
	__HAL_RCC_CRC_CLK_ENABLE();
//	BMP280.addr = BMP280_I2C_ADDRESS_0;
//	bmp280_init_default_params(&BMP280_param);
//	HAL_GPIO_WritePin(RADIO_EN_GPIO_Port, RADIO_EN_Pin, GPIO_PIN_SET);
	
//		Saved_Parameters.key = 41312;		
//	OBD_General_State = NOP;
//	W25Q_Read(RX_BUFFER,1);
	
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

  /* USER CODE BEGIN RTOS_QUEUES */
	QueueODBFromISR = xQueueCreate(1, sizeof(DMA_BUFFER_OBD));
	QueueBTFromISR = xQueueCreate(1, sizeof(DMA_BUFFER_BT));
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
	/* definition and creation of SaveReadParamet */
  osThreadDef(SaveReadParamet, _SaveReadParameters, osPriorityNormal, 0, 2048);
  SaveReadParametHandle = osThreadCreate(osThread(SaveReadParamet), NULL);
	
  /* definition and creation of GUI */
  osThreadDef(GUI, _GUI, osPriorityNormal, 0, 2048);
  GUIHandle = osThreadCreate(osThread(GUI), NULL);

  /* definition and creation of Parser */
  osThreadDef(Parser, _Parser, osPriorityNormal, 0, 2048);
  ParserHandle = osThreadCreate(osThread(Parser), NULL);

  /* definition and creation of OBD */
  osThreadDef(OBD, _OBD, osPriorityNormal, 0, 1024);
  OBDHandle = osThreadCreate(osThread(OBD), NULL);

  /* definition and creation of Audio */
  osThreadDef(Audio, _Audio, osPriorityNormal, 0, 512);
  AudioHandle = osThreadCreate(osThread(Audio), NULL);

  /* definition and creation of Touch */
  osThreadDef(Touch, _Touch, osPriorityNormal, 0, 512);
  TouchHandle = osThreadCreate(osThread(Touch), NULL);

  /* definition and creation of Meteo */
  osThreadDef(Meteo, _Meteo, osPriorityNormal, 0, 256);
  MeteoHandle = osThreadCreate(osThread(Meteo), NULL);

  

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header__SaveReadParameters */
/**
* @brief Function implementing the SaveReadParamet thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header__SaveReadParameters */
void _SaveReadParameters(void const * argument)
{
  /* USER CODE BEGIN _SaveReadParameters */
	W25Q_Read(RX_BUFFER,1);
	ConvertArrayToStruct(RX_BUFFER, &Saved_Parameters);
	LCD_Brightness(Saved_Parameters.Brightness);
  /* Infinite loop */
  for(;;)
  {
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		ConvertStructToArray(&Saved_Parameters, TX_BUFFER);
		W25Q_Read(RX_BUFFER,1);
		if(memcmp(RX_BUFFER, TX_BUFFER, 256) != 0)
		{
			W25Q_ChipErase();
			W25Q_Write(TX_BUFFER, 1);
			HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		}
//		ConvertArrayToStruct(RX_BUFFER, &Saved_Parameters);
    osDelay(50000);
  }
  /* USER CODE END _SaveReadParameters */
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
  /* USER CODE BEGIN _GUI */
	GUI_Init();
	CreateMainWindow();
  /* Infinite loop */
  for(;;)
  {
    
		GUI_Exec();	
		
		switch(msg.MsgId)
		{
			case WM_UPDATE_MIN:
				WM_SendMessage(GuiHandles.hMainWindow, &msg);
				msg.MsgId = WM_UPDATE_MIN;
				WM_SendMessage(GuiHandles.hAudioWindow, &msg);				
				break;
			case WM_UPDATE_CAR:
				WM_SendMessage(GuiHandles.hMainWindow, &msg);
				msg.MsgId = WM_UPDATE_CAR;				
				WM_SendMessage(GuiHandles.hAudioWindow, &msg);
				break;
			case WM_UPDATE_AUDIO:
				WM_SendMessage(GuiHandles.hAudioWindow, &msg);
				break;
			case WM_UPDATE_BT:
				WM_SendMessage(GuiHandles.hAudioWindow, &msg);
				break;
			case WM_UPDATE_BT_POWERMODE:
				WM_SendMessage(GuiHandles.hAudioWindow, &msg);
				break;
			case WM_UPDATE_METEO:
				WM_SendMessage(GuiHandles.hMainWindow, &msg);
				break;
			case WM_AUX:
				WM_SendMessage(GuiHandles.hMainWindow, &msg);
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
				if(BT_PowerMode != OFF)
				{
					BTCheckState(BT_BUFFER, &BT_Value);	
				}					
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
	uint8_t k = 0;
  /* Infinite loop */
  for(;;)
  {		
		if(Saved_Parameters.OBD_mode)
		{			
			OBD_Init();		
			if(OBD_General_State == OBD_INIT)
			{	
				OBD_Update();
			
			if(OBD_Data_State == COMPLETE_ALL_DATA)
			{			
				Car_Param.Voltage = CarParameters.Voltage;
				Car_Param.ECT = CarParameters.ECT - 40.0;
				Car_Param.FUEL = ((CarParameters.FUEL) * 100.0) / 255.0;
				Car_Param.FUEL_Liters = Car_Param.FUEL / 100.0 * 55.0;
				VSS = CarParameters.VSS;
				if(VSS <= 0)
				{
					VSS = 1;
				}
				IAT = CarParameters.IAT - 40.0;
				LONGFT = ((CarParameters.LONGFT - 128.0) * 100.0) / 128.0;
				SHRTFT = ((CarParameters.SHRTFT - 128.0) * 100.0) / 128.0;
				MAP = CarParameters.MAP;
				RPM = (CarParameters.RPM_A * 256.0 + CarParameters.RPM_B)/4;
				Fb = (Saved_Parameters.K / 100.0) * (RPM / 60.0) * MAP * 0.8 * 28.98 / (8.31441 * (IAT + 273.15));
				Ft = 1000.0 * (1 + 0.001 * (IAT - 20.0)) * 3600.0 * Fb * 1 + ((SHRTFT + LONGFT) / 100.0) / (14.7 * 750.0);
				Car_Param.Fuel_consumption = Ft / (VSS * 1000000.0);
				Car_Param.LH_consumption = Ft;
				if(OBD_Average_Cons_State == CONSUMPTION_WAIT_RECEIVE)
				{
				Current_Consumption[k] = Car_Param.Fuel_consumption;
				k++;
				if(k == 50)
				{
					OBD_Average_Cons_State = CONSUMPTION_RECEIVE;
					k = 0;
				}
				}
				OBD_Data_State = CALCULATE_END;
				msg.MsgId = WM_UPDATE_CAR;			
			}
			if(OBD_Average_Cons_State == CONSUMPTION_RECEIVE)
			{
				for(uint8_t i = 0; i < 50; i++)
				{
					Current_Consumption[0] += Current_Consumption[i];
				}
				Saved_Parameters.Average_consumption = Current_Consumption[0]/50.0;
				OBD_Average_Cons_State = CONSUMPTION_WAIT_RECEIVE;
			}
		}
	}
}
  
  /* USER CODE END _OBD */
}

/* USER CODE BEGIN Header__Audio */
/**
* @brief Function implementing the Audio thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header__Audio */
void _Audio(void const * argument)
{
  /* USER CODE BEGIN _Audio */
  /* Infinite loop */
  for(;;)
  {	
		BT_Init();
  }
  /* USER CODE END _Audio */
}

/* USER CODE BEGIN Header__Touch */
/**
* @brief Function implementing the Touch thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header__Touch */
void _Touch(void const * argument)
{
  /* USER CODE BEGIN _Touch */
  /* Infinite loop */
  for(;;)
  {		
		Touch_Update();   
		
  }
  /* USER CODE END _Touch */
}

/* USER CODE BEGIN Header__Meteo */
/**
* @brief Function implementing the Meteo thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header__Meteo */
void _Meteo(void const * argument)
{
  /* USER CODE BEGIN _Meteo */
	HAL_GPIO_WritePin(RADIO_BMP280_EN_GPIO_Port, RADIO_BMP280_EN_Pin, GPIO_PIN_SET);	
	BMP280.addr = BMP280_I2C_ADDRESS_0;	
	bmp280_init(&BMP280);
	bmp280_read_float(&BMP280, &Temp_Pres.Temperature, &Temp_Pres.Pressure);
	Temp_Pres.Pressure = Temp_Pres.Pressure/133.3224;
  /* Infinite loop */
  for(;;)
  {
    if(Saved_Parameters.Temperature_mode)
		{				
		bmp280_read_float(&BMP280, &Temp_Pres.Temperature, &Temp_Pres.Pressure);
		Temp_Pres.Pressure = Temp_Pres.Pressure/133.3224;
		msg.MsgId = WM_UPDATE_METEO;
		}
		osDelay(5000);
  }
  /* USER CODE END _Meteo */
}



/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */


void RTC_WakeupCallback(void) {		
	msg.MsgId = WM_UPDATE_MIN;
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
