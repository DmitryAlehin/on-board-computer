#ifndef OBDII_H
#define OBDII_H


#include "usart.h"
#include "string.h"
#include "ctype.h"
extern uint8_t OBD_BUFFER[DMA_BUFFER_OBD_SIZE];

typedef enum 
{
	NOP = 0,
	CONNECT,
	NO_DATA,
	DISCONNECT,
	ATTP_OK,
	ATDP_OK,
	WAIT_INIT,
	VIN_INIT,
	OBD_INIT,
	WAIT_ATE,
	ATE_OK
}OBD_General_States_Typedef;

typedef enum 
{
	WAIT_DATA = 0,
	WAIT_VOLT,
	VOLTAGE_DATA_COMPLETE,
	VSS_DATA_COMPLETE,
	RPM_DATA_COMPLETE,
	ECT_DATA_COMPLETE,
	IAT_DATA_COMPLETE,
	FUELLVL_DATA_COMPLETE,
	MAP_DATA_COMPLETE,
	SHRTFT_DATA_COMPLETE,
	LONGFT_DATA_COMPLETE,
	COMPLETE_ALL_DATA,
	CALCULATE_END,
	READY_TO_RECEIVE
}OBD_Data_States_Typedef;

typedef enum 
{
	OBD_OK = 0,
	IC_OK,
	PCM_OK,
	WAIT_IC,
	WAIT_PCM
}OBD_Sign_States_Typedef;

typedef struct
{
	uint8_t VIN_NUMBER[26];
	float Voltage;
	uint8_t VSS, RPM_A, RPM_B, ECT, IAT, MAP, FUEL, LONGFT, SHRTFT;	
}CarParameters_Typedef;

typedef struct
{	
	float Voltage, ECT, FUEL, Fuel_consumption, K_MAP, LH_consumption;	
}CarValues_Typedef;


void OBD_Init(void);
void OBD_Update(void);
void OBD_CheckState(uint8_t * buffer, CarParameters_Typedef *car);
int htoi(const char* hex);
int getRawInt(char c);
#endif