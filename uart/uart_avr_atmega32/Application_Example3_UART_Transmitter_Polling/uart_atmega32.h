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
*  uart_atmega32.h 
* 
** Description:
*  This file contains the public programming interfaces for the device driver of UART peripheral of the atmega32
*  microcontroller.
*********************************************************************************************************************/


/*********************************************************************************************************************
                                               << Header Guard >>
*********************************************************************************************************************/
#ifndef UART_ATMEGA32_H_
#define UART_ATMEGA32_H_

/*********************************************************************************************************************
                                               << File Inclusions >>
*********************************************************************************************************************/
#include <stdint.h>

/*********************************************************************************************************************
                                               << Public Constants >>
*********************************************************************************************************************/


/*********************************************************************************************************************
                                               << Public Data Types >>
*********************************************************************************************************************/
typedef enum
{
	UART_E_OK = 0,
	UART_E_NOT_OK = 1
	} uart_std_error_type_t;
	
typedef enum
{
	UART_NOT_READY = 0,
	UART_READY = 1
	} uart_is_ready_t;

typedef enum
{
	UART_ASYNCHRONOUS_OPERATION = 0,
	UART_SYNCHRONOUS_OPERATION
	} uart_operation_mode_t;

typedef enum
{
	UART_PARITY_DISABLED = 0,
	UART_ODD_PARITY,
	UART_EVEN_PARITY
	} uart_parity_mode_t;
	
typedef enum
{
	UART_5BIT_CHARACTER_SIZE = 0, 
	UART_6BIT_CHARACTER_SIZE, 
	UART_7BIT_CHARACTER_SIZE,
	UART_8BIT_CHARACTER_SIZE,
	UART_9BIT_CHARACTER_SIZE
	} uart_character_size_t;
	
typedef enum
{
	UART_1STOP_BIT = 0,
	UART_2STOP_BIT
	} uart_stop_bit_size_t;
	
	
typedef enum
{
	UART_CLOCK_POLARITY_0 = 0,
	UART_CLOCK_POLARITY_1
	}uart_clock_polarity_t;
/*********************************************************************************************************************
                                           << Public Function Declarations >>
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
*    This parameter is used to pass the microcontroller's clock frequency in HZ to the function.
* 
** Return Value:
*  - uart_std_error_type_t
*    The return value returns UART_E_OK if baud rate value is within range, and returns "UART_E_NOT_OK" otherwise.
*********************************************************************************************************************/
extern uart_std_error_type_t uart_baud_rate_config(uint32_t baudrate, uint32_t sys_osc_clock_freq);


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
extern uart_std_error_type_t uart_frame_format_select(uart_character_size_t uart_character_size, uart_stop_bit_size_t uart_stop_bit_size);

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
extern uart_std_error_type_t uart_synch_asynch_mode_select(uart_operation_mode_t uart_operation_mode);


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
extern uart_std_error_type_t uart_parity_mode_select(uart_parity_mode_t uart_parity_mode);


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
extern uart_std_error_type_t uart_clock_polarity_select(uart_clock_polarity_t uart_clock_polarity);


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
*********************************************************************************************************************/
extern void uart_transmitter_enable(void);


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
*********************************************************************************************************************/
extern void uart_transmitter_disable(void);


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
*********************************************************************************************************************/
extern void uart_transmit_complete_interrupt_enable(void);


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
extern void uart_transmit_complete_interrupt_disable(void);


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
extern void uart_transmit_complete_interrupt_callback_set(void (*tx_complete_callback)(void));


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
extern uart_is_ready_t uart_transmitter_is_ready(void);


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
extern void uart_data_write(uint8_t data_byte);


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
extern void uart_receiver_enable(void);


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
extern void uart_receiver_disable(void);


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
extern void uart_receive_complete_interrupt_enable(void);


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
extern void uart_receive_complete_interrupt_disable(void);


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
extern void uart_receive_complete_interrupt_callback_set(void (*rx_complete_callback)(void));


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
extern uart_is_ready_t uart_receiver_is_ready(void);


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
*********************************************************************************************************************/
extern uint8_t uart_data_read(void);


#endif /* UART_ATMEGA32_H_ */ 
/*********************************************************************************************************************
                                                    << End of File >>
*********************************************************************************************************************/