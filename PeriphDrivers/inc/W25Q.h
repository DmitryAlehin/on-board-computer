#ifndef W25Q_H
#define W25Q_H

#include "stm32f4xx_hal.h"
#include "spi.h"

#define W25Q_SECTOR_4           0x04
#define W25Q_BLOCK_64           0x40
#define W25Q_PAGE_16            0x1FFF
#define W25Q_WRITE_ENABLE       0x06
#define W25Q_WRITE_DISABLE      0x04
#define W25Q_RD_STATUS_1        0x05       
#define W25Q_RD_STATUS_2        0x35
#define W25Q_WR_STATUS          0x01
#define W25Q_PAGE_PROGRAM       0x02
#define W25Q_Q_PAGE_PROGRAM     0x32
#define W25Q_BLOCK_ERASE_64     0xD8
#define W25Q_BLOCK_ERASE_32     0x52
#define W25Q_SECTOR_ERASE_4     0x20
#define W25Q_CHIP_ERASE         0xC7
#define W25Q_ERASE_SUSPEND      0X75
#define W25Q_ERASE_RESUME       0x7A
#define W25Q_POWER_DOWN         0xB9
#define W25Q_HI_PF_MODE         0xA3
#define W25Q_MODE_BIT_RESET     0xFF
#define W25Q_RS_PWR_DOUN        0xAB
#define W25Q_MNF_DEVICE_ID      0x90
#define W25Q_RD_UNIQUE_ID       0x4B
#define W25Q_JEDEC_ID           0x9F
#define W25Q_READ_PAGE          0x0B
#define W25Q_PAGE_LEN           256
#define W25Q_NUMBERS_OF_PAGES   8192

typedef struct
{
	uint8_t Brightness;
	uint8_t Temperature_mode;
	uint8_t OBD_mode;
	uint8_t Debug_mode;
	uint8_t Consumption_mode;
	uint8_t K;
	uint8_t Volume;
	uint32_t key;
	float Average_consumption;
	int8_t FL;
	int8_t FR;
	int8_t RL;
	int8_t RR;
	int8_t Bass;
	int8_t Treble;
	int8_t Amplification;
}Saved_parameters_Typedef;

void W25Q_ChipErase(void);
void W25Q_Write(uint8_t *page, uint16_t pagenum);
void W25Q_Read(uint8_t *page, uint16_t pagenum);
void w25q_SetBlockProtect(uint8_t protect);
void w25q_WaitForReady(void);
void ConvertStructToArray(Saved_parameters_Typedef *Struct, uint8_t *Array);
void ConvertArrayToStruct( uint8_t *Array, Saved_parameters_Typedef *Struct);
#endif
