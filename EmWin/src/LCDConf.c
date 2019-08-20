/*********************************************************************
*          Portions COPYRIGHT 2016 STMicroelectronics                *
*          Portions SEGGER Microcontroller GmbH & Co. KG             *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2015  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.32 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The  software has  been licensed  to STMicroelectronics International
N.V. a Dutch company with a Swiss branch and its headquarters in Plan-
les-Ouates, Geneva, 39 Chemin du Champ des Filles, Switzerland for the
purposes of creating libraries for ARM Cortex-M-based 32-bit microcon_
troller products commercialized by Licensee only, sublicensed and dis_
tributed under the terms and conditions of the End User License Agree_
ment supplied by STMicroelectronics International N.V.
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LCDConf_FlexColor_Template.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

/**
  ******************************************************************************
  * @attention
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#include "GUI.h"
#include "GUIDRV_FlexColor.h"


/*********************************************************************
*
*       Layer configuration (to be modified)
*
**********************************************************************
*/

//
// Physical display size
//
#define XSIZE_PHYS  800 // To be adapted to x-screen size
#define YSIZE_PHYS  480 // To be adapted to y-screen size

#define DATA_ADDR    ((uint32_t)(CMD_ADDR+(2<<18)))    //disp Data ADDR
#define CMD_ADDR    ((uint32_t)0x60000000)	 //disp Reg ADDR 

#define HDP 799
#define HT 900
#define HPS 5
#define LPS 5
#define HPW 5
#define VDP 479
#define VT 530
#define VPS 5
#define FPS 5
#define VPW 5

/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   VXSIZE_PHYS
  #define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
  #define VYSIZE_PHYS YSIZE_PHYS
#endif
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   GUICC_565
  #error Color conversion not defined!
#endif
#ifndef   GUIDRV_FLEXCOLOR
  #error No display driver defined!
#endif

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/
/********************************************************************
*
*       LcdWriteReg
*
* Function description:
*   Sets display register
*/
static void LcdWriteReg(U16 Data) 
{
  *(__IO uint16_t *) (CMD_ADDR)= Data;
}

/********************************************************************
*
*       LcdWriteData
*
* Function description:
*   Writes a value to a display register
*/
static void LcdWriteData(U16 Data) 
{
  *(__IO uint16_t *) (DATA_ADDR)= Data;
}

/********************************************************************
*
*       LcdWriteDataMultiple
*
* Function description:
*   Writes multiple values to a display register.
*/
static void LcdWriteDataMultiple(U16 * pData, int NumItems) 
{
  while (NumItems--) 
	{
    *(__IO uint16_t *) DATA_ADDR= *pData;
		pData++;
  }
}

/********************************************************************
*
*       LcdReadDataMultiple
*
* Function description:
*   Reads multiple values from a display register.
*/
static void LcdReadDataMultiple(U16 * pData, int NumItems) 
{
  while (NumItems--) 
	{
    *pData = *(__IO uint16_t *) DATA_ADDR;
		pData++;
  }
}

/*********************************************************************
*
*       Public functions
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_Config
*
* Function description:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*
*/
void LCD_X_Config(void) {
  GUI_DEVICE * pDevice;
  CONFIG_FLEXCOLOR Config = {0};
  GUI_PORT_API PortAPI = {0};
  //
  // Set display driver and color conversion
  //
  pDevice = GUI_DEVICE_CreateAndLink(GUIDRV_FLEXCOLOR, GUICC_M565, 0, 0);
  //
  // Display driver configuration, required for Lin-driver
  //
  LCD_SetSizeEx (0, XSIZE_PHYS , YSIZE_PHYS);
  LCD_SetVSizeEx(0, VXSIZE_PHYS, VYSIZE_PHYS);
  //
  // Orientation
  //
	
	Config.Orientation = GUI_MIRROR_Y;
	Config.FirstCOM = 0x01;
	Config.FirstSEG = 0x02;
  GUIDRV_FlexColor_Config(pDevice, &Config);
  //
  // Set controller and operation mode
  //
  PortAPI.pfWrite16_A0  = LcdWriteReg;
  PortAPI.pfWrite16_A1  = LcdWriteData;
  PortAPI.pfWriteM16_A1 = LcdWriteDataMultiple;
  PortAPI.pfReadM16_A1  = LcdReadDataMultiple;
  GUIDRV_FlexColor_SetReadFunc66720_B16(pDevice, GUIDRV_FLEXCOLOR_IF_TYPE_II);
	GUIDRV_FlexColor_SetFunc ( pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66720, GUIDRV_FLEXCOLOR_M16C0B16 );
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Function description:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;
  (void) LayerIndex;
  (void) pData;
  
  switch (Cmd) {
  case LCD_X_INITCONTROLLER: 
		{
			delay_time(10);
			LcdWriteReg(0x00E2);	//PLL multiplier, set PLL clock to 120M
			LcdWriteData(0x0023);	    //N=0x36 for 6.5M, 0x23 for 10M crystal
			LcdWriteData(0x0002);
			LcdWriteData(0x0004);
			
			LcdWriteReg(0x00E0);  // PLL enable
			LcdWriteData(0x0001);
			delay_time(1);
			LcdWriteReg(0x00E0);
			LcdWriteData(0x0003);
			delay_time(5);
			LcdWriteReg(0x0001);  // software reset
			delay_time(5);
			LcdWriteReg(0x00E6);	//PLL setting for PCLK, depends on resolution
			LcdWriteData(0x0003);
			LcdWriteData(0x0033);
			LcdWriteData(0x0033);

			LcdWriteReg(0x00B0);	//LCD SPECIFICATION
			LcdWriteData(0x0000);
			LcdWriteData(0x0000);
			LcdWriteData((HDP>>8)&0X00FF);  //Set HDP
			LcdWriteData(HDP&0X00FF);
			LcdWriteData((VDP>>8)&0X00FF);  //Set VDP
			LcdWriteData(VDP&0X00FF);
			LcdWriteData(0x0000);

			LcdWriteReg(0x00B4);	//HSYNC
			LcdWriteData((HT>>8)&0X00FF);  //Set HT
			LcdWriteData(HT&0X00FF);
			LcdWriteData((HPS>>8)&0X00FF);  //Set HPS
			LcdWriteData(HPS&0X00FF);
			LcdWriteData(HPW);			   //Set HPW
			LcdWriteData((LPS>>8)&0X00FF);  //Set HPS
			LcdWriteData(LPS&0X00FF);
			LcdWriteData(0x0000);

			LcdWriteReg(0x00B6);	//VSYNC
			LcdWriteData((VT>>8)&0X00FF);   //Set VT
			LcdWriteData(VT&0X00FF);
			LcdWriteData((VPS>>8)&0X00FF);  //Set VPS
			LcdWriteData(VPS&0X00FF);
			LcdWriteData(VPW);			   //Set VPW
			LcdWriteData((FPS>>8)&0X00FF);  //Set FPS
			LcdWriteData(FPS&0X00FF);

			LcdWriteReg(0x00BA);
			LcdWriteData(0x000F);    //GPIO[3:0] out 1

			LcdWriteReg(0x00B8);
			LcdWriteData(0x0007);    //GPIO3=input, GPIO[2:0]=output
			LcdWriteData(0x0001);    //GPIO0 normal

			LcdWriteReg(0x0036); //rotation
			LcdWriteData(0x0001);
			
			LcdWriteReg(0x00F0); //pixel data interface
			LcdWriteData(0x0003);


			delay_time(5);
			LcdWriteReg(0x0026); //display on
			LcdWriteData(0x0001);

			LcdWriteReg(0x0029); //display on

			LcdWriteReg(0x00BE); //set PWM for B/L
			
			LcdWriteData(0x0008);
			LcdWriteData(0x0080);
			
			LcdWriteData(0x0001);
			
			LcdWriteReg(0x00d0);
			LcdWriteData(0x000d);
    return 0;
  }
  default:
    r = -1;
  }
  return r;
}

void delay_time(unsigned int i)
{
    unsigned int a;
    unsigned int b;
    for(b=0;b<i;b++)
    for(a=0;a<1000;a++);
}

void LCD_Clear(uint16_t p)
{
	uint32_t l = 384000;
	LcdWriteReg(0x002A);	
	LcdWriteData(0x0000);	    
	LcdWriteData(0x0000);
	LcdWriteData(HDP>>8);	    
	LcdWriteData(HDP&0X00ff);
  LcdWriteReg(0x002b);	
	LcdWriteData(0x0000);	    
	LcdWriteData(0x0000);
	LcdWriteData(VDP>>8);	    
	LcdWriteData(VDP&0X00ff);
	LcdWriteReg(0x002c);
	
	while(l--)
	{
	      
          	LcdWriteData(p);
		
	}
}

void LCD_Brightness(uint8_t Brightness)
{
	uint16_t Br = 0x0000;
	Br |= Brightness;
	LcdWriteReg(0x00BE);
	LcdWriteData(0x0008);
	LcdWriteData(Br);
	LcdWriteData(0x0001);
}

/*************************** End of file ****************************/

