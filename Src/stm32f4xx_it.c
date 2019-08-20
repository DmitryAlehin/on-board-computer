/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
#include "cmsis_os.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "TouchPanel.h"
#include "GUI.h"
#include "OBDII.h"
#include "RDA5807m.h"
#include "freertos.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
extern OBD_Data_States_Typedef OBD_Data_State;
extern RDA5807M_Update_States_Typedef RDA5807M_Update_States;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern RTC_HandleTypeDef hrtc;
extern TIM_HandleTypeDef htim7;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim1;

/* USER CODE BEGIN EV */
extern uint8_t DMA_BUFFER_OBD[DMA_BUFFER_OBD_SIZE];
extern uint8_t OBD_BUFFER[DMA_BUFFER_OBD_SIZE];

extern uint8_t DMA_BUFFER_BT[DMA_BUFFER_BT_SIZE];
extern uint8_t BT_BUFFER[DMA_BUFFER_BT_SIZE];
extern xQueueHandle QueueODBFromISR;
extern xQueueHandle QueueBTFromISR;

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles RTC wake-up interrupt through EXTI line 22.
  */
void RTC_WKUP_IRQHandler(void)
{
  /* USER CODE BEGIN RTC_WKUP_IRQn 0 */
	/* Check for RTC interrupt */
	if (__HAL_RTC_WAKEUPTIMER_GET_IT(&hrtc, RTC_IT_WUT) != RESET) {
		/* Call user function */
		RTC_WakeupCallback();
		
		/* Clear interrupt flags */
		__HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&hrtc, RTC_FLAG_WUTF);
	}
	
	/* Clear EXTI line 22 bit */
	__HAL_RTC_WAKEUPTIMER_EXTI_CLEAR_FLAG();
  /* USER CODE END RTC_WKUP_IRQn 0 */
  HAL_RTCEx_WakeUpTimerIRQHandler(&hrtc);
  /* USER CODE BEGIN RTC_WKUP_IRQn 1 */

  /* USER CODE END RTC_WKUP_IRQn 1 */
}

/**
  * @brief This function handles RCC global interrupt.
  */
void RCC_IRQHandler(void)
{
  /* USER CODE BEGIN RCC_IRQn 0 */

  /* USER CODE END RCC_IRQn 0 */
  /* USER CODE BEGIN RCC_IRQn 1 */

  /* USER CODE END RCC_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream5 global interrupt.
  */
void DMA1_Stream5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream5_IRQn 0 */
	static BaseType_t xHigherPriorityTaskWoken;
	typedef struct
	{
		__IO uint32_t ISR;   /*!< DMA interrupt status register */
		__IO uint32_t Reserved0;
		__IO uint32_t IFCR;  /*!< DMA interrupt flag clear register */
	} DMA_Base_Registers;

	DMA_Base_Registers *regs = (DMA_Base_Registers *)hdma_usart2_rx.StreamBaseAddress;
	if ((regs->ISR & (DMA_FLAG_TCIF0_4 << hdma_usart2_rx.StreamIndex)) != RESET)
  {
		if(__HAL_DMA_GET_IT_SOURCE(&hdma_usart2_rx, DMA_IT_TC) != RESET)
		{
			regs->IFCR = DMA_FLAG_TCIF0_4 << hdma_usart2_rx.StreamIndex;
			memcpy(&BT_BUFFER, &DMA_BUFFER_BT, DMA_BUFFER_BT_SIZE);
			for(uint8_t i=0; i<DMA_BUFFER_BT_SIZE; i++)
			{
				DMA_BUFFER_BT[i] = 0;
			}
			xHigherPriorityTaskWoken = pdFALSE;					
			xQueueSendFromISR(QueueBTFromISR, &BT_BUFFER, &xHigherPriorityTaskWoken);
			regs->IFCR = 0x3FU << hdma_usart2_rx.StreamIndex; // clear all interrupts
			hdma_usart2_rx.Instance->M0AR = (uint32_t)DMA_BUFFER_BT;   /* Set memory address for DMA again */
			hdma_usart2_rx.Instance->NDTR = DMA_BUFFER_BT_SIZE;    /* Set number of bytes to receive */
			hdma_usart2_rx.Instance->CR |= DMA_SxCR_EN;            /* Start DMA transfer */
		}
}
  /* USER CODE END DMA1_Stream5_IRQn 0 */
//  HAL_DMA_IRQHandler(&hdma_usart2_rx);
  /* USER CODE BEGIN DMA1_Stream5_IRQn 1 */

  /* USER CODE END DMA1_Stream5_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream6 global interrupt.
  */
void DMA1_Stream6_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream6_IRQn 0 */

  /* USER CODE END DMA1_Stream6_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_tx);
  /* USER CODE BEGIN DMA1_Stream6_IRQn 1 */

  /* USER CODE END DMA1_Stream6_IRQn 1 */
}

/**
  * @brief This function handles TIM1 update interrupt and TIM10 global interrupt.
  */
void TIM1_UP_TIM10_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 0 */

  /* USER CODE END TIM1_UP_TIM10_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 1 */

  /* USER CODE END TIM1_UP_TIM10_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
	if (huart1.Instance->SR & UART_FLAG_IDLE)
	{
		volatile uint32_t tmp;
        tmp = huart1.Instance->SR;
        tmp = huart1.Instance->DR;
		hdma_usart1_rx.Instance->CR &= ~DMA_SxCR_EN; 
	}
  /* USER CODE END USART1_IRQn 0 */
//  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
	if (huart2.Instance->SR & UART_FLAG_IDLE)
	{
		volatile uint32_t tmp;
        tmp = huart2.Instance->SR;
        tmp = huart2.Instance->DR;
		hdma_usart2_rx.Instance->CR &= ~DMA_SxCR_EN;
	}
  /* USER CODE END USART2_IRQn 0 */
//  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

/**
  * @brief This function handles TIM7 global interrupt.
  */
void TIM7_IRQHandler(void)
{
  /* USER CODE BEGIN TIM7_IRQn 0 */
	if ((htim7.Instance == TIM7) && (OBD_Data_State == CALCULATE_END)) 
	{				
    OBD_Data_State = READY_TO_RECEIVE;
  }
	if ((htim7.Instance == TIM7) && (RDA5807M_Update_States == RDA5807M_RSSI_UPDATE)) 
	{				
    RDA5807M_Update_States = RDA5807M_RSSI_WAIT;
  }
  /* USER CODE END TIM7_IRQn 0 */
  HAL_TIM_IRQHandler(&htim7);
  /* USER CODE BEGIN TIM7_IRQn 1 */

  /* USER CODE END TIM7_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream2 global interrupt.
  */
void DMA2_Stream2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream2_IRQn 0 */
	static BaseType_t xHigherPriorityTaskWoken;
	typedef struct
	{
		__IO uint32_t ISR;   /*!< DMA interrupt status register */
		__IO uint32_t Reserved0;
		__IO uint32_t IFCR;  /*!< DMA interrupt flag clear register */
	} DMA_Base_Registers;

	DMA_Base_Registers *regs = (DMA_Base_Registers *)hdma_usart1_rx.StreamBaseAddress;
	if ((regs->ISR & (DMA_FLAG_TCIF0_4 << hdma_usart1_rx.StreamIndex)) != RESET)
  {
		if(__HAL_DMA_GET_IT_SOURCE(&hdma_usart1_rx, DMA_IT_TC) != RESET)
		{
			regs->IFCR = DMA_FLAG_TCIF0_4 << hdma_usart1_rx.StreamIndex;
			memcpy(&OBD_BUFFER, &DMA_BUFFER_OBD, DMA_BUFFER_OBD_SIZE);
			for(uint8_t i=0; i<DMA_BUFFER_OBD_SIZE; i++)
			{
				DMA_BUFFER_OBD[i] = 0;
			}
		  xHigherPriorityTaskWoken = pdFALSE;					
			xQueueSendFromISR(QueueODBFromISR, &OBD_BUFFER, &xHigherPriorityTaskWoken);				
			regs->IFCR = 0x3FU << hdma_usart1_rx.StreamIndex; // clear all interrupts
			hdma_usart1_rx.Instance->M0AR = (uint32_t)DMA_BUFFER_OBD;   /* Set memory address for DMA again */
			hdma_usart1_rx.Instance->NDTR = DMA_BUFFER_OBD_SIZE;    /* Set number of bytes to receive */
			hdma_usart1_rx.Instance->CR |= DMA_SxCR_EN;            /* Start DMA transfer */
		}
}
  /* USER CODE END DMA2_Stream2_IRQn 0 */
//  HAL_DMA_IRQHandler(&hdma_usart1_rx);
  /* USER CODE BEGIN DMA2_Stream2_IRQn 1 */

  /* USER CODE END DMA2_Stream2_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream7 global interrupt.
  */
void DMA2_Stream7_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream7_IRQn 0 */
	
  /* USER CODE END DMA2_Stream7_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_tx);
  /* USER CODE BEGIN DMA2_Stream7_IRQn 1 */

  /* USER CODE END DMA2_Stream7_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
