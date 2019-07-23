#include "SSD1963.h"



void SSD1963_Init(void)
{
//	LCD_RESET
//  HAL_Delay(100);
//  LCD_SET
//  HAL_Delay(120);	 

	SSD1963_SendCommand(0x00E2);	//PLL multiplier, set PLL clock to 120M
	SSD1963_SendData(0x0023);	    //N=0x36 for 6.5M, 0x23 for 10M crystal
	SSD1963_SendData(0x0002);
	SSD1963_SendData(0x0004);
	
	SSD1963_SendCommand(0x00E0);  // PLL enable
	SSD1963_SendData(0x0001);
	delay_time(1);
	SSD1963_SendCommand(0x00E0);
	SSD1963_SendData(0x0003);
	delay_time(5);
	SSD1963_SendCommand(0x0001);  // software reset
	delay_time(5);
	SSD1963_SendCommand(0x00E6);	//PLL setting for PCLK, depends on resolution
	SSD1963_SendData(0x0003);
	SSD1963_SendData(0x0033);
	SSD1963_SendData(0x0033);

	//SSD1963_SendData(0x0000);
	//SSD1963_SendData(0x00b4);
	//SSD1963_SendData(0x00e7);


	SSD1963_SendCommand(0x00B0);	//LCD SPECIFICATION
	SSD1963_SendData(0x0000);
	SSD1963_SendData(0x0000);
	SSD1963_SendData((HDP>>8)&0X00FF);  //Set HDP
	SSD1963_SendData(HDP&0X00FF);
  SSD1963_SendData((VDP>>8)&0X00FF);  //Set VDP
	SSD1963_SendData(VDP&0X00FF);
  SSD1963_SendData(0x0000);

	SSD1963_SendCommand(0x00B4);	//HSYNC
	SSD1963_SendData((HT>>8)&0X00FF);  //Set HT
	SSD1963_SendData(HT&0X00FF);
	SSD1963_SendData((HPS>>8)&0X00FF);  //Set HPS
	SSD1963_SendData(HPS&0X00FF);
	SSD1963_SendData(HPW);			   //Set HPW
	SSD1963_SendData((LPS>>8)&0X00FF);  //Set HPS
	SSD1963_SendData(LPS&0X00FF);
	SSD1963_SendData(0x0000);

	SSD1963_SendCommand(0x00B6);	//VSYNC
	SSD1963_SendData((VT>>8)&0X00FF);   //Set VT
	SSD1963_SendData(VT&0X00FF);
	SSD1963_SendData((VPS>>8)&0X00FF);  //Set VPS
	SSD1963_SendData(VPS&0X00FF);
	SSD1963_SendData(VPW);			   //Set VPW
	SSD1963_SendData((FPS>>8)&0X00FF);  //Set FPS
	SSD1963_SendData(FPS&0X00FF);

	SSD1963_SendCommand(0x00BA);
	SSD1963_SendData(0x000F);    //GPIO[3:0] out 1

	SSD1963_SendCommand(0x00B8);
	SSD1963_SendData(0x0007);    //GPIO3=input, GPIO[2:0]=output
	SSD1963_SendData(0x0001);    //GPIO0 normal

	SSD1963_SendCommand(0x0036); //rotation
	SSD1963_SendData(0x0001);
//	SSD1963_SendData(0x0060);


	SSD1963_SendCommand(0x00F0); //pixel data interface
	SSD1963_SendData(0x0003);


	delay_time(5);

//	SSD1963_Clear(0xf800);
	SSD1963_SendCommand(0x0026); //display on
	SSD1963_SendData(0x0001);

	SSD1963_SendCommand(0x0029); //display on

//	SSD1963_SendCommand(0x00BE); //set PWM for B/L
//	SSD1963_SendData(0x0006);
//	//SSD1963_SendData(0x0008);
//	SSD1963_SendData(0x0080);
//	//SSD1963_SendData(0x00f0);
//	
//	SSD1963_SendData(0x0001);
//	SSD1963_SendData(0x00f0);
//	SSD1963_SendData(0x0000);
//	SSD1963_SendData(0x0000);

	SSD1963_SendCommand(0x00d0);
	SSD1963_SendData(0x000d);
}
//void SSD1963_Clear(uint16_t p)
//{
//	uint32_t l = 384000;
//	SSD1963_SendCommand(0x002A);	
//	SSD1963_SendData(0x0000);	    
//	SSD1963_SendData(0x0000);
//	SSD1963_SendData(HDP>>8);	    
//	SSD1963_SendData(HDP&0X00ff);
//  SSD1963_SendCommand(0x002b);	
//	SSD1963_SendData(0x0000);	    
//	SSD1963_SendData(0x0000);
//	SSD1963_SendData(VDP>>8);	    
//	SSD1963_SendData(VDP&0X00ff);
//	SSD1963_SendCommand(0x002c);
//	
//	while(l--)
//	{
//	      
//          	SSD1963_SendData(p);
//		
//	}
//}
void SSD1963_SendCommand(uint16_t command)
{
	*(__IO uint16_t *) (CMD_ADDR)= command;
}
void SSD1963_SendData(uint16_t data)
{
	*(__IO uint16_t *) (DATA_ADDR)= data; 
}
void SSD1963_SetCursorPosition(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	SSD1963_SendCommand(0x002A);	
	SSD1963_SendData(x1 >> 8);	    
	SSD1963_SendData(x1&0x00FF);
	SSD1963_SendData(x2>>8);	    
	SSD1963_SendData(x2&0x00FF);
  SSD1963_SendCommand(0x002b);	
	SSD1963_SendData(y1 >> 8);	    
	SSD1963_SendData(y1&0x00FF);
	SSD1963_SendData(y2>>8);	    
	SSD1963_SendData(y2&0x00FF);
	SSD1963_SendCommand(0x002C);
}
void SSD1963_DrawPixel(uint16_t x, uint16_t y, uint16_t color)
{
	SSD1963_SetCursorPosition(x, y, x, y);
	SSD1963_SendData(color);
}

void SSD1963_DrawVLine(uint16_t xsta, uint16_t ysta, uint16_t yend, uint16_t color)
{
	unsigned int y;

	SSD1963_SetCursorPosition(xsta, ysta, xsta, yend);  		
	y =  ((yend-ysta)+1);
	while(y--)
	{
		*(__IO uint16_t *) (DATA_ADDR)= color; 	
	}
}

void SSD1963_DrawHLine(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t color)
{
	unsigned int y;

	SSD1963_SetCursorPosition(xsta, ysta, xend, ysta);  		
	y =  ((xend-xsta)+1);

	while(y--)
	{
		*(__IO uint16_t *) (DATA_ADDR)= color;  	
	}
}

void SSD1963_DrawLine(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color)
{
    uint16_t x, y, t;	 
	if((xsta==xend)&&(ysta==yend))
		SSD1963_DrawPixel(xsta, ysta, color);
	else if(xsta==xend)
	{
		SSD1963_DrawVLine(xsta,ysta,yend,color);
	}
	else if(ysta==yend)
	{	
		SSD1963_DrawHLine(xsta,ysta,xend,color);
	}
	else{ 
		if(abs(yend-ysta)>abs(xend-xsta))
		{
			if(ysta>yend) 
			{
				t=ysta;
				ysta=yend;
				yend=t; 
				t=xsta;
				xsta=xend;
				xend=t; 
			}
			for(y=ysta;y<yend;y++)
			{
				x = (uint32_t)(y-ysta)*(xend-xsta)/(yend-ysta)+xsta;
				SSD1963_DrawPixel(x, y, color);  
			}
		}
		else
		{
			if(xsta>xend)
			{
				t=ysta;
				ysta=yend;
				yend=t;
				t=xsta;
				xsta=xend;
				xend=t;
			}   
			for(x=xsta;x<=xend;x++)
			{
				y = (uint32_t)(x-xsta)*(yend-ysta)/(xend-xsta)+ysta;
				SSD1963_DrawPixel(x, y, color); 
			}
		}
	} 
}

void SSD1963_DrawCross(uint16_t Xpos,uint16_t Ypos)
{
  SSD1963_DrawLine(Xpos-15,Ypos,Xpos-2,Ypos,0xffff);
  SSD1963_DrawLine(Xpos+2,Ypos,Xpos+15,Ypos,0xffff);
  SSD1963_DrawLine(Xpos,Ypos-15,Xpos,Ypos-2,0xffff);
  SSD1963_DrawLine(Xpos,Ypos+2,Xpos,Ypos+15,0xffff);
}

//void delay_time(unsigned int i)
//{
//    unsigned int a;
//    unsigned int b;
//    for(b=0;b<i;b++)
//    for(a=0;a<1000;a++);
//}

