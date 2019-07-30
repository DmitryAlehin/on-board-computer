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
#define ID_BUTTON_0         (GUI_ID_USER + 0x01)
#define ID_BUTTON_1         (GUI_ID_USER + 0x02)
#define ID_BUTTON_2         (GUI_ID_USER + 0x03)
#define ID_TEXT_0         (GUI_ID_USER + 0x04)
#define ID_TEXT_1         (GUI_ID_USER + 0x05)
#define ID_TEXT_2         (GUI_ID_USER + 0x06)
#define ID_TEXT_3         (GUI_ID_USER + 0x07)
#define ID_TEXT_4         (GUI_ID_USER + 0x08)
#define ID_TEXT_5         (GUI_ID_USER + 0x09)
#define ID_TEXT_6         (GUI_ID_USER + 0x0A)

// USER START (Optionally insert additional defines)
RTC_TimeTypeDef time;
RTC_DateTypeDef date;
GUIHandles GuiHandles;
extern TnP Temp_Pres;
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
  { WINDOW_CreateIndirect, "MainWindow", ID_WINDOW_0, 0, 0, 800, 480, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "SETTINGS_Button", ID_BUTTON_0, 0, 325, 170, 155, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "OBDII_Button", ID_BUTTON_1, 0, 162, 170, 155, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "AUDIO_Button", ID_BUTTON_2, 0, 0, 170, 155, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Time_Text", ID_TEXT_0, 340, 110, 260, 90, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Date_Text", ID_TEXT_1, 340, 220, 260, 30, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Temperature_Text", ID_TEXT_2, 450, 320, 340, 50, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Fuel_Text", ID_TEXT_3, 510, 430, 110, 40, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Vbat_Text", ID_TEXT_4, 220, 430, 110, 40, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "F_Text", ID_TEXT_5, 350, 430, 160, 40, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Temp_Engine_Text", ID_TEXT_6, 620, 430, 110, 40, 0, 0x64, 0 },
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
	BUTTON_SKINFLEX_PROPS    	Props;
	SLIDER_SKINFLEX_PROPS  Slider_Props;
	BUTTON_SetDefaultFont(GUI_FONT_32B_1);
	BUTTON_SetDefaultTextColor(GUI_BLUE_COLOR,BUTTON_SKINFLEX_PI_ENABLED);
	BUTTON_SetDefaultTextColor(GUI_BLUE_COLOR,BUTTON_SKINFLEX_PI_FOCUSSED);
	BUTTON_SetDefaultTextColor(GUI_BLUE_COLOR,BUTTON_SKINFLEX_PI_PRESSED);
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'MainWindow'
		
		BUTTON_GetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_PRESSED);
		Props.aColorFrame[0] = GUI_GRAY_COLOR;
		Props.aColorFrame[1] = GUI_GRAY_COLOR;
		Props.aColorLower[0] = GUI_GRAY_COLOR;
		Props.aColorLower[1] = GUI_GRAY_COLOR;
		Props.aColorUpper[0] = GUI_GRAY_COLOR;
		Props.aColorUpper[1] = GUI_GRAY_COLOR;
		Props.Radius = 0;
		BUTTON_SetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_PRESSED);		
		BUTTON_SetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_FOCUSSED);		
		Props.aColorFrame[0] = GUI_BLUE_COLOR;
		Props.aColorFrame[1] = GUI_BLUE_COLOR;		
		BUTTON_SetSkinFlexProps(&Props, BUTTON_SKINFLEX_PI_ENABLED);
		
		SLIDER_GetSkinFlexProps(&Slider_Props, SLIDER_SKINFLEX_PI_PRESSED);
		Slider_Props.aColorFrame[0] = GUI_BLUE_COLOR;
		Slider_Props.aColorFrame[1] = GUI_BLUE_COLOR;
		Slider_Props.ColorFocus = GUI_GRAY_COLOR;
		Slider_Props.ColorTick = GUI_BLUE_COLOR;
		Slider_Props.aColorInner[0] = GUI_BLUE_COLOR;
		Slider_Props.aColorInner[1] = GUI_BLUE_COLOR;
		Slider_Props.aColorShaft[0] = GUI_BLUE_COLOR;
		Slider_Props.aColorShaft[1] = GUI_BLUE_COLOR;
		SLIDER_SetSkinFlexProps(&Slider_Props, SLIDER_SKINFLEX_PI_PRESSED);
		SLIDER_SetSkinFlexProps(&Slider_Props, SLIDER_SKINFLEX_PI_UNPRESSED);
		
    //
    hItem = pMsg->hWin;
    WINDOW_SetBkColor(hItem, GUI_BKCOLOR);
    //
    // Initialization of 'SETTINGS_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetText(hItem, "SETTINGS");
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of 'OBDII_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetText(hItem, "OBDII");
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of 'AUDIO_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
    BUTTON_SetText(hItem, "AUDIO");
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of 'Time_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_D64);
    //
    // Initialization of 'Date_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    //
    // Initialization of 'Temperature_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
		TEXT_SetFont(hItem, GUI_FONT_32B_1);
		TEXT_SetText(hItem, "");  
    //
    // Initialization of 'Fuel_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
		TEXT_SetFont(hItem, GUI_FONT_32B_1);
		TEXT_SetText(hItem, "");
    //
    // Initialization of 'Vbat_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    //
    // Initialization of 'F_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
		//
    // Initialization of 'Temp_Engine_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetTextColor(hItem, GUI_RED_COLOR);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    // USER START (Optionally insert additional code for further widget initialization)
//		LCD_Brightness(Saved_Parameters.Brightness);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
		HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
		sprintf((char *)Data, "%02d:%02d", time.Hours, time.Minutes);
		TEXT_SetText(hItem, (char *)Data);
		HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);
		RTC_Fix_Date(&date);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
		sprintf((char *)Data, "%02d.%02d.20%02d", date.Date, date.Month, date.Year);
		TEXT_SetText(hItem, (char *)Data);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
		if(CarParameters.VSS != 0)
		{
			sprintf((char *)Data, "%.1f L/100km", Saved_Parameters.Average_consumption);
			TEXT_SetText(hItem, (char *)Data);
		}
		else
		{
			sprintf((char *)Data, "%.1f L/h", Car_Param.LH_consumption);
			TEXT_SetText(hItem, (char *)Data);
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
		sprintf((char *)Data, "%.1f V", Car_Param.Voltage);
		TEXT_SetText(hItem, (char *)Data);
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
		if(Saved_Parameters.Consumption_mode)
		{			
			sprintf((char *)Data, "%.1f L", Car_Param.FUEL_Liters);
			TEXT_SetText(hItem, (char *)Data);
		}
		else
		{
			sprintf((char *)Data, "%.1f%c", Car_Param.FUEL, 37);
			TEXT_SetText(hItem, (char *)Data);
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
		if(Car_Param.ECT >108.0f)
		{			
			sprintf((char *)Data, "%.1f %cC", Car_Param.ECT, 176);
			TEXT_SetText(hItem, (char *)Data);
		}
		else	
		{						
			TEXT_SetText(hItem, "");
		}						
		pMsg->MsgId = 0;
    // USER END
    break;
		
	case WM_UPDATE_MIN:
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
		HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
		sprintf((char *)Data, "%02d:%02d", time.Hours, time.Minutes);
		TEXT_SetText(hItem, (char *)Data);
		HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);
		RTC_Fix_Date(&date);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
		sprintf((char *)Data, "%02d.%02d.20%02d", date.Date, date.Month, date.Year);
		TEXT_SetText(hItem, (char *)Data);
		pMsg->MsgId = 0;
		break;
	
	case WM_UPDATE_CAR:
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
		if(CarParameters.VSS == 0)
		{
			sprintf((char *)Data, "%.1f L/100km", Saved_Parameters.Average_consumption);
			TEXT_SetText(hItem, (char *)Data);
		}
		else
		{
			sprintf((char *)Data, "%.1f L/h", Car_Param.LH_consumption);
			TEXT_SetText(hItem, (char *)Data);
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
		sprintf((char *)Data, "%.1f V", Car_Param.Voltage);
		TEXT_SetText(hItem, (char *)Data);
		
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
		if(!Saved_Parameters.Consumption_mode)
		{			
			sprintf((char *)Data, "%.1f L", Car_Param.FUEL_Liters);
			TEXT_SetText(hItem, (char *)Data);
		}
		else
		{
			sprintf((char *)Data, "%.1f%c", Car_Param.FUEL, 37);
			TEXT_SetText(hItem, (char *)Data);
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
		if(Car_Param.ECT >108.0f)
		{			
			sprintf((char *)Data, "%.1f %cC", Car_Param.ECT, 176);
			TEXT_SetText(hItem, (char *)Data);
		}
		else	
		{						
			TEXT_SetText(hItem, "");
		}			
		pMsg->MsgId = 0;
		break;
	case WM_UPDATE_METEO:		
		//вывод температуры
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
		if((Temp_Pres.Temperature >= 22.0f) &&(Temp_Pres.Temperature <= 25.0f))
		{
			TEXT_SetTextColor(hItem, GUI_DARKGREEN);
		}
		if(Temp_Pres.Temperature > 25.0f)
		{
			TEXT_SetTextColor(hItem, GUI_RED_COLOR);
		}
		if(Temp_Pres.Temperature < 22.0f)
		{
			TEXT_SetTextColor(hItem, GUI_BLUE);
		}
		sprintf((char *)Data, "%.1f %cC, %.1f mm Hg", Temp_Pres.Temperature, 176, Temp_Pres.Pressure);
		TEXT_SetText(hItem, (char *)Data);		   
		pMsg->MsgId = 0;
		break;
				
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'SETTINGS_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				WM_DeleteWindow(pMsg->hWin);
				hWin = CreateSettingsWindow();
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'OBDII_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				WM_DeleteWindow(pMsg->hWin);
				hWin = CreateOBDWindow();
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_2: // Notifications sent by 'AUDIO_Button'
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
*       CreateMainWindow
*/

WM_HWIN CreateMainWindow(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	GuiHandles.hMainWindow = hWin;
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
