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
	UART_CLOAK_POLARITY_0 = 0,
	UART_CLOAK_POLARITY_1
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
*    This parameter is used to select the desired baud rate.
*  - sys_Osc_clock_freq: uint32_t
*    This parameter is used to pass the microcontroller clock frequency to the function in HZ.
* 
** Return Value:
*  - uart_std_error_type_t
*    The return value returns UART_E_OK if all the passed configurations are correct, and returns "UART_E_NOT_OK" if
*    any of the configurations is wrong.
*********************************************************************************************************************/
extern uart_std_error_type_t uart_baud_rate_config(uint32_t baudrate, uint32_t sys_Osc_clock_freq);


/*********************************************************************************************************************
** Function Name:
*
*
** Description:
*
*
** Input Parameters:
*  - :
*    This parameter is used to select
*
** Return Value:
*  - uart_std_error_type_t
*    The return value returns UART_E_OK if all the passed configurations are correct, and returns "UART_E_NOT_OK" if
*    any of the configurations is wrong.
*********************************************************************************************************************/
extern uart_std_error_type_t uart_frame_format_select(uart_character_size_t uart_character_size, uart_stop_bit_size_t uart_stop_bit_size);


/*********************************************************************************************************************
** Function Name:
*
*
** Description:
*
*
** Input Parameters:
*  - :
*    This parameter is used to select
*
** Return Value:
*  - uart_std_error_type_t
*    The return value returns UART_E_OK if the selected configuration is correct, and returns "UART_E_NOT_OK" if
*    the selected configuration is wrong.
*********************************************************************************************************************/
extern uart_std_error_type_t uart_synch_asynch_mode_select(uart_operation_mode_t uart_operation_mode);


/*********************************************************************************************************************
** Function Name:
*
*
** Description:
*
*
** Input Parameters:
*  - :
*    This parameter is used to select
*
** Return Value:
*  - uart_std_error_type_t
*    The return value returns UART_E_OK if the selected configuration is correct, and returns "UART_E_NOT_OK" if
*    the selected configuration is wrong.
*********************************************************************************************************************/
extern uart_std_error_type_t uart_uart_parity_mode_select(uart_parity_mode_t uart_parity_mode);


/*********************************************************************************************************************
** Function Name:
*
*
** Description:
*
*
** Input Parameters:
*  - :
*    This parameter is used to select
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
*
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
*
*
** Input Parameters:
*  - void
*
** Return Value:
*  - void
*
*********************************************************************************************************************/
extern void uart_transmitter_disable(void);


/*********************************************************************************************************************
** Function Name:
*
*
** Description:
*
*
** Input Parameters:
*  - void
*
** Return Value:
*  - void
*
*********************************************************************************************************************/
extern void uart_transmit_complete_interrupt_enable(void);


/*********************************************************************************************************************
** Function Name:
*
*
** Description:
*
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
*
*
** Description:
*
*
** Input Parameters:
*  - void (*tx_complete_callback)(void)
*    This parameter is used to pass an address to the function that will be executed in the TXC interrupt routine.
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
*
*
** Description:
*
*
** Input Parameters:
*  - :
*    This parameter is used to select
*
** Return Value:
*  - uart_std_error_type_t
*
*********************************************************************************************************************/
extern void uart_data_write(uint8_t data_byte);


/*********************************************************************************************************************
** Function Name:
*
*
** Description:
*
*
** Input Parameters:
*  - :
*    This parameter is used to select
*
** Return Value:
*  - uart_std_error_type_t
*
*********************************************************************************************************************/
extern void uart_receiver_enable(void);


/*********************************************************************************************************************
** Function Name:
*
*
** Description:
*
*
** Input Parameters:
*  - :
*    This parameter is used to select
*
** Return Value:
*  - uart_std_error_type_t
*
*********************************************************************************************************************/
extern void uart_receiver_disable(void);


/*********************************************************************************************************************
** Function Name:
*
*
** Description:
*
*
** Input Parameters:
*  - :
*    This parameter is used to select
*
** Return Value:
*  - uart_std_error_type_t
*
*********************************************************************************************************************/
extern void uart_receive_complete_interrupt_enable(void);


/*********************************************************************************************************************
** Function Name:
*
*
** Description:
*
*
** Input Parameters:
*  - :
*    This parameter is used to select
*
** Return Value:
*  - uart_std_error_type_t
*
*********************************************************************************************************************/
extern void uart_receive_complete_interrupt_disable(void);


/*********************************************************************************************************************
** Function Name:
*
*
** Description:
*
*
** Input Parameters:
*  - :
*    This parameter is used to select
*
** Return Value:
*  - uart_std_error_type_t
*
*********************************************************************************************************************/
extern void uart_receive_complete_interrupt_callback_set(void (*rx_complete_callback)(void));


/*********************************************************************************************************************
** Function Name:
*
*
** Description:
*
*
** Input Parameters:
*  - :
*    This parameter is used to select
*
** Return Value:
*  - uart_std_error_type_t
*
*********************************************************************************************************************/
extern uart_is_ready_t uart_receiver_is_ready(void);


/*********************************************************************************************************************
** Function Name:
*
*
** Description:
*
*
** Input Parameters:
*  - :
*    This parameter is used to select
*
** Return Value:
*  - uart_std_error_type_t
*
*********************************************************************************************************************/
extern uint8_t uart_data_read(void);





#endif /* UART_ATMEGA32_H_ */ 
/*********************************************************************************************************************
                                               << End of File >>
*********************************************************************************************************************/