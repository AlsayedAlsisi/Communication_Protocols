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
*  uart_atmega32.c
* 
** Description:
*  This file contains the implementation for the device driver of UART peripheral of the atmega32 microcontroller.
*********************************************************************************************************************/


/*********************************************************************************************************************
                                               << File Inclusions >>
*********************************************************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "uart_atmega32.h"
#include "bit_math.h"

/*********************************************************************************************************************
                                              << Private Constants >>
*********************************************************************************************************************/
#define   INITIALIZE_TO_ZERO (0U)
#define   SHIFT_BY_EIGHT     (8U)

/******************************************** UCSZ1:0 Bit-relating Macros *******************************************/
#define   UCSZ_BITS_MASK_WITH_ZEROs      0xF9    /* 0b11111001 */
#define   UCSZ_5BIT_CHAR_SIZE_SELECTED   0x00    /* UCSZ1:0 = 00 */
#define   UCSZ_6BIT_CHAR_SIZE_SELECTED   0x02    /* UCSZ1:0 = 01 */
#define   UCSZ_7BIT_CHAR_SIZE_SELECTED   0x04    /* UCSZ1:0 = 10 */
#define   UCSZ_8BIT_CHAR_SIZE_SELECTED   0x06    /* UCSZ1:0 = 11 */
#define   UCSZ_9BIT_CHAR_SIZE_SELECTED   0x06    /* UCSZ1:0 = 11 */

/*********************************************************************************************************************
                                              << Private Data Types >>
*********************************************************************************************************************/


/*********************************************************************************************************************
                                          << Private Variable Definitions >>
*********************************************************************************************************************/
static void (*g_tx_complete_callback)(void);
static void (*g_rx_complete_callback)(void);

/*********************************************************************************************************************
                                          << Public Variable Definitions >>
*********************************************************************************************************************/


/*********************************************************************************************************************
                                         << Private Functions Prototypes >>
*********************************************************************************************************************/
static uart_std_error_type_t uart_character_size_select(uart_character_size_t uart_character_size);
static uart_std_error_type_t uart_stop_bit_size_select(uart_stop_bit_size_t uart_stop_bit_size);

/*********************************************************************************************************************
                                          << Public Function Definitions >>
*********************************************************************************************************************/
/*********************************************************************************************************************
** Function Name:
*  uart_baud_rate_config
*
** Description:
*  This function configures the baudrate of the UART peripheral operation.
*
** Input Parameters:
*  - baudrate: uint32_t
*    This parameter is used to select the desired baud rate in bit/second.
*  - sys_Osc_clock_freq: uint32_t
*    This parameter is used to pass the microcontroller's clock frequency to the function in HZ.
*
** Return Value:
*  - uart_std_error_type_t
*    The return value returns UART_E_OK if baud rate value is within range, and returns "UART_E_NOT_OK" otherwise.
*********************************************************************************************************************/
uart_std_error_type_t uart_baud_rate_config(uint32_t baudrate, uint32_t sys_osc_clock_freq)
{
	uart_std_error_type_t return_error = UART_E_NOT_OK;
	uint16_t baudrate_register_value = 0;
	/* Checking if the baud rate value passed to the function lies withing the valid range: */
	if (0 /* TO DO */)
	{
		/* Error: baud rate value is out of range. */
		return_error = UART_E_NOT_OK;
	}
	else
	{
		/* Baud rate value is within range */
		return_error = UART_E_OK;
		baudrate_register_value = (sys_osc_clock_freq / (16UL*baudrate))-1;
		UBRRH = (uint8_t)(baudrate_register_value>> SHIFT_BY_EIGHT);
		UBRRL = (uint8_t)baudrate_register_value;
	}
	
	return return_error;
	
}


/*********************************************************************************************************************
** Function Name:
*  uart_frame_format_select
*
** Description:
*  This function defines the UART frame format by choosing the character and stop bit size.
*
** Input Parameters:
*  - uart_character_size: uart_character_size_t
*    This parameter selects the character size. For example: UART_7BIT_CHARACTER_SIZE.
*  - uart_stop_bit_size: uart_stop_bit_size_t
*    This parameter selects stop bit size. For example: UART_1STOP_BIT
*
** Return Value:
*  - uart_std_error_type_t
*    The return value returns UART_E_OK if all the passed configurations are correct, and returns "UART_E_NOT_OK" if
*    any of the configurations is wrong.
*********************************************************************************************************************/
uart_std_error_type_t uart_frame_format_select(uart_character_size_t uart_character_size, 
                                               uart_stop_bit_size_t uart_stop_bit_size)
{
	uart_std_error_type_t character_size_return_error = UART_E_NOT_OK;
	uart_std_error_type_t stop_bit_size_return_error = UART_E_NOT_OK;
	uart_std_error_type_t return_error = UART_E_NOT_OK;
	
	character_size_return_error = uart_character_size_select(uart_character_size);
	stop_bit_size_return_error  = uart_stop_bit_size_select(uart_stop_bit_size);
	
	return_error =  character_size_return_error || stop_bit_size_return_error;
	
	return return_error;
}

/*********************************************************************************************************************
** Function Name:
*  uart_synch_asynch_mode_select
*
** Description:
*  This function selects between UART Asynchronous and Synchronous modes of operation.
*
** Input Parameters:
*  - uart_operation_mode : uart_operation_mode_t
*    This parameter is used to pass user selection to the function. The options for the  user  selection  are: 
*    'UART_ASYNCHRONOUS_OPERATION', or 'UART_SYNCHRONOUS_OPERATION'. If not specified by the user, the default
*    configuration would be ''UART_ASYNCHRONOUS_OPERATION''.
*
** Return Value:
*  - uart_std_error_type_t
*    The return value returns UART_E_OK if the selected configuration is correct, and returns "UART_E_NOT_OK" if
*    the selected configuration is wrong.
*********************************************************************************************************************/
uart_std_error_type_t uart_synch_asynch_mode_select(uart_operation_mode_t uart_operation_mode)
{
	uart_std_error_type_t return_error = UART_E_NOT_OK;
	switch (uart_operation_mode)
	{
		/* Selecting UART asynchronous Operation */
		case UART_ASYNCHRONOUS_OPERATION:
		UCSRC = ((UCSRC & (~(1<<UMSEL))) | (1<<URSEL));
		return_error = UART_E_OK;
		break;
		
		/* Selecting UART synchronous Operation */
		case UART_SYNCHRONOUS_OPERATION:
		UCSRC = (UCSRC | ((1<<UMSEL)|(1<<URSEL)));
		return_error = UART_E_OK;
		break; 
		
		/* error: wrong configuration. */
		default:
		return_error = UART_E_NOT_OK;
		break;
	}
	
	return return_error;
}

/*********************************************************************************************************************
** Function Name:
*  uart_parity_mode_select
*
** Description:
*  This function defines the UART's parity mode.
*
** Input Parameters:
*  - uart_parity_mode: uart_parity_mode_t
*    This parameter passes the parity mode selection to the function. For example: UART_ODD_PARITY.
*
** Return Value:
*  - uart_std_error_type_t
*    The return value returns UART_E_OK if the selected configuration is correct, and returns "UART_E_NOT_OK" if
*    the selected configuration is wrong.
*********************************************************************************************************************/
uart_std_error_type_t uart_parity_mode_select(uart_parity_mode_t uart_parity_mode)
{
	uart_std_error_type_t return_error = UART_E_NOT_OK;
	
	switch (uart_parity_mode)
	{
		case UART_PARITY_DISABLED:
		UCSRC = ((UCSRC & (~((1<<UPM1)|(1<<UPM0)))) | (1<<URSEL));
		return_error = UART_E_OK;
		break;
		
		case UART_EVEN_PARITY:
		UCSRC = ((UCSRC & (~(1<<UPM0))) | ((1<<UPM1)|(1<<URSEL)));
		return_error = UART_E_OK;
		break;
		
		case UART_ODD_PARITY:
		UCSRC = (UCSRC | ((1<<UPM1)|(1<<UPM0)|(1<<URSEL)));
		return_error = UART_E_OK;
		break;
		/* error: wrong configuration. */
		default:
		return_error = UART_E_NOT_OK;
		break;
	}
	
	return return_error;
}

/*********************************************************************************************************************
** Function Name:
*  uart_clock_polarity_select
*
** Description:
*  This function defines the UART's clock polarity.
*
** Input Parameters:
*  - uart_clock_polarity: uart_clock_polarity_t
*    This parameter passes the clock polarity selection to the function. For example: UART_CLOCK_POLARITY_1.
*
** Return Value:
*  - uart_std_error_type_t
*    The return value returns UART_E_OK if the selected configuration is correct, and returns "UART_E_NOT_OK" if
*    the selected configuration is wrong.
*********************************************************************************************************************/
uart_std_error_type_t uart_clock_polarity_select(uart_clock_polarity_t uart_clock_polarity)
{
	uart_std_error_type_t return_error = UART_E_NOT_OK;
	switch(uart_clock_polarity)
	{
		case UART_CLOCK_POLARITY_0:
		UCSRC = ((UCSRC & (~(1<<UCPOL))) | (1<<URSEL));
		return_error = UART_E_OK;
		break;
		
		case UART_CLOCK_POLARITY_1:
		UCSRC = (UCSRC | ((1<<UCPOL)|(1<<URSEL)));
		return_error = UART_E_OK;
		break;
		/* error: wrong configuration. */
		default:
		return_error = UART_E_NOT_OK;
	}
	
	return return_error;
	
}

/*********************************************************************************************************************
** Function Name:
*  uart_transmitter_enable
*
** Description:
*  This function enables the UART Transmitter.
*
** Input Parameters:
*  - void
*
** Return Value:
*  - void
*
*********************************************************************************************************************/
void uart_transmitter_enable(void)
{
	BIT_SET(UCSRB, TXEN);
}

/*********************************************************************************************************************
** Function Name:
*  uart_transmitter_disable
*
** Description:
*  This function disables the UART transmitter.
*
** Input Parameters:
*  - void
*
** Return Value:
*  - void
*
*********************************************************************************************************************/
void uart_transmitter_disable(void)
{
	BIT_CLEAR(UCSRB, TXEN);
}

/*********************************************************************************************************************
** Function Name:
*  uart_transmit_complete_interrupt_enable
*
** Description:
*  This function enables the UART transmit complete interrupt.
*
** Input Parameters:
*  - void
*
** Return Value:
*  - void
*
*********************************************************************************************************************/
void uart_transmit_complete_interrupt_enable(void)
{
	BIT_SET(UCSRB, UDRIE);
}

/*********************************************************************************************************************
** Function Name:
*  uart_transmit_complete_interrupt_disable
*
** Description:
*  This function disables the UART transmit complete interrupt.
*
** Input Parameters:
*  - void
*
** Return Value:
*  - void
*
*********************************************************************************************************************/
void uart_transmit_complete_interrupt_disable(void)
{
	BIT_CLEAR(UCSRB, UDRIE);
}

/*********************************************************************************************************************
** Function Name:
*  uart_transmit_complete_interrupt_callback_set
*
** Description:
*  This function is used to pass the address of the callback function to the UART driver, in case the transmit complete
*  interrupt is enabled.
*
** Input Parameters:
*  - void (*tx_complete_callback)(void)
*    Passes the address of the function that will be executed in the interrupt service routine when the transmit complete 
*    interrupt fires.
*
** Return Value:
*  - void
*
*********************************************************************************************************************/
extern void uart_transmit_complete_interrupt_callback_set(void (*tx_complete_callback)(void))
{
	g_tx_complete_callback = tx_complete_callback; /* Call the transmitter callback */
}

/*********************************************************************************************************************
** Function Name:
*  uart_transmitter_is_ready
*
** Description:
*  This function returns the status of the UART transmitter.
*  Note that In a polling-based implementation, you need to call this API before sending data using the USART to check
*  the availability of the UART transmitter, otherwise written data will be ignored by the USART Transmitter.
*
** Input Parameters:
*  - void
*
** Return Value:
*  - uart_is_ready_t
*    Returns "UART_READY" if the UART transmitter is ready to receive new data, and "UART_NOT_READY" if the transmit-
*    ter isn't ready to receive new data.
*
*********************************************************************************************************************/
uart_is_ready_t uart_transmitter_is_ready(void)
{
	uart_is_ready_t return_value;
	
	return_value = BIT_GET(UCSRA, UDRE);
	
	return return_value;
}

/*********************************************************************************************************************
** Function Name:
*  uart_data_write
*
** Description:
*  Writes data to the UART data register to be sent by the UART transmitter.
*
** Input Parameters:
*  - data_byte: uint8_t
*    Passes the data to be sent by the UART transmitter.
*
** Return Value:
*  - void
*
*********************************************************************************************************************/
void uart_data_write(uint8_t data_byte)
{
	UDR = data_byte;
}

/*********************************************************************************************************************
** Function Name:
*  uart_receiver_enable
*
** Description:
*  This function enables the UART receiver.
*
** Input Parameters:
*  - void
*
** Return Value:
*  - void
*
*********************************************************************************************************************/
void uart_receiver_enable(void)
{
	BIT_SET(UCSRB, RXEN);
}

/*********************************************************************************************************************
** Function Name:
*  uart_receiver_disable
*
** Description:
*  This function disables the UART receiver.
*
** Input Parameters:
*  - void
*
** Return Value:
*  - void
*
*********************************************************************************************************************/
void uart_receiver_disable(void)
{
	BIT_CLEAR(UCSRB, RXEN);
}

/*********************************************************************************************************************
** Function Name:
*  uart_receive_complete_interrupt_enable
*
** Description:
*  This function enables the UART receive complete interrupt.
*
** Input Parameters:
*  - void
*
** Return Value:
*  - void
*
*********************************************************************************************************************/
void uart_receive_complete_interrupt_enable(void)
{
	BIT_SET(UCSRB, RXCIE);
}


/*********************************************************************************************************************
** Function Name:
*  uart_receive_complete_interrupt_disable
*
** Description:
*  This function disables the UART receive complete interrupt.
*
** Input Parameters:
*  - void
*
** Return Value:
*  - void
*
*********************************************************************************************************************/
void uart_receive_complete_interrupt_disable(void)
{
		BIT_CLEAR(UCSRB, RXCIE);
}

/*********************************************************************************************************************
** Function Name:
*  uart_receive_complete_interrupt_callback_set
*
** Description:
*  This function is used to pass the address of the callback function to the UART driver, in case the receive complete
*  interrupt is enabled.
*
** Input Parameters:
*  - void (*rx_complete_callback)(void)
*    Passes the address of the function that will be executed in the interrupt service routine when the receive complete
*    interrupt fires.
*
** Return Value:
*  - void
*
*********************************************************************************************************************/
void uart_receive_complete_interrupt_callback_set(void (*rx_complete_callback)(void))
{
	g_rx_complete_callback = rx_complete_callback;
}

/*********************************************************************************************************************
** Function Name:
*  uart_receiver_is_ready
*
** Description:
*  This function returns the status of the UART receiver.
*  Note that In a polling-based implementation, you need to call this API to check for the receipt of new data.
** Input Parameters:
*  - void
*
** Return Value:
*  - uart_is_ready_t
*    Returns "UART_READY" if the UART receiver has received new data, and "UART_NOT_READY" if the receiver has no
*    data to be read.
*
*********************************************************************************************************************/
uart_is_ready_t uart_receiver_is_ready(void)
{
		uart_is_ready_t return_value;
		
		return_value = BIT_GET(UCSRA, RXC);
		
		return return_value;
}


/*********************************************************************************************************************
** Function Name:
*  uart_data_read
*
** Description:
*  This function returns the data received in the UART data register.
*
** Input Parameters:
*  - void
*
** Return Value:
*  - uint8_t
*    Returns the data in the UART receiver register.
*
*********************************************************************************************************************/
uint8_t uart_data_read(void)
{
	return UDR;
	
}


/*********************************************************************************************************************
                                          << Private Function Definitions >>
*********************************************************************************************************************/
/*********************************************************************************************************************
Interrupt service routine definition for the UART transmit ready interrupt
*********************************************************************************************************************/
ISR(USART_UDRE_vect)
{
	g_tx_complete_callback();
}

/*********************************************************************************************************************
Interrupt service routine definition for the UART receive complete interrupt.
*********************************************************************************************************************/
ISR(USART_RXC_vect)
{
	g_rx_complete_callback();
}
/*********************************************************************************************************************
** Function Name:
*  uart_character_size_select
*
** Description:
*  This function configures the UART to work with the selected character size passed to it.
*
** Input Parameters:
*  - uart_character_size: uart_character_size_t
*    This parameters is used to pass user's selection of character size to the function. Different options can be 
*    found in the specification of the datatype. 
*
** Return Value:
*  - uart_std_error_type_t
*    The return value returns UART_E_OK if the selected configuration is correct, and returns "UART_E_NOT_OK" if
*    the selected configuration is wrong.
*********************************************************************************************************************/
static uart_std_error_type_t uart_character_size_select(uart_character_size_t uart_character_size)
{
	uart_std_error_type_t return_error = UART_E_NOT_OK;
	
	switch (uart_character_size)
	{
		/* Selecting 5-bit Character size --> UCSZ2 = 0 and UCSZ1:0 = 00 */
		case UART_5BIT_CHARACTER_SIZE:
		BIT_CLEAR(UCSRB, UCSZ2);
		UCSRC = ((UCSRC & UCSZ_BITS_MASK_WITH_ZEROs) | UCSZ_5BIT_CHAR_SIZE_SELECTED);
		break;
		
		/* Selecting 6-bit Character size --> UCSZ2 = 0 and UCSZ1:0 = 01 */ 
		case UART_6BIT_CHARACTER_SIZE:
		BIT_CLEAR(UCSRB, UCSZ2);
		UCSRC = ((UCSRC & UCSZ_BITS_MASK_WITH_ZEROs) | UCSZ_6BIT_CHAR_SIZE_SELECTED);
		break;
		
		/* Selecting 7-bit Character size --> UCSZ2 = 0 and UCSZ1:0 = 10 */
		case UART_7BIT_CHARACTER_SIZE:
		BIT_CLEAR(UCSRB, UCSZ2);
		UCSRC = ((UCSRC & UCSZ_BITS_MASK_WITH_ZEROs) | UCSZ_7BIT_CHAR_SIZE_SELECTED);
		break;
		
		/* Selecting 8-bit Character size --> UCSZ2 = 0 and UCSZ1:0 = 11 */
		case UART_8BIT_CHARACTER_SIZE:
		BIT_CLEAR(UCSRB, UCSZ2);
		UCSRC = ((UCSRC & UCSZ_BITS_MASK_WITH_ZEROs) | UCSZ_8BIT_CHAR_SIZE_SELECTED);
		break;
		
		/* Selecting 9-bit Character size --> UCSZ2 = 1 and UCSZ1:0 = 11*/
		case UART_9BIT_CHARACTER_SIZE:
		BIT_SET(UCSRB, UCSZ2);
		UCSRC = ((UCSRC & UCSZ_BITS_MASK_WITH_ZEROs) | UCSZ_9BIT_CHAR_SIZE_SELECTED);
		break;
		
		/* Error: Wrong configurations */
		default:
		return_error = UART_E_NOT_OK;
		break;
	}
	
	return return_error;
}

/*********************************************************************************************************************
** Function Name:
*  uart_stop_bit_size_select
*
** Description:
*  This function configures the UART to work with the selected stop bit size passed to it.
*
** Input Parameters:
*  - uart_stop_bit_size: uart_stop_bit_size_t
*    This parameters is used to pass the stop bit size selection to the function.
*
** Return Value:
*  - uart_std_error_type_t
*    The return value returns UART_E_OK if the selected configuration is correct, and returns "UART_E_NOT_OK" if
*    the selected configuration is wrong.
*********************************************************************************************************************/
static uart_std_error_type_t uart_stop_bit_size_select(uart_stop_bit_size_t uart_stop_bit_size)
{
		uart_std_error_type_t return_error = UART_E_NOT_OK;
		
		switch (uart_stop_bit_size)
		{
			/* Selecting 1 Stop Bit to be inserted by the Transmitter */
			case UART_1STOP_BIT:
			UCSRC = ((UCSRC & (~(1<<USBS))) | (1<<URSEL));
			return_error = UART_E_OK;
			break;
			
			/* Selecting 2 Stop Bits to be inserted by the Transmitter */
			case UART_2STOP_BIT:
			UCSRC = (UCSRC | ((1<<USBS)|(1<<URSEL)));
			return_error = UART_E_OK;
			break;
			
			/* error: wrong configuration. */
			default:
			return_error = UART_E_NOT_OK;
		}
		
		return return_error;
}

/*********************************************************************************************************************
                                                << End of File >>
*********************************************************************************************************************/