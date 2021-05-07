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
*  lcd.h
* 
** Description:
*  This file contains the public programming interfaces for the LCD device driver for ATmega32 family of microcontroller.
*  This file can be used with any of the following members of this family:
*  ATmega32, ATmega16, ATmega16A
*********************************************************************************************************************/


/*********************************************************************************************************************
                                               << Header Guard >>
*********************************************************************************************************************/
#ifndef LCD_H_
#define LCD_H_

/*********************************************************************************************************************
                                               << File Inclusions >>
*********************************************************************************************************************/


/*********************************************************************************************************************
                                               << Public Constants >>
*********************************************************************************************************************/


/*********************************************************************************************************************
                                               << Public Data Types >>
*********************************************************************************************************************/
typedef enum
{
	LCD_OK = 0,
	LCD_NOT_OK
} lcd_std_error_type_t;

typedef enum
{
	LCD_CLEAR_ALL = 0x00,

	} lcd_command_t;

/*********************************************************************************************************************
                                          << Public Variable Declarations >>
*********************************************************************************************************************/


/*********************************************************************************************************************
                                   << Public Function Declarations (Programming Interfaces) >>
*********************************************************************************************************************/
extern void lcd_init(void);

extern lcd_std_error_type_t lcd_gotoxy(uint8_t x, uint8_t y);

extern lcd_std_error_type_t lcd_command_send(lcd_command_t lcd_command);

extern void lcd_character_write(uint8_t data_character);

extern void lcd_print_string(char* str);



#endif /* LCD_H_ */
/*********************************************************************************************************************
                                               << End of File >>
*********************************************************************************************************************/