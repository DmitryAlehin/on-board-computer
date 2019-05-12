#ifndef MVH_08UB_H
#define MVH_08UB_H

#include "string.h"
#include "stdarg.h"
#include "DIALOG.h"
#include "spi.h"

typedef struct
{
	uint8_t MVH_TEXT[15];
}MVH_Values_Typedef;

typedef enum 
{
	MVH_INIT_STATE = 0,
	MVH_CENTER,
	MVH_FRONT,
	MVH_REAR,
	MVH_RIGHT,
	MVH_LEFT,
	MVH_BASS_BOOST,
	MVH_SLA,
	MVH_VOLUME,
	MVH_AUX,
	MVH_AUX_MODE_ON,
	MVH_AUX_MODE_OFF,
	MVH_RADIO,
	MVH_DEMO_OFF,
	MVH_FADER,
	MVH_BALANCE,
	MVH_EQ_SETTINGS,
	MVH_LOUNDLESS,
	MVH_HPF_SETTINGS,
	MVH_CANCEL,
	MVH_CLOCK_SET,
	MVH_12H,
	MVH_24H,
	MVH_USB_AUTO_ON,
	MVH_USB_AUTO_OFF,
	MVH_SYSTEM,
	MVH_INITIAL,
	MVH_LANGUAGE,
	MVH_AUDIO,
	MVH_RADIO_ON,
	MVH_RADIO_OFF
}MVH_States_Typedef;

void MVH_CheckState(uint8_t * buffer, MVH_Values_Typedef * MVH);
uint8_t getNumber(uint8_t * str);
void MVH_OFF(void);
void MVH_ENC(uint8_t turn);
#endif