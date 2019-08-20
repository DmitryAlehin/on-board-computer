/* Includes ------------------------------------------------------------------*/
#include "TouchPanel.h"
#include "spi.h"
#include "GUI.h"

/* Private variables ---------------------------------------------------------*/
Matrix matrix ;
Coordinate  display ;

/* DisplaySample */
Coordinate ScreenSample[3];
Coordinate DisplaySample[3] =   {
                      { 45, 45 }, 
											{ 755 , 240},
                      { 400, 400}
	                            } ;

/* Private define ------------------------------------------------------------*/
#define THRESHOLD 300

void TP_GetAdXY(int *x,int *y)  
{ 
	unsigned int buff = 0;
	unsigned char cmd, temp;
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
  cmd = CHX;
HAL_SPI_TransmitReceive(&hspi2, &cmd, (uint8_t *) &temp, 1, 3000); 
HAL_Delay(1); 

cmd  = 0;
temp = 0;
	
HAL_SPI_TransmitReceive(&hspi2, &cmd, (uint8_t *) &temp, 1, 3000);
  buff = temp<<4; 
	cmd = CHY;
HAL_SPI_TransmitReceive(&hspi2, &cmd, (uint8_t *) &temp, 1, 3000);
HAL_Delay(1); 
  buff |= temp>>4; 
  *x= ((buff >>4)) ;
buff = 0;	
cmd = 0;
HAL_SPI_TransmitReceive(&hspi2, &cmd, (uint8_t *) &temp, 1, 3000);
  buff = temp<<4; 
HAL_SPI_TransmitReceive(&hspi2, &cmd, (uint8_t *) &temp, 1, 3000);
  buff |= temp>>4; 
  *y= ((buff >> 4)) ; 
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
}
Coordinate *Read_Ads7846(void)
{
  static Coordinate  screen;
  int m0,m1,m2,TP_X[1],TP_Y[1],temp[3];
  uint8_t count=0;
  int buffer[2][9]={{0},{0}};  
  
  do	
  {		   
    TP_GetAdXY(TP_X,TP_Y);  
	buffer[0][count]=TP_X[0];  
	buffer[1][count]=TP_Y[0];
	count++;  
  }
  while(!T_IRQ && count<9);
  if(count==9)
  {      
    temp[0]=(buffer[0][0]+buffer[0][1]+buffer[0][2])/3;
	temp[1]=(buffer[0][3]+buffer[0][4]+buffer[0][5])/3;
	temp[2]=(buffer[0][6]+buffer[0][7]+buffer[0][8])/3;

	m0=temp[0]-temp[1];
	m1=temp[1]-temp[2];
	m2=temp[2]-temp[0];

	m0=m0>0?m0:(-m0);
    m1=m1>0?m1:(-m1);
	m2=m2>0?m2:(-m2);
	
	if( m0>THRESHOLD  &&  m1>THRESHOLD  &&  m2>THRESHOLD ) return 0;
	   
	if(m0<m1)
	{
	  if(m2<m0) 
	    screen.x=(temp[0]+temp[2])/2;
	  else 
	    screen.x=(temp[0]+temp[1])/2;	
	}
	else if(m2<m1) 
	  screen.x=(temp[0]+temp[2])/2;
	else 
	  screen.x=(temp[1]+temp[2])/2;
	
  temp[0]=(buffer[1][0]+buffer[1][1]+buffer[1][2])/3; 
	temp[1]=(buffer[1][3]+buffer[1][4]+buffer[1][5])/3; 
	temp[2]=(buffer[1][6]+buffer[1][7]+buffer[1][8])/3; 
	m0=temp[0]-temp[1];
	m1=temp[1]-temp[2];
	m2=temp[2]-temp[0];
	m0=m0>0?m0:(-m0);
	m1=m1>0?m1:(-m1);
	m2=m2>0?m2:(-m2);	
	if(m0>THRESHOLD&&m1>THRESHOLD&&m2>THRESHOLD) return 0;
	if(m0<m1)
	{
	  if(m2<m0) 
	    screen.y=(temp[0]+temp[2])/2;
	  else 
	    screen.y=(temp[0]+temp[1])/2;	
    }
	else if(m2<m1) 
	   screen.y=(temp[0]+temp[2])/2;
	else
	   screen.y=(temp[1]+temp[2])/2;

	return &screen;
  }  
  return 0; 
}

FunctionalState setCalibrationMatrix( Coordinate * displayPtr,
                          Coordinate * screenPtr,
                          Matrix * matrixPtr)
{

  FunctionalState retTHRESHOLD = ENABLE ;
  matrixPtr->Divider = ((screenPtr[0].x - screenPtr[2].x) * (screenPtr[1].y - screenPtr[2].y)) - 
                       ((screenPtr[1].x - screenPtr[2].x) * (screenPtr[0].y - screenPtr[2].y)) ;
	
  if( matrixPtr->Divider == 0 )
  {
    retTHRESHOLD = DISABLE;
  }
  else
  {
    matrixPtr->An = ((displayPtr[0].x - displayPtr[2].x) * (screenPtr[1].y - screenPtr[2].y)) - 
                    ((displayPtr[1].x - displayPtr[2].x) * (screenPtr[0].y - screenPtr[2].y)) ;
    matrixPtr->Bn = ((screenPtr[0].x - screenPtr[2].x) * (displayPtr[1].x - displayPtr[2].x)) - 
                    ((displayPtr[0].x - displayPtr[2].x) * (screenPtr[1].x - screenPtr[2].x)) ;
    matrixPtr->Cn = (screenPtr[2].x * displayPtr[1].x - screenPtr[1].x * displayPtr[2].x) * screenPtr[0].y +
                    (screenPtr[0].x * displayPtr[2].x - screenPtr[2].x * displayPtr[0].x) * screenPtr[1].y +
                    (screenPtr[1].x * displayPtr[0].x - screenPtr[0].x * displayPtr[1].x) * screenPtr[2].y ;
    matrixPtr->Dn = ((displayPtr[0].y - displayPtr[2].y) * (screenPtr[1].y - screenPtr[2].y)) - 
                    ((displayPtr[1].y - displayPtr[2].y) * (screenPtr[0].y - screenPtr[2].y)) ;
    matrixPtr->En = ((screenPtr[0].x - screenPtr[2].x) * (displayPtr[1].y - displayPtr[2].y)) - 
                    ((displayPtr[0].y - displayPtr[2].y) * (screenPtr[1].x - screenPtr[2].x)) ;
    matrixPtr->Fn = (screenPtr[2].x * displayPtr[1].y - screenPtr[1].x * displayPtr[2].y) * screenPtr[0].y +
                    (screenPtr[0].x * displayPtr[2].y - screenPtr[2].x * displayPtr[0].y) * screenPtr[1].y +
                    (screenPtr[1].x * displayPtr[0].y - screenPtr[0].x * displayPtr[1].y) * screenPtr[2].y ;
  }
  return( retTHRESHOLD ) ;
}

FunctionalState getDisplayPoint(Coordinate * displayPtr,
                     Coordinate * screenPtr,
                     Matrix * matrixPtr )
{
  FunctionalState retTHRESHOLD =ENABLE ;

  if( matrixPtr->Divider != 0 )
  {      
    displayPtr->x = ( (matrixPtr->An * screenPtr->x) + 
                      (matrixPtr->Bn * screenPtr->y) + 
                       matrixPtr->Cn 
                    ) / matrixPtr->Divider ;      
    displayPtr->y = ( (matrixPtr->Dn * screenPtr->x) + 
                      (matrixPtr->En * screenPtr->y) + 
                       matrixPtr->Fn 
                    ) / matrixPtr->Divider ;
	
  }
  else
  {
    retTHRESHOLD = DISABLE;
  }
	
  return(retTHRESHOLD);
} 

void GetPoint_TS  (uint16_t *x, uint16_t *y)
{
	Matrix * matrixPtr;
	Coordinate * displayPtr;
	Coordinate * screenPtr;

  if( matrixPtr->Divider != 0 )
  {       
    displayPtr->x = ( (matrixPtr->An * screenPtr->x) + 
                      (matrixPtr->Bn * screenPtr->y) + 
                       matrixPtr->Cn 
                    ) / matrixPtr->Divider ;    
    displayPtr->y = ( (matrixPtr->Dn * screenPtr->x) + 
                      (matrixPtr->En * screenPtr->y) + 
                       matrixPtr->Fn 
                    ) / matrixPtr->Divider ;

  }

}

void TouchPanel_Calibrate(void)
{
  uint8_t i;
  Coordinate * Ptr;

	

  for(i=0;i<3;i++)
  {
//		SSD1963_Clear(BLACK);	
		SSD1963_DrawCross(DisplaySample[i].x,DisplaySample[i].y);
		do
		{
			Ptr=Read_Ads7846();
		}
		while( Ptr == (void*)0 );
		ScreenSample[i].x= Ptr->x; ScreenSample[i].y= Ptr->y;		
  	HAL_Delay(500);
  }
  setCalibrationMatrix( &DisplaySample[0],&ScreenSample[0],&matrix );
} 

void Touch_Cal_Read (Matrix * matrixPtr)
{
	matrixPtr->An = 44375;
	matrixPtr->Bn = -355;
	matrixPtr->Cn = -131900;
	matrixPtr->Dn = -430;
	matrixPtr->En = 27970;
	matrixPtr->Fn = -193700;
	matrixPtr->Divider = 6788;

}	

void Touch_Update ( void )
{
  GUI_PID_STATE TS_State;

  getDisplayPoint(&display, Read_Ads7846(), &matrix );
	TS_State.Pressed = isTouch();
  TS_State.x = display.x;
  TS_State.y = display.y;  
  TS_State.Layer = 0;
  GUI_TOUCH_StoreStateEx (&TS_State);
}


bool isTouch(void)
{
	if(!T_IRQ)
	{
		return true;
	}
	else
	{
		return false;
	}
}
