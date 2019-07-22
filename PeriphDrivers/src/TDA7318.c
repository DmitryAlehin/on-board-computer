#include "TDA7318.h"

void TDA7318_SetVolume(uint8_t Volume)
{
	uint8_t tx_data;
	tx_data = TDA7318_SET_VOLUME|Volume;
	HAL_I2C_Master_Transmit(&hi2c1, TDA7318_ADDRESS<<1, &tx_data, 1, 100);
}

void TDA7318_SetAttenuation(uint8_t Speaker,uint8_t Value)
{
	uint8_t tx_data;
	tx_data = Speaker|Value;
	HAL_I2C_Master_Transmit(&hi2c1, TDA7318_ADDRESS<<1, &tx_data, 1, 100);
}

void TDA7318_SetBass(int8_t Bass)
{
	uint8_t tx_data;
	tx_data = TDA7318_SET_BASS|Bass;
	HAL_I2C_Master_Transmit(&hi2c1, TDA7318_ADDRESS<<1, &tx_data, 1, 100);
}

void TDA7318_SetTreble(int8_t Treble)
{
	uint8_t tx_data;
	tx_data = TDA7318_SET_TREBLE|Treble;
	HAL_I2C_Master_Transmit(&hi2c1, TDA7318_ADDRESS<<1, &tx_data, 1, 100);
}

void TDA7318_SelectInput(uint8_t Input)
{
	uint8_t tx_data;
	tx_data = TDA7318_AUDIO_SWITCH|Input;
	HAL_I2C_Master_Transmit(&hi2c1, TDA7318_ADDRESS<<1, &tx_data, 1, 100);
}

void TDA7318_SetAmplification(uint8_t Amplification)
{	
	switch(Amplification)
	{
		case 1:
			Amplification = AMP_PLUS_0_dBm;
			break;
		case 2:
			Amplification = AMP_PLUS_6_25_dBm;
			break;
		case 3:
			Amplification = AMP_PLUS_12_5_dBm;
			break;
		case 4:
			Amplification = AMP_PLUS_18_75_dBm;
			break;
	}
	uint8_t tx_data;
	tx_data = TDA7318_AUDIO_SWITCH|INPUT_1|Amplification;
	HAL_I2C_Master_Transmit(&hi2c1, TDA7318_ADDRESS<<1, &tx_data, 1, 100);
	tx_data = TDA7318_AUDIO_SWITCH|RADIO_INPUT|Amplification;
	HAL_I2C_Master_Transmit(&hi2c1, TDA7318_ADDRESS<<1, &tx_data, 1, 100);
	tx_data = TDA7318_AUDIO_SWITCH|BT_INPUT|Amplification;
	HAL_I2C_Master_Transmit(&hi2c1, TDA7318_ADDRESS<<1, &tx_data, 1, 100);
	tx_data = TDA7318_AUDIO_SWITCH|AUX_INPUT|Amplification;
	HAL_I2C_Master_Transmit(&hi2c1, TDA7318_ADDRESS<<1, &tx_data, 1, 100);
}