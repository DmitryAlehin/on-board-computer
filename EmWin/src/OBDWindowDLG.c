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
#define ID_WINDOW_0         (GUI_ID_USER + 0x08)
#define ID_TEXT_0         (GUI_ID_USER + 0x09)
#define ID_TEXT_1         (GUI_ID_USER + 0x0A)
#define ID_TEXT_2         (GUI_ID_USER + 0x0B)
#define ID_BUTTON_0         (GUI_ID_USER + 0x0C)
#define ID_BUTTON_1         (GUI_ID_USER + 0x0D)
#define ID_TEXT_3         (GUI_ID_USER + 0x0E)
#define ID_BUTTON_2         (GUI_ID_USER + 0x0F)


// USER START (Optionally insert additional defines)
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
  { WINDOW_CreateIndirect, "OBDWindow", ID_WINDOW_0, 0, 0, 800, 480, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "OBD_Text", ID_TEXT_0, 270, 50, 260, 50, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Error_Text", ID_TEXT_1, 270, 150, 260, 70, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Transcript_Text", ID_TEXT_2, 270, 245, 260, 70, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Clear_Button", ID_BUTTON_0, 0, 245, 200, 70, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Read_Button", ID_BUTTON_1, 0, 150, 200, 70, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "VIN_Text", ID_TEXT_3, 10, 380, 540, 70, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, "Main_Button", ID_BUTTON_2, 698, 410, 100, 70, 0, 0x0, 0 },
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
    // Initialization of 'OBDWindow'
    //
    hItem = pMsg->hWin;
    WINDOW_SetBkColor(hItem, GUI_BKCOLOR);
    //
    // Initialization of 'OBD_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    TEXT_SetText(hItem, "OBD");
    TEXT_SetTextColor(hItem, GUI_BLUE_COLOR);
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    //
    // Initialization of 'Error_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetText(hItem, "NumError");
    TEXT_SetTextColor(hItem, GUI_RED_COLOR);
    TEXT_SetFont(hItem, GUI_FONT_24B_1);
		TEXT_SetText(hItem, "");
    //
    // Initialization of 'Transcript_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetTextColor(hItem, GUI_RED_COLOR);
    TEXT_SetFont(hItem, GUI_FONT_16B_1);
		TEXT_SetText(hItem, "");
    //
    // Initialization of 'Clear_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetText(hItem, "Clear Errors");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of 'Read_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetText(hItem, "Read Errors");
    BUTTON_SetFont(hItem, GUI_FONT_32B_1);
		BUTTON_SetFocussable(hItem, 0);
    //
    // Initialization of 'VIN_Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetTextColor(hItem, GUI_GREEN);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
		sprintf((char *)Data, "VIN Number:%s", CarParameters.VIN_NUMBER);
		TEXT_SetText(hItem, (char *)Data);
    //
    // Initialization of 'Main_Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
    BUTTON_SetText(hItem, "Main");
		BUTTON_SetFont(hItem, GUI_FONT_24B_1);
		BUTTON_SetFocussable(hItem, 0);
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'Clear_Button'
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
    case ID_BUTTON_1: // Notifications sent by 'Read_Button'
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
    case ID_BUTTON_2: // Notifications sent by 'Main_Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
//				GUI_EndDialog(CreateOBDWindow(), 0);
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
*       CreateOBDWindow
*/

WM_HWIN CreateOBDWindow(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	GuiHandles.hOBDWindow = hWin;
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
