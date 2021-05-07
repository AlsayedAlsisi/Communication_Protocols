/*********************************************************************************************************************
* Author : Alsayed Alsisi
* Date   : Thursday, May 06, 2021
* Version: 1.0
* Contact: alsayed.alsisi@gmail.com
* License:
* You have the right to use the file as you wish in any educational or commercial purposes under the following
* conditions:
* [1] This file is to be used as is. No modifications are to be made to any part of the file, including this section.
* [2] This section is not to be removed under any circumstances.
* [3] Parts of the file may be used separately under the condition they are not modified, and preceded by this section.
* [4] Any bug encountered in this file or parts of it should be reported to the email address given above to be fixed.
* [5] No warranty is expressed or implied by the publication or distribution of this source code.
*********************************************************************************************************************/
/*********************************************************************************************************************
* File Information:
** File Name:
*  main.c
*
** File Description:
*  Project main file.
*********************************************************************************************************************/
/*********************************************************************************************************************
                                               << File Inclusions >>
*********************************************************************************************************************/
#include <avr/interrupt.h>
#include "uart_atmega32.h"
#include "queue.h"
#include "lcd.h"
/*********************************************************************************************************************
                                              << Private Constants >>
*********************************************************************************************************************/
#define   INITIALIZE_TO_ZERO    0 
#define   LCD_QUEUE_SIZE        13
#define   LCD_FIRST_ROW         0
#define   LCD_LAST_CHAR_INDEX   12
/* Baud Rate and Clock Frequency definition */
#define   F_CPU              12000000UL
#define   BAUDRATE           9600UL

/*********************************************************************************************************************
                                              << Variable Definitions >>
*********************************************************************************************************************/
/* Creating a data buffer for the LCD queue: */
static uint8_t lcd_queue_data_buffer[LCD_QUEUE_SIZE] = {INITIALIZE_TO_ZERO}; 
/* Creating the LCD queue and initializing it:*/
static queue_t lcd_display_queue = {.data_buffer = lcd_queue_data_buffer, .queue_size = LCD_QUEUE_SIZE,
	                                .front_index = INITIALIZE_TO_ZERO, .rear_index = INITIALIZE_TO_ZERO};

/*********************************************************************************************************************
                                              << Function Declarations >>
*********************************************************************************************************************/
static void uart_receiver_init(void);
static void receive_task(void);
static void display_task(void);


	
/*********************************************************************************************************************
                                               << Function Definitions >>
*********************************************************************************************************************/
/********************************************************************************************************************
** Function Name:
*  main
*  
** Description:
*  Project main function.
*
** Input Parameters:
*  - void
*
** Return Value:
*  - int
********************************************************************************************************************/
int main(void)
{
	uart_receiver_init();
    lcd_init();
	
    while (1) 
    {
		display_task(); 
    }
}

/********************************************************************************************************************
** Function Name:
*  uart_receiver_init
*
** Description:
*  Initializes the UART module.
*
** Input Parameters:
*  - void
*
** Return Value:
*  - void
********************************************************************************************************************/
void uart_receiver_init(void)
{
	/* UART Initialization */
	(void)uart_baud_rate_config(BAUDRATE, F_CPU);
 	uart_frame_format_select(UART_8BIT_CHARACTER_SIZE, UART_1STOP_BIT);
 	uart_synch_asynch_mode_select(UART_ASYNCHRONOUS_OPERATION);
 	uart_receiver_enable(); 
	uart_receive_complete_interrupt_enable();
	uart_receive_complete_interrupt_callback_set(&receive_task);
	sei(); /* Enable global interrupts */
}

/********************************************************************************************************************
** Function Name:
*  receive_task
*
** Description:
*  The receive task checks for the receipt of a new character in the UART module and appends it to the LCD data 
*  queue. This function runs in the receive complete interrupt routine.
*
** Input Parameters:
*  - void
*
** Return Value:
*  - void
********************************************************************************************************************/
void receive_task(void)
{
	uint8_t uart_received_data = INITIALIZE_TO_ZERO;
    /* Read new data: */
	uart_received_data = uart_data_read();
	/* Add the received data to the queue: */
	queue_enqueue(&lcd_display_queue, uart_received_data);
}

/********************************************************************************************************************
** Function Name:
*  display_task
*
** Description:
*  The display task checks if there's data in the LCD data queue and displays it on the LCD.
*
** Input Parameters:
*  - void
*
** Return Value:
*  - void
********************************************************************************************************************/
void display_task(void)
{
	static uint8_t lcd_display_char_index = 0;
	uint8_t lcd_display_char = INITIALIZE_TO_ZERO;
	/* Checking if there is data in the queue: */
	if (QUEUE_NOT_EMPTY == queue_isEmpty(&lcd_display_queue))
	{
		/* Reading the data from the front of the queue: */
		queue_dequeue(&lcd_display_queue, &lcd_display_char);
		/* Go to the coordinates of the next character to display on the LCD: */
		lcd_gotoxy(lcd_display_char_index, LCD_FIRST_ROW);
		/* Displaying the next character: */
		lcd_character_write(lcd_display_char);
		lcd_display_char_index++;
	}
	
	/* Check if the LCD has printed the last character: */
	if ((LCD_LAST_CHAR_INDEX+1) == lcd_display_char_index)
	{
		/* Reset the display character index, so that the next time the LCD 
		   will go to the first character coordinates. */
		lcd_display_char_index = INITIALIZE_TO_ZERO;
	}
}

/*********************************************************************************************************************
                                               << End of File >>
*********************************************************************************************************************/
