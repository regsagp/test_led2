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

	    while(1)
	    {
	        __NOP();
	    }
}

int main(void)
{
	test_lcd();
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
}
