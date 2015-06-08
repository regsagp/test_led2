/**
  *****************************************************************************
  * @title   main.c
  * @author  lordzuqi
  * @date    28 Jun 2014
  * @brief   Blinking LED with Input from Button
  *******************************************************************************
  */
////// The above comment is automatically generated by CoIDE ///////////////////

#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>

//#include <stm32f4xx.h>
//#include <stm32f4xx_gpio.h>
//#include <stm32f4xx_rcc.h>
#define LED1 GPIOD, GPIO_Pin_12
#define LED2 GPIOD, GPIO_Pin_13
#define LED3 GPIOD, GPIO_Pin_14
#define LED4 GPIOD, GPIO_Pin_15
#define button GPIOA, GPIO_Pin_0
int a, b, c, d ;
GPIO_InitTypeDef GPIO_InitStruct;

static void GPIO_setup(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12; // we want to configure all LED GPIO pins
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; 		// we want the pins to be an output
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 	// this sets the GPIO modules clock speed
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; 	// this sets the pin type to push / pull (as opposed to open drain)
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; 	// this sets the pullup / pulldown resistors to be inactive
	GPIO_Init(GPIOD, &GPIO_InitStruct);
}

static void button_setup(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;		  // we want to configure PA0
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; 	  // we want it to be an input
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//this sets the GPIO modules clock speed
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;   // this sets the pin type to push / pull (as opposed to open drain)
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;   // this enables the pulldown resistor --> we want to detect a high level
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// ���������� ���������� TIM6_DAC
void TIM6_DAC_IRQHandler(void)
{
	TIM6->SR &= ~TIM_SR_UIF; //���������� ���� UIF
	GPIOC->ODR ^= (GPIO_Pin_9 | GPIO_Pin_8); //����������� ��������� �����������
}

static void startTimer(int msec)
{
	TIM6->DIER |= TIM_DIER_UIE; //��������� ���������� �� �������
	TIM6->CR1 |= TIM_CR1_CEN; // ������ ������!
	TIM6->ARR = msec; // ���� ���������� ��������� ��� � �������
}

static void initTimer()
{
	GPIO_InitTypeDef PORT;
	//�������� ���� � � ������ 6
	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOC , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	// �������� ���� �� ������������ �� �����
	PORT.GPIO_Pin = (GPIO_Pin_9 | GPIO_Pin_8);
	PORT.GPIO_Mode = GPIO_Mode_OUT;
	PORT.GPIO_OType = GPIO_OType_PP; 	// this sets the pin type to push / pull (as opposed to open drain)
	PORT.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &PORT);
	TIM6->PSC = 24000 - 1; // ����������� �������� ��� ������ ����� 1000 ��� � �������
	NVIC_EnableIRQ(TIM6_DAC_IRQn); //���������� TIM6_DAC_IRQn ����������
}

void test_lcd()
{
	MT_Init();
	    MT_Delay(1000);

	    MT_FunctionSet8bit();
	    MT_Delay(1000);

	    MT_FunctionSet4bit(1, 1);
	    MT_Delay(1000);

	    MT_FunctionSet4bit(1, 1);
	    MT_Delay(1000);

	    MT_DisplayOnOff();
	    MT_Delay(1000);

	    MT_DisplayClear();
	    MT_Delay(10000);

	    MT_WriteData(0x32);
	    MT_Delay(1000);
	    MT_WriteData(0x20);
	    MT_Delay(1000);
	    MT_WriteData(0x62);
	    MT_Delay(1000);
	    MT_WriteData(0x69);
	    MT_Delay(1000);
	    MT_WriteData(0x74);
	    MT_Delay(1000);
	    MT_WriteData(0x20);
	    MT_Delay(1000);
	    MT_WriteData(0x6D);
	    MT_Delay(1000);
	    MT_WriteData(0x6F);
	    MT_Delay(1000);
	    MT_WriteData(0x64);
	    MT_Delay(1000);
	    MT_WriteData(0x65);
	    MT_Delay(1000);

}

#include "defines.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_hd44780.h"

int main2(void) {
	/* Rectangle for custom character */
	/* xxx means doesn't care, lower 5 bits are important for LCD */
	uint8_t customChar[] = {
		0x1F,	/*  xxx 11111 */
		0x11,	/*  xxx 10001 */
		0x11,	/*  xxx 10001 */
		0x11,	/*  xxx 10001 */
		0x11,	/*  xxx 10001 */
		0x11,	/*  xxx 10001 */
		0x11,	/*  xxx 10001 */
		0x1F	/*  xxx 11111 */
	};

	/* Initialize system */
	SystemInit();

	/* Initialize LCD 20 cols x 4 rows */
	TM_HD44780_Init(20, 2);

	/* Save custom character on location 0 in LCD */
	TM_HD44780_CreateChar(0, &customChar[0]);

	/* Put string to LCD */
	TM_HD44780_Puts(0, 0, "STM32F4/29 Discovery");
	TM_HD44780_Puts(2, 1, "20x4 HD44780 LCD");
	TM_HD44780_Puts(0, 2, "stm32f4-\n\r       discovery.com");

	/* Wait a little */
	Delayms(3000);

	/* Clear LCD */
	TM_HD44780_Clear();

	/* Show cursor */
	TM_HD44780_CursorOn();

	/* Write new text */
	TM_HD44780_Puts(6, 2, "CLEARED!");

	/* Wait a little */
	Delayms(1000);

	/* Enable cursor blinking */
	TM_HD44780_BlinkOn();

	/* Show custom character at x = 1, y = 2 from RAM location 0 */
	TM_HD44780_PutCustom(1, 2, 0);
}

#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_adc.h"
//#include "tm_stm32f4_usart.h"
#include <stdio.h>
void test_adc()
{
	 char str[150];
	/* Initialize Delay library */
	    TM_DELAY_Init();

	    /* Initialize USART1, 115200 baud, TX: PB6 */
	    //TM_USART_Init(USART1, TM_USART_PinsPack_2, 115200);


	    /* Initialize ADC1 on channel 0, this is pin PA0 */
	    //TM_ADC_Init(ADC1, ADC_Channel_0);

	    /* Initialize ADC1 on channel 3, this is pin PA3 */
	    //TM_ADC_Init(ADC1, ADC_Channel_3);

	    /* Initialize ADC1 */
	    TM_ADC_InitADC(ADC1);

	    /* Enable vbat channel */
	    TM_ADC_EnableVbat();


	    while (1) {
	        /* Read & format data */
	        sprintf(str, "----------------------------\nVbat voltage: %d mV\n", TM_ADC_ReadVbat(ADC1));

	        printf("----------------------------\nVbat voltage: %d mV\n", TM_ADC_ReadVbat(ADC1));

	        /* Put to USART */
	        //TM_USART_Puts(USART1, str);

	        /* Little delay */
	        Delayms(1000);
	    }
}

int main(void)
{
	//test_lcd();
	//main2();
	test_adc();




	/*
	GPIO_setup();
	button_setup();
	GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 |GPIO_Pin_14 |GPIO_Pin_15 );

	initTimer();

	startTimer(1000);

	while(1)
	{

	}
	*/
	while(1)
	{

	}
	return 0;
}

