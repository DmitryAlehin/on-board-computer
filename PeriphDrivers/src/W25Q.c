#include "W25Q.h"

void w25q_WaitForReady(void)
{
  uint8_t reg = W25Q_RD_STATUS_1;
  uint8_t status = 0;
  HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_RESET);
  do
  {
    status = 0;
    HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_RESET); 
    HAL_SPI_Transmit(&hspi1, &reg, 1, 100);
    HAL_SPI_Receive(&hspi1, &status, 1, 100);
    HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_SET);
  }
  while (status & 0x01);  
}

void w25q_SetBlockProtect(uint8_t protect)
{
  uint8_t temp[] = {0x50, 0x00};
  HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi1, temp, 1, 100);
  HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_SET);    
  temp[0] = W25Q_WR_STATUS;
  temp[1] = ((protect & 0x0F) << 2);
  HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi1, temp, 2, 100);
  HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_SET);
}

void W25Q_ChipErase(void)
{
	w25q_SetBlockProtect(0x00);    
  uint8_t temp[3] = {W25Q_WRITE_ENABLE, W25Q_CHIP_ERASE, W25Q_WRRITE_DISABLE};
  HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, &temp[0], 1, 100);
  HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_SET);    
  HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, &temp[1], 1, 100);
  HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_SET);
  w25q_WaitForReady();   
  HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, &temp[2], 1, 100);
  HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_SET);
  w25q_SetBlockProtect(0x0F);
}

void W25Q_Write(Saved_parameters_Typedef *Params)
{
	
}