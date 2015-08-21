/**
 *  Defines for your entire project at one place
 *
 *	@author 	Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@version 	v1.0
 *	@ide		Keil uVision 5
 *	@license	GNU GPL v3
 *
 * |----------------------------------------------------------------------
 * | Copyright (C) Tilen Majerle, 2014
 * |
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * |
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 */
#ifndef TM_DEFINES_H
#define TM_DEFINES_H

/* Put your global defines for all libraries here used in your project */

/* If you want to change your pinout
/ then uncomment pin you want to change
/ and edit its settings */

/* Control pins */
/* RS - Register select pin */
#define TM_HD44780_RS_RCC				RCC_AHB1Periph_GPIOB
#define TM_HD44780_RS_PORT			GPIOB
#define TM_HD44780_RS_PIN				GPIO_Pin_0
/* E - Enable pin */
#define TM_HD44780_E_RCC				RCC_AHB1Periph_GPIOB
#define TM_HD44780_E_PORT				GPIOB
#define TM_HD44780_E_PIN				GPIO_Pin_2

/* D4 - Data 4 pin */
#define TM_HD44780_D4_RCC				RCC_AHB1Periph_GPIOC
#define TM_HD44780_D4_PORT				GPIOB
#define TM_HD44780_D4_PIN				GPIO_Pin_12
/* D5 - Data 5 pin */
#define TM_HD44780_D5_RCC				RCC_AHB1Periph_GPIOC
#define TM_HD44780_D5_PORT				GPIOB
#define TM_HD44780_D5_PIN				GPIO_Pin_13
/* D6 - Data 6 pin */
#define TM_HD44780_D6_RCC				RCC_AHB1Periph_GPIOB
#define TM_HD44780_D6_PORT				GPIOB
#define TM_HD44780_D6_PIN				GPIO_Pin_14
/* D7 - Data 7 pin */
#define TM_HD44780_D7_RCC				RCC_AHB1Periph_GPIOB
#define TM_HD44780_D7_PORT				GPIOB
#define TM_HD44780_D7_PIN				GPIO_Pin_15


// Set RS port
#define MT_WH1602_RS_PORT       (GPIOB)
// Set RS pin
#define MT_WH1602_RS_PIN		(GPIO_Pin_0)

// Set RW port
#define MT_WH1602_RW_PORT		(GPIOB)
// Set RW pin
#define MT_WH1602_RW_PIN		(GPIO_Pin_1)

// Set E port
#define MT_WH1602_E_PORT		(GPIOB)
// Set E pin
#define MT_WH1602_E_PIN	  		(GPIO_Pin_2)

// Set DB7 port
#define MT_WH1602_DB7_PORT		(GPIOB)
// Set DB7 pin
#define MT_WH1602_DB7_PIN		(GPIO_Pin_15)

// Set DB6 port
#define MT_WH1602_DB6_PORT		(GPIOB)
// Set DB6 pin
#define MT_WH1602_DB6_PIN       (GPIO_Pin_14)

// Set DB5 port
#define MT_WH1602_DB5_PORT		(GPIOB)
// Set DB5 pin
#define MT_WH1602_DB5_PIN	    (GPIO_Pin_13)

// Set DB4 port
#define MT_WH1602_DB4_PORT		(GPIOB)
// Set DB4 pin
#define MT_WH1602_DB4_PIN		(GPIO_Pin_12)

#define FATFS_USE_USB 1

#endif

