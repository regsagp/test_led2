
#ifndef __LCD_INCLUDED__
#define __LCD_INCLUDED__

#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include "pins.h"


typedef enum {FALSE = 0, TRUE = !FALSE} bool;


#define BIT_7_MASK    (0x80)
#define BIT_6_MASK    (0x40)
#define BIT_5_MASK    (0x20)
#define BIT_4_MASK    (0x10)
#define BIT_3_MASK    (0x08)
#define BIT_2_MASK    (0x04)
#define BIT_1_MASK    (0x02)
#define BIT_0_MASK    (0x01)


GPIO_InitTypeDef MT_GPIOcfg;

void MT_Init();
void MT_Delay(uint32_t us);
void MT_DataReadWrite();
void MT_FunctionSet8bit();
void MT_FunctionSet4bit(bool N, bool F);
void MT_DisplayOnOff();
void MT_DisplayClear();
void MT_WriteData(uint8_t data);



#endif
