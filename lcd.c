// http://microtechnics.ru/rabota-s-displeem-na-baze-hd44780/
#if 00000
#include "lcd.h"

//**************************************************************************************************
void MT_Init()
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    // Initialize all pins connected to the WH1602 module

    GPIO_StructInit(&MT_GPIOcfg);
    MT_GPIOcfg.GPIO_Pin = MT_WH1602_RS_PIN;
    MT_GPIOcfg.GPIO_Mode = GPIO_Mode_OUT;
    MT_GPIOcfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MT_WH1602_RS_PORT, &MT_GPIOcfg);

    GPIO_StructInit(&MT_GPIOcfg);
    MT_GPIOcfg.GPIO_Pin = MT_WH1602_RW_PIN;
    MT_GPIOcfg.GPIO_Mode = GPIO_Mode_OUT;
    MT_GPIOcfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MT_WH1602_RW_PORT, &MT_GPIOcfg);

    GPIO_StructInit(&MT_GPIOcfg);
    MT_GPIOcfg.GPIO_Pin = MT_WH1602_E_PIN;
    MT_GPIOcfg.GPIO_Mode = GPIO_Mode_OUT;
    MT_GPIOcfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MT_WH1602_E_PORT, &MT_GPIOcfg);

    GPIO_StructInit(&MT_GPIOcfg);
    MT_GPIOcfg.GPIO_Pin = MT_WH1602_DB7_PIN;
    MT_GPIOcfg.GPIO_Mode = GPIO_Mode_OUT;
    MT_GPIOcfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MT_WH1602_DB7_PORT, &MT_GPIOcfg);

    GPIO_StructInit(&MT_GPIOcfg);
    MT_GPIOcfg.GPIO_Pin = MT_WH1602_DB6_PIN;
    MT_GPIOcfg.GPIO_Mode = GPIO_Mode_OUT;
    MT_GPIOcfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MT_WH1602_DB6_PORT, &MT_GPIOcfg);

    GPIO_StructInit(&MT_GPIOcfg);
    MT_GPIOcfg.GPIO_Pin = MT_WH1602_DB5_PIN;
    MT_GPIOcfg.GPIO_Mode = GPIO_Mode_OUT;
    MT_GPIOcfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MT_WH1602_DB5_PORT, &MT_GPIOcfg);

    GPIO_StructInit(&MT_GPIOcfg);
    MT_GPIOcfg.GPIO_Pin = MT_WH1602_DB4_PIN;
    MT_GPIOcfg.GPIO_Mode = GPIO_Mode_OUT;
    MT_GPIOcfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MT_WH1602_DB4_PORT, &MT_GPIOcfg);
}


//**************************************************************************************************
// Функция для реализации задержки
void MT_Delay(uint32_t us)
{
    volatile uint32_t i;
    RCC_ClocksTypeDef rcc;

    RCC_GetClocksFreq (&rcc);
    i = (rcc.HCLK_Frequency/10000000)*us;

    for (; i != 0; i--);
}

// Строб импульс
void MT_DataReadWrite()
{
    GPIO_SetBits(MT_WH1602_E_PORT, MT_WH1602_E_PIN);
    MT_Delay(2);
    GPIO_ResetBits(MT_WH1602_E_PORT, MT_WH1602_E_PIN);
}

// И наконец функции для инициализации дисплея
void MT_FunctionSet8bit()
{
    GPIO_ResetBits(MT_WH1602_RS_PORT, MT_WH1602_RS_PIN);
    GPIO_ResetBits(MT_WH1602_RW_PORT, MT_WH1602_RW_PIN);
    GPIO_ResetBits(MT_WH1602_DB7_PORT, MT_WH1602_DB7_PIN);
    GPIO_ResetBits(MT_WH1602_DB6_PORT, MT_WH1602_DB6_PIN);
    GPIO_SetBits(MT_WH1602_DB5_PORT, MT_WH1602_DB5_PIN);
    GPIO_SetBits(MT_WH1602_DB4_PORT, MT_WH1602_DB4_PIN);

    MT_DataReadWrite();
}

void MT_FunctionSet4bit(bool N, bool F)
{
    GPIO_ResetBits(MT_WH1602_RS_PORT, MT_WH1602_RS_PIN);
    GPIO_ResetBits(MT_WH1602_RW_PORT, MT_WH1602_RW_PIN);
    GPIO_ResetBits(MT_WH1602_DB7_PORT, MT_WH1602_DB7_PIN);
    GPIO_ResetBits(MT_WH1602_DB6_PORT, MT_WH1602_DB6_PIN);
    GPIO_SetBits(MT_WH1602_DB5_PORT, MT_WH1602_DB5_PIN);
    GPIO_ResetBits(MT_WH1602_DB4_PORT, MT_WH1602_DB4_PIN);

    MT_DataReadWrite();
    MT_Delay(100);

    if (N == 1)
    {
        GPIO_SetBits(MT_WH1602_DB7_PORT, MT_WH1602_DB7_PIN);
    }
    else
    {
	GPIO_ResetBits(MT_WH1602_DB7_PORT, MT_WH1602_DB7_PIN);
    }

    if (F == 1)
    {
        GPIO_SetBits(MT_WH1602_DB6_PORT, MT_WH1602_DB6_PIN);
    }
    else
    {
        GPIO_ResetBits(MT_WH1602_DB6_PORT, MT_WH1602_DB6_PIN);
    }
    GPIO_ResetBits(MT_WH1602_DB5_PORT, MT_WH1602_DB5_PIN);
    GPIO_ResetBits(MT_WH1602_DB4_PORT, MT_WH1602_DB4_PIN);

    MT_DataReadWrite();
}

void MT_DisplayOnOff()
{
    GPIO_ResetBits(MT_WH1602_RS_PORT, MT_WH1602_RS_PIN);
    GPIO_ResetBits(MT_WH1602_RW_PORT, MT_WH1602_RW_PIN);

    GPIO_ResetBits(MT_WH1602_DB7_PORT, MT_WH1602_DB7_PIN);
    GPIO_ResetBits(MT_WH1602_DB6_PORT, MT_WH1602_DB6_PIN);
    GPIO_ResetBits(MT_WH1602_DB5_PORT, MT_WH1602_DB5_PIN);
    GPIO_ResetBits(MT_WH1602_DB4_PORT, MT_WH1602_DB4_PIN);

    MT_DataReadWrite();
    MT_Delay(100);

    GPIO_SetBits(MT_WH1602_DB7_PORT, MT_WH1602_DB7_PIN);
    GPIO_SetBits(MT_WH1602_DB6_PORT, MT_WH1602_DB6_PIN);
    GPIO_ResetBits(MT_WH1602_DB5_PORT, MT_WH1602_DB5_PIN);
    GPIO_ResetBits(MT_WH1602_DB4_PORT, MT_WH1602_DB4_PIN);

    MT_DataReadWrite();
}

void MT_DisplayClear()
{
    GPIO_ResetBits(MT_WH1602_RS_PORT, MT_WH1602_RS_PIN);
    GPIO_ResetBits(MT_WH1602_RW_PORT, MT_WH1602_RW_PIN);

    GPIO_ResetBits(MT_WH1602_DB7_PORT, MT_WH1602_DB7_PIN);
    GPIO_ResetBits(MT_WH1602_DB6_PORT, MT_WH1602_DB6_PIN);
    GPIO_ResetBits(MT_WH1602_DB5_PORT, MT_WH1602_DB5_PIN);
    GPIO_ResetBits(MT_WH1602_DB4_PORT, MT_WH1602_DB4_PIN);

    MT_DataReadWrite();
    MT_Delay(100);

    GPIO_ResetBits(MT_WH1602_DB7_PORT, MT_WH1602_DB7_PIN);
    GPIO_ResetBits(MT_WH1602_DB6_PORT, MT_WH1602_DB6_PIN);
    GPIO_ResetBits(MT_WH1602_DB5_PORT, MT_WH1602_DB5_PIN);
    GPIO_SetBits(MT_WH1602_DB4_PORT, MT_WH1602_DB4_PIN);

    MT_DataReadWrite();
}



//**************************************************************************************************

//**************************************************************************************************
void MT_WriteData(uint8_t data)
{
    GPIO_SetBits(MT_WH1602_RS_PORT, MT_WH1602_RS_PIN);
    GPIO_ResetBits(MT_WH1602_RW_PORT, MT_WH1602_RW_PIN);

    if (data & BIT_7_MASK)
    {
    	GPIO_SetBits(MT_WH1602_DB7_PORT, MT_WH1602_DB7_PIN);
    }
    else
    {
	GPIO_ResetBits(MT_WH1602_DB7_PORT, MT_WH1602_DB7_PIN);
    }

    if (data & BIT_6_MASK)
    {
	GPIO_SetBits(MT_WH1602_DB6_PORT, MT_WH1602_DB6_PIN);
    }
    else
    {
	GPIO_ResetBits(MT_WH1602_DB6_PORT, MT_WH1602_DB6_PIN);
    }

    if (data & BIT_5_MASK)
    {
	GPIO_SetBits(MT_WH1602_DB5_PORT, MT_WH1602_DB5_PIN);
    }
    else
    {
	GPIO_ResetBits(MT_WH1602_DB5_PORT, MT_WH1602_DB5_PIN);
    }

    if (data & BIT_4_MASK)
    {
    	GPIO_SetBits(MT_WH1602_DB4_PORT, MT_WH1602_DB4_PIN);
    }
    else
    {
    	GPIO_ResetBits(MT_WH1602_DB4_PORT, MT_WH1602_DB4_PIN);
    }

    MT_Delay(100);
    MT_DataReadWrite();

    if (data & BIT_3_MASK)
    {
    	GPIO_SetBits(MT_WH1602_DB7_PORT, MT_WH1602_DB7_PIN);
    }
    else
    {
    	GPIO_ResetBits(MT_WH1602_DB7_PORT, MT_WH1602_DB7_PIN);
    }

    if (data & BIT_2_MASK)
    {
    	GPIO_SetBits(MT_WH1602_DB6_PORT, MT_WH1602_DB6_PIN);
    }
    else
    {
    	GPIO_ResetBits(MT_WH1602_DB6_PORT, MT_WH1602_DB6_PIN);
    }

    if (data & BIT_1_MASK)
    {
    	GPIO_SetBits(MT_WH1602_DB5_PORT, MT_WH1602_DB5_PIN);
    }
    else
    {
	GPIO_ResetBits(MT_WH1602_DB5_PORT, MT_WH1602_DB5_PIN);
    }

    if (data & BIT_0_MASK)
    {
    	GPIO_SetBits(MT_WH1602_DB4_PORT, MT_WH1602_DB4_PIN);
    }
    else
    {
	GPIO_ResetBits(MT_WH1602_DB4_PORT, MT_WH1602_DB4_PIN);
    }

    MT_Delay(100);
    MT_DataReadWrite();
}


#endif
