#include "BK8000L.h"
extern BT_General_States_Typedef BT_General_State;
extern BT_States_Typedef BT_State;
extern BT_Values_Typedef BT_Value;
void BTCheckState(uint8_t * buffer, BT_Values_Typedef * Bluetooth)
{
	if(buffer[0] == 'O' && buffer[1] == 'N')
	{
		BT_General_State = BT_ON;
	}
	if(buffer[0] == 'I' && buffer[1] == 'I')
	{		
		BT_State = BT_CONNECTED;
		msg.MsgId = WM_UPDATE_BT;
	}
	if(buffer[0] == 'I' && buffer[1] == 'A')
	{
		BT_State = BT_DISCONNECTED;
		msg.MsgId = WM_UPDATE_BT;
	}
	if(buffer[0] == 'M' && buffer[1] == 'A')
	{
		BT_State = BT_PAUSE;
		msg.MsgId = WM_UPDATE_BT;
	}
	if(buffer[0] == 'M' && buffer[1] == 'B')
	{
		BT_State = BT_PLAY;
		msg.MsgId = WM_UPDATE_BT;
	}
	if(buffer[0] == 'N' && buffer[1] == 'A')
	{
		if(sscanf((char *)buffer, "NA: %s", Bluetooth->BT_NAME) == 1)
		{
			BT_General_State = BT_NAME_RECEIVED;
		}
	}
	if(buffer[0] == ' ' && buffer[1] == 'P' && buffer[2] == 'N')
	{
		if(sscanf((char *)buffer, " PN: %s", Bluetooth->PIN) == 1)
		{
			BT_General_State = BT_PIN_RECEIVED;
		}
	}
	if(buffer[0] == 'M' && buffer[1] == 'B')
	{
		BT_State = BT_PLAY;
		msg.MsgId = WM_UPDATE_BT;
	}
	if(buffer[0] == 'M' && buffer[1] == 'A')
	{
		BT_State = BT_PAUSE;
		msg.MsgId = WM_UPDATE_BT;
	}
	if(buffer[0] == 'I' && buffer[1] == 'I')
	{
		BT_State = BT_CONNECTED;
		msg.MsgId = WM_UPDATE_BT;
	}
	if(buffer[0] == 'I' && buffer[1] == 'A')
	{
		BT_State = BT_DISCONNECTED;
		msg.MsgId = WM_UPDATE_BT;
	}
	if(buffer[0] == 'C' && buffer[1] == '1')
	{
		BT_State = BT_CONNECTED;
		msg.MsgId = WM_UPDATE_BT;
	}
	if(buffer[0] == 'C' && buffer[1] == '0')
	{
		BT_State = BT_DISCONNECTED;
		msg.MsgId = WM_UPDATE_BT;
	}
//	else
//	{
//		msg.MsgId = WM_UPDATE_BT;
//	}
	for(uint8_t i = 0; i<DMA_BUFFER_BT_SIZE; i++)
	{
		buffer[i] = 0;
	}
}

void BT_Init(void)
{	
	switch(BT_General_State)
	{
		case WAIT_BT_INIT:
			break;
		case BT_ON:
			HAL_UART_Transmit(&huart2, "AT+MN\r\n", 8, 100);
			BT_General_State = WAIT_BT_INIT;
			break;
		case BT_NAME_RECEIVED:
			HAL_UART_Transmit(&huart2, "AT+MP\r\n", 8, 100);
			BT_General_State = WAIT_BT_INIT;
			break;	
		case BT_PIN_RECEIVED:			
			BT_General_State = BT_INIT_OK;
			msg.MsgId = WM_UPDATE_BT;
			break;
		case BT_INIT_OK:
		break;
		case BT_CHECK_POWER:
		HAL_UART_Transmit(&huart2, "AT+MO\r\n", 8, 100);
		BT_General_State = WAIT_BT_INIT;
		break;
	}
}
