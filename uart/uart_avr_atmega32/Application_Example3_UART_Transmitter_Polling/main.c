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




/*********************************************************************************************************************
                                              << Private Constants >>
*********************************************************************************************************************/
#define   INITIALIZE_TO_ZERO    0 
/* Baud Rate and Clock Frequency definition */
#define   F_CPU                 16000000UL
#define   BAUDRATE              9600UL


/*********************************************************************************************************************
                                              << Variable Definitions >>
*********************************************************************************************************************/
static uint8_t transmission_data = INITIALIZE_TO_ZERO;


/*********************************************************************************************************************
                                              << Function Declarations >>
*********************************************************************************************************************/
static void uart_transmitter_init(void);
static void transmit_task(void);
static void transmit_data_update_task(void);

/*********************************************************************************************************************
                                              << Function Definitions >>
*********************************************************************************************************************/
int main(void)
{
    uart_transmitter_init();
    while (1) 
    {
	    transmit_data_update_task();
		transmit_task();
		/* Suggestion 1: Send data through the UART periodically. The purpose of the time period is to give the receiver
		   on the other side enough time to process the data received. The receiver could be displaying the data on an 
		   LCD for example.
		   Suggestion 2: use a hardware timer for creating the time periods instead of software delay that blocks the 
		   CPU. */
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
void uart_transmitter_init()
{
	/* UART Initialization */
	(void)uart_baud_rate_config(BAUDRATE, F_CPU);
 	uart_frame_format_select(UART_8BIT_CHARACTER_SIZE, UART_1STOP_BIT);
 	uart_synch_asynch_mode_select(UART_ASYNCHRONOUS_OPERATION);
	uart_transmitter_enable();
}

/********************************************************************************************************************
** Function Name:
*  transmit_data_update_task
*
** Description:
*  This function works as a task that updates the data that will be sent over the UART. Provided here is just a 
*   dummy code for demonstration purposes. The function could implement other any logic that updates the data to 
*   be sent, for example with temperature value obtained from the sensor connected to the microcontroller.
*
** Input Parameters:
*  - void
*
** Return Value:
*  - void
********************************************************************************************************************/
void transmit_data_update_task(void)
{
	
	transmission_data = transmission_data + 1;
}

/********************************************************************************************************************
** Function Name:
*  transmit_task
*
** Description:
*  This function works as a task to send data through the UART.
*
** Input Parameters:
*  - void
*
** Return Value:
*  - void
********************************************************************************************************************/
void transmit_task(void)
{
	if (UART_READY == uart_transmitter_is_ready())
	{
		uart_data_write(transmission_data);
	}
		
}

/*********************************************************************************************************************
                                               << End of File >>
*********************************************************************************************************************/
