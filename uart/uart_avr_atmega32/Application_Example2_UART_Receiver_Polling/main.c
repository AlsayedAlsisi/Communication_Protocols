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
#include "uart_atmega32.h"
#include "gpio_atmega32.h"

/*********************************************************************************************************************
                                              << Private Constants >>
*********************************************************************************************************************/
#define  GPIO_INIT_PINS_ALL_OFF  0x00
/*Baud Rate and Clock Frequency definition*/
#define  F_CPU     12000000
#define  BAUDRATE  9600

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
	uint8_t data_received = 0;
	gpio_port_config(GPIO_PORTC, GPIO_OUTPUT, GPIO_INIT_PINS_ALL_OFF);
	uart_receiver_init();
   
    while (1) 
    {
		if (UART_READY == uart_receiver_is_ready())
		{
			 data_received = uart_data_read();
			 /* Process received data:
			    Note that  */
			 gpio_port_write(GPIO_PORTC, data_received); 
		}
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
}
/*********************************************************************************************************************
                                               << End of File >>
*********************************************************************************************************************/
