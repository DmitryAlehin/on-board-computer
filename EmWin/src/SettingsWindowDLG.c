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
#define ID_CHECKBOX_0         (GUI_ID_USER + 0x02)
#define ID_CHECKBOX_1         (GUI_ID_USER + 0x03)
#define ID_CHECKBOX_2         (GUI_ID_USER + 0x04)
#define ID_CHECKBOX_3         (GUI_ID_USER + 0x05)
#define ID_BUTTON_0         (GUI_ID_USER + 0x06)
#define ID_SPINBOX_0         (GUI_ID_USER + 0x07)
#define ID_BUTTON_1         (GUI_ID_USER + 0x08)
#define ID_BUTTON_2         (GUI_ID_USER + 0x0A)
#define ID_LISTWHEEL_0         (GUI_ID_USER + 0x0C)
#define ID_LISTWHEEL_1         (GUI_ID_USER + 0x0E)
#define ID_LISTWHEEL_2         (GUI_ID_USER + 0x10)
#define ID_LISTWHEEL_3         (GUI_ID_USER + 0x11)
#define ID_LISTWHEEL_4         (GUI_ID_USER + 0x12)
#define ID_TEXT_1         (GUI_ID_USER + 0x13)
#define ID_TEXT_2         (GUI_ID_USER + 0x14)
#define ID_TEXT_3         (GUI_ID_USER + 0x15)
#define ID_TEXT_4         (GUI_ID_USER + 0x16)
#define ID_SLIDER_0         (GUI_ID_USER + 0x17)
#define ID_TEXT_5         (GUI_ID_USER + 0x18)


// USER START (Optionally insert additional defines)
extern RTC_TimeTypeDef time;
extern RTC_DateTypeDef date;
extern GUIHandles GuiHandles;
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
  { WINDOW_CreateIndirect, "SettingsWindow", ID_WINDOW_0, 0, 0, 800, 480, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Settings_Text", ID_TEXT_0, 270, 20, 260, 50, 0, 0x64, 0 },
  { CHECKBOX_CreateIndirect, "OBD_Checkbox", ID_CHECKBOX_0, 470, 400, 120, 30, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "Temp_Checkbox", ID_CHECKBOX_1, 50, 400, 120, 30, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "Cons_Checkbox", ID_CHECKBOX_2, 330, 400, 120, 30, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "Debug_Checkbox", ID_CHECKBOX_3, 190, 400, 120, 30, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "About_Button", ID_BUTTON_0, 0, 0, 100, 70, 0, 0x0, 0 },
  { SPINBOX_CreateIndirect, "K_Spinbox", ID_SPINBOX_0, 20, 175, 150, 100, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Main_Button", ID_BUTTON_1, 698, 410, 100, 70, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Apply_Button", ID_BUTTON_2, 698, 0, 100, 70, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, "Listwheel", ID_LISTWHEEL_0, 520, 145, 120, 90, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, "Listwheel", ID_LISTWHEEL_1, 640, 145, 120, 90, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, "Listwheel", ID_LISTWHEEL_2, 520, 290, 80, 90, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, "Listwheel", ID_LISTWHEEL_3, 600, 290, 80, 90, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, "Listwheel", ID_LISTWHEEL_4, 680, 290, 80, 90, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Time_Text", ID_TEXT_1, 520, 100, 240, 30, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Date_Text", ID_TEXT_2, 520, 250, 240, 30, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "F_Text", ID_TEXT_3, 5, 125, 176, 30, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Brightness_Text", ID_TEXT_4, 290, 125, 160, 30, 0, 0x64, 0 },
  { SLIDER_CreateIndirect, "Slider", ID_SLIDER_0, 200, 175, 265, 50, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_5, 190, 330, 200, 30, 0, 0x64, 0 },
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
	char    acBuffer[32];
	GUI_PID_STATE State;
  int           Item;  
	SLIDER_SKINFLEX_PROPS  Slider_Props;
	SPINBOX_SKINFLEX_PROPS Spinbox_Props;
	CHECKBOX_SKINFLEX_PROPS Checkbox_Props;
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'SettingsWindow'
//		HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
//		HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);
//		SLIDER_GetSkinFlexProps(&Slider_Props, SLIDER_SKINFLEX_PI_PRESSED);
//		Slider_Props.aColorFrame[0] = GUI_BLUE_COLOR;
//		Slider_Props.aColorFrame[1] = GUI_BLUE_COLOR;
//		Slider_Props.ColorFocus = GUI_GRAY_COLOR;
//		Slider_Props.ColorTick = GUI_BLUE_COLOR;
//		Slider_Props.aColorInner[0] = GUI_BLUE_COLOR;
//		Slider_Props.aColorInner[1] = GUI_BLUE_COLOR;
//		Slider_Props.aColorShaft[0] = GUI_BLUE_COLOR;
//		Slider_Props.aColorShaft[1] = GUI_BLUE_COLOR;
//		SLIDER_SetSkinFlexProps(&Slider_Props, SLIDER_SKINFLEX_PI_PRESSED);
//		SLIDER_SetSkinFlexProps(&Slider_Props, SLIDER_SKINFLEX_PI_UNPRESSED);
		SPINBOX_GetSkinFlexProps(&Spinbox_Props, SPINBOX_SKINFLEX_PI_ENABLED);
		Spinbox_Props.ColorBk = GUI_GRAY_COLOR;
		Spinbox_Props.aColorFrame[0] = GUI_BLUE_COLOR;
		Spinbox_Props.aColorFrame[1] = GUI_BLUE_COLOR;
		Spinbox_Props.aColorLower[0] = GUI_GRAY_COLOR;
		Spinbox_Props.aColorLower[1] = GUI_GRAY_COLOR;
		Spinbox_Props.aColorUpper[0] = GUI_GRAY_COLOR;
		Spinbox_Props.aColorUpper[1] = GUI_GRAY_COLOR;
		Spinbox_Props.ColorArrow = GUI_BLUE_COLOR;
		Spinbox_Props.ColorButtonFrame = GUI_BLUE_COLOR;
		SPINBOX_SetSkinFlexProps(&Spinbox_Props, SPINBOX_SKINFLEX_PI_ENABLED);
		SPINBOX_SetSkinFlexProps(&Spinbox_Props, SPINBOX_SKINFLEX_PI_PRESSED);
		SPINBOX_SetSkinFlexProps(&Spinbox_Props, SPINBOX_SKINFLEX_PI_FOCUSSED);
		CHECKBOX_GetSkinFlexProps(&Checkbox_Props, CHECKBOX_BI_INACTIV_UNCHECKED);
		Checkbox_Props.aColorFrame[0] = GUI_BLUE_COLOR;
		Checkbox_Props.aColorFrame[1] = GUI_BLUE_COLOR;
		Checkbox_Props.aColorFrame[2] = GUI_BLUE_COLOR;
		Checkbox_Props.aColorInner[0] = GUI_GRAY_COLOR;
		Checkbox_Props.aColorInner[1] = GUI_GRAY_COLOR;
		Checkbox_Props.ColorCheck = GUI_GREEN;
		CHECKBOX_SetSkinFlexProps(&Checkbox_Props, CHECKBOX_SKINFLEX_PI_ENABLED);
		CHECKBOX_SetSkinFlexProps(&Checkbox_Props, CHECKBOX_SKINFLEX_PI_DISABLED);
//		CHECKBOX_SetSkinFlexProps(&Checkbox_Props, CHECKBOX_BI_INACTIV_CHECKED);
//		CHECKBOX_SetSkinFlexProps(&Checkbox_Props, CHECKBOX_BI_ACTIV_CHECKED);
//		CHECKBOX_SetSkinFlexProps(&Checkbox_Props, CHECKBOX_BI_INACTIV_3STATE);
//		CHECKBOX_SetSkinFlexProps(&Checkbox_Props, CHECKBOX_BI_ACTIV_3STATE);
    //		
    hItem = pMsg->hWin;
    WINDOW_SetBkColor(hItem, GUI_BKCOLOR);
    //
    // Initialization of 'Settings_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "Settings");
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    //
    // Initialization of 'OBD_Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_0);
    CHECKBOX_SetText(hItem, "OBD");
    CHECKBOX_SetTextColor(hItem, GUI_BLUE_COLOR);
		CHECKBOX_SetFocusColor(hItem, GUI_GRAY_COLOR);
    CHECKBOX_SetFont(hItem, GUI_FONT_24B_1);
		CHECKBOX_SetState(hItem, Saved_Parameters.OBD_mode);
    //
    // Initialization of 'Temp_Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_1);
    CHECKBOX_SetText(hItem, "Temp");
    CHECKBOX_SetTextColor(hItem, GUI_BLUE_COLOR);
		CHECKBOX_SetFocusColor(hItem, GUI_GRAY_COLOR);		
    CHECKBOX_SetFont(hItem, GUI_FONT_24B_1);
		CHECKBOX_SetState(hItem, Saved_Parameters.Temperature_mode);
    //
    // Initialization of 'Cons_Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_2);
    CHECKBOX_SetText(hItem, "L/h");
    CHECKBOX_SetTextColor(hItem, GUI_BLUE_COLOR);
		CHECKBOX_SetFocusColor(hItem, GUI_GRAY_COLOR);
    CHECKBOX_SetFont(hItem, GUI_FONT_24B_1);
		CHECKBOX_SetState(hItem, Saved_Parameters.Consumption_mode);
    //
    // Initialization of 'Debug_Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_3);
    CHECKBOX_SetText(hItem, "Debug");
    CHECKBOX_SetTextColor(hItem, GUI_BLUE_COLOR);
		CHECKBOX_SetFocusColor(hItem, GUI_GRAY_COLOR);
    CHECKBOX_SetFont(hItem, GUI_FONT_24B_1);
		CHECKBOX_SetState(hItem, Saved_Parameters.Debug_mode);
    //
    // Initialization of 'About_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetText(hItem, "About");
    BUTTON_SetFont(hItem, GUI_FONT_24B_1);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of 'K_Spinbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
    SPINBOX_SetFont(hItem, GUI_FONT_32B_1);
		SPINBOX_SetTextColor(hItem, SPINBOX_CI_ENABLED, GUI_BLUE_COLOR);
		SPINBOX_SetBkColor(hItem, SPINBOX_CI_ENABLED, GUI_GRAY_COLOR );		
		SPINBOX_SetValue(hItem, Saved_Parameters.K);
    //
    // Initialization of 'Main_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetText(hItem, "Main");
    BUTTON_SetFont(hItem, GUI_FONT_24B_1);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of 'Apply_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
    BUTTON_SetText(hItem, "Apply");
    BUTTON_SetFont(hItem, GUI_FONT_24B_1);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of 'Time_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetText(hItem, "Time");
    //
    // Initialization of 'Date_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetText(hItem, "Date");
    //
    // Initialization of 'F_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetText(hItem, "Fuel coefficient");
    //
    // Initialization of 'Britness_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetText(hItem, "Brightness");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
    TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
    TEXT_SetText(hItem, "Other settings");
    // USER START (Optionally insert additional code for further widget initialization)
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_0);
		SLIDER_SetRange(hItem, 15, 100);
		SLIDER_SetValue(hItem, Saved_Parameters.Brightness);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
		sprintf((char *) Data, "Brightness: %d", Saved_Parameters.Brightness);
		TEXT_SetText(hItem, (char *)Data);
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_0);		
		LISTWHEEL_SetFont(hItem, GUI_FONT_32B_1);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_UNSEL, GUI_BKCOLOR);
		LISTWHEEL_SetTextColor(hItem, LISTWHEEL_CI_UNSEL, GUI_BLUE_COLOR);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_SEL, GUI_BKCOLOR);
		LISTWHEEL_SetTextColor(hItem, LISTWHEEL_CI_SEL, GUI_GREEN);
		LISTWHEEL_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    for (uint8_t i = 0; i < 24; i++) {
      sprintf(acBuffer, "%02i", i);
      LISTWHEEL_AddString(hItem, acBuffer);
    }
    LISTWHEEL_SetSnapPosition(hItem, 30);
    LISTWHEEL_SetDeceleration(hItem, 8);
		LISTWHEEL_SetSel(hItem, time.Hours);
		LISTWHEEL_SetPos(hItem, time.Hours);
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_1);		
		LISTWHEEL_SetFont(hItem, GUI_FONT_32B_1);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_UNSEL, GUI_BKCOLOR);
		LISTWHEEL_SetTextColor(hItem, LISTWHEEL_CI_UNSEL, GUI_BLUE_COLOR);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_SEL, GUI_BKCOLOR);
		LISTWHEEL_SetTextColor(hItem, LISTWHEEL_CI_SEL, GUI_GREEN);
		LISTWHEEL_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    for (uint8_t i = 0; i < 60; i++) {
      sprintf(acBuffer, "%02i", i);
      LISTWHEEL_AddString(hItem, acBuffer);
    }
    LISTWHEEL_SetSnapPosition(hItem, 30);
    LISTWHEEL_SetDeceleration(hItem, 8);
		LISTWHEEL_SetSel(hItem, time.Minutes);
		LISTWHEEL_SetPos(hItem, time.Minutes);
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_2);		
		LISTWHEEL_SetFont(hItem, GUI_FONT_32B_1);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_UNSEL, GUI_BKCOLOR);
		LISTWHEEL_SetTextColor(hItem, LISTWHEEL_CI_UNSEL, GUI_BLUE_COLOR);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_SEL, GUI_BKCOLOR);
		LISTWHEEL_SetTextColor(hItem, LISTWHEEL_CI_SEL, GUI_GREEN);
		LISTWHEEL_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		for (uint8_t i = 1; i < 32; i++) {
      sprintf(acBuffer, "%02i", i);
    LISTWHEEL_AddString(hItem, acBuffer);
		}
    LISTWHEEL_SetSnapPosition(hItem, 30);
    LISTWHEEL_SetDeceleration(hItem, 8);
		LISTWHEEL_SetSel(hItem, date.Date - 1);
		LISTWHEEL_SetPos(hItem, date.Date - 1);
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_3);		
		LISTWHEEL_SetFont(hItem, GUI_FONT_32B_1);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_UNSEL, GUI_BKCOLOR);
		LISTWHEEL_SetTextColor(hItem, LISTWHEEL_CI_UNSEL, GUI_BLUE_COLOR);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_SEL, GUI_BKCOLOR);
		LISTWHEEL_SetTextColor(hItem, LISTWHEEL_CI_SEL, GUI_GREEN);
		LISTWHEEL_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		for (uint8_t i = 1; i < 13; i++) {
      sprintf(acBuffer, "%02i", i);
    LISTWHEEL_AddString(hItem, acBuffer);
		}
    LISTWHEEL_SetSnapPosition(hItem, 30);
    LISTWHEEL_SetDeceleration(hItem, 8);
		LISTWHEEL_SetSel(hItem, date.Month - 1);
		LISTWHEEL_SetPos(hItem, date.Month - 1);
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_4);		
		LISTWHEEL_SetFont(hItem, GUI_FONT_32B_1);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_UNSEL, GUI_BKCOLOR);
		LISTWHEEL_SetTextColor(hItem, LISTWHEEL_CI_UNSEL, GUI_BLUE_COLOR);
		LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_SEL, GUI_BKCOLOR);
		LISTWHEEL_SetTextColor(hItem, LISTWHEEL_CI_SEL, GUI_GREEN);
		LISTWHEEL_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		for (uint8_t i = 0; i < 100; i++) {
      sprintf(acBuffer, "20%i", i);
    LISTWHEEL_AddString(hItem, acBuffer);
		}
    LISTWHEEL_SetSnapPosition(hItem, 30);
    LISTWHEEL_SetDeceleration(hItem, 8);
		LISTWHEEL_SetSel(hItem, date.Year);
		LISTWHEEL_SetPos(hItem, date.Year);
		pMsg->MsgId = 0;
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_CHECKBOX_0: // Notifications sent by 'OBD_Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_0);				
				Saved_Parameters.OBD_mode = CHECKBOX_GetState(hItem);
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
				
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_CHECKBOX_1: // Notifications sent by 'Temp_Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_1);				
				Saved_Parameters.Temperature_mode = CHECKBOX_GetState(hItem);
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
				
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_CHECKBOX_2: // Notifications sent by 'Cons_Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_2);				
				Saved_Parameters.Consumption_mode = CHECKBOX_GetState(hItem);
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
				
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_CHECKBOX_3: // Notifications sent by 'Debug_Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_3);				
				Saved_Parameters.Debug_mode = CHECKBOX_GetState(hItem);
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
				
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_0: // Notifications sent by 'About_Button'
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
    case ID_SPINBOX_0: // Notifications sent by 'K_Spinbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_MOVED_OUT:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
				hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_0);
				Saved_Parameters.K = SPINBOX_GetValue(hItem);				
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'Main_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				WM_DeleteWindow(pMsg->hWin);
				hWin = CreateMainWindow();
//				retCode = GUI_ExecCreatedDialog(hWin);
				
//				GUI_EndDialog(CreateSettingsWindow(), 0);
////				WM_DeleteWindow(hWin);
//				hWin = CreateMainWindow();
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_2: // Notifications sent by 'Apply_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				HAL_RTC_SetDate(&hrtc, &date, RTC_FORMAT_BIN);
				HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN);
				
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_LISTWHEEL_0: // Notifications sent by 'Listwheel'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_0);	
				Item = LISTWHEEL_GetPos(hItem);
				LISTWHEEL_SetSel(hItem, Item);
				LISTWHEEL_SetPos(hItem, Item);
				time.Hours = Item;				
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_LISTWHEEL_1: // Notifications sent by 'Listwheel'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_1);	
				Item = LISTWHEEL_GetPos(hItem);
				LISTWHEEL_SetSel(hItem, Item);
				LISTWHEEL_SetPos(hItem, Item);
				time.Minutes = Item;				
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_LISTWHEEL_2: // Notifications sent by 'Listwheel'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_2);	
				Item = LISTWHEEL_GetPos(hItem);
				LISTWHEEL_SetSel(hItem, Item);
				LISTWHEEL_SetPos(hItem, Item);
				date.Date = Item + 1;
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_LISTWHEEL_3: // Notifications sent by 'Listwheel'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_3);	
				Item = LISTWHEEL_GetPos(hItem);
				LISTWHEEL_SetSel(hItem, Item);
				LISTWHEEL_SetPos(hItem, Item);
				date.Month = Item + 1;
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_LISTWHEEL_4: // Notifications sent by 'Listwheel'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
				hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_4);	
				Item = LISTWHEEL_GetPos(hItem);
				LISTWHEEL_SetSel(hItem, Item);
				LISTWHEEL_SetPos(hItem, Item);
				date.Year = Item;
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SLIDER_0: // Notifications sent by 'Slider'
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
				Saved_Parameters.Brightness = SLIDER_GetValue(hItem);
				hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
				sprintf((char *) Data, "Brightness: %d", Saved_Parameters.Brightness);
				TEXT_SetText(hItem, (char *)Data);
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
*       CreateSettingsWindow
*/

WM_HWIN CreateSettingsWindow(void) {
  WM_HWIN hWin;
  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	GuiHandles.hSettingsWindow = hWin;
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
