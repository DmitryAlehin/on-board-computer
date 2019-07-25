#include "RDA5807m.h"

void RDA5807M_Init(void)
{
	uint8_t tx_data[2];
	uint16_t value = 0;
	value = RDA5807M_FLG_DHIZ | RDA5807M_FLG_DMUTE | RDA5807M_FLG_BASS | RDA5807M_FLG_SEEKUP | RDA5807M_FLG_RDS |  RDA5807M_FLG_NEW | RDA5807M_FLG_ENABLE | RDA5807M_FLG_SEEK;
	tx_data[0] = value >> 8;
	tx_data[1] = value;
	HAL_I2C_Mem_Write(&hi2c1, RDA5807M_ADDRESS<<1, RDA5807M_REG_CONFIG, 1, tx_data, 2, 100);
	value = RDA5807M_BAND_MASK | RDA5807M_BAND_WEST | RDA5807M_SPACE_100K;
	tx_data[0] = value >> 8;
	tx_data[1] = value;
	HAL_I2C_Mem_Write(&hi2c1, RDA5807M_ADDRESS<<1, RDA5807M_REG_TUNING, 1, tx_data, 2, 1000);
	tx_data[0] = 0x0F;
	HAL_I2C_Mem_Write(&hi2c1, RDA5807M_ADDRESS<<1, 0x05, 1, &tx_data[0], 1, 1000);
}

void RDA5807M_SeekUp(void)
{
	uint8_t tx_data[2];
	uint16_t value = 0;
	value = RDA5807M_FLG_DHIZ | RDA5807M_FLG_DMUTE | RDA5807M_FLG_BASS | RDA5807M_FLG_SEEKUP | RDA5807M_FLG_RDS |  RDA5807M_FLG_NEW | RDA5807M_FLG_ENABLE | RDA5807M_FLG_SEEK;
	tx_data[0] = value >> 8;
	tx_data[1] = value;
	HAL_I2C_Mem_Write(&hi2c1, RDA5807M_ADDRESS<<1, RDA5807M_REG_CONFIG, 1, tx_data, 2, 100);
}

void RDA5807M_SeekDown(void)
{
	uint8_t tx_data[2];
	uint16_t value = 0;
	value = RDA5807M_FLG_DHIZ | RDA5807M_FLG_DMUTE | RDA5807M_FLG_BASS | RDA5807M_FLG_SEEKDOWN | RDA5807M_FLG_RDS |  RDA5807M_FLG_NEW | RDA5807M_FLG_ENABLE | RDA5807M_FLG_SEEK;
	tx_data[0] = value >> 8;
	tx_data[1] = value;
	HAL_I2C_Mem_Write(&hi2c1, RDA5807M_ADDRESS<<1, RDA5807M_REG_CONFIG, 1, tx_data, 2, 100);
}

uint8_t RDA5807M_GetRSSI(void)
{
	uint8_t tx_data = RDA5807M_REG_RSSI;
	uint8_t rx_data[2];
	uint16_t value = 0;
	HAL_I2C_Master_Transmit(&hi2c1, RDA5807M_ADDRESS<<1, &tx_data, 1, 100);
	HAL_I2C_Master_Receive(&hi2c1, RDA5807M_ADDRESS<<1, rx_data, 2, 100);
	value = rx_data[0] << 8;
	value |= rx_data[1];
	return (value & RDA5807M_RSSI_MASK) >> RDA5807M_RSSI_SHIFT;
}

float RDA5807M_GetFrequency(void)
{
	uint8_t tx_data = RDA5807M_REG_STATUS;
	uint8_t rx_data[2];
	uint16_t value = 0;
	HAL_I2C_Master_Transmit(&hi2c1, RDA5807M_ADDRESS<<1, &tx_data, 1, 100);
	HAL_I2C_Master_Receive(&hi2c1, RDA5807M_ADDRESS<<1, rx_data, 2, 100);
	value = rx_data[0] << 8;
	value |= rx_data[1];
	return (0.1 * (value & RDA5807M_READCHAN_MASK)) + 87.5;
}

void RDA5807M_SetFrequency(float Freq)
{
	uint8_t tx_data[2];
	uint16_t value = 0;
	uint16_t Channel;
	Channel = (Freq - 87.5)/0.1;
	value =  RDA5807M_CHAN_MASK  | RDA5807M_FLG_TUNE | (Channel << RDA5807M_CHAN_SHIFT);
	tx_data[0] = value >> 8;
	tx_data[1] = value;
	HAL_I2C_Mem_Write(&hi2c1, RDA5807M_ADDRESS<<1, RDA5807M_REG_TUNING, 1, tx_data, 2, 100);
}

void RDA5807M_GetRDS(RDA5807M_Data_Typedef *Struct)
{
	uint8_t rx_data[2];
	HAL_I2C_Mem_Read(&hi2c1, RDA5807M_ADDRESS<<1, RDA5807M_RDSA, 1, rx_data, 2, 100);
	Struct->RDS_Text[0] = rx_data[0];
	Struct->RDS_Text[1] = rx_data[1];
	memset(rx_data, 0, 2);
	HAL_I2C_Mem_Read(&hi2c1, RDA5807M_ADDRESS<<1, RDA5807M_RDSB, 1, rx_data, 2, 100);
	Struct->RDS_Text[2] = rx_data[0];
	Struct->RDS_Text[3] = rx_data[1];
	memset(rx_data, 0, 2);
	HAL_I2C_Mem_Read(&hi2c1, RDA5807M_ADDRESS<<1, RDA5807M_RDSC, 1, rx_data, 2, 100);
	Struct->RDS_Text[4] = rx_data[0];
	Struct->RDS_Text[5] = rx_data[1];
	memset(rx_data, 0, 2);
	HAL_I2C_Mem_Read(&hi2c1, RDA5807M_ADDRESS<<1, RDA5807M_RDSD, 1, rx_data, 2, 100);
	Struct->RDS_Text[6] = rx_data[0];
	Struct->RDS_Text[7] = rx_data[1];
}