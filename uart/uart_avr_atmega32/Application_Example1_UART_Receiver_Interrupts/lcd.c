/*********************************************************************************************************************
* Author : Alsayed Alsisi
* Date   : Saturday, November 07, 2020
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
*  lcd.c
* 
** Description:
*  This file contains the implementation for the LCD device driver for ATmega32 family of microcontroller. 
*  This file can be used with any of the following members of this family:
*  ATmega32, ATmega16, ATmega16A
*********************************************************************************************************************/


/*********************************************************************************************************************
                                               << File Inclusions >>
*********************************************************************************************************************/
#include "lcd_config.h"  /* Note: It also contains the definition of F_CPU required for the delay functions. */
#include <util/delay.h>
#include <stdint.h>

#include "lcd.h"
#include "bit_math.h"
#include "gpio_atmega32.h"

/*********************************************************************************************************************
                                              << Private Constants >>
*********************************************************************************************************************/
#define   SHIFT_BY_FOUR   (4U)

/*********************************************************************************************************************
                                              << Private Data Types >>
*********************************************************************************************************************/


/*********************************************************************************************************************
                                          << Private Variable Definitions >>
*********************************************************************************************************************/


/*********************************************************************************************************************
                                          << Public Variable Definitions >>
*********************************************************************************************************************/


/*********************************************************************************************************************
                                         << Private Functions Prototypes >>
*********************************************************************************************************************/
static void lcd_4bit_init(void);
static void lcd_8bit_init(void);

static void lcd_8bit_command_send(lcd_command_t lcd_command);
static void lcd_4bit_command_send(lcd_command_t lcd_command);
static void lcd_8bit_character_write(uint8_t data_character);
static void lcd_4bit_character_write(uint8_t data_character);
/*********************************************************************************************************************
                                          << Public Function Definitions >>
*********************************************************************************************************************/
/*********************************************************************************************************************
** Function Name:
*  lcd_init
*
** Description:
*  This function starts the LCD initialization with the certain LCD configurations selected.
*
** Input Parameters:
*  - void
*
** Return Value:
*  - void
*    
*********************************************************************************************************************/
void lcd_init(void)
{

	lcd_8bit_init();
	lcd_gotoxy(0,0);

}

/*********************************************************************************************************************
** Function Name:
*
*
** Description:
*
*
** Input Parameters:
*  - x: uint8_t
*    Passes the desired character column number to the function.
*  - y: uint8_t
*    Passes the desired character line number to the function.
*
** Return Value:
*  - lcd_std_error_type_t
*    Returns 'LCD_OK' for correct character coordinates, and 'LCD_NOT_OK' if the x or y coordinates is wrong.
*********************************************************************************************************************/
lcd_std_error_type_t lcd_gotoxy(uint8_t x, uint8_t y)
{
	uint8_t first_char_address[]={0x80, 0xC0, 0x90, 0xD0}; /* Fits 16x2 and 16x4 LCDs */
	lcd_command_send(first_char_address[y]+(x));
	_delay_us(100);	
}

/*********************************************************************************************************************
** Function Name:
*  lcd_command_send
*
** Description:
*  This function sends a certain command to the LCD.
*
** Input Parameters:
*  - lcd_command: lcd_command_t
*    Command to send to the LCD.
*
** Return Value:
*  - lcd_std_error_type_t
*    Returns 'LCD_OK' for correct command, and 'LCD_NOT_OK' if the passed command isn't any of the available commands.
*
*********************************************************************************************************************/
lcd_std_error_type_t lcd_command_send(lcd_command_t lcd_command)
{
	lcd_8bit_command_send(lcd_command);
}

/*********************************************************************************************************************
** Function Name:
*  lcd_character_write
*
** Description:
*  This function 
*
** Input Parameters:
*  - void
*
** Return Value:
*  - void
*
*********************************************************************************************************************/
void lcd_character_write(uint8_t data_character)
{
	/* For 8 bit LCD operation: */
	lcd_8bit_character_write(data_character);


}



/*********************************************************************************************************************
                                          << Private Function Definitions >>
*********************************************************************************************************************/
/*********************************************************************************************************************
** Function Name:
*  lcd_4bit_init
*
** Description:
*  This function initializes the LCD for the 4 bit operation mode.
*
** Input Parameters:
*  - void
*
** Return Value:
*  - void
*    
*********************************************************************************************************************/
static void lcd_4bit_init(void)
{
	_delay_ms(15);
	gpio_pins_config(LCD_DATA_PORT, (LCD_D7|LCD_D6|LCD_D5|LCD_D4), GPIO_OUTPUT, 0x00);
	gpio_pins_config(LCD_CNTRL_PORT, (LCD_RS|LCD_RW|LCD_EN), GPIO_OUTPUT, 0x00);

	lcd_command_send(0x33); 
	_delay_us(100);
	lcd_command_send(0x32); //for 4-bit mode
	_delay_us(100);
	lcd_command_send(0x28); //for 4-bit mode
	_delay_us(100);
	lcd_command_send(0x0E); //display on, cursor on.
	_delay_us(100);
	lcd_command_send(0x06); //No shift and auto increment right
	_delay_us(100);
	lcd_command_send(0x01); //clear lcd
	_delay_us(1500); /* This is necessary for the LCD to work correctly.*/
}

/*********************************************************************************************************************
** Function Name:
*  lcd_8bit_init
*
** Description:
*  This function initializes the LCD for the 8 bit operation mode.
*
** Input Parameters:
*  - void
*
** Return Value:
*  - void
*
*********************************************************************************************************************/
static void lcd_8bit_init(void)
{
	_delay_ms(15);
	/* Configuring data pins as output: */
	gpio_port_config(LCD_DATA_PORT, GPIO_OUTPUT, 0x00);
	/* Configuring control pins as output: */
	gpio_pin_config(LCD_CNTRL_PORT, LCD_RS, GPIO_OUTPUT, GPIO_PIN_LOW);
	gpio_pin_config(LCD_CNTRL_PORT, LCD_RW, GPIO_OUTPUT, GPIO_PIN_LOW);
	gpio_pin_config(LCD_CNTRL_PORT, LCD_EN, GPIO_OUTPUT, GPIO_PIN_LOW);	

	lcd_command_send(0x38); 
	_delay_us(100);
	lcd_command_send(0x0E); //display on, cursor on.
	_delay_us(100);
	lcd_command_send(0x06); //No shift and auto increment right
	_delay_us(100);
	lcd_command_send(0x01); //clear lcd
	_delay_us(1500); /* This is necessary for the LCD to work correctly.*/
	

}
static void lcd_8bit_command_send(lcd_command_t lcd_command)
{
	/* For 8 bit LCD operation: */
	gpio_port_write(LCD_DATA_PORT, lcd_command);
	gpio_pins_write(LCD_CNTRL_PORT, (LCD_RS|LCD_RW), 0x00); /**/
	gpio_pin_write(LCD_CNTRL_PORT, LCD_EN, GPIO_PIN_HIGH);
	_delay_us(40);
	gpio_pin_write(LCD_CNTRL_PORT, LCD_EN, GPIO_PIN_LOW);
	_delay_us(100);
}

static void lcd_4bit_command_send(lcd_command_t lcd_command)
{
	/* Sending the first 4 bits (MSB bits) */
	gpio_pins_write(LCD_DATA_PORT, (LCD_D7|LCD_D6|LCD_D5|LCD_D4), ((uint32_t)(lcd_command>>SHIFT_BY_FOUR)<<LCD_D4_PIN_NUMBER));
	gpio_pins_write(LCD_CNTRL_PORT, (LCD_RS|LCD_RW), 0x00);
	gpio_pin_write(LCD_CNTRL_PORT, LCD_EN, GPIO_PIN_HIGH);	/* Start of a pulse on the Enable pin: */
	_delay_us(40);
	gpio_pin_write(LCD_CNTRL_PORT, LCD_EN, GPIO_PIN_LOW);  	/* End of a pulse on the Enable pin: */
	
	_delay_us(100);
	
	/* Sending the last 4 bits (LSB bits): */
	gpio_pins_write(LCD_DATA_PORT, (LCD_D7|LCD_D6|LCD_D5|LCD_D4), ((uint32_t)lcd_command << LCD_D4_PIN_NUMBER));
	gpio_pin_write(LCD_CNTRL_PORT, LCD_EN, GPIO_PIN_HIGH);	/* Start of a pulse on the Enable pin: */
	_delay_us(40);
	gpio_pin_write(LCD_CNTRL_PORT, LCD_EN, GPIO_PIN_LOW);  	/* End of a pulse on the Enable pin: */
}
static void lcd_8bit_character_write(uint8_t data_character)
{
	gpio_port_write(LCD_DATA_PORT, data_character);
	gpio_pin_write(LCD_CNTRL_PORT, LCD_RS, GPIO_PIN_HIGH);
	gpio_pin_write(LCD_CNTRL_PORT, LCD_RW, GPIO_PIN_LOW);
	gpio_pin_write(LCD_CNTRL_PORT, LCD_EN, GPIO_PIN_HIGH);
	_delay_us(40);
	gpio_pin_write(LCD_CNTRL_PORT, LCD_EN, GPIO_PIN_LOW);
	_delay_us(100);
}

static void lcd_4bit_character_write(uint8_t data_character)
{
	/* Sending the first 4 bits (MSB bits) */
	gpio_pins_write(LCD_DATA_PORT, (LCD_D7|LCD_D6|LCD_D5|LCD_D4), ((uint32_t)(data_character>>SHIFT_BY_FOUR)<<LCD_D4_PIN_NUMBER));
	gpio_pin_write(LCD_CNTRL_PORT, LCD_RS, GPIO_PIN_HIGH);
	gpio_pin_write(LCD_CNTRL_PORT, LCD_RW, GPIO_PIN_LOW);
	gpio_pin_write(LCD_CNTRL_PORT, LCD_EN, GPIO_PIN_HIGH);	/* Start of a pulse on the Enable pin: */
	_delay_us(40);
	gpio_pin_write(LCD_CNTRL_PORT, LCD_EN, GPIO_PIN_LOW);  	/* End of a pulse on the Enable pin: */
	
	_delay_us(100);
	
	/* Sending the last 4 bits (LSB bits) */
	gpio_pins_write(LCD_DATA_PORT, (LCD_D7|LCD_D6|LCD_D5|LCD_D4), ((uint32_t)data_character << LCD_D4_PIN_NUMBER));
	gpio_pin_write(LCD_CNTRL_PORT, LCD_EN, GPIO_PIN_HIGH);	/* Start of a pulse on the Enable pin: */
	_delay_us(40);
	gpio_pin_write(LCD_CNTRL_PORT, LCD_EN, GPIO_PIN_LOW);  	/* End of a pulse on the Enable pin: */
}
void lcd_print_string(char* str)
{
	uint8_t i=0;
	while (str[i]!=0)
	{
		lcd_character_write(str[i]);
		i++;
	}
}

void int_to_string(uint32_t int_number, uint8_t number_of_digits, char* string)
{
	uint8_t digit;
	for(int8_t i=(number_of_digits-1); i>=0; i--)
	{
		digit = int_number%10;
		int_number = int_number/10;
		switch(digit)
		{
			case 0:
			string[i]='0';
			break;
			case 1:
			string[i]='1';
			break;
			case 2:
			string[i]='2';
			break;
			case 3:
			string[i]='3';
			break;
			case 4:
			string[i]='4';
			break;
			case 5:
			string[i]='5';
			break;
			case 6:
			string[i]='6';
			break;
			case 7:
			string[i]='7';
			break;
			case 8:
			string[i]='8';
			break;
			case 9:
			string[i]='9';
			break;
			default:
			break;
		}
		string[number_of_digits]=0;
	}
}

/*********************************************************************************************************************
                                                << End of File >>
*********************************************************************************************************************/