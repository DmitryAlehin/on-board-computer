#ifndef OBDII_H
#define OBDII_H


#include "usart.h"
#include "string.h"
#include "ctype.h"
#include "stdio.h"
#include "WM.h"
//#include "DIALOG.h"
extern WM_MESSAGE msg;
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
	CONSUMPTION_RECEIVE = 0,
	CONSUMPTION_WAIT_RECEIVE
}OBD_Average_Cons_States_Typedef;

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
	uint8_t NumberOfErrors;
}CarParameters_Typedef;

typedef struct
{	
	float Voltage, ECT, FUEL, Fuel_consumption, LH_consumption, FUEL_Liters, Average_Consumption;	
}CarValues_Typedef;

typedef enum
{
	START_READ_ERRORS = 0,
	WAIT_ERROR,
	READ_OBD_ERRORS,
	CLEAR_OBD_ERRORS,
	OBD_ERRORS_NOP,
	OBD_ERRORS_WAIT_VIN
}OBD_Errors_State_Typedef;

void OBD_Init(void);
void OBD_Update(void);
void OBD_CheckState(uint8_t * buffer, CarParameters_Typedef *car);
void OBDReadErrors(void);
int htoi(const char* hex);
int getRawInt(char c);
#endif
