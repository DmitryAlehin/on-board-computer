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
#define ID_WINDOW_0         (GUI_ID_USER + 0x00)
#define ID_TEXT_0         (GUI_ID_USER + 0x01)
#define ID_BUTTON_0         (GUI_ID_USER + 0x02)
#define ID_BUTTON_1         (GUI_ID_USER + 0x03)
#define ID_BUTTON_2         (GUI_ID_USER + 0x04)
#define ID_BUTTON_3         (GUI_ID_USER + 0x05)
#define ID_BUTTON_4         (GUI_ID_USER + 0x06)
#define ID_BUTTON_5         (GUI_ID_USER + 0x07)
#define ID_BUTTON_6         (GUI_ID_USER + 0x08)
#define ID_BUTTON_7         (GUI_ID_USER + 0x09)
#define ID_BUTTON_8         (GUI_ID_USER + 0x0A)
#define ID_BUTTON_9         (GUI_ID_USER + 0x0B)
#define ID_BUTTON_10         (GUI_ID_USER + 0x0C)
#define ID_BUTTON_11         (GUI_ID_USER + 0x0D)
#define ID_TEXT_1         (GUI_ID_USER + 0x0E)
#define ID_BUTTON_12         (GUI_ID_USER + 0x0F)
#define ID_BUTTON_13         (GUI_ID_USER + 0x10)
#define ID_BUTTON_14         (GUI_ID_USER + 0x11)
#define ID_BUTTON_15         (GUI_ID_USER + 0x12)
#define ID_BUTTON_16         (GUI_ID_USER + 0x13)
#define ID_BUTTON_17         (GUI_ID_USER + 0x14)
#define ID_BUTTON_18         (GUI_ID_USER + 0x15)
#define ID_TEXT_2         (GUI_ID_USER + 0x17)
#define ID_TEXT_3         (GUI_ID_USER + 0x18)
#define ID_TEXT_4         (GUI_ID_USER + 0x19)
#define ID_TEXT_5         (GUI_ID_USER + 0x1A)


// USER START (Optionally insert additional defines)
extern RTC_TimeTypeDef time;
extern RTC_DateTypeDef date;
extern GUIHandles GuiHandles;
extern BT_General_States_Typedef BT_General_State;
extern BT_States_Typedef BT_State;
extern BT_Values_Typedef BT_Value;
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
  { BUTTON_CreateIndirect, "Back_Button", ID_BUTTON_4, 638, 270, 80, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Tr_plus_Button", ID_BUTTON_5, 490, 240, 100, 70, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Tr_minus_Button", ID_BUTTON_6, 270, 240, 100, 70, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Play_Button", ID_BUTTON_7, 380, 240, 100, 70, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Src_Button", ID_BUTTON_8, 380, 350, 100, 70, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "ENC_plus_Button", ID_BUTTON_9, 490, 350, 100, 70, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "ENC_minus_Button", ID_BUTTON_10, 270, 350, 100, 70, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Disp_Button", ID_BUTTON_11, 718, 270, 80, 80, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "MVH_Text", ID_TEXT_1, 270, 140, 300, 50, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Main_Button", ID_BUTTON_12, 698, 410, 100, 70, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "2_Button", ID_BUTTON_13, 718, 30, 80, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "6_Button", ID_BUTTON_14, 718, 190, 80, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "1_Button", ID_BUTTON_15, 638, 30, 80, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "5_Button", ID_BUTTON_16, 638, 190, 80, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "3_Button", ID_BUTTON_17, 638, 110, 80, 80, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "4_Button", ID_BUTTON_18, 718, 111, 80, 80, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Cons_Text", ID_TEXT_2, 675, 0, 125, 30, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Bat_Text", ID_TEXT_3, 570, 0, 100, 30, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "AUDIO_Text", ID_TEXT_4, 380, 55, 100, 50, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "BT_INFO_Text", ID_TEXT_5, 150, 30, 150, 70, 0, 0x0, 0 },
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
	int retCode;
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
    // Initialization of 'Back_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4);
    BUTTON_SetText(hItem, "Back");
    BUTTON_SetFont(hItem, GUI_FONT_24B_1);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of 'Tr_plus_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
    BUTTON_SetText(hItem, ">>|");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of 'Tr_minus_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_6);
    BUTTON_SetText(hItem, "|<<");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of 'Play_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_7);
    BUTTON_SetText(hItem, "||");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of 'Src_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_8);
    BUTTON_SetText(hItem, "*");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of 'ENC_plus_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_9);
    BUTTON_SetText(hItem, "+");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of 'ENC_minus_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_10);
    BUTTON_SetText(hItem, "-");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of 'Disp_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_11);
    BUTTON_SetText(hItem, "Disp");
    BUTTON_SetFont(hItem, GUI_FONT_24B_1);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of 'MVH_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    //
    // Initialization of 'Main_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_12);
    BUTTON_SetText(hItem, "Main");
    BUTTON_SetFont(hItem, GUI_FONT_24B_1);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of '2_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_13);
    BUTTON_SetText(hItem, "2");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of '6_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_14);
    BUTTON_SetText(hItem, "6");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of '1_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_15);
    BUTTON_SetText(hItem, "1");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of '5_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_16);
    BUTTON_SetText(hItem, "5");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of '3_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_17);
    BUTTON_SetText(hItem, "3");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of '4_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_18);
    BUTTON_SetText(hItem, "4");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
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
		if(/*AUX*/ 1)
		{			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_13);//2
			WM_HideWindow(hItem);
			WM_DisableWindow(hItem);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_14);
			WM_HideWindow(hItem);
			WM_DisableWindow(hItem);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_15);
			WM_HideWindow(hItem);
			WM_DisableWindow(hItem);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_16);
			WM_HideWindow(hItem);
			WM_DisableWindow(hItem);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_17);
			WM_HideWindow(hItem);
			WM_DisableWindow(hItem);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_18);
			WM_HideWindow(hItem);
			WM_DisableWindow(hItem);			
		}
		else
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_13);//2
			WM_ShowWindow(hItem);
			WM_EnableWindow(hItem);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_14);
			WM_ShowWindow(hItem);
			WM_EnableWindow(hItem);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_15);
			WM_ShowWindow(hItem);
			WM_EnableWindow(hItem);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_16);
			WM_ShowWindow(hItem);
			WM_EnableWindow(hItem);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_17);
			WM_ShowWindow(hItem);
			WM_EnableWindow(hItem);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_18);
			WM_ShowWindow(hItem);
			WM_EnableWindow(hItem);			
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
		HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
		sprintf((char *)Data, "%02d:%02d", time.Hours, time.Minutes);
		TEXT_SetText(hItem, (char *)Data);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
		sprintf((char *)Data, "%.1f L/100km", Car_Param.Fuel_consumption);
		TEXT_SetText(hItem, (char *)Data);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
		sprintf((char *)Data, "%.1f V", Car_Param.Voltage);
		TEXT_SetText(hItem, (char *)Data);		
		if(BT_General_State == BT_INIT_OK)
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
			sprintf((char *)Data, "Name:%s\r\nPIN:%s", BT_Value.BT_NAME, BT_Value.PIN);
			TEXT_SetText(hItem, (char *)Data);
		}
		if(BT_State == BT_CONNECTED)
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
			BUTTON_SetText(hItem, "CN");
			BUTTON_SetFont(hItem, GUI_FONT_32B_ASCII);
		}
		if(BT_State == BT_DISCONNECTED)
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
			BUTTON_SetText(hItem, "DN");
			BUTTON_SetFont(hItem, GUI_FONT_32B_ASCII);
		}
		if(BT_State == BT_PLAY)
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
			BUTTON_SetText(hItem, "||");
		}
		if(BT_State == BT_PAUSE)
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
			BUTTON_SetText(hItem, "|>");		
		}
		if(BT_General_State == BT_OFF)
		{
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
			BUTTON_SetText(hItem, "BT");
			BUTTON_SetFont(hItem, GUI_FONT_32B_ASCII);
		}
		pMsg->MsgId = 0;
    // USER END
    break;
		
		case WM_UPDATE_MIN:
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
			HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
			sprintf((char *)Data, "%02d:%02d", time.Hours, time.Minutes);
			TEXT_SetText(hItem, (char *)Data);
			pMsg->MsgId = 0;
			break;
		
		case WM_UPDATE_CAR:
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
			sprintf((char *)Data, "%.1f L/100km", Car_Param.Fuel_consumption);
			TEXT_SetText(hItem, (char *)Data);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
			sprintf((char *)Data, "%.1f V", Car_Param.Voltage);
			TEXT_SetText(hItem, (char *)Data);
			pMsg->MsgId = 0;
			break;		
		case WM_UPDATE_BT:
			if(BT_General_State == BT_INIT_OK)
			{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
				sprintf((char *)Data, "Name:%s\r\nPIN:%s", BT_Value.BT_NAME, BT_Value.PIN);
				TEXT_SetText(hItem, (char *)Data);
			}
			if(BT_State == BT_CONNECTED)
			{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
				BUTTON_SetText(hItem, "CN");
				BUTTON_SetFont(hItem, GUI_FONT_32B_ASCII);
			}
			if(BT_State == BT_DISCONNECTED)
			{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
				BUTTON_SetText(hItem, "DN");
				BUTTON_SetFont(hItem, GUI_FONT_32B_ASCII);
			}
			if(BT_State == BT_PLAY)
			{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
				BUTTON_SetText(hItem, "||");
			}
			if(BT_State == BT_PAUSE)
			{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
				BUTTON_SetText(hItem, "|>");		
			}
			if(BT_General_State == BT_OFF)
			{
				hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
				BUTTON_SetText(hItem, "BT");
				BUTTON_SetFont(hItem, GUI_FONT_32B_ASCII);
			}
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
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_4: // Notifications sent by 'Back_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
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
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_8: // Notifications sent by 'Src_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_9: // Notifications sent by 'ENC_plus_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_10: // Notifications sent by 'ENC_minus_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_11: // Notifications sent by 'Disp_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_12: // Notifications sent by 'Main_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
//				GUI_EndDialog(CreateAudioWindow(), 0);
////				WM_DeleteWindow(hWin);
//				hWin = CreateMainWindow();
				WM_DeleteWindow(pMsg->hWin);
				hWin = CreateMainWindow();
//				retCode = GUI_ExecCreatedDialog(hWin);
				
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_13: // Notifications sent by '2_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_14: // Notifications sent by '6_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_15: // Notifications sent by '1_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_16: // Notifications sent by '5_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_17: // Notifications sent by '3_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_18: // Notifications sent by '4_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
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
WM_HWIN CreateAudioWindow(void);
WM_HWIN CreateAudioWindow(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	GuiHandles.hAudioWindow = hWin;
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
