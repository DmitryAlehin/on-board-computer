#include "OBDII.h"


extern OBD_General_States_Typedef OBD_General_State;
extern CarParameters_Typedef CarParameters;
extern OBD_Sign_States_Typedef OBD_Sign_State;
extern OBD_Data_States_Typedef OBD_Data_State;
extern OBD_Errors_State_Typedef OBD_Errors_State;

void OBD_Init(void)
{
	switch(OBD_General_State)
			{
				/* старт инициализации*/				
				case NOP:
					HAL_Delay(4000);
					OBD_General_State = WAIT_INIT;
					HAL_UART_Transmit(&huart1, "atws\r\n", 7, 100);
					
					
					break;
				/* если устройство отвечает и соединение установлено*/
				case CONNECT:
//					HAL_Delay(500);
				OBD_General_State = WAIT_INIT;
					HAL_UART_Transmit(&huart1, "attp1\r\n", 8, 100);
				
					
					break;
				/* отстуствие данных, отправка команды для проверки подключения*/
				case NO_DATA:
					HAL_Delay(1000);
				OBD_General_State = WAIT_INIT;
					HAL_UART_Transmit(&huart1, "atz\r\n", 8, 100);
//					OBD_General_State = WAIT_INIT;
					break;
				/* удалить*/
				case DISCONNECT:
//					HAL_Delay(500);
				HAL_Delay(100);
				OBD_General_State = WAIT_INIT;
					HAL_UART_Transmit(&huart1, "ati\r\n", 6, 100);
					break;
				/* протокол применен, отправка команды для получения текущего протокола*/
				case ATTP_OK:
//					HAL_Delay(500);
				HAL_Delay(100);
				OBD_General_State = WAIT_INIT;
					HAL_UART_Transmit(&huart1, "atdp\r\n", 7, 100);
					break;
				/* протокол настроен правильно, отправка команды для получения VIN номера авто*/
				case ATDP_OK:	
//					HAL_Delay(50);
					HAL_Delay(100);
					OBD_General_State = WAIT_ATE;
					HAL_UART_Transmit(&huart1, "ate0\r\n", 7, 100);
					
					break;
				case ATE_OK:
//					HAL_Delay(500);
					HAL_Delay(500);
//					OBD_General_State = WAIT_INIT;
					if(OBD_Errors_State == OBD_ERRORS_WAIT_VIN)
					{
						HAL_UART_Transmit(&huart1, "0902\r\n", 7, 100);
					}
					OBD_Data_State = READY_TO_RECEIVE;
					OBD_General_State = OBD_INIT;
					break;
				/* ожидание - ничего не делать*/
				case WAIT_INIT:
					__NOP();
					break;
				/* VIN номер получен - устройство инициализировано, данные занесены в соотв. сруктуру данных*/ 
				case VIN_INIT:
					OBD_Errors_State = START_READ_ERRORS;
//					OBD_Data_State = READY_TO_RECEIVE;
					OBD_General_State = OBD_INIT;					
					break;
				/* функция ничего не делает после инициализации устройства*/
				case OBD_INIT:
					break;
				case WAIT_ATE:
					break;
			}
	
}

void OBD_Update(void)
{
	switch(OBD_Data_State)
	{
		/* ожидание получения данных - ничего не делать*/
		case WAIT_DATA:
			__NOP();			
			break;
		/* готов к получению данных - устройство верно инициализировано, отправляется команда для получения напряжения*/
		case READY_TO_RECEIVE:
			HAL_Delay(100);
			OBD_Data_State = WAIT_VOLT;
			HAL_UART_Transmit(&huart1, "atrv\r\n", 8, 100);
			
			break;
		/* получено напряжение, отправка команды для получения скорости*/
		case VOLTAGE_DATA_COMPLETE:
//			HAL_Delay(100);
			OBD_Data_State = WAIT_DATA;
			if(OBD_Sign_State == PCM_OK) //проверка текущего заголовка
			{
				HAL_UART_Transmit(&huart1, "22000d1\r\n", 10, 100); // отправка команды для получения скорости
				
			}
			else
			{
				OBD_Sign_State = WAIT_PCM;
				HAL_UART_Transmit(&huart1, "atshc410f5\r\n", 13, 100); // отправка команды для применения заголовка для работы с PCM
				
				
			}
			
			break;
			/* получено значение скорости, отправка команды для получения оборотов*/
		case VSS_DATA_COMPLETE:
//			HAL_Delay(100);
//		HAL_Delay(100);
			OBD_Data_State = WAIT_DATA;
			if(OBD_Sign_State == PCM_OK)
			{
				HAL_UART_Transmit(&huart1, "22000c1\r\n", 10, 100); // отправка команды для получения оборотов
			}
			else
			{
				OBD_Sign_State = WAIT_PCM;
				HAL_UART_Transmit(&huart1, "atshc410f5\r\n", 13, 100);
				
			}
			
			break;
			/* получено значение оборотов, отправка команды для получения температуры охлаждающей жидкости*/
		case RPM_DATA_COMPLETE:
//			HAL_Delay(100);
//		HAL_Delay(100);
			OBD_Data_State = WAIT_DATA;
			if(OBD_Sign_State == PCM_OK)
			{
				HAL_UART_Transmit(&huart1, "2200051\r\n", 10, 100); // отправка команды для получения температуры охлаждающей жидкости
			}
			else
			{
				OBD_Sign_State = WAIT_PCM;
				HAL_UART_Transmit(&huart1, "atshc410f5\r\n", 13, 100);
				
			}		
			break;
			/* получено значение температуры ОЖ, отправка команды для получения температуры на впуске*/
		case ECT_DATA_COMPLETE:
//			HAL_Delay(100);
//		HAL_Delay(100);
			OBD_Data_State = WAIT_DATA;
			if(OBD_Sign_State == PCM_OK)
			{
				HAL_UART_Transmit(&huart1, "22000f1\r\n", 10, 100); //отправка команды для получения температуры на впуске				
			}
			else
			{
				OBD_Sign_State = WAIT_PCM;
				HAL_UART_Transmit(&huart1, "atshc410f5\r\n", 13, 100);
				
			}
			break;
			/* получено значение температуры на впуске, отправка команды для получения давления на впуске */
		case IAT_DATA_COMPLETE:
//			HAL_Delay(100);
//		HAL_Delay(100);
			OBD_Data_State = WAIT_DATA;
			if(OBD_Sign_State == PCM_OK)
			{
				HAL_UART_Transmit(&huart1, "22000b1\r\n", 10, 100); //отправка команды для получения давления на впуске
			}
			else
			{
				OBD_Sign_State = WAIT_PCM;
				HAL_UART_Transmit(&huart1, "atshc410f5\r\n", 13, 100);
				
			}
			break;
			/* получено значение давления на впуске, отправка команды для получения кратковременной подстройки топлива*/
		case MAP_DATA_COMPLETE:
//			HAL_Delay(100);
//		HAL_Delay(100);
			OBD_Data_State = WAIT_DATA;
			if(OBD_Sign_State == PCM_OK)
			{
				HAL_UART_Transmit(&huart1, "2200061\r\n", 10, 100); //отправка команды для получения кратковременной подстройки топлива
			}
			else
			{
				OBD_Sign_State = WAIT_PCM;
				HAL_UART_Transmit(&huart1, "atshc410f5\r\n", 13, 100);
				
			}
			break;
			/* получено значение кратковременной подстройки топливаб отправка команды для получения долговременной подстройки топлива*/
		case SHRTFT_DATA_COMPLETE:
//			HAL_Delay(100);
//		HAL_Delay(100);
			OBD_Data_State = WAIT_DATA;
			if(OBD_Sign_State == PCM_OK)
			{
				HAL_UART_Transmit(&huart1, "2200071\r\n", 10, 100); //отправка команды для получения долговременной подстройки топлива
			}
			else
			{
				OBD_Sign_State = WAIT_PCM;
				HAL_UART_Transmit(&huart1, "atshc410f5\r\n", 13, 100);
				
			}
			break;
			/* получено значение кратковременной подстройки топлива, отправка команды для получения значения уровня топлива*/
		case LONGFT_DATA_COMPLETE:
//			HAL_Delay(100);
//		HAL_Delay(100);
			OBD_Data_State = WAIT_DATA;
			if(OBD_Sign_State == IC_OK) //проверка текущего заголовка
			{
				HAL_UART_Transmit(&huart1, "2261851\r\n", 10, 100); //отправка команды для получения значения уровня топлива
			}
			else
			{
				OBD_Sign_State = WAIT_IC;
				HAL_UART_Transmit(&huart1, "atshc460f5\r\n", 13, 100); // отправка команды для применения заголовка для работы с IC
				
			}			
			break;
			/* получено значение уровня топлива*/
		case FUELLVL_DATA_COMPLETE:
			
			OBD_Data_State = COMPLETE_ALL_DATA; // все данные получены
			break;
		/* все данные получены - функция ничего не делает */
		case COMPLETE_ALL_DATA:			
			__NOP();
			break;	
		case CALCULATE_END:			
			__NOP();
			break;
		case WAIT_VOLT:			
			__NOP();
			break;		
	}
}

/** функция запущена в задаче парсинга данных, получает ответы и сырые данные от сканера 
**для последующей передачи в задачу обработки данных авто
**/
void OBD_CheckState(uint8_t * buffer, CarParameters_Typedef *car)
{
	uint8_t A[3];
	uint8_t B[6];
	uint8_t PIECE1[2] = {0};
	uint8_t PIECE2[2] = {0};
	uint8_t PIECE3[2] = {0};
	uint8_t PIECE4[2] = {0};	
	uint8_t COMPLETE_VIN[26] = {0};
	uint8_t VIN[5][5];	
	unsigned int number;
	float Voltage;
	/* Ответ от сканера после перезагрузки и включения*/ 
	if(strncmp((char *)buffer,"\r\rELM327 v1.5\r\r>", 65) == 0)
	{					
		OBD_General_State = CONNECT;
		// если произойдет перезагрузка устройства, данный флаг позволит правильно инициализировать протокол
		OBD_Sign_State = OBD_OK; 
	}
	if(strncmp((char *)buffer,"ELM327 v1.5\r\r>", 14) == 0)
	{					
		OBD_General_State = CONNECT;
		// если произойдет перезагрузка устройства, данный флаг позволит правильно инициализировать протокол
		OBD_Sign_State = OBD_OK; 
	}
	if(strncmp((char *)buffer,"?\r\r>", 4) == 0)
	{		
		OBD_General_State = CONNECT;
		// если произойдет перезагрузка устройства, данный флаг позволит правильно инициализировать протокол
		OBD_Sign_State = OBD_OK; 
	}
	if(strncmp((char *)buffer,"STOPPED\r\r>", 10) == 0)
	{		
		OBD_General_State = NO_DATA;
		// если произойдет перезагрузка устройства, данный флаг позволит правильно инициализировать протокол
		OBD_Sign_State = OBD_OK; 
	}
	/* ответ от сканера при применении настроек*/
	if(strncmp((char *)buffer,"OK\r\r>", 5) == 0)
	{	
		switch(OBD_Sign_State)
		{
			case WAIT_IC:
				OBD_Sign_State = IC_OK;
				OBD_Data_State = LONGFT_DATA_COMPLETE;
				break;
			case WAIT_PCM:
				OBD_Sign_State = PCM_OK;
				OBD_Data_State = VOLTAGE_DATA_COMPLETE;
				if(OBD_Errors_State == START_READ_ERRORS)
				{
					OBD_Errors_State = READ_OBD_ERRORS;
				}
				break;
			case OBD_OK:
				if(OBD_General_State == WAIT_ATE)
				{
					OBD_General_State = ATE_OK;		
				}
				else
				{
					OBD_General_State = ATTP_OK;
				}
				break;
		}
//		if(OBD_Sign_State == WAIT_IC) //если ожидаем включение заголовка IC
//		{
//			OBD_Sign_State = IC_OK;
//			OBD_Data_State = LONGFT_DATA_COMPLETE;
//		}
//		else if(OBD_Sign_State == WAIT_PCM) //если ожидаем включение заголовка PCM
//		{
//			OBD_Sign_State = PCM_OK;
//			OBD_Data_State = VOLTAGE_DATA_COMPLETE;
//		}
//		else if((OBD_Sign_State == OBD_OK) && (OBD_General_State == WAIT_INIT)) //вхождение при инициализации
//		{
//			OBD_General_State = ATTP_OK;		
//		}
//		else if((OBD_Sign_State == OBD_OK) && (OBD_General_State == WAIT_ATE)) 
//		{
//			OBD_General_State = ATE_OK;		
//		}				
	}
	/* ответ от сканера при применении протокола */
	if(strncmp((char *)buffer,"SAE J1850 PWM\r\r>", 16) == 0)
	{				
		OBD_General_State = ATDP_OK;				
	}		
	/** ответ от сканера, когда данные не были получены:
	**глюк
	**неправильная инициализация
	**/
	if(strncmp((char *)buffer,"NO DATA\r\r>", 10) == 0)
	{
		OBD_General_State = NO_DATA;
	}
	
	/* удалить */
	if(strcmp((char *)buffer,"0902 SEARCHING... UNABLE TO CONNECT >") == 0)
	{
		OBD_General_State = DISCONNECT;
	}
	/* получение вин номера */
	if( buffer[0] == '4' &&	buffer[1] == '9' &&	buffer[2] == ' ' && buffer[3] == '0' &&	buffer[4] == '2')
	{
		for(uint8_t i = 0; i < 14; i++)
		{
			COMPLETE_VIN[i] = buffer[i+7];
		}
		if(sscanf((char *)COMPLETE_VIN, "%d %s %s %s %s", &number, PIECE1, PIECE2, PIECE3, PIECE4) == 5)
		{	
			sprintf((char *)VIN[number - 1], "%c%c%c%c", htoi((char *)PIECE1), htoi((char *)PIECE2), htoi((char *)PIECE3), htoi((char *)PIECE4));
			if(number == 5)
			{
				
				sprintf((char *)car->VIN_NUMBER, "%s%s%s%s%s", VIN[0], VIN[1], VIN[2], VIN[3], VIN[4]);
				OBD_General_State = VIN_INIT;
			}
		}
	}	
	/* получение значения текущего напряжения*/
	if((sscanf((char *)buffer, "%f", &Voltage) == 1) && (OBD_Data_State == WAIT_VOLT))
	{
		car->Voltage = Voltage;
		OBD_Data_State = VOLTAGE_DATA_COMPLETE;
	}
	/* получение значения текущего уровня топлива в процентах*/
	if(buffer[0] == '6' &&	buffer[1] == '2' &&	buffer[2] == ' ' && buffer[3] == '6' &&	buffer[4] == '1')
	{
		for(uint8_t i = 0; i<2; i++)
		{
			A[i] = buffer[i+9];
		}		
			car->FUEL = htoi((char *)A);
			OBD_Data_State = FUELLVL_DATA_COMPLETE;		
	}
	
	/* получение значения температуры ОЖ*/
	if(buffer[0] == '6' &&	buffer[1] == '2' &&	buffer[2] == ' ' && buffer[3] == '0' &&	buffer[4] == '0' &&	buffer[5] == ' ' &&	buffer[6] == '0' &&	buffer[7] == '5')
	{
		for(uint8_t i = 0; i<2; i++)
		{
			A[i] = buffer[i+9];
		}		
			car->ECT = htoi((char *)A);
			OBD_Data_State = ECT_DATA_COMPLETE;		
	}
	
	/* получение значения температуры поступающего воздуха*/
	if(buffer[0] == '6' &&	buffer[1] == '2' &&	buffer[2] == ' ' && buffer[3] == '0' &&	buffer[4] == '0' &&	buffer[5] == ' ' &&	buffer[6] == '0' &&	buffer[7] == 'F')
	{
		for(uint8_t i = 0; i<2; i++)
		{
			A[i] = buffer[i+9];
		}		
			car->IAT = htoi((char *)A);
			OBD_Data_State = IAT_DATA_COMPLETE;		
	}
	
	/* получение значения долговременной подстройки подачи топлива*/
	if(buffer[0] == '6' &&	buffer[1] == '2' &&	buffer[2] == ' ' && buffer[3] == '0' &&	buffer[4] == '0' &&	buffer[5] == ' ' &&	buffer[6] == '0' &&	buffer[7] == '7')
	{
		for(uint8_t i = 0; i<2; i++)
		{
			A[i] = buffer[i+9];
		}		
			car->LONGFT = htoi((char *)A);
			OBD_Data_State = LONGFT_DATA_COMPLETE;		
	}
		
	/* получение значения кратковременной подстройки подачи топлива*/
	if(buffer[0] == '6' &&	buffer[1] == '2' &&	buffer[2] == ' ' && buffer[3] == '0' &&	buffer[4] == '0' &&	buffer[5] == ' ' &&	buffer[6] == '0' &&	buffer[7] == '6')
	{
		for(uint8_t i = 0; i<2; i++)
		{
			A[i] = buffer[i+9];
		}		
			car->SHRTFT = htoi((char *)A);
			OBD_Data_State = SHRTFT_DATA_COMPLETE;		
	}		
		
	/* получение значения скорости*/
	if(buffer[0] == '6' &&	buffer[1] == '2' &&	buffer[2] == ' ' && buffer[3] == '0' &&	buffer[4] == '0' &&	buffer[5] == ' ' &&	buffer[6] == '0' &&	buffer[7] == 'D')
{
		for(uint8_t i = 0; i<2; i++)
		{
			A[i] = buffer[i+9];
		}		
			car->VSS = htoi((char *)A);
			OBD_Data_State = VSS_DATA_COMPLETE;		
	}		
		
	/* получение значения давления на впуске*/
	if(buffer[0] == '6' &&	buffer[1] == '2' &&	buffer[2] == ' ' && buffer[3] == '0' &&	buffer[4] == '0' &&	buffer[5] == ' ' &&	buffer[6] == '0' &&	buffer[7] == 'B')
{
		for(uint8_t i = 0; i<2; i++)
		{
			A[i] = buffer[i+9];
		}		
			car->MAP = htoi((char *)A);
			OBD_Data_State = MAP_DATA_COMPLETE;		
	}		
		
	/* получение значения оборотов*/
	if(buffer[0] == '6' &&	buffer[1] == '2' &&	buffer[2] == ' ' && buffer[3] == '0' &&	buffer[4] == '0' &&	buffer[5] == ' ' &&	buffer[6] == '0' &&	buffer[7] == 'C')
		{
		for(uint8_t i = 0; i<5; i++)
		{
			B[i] = buffer[i+9];
		}	
			if(sscanf((char *)B, "%s %s", PIECE1, PIECE2) == 2)
		{
			car->RPM_A = htoi((char *)PIECE1);
			car->RPM_B = htoi((char *)PIECE2);
			OBD_Data_State = RPM_DATA_COMPLETE;
		}					
	}	
	if(buffer[0] == '6' &&	buffer[1] == '2' &&	buffer[2] == ' ' && buffer[3] == '0' &&	buffer[4] == '2' &&	buffer[5] == ' ' &&	buffer[6] == '0' &&	buffer[7] == '0')
	{
		for(uint8_t i = 0; i < 2; i++)
		{
			PIECE1[i] = buffer[i+9];
		}
		car->NumberOfErrors = htoi((char *)PIECE1);
		OBD_Errors_State = READ_OBD_ERRORS;
		msg.MsgId = WM_UPDATE_OBD_ERRORS;
	}
	
//	 for(uint8_t i = 0; i < DMA_BUFFER_OBD_SIZE; i++)
//	 {
//		buffer[i] = 0;
//	 }
	
}

void OBDReadErrors(void)
{
	switch(OBD_Errors_State)
	{
		case START_READ_ERRORS:
			OBD_Errors_State = WAIT_ERROR;
			if(OBD_Sign_State == PCM_OK) //проверка текущего заголовка
			{
				HAL_UART_Transmit(&huart1, "2202001\r\n", 10, 100); // отправка команды для получения количества ошибок				
			}
			else
			{
				OBD_Sign_State = WAIT_PCM;
				HAL_UART_Transmit(&huart1, "atshc410f5\r\n", 13, 100); // отправка команды для применения заголовка для работы с PCM
			}
			break;
		case READ_OBD_ERRORS:
			OBD_Errors_State = WAIT_ERROR;
			if(OBD_Sign_State == PCM_OK) //проверка текущего заголовка
			{
				HAL_UART_Transmit(&huart1, "13\r\n", 10, 100); // отправка команды для получения номеров ошибок			
			}
			else
			{
				OBD_Sign_State = WAIT_PCM;
				HAL_UART_Transmit(&huart1, "atshc410f5\r\n", 13, 100); // отправка команды для применения заголовка для работы с PCM
			}
			break;
		case CLEAR_OBD_ERRORS:
			OBD_Errors_State = WAIT_ERROR;
			HAL_UART_Transmit(&huart1, "04\r\n", 5, 100); // отправка команды для удаления номеров ошибок
			break;
		case WAIT_ERROR:
			break;
	}
}
	
int htoi(const char* hex)
{
	const int LEN = strlen(hex) - 1;
	int power = 1;
	int dec = 0;
	for(int i=LEN; i>=0; i--)
	{		
		dec += getRawInt(hex[i]) * power;
		power *= 16;
		
	}
	return dec;
	
}

int getRawInt(char c)
{
	if(isalpha(c))
	{
		return toupper(c) - 'A' + 10;
	}
	return c - '0';
}

