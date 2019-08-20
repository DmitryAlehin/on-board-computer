/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.32                          *
*        Compiled Oct  8 2015, 11:59:02                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0  (GUI_ID_USER + 0x00)
#define ID_TEXT_0    (GUI_ID_USER + 0x01)
#define ID_BUTTON_0  (GUI_ID_USER + 0x02)
#define ID_BUTTON_1  (GUI_ID_USER + 0x03)
#define ID_BUTTON_2  (GUI_ID_USER + 0x04)
#define ID_BUTTON_3  (GUI_ID_USER + 0x05)
#define ID_SLIDER_0  (GUI_ID_USER + 0x06)
#define ID_BUTTON_5  (GUI_ID_USER + 0x07)
#define ID_BUTTON_6  (GUI_ID_USER + 0x08)
#define ID_BUTTON_7  (GUI_ID_USER + 0x09)
#define ID_BUTTON_8  (GUI_ID_USER + 0x0A)
#define ID_BUTTON_9 (GUI_ID_USER + 0x0B)
#define ID_TEXT_2    (GUI_ID_USER + 0x0C)
#define ID_TEXT_3    (GUI_ID_USER + 0x0D)
#define ID_TEXT_1    (GUI_ID_USER + 0x0E)
#define ID_TEXT_4    (GUI_ID_USER + 0x0F)
#define ID_TEXT_5    (GUI_ID_USER + 0x10)
// USER START (Optionally insert additional defines)
extern RTC_TimeTypeDef time;
extern RTC_DateTypeDef date;
extern GUIHandles GuiHandles;
extern BT_General_States_Typedef BT_General_State;
extern BT_States_Typedef BT_State;
extern BT_Values_Typedef BT_Value;
extern BT_PowerMode_Typedef BT_PowerMode;
extern TDA7318_States_Typedef TDA7318_General_State;
extern TDA7318_Volume_States_Typedef TDA7318_Volume_State;
extern RDA5807M_Update_States_Typedef RDA5807M_Update_States;
extern RDA5807M_PowerMode_Typedef RDA5807M_PowerMode;
uint8_t Volume;
extern RDA5807M_Data_Typedef RDA5807M_Data;
extern Audio_Switch_States_Typedef Audio_Switch;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontArialBlack32;
extern OBD_General_States_Typedef OBD_General_State;
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "AudioWindow", ID_WINDOW_0, 0, 0, 800, 480, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Time_Text", ID_TEXT_0, 0, 0, 100, 30, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, "EQ_Button", ID_BUTTON_0, 0, 345, 150, 100, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "AUX_Button", ID_BUTTON_1, 0, 240, 150, 100, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "RADIO_Button", ID_BUTTON_2, 0, 135, 150, 100, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "BT_Button", ID_BUTTON_3, 0, 30, 150, 100, 0, 0x0, 0 },  
  { BUTTON_CreateIndirect, "Tr_plus_Button", ID_BUTTON_5, 490, 240, 100, 70, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Tr_minus_Button", ID_BUTTON_6, 270, 240, 100, 70, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Play_Button", ID_BUTTON_7, 380, 240, 100, 70, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "MUTE_Button", ID_BUTTON_8, 648, 200, 150, 100, 0, 0x0, 0 },    
  { TEXT_CreateIndirect, "AUDIO_Text", ID_TEXT_1, 220, 140, 400, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Main_Button", ID_BUTTON_9, 698, 410, 100, 70, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Cons_Text", ID_TEXT_2, 665, 0, 135, 30, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Bat_Text", ID_TEXT_3, 570, 0, 90, 30, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "AUDIO_Text", ID_TEXT_4, 380, 55, 100, 50, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "BT_INFO_Text", ID_TEXT_5, 150, 30, 150, 70, 0, 0x0, 0 },
	{ SLIDER_CreateIndirect, "Volume_Slider", ID_SLIDER_0, 268, 350, 320, 50, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem, hWin;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
	uint8_t Data[20];
	
	
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'AudioWindow'
    //
    hItem = pMsg->hWin;
    WINDOW_SetBkColor(hItem, GUI_BKCOLOR);
    //
    // Initialization of 'Time_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetText(hItem, "00:00");
    //
    // Initialization of 'EQ_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetText(hItem, "EQ");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of 'AUX_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetText(hItem, "AUX");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of 'RADIO_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
    BUTTON_SetText(hItem, "RADIO");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of 'BT_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
    BUTTON_SetText(hItem, "BT");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
		BUTTON_SetFocussable(hItem, 0);   
    //
    // Initialization of 'Tr_plus_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
		sprintf((char *)Data, "%c%c%c", 13, 13, 108);
    BUTTON_SetText(hItem, (char *)Data);
    BUTTON_SetFont(hItem, &GUI_FontArialBlack32);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of 'Tr_minus_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_6);
    sprintf((char *)Data, "%c%c%c", 108, 12, 12);
    BUTTON_SetText(hItem, (char *)Data);
    BUTTON_SetFont(hItem, &GUI_FontArialBlack32);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of 'Play_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_7);
    sprintf((char *)Data, "%c", 13);
    BUTTON_SetText(hItem, (char *)Data);
    BUTTON_SetFont(hItem, &GUI_FontArialBlack32);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of 'MUTE_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_8);
    BUTTON_SetText(hItem, "MUTE");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
		BUTTON_SetFocussable(hItem, 0);		
    //    
    // Initialization of 'AUDIO_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
		TEXT_SetText(hItem, "Music player");
    TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    //
    // Initialization of 'Main_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_9);
    BUTTON_SetText(hItem, "Main");
    BUTTON_SetFont(hItem, GUI_FONT_24B_1);
		BUTTON_SetFocussable(hItem, 0);    
    //
    // Initialization of 'Cons_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetText(hItem, "F_cons");
    //
    // Initialization of 'Bat_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetText(hItem, "Vbat");
    //
    // Initialization of 'AUDIO_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetText(hItem, "AUDIO");
    //
    // Initialization of 'BT_INFO_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
    TEXT_SetTextColor(hItem, GUI_GREEN);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_20B_1);
		TEXT_SetWrapMode(hItem, GUI_WRAPMODE_WORD);
		TEXT_SetText(hItem, "");
    // USER START (Optionally insert additional code for further widget initialization)
		TDA7318_SetVolume(Saved_Parameters.Volume);		
		TDA7318_SetBass(Saved_Parameters.Bass - 14);
		TDA7318_SetTreble(Saved_Parameters.Treble - 14);
		TDA7318_SetAmplification(Saved_Parameters.Amplification);
		TDA7318_SetAttenuation(TDA7318_SPEAKER_LF, Saved_Parameters.FL);
		TDA7318_SetAttenuation(TDA7318_SPEAKER_RF, Saved_Parameters.FR);
		TDA7318_SetAttenuation(TDA7318_SPEAKER_LR, Saved_Parameters.RL);
		TDA7318_SetAttenuation(TDA7318_SPEAKER_RR, Saved_Parameters.RR);
		TDA7318_SelectInput(Audio_Switch);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_0);		
		SLIDER_SetRange(hItem, 0, 63);
		SLIDER_SetValue(hItem, ~(Saved_Parameters.Volume - 64));
		if(TDA7318_Volume_State == TDA7318_UNMUTE)
			{
				TDA7318_SetVolume(Saved_Parameters.Volume);
				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_8);
				BUTTON_SetText(hItem, "MUTE");
				BUTTON_SetFont(hItem, GUI_FONT_32B_1);
				BUTTON_SetFocussable(hItem, 0);				
			}
			if(TDA7318_Volume_State == TDA7318_MUTE)
			{
				TDA7318_SetVolume(63);
				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_8);
				BUTTON_SetText(hItem, "UNMUTE");
				BUTTON_SetFont(hItem, GUI_FONT_32B_1);
				BUTTON_SetFocussable(hItem, 0);
			}
		switch(Audio_Switch)
		{
			case INPUT_1_SWITCH:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
				TEXT_SetText(hItem, "Music player");
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);			
				TEXT_SetText(hItem, "");
				break;
			case RADIO_SWITCH:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
				TEXT_SetText(hItem, "RADIO");
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);			
				TEXT_SetText(hItem, "");
				break;
			case BT_SWITCH:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
				TEXT_SetText(hItem, "Bluetooth");
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);			
				TEXT_SetText(hItem, "");
				break;
			case AUX_SWITCH:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
				TEXT_SetText(hItem, "AUX");
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);			
				TEXT_SetText(hItem, "");
				break;
		}	
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
		sprintf((char *) Data, "VOLUME: %d", Saved_Parameters.Volume);
		TEXT_SetText(hItem, (char *)Data);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
		HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);
		sprintf((char *)Data, "%02d:%02d", time.Hours, time.Minutes);
		TEXT_SetText(hItem, (char *)Data);
		if(Saved_Parameters.OBD_mode)
		{
			if(OBD_General_State == OBD_INIT)
			{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
				if(CarParameters.VSS != 0.0f)
				{
					if(Saved_Parameters.Average_consumption != 0.0f)
					{
						sprintf((char *)Data, "%.1f L/100km", Saved_Parameters.Average_consumption);
						TEXT_SetText(hItem, (char *)Data);
					}
				}
				else
				{
					if(Car_Param.LH_consumption != 0.0f)
					{
						sprintf((char *)Data, "%.1f L/h", Car_Param.LH_consumption);
						TEXT_SetText(hItem, (char *)Data);
					}
				}
			}
			if(CarParameters.Voltage != 0.0f)
			{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
				sprintf((char *)Data, "%.1f V", CarParameters.Voltage);
				TEXT_SetText(hItem, (char *)Data);
			}
		}	
		if(BT_General_State == BT_INIT_OK)
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
			sprintf((char *)Data, "Name:%s\r\nPIN:%s", BT_Value.BT_NAME, BT_Value.PIN);
			TEXT_SetText(hItem, (char *)Data);
		}
		switch(BT_State)
		{
			case BT_CONNECTED:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
				TEXT_SetText(hItem, "Bluetooth connected");
				TEXT_SetFont(hItem, GUI_FONT_32B_ASCII);
				break;
			case BT_DISCONNECTED:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
				TEXT_SetText(hItem, "Bluetooth disconnected");
				TEXT_SetFont(hItem, GUI_FONT_32B_ASCII);
				break;
			case BT_PLAY:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_7);
				sprintf((char *)Data, "%c%c", 108, 108);
				BUTTON_SetText(hItem, (char *)Data);
				BUTTON_SetFocussable(hItem, 0);
				break;
			case BT_PAUSE:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_7);
				sprintf((char *)Data, "%c", 13);
				BUTTON_SetText(hItem, (char *)Data);
				BUTTON_SetFocussable(hItem, 0);		
				break;
			case WAIT:	
				break;
			case BT_CALL:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
				TEXT_SetText(hItem, (char *)BT_Value.CALL_NUMBER);
				TEXT_SetFont(hItem, GUI_FONT_32B_ASCII);
				break;
		}
		if(BT_PowerMode == OFF)
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
			TEXT_SetText(hItem, "Music player");
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);			
			TEXT_SetText(hItem, "");
				
		}
		if(BT_PowerMode == ON)
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
			TEXT_SetText(hItem, "Bluetooth");
		}
		pMsg->MsgId = 0;
    // USER END
    break;
		
		case WM_UPDATE_MIN:
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
			HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
			sprintf((char *)Data, "%02d:%02d", time.Hours, time.Minutes);
			HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);
			TEXT_SetText(hItem, (char *)Data);
			if(CarParameters.Voltage != 0.0f)
			{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
				sprintf((char *)Data, "%.1f V", CarParameters.Voltage);
				TEXT_SetText(hItem, (char *)Data);
			}
			pMsg->MsgId = 0;
			break;
		
		case WM_UPDATE_CAR:
			if(Saved_Parameters.OBD_mode)
			{
				if(OBD_General_State == OBD_INIT)
				{
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
					if(CarParameters.VSS != 0.0f)
					{
						if(Saved_Parameters.Average_consumption != 0.0f)
						{
							sprintf((char *)Data, "%.1f L/100km", Saved_Parameters.Average_consumption);
							TEXT_SetText(hItem, (char *)Data);
						}
					}
					else
					{
						if(Car_Param.LH_consumption != 0.0f)
						{
							sprintf((char *)Data, "%.1f L/h", Car_Param.LH_consumption);
							TEXT_SetText(hItem, (char *)Data);
						}
					}
				}
				if(CarParameters.Voltage != 0.0f)
				{
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
					sprintf((char *)Data, "%.1f V", CarParameters.Voltage);
					TEXT_SetText(hItem, (char *)Data);
				}
			}	
			pMsg->MsgId = 0;
			break;		
		case WM_UPDATE_AUDIO:			
			if(TDA7318_Volume_State == TDA7318_UNMUTE)
			{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_8);
				BUTTON_SetText(hItem, "MUTE");
				BUTTON_SetFont(hItem, GUI_FONT_32B_1);
				BUTTON_SetFocussable(hItem, 0);
				
			}
			if(TDA7318_Volume_State == TDA7318_MUTE)
			{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_8);
				BUTTON_SetText(hItem, "UNMUTE");
				BUTTON_SetFont(hItem, GUI_FONT_32B_1);
				BUTTON_SetFocussable(hItem, 0);
			}
			
			switch(Audio_Switch)
			{
				case INPUT_1_SWITCH:
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
					TEXT_SetText(hItem, "Music player");
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);			
					TEXT_SetText(hItem, "");
					break;
				case RADIO_SWITCH:
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
					TEXT_SetText(hItem, "RADIO");
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);			
					TEXT_SetText(hItem, "");
					break;
				case BT_SWITCH:
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
					TEXT_SetText(hItem, "Bluetooth");
					if(BT_General_State == BT_INIT_OK)
					{
						hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
						sprintf((char *)Data, "Name:%s\r\nPIN:%s", BT_Value.BT_NAME, BT_Value.PIN);
						TEXT_SetText(hItem, (char *)Data);
					}
					break;
				case AUX_SWITCH:
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
					TEXT_SetText(hItem, "AUX");
					hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);			
					TEXT_SetText(hItem, "");
					break;
			}
			pMsg->MsgId = 0;
			break;
	case WM_UPDATE_BT:
		if(BT_General_State == BT_INIT_OK)
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
			sprintf((char *)Data, "Name:%s\r\nPIN:%s", BT_Value.BT_NAME, BT_Value.PIN);
			TEXT_SetText(hItem, (char *)Data);
		}
		switch(BT_State)
		{
			case BT_CONNECTED:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
				TEXT_SetText(hItem, "Bluetooth connected");
				TEXT_SetFont(hItem, GUI_FONT_32B_ASCII);
				break;
			case BT_DISCONNECTED:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
				TEXT_SetText(hItem, "Bluetooth disconnected");
				TEXT_SetFont(hItem, GUI_FONT_32B_ASCII);
				break;
			case BT_PLAY:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_7);
				sprintf((char *)Data, "%c%c", 108, 108);
				BUTTON_SetText(hItem, (char *)Data);
				BUTTON_SetFocussable(hItem, 0);
				break;
			case BT_PAUSE:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_7);
				sprintf((char *)Data, "%c", 13);
				BUTTON_SetText(hItem, (char *)Data);
				BUTTON_SetFocussable(hItem, 0);		
				break;
			case WAIT:	
				break;
			case BT_CALL:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
				TEXT_SetText(hItem, (char *)BT_Value.CALL_NUMBER);
				TEXT_SetFont(hItem, GUI_FONT_32B_ASCII);
				break;
		}
		pMsg->MsgId = 0;
		break;
	case WM_RADIO:
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
		sprintf((char *)Data, "RADIO Freq %.2f", RDA5807M_Data.Frequency);
		TEXT_SetText(hItem, (char *)Data);
		pMsg->MsgId = 0;
		break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'EQ_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				WM_DeleteWindow(pMsg->hWin);
				hWin = CreateEqualizerWindow();
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'AUX_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				if(Audio_Switch != AUX_SWITCH)
				{
					Audio_Switch = AUX_SWITCH;
					BT_PowerMode = OFF;
					TDA7318_SelectInput(Audio_Switch);
				}		
				else
				{
					Audio_Switch = INPUT_1_SWITCH;
					BT_PowerMode = OFF;					
					TDA7318_SelectInput(Audio_Switch);
				}
				msg.MsgId = WM_UPDATE_AUDIO;
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_2: // Notifications sent by 'RADIO_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				if(RDA5807M_PowerMode == RDA5807M_OFF)
				{					
					Audio_Switch = RADIO_SWITCH;
					BT_PowerMode = OFF;
					TDA7318_SelectInput(Audio_Switch);
					msg.MsgId = WM_UPDATE_AUDIO;
				}
				else if(RDA5807M_PowerMode == RDA5807M_ON)
				{
					Audio_Switch = INPUT_1_SWITCH;
					BT_PowerMode = OFF;
					TDA7318_SelectInput(Audio_Switch);
					msg.MsgId = WM_UPDATE_AUDIO;
				}
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_3: // Notifications sent by 'BT_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)						
				if(BT_PowerMode == OFF)
				{					
					HAL_GPIO_WritePin(BT_EN_GPIO_Port, BT_EN_Pin, GPIO_PIN_SET);					
					BT_PowerMode = ON;
				}
				else if(BT_PowerMode == ON)
				{
					BT_PowerMode = OFF;
				}
				if(Audio_Switch != BT_SWITCH)
				{
					Audio_Switch = BT_SWITCH;
					TDA7318_SelectInput(Audio_Switch);
				}
				else
				{
					Audio_Switch = INPUT_1_SWITCH;
					TDA7318_SelectInput(Audio_Switch);
				}
					msg.MsgId = WM_UPDATE_AUDIO;				
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_5: // Notifications sent by 'Tr_plus_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				if(Audio_Switch == BT_SWITCH)
				{
					HAL_UART_Transmit(&huart2, "AT+MD\r\n", 8, 100);
				}
				else if(Audio_Switch == RADIO_SWITCH)
				{
					RDA5807M_SeekUp();						
					RDA5807M_Update_States = RDA5807M_RSSI_WAIT;
					msg.MsgId = WM_RADIO;
				}
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_6: // Notifications sent by 'Tr_minus_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)				
				if(Audio_Switch == BT_SWITCH)
				{
					HAL_UART_Transmit(&huart2, "AT+ME\r\n", 8, 100);
				}
				else if(Audio_Switch == RADIO_SWITCH)
				{
					RDA5807M_SeekDown();		
					RDA5807M_Update_States = RDA5807M_RSSI_WAIT;
					msg.MsgId = WM_RADIO;
				}
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_7: // Notifications sent by 'Play_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				if(Audio_Switch == BT_SWITCH)
				{
					HAL_UART_Transmit(&huart2, "AT+MA\r\n", 8, 100);
				}
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_8: // Notifications sent by 'MUTE_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				if(TDA7318_Volume_State == TDA7318_UNMUTE)
				{
					TDA7318_SetVolume(63);
					TDA7318_Volume_State = TDA7318_MUTE;
					msg.MsgId = WM_UPDATE_AUDIO;
				}
				else
				{
					TDA7318_SetVolume(Saved_Parameters.Volume);
					TDA7318_Volume_State = TDA7318_UNMUTE;
					msg.MsgId = WM_UPDATE_AUDIO;
				}
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;		
		case ID_SLIDER_0: // Notifications sent by 'Volume_Slider'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
				TDA7318_Volume_State = TDA7318_UNMUTE;
				hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_0);
				Volume = SLIDER_GetValue(hItem);
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
				sprintf((char *) Data, "VOLUME: %d", Volume);
				TEXT_SetText(hItem, (char *)Data);
				Saved_Parameters.Volume =~ (Volume - 64);				
				TDA7318_SetVolume(Saved_Parameters.Volume);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;    
    case ID_BUTTON_9: // Notifications sent by 'Main_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				WM_DeleteWindow(pMsg->hWin);
				hWin = CreateMainWindow();				
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateAudioWindow
*/

WM_HWIN CreateAudioWindow(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	GuiHandles.hAudioWindow = hWin;
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
