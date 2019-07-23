#ifndef TDA7318_H
#define TDA7318_H

#include "i2c.h"

#define TDA7318_ADDRESS 0x44

#define INPUT_1               0x00
#define RADIO_INPUT           0x01
#define BT_INPUT              0x02
#define AUX_INPUT             0x03

#define TDA7318_SET_VOLUME    0x00
#define TDA7318_SPEAKER_LR    0xC0
#define TDA7318_SPEAKER_RR    0xE0
#define TDA7318_SPEAKER_LF    0x80
#define TDA7318_SPEAKER_RF    0xA0
#define TDA7318_AUDIO_SWITCH  0x40
#define TDA7318_SET_BASS 		  0x60
#define TDA7318_SET_TREBLE    0x70

#define AMP_PLUS_18_75_dBm    0x00
#define AMP_PLUS_12_5_dBm      0x08
#define AMP_PLUS_6_25_dBm     0x10
#define AMP_PLUS_0_dBm        0x18

typedef enum 
{
	TDA7318_INIT_OK = 0,
	TDA7318_WAIT_INIT
}TDA7318_States_Typedef;

typedef enum 
{
	TDA7318_MUTE = 0,
	TDA7318_UNMUTE
}TDA7318_Volume_States_Typedef;


typedef enum 
{
	RADIO_SWITCH = 0x01,
	BT_SWITCH = 0x02,
	AUX_SWITCH = 0x03,
	INPUT_1_SWITCH = 0x00
}Audio_Switch_States_Typedef;

void TDA7318_SetVolume(uint8_t Volume);
void TDA7318_SetAttenuation(uint8_t Speaker,uint8_t Value);
void TDA7318_SetBass(int8_t Bass);
void TDA7318_SetTreble(int8_t Treble);
void TDA7318_SelectInput(uint8_t Input);
void TDA7318_SetAmplification(uint8_t Amplification);
#endif