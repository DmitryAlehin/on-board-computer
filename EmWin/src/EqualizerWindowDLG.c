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
#define ID_WINDOW_0 (GUI_ID_USER + 0x00)
#define ID_TEXT_0 (GUI_ID_USER + 0x01)
#define ID_SLIDER_0 (GUI_ID_USER + 0x02)
#define ID_SLIDER_1 (GUI_ID_USER + 0x03)
#define ID_SLIDER_2 (GUI_ID_USER + 0x04)
#define ID_SLIDER_3 (GUI_ID_USER + 0x05)
#define ID_SLIDER_4 (GUI_ID_USER + 0x06)
#define ID_SLIDER_5 (GUI_ID_USER + 0x07)
#define ID_SLIDER_6 (GUI_ID_USER + 0x08)
#define ID_BUTTON_0 (GUI_ID_USER + 0x09)
#define ID_TEXT_1 (GUI_ID_USER + 0x0A)
#define ID_TEXT_2 (GUI_ID_USER + 0x0B)
#define ID_TEXT_3 (GUI_ID_USER + 0x0C)
#define ID_TEXT_4 (GUI_ID_USER + 0x0D)
#define ID_TEXT_5 (GUI_ID_USER + 0x0E)
#define ID_TEXT_6 (GUI_ID_USER + 0x0F)
#define ID_TEXT_7 (GUI_ID_USER + 0x10)
#define ID_TEXT_8 (GUI_ID_USER + 0x11)


// USER START (Optionally insert additional defines)
extern GUIHandles GuiHandles;
extern Audio_Switch_States_Typedef Audio_Switch;
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
  { WINDOW_CreateIndirect, "EqualizerWindow", ID_WINDOW_0, 0, 0, 800, 480, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Equalizer_Text", ID_TEXT_0, 300, 5, 200, 50, 0, 0x64, 0 },
  { SLIDER_CreateIndirect, "Bass_Slider", ID_SLIDER_0, 10, 150, 50, 320, 8, 0x0, 0 },
  { SLIDER_CreateIndirect, "Treble_Slider", ID_SLIDER_1, 120, 150, 50, 320, 8, 0x0, 0 },
  { SLIDER_CreateIndirect, "FL_Slider", ID_SLIDER_2, 230, 150, 50, 320, 8, 0x0, 0 },
  { SLIDER_CreateIndirect, "FR_Slider", ID_SLIDER_3, 340, 150, 50, 320, 8, 0x0, 0 },
  { SLIDER_CreateIndirect, "RL_Slider", ID_SLIDER_4, 450, 150, 50, 320, 8, 0x0, 0 },
  { SLIDER_CreateIndirect, "RR_Slider", ID_SLIDER_5, 560, 150, 50, 320, 8, 0x0, 0 },
  { SLIDER_CreateIndirect, "Amp_Slider", ID_SLIDER_6, 680, 150, 50, 200, 8, 0x0, 0 },
  { BUTTON_CreateIndirect, "Back_Button", ID_BUTTON_0, 698, 410, 100, 70, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Bass_Text", ID_TEXT_1, 0, 100, 60, 40, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Treble_Text", ID_TEXT_2, 110, 100, 70, 40, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "FL_Text", ID_TEXT_3, 210, 100, 100, 40, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "FR_Text", ID_TEXT_4, 310, 100, 110, 40, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "RL_Text", ID_TEXT_5, 420, 100, 100, 40, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "RR_Text", ID_TEXT_6, 540, 100, 100, 40, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Amp_Text", ID_TEXT_7, 650, 100, 150, 40, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Value_Text", ID_TEXT_8, 325, 55, 150, 40, 0, 0x64, 0 },
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
    // Initialization of 'Equalizer_Text'
    //
		hItem = pMsg->hWin;
    WINDOW_SetBkColor(hItem, GUI_BKCOLOR);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetText(hItem, "Equalizer");
    //
    // Initialization of 'Back_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetFont(hItem, GUI_FONT_24B_1);
    BUTTON_SetText(hItem, "Back");
    //
    // Initialization of 'Bass_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetText(hItem, "Bass");
    //
    // Initialization of 'Treble_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetText(hItem, "Treble");
    //
    // Initialization of 'FL_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetText(hItem, "Front left");
    //
    // Initialization of 'FR_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetText(hItem, "Front right");
    //
    // Initialization of 'RL_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetText(hItem, "Rear left");
    //
    // Initialization of 'RR_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetText(hItem, "Rear right");
    //
    // Initialization of 'Amp_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetText(hItem, "Amplification");
    //
    // Initialization of 'Value_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetText(hItem, "");
    // USER START (Optionally insert additional code for further widget initialization)
//		TDA7318_SetVolume(Saved_Parameters.Volume);		
//		TDA7318_SetBass(Saved_Parameters.Bass);
//		TDA7318_SetTreble(Saved_Parameters.Treble);
//		TDA7318_SetAmplification(Saved_Parameters.Amplification);
//		TDA7318_SetAttenuation(TDA7318_SPEAKER_LF, Saved_Parameters.FL);
//		TDA7318_SetAttenuation(TDA7318_SPEAKER_RF, Saved_Parameters.FR);
//		TDA7318_SetAttenuation(TDA7318_SPEAKER_LR, Saved_Parameters.RL);
//		TDA7318_SetAttenuation(TDA7318_SPEAKER_RR, Saved_Parameters.RR);
		
		TDA7318_SetVolume(Saved_Parameters.Volume);		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_0);
		SLIDER_SetRange(hItem, 0, 15);
		SLIDER_SetValue(hItem, ~(Saved_Parameters.Bass -16));
		hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_1);
		SLIDER_SetRange(hItem, 0, 15);
		SLIDER_SetValue(hItem, ~(Saved_Parameters.Treble -16));
		hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_2);
		SLIDER_SetRange(hItem, 0, 12);
		SLIDER_SetValue(hItem, ~(Saved_Parameters.FL - 13));
		hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_3);
		SLIDER_SetRange(hItem, 0, 12);
		SLIDER_SetValue(hItem, ~(Saved_Parameters.FR - 13));
		hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_4);
		SLIDER_SetRange(hItem, 0, 12);
		SLIDER_SetValue(hItem, ~(Saved_Parameters.RL - 13));
		hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_5);
		SLIDER_SetRange(hItem, 0, 12);
		SLIDER_SetValue(hItem, ~(Saved_Parameters.RR - 13));
		hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_6);
		SLIDER_SetRange(hItem, 1, 4);
		SLIDER_SetValue(hItem, Saved_Parameters.Amplification);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
		TEXT_SetText(hItem, "");
		TDA7318_SelectInput(Audio_Switch);
		pMsg->MsgId = 0;
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_SLIDER_0: // Notifications sent by 'Bass_Slider'
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
				hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_0);
				Saved_Parameters.Bass =~ (SLIDER_GetValue(hItem) - 16);
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
				sprintf((char *) Data, "Value: %d", Saved_Parameters.Bass);
				TEXT_SetText(hItem, (char *)Data);
				TDA7318_SetBass(Saved_Parameters.Bass);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SLIDER_1: // Notifications sent by 'Treble_Slider'
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
				hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_1);
				Saved_Parameters.Treble = SLIDER_GetValue(hItem);
				Saved_Parameters.Treble =~ (SLIDER_GetValue(hItem) - 16);
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
				sprintf((char *) Data, "Value: %d", Saved_Parameters.Treble);
				TEXT_SetText(hItem, (char *)Data);
				TDA7318_SetTreble(Saved_Parameters.Treble);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SLIDER_2: // Notifications sent by 'FL_Slider'
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
				hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_2);
				Saved_Parameters.FL =~ (SLIDER_GetValue(hItem) -13);
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
				sprintf((char *) Data, "Value: %d", Saved_Parameters.FL);
				TEXT_SetText(hItem, (char *)Data);
				TDA7318_SetAttenuation(TDA7318_SPEAKER_LF, Saved_Parameters.FL);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SLIDER_3: // Notifications sent by 'FR_Slider'
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
				hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_3);
				Saved_Parameters.FR =~ (SLIDER_GetValue(hItem) -13);
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
				sprintf((char *) Data, "Value: %d", Saved_Parameters.FR);
				TEXT_SetText(hItem, (char *)Data);
				TDA7318_SetAttenuation(TDA7318_SPEAKER_RF, Saved_Parameters.FR);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SLIDER_4: // Notifications sent by 'RL_Slider'
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
				hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_4);
				Saved_Parameters.RL =~ (SLIDER_GetValue(hItem)-13);
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
				sprintf((char *) Data, "Value: %d", Saved_Parameters.RL);
				TEXT_SetText(hItem, (char *)Data);
				TDA7318_SetAttenuation(TDA7318_SPEAKER_LR, Saved_Parameters.RL);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SLIDER_5: // Notifications sent by 'RR_Slider'
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
				hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_5);
				Saved_Parameters.RR =~ (SLIDER_GetValue(hItem)-13);
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
				sprintf((char *) Data, "Value: %d", Saved_Parameters.RR);
				TEXT_SetText(hItem, (char *)Data);
				TDA7318_SetAttenuation(TDA7318_SPEAKER_RR, Saved_Parameters.RR);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SLIDER_6: // Notifications sent by 'Amp_Slider'
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
				hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_6);
				Saved_Parameters.Amplification = SLIDER_GetValue(hItem);
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
				sprintf((char *) Data, "Value: %d", Saved_Parameters.Amplification);
				TEXT_SetText(hItem, (char *)Data);
				TDA7318_SetAmplification(Saved_Parameters.Amplification);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_0: // Notifications sent by 'Back_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				WM_DeleteWindow(pMsg->hWin);
				hWin = CreateAudioWindow();
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
*       CreateEqualizerWindow
*/

WM_HWIN CreateEqualizerWindow(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	GuiHandles.hEqualizerWindow = hWin;
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/