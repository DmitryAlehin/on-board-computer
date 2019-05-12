//#include "GUI.h"
//#include "spi.h"
//#include "stm32f4xx_it.h"
//extern uint8_t TOUCH_PRESSED;
//void GUI_TOUCH_X_ActivateX(void)
//{
//	return;
//}

//void GUI_TOUCH_X_ActivateY(void)
//{
//	return;
//}

//int  GUI_TOUCH_X_MeasureX(void) 
//{
//	
//	uint16_t buff = 0;
//	uint8_t cmd, temp;
//	int16_t x;
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
//  cmd = 0xD0;
//	HAL_SPI_TransmitReceive(&hspi2, &cmd, (uint8_t *) &temp, 1, 3000); // отправляем команду на X
//	HAL_Delay(1); 

//	cmd  = 0;
//	temp = 0;
//	
//	HAL_SPI_TransmitReceive(&hspi2, &cmd, (uint8_t *) &temp, 1, 3000);
//  buff = temp<<4;	
//	HAL_SPI_TransmitReceive(&hspi2, &cmd, (uint8_t *) &temp, 1, 3000); // получаем младший байт и одновременно отправляем команду на Y
//	HAL_Delay(1); 
//  buff |= temp>>4; 
//  x = buff >>4 ; //получение Х
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
//		
//	return (int)x;
//	
//}

//int  GUI_TOUCH_X_MeasureY(void)
//{
//	uint16_t buff = 0;
//	uint8_t cmd, temp;
//	int16_t y;
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
//	cmd = 0x90;
//	HAL_SPI_TransmitReceive(&hspi2, &cmd, (uint8_t *) &temp, 1, 3000); // получаем младший байт и одновременно отправляем команду на Y
//	HAL_Delay(1);
//	
//	cmd = 0;
//	temp = 0;
//	
//	HAL_SPI_TransmitReceive(&hspi2, &cmd, (uint8_t *) &temp, 1, 3000);
//  buff = temp<<4; 
//	HAL_SPI_TransmitReceive(&hspi2, &cmd, (uint8_t *) &temp, 1, 3000);
//  buff |= temp>>4; 
//  y = buff >>4 ; //получение Y
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
//		
//	return (int)y;
//	
//}