#include "MVH_08UB.h"

uint8_t Number[5];
extern MVH_States_Typedef MVH_States;
extern WM_MESSAGE msg;


void MVH_CheckState(uint8_t * buffer, MVH_Values_Typedef * MVH)
{
	if(buffer[0] == 0x82 && buffer[10] == 0x82 && buffer[20] == 0x82 && buffer[30] == 0x82)
	{
		for(uint8_t i = 0; i < 15; i++)
		{
			MVH->MVH_TEXT[i] = 0;
		}
		if(buffer[6] == 0x24 && buffer[7] == 0x05 && buffer[11] == 0x50 
			&& buffer[12] == 0x1A && buffer[13] == 0x52 && buffer[14] == 0xAA)
		{
			//AUX
			MVH_States = MVH_AUX;
			MVH->MVH_TEXT[0] = 'A';
			MVH->MVH_TEXT[1] = 'U';
			MVH->MVH_TEXT[2] = 'X';
			msg.MsgId = WM_UPDATE_MVH;
			if(buffer[31] == 0x90 && buffer[32] == 0x5A && buffer[33] == 0xA2 
			&& buffer[34] == 0x0A)
			{
				//AUX OFF
				MVH->MVH_TEXT[0] = 'A';
				MVH->MVH_TEXT[1] = 'U';
				MVH->MVH_TEXT[2] = 'X';
				MVH->MVH_TEXT[3] = ' ';
				MVH->MVH_TEXT[4] = 'O';
				MVH->MVH_TEXT[5] = 'F';
				MVH->MVH_TEXT[6] = 'F';
				msg.MsgId = WM_UPDATE_MVH;
			}
			if(buffer[31] == 0x90 && buffer[32] == 0x5E && buffer[33] == 0x00 
			&& buffer[34] == 0x70 && buffer[35] == 0xA2)
			{
				//AUX ON
				MVH->MVH_TEXT[0] = 'A';
				MVH->MVH_TEXT[1] = 'U';
				MVH->MVH_TEXT[2] = 'X';
				MVH->MVH_TEXT[3] = ' ';
				MVH->MVH_TEXT[4] = 'O';
				MVH->MVH_TEXT[5] = 'N';
				msg.MsgId = WM_UPDATE_MVH;
			}
		}
		if(buffer[4] == 0x50 && buffer[5] == 0x9A && buffer[6] == 0x54 && buffer[7] == 0x0E 
			&& buffer[11] == 0x02 && buffer[12] == 0xBA && buffer[13] == 0x51 && buffer[14] == 0xD0 
			&& buffer[16] == 0xA9 && buffer[17] == 0x05 && buffer[21] == 0xAA && buffer[22] == 0x20 
			&& buffer[23] == 0xAA && buffer[24] == 0x20 && buffer[36] == 0x02)
		{
			//DEMO OFF >
			MVH->MVH_TEXT[0] = 'D';
			MVH->MVH_TEXT[1] = 'E';
			MVH->MVH_TEXT[2] = 'M';
			MVH->MVH_TEXT[3] = 'O';
			MVH->MVH_TEXT[4] = ' ';
			MVH->MVH_TEXT[5] = 'O';
			MVH->MVH_TEXT[6] = 'F';
			MVH->MVH_TEXT[7] = 'F';
			MVH->MVH_TEXT[8] = '>';
			msg.MsgId = WM_UPDATE_MVH;
		}
		if(buffer[6] == 0x12 && buffer[7] == 0x94 && buffer[11] == 0x02 
			&& buffer[12] == 0xBA && buffer[13] == 0x05 && buffer[14] == 0x04)
		{			
			//YES
			MVH->MVH_TEXT[0] = 'Y';
			MVH->MVH_TEXT[1] = 'E';
			MVH->MVH_TEXT[2] = 'S';
			msg.MsgId = WM_UPDATE_MVH;
		}
		if(buffer[6] == 0x52 && buffer[7] == 0xAA && buffer[11] == 0x00 
			&& buffer[12] == 0x1A && buffer[13] == 0x12 && buffer[14] == 0x94)
		{			
			//SLA >
			MVH->MVH_TEXT[0] = 'S';
			MVH->MVH_TEXT[1] = 'L';
			MVH->MVH_TEXT[2] = 'A';
			MVH->MVH_TEXT[3] = '>';
			msg.MsgId = WM_UPDATE_MVH;
			MVH_States = MVH_SLA;
		}
		if(buffer[2] == 0x62 && buffer[3] == 0xAA && buffer[4] == 0x02 && buffer[5] == 0xBA 
			&& buffer[6] == 0x51 && buffer[7] == 0xD0 && buffer[11] == 0x52 && buffer[12] == 0xAA 
			&& buffer[13] == 0x02 && buffer[14] == 0xAA && buffer[36] == 0x02)
		{
			//FADER >
			MVH->MVH_TEXT[0] = 'F';
			MVH->MVH_TEXT[1] = 'A';
			MVH->MVH_TEXT[2] = 'D';
			MVH->MVH_TEXT[3] = 'E';
			MVH->MVH_TEXT[4] = 'R';
			MVH->MVH_TEXT[5] = '>';
			msg.MsgId = WM_UPDATE_MVH;
		}
		if(buffer[2] == 0x70 && buffer[3] == 0x0E && buffer[4] == 0x52 && buffer[5] == 0xAA 
			&& buffer[6] == 0x00 && buffer[7] == 0x1A && buffer[11] == 0x52 && buffer[12] == 0xAA 
			&& buffer[13] == 0x53 && buffer[14] == 0xD0 && buffer[16] == 0xA9 && buffer[21] == 0xAB 
			&& buffer[22] == 0x20 && buffer[36] == 0x02)
		{
			//BALANCE >
			MVH->MVH_TEXT[0] = 'B';
			MVH->MVH_TEXT[1] = 'A';
			MVH->MVH_TEXT[2] = 'L';
			MVH->MVH_TEXT[3] = 'A';
			MVH->MVH_TEXT[4] = 'N';
			MVH->MVH_TEXT[5] = 'C';
			MVH->MVH_TEXT[6] = 'E';
			MVH->MVH_TEXT[7] = '>';
			msg.MsgId = WM_UPDATE_MVH;
		}		
		if(buffer[2] == 0x02 && buffer[3] == 0xBA && buffer[4] == 0x12 && buffer[5] == 0x94 
			&& buffer[11] == 0x70 && buffer[12] == 0x9A && buffer[13] == 0x02 && buffer[14] == 0xBA 
			&& buffer[16] == 0x0C	&& buffer[17] == 0x10 && buffer[21] == 0x0C && buffer[22] == 0x10 
			&& buffer[23] == 0x0D && buffer[24] == 0x10 && buffer[25] == 0xE0 && buffer[26] == 0x07
			&& buffer[31] == 0x92 && buffer[32] == 0x10		&& buffer[36] == 0x02)
		{
			//EQ SETTING >
			MVH->MVH_TEXT[0] = 'E';
			MVH->MVH_TEXT[1] = 'Q';
			MVH->MVH_TEXT[2] = ' ';
			MVH->MVH_TEXT[3] = 'S';
			MVH->MVH_TEXT[4] = 'E';
			MVH->MVH_TEXT[5] = 'T';
			MVH->MVH_TEXT[6] = 'T';
			MVH->MVH_TEXT[7] = 'I';
			MVH->MVH_TEXT[8] = 'N';
			MVH->MVH_TEXT[9] = 'G';
			MVH->MVH_TEXT[10] = '>';
			msg.MsgId = WM_UPDATE_MVH;
		}		
		if(buffer[2] == 0x70 && buffer[3] == 0x0E && buffer[4] == 0x51 && buffer[5] == 0xD0 
			&& buffer[6] == 0x50 && buffer[7] == 0x1A && buffer[11] == 0x50 && buffer[12] == 0x9A 
			&& buffer[13] == 0x00 && buffer[14] == 0x1A && buffer[16] == 0xAB	&& buffer[17] == 0x20 
			&& buffer[21] == 0x49 && buffer[22] == 0x21 && buffer[23] == 0x49 && buffer[24] == 0x21)
		{
			if(buffer[31] == 0x90 && buffer[32] == 0x5A	&& buffer[33] == 0xA2 && buffer[34] == 0x0A	&& buffer[35] == 0xA2)
			{
				//LOUNDLESS : OFF
				MVH->MVH_TEXT[0] = 'L';
				MVH->MVH_TEXT[1] = 'O';
				MVH->MVH_TEXT[2] = 'U';
				MVH->MVH_TEXT[3] = 'N';
				MVH->MVH_TEXT[4] = 'D';
				MVH->MVH_TEXT[5] = 'L';
				MVH->MVH_TEXT[6] = 'E';
				MVH->MVH_TEXT[7] = 'S';
				MVH->MVH_TEXT[8] = 'S';
				MVH->MVH_TEXT[9] = ':';
				MVH->MVH_TEXT[10] = 'O';
				MVH->MVH_TEXT[11] = 'F';
				MVH->MVH_TEXT[12] = 'F';
				msg.MsgId = WM_UPDATE_MVH;
			}
			if(buffer[31] == 0x10 && buffer[32] == 0x0A	&& buffer[33] == 0x90 && buffer[34] == 0x5B	&& buffer[36] == 0x70)
			{
				//LOUNDLESS : LOW
				MVH->MVH_TEXT[0] = 'L';
				MVH->MVH_TEXT[1] = 'O';
				MVH->MVH_TEXT[2] = 'U';
				MVH->MVH_TEXT[3] = 'N';
				MVH->MVH_TEXT[4] = 'D';
				MVH->MVH_TEXT[5] = 'L';
				MVH->MVH_TEXT[6] = 'E';
				MVH->MVH_TEXT[7] = 'S';
				MVH->MVH_TEXT[8] = 'S';
				MVH->MVH_TEXT[9] = ':';
				MVH->MVH_TEXT[10] = 'L';
				MVH->MVH_TEXT[11] = 'O';
				MVH->MVH_TEXT[12] = 'W';
				msg.MsgId = WM_UPDATE_MVH;
			}
			if(buffer[31] == 0x04 && buffer[32] == 0x50	&& buffer[33] == 0xD1 && buffer[35] == 0xD1	&& buffer[36] == 0x50)
			{
				//LOUNDLESS : MID
				MVH->MVH_TEXT[0] = 'L';
				MVH->MVH_TEXT[1] = 'O';
				MVH->MVH_TEXT[2] = 'U';
				MVH->MVH_TEXT[3] = 'N';
				MVH->MVH_TEXT[4] = 'D';
				MVH->MVH_TEXT[5] = 'L';
				MVH->MVH_TEXT[6] = 'E';
				MVH->MVH_TEXT[7] = 'S';
				MVH->MVH_TEXT[8] = 'S';
				MVH->MVH_TEXT[9] = ':';
				MVH->MVH_TEXT[10] = 'M';
				MVH->MVH_TEXT[11] = 'I';
				MVH->MVH_TEXT[12] = 'D';
				msg.MsgId = WM_UPDATE_MVH;
			}
			if(buffer[31] == 0x00 && buffer[32] == 0x0A	&& buffer[33] == 0x22 && buffer[34] == 0x50	&& buffer[35] == 0xD1)
			{
				//LOUNDLESS : HI
				MVH->MVH_TEXT[0] = 'L';
				MVH->MVH_TEXT[1] = 'O';
				MVH->MVH_TEXT[2] = 'U';
				MVH->MVH_TEXT[3] = 'N';
				MVH->MVH_TEXT[4] = 'D';
				MVH->MVH_TEXT[5] = 'L';
				MVH->MVH_TEXT[6] = 'E';
				MVH->MVH_TEXT[7] = 'S';
				MVH->MVH_TEXT[8] = 'S';
				MVH->MVH_TEXT[9] = ':';
				MVH->MVH_TEXT[10] = 'H';
				MVH->MVH_TEXT[11] = 'I';
				msg.MsgId = WM_UPDATE_MVH;
			}
		}
		if(buffer[4] == 0x12 && buffer[5] == 0x94 && buffer[6] == 0x12 && buffer[7] == 0x94 
			&& buffer[11] == 0x52 && buffer[12] == 0xAA && buffer[13] == 0x53 && buffer[14] == 0xD0 
			&& buffer[16] == 0x0D	&& buffer[17] == 0x35 && buffer[21] == 0xA9 && buffer[22] == 0x05 
			&& buffer[23] == 0xA9 && buffer[24] == 0x05 && buffer[25] == 0x49 && buffer[26] == 0x21
			&& buffer[31] == 0xC1 && buffer[36] == 0x02)
		{
			//BASS BOOST >
			MVH->MVH_TEXT[0] = 'B';
			MVH->MVH_TEXT[1] = 'A';
			MVH->MVH_TEXT[2] = 'S';
			MVH->MVH_TEXT[3] = 'S';
			MVH->MVH_TEXT[4] = ' ';
			MVH->MVH_TEXT[5] = 'B';
			MVH->MVH_TEXT[6] = 'O';
			MVH->MVH_TEXT[7] = 'O';
			MVH->MVH_TEXT[8] = 'S';
			MVH->MVH_TEXT[9] = 'T';
			MVH->MVH_TEXT[10] = '>';
			msg.MsgId = WM_UPDATE_MVH;
			MVH_States = MVH_BASS_BOOST;
		}	
		if(buffer[2] == 0x12 && buffer[3] == 0x94 && buffer[6] == 0x02 && buffer[7] == 0xAA 
			&& buffer[11] == 0x42 && buffer[12] == 0xAA && buffer[13] == 0x52 && buffer[14] == 0x2A 
			&& buffer[16] == 0xAB	&& buffer[17] == 0x20 && buffer[21] == 0x0C && buffer[22] == 0x10 
			&& buffer[23] == 0x0C && buffer[24] == 0x10 && buffer[25] == 0x0D && buffer[26] == 0x10
			&& buffer[32] == 0x7A && buffer[33] == 0x92 && buffer[34] == 0x10  && buffer[36] == 0x02)
		{
			//HPF SETTING >
			MVH->MVH_TEXT[0] = 'H';
			MVH->MVH_TEXT[1] = 'P';
			MVH->MVH_TEXT[2] = 'F';
			MVH->MVH_TEXT[3] = ' ';
			MVH->MVH_TEXT[4] = 'S';
			MVH->MVH_TEXT[5] = 'E';
			MVH->MVH_TEXT[6] = 'T';
			MVH->MVH_TEXT[7] = 'T';
			MVH->MVH_TEXT[8] = 'I';
			MVH->MVH_TEXT[9] = 'N';
			MVH->MVH_TEXT[10] = 'G';
			MVH->MVH_TEXT[11] = '>';
			msg.MsgId = WM_UPDATE_MVH;
		}
		if(buffer[2] == 0x02 && buffer[3] == 0xBA && buffer[4] == 0x01 && buffer[5] == 0xC0 
			&& buffer[6] == 0x70 && buffer[7] == 0x0E && buffer[11] == 0x02 && buffer[12] == 0xBA 
			&& buffer[13] == 0x00	&& buffer[14] == 0x9A && buffer[15] == 0x00 && buffer[16] == 0xAA 
			&& buffer[17] == 0x26)
		{
			// 	CENTER :00
			MVH->MVH_TEXT[0] = 'C';
			MVH->MVH_TEXT[1] = 'E';
			MVH->MVH_TEXT[2] = 'N';
			MVH->MVH_TEXT[3] = 'T';
			MVH->MVH_TEXT[4] = 'E';
			MVH->MVH_TEXT[5] = 'R';
			MVH->MVH_TEXT[6] = ':';
			MVH->MVH_TEXT[7] = '0';
			MVH->MVH_TEXT[8] = '0';
			msg.MsgId = WM_UPDATE_MVH;
			MVH_States = MVH_CENTER;
		}
		if(buffer[2] == 0x01 && buffer[3] == 0xC0 && buffer[4] == 0x70 && buffer[5] == 0x0E 
			&& buffer[6] == 0x50 && buffer[7] == 0x9A && buffer[11] == 0x62 && buffer[12] == 0xAA 
			&& buffer[13] == 0x02	&& buffer[14] == 0xAA && buffer[31] == 0x63)
		{			
			// FRONT
			MVH_States = MVH_FRONT;
			for(uint8_t i = 0; i<3; i++)
			{
				Number[i] = buffer[i+34];
			}			
			sprintf((char *)(MVH->MVH_TEXT), "FRONT +%d",getNumber(Number));
			msg.MsgId = WM_UPDATE_MVH;			
		}		
		
		if(buffer[4] == 0x62 && buffer[5] == 0xAA	&& buffer[6] == 0x52 && buffer[7] == 0xAA
			&& buffer[11] == 0x02 && buffer[12] == 0xBA && buffer[13] == 0x62 && buffer[14] == 0xAA 
			&& buffer[31] == 0x63)
		{
			//REAR
			MVH_States = MVH_REAR;
			for(uint8_t i = 0; i<3; i++)
			{
				Number[i] = buffer[i+34];
			}			
			sprintf((char *)(MVH->MVH_TEXT), "REAR +%d",getNumber(Number));
			msg.MsgId = WM_UPDATE_MVH;
		}		
		if(buffer[4] == 0x01 && buffer[5] == 0xC0	&& buffer[6] == 0x02 && buffer[7] == 0xAA
			&& buffer[11] == 0x02 && buffer[12] == 0xBA && buffer[13] == 0x00 && buffer[14] == 0x1A 
			&& buffer[31] == 0x63)
		{
			//LEFT
			MVH_States = MVH_LEFT;
			for(uint8_t i = 0; i<3; i++)
			{
				Number[i] = buffer[i+34];
			}			
			sprintf((char *)(MVH->MVH_TEXT), "LEFT +%d",getNumber(Number));
			msg.MsgId = WM_UPDATE_MVH;
		}		
		if(buffer[2] == 0x01 && buffer[3] == 0xC0 && buffer[4] == 0x52 && buffer[5] == 0x2A 
			&& buffer[6] == 0x12 && buffer[7] == 0x9A && buffer[11] == 0x01 && buffer[12] == 0xD0 
			&& buffer[13] == 0x62	&& buffer[14] == 0xAA && buffer[31] == 0x63)
		{
			//RIGHT
			MVH_States = MVH_RIGHT;
			for(uint8_t i = 0; i<3; i++)
			{
				Number[i] = buffer[i+34];
			}			
			sprintf((char *)(MVH->MVH_TEXT), "RIGHT +%d",getNumber(Number));
			msg.MsgId = WM_UPDATE_MVH;
		}
		
		if(buffer[2] == 0x02 && buffer[3] == 0xBA && buffer[4] == 0x00 && buffer[5] == 0x9A 
			&& buffer[6] == 0x70 && buffer[7] == 0x0E && buffer[11] == 0x52 && buffer[12] == 0xAA 
			&& buffer[13] == 0x00 && buffer[14] == 0x9A && buffer[15] == 0x00 && buffer[16] == 0xA1)
		{
			//CANCEL
			MVH->MVH_TEXT[0] = 'C';
			MVH->MVH_TEXT[1] = 'A';
			MVH->MVH_TEXT[2] = 'N';
			MVH->MVH_TEXT[3] = 'C';
			MVH->MVH_TEXT[4] = 'E';
			MVH->MVH_TEXT[5] = 'L';
			msg.MsgId = WM_UPDATE_MVH;
		}
		if(buffer[2] == 0x24 && buffer[3] == 0x2A && buffer[4] == 0x00 && buffer[5] == 0x9A 
			&& buffer[6] == 0x50 && buffer[7] == 0x9A && buffer[11] == 0x00 && buffer[12] == 0x1A 
			&& buffer[13] == 0x00 && buffer[14] == 0x9A && buffer[21] == 0x49 && buffer[22] == 0x21
			&& buffer[23] == 0xAB && buffer[24] == 0x20 && buffer[25] == 0x0C && buffer[26] == 0x10 && buffer[36] == 0x02)
		{
			//CLOCK SET >
			MVH->MVH_TEXT[0] = 'C';
			MVH->MVH_TEXT[1] = 'L';
			MVH->MVH_TEXT[2] = 'O';
			MVH->MVH_TEXT[3] = 'C';
			MVH->MVH_TEXT[4] = 'K';
			MVH->MVH_TEXT[5] = ' ';
			MVH->MVH_TEXT[6] = 'S';
			MVH->MVH_TEXT[7] = 'E';
			MVH->MVH_TEXT[8] = 'T';
			MVH->MVH_TEXT[9] = '>';
			msg.MsgId = WM_UPDATE_MVH;
		}
		if(buffer[2] == 0x42 && buffer[3] == 0xB2 && buffer[4] == 0x00 && buffer[5] == 0x41 
			&& buffer[6] == 0x52 && buffer[7] == 0x2A && buffer[11] == 0x42 && buffer[12] == 0xB2 
			&& buffer[13] == 0x50 && buffer[14] == 0x00 && buffer[15] == 0x00 && buffer[16] == 0x82 
			&& buffer[17] == 0x25 && buffer[21] == 0xA2 && buffer[22] == 0x25)
		{		
			if(buffer[32] == 0x52 && buffer[33] == 0xB2 && buffer[34] == 0x4A 
					&& buffer[35] == 0x22 && buffer[36] == 0x50)
			{
			//12H/24H : 12H >
				MVH->MVH_TEXT[0] = 'T';
				MVH->MVH_TEXT[1] = 'I';
				MVH->MVH_TEXT[2] = 'M';
				MVH->MVH_TEXT[3] = 'E';
				MVH->MVH_TEXT[4] = ' ';
				MVH->MVH_TEXT[5] = '1';
				MVH->MVH_TEXT[6] = '2';
				MVH->MVH_TEXT[7] = 'H';
				msg.MsgId = WM_UPDATE_MVH;
			}
			if(buffer[31] == 0xB2 && buffer[32] == 0x48 && buffer[33] == 0x22 && buffer[34] == 0x5A 
					&& buffer[35] == 0x22 && buffer[36] == 0x50)
			{
			//12H/24H : 24H >
				MVH->MVH_TEXT[0] = 'T';
				MVH->MVH_TEXT[1] = 'I';
				MVH->MVH_TEXT[2] = 'M';
				MVH->MVH_TEXT[3] = 'E';
				MVH->MVH_TEXT[4] = ' ';
				MVH->MVH_TEXT[5] = '2';
				MVH->MVH_TEXT[6] = '4';
				MVH->MVH_TEXT[7] = 'H';
				msg.MsgId = WM_UPDATE_MVH;
			}
		}		
		if(buffer[2] == 0x52 && buffer[3] == 0xAA && buffer[4] == 0x00 && buffer[5] == 0x00 
			&& buffer[6] == 0x53 && buffer[7] == 0xD0 && buffer[11] == 0x12 && buffer[12] == 0x94 
			&& buffer[13] == 0x50 && buffer[14] == 0x1A && buffer[16] == 0xA1 && buffer[17] == 0x05	
			&& buffer[21] == 0x0C && buffer[22] == 0x10 && buffer[23] == 0xA9 && buffer[24] == 0x05 
			&& buffer[31] == 0x90)
		{		if(buffer[32] == 0x5E && buffer[33] == 0x00 && buffer[34] == 0x70 && buffer[35] == 0x00)
				{
					HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
					//USB AUTO : ON
					MVH->MVH_TEXT[0] = 'U';
					MVH->MVH_TEXT[1] = 'S';
					MVH->MVH_TEXT[2] = 'B';
					MVH->MVH_TEXT[3] = ' ';
					MVH->MVH_TEXT[4] = 'A';
					MVH->MVH_TEXT[5] = 'U';
					MVH->MVH_TEXT[6] = 'T';
					MVH->MVH_TEXT[7] = 'O';
					MVH->MVH_TEXT[8] = ':';
					MVH->MVH_TEXT[9] = 'O';
					MVH->MVH_TEXT[10] = 'N';
					msg.MsgId = WM_UPDATE_MVH;
				}
				if(buffer[32] == 0x5A && buffer[33] == 0xA2 && buffer[34] == 0x0A && buffer[35] == 0xA2)
				{
					HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
					//USB AUTO : OFF
					MVH->MVH_TEXT[0] = 'U';
					MVH->MVH_TEXT[1] = 'S';
					MVH->MVH_TEXT[2] = 'B';
					MVH->MVH_TEXT[3] = ' ';
					MVH->MVH_TEXT[4] = 'A';
					MVH->MVH_TEXT[5] = 'U';
					MVH->MVH_TEXT[6] = 'T';
					MVH->MVH_TEXT[7] = 'O';
					MVH->MVH_TEXT[8] = ':';
					MVH->MVH_TEXT[9] = 'O';
					MVH->MVH_TEXT[10] = 'F';
					MVH->MVH_TEXT[11] = 'F';
					msg.MsgId = WM_UPDATE_MVH;
				}
		}
		if(buffer[2] == 0x02 && buffer[3] == 0xBA && buffer[4] == 0x01 && buffer[5] == 0xC0 
			&& buffer[6] == 0x12 && buffer[7] == 0x94 && buffer[11] == 0x05 && buffer[12] == 0x04 
			&& buffer[13] == 0x12 && buffer[14] == 0x94 && buffer[36] == 0x02)
		{
			//SYSTEM >
			MVH->MVH_TEXT[0] = 'S';
			MVH->MVH_TEXT[1] = 'Y';
			MVH->MVH_TEXT[2] = 'S';
			MVH->MVH_TEXT[3] = 'T';
			MVH->MVH_TEXT[4] = 'E';
			MVH->MVH_TEXT[5] = 'M';
			MVH->MVH_TEXT[6] = '>';
			msg.MsgId = WM_UPDATE_MVH;
		}
		if(buffer[2] == 0x01 && buffer[3] == 0xD0 && buffer[4] == 0x01 && buffer[5] == 0xC0 
			&& buffer[6] == 0x01 && buffer[7] == 0xD0 && buffer[11] == 0x70 && buffer[12] == 0x0E 
			&& buffer[13] == 0x01 && buffer[14] == 0xD0 && buffer[36] == 0x02)
		{
			
			//INITIAL >
			MVH->MVH_TEXT[0] = 'I';
			MVH->MVH_TEXT[1] = 'N';
			MVH->MVH_TEXT[2] = 'I';
			MVH->MVH_TEXT[3] = 'T';
			MVH->MVH_TEXT[4] = 'I';
			MVH->MVH_TEXT[5] = 'A';
			MVH->MVH_TEXT[6] = 'L';
			MVH->MVH_TEXT[7] = '>';
			msg.MsgId = WM_UPDATE_MVH;
		}
		if(buffer[2] == 0x50 && buffer[3] == 0x1A && buffer[4] == 0x12 && buffer[5] == 0x9A 
			&& buffer[6] == 0x70 && buffer[7] == 0x0E && buffer[11] == 0x52 && buffer[12] == 0xAA 
			&& buffer[13] == 0x00 && buffer[14] == 0x1A && buffer[36] == 0x10
		&& buffer[21] == 0xA9 && buffer[22] == 0x21 && buffer[23] == 0xAB
		&& buffer[24] == 0x20 && buffer[25] == 0x00 && buffer[26] == 0x08
		&& buffer[31] == 0xB2 && buffer[32] == 0x0E && buffer[33] == 0x00 && buffer[34] == 0x7A && buffer[35] == 0x92)
		{
			
			//LANGUAGE :ENG
			MVH->MVH_TEXT[0] = 'L';
			MVH->MVH_TEXT[1] = 'A';
			MVH->MVH_TEXT[2] = 'N';
			MVH->MVH_TEXT[3] = 'G';
			MVH->MVH_TEXT[4] = 'U';
			MVH->MVH_TEXT[5] = 'A';
			MVH->MVH_TEXT[6] = 'G';
			MVH->MVH_TEXT[7] = 'E';
			MVH->MVH_TEXT[8] = ':';
			MVH->MVH_TEXT[9] = 'E';
			MVH->MVH_TEXT[10] = 'N';
			MVH->MVH_TEXT[11] = 'G';
			msg.MsgId = WM_UPDATE_MVH;
		}
		if(buffer[2] == 0x50 && buffer[3] == 0x9A && buffer[4] == 0x01 && buffer[5] == 0xD0 
			&& buffer[6] == 0x51 && buffer[7] == 0xD0 && buffer[11] == 0x50 && buffer[12] == 0x1A 
			&& buffer[13] == 0x52 && buffer[14] == 0xAA && buffer[36] == 0x02)
		{
			//AUDIO >
			MVH->MVH_TEXT[0] = 'A';
			MVH->MVH_TEXT[1] = 'U';
			MVH->MVH_TEXT[2] = 'D';
			MVH->MVH_TEXT[3] = 'I';
			MVH->MVH_TEXT[4] = 'O';
			MVH->MVH_TEXT[5] = '>';
			msg.MsgId = WM_UPDATE_MVH;

		}
		if(buffer[2] == 0x50 && buffer[3] == 0x1A && buffer[4] == 0x00 && buffer[5] == 0x1A 
			&& buffer[6] == 0x50 && buffer[7] == 0x9A && buffer[11] == 0x04 && buffer[12] == 0x0B)
		{
			//VOLUME >
			MVH->MVH_TEXT[0] = 'V';
			MVH->MVH_TEXT[1] = 'o';
			MVH->MVH_TEXT[2] = 'l';
			MVH->MVH_TEXT[3] = 'u';
			MVH->MVH_TEXT[4] = 'm';
			MVH->MVH_TEXT[5] = 'e';
			MVH->MVH_TEXT[6] = ' ';
			MVH_States = MVH_VOLUME;
			if(buffer[27] == 0xB0)
			{
				MVH->MVH_TEXT[7] = ' ';
				if(buffer[32] == 0x5B && buffer[33] == 0x94 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '0';
				}
				if(buffer[32] == 0x50 && buffer[33] == 0x00 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '1';
				}
				if(buffer[32] == 0x52 && buffer[33] == 0xB2 && buffer[34] == 0x40)
				{
					MVH->MVH_TEXT[8] = '2';
				}
				if(buffer[32] == 0x50 && buffer[33] == 0xB2 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '3';
				}
				if(buffer[32] == 0x58 && buffer[33] == 0x22 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '4';
				}
				if(buffer[32] == 0x58 && buffer[33] == 0xB2 && buffer[34] == 0x10)
				{
					MVH->MVH_TEXT[8] = '5';
				}
				if(buffer[32] == 0x5A && buffer[33] == 0xB2 && buffer[34] == 0x10)
				{
					MVH->MVH_TEXT[8] = '6';
				}
				if(buffer[32] == 0x50 && buffer[33] == 0x80 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '7';
				}
				if(buffer[32] == 0x5A && buffer[33] == 0xB2 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '8';
				}
				if(buffer[32] == 0x58 && buffer[33] == 0xB2 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '9';
				}
			}
			if(buffer[27] == 0x00)
			{
				MVH->MVH_TEXT[7] = '1';
				if(buffer[32] == 0x5B && buffer[33] == 0x94 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '0';
				}
				if(buffer[32] == 0x50 && buffer[33] == 0x00 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '1';
				}
				if(buffer[32] == 0x52 && buffer[33] == 0xB2 && buffer[34] == 0x40)
				{
					MVH->MVH_TEXT[8] = '2';
				}
				if(buffer[32] == 0x50 && buffer[33] == 0xB2 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '3';
				}
				if(buffer[32] == 0x58 && buffer[33] == 0x22 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '4';
				}
				if(buffer[32] == 0x58 && buffer[33] == 0xB2 && buffer[34] == 0x10)
				{
					MVH->MVH_TEXT[8] = '5';
				}
				if(buffer[32] == 0x5A && buffer[33] == 0xB2 && buffer[34] == 0x10)
				{
					MVH->MVH_TEXT[8] = '6';
				}
				if(buffer[32] == 0x50 && buffer[33] == 0x80 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '7';
				}
				if(buffer[32] == 0x5A && buffer[33] == 0xB2 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '8';
				}
				if(buffer[32] == 0x58 && buffer[33] == 0xB2 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '9';
				}
			}
			if(buffer[27] == 0x20 && buffer[31] == 0xB2)
			{
				MVH->MVH_TEXT[7] = '2';
				if(buffer[32] == 0x4B && buffer[33] == 0x94 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '0';
				}
				if(buffer[32] == 0x40 && buffer[33] == 0x00 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '1';
				}
				if(buffer[32] == 0x42 && buffer[33] == 0xB2 && buffer[34] == 0x40)
				{
					MVH->MVH_TEXT[8] = '2';
				}
				if(buffer[32] == 0x40 && buffer[33] == 0xB2 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '3';
				}
				if(buffer[32] == 0x48 && buffer[33] == 0x22 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '4';
				}
				if(buffer[32] == 0x48 && buffer[33] == 0xB2 && buffer[34] == 0x10)
				{
					MVH->MVH_TEXT[8] = '5';
				}
				if(buffer[32] == 0x4A && buffer[33] == 0xB2 && buffer[34] == 0x10)
				{
					MVH->MVH_TEXT[8] = '6';
				}
				if(buffer[32] == 0x40 && buffer[33] == 0x80 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '7';
				}
				if(buffer[32] == 0x4A && buffer[33] == 0xB2 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '8';
				}
				if(buffer[32] == 0x48 && buffer[33] == 0xB2 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '9';
				}
			}
			if(buffer[27] == 0x00 && buffer[31] == 0xB2)
			{
				MVH->MVH_TEXT[7] = '3';
				if(buffer[32] == 0x5B && buffer[33] == 0x94 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '0';
				}
				if(buffer[32] == 0x50 && buffer[33] == 0x00 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '1';
				}
				if(buffer[32] == 0x52 && buffer[33] == 0xB2 && buffer[34] == 0x40)
				{
					MVH->MVH_TEXT[8] = '2';
				}
				if(buffer[32] == 0x50 && buffer[33] == 0xB2 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '3';
				}
				if(buffer[32] == 0x58 && buffer[33] == 0x22 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '4';
				}
				if(buffer[32] == 0x58 && buffer[33] == 0xB2 && buffer[34] == 0x10)
				{
					MVH->MVH_TEXT[8] = '5';
				}
				if(buffer[32] == 0x5A && buffer[33] == 0xB2 && buffer[34] == 0x10)
				{
					MVH->MVH_TEXT[8] = '6';
				}
				if(buffer[32] == 0x50 && buffer[33] == 0x80 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '7';
				}
				if(buffer[32] == 0x5A && buffer[33] == 0xB2 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '8';
				}
				if(buffer[32] == 0x58 && buffer[33] == 0xB2 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '9';
				}
			}
			if(buffer[27] == 0x80 && buffer[31] == 0x22)
			{
				MVH->MVH_TEXT[7] = '4';
				if(buffer[32] == 0x5B && buffer[33] == 0x94 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '0';
				}
				if(buffer[32] == 0x50 && buffer[33] == 0x00 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '1';
				}
				if(buffer[32] == 0x52 && buffer[33] == 0xB2 && buffer[34] == 0x40)
				{
					MVH->MVH_TEXT[8] = '2';
				}
				if(buffer[32] == 0x50 && buffer[33] == 0xB2 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '3';
				}
				if(buffer[32] == 0x58 && buffer[33] == 0x22 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '4';
				}
				if(buffer[32] == 0x58 && buffer[33] == 0xB2 && buffer[34] == 0x10)
				{
					MVH->MVH_TEXT[8] = '5';
				}
				if(buffer[32] == 0x5A && buffer[33] == 0xB2 && buffer[34] == 0x10)
				{
					MVH->MVH_TEXT[8] = '6';
				}
				if(buffer[32] == 0x50 && buffer[33] == 0x80 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '7';
				}
				if(buffer[32] == 0x5A && buffer[33] == 0xB2 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '8';
				}
				if(buffer[32] == 0x58 && buffer[33] == 0xB2 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '9';
				}
			}
			if(buffer[27] == 0x80 && buffer[31] == 0xB2)
			{
				MVH->MVH_TEXT[7] = '5';
				if(buffer[32] == 0x1B && buffer[33] == 0x94 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '0';
				}
				if(buffer[32] == 0x10 && buffer[33] == 0x00 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '1';
				}
				if(buffer[32] == 0x12 && buffer[33] == 0xB2 && buffer[34] == 0x40)
				{
					MVH->MVH_TEXT[8] = '2';
				}
				if(buffer[32] == 0x10 && buffer[33] == 0xB2 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '3';
				}
				if(buffer[32] == 0x18 && buffer[33] == 0x22 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '4';
				}
				if(buffer[32] == 0x18 && buffer[33] == 0xB2 && buffer[34] == 0x10)
				{
					MVH->MVH_TEXT[8] = '5';
				}
				if(buffer[32] == 0x1A && buffer[33] == 0xB2 && buffer[34] == 0x10)
				{
					MVH->MVH_TEXT[8] = '6';
				}
				if(buffer[32] == 0x10 && buffer[33] == 0x80 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '7';
				}
				if(buffer[32] == 0x1A && buffer[33] == 0xB2 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '8';
				}
				if(buffer[32] == 0x18 && buffer[33] == 0xB2 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '9';
				}
			}
			if(buffer[27] == 0xA0 && buffer[31] == 0xB2)
			{
				MVH->MVH_TEXT[7] = '6';
				if(buffer[32] == 0x1B && buffer[33] == 0x94 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '0';
				}
				if(buffer[32] == 0x10 && buffer[33] == 0x00 && buffer[34] == 0x50)
				{
					MVH->MVH_TEXT[8] = '1';
				}
				if(buffer[32] == 0x12 && buffer[33] == 0xB2 && buffer[34] == 0x40)
				{
					MVH->MVH_TEXT[8] = '2';
				}				
			}
			msg.MsgId = WM_UPDATE_MVH;
		}
		
		
	}
	if(MVH_States == MVH_BASS_BOOST)
	{
		for(uint8_t i = 0; i<3; i++)
			{
				Number[i] = buffer[i+32];
			}			
			sprintf((char *)(MVH->MVH_TEXT), "BASS BOOST %d",getNumber(Number));
			MVH_States = MVH_INIT_STATE;
	}
	if(MVH_States == MVH_SLA)
	{
		for(uint8_t i = 0; i<3; i++)
				{
					Number[i] = buffer[i+34];
				}
		if(buffer[33] == 0x22)
		{
			sprintf((char *)(MVH->MVH_TEXT), "SLA -%d",getNumber(Number));
		}
		else
		{
			sprintf((char *)(MVH->MVH_TEXT), "SLA +%d",getNumber(Number));
		}
		MVH_States = MVH_INIT_STATE;
	}			
}

uint8_t getNumber(uint8_t * str)
{
	if(str[0] == 0x0B	&& str[1] == 0x94 && str[2] == 0x50)
		{
			return 0;			
		}
	if(str[0] == 0x00	&& str[1] == 0x00 && str[2] == 0x50)
		{
			return 1;			
		}
			if(str[0] == 0x02	&& str[1] == 0xB2 && str[2] == 0x40)
		{
			return 2;			
		}
			if(str[0] == 0x00	&& str[1] == 0xB2 && str[2] == 0x50)
		{
			return 3;
		}
			if(str[0] == 0x08 && str[1] == 0x22 && str[2] == 0x50)
		{
			return 4;
		}
			if(str[0] == 0x08 && str[1] == 0xB2 && str[2] == 0x10)
		{
			return 5;
		}
			if(str[0] == 0x0A && str[1] == 0xB2 && str[2] == 0x10)
		{
			return 6;
		}
			if(str[0] == 0x00 && str[1] == 0x80 && str[2] == 0x50)
		{
			return 7;
		}
			if(str[0] == 0x0A && str[1] == 0xB2 && str[2] == 0x50)
		{
			return 8;
		}
			if(str[0] == 0x08 && str[1] == 0xB2 && str[2] == 0x50)
		{
			return 9;
		}
			if(str[0] == 0x5B && str[1] == 0x94 && str[2] == 0x50)
		{
			return 10;
		}
			if(str[0] == 0x50 && str[1] == 0x00 && str[2] == 0x50)
		{
			return 11;
		}
			if(str[0] == 0x52 && str[1] == 0xB2 && str[2] == 0x40)
		{
			return 12;
		}
			if(str[0] == 0x50	&& str[1] == 0xB2 && str[2] == 0x50)
		{
			return 13;
		}
			if(str[0] == 0x58 && str[1] == 0x22 && str[2] == 0x50)
		{
			return 14;
		}
			if(str[0] == 0x58 && str[1] == 0xB2 && str[2] == 0x10)
		{
			return 15;
		}
}

void MVH_OFF(void)
{
	uint8_t txBuffer[1];	
	//SRC
	HAL_GPIO_WritePin(K1_CS_GPIO_Port, K1_CS_Pin, GPIO_PIN_RESET);
	txBuffer[0] = 0x11;
	HAL_SPI_Transmit(&hspi1, (uint8_t *)txBuffer, 1, 100);
	txBuffer[0] = 0x12; //0.55V
	HAL_SPI_Transmit(&hspi1, (uint8_t *)txBuffer, 1, 100);
	HAL_Delay(5000);
	HAL_GPIO_WritePin(K1_CS_GPIO_Port, K1_CS_Pin, GPIO_PIN_SET);
	//disp
	HAL_GPIO_WritePin(K2_CS_GPIO_Port, K2_CS_Pin, GPIO_PIN_RESET);			
	txBuffer[0] = 0x11;
	HAL_SPI_Transmit(&hspi1, (uint8_t *)txBuffer, 1, 100);
	txBuffer[0] = 0xFF; // 2.2V
	HAL_SPI_Transmit(&hspi1, (uint8_t *)txBuffer, 1, 100);
	HAL_Delay(500);
	HAL_GPIO_WritePin(K2_CS_GPIO_Port, K2_CS_Pin, GPIO_PIN_SET);
}

void MVH_ENC(uint8_t turn)
{
	switch(turn)
	{
		case 1:
			HAL_GPIO_WritePin(EN_A_GPIO_Port, EN_A_Pin, GPIO_PIN_SET);
			HAL_Delay(10);
			HAL_GPIO_WritePin(EN_B_GPIO_Port, EN_B_Pin, GPIO_PIN_SET);
			HAL_Delay(10);
			HAL_GPIO_WritePin(EN_A_GPIO_Port, EN_A_Pin, GPIO_PIN_RESET);
//			HAL_Delay(10);
			HAL_GPIO_WritePin(EN_B_GPIO_Port, EN_B_Pin, GPIO_PIN_RESET);
			break;
		case 2:
			HAL_GPIO_WritePin(EN_B_GPIO_Port, EN_B_Pin, GPIO_PIN_SET);
			HAL_Delay(10);
			HAL_GPIO_WritePin(EN_A_GPIO_Port, EN_A_Pin, GPIO_PIN_SET);
			HAL_Delay(10);
			HAL_GPIO_WritePin(EN_B_GPIO_Port, EN_B_Pin, GPIO_PIN_RESET);
//			HAL_Delay(10);
			HAL_GPIO_WritePin(EN_A_GPIO_Port, EN_A_Pin, GPIO_PIN_RESET);		
			break;			
	}
}