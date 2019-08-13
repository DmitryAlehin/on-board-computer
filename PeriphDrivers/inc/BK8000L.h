#ifndef BK8000L_H
#define BK8000L_H

#include "usart.h"
#include "DIALOG.h"
extern WM_MESSAGE msg;
extern uint8_t BT_BUFFER[DMA_BUFFER_BT_SIZE];

typedef enum 
{
	WAIT_BT_INIT = 0,
	BT_ON,
	BT_NAME_RECEIVED,
	BT_PIN_RECEIVED,
	BT_INIT_OK,
	BT_CHECK_POWER,
}BT_General_States_Typedef;

typedef enum 
{
	WAIT = 0,
	BT_CONNECTED,
	BT_DISCONNECTED,
	BT_PAUSE,
	BT_PLAY,
	BT_CALL
}BT_States_Typedef;

typedef enum 
{
	ON = 0,
	OFF
}BT_PowerMode_Typedef;

typedef struct
{	
	uint8_t BT_NAME[10], PIN[10], CALL_NUMBER[13]; 	
}BT_Values_Typedef;

void BTCheckState(uint8_t * buffer, BT_Values_Typedef * Bluetooth);
void BT_Init(void);
#endif
