#include "W25Q.h"

union 
{
	float Float_value;
	uint8_t Array_value[4];
}Float_to_int;

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
  uint8_t temp[3] = {W25Q_WRITE_ENABLE, W25Q_CHIP_ERASE, W25Q_WRITE_DISABLE};
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

void W25Q_Write(uint8_t *page, uint16_t pagenum)
{
	uint8_t temp[4] = {W25Q_WRITE_ENABLE, 0x00, 0x00, 0x00};
  
  w25q_SetBlockProtect(0x00);
	HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, temp, 1, 100);
	HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_SET);
	temp[0] = W25Q_PAGE_PROGRAM;
  temp[1] = (uint8_t)(pagenum >> 8);
  temp[2] = (uint8_t)(pagenum & 0x00FF);
  temp[3] = 0x00;
	HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, temp, 4, 100);
  HAL_SPI_Transmit(&hspi1, page, W25Q_PAGE_LEN, 100);
	HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_SET);
	w25q_WaitForReady();
	temp[0] = W25Q_WRITE_DISABLE;
  HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi1, temp, 1, 100);
  HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_SET);    
  w25q_SetBlockProtect(0x0F);
}

void W25Q_Read(uint8_t *page, uint16_t pagenum)
{
	uint8_t com[5] = {W25Q_READ_PAGE, (uint8_t)(pagenum >> 8), (uint8_t)(pagenum & 0x00FF), 0x00, 0x00};
	HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi1, com, 5, 100);
  HAL_SPI_Receive(&hspi1, page, W25Q_PAGE_LEN, 100);
  HAL_GPIO_WritePin(F_CS_GPIO_Port, F_CS_Pin, GPIO_PIN_SET);
}

void ConvertStructToArray(Saved_parameters_Typedef *Struct, uint8_t *Array)
{	
	
	Array[0] = Struct->Amplification;	
	Array[1] = Struct->Bass;
	Array[2] = Struct->Brightness;
	Array[3] = Struct->Fuel_mode;
	Array[4] = Struct->Pressure_mode;
	Array[5] = Struct->FL;
	Array[6] = Struct->FR;
	Array[7] = Struct->K;
	Array[8] = Struct->OBD_mode;
	Array[9] = Struct->RL;
	Array[10] = Struct->RR;
	Array[11] = Struct->Temperature_mode;
	Array[12] = Struct->Treble;
	Array[13] = Struct->Volume;
	Float_to_int.Float_value = Struct->Average_consumption;
	Array[14] = Float_to_int.Array_value[0];
	Array[15] = Float_to_int.Array_value[1];
	Array[16] = Float_to_int.Array_value[2];
	Array[17] = Float_to_int.Array_value[3];
	Array[18] = (Struct->key) & 0xFF;
	Array[19] = ((Struct->key) >> 8) & 0xFF;
	Array[20] = ((Struct->key) >> 16) & 0xFF;
	Array[21] = ((Struct->key) >> 24) & 0xFF;
}

void ConvertArrayToStruct( uint8_t *Array, Saved_parameters_Typedef *Struct)
{
	Struct->Amplification = Array[0];
	Struct->Bass = Array[1];
	Struct->Brightness = Array[2];
	Struct->Fuel_mode = Array[3];
	Struct->Pressure_mode = Array[4];
	Struct->FL = Array[5];
	Struct->FR = Array[6];
	Struct->K = Array[7];
	Struct->OBD_mode = Array[8];
	Struct->RL = Array[9];
	Struct->RR = Array[10];
	Struct->Temperature_mode = Array[11];
	Struct->Treble = Array[12];
	Struct->Volume = Array[13];
	Float_to_int.Array_value[0] = Array[14];
	Float_to_int.Array_value[1] = Array[15];
	Float_to_int.Array_value[2] = Array[16];
	Float_to_int.Array_value[3] = Array[17];
	Struct->Average_consumption = Float_to_int.Float_value;
	Struct->key = Array[18] || (Array[19] <<8) || (Array[20] <<16) || (Array[21] <<24);
}

void LoadDefaultParameters(Saved_parameters_Typedef *Struct)
{
	Struct->Amplification = 4;
	Struct->Bass = 14;
	Struct->Brightness = 127;
	Struct->FL = 0;
	Struct->FR = 0;
	Struct->K = 60;
	Struct->OBD_mode = 1;
	Struct->RL = 0;
	Struct->RR = 0;
	Struct->Temperature_mode = 1;
	Struct->Treble = 14;
	Struct->Volume = 48;
	Struct->Fuel_mode = 0;
	Struct->Average_consumption = 10.0f;
	Struct->Pressure_mode = 0;
}
