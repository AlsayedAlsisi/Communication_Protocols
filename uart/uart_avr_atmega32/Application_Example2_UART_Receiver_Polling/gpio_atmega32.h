/*********************************************************************************************************************
* Author : Alsayed Alsisi
* Date   : Saturday, November 07, 2020
* Version: 1.0
* Contact: alsayed.alsisi@gmail.com
* License:
* You have the right to use the file as you wish in any educational or commercial purposes under the following condit-
  ions:
* - This file is to be used as is. No modifications are to be made to any part of the file, including this section.
* - This section is not to be removed under any circumstances.
* - Parts of the file may be used separately under the condition they are not modified, and preceded by this section.
* - Any bug encountered in this file or parts of it should be reported to the email address given above to be fixed.
* - No warranty is expressed or implied by the publication or distribution of this source code.
*********************************************************************************************************************/
/*********************************************************************************************************************
* File Information:
** File Name:
*  gpio_atmega32.h
* 
** Description:
*  This file contains the public programming interfaces for the device driver of the gpio peripheral of the ATmega32 
*  microcontroller. This file can be used with other microcontrollers compatible with the ATmega32 like:
*  ATmega16, ATmega16A 
*********************************************************************************************************************/


/*********************************************************************************************************************
                                               << Header Guard >>
*********************************************************************************************************************/
#ifndef GPIO_ATMEGA32_H_
#define GPIO_ATMEGA32_H_

/*********************************************************************************************************************
                                               << File Inclusions >>
*********************************************************************************************************************/
#include <stdint.h>

/*********************************************************************************************************************
                                               << Public Data Types >>
*********************************************************************************************************************/
typedef enum{
	GPIO_PIN0 = 0,
	GPIO_PIN1 = 1,
	GPIO_PIN2 = 2,
	GPIO_PIN3 = 3,
	GPIO_PIN4 = 4,
	GPIO_PIN5 = 5,
	GPIO_PIN6 = 6,
	GPIO_PIN7 = 7
} gpio_pin_t;

typedef enum
{
	GPIO_E_OK     = 0,
	GPIO_E_NOT_OK = 1
} gpio_std_return_error_t;

typedef enum{
	GPIO_PORTA = 0,
	GPIO_PORTB,
	GPIO_PORTC,
	GPIO_PORTD
} gpio_port_t;


typedef enum {
	GPIO_INPUT  = 0x00,
	GPIO_OUTPUT = 0xff
} gpio_direction_t;

typedef enum{
	GPIO_PIN_LOW  = 0x00,
	GPIO_PIN_HIGH = 0x01
} gpio_pin_level_t;


/*********************************************************************************************************************
                                               << Public Constants >>
*********************************************************************************************************************/


/*********************************************************************************************************************
                                          << Public Variable Declarations >>
*********************************************************************************************************************/


/*********************************************************************************************************************
                                           << Public Function Declarations >>
*********************************************************************************************************************/
/*********************************************************************************************************************
** Function Name:
*  gpio_port_config
*
** Description:
*  The following function is used to initialize an entire port as input or output. In case of setting the port as 
*  output, the init value sets the initial state of the port pins to HIGH or LOW. And in case of setting the port 
*  as  input, initial state can be used to set pull-up resistors.
*
** Input Parameters:
*  - gpio_port: gpio_port_t
*    This parameter is used to pass the certain port to be configured to the function. Example: GPIO_PORTA.
*  - gpio_port_direction: gpio_direction_t
*    This parameter passes the desired port direction to the function. The port can be configured to be input by
*    passing "GPIO_INPUT", or output by passing "GPIO_OUTPUT".
*  - gpio_port_init_value: uint8_t
*    This parameter is used to set the initial state of the port pins as HIGH or low, in case the port is configured
*    to be output, or to set pull-up resistors on some/all pins, in case the port is configured to be output. 
*
** Return Value:
*  - gpio_std_return_error_t
*    Returns 'GPIO_E_OK' for a correct port, and 'GPIO_E_NOT_OK' for a wrong value.
*    
** Use Examples:
*  - Setting PORT B as output with initial value of all pins as HIGH:
*    gpio_port_config(GPIO_PORTB, GPIO_OUTPUT, 0xff);
*  - Setting PORT B as input with all pull-up resistors enabled:
*    gpio_port_config(GPIO_PORTD, GPIO_INPUT, 0xff);
*  - Using the return value in error handling:
*    gpio_std_return_error_t return_error;
*    return_error = gpio_port_config(GPIO_PORTD, GPIO_INPUT, 0xff);
*    if(GPIO_E_OK != return_error)
*    { //Report error}
*********************************************************************************************************************/
extern gpio_std_return_error_t gpio_port_config(gpio_port_t gpio_port, gpio_direction_t gpio_port_direction, uint8_t gpio_port_init_value);



/*********************************************************************************************************************
** Function Name:
*  gpio_pins_config
*
** Description:
*  The following function is used to initialize a group of pins as input or output. In case of setting the pins as
*  output, the init value sets the initial state of the port pins to HIGH or LOW. And in case of setting the port
*  as  input, init value can be used to set pull-up resistors.
*
** Input Parameters:
*  - gpio_port: gpio_port_t
*    This parameter is used to pass the certain port to be configured to the function. Example: GPIO_PORTA.
*  - gpio_pins: uint8_t
*    This parameter is used to pass the certain pins to be configured to the function. Example: (1<<GPIO_PIN7).
*  - gpio_pins_direction: gpio_direction_t
*    This parameter passes the desired pins direction to the function. The pins can be configured to be input by
*    passing "GPIO_INPUT", or output by passing "GPIO_OUTPUT".
*  - gpio_pins_init_value: uint8_t
*    This parameter is used to set the initial state of the pins as HIGH or low, in case the pins are configured
*    to be output, or to set pull-up resistors on some/all pins, in case the pins are configured to be output.
*
** Return Value:
*  - gpio_std_return_error_t
*    Returns 'GPIO_E_OK' for a correct port, and 'GPIO_E_NOT_OK' for a wrong value.
*
** Use Examples:
*  - setting PIN 1 and PIN 7  of PORT D as output with initial value HIGH:
*    gpio_pins_config(GPIO_PORTD, ((1<<GPIO_PIN7)|(1<<GPIO_PIN0)), GPIO_OUTPUT, 0b10000010);
*    Note that this can also be written as:
*    gpio_pins_config(GPIO_PORTD, ((1<<GPIO_PIN7)|(1<<GPIO_PIN0)), GPIO_OUTPUT, ((1<<GPIO_PIN7)|(1<<GPIO_PIN0)));
*  - setting PIN 1 and PIN 7  of PORT D as input with PULL-UP resistor on PIN 7 only:
*    gpio_pins_config(GPIO_PORTD, ((1<<GPIO_PIN7)|(1<<GPIO_PIN0)), GPIO_INPUT, 0b10000000);
*    Note that this can also be written as:
*    gpio_pins_config(GPIO_PORTD, ((1<<GPIO_PIN7)|(1<<GPIO_PIN0)), GPIO_INPUT, (1<<GPIO_PIN7));
*  - Using the return value in error handling:
*    gpio_std_return_error_t return_error;
*    return_error = gpio_pins_config(GPIO_PORTD, ((1<<GPIO_PIN7)|(1<<GPIO_PIN0)), GPIO_INPUT, 0b10000000);
*    if(GPIO_E_OK != return_error)
*    { //Report error}
*********************************************************************************************************************/
extern gpio_std_return_error_t gpio_pins_config(gpio_port_t gpio_port, uint8_t gpio_pins, gpio_direction_t gpio_pins_direction, uint8_t gpio_pins_init_value);



/*********************************************************************************************************************
** Function Name:
*  gpio_pins_config
*
** Description:
* The following function is used to initialize a single pin as input or output. In case of setting the pin as output, 
* the initial_state sets the initial value of the pin as HIGH or LOW.  And in case of setting the pin as input, the 
* init value can be used to enable pull-up resistor on that pin.
*
** Input Parameters:
*  - gpio_port: gpio_port_t
*    This parameter is used to pass the certain pin port to be configured to the function. Example: GPIO_PORTA.
*  - gpio_pin: gpio_pin_t
*    This parameter is used to pass the certain pin to be configured to the function. Example: GPIO_PIN7.
*  - gpio_pin_direction: gpio_direction_t
*    This parameter passes the desired pin direction to the function. The pin can be configured to be input by
*    passing "GPIO_INPUT", or output by passing "GPIO_OUTPUT".
*  - gpio_pin_init_value: gpio_pin_level_t
*    This parameter is used to set the initial state of the pins as HIGH or low, in case the pin is configured
*    to be output, or to set pull-up resistors on that pin, in case the pin are configured to be output.
*
** Return Value:
*  - gpio_std_return_error_t
*    Returns 'GPIO_E_OK' for a correct port and pin level, and 'GPIO_E_NOT_OK' for a wrong a wrong port or pin level.
*
** Use Examples:
*  - Setting PIN 0  of  PORT B as output with initial value HIGH:
*  	 gpio_pin_config(GPIO_PORTB, GPIO_PIN0, GPIO_OUTPUT, GPIO_PIN_HIGH);
*  - Setting PIN 0  of  PORT D as input with pull-up resistor enabled:
*  	 gpio_pin_config(GPIO_PORTD,  GPIO_PIN0, GPIO_INPUT, GPIO_PIN_HIGH);
*********************************************************************************************************************/
extern gpio_std_return_error_t gpio_pin_config(gpio_port_t gpio_port, gpio_pin_t gpio_pin, gpio_direction_t gpio_pin_direction, gpio_pin_level_t gpio_pin_init_level);



/*********************************************************************************************************************
** Function Name:
*  gpio_port_write
*
** Description:
*  The following function is used to output certain values on all the pins of the selected port in case the port is 
*  set as output. Or to enable/disable the pull-up resistors on the pins of the selected port in case the port is set 
*  as input.
*
** Input Parameters:
*  - gpio_port: gpio_port_t
*    This parameter is used to pass the certain port to be configured to the function. Example: GPIO_PORTA.
*  - gpio_port_value: uint8_t
*    This parameter is used to set the state of the port pins as HIGH or LOW, in case the port is configured
*    to be output, or to set pull-up resistors on some/all pins, in case the port is configured to be output.
*
** Return Value:
*  - gpio_std_return_error_t
*    Returns 'GPIO_E_OK' for a correct port, and 'GPIO_E_NOT_OK' for a wrong value.
*
** Use Examples:
*  [1] Output +5v on PIN_7, PIN_6, PIN_5, and PIN_4 and 0v on other pins. PORT A is configured as as output:
*      gpio_port_write(GPIO_PORTA, 0xf0);
*  [2] Enable the pull-up resistors on PIN_7, PIN_6, PIN_5, and PIN_4 pins. PORT A is configured as input:
*      gpio_port_write(GPIO_PORTA, 0xf0);
*  [3] Using the return value in error handling:
*      gpio_std_return_error_t return_error;
*      return_error = gpio_port_write(GPIO_PORTD, 0xf0);
*      if(GPIO_E_OK != return_error)
*      { //Report error}
*********************************************************************************************************************/
extern gpio_std_return_error_t gpio_port_write(gpio_port_t gpio_port, uint8_t gpio_port_value);



/*********************************************************************************************************************
** Function Name:
*  gpio_pins_write
*
** Description:
*  The following function is used to output certain values  on a group of selected pins of a certain  port in case the
*  port is set as output, or to enable/disable the pull-up resistors on the selected pins in case the port is set as 
*  input.
*
** Input Parameters:
*  - gpio_port: gpio_port_t
*    This parameter is used to pass the certain port to which the pins belong to the function. Example: GPIO_PORTA.
*  - gpio_pins: uint8_t
*    This parameter passes the group of the selected pins to the function. Example: ((1<<GPIO_PIN3)|(1<<GPIO_PIN4)).
*  - gpio_pins_value: uint8_t
*    This parameter is used to set the state of the pins as HIGH or LOW, in case the port is configured to be output, 
*    or to set pull-up resistors on some/all pins, in case the port is configured to be input.
*
** Return Value:
*  - gpio_std_return_error_t
*    Returns 'GPIO_E_OK' for a correct port, and 'GPIO_E_NOT_OK' for a wrong value.
*
** Use Examples:
*  [1] Output +5v on PIN 4, and PIN 3 of PORT A, and don't affect other pins. Both pins are configured as as output:
*      gpio_pins_write(GPIO_PORTA, ((1<<GPIO_PIN4)|(1<<GPIO_PIN3)),  0b00011000);
*      - Note that this can also be written as:
*      gpio_pins_write(GPIO_PORTA, ((1<<GPIO_PIN4)|(1<<GPIO_PIN3)),  ((1<<GPIO_PIN4)|(1<<GPIO_PIN3)));
*  [2] Output +5v on PIN 4, and 0V on PIN 3 of PORT A, and don't affect other pins. Both pins are configured as as 
*      output:
*      gpio_pins_write(GPIO_PORTA, ((1<<GPIO_PIN4)|(1<<GPIO_PIN3)),  (1<<GPIO_PIN4));
*  [3] Enable the pull-up resistors on PIN_7, PIN_6 of PORT A. Both pins are configured as input:
*      gpio_pins_write(GPIO_PORTA, ((1<<GPIO_PIN7)|(1<<GPIO_PIN6)),  0b11000000);
*      - Note that this can also be written as:
*      gpio_pins_write(GPIO_PORTA, ((1<<GPIO_PIN7)|(1<<GPIO_PIN6)),  ((1<<GPIO_PIN7)|(1<<GPIO_PIN6)));
*  [4] Using the return value in error handling:
*      gpio_std_return_error_t return_error;
*      return_error = gpio_pins_write(GPIO_PORTA, (1<<GPIO_PIN7), 0x00);
*      if(GPIO_E_OK != return_error)
*      { //Report error}
*********************************************************************************************************************/
extern gpio_std_return_error_t gpio_pins_write(gpio_port_t gpio_port, gpio_pin_t gpio_pins, uint8_t gpio_pins_value);


/*********************************************************************************************************************
** Function Name:
*  gpio_pin_write
*
** Description:
*  The following function is used to output HIGH(+5V) or LOW(0V) on a selected pin of a certain  port in case the pin 
*  is configured as output, or to enable/disable the pull-up resistors on the selected pin in case the pin is 
*  configured as input.
*
** Input Parameters:
*  - gpio_port: gpio_port_t
*    This parameter is used to pass the certain port to which the pin belongs to the function. Example: GPIO_PORTA.
*  - gpio_pin: gpio_pin_t
*    This parameter passes the selected pin to be configured to the function. Example: GPIO_PIN3.
*  - gpio_pin_level: gpio_pin_level_t
*    This parameter is used to set the state of the pin as HIGH(+5V) or LOW(0V), in case the pin is configured to be
*    output, or to enable/disable the pull-up resistor on the pin, in case it is configured to be input. Example:
*    GPIO_PIN_HIGH.
* 
** Return Value:
*  - gpio_std_return_error_t
*    Returns 'GPIO_E_OK' for correct configurations, and 'GPIO_E_NOT_OK' if any of the passed configurations is 
*    wrong.
*
** Use Examples:
*  [1] Output +5v on PIN 4 of PORT A, and leave other pins as is. The pin is configured as as output:
*      gpio_pin_write(GPIO_PORTA, GPIO_PIN4,  GPIO_PIN_HIGH);
*  [2] Output 0V on PIN 3 of PORT C, and leave other pins as is. The pin is configured as as output:
*      gpio_pin_write(GPIO_PORTC, GPIO_PIN3,  GPIO_PIN_LOW);
*  [3] Using the return value in error handling:
*      gpio_std_return_error_t return_error;
*      return_error = gpio_pin_write(GPIO_PORTC, GPIO_PIN3,  GPIO_PIN_LOW);
*      if(GPIO_E_OK != return_error)
*      { //Report error}
*********************************************************************************************************************/
extern gpio_std_return_error_t gpio_pin_write(gpio_port_t gpio_port, gpio_pin_t gpio_pin, 
                                              gpio_pin_level_t gpio_pin_level);


/*********************************************************************************************************************
** Function Name:
*  gpio_port_read
*
** Description:
*  The following function is used to read the value on all the pins of a port that is configured as input.
*
** Input Parameters:
*  - gpio_port: gpio_port_t
*    This parameter is used to pass the certain port to the function. Example: GPIO_PORTA.
*  - gpio_port_value: uint8*
*    This a pointer to read back the value of the port in the caller function.
*
** Return Value:
*  - gpio_std_return_error_t
*    Returns 'GPIO_E_OK' for correct port, and 'GPIO_E_NOT_OK' for wrong value.
*
** Use Examples:
*  [1] Read the value on the pins of PORT A:
*      uint8_t port_value;
*      gpio_port_read(GPIO_PORTA, &port_value); 
*  [2] Using the return value in error handling:
*      gpio_std_return_error_t return_error;
*      return_error = gpio_port_read(GPIO_PORTA, &port_value); 
*      if(GPIO_E_OK != return_error)
*      { //Report error}
*********************************************************************************************************************/
extern gpio_std_return_error_t gpio_port_read(gpio_port_t gpio_port, uint8_t* gpio_port_value);



/*********************************************************************************************************************
** Function Name:
*  gpio_pins_read
*
** Description:
*  The following function is used to read the values on group of pins of a certain port that are configured as input.
*
** Input Parameters:
*  - gpio_port: gpio_port_t
*    This parameter is used to pass the certain port, to which the pins belong, to the function. Example: GPIO_PORTA.
*  - gpio_pins: uint8_t
*    This parameter passes the group of the selected pins to the function.
*  - gpio_pins_value: uint8_t*
*    This a pointer to read back the value of the port in the caller function.
*
** Return Value:
*  - gpio_std_return_error_t
*    Returns 'GPIO_E_OK' for correct port, and 'GPIO_E_NOT_OK' for wrong value.
*
** Use Examples:
*  [1] Read the value on PIN 5 and PIN 0 of PORT A:
*      uint8_t pins_value;
*      gpio_pins_read(GPIO_PORTA, ((1<<GPIO_PIN5)|(1<<GPIO_PIN0)), &pins_value);
*      - Note that the returned value in this example, pins_value, is on the form of 0b00x0000y, where x is the value
*        of PIN 5 and y is the value of PIN 0.
*  [2] Using the return value in error handling:
*      gpio_std_return_error_t return_error;
*      return_error = gpio_pins_read(GPIO_PORTA, ((1<<GPIO_PIN5)|(1<<GPIO_PIN0)), &pins_value);
*      if(GPIO_E_OK != return_error)
*      { //Report error}
*********************************************************************************************************************/
extern gpio_std_return_error_t gpio_pins_read(gpio_port_t gpio_port, gpio_pin_t gpio_pins, uint8_t* gpio_pins_value);




/*********************************************************************************************************************
** Function Name:
*  gpio_pin_read
*
** Description:
* The following function is used to read the value of a single pin that is configured as input.
*
** Input Parameters:
*  - gpio_port: gpio_port_t
*    This parameter is used to pass the certain port, to which the pin belongs, to the function. Example: GPIO_PORTA.
*  - gpio_pin: gpio_pin_t
*    This parameter passes the selected pin to the function. Example: GPIO_PIN5
*  - pin_level: gpio_pin_level_t*
*    This a pointer to read back the value of the pin in the caller function.
*
** Return Value:
*  - gpio_std_return_error_t
*    Returns 'GPIO_E_OK' for correct port and pin, and 'GPIO_E_NOT_OK' if any of them is wrong
*
** Use Examples:
*  [1] Read the value on PIN 5 of PORT A:
*      uint8_t pin_level;
*      gpio_pin_read(GPIO_PORTA, GPIO_PIN5, &pin_level);
*  [2] Using the return value in error handling:
*      gpio_std_return_error_t return_error;
*      return_error = gpio_pin_read(GPIO_PORTA, GPIO_PIN5, &pin_level);
*      if(GPIO_E_OK != return_error)
*      { //Report wrong port or pin}
*********************************************************************************************************************/
extern gpio_std_return_error_t gpio_pin_read(gpio_port_t gpio_port, gpio_pin_t gpio_pin, gpio_pin_level_t* pin_level);


#endif /* GPIO_ATMEGA32_H_ */
/*********************************************************************************************************************
                                               << End of File >>
*********************************************************************************************************************/