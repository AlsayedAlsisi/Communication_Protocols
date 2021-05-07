/*********************************************************************************************************************
* Author : Alsayed Alsisi
* Date   : Saturday, April 10, 2021
* Version: 1.0
* Contact: alsayed.alsisi@gmail.com
* License:
* You have the right to use the file as you wish in any educational or commercial purposes under the following
* conditions:
* - This file is to be used as is. No modifications are to be made to any part of the file, including this section.
* - This section is not to be removed under any circumstances.
* - Parts of the file may be used separately under the condition they are not modified, and preceded by this section.
* - Any bug encountered in this file or parts of it should be reported to the email address given above to be fixed.
* - No warranty is expressed or implied by the publication or distribution of this source code.
*********************************************************************************************************************/
/*********************************************************************************************************************
* File Information:
** File Name:
*  lcd_config.h
*
** Description:
*  This file contains the set of configurations for the LCD device driver for ATmega32 family of microcontroller.
*  This file can be used with any of the following members of this family:
*  ATmega32, ATmega16, ATmega16A
*********************************************************************************************************************/


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_


/*
Define the CPU clock frequency. This is important to calculate delays..
required for the initialization and operation of the LCD.
*/
#define F_CPU  12000000UL


/* Choosing the LCD operation mode
** Options: 
*  LCD_4BIT_OPERATION
*  LCD_8BIT_OPERATION
*/
#define LCD_MODE  LCD_8BIT_OPERATION


/* Choosing the LCD size
** Options:
*  LCD_16x2
*  LCD_16x4
*  LCD_20x2
*  LCD_20x4
*/
#define LCD_SIZE LCD_16x2


/* Choosing the lcd data port
** Options:
* GPIO_PORTA
* GPIO_PORTB
* GPIO_PORTC
* GPIO_PORTD
*/
#define  LCD_DATA_PORT  GPIO_PORTA

/* Setting data pin numbers: 
** Options:
* GPIO_PIN_0 to GPIO_PIN_31
* Note: The pins need to contiguous.
*/
#define LCD_D0   GPIO_PIN0
#define LCD_D1   GPIO_PIN1
#define LCD_D2   GPIO_PIN2
#define LCD_D3   GPIO_PIN3
#define LCD_D4   GPIO_PIN4
#define LCD_D5   GPIO_PIN5
#define LCD_D6   GPIO_PIN6
#define LCD_D7   GPIO_PIN7

/* 
   The following MACRO defines the number of the pin the LCD_D4 is connected to.
   This number is necessary to allow the LCD to fit anywhere along any port, not 
   just the first 8 pins, in case the port is more than 8 pins.
*/
#define LCD_D4_PIN_NUMBER (4U) 


/* Choosing the lcd control port
** Options:
* GPIO_PORTA
* GPIO_PORTB
* GPIO_PORTC
* GPIO_PORTD
*/
#define  LCD_CNTRL_PORT  GPIO_PORTB

/* Setting control pin numbers: 
** Options:
* GPIO_PIN_0
* GPIO_PIN_1
* GPIO_PIN_2
* GPIO_PIN_3
* GPIO_PIN_4
* GPIO_PIN_5
* GPIO_PIN_6
* GPIO_PIN_7
*/
#define  LCD_RS	  GPIO_PIN0
#define  LCD_RW	  GPIO_PIN1
#define  LCD_EN   GPIO_PIN2
#endif /* LCD_CONFIG_H_ */