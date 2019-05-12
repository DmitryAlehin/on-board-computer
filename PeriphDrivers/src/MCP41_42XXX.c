#include "MCP41_42XXX.h"



void MCP41_Write(uint8_t value)
{
	uint8_t txBuffer[1];
	HAL_GPIO_WritePin(K1_CS_GPIO_Port, K1_CS_Pin, GPIO_PIN_RESET);
	txBuffer[0] = 0x11;
	HAL_SPI_Transmit(&hspi1, (uint8_t *)txBuffer, 1, 100);
	txBuffer[0] = value;
	HAL_SPI_Transmit(&hspi1, (uint8_t *)txBuffer, 1, 100);
	HAL_GPIO_WritePin(K1_CS_GPIO_Port, K1_CS_Pin, GPIO_PIN_SET);
}

void MCP42_Write(uint8_t value, uint8_t channel)
{
	uint8_t txBuffer[1];
	
	switch(channel)
	{
		case 1:			
			txBuffer[0] = 0x11;
			HAL_SPI_Transmit(&hspi1, (uint8_t *)txBuffer, 1, 100);
			txBuffer[0] = value;
			HAL_SPI_Transmit(&hspi1, (uint8_t *)txBuffer, 1, 100);
			break;
		case 2:
			HAL_GPIO_WritePin(K2_CS_GPIO_Port, K2_CS_Pin, GPIO_PIN_RESET);
			txBuffer[0] = 0x12;
			HAL_SPI_Transmit(&hspi1, (uint8_t *)txBuffer, 1, 100);
			txBuffer[0] = value;
			HAL_SPI_Transmit(&hspi1, (uint8_t *)txBuffer, 1, 100);
			HAL_GPIO_WritePin(K2_CS_GPIO_Port, K2_CS_Pin, GPIO_PIN_SET);			
			break;
	}
	
}

void MCP_Idle(uint8_t channel)
{
	uint8_t txBuffer[1];	
	switch(channel)
	{
		case 0:
			HAL_GPIO_WritePin(K1_CS_GPIO_Port, K1_CS_Pin, GPIO_PIN_RESET);
			txBuffer[0] = 0x11;
			HAL_SPI_Transmit(&hspi1, (uint8_t *)txBuffer, 1, 100);
			txBuffer[0] = 0xFF;
			HAL_SPI_Transmit(&hspi1, (uint8_t *)txBuffer, 1, 100);
			HAL_GPIO_WritePin(K1_CS_GPIO_Port, K1_CS_Pin, GPIO_PIN_SET);
			break;
		case 1:
			HAL_GPIO_WritePin(K2_CS_GPIO_Port, K2_CS_Pin, GPIO_PIN_RESET);			
			txBuffer[0] = 0x11;
			HAL_SPI_Transmit(&hspi1, (uint8_t *)txBuffer, 1, 100);
			txBuffer[0] = 0xFF;
			HAL_SPI_Transmit(&hspi1, (uint8_t *)txBuffer, 1, 100);
			HAL_GPIO_WritePin(K2_CS_GPIO_Port, K2_CS_Pin, GPIO_PIN_SET);	
			break;
		case 2:
			HAL_GPIO_WritePin(K2_CS_GPIO_Port, K2_CS_Pin, GPIO_PIN_RESET);
			txBuffer[0] = 0x12;
			HAL_SPI_Transmit(&hspi1, (uint8_t *)txBuffer, 1, 100);
			txBuffer[0] = 0xFF;
			HAL_SPI_Transmit(&hspi1, (uint8_t *)txBuffer, 1, 100);
			HAL_GPIO_WritePin(K2_CS_GPIO_Port, K2_CS_Pin, GPIO_PIN_SET);			
			break;
	}	
}