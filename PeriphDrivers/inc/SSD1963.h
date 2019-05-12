#ifndef SSD1963_H
#define SSD1963_H


#include "stm32f4xx.h"
#include "stdlib.h"

#define LCD_SET       HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);         // 1 на вывод reset дисплея
#define LCD_RESET     HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);       // 0 на вывод reset

#define DATA_ADDR    ((uint32_t)(CMD_ADDR+(2<<18)))    //disp Data ADDR
#define CMD_ADDR    ((uint32_t)0x60000000)	 //disp Reg ADDR
extern char array [100]; 
/*------------Замена цвета---------------*/
                                              
#define BLACK           0x0000      /*   0,   0,   0 */
#define NAVY            0x000F      /*   0,   0, 128 */
#define DGREEN          0x03E0      /*   0, 128,   0 */
#define DCYAN           0x03EF      /*   0, 128, 128 */
#define MAROON          0x7800      /* 128,   0,   0 */
#define PURPLE          0x780F      /* 128,   0, 128 */
#define OLIVE           0x7BE0      /* 128, 128,   0 */
#define LGRAY           0xC618      /* 192, 192, 192 */
#define DGRAY           0x7BEF      /* 128, 128, 128 */
#define BLUE            0x001F      /*   0,   0, 255 */
#define GREEN           0x07E0      /*   0, 255,   0 */
#define CYAN            0x07FF      /*   0, 255, 255 */
#define RED             0xF800      /* 255,   0,   0 */
#define MAGENTA         0xF81F      /* 255,   0, 255 */
#define YELLOW          0xFFE0      /* 255, 255,   0 */
#define WHITE           0xFFFF      /* 255, 255, 255 */
#define ORANGE          0xFD20      /* 255, 165,   0 */
#define GREENYELLOW     0xAFE5      /* 173, 255,  47 */
#define BROWN 			     0XBC40 //
#define BRRED 			     0XFC07 //


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

void SSD1963_Init(void);
//void SSD1963_Clear(uint16_t p);
void SSD1963_SendCommand(uint16_t com);
void SSD1963_SendData(uint16_t data);
void SSD1963_SetCursorPosition(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void SSD1963_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void SSD1963_DrawVLine(uint16_t xsta, uint16_t ysta, uint16_t yend, uint16_t color);
void SSD1963_DrawHLine(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t color);
void SSD1963_DrawLine(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color);
void SSD1963_DrawCross(uint16_t Xpos,uint16_t Ypos);
void delay_time(unsigned int i);
#endif 
