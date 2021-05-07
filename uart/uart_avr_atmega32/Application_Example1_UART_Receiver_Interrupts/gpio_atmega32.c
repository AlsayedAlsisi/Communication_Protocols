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
*  gpio_atmega32.c
*
** Description:
*  This file contains the implementation of the device driver of the gpio peripheral of the ATmega32 microcontroller. 
*  This file can be used with other microcontrollers compatible with the ATmega32 like:
*  ATmega16, ATmega16A
*
*********************************************************************************************************************/

/*********************************************************************************************************************
                                               << File Inclusions >>
*********************************************************************************************************************/
#include <stdint.h>
#include "bit_math.h"
#include "gpio_atmega32.h"

/*********************************************************************************************************************
                                              << Private Constants >>
*********************************************************************************************************************/
#define   PORTA_REG   *((volatile uint8_t*)(0x3B))
#define   DDRA_REG    *((volatile uint8_t*)(0x3A))
#define   PINA_REG    *((volatile uint8_t*)(0x39))
	     
#define   PORTB_REG   *((volatile uint8_t*)(0x38))
#define   DDRB_REG    *((volatile uint8_t*)(0x37))
#define   PINB_REG    *((volatile uint8_t*)(0x36))
	     
#define   PORTC_REG   *((volatile uint8_t*)(0x35))
#define   DDRC_REG    *((volatile uint8_t*)(0x34))
#define   PINC_REG    *((volatile uint8_t*)(0x33))
	     
#define   PORTD_REG   *((volatile uint8_t*)(0x32))
#define   DDRD_REG    *((volatile uint8_t*)(0x31))
#define   PIND_REG    *((volatile uint8_t*)(0x30))

#define   PORT_MAX_PIN_COUNT   8
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


/*********************************************************************************************************************
                                          << Public Function Definitions >>
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
*    This parameter is used to pass the certain port to be configured to the function.
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
*********************************************************************************************************************/
gpio_std_return_error_t gpio_port_config(gpio_port_t gpio_port, gpio_direction_t gpio_port_direction, uint8_t gpio_port_init_value) 
{
	gpio_std_return_error_t return_error = GPIO_E_NOT_OK;

	switch(gpio_port)
	{
		case GPIO_PORTA:
		/* Setting the port direction: */
	    DDRA_REG = gpio_port_direction;      /* Accessing DDRA. */
    	/* Setting the initial value: */
	    PORTA_REG = gpio_port_init_value;    /* Accessing PORTA*/
		return_error = GPIO_E_OK;
		break;
		
		case GPIO_PORTB:
		/* Setting the port direction: */
	     DDRB_REG = gpio_port_direction;     /* Accessing DDRB. */
    	/* Setting the initial value: */
	    PORTB_REG = gpio_port_init_value;    /* Accessing PORTB*/
		return_error = GPIO_E_OK;
		break;
		
		case GPIO_PORTC:
		/* Setting the port direction: */
	     DDRC_REG = gpio_port_direction;     /* Accessing DDRC. */
    	/* Setting the initial value: */
	    PORTC_REG = gpio_port_init_value;    /* Accessing PORTC*/
		return_error = GPIO_E_OK;
		break;
		
		case GPIO_PORTD:
		/* Setting the port direction: */
		DDRD_REG = gpio_port_direction;      /* Accessing DDRD. */
		/* Setting the initial value: */
		PORTD_REG = gpio_port_init_value;    /* Accessing PORTD*/
		return_error = GPIO_E_OK;
		break;
		
		default:
		return_error = GPIO_E_NOT_OK;
		break;
	}
	
	return return_error;
}


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
*********************************************************************************************************************/
gpio_std_return_error_t gpio_pins_config(gpio_port_t gpio_port, uint8_t gpio_pins, gpio_direction_t gpio_pins_direction, uint8_t gpio_pins_init_value) 
{
	gpio_std_return_error_t return_error = GPIO_E_NOT_OK;

	switch(gpio_port)
	{
		case GPIO_PORTA:
		/* Setting the pins direction: */
		DDRA_REG  = (DDRA_REG & ~gpio_pins)  | (gpio_pins & gpio_pins_direction);     /* Accessing DDRA. */
		/* Setting the initial value: */
		PORTA_REG = (PORTA_REG & ~gpio_pins) | (gpio_pins & gpio_pins_init_value);    /* Accessing PORTA*/
		return_error = GPIO_E_OK;
		break;
		
		case GPIO_PORTB:
		/* Setting the pins direction: */
		DDRB_REG  =  (DDRB_REG & ~gpio_pins)  | (gpio_pins & gpio_pins_direction);    /* Accessing DDRA. */
		/* Setting the initial value: */
		PORTB_REG =  (PORTB_REG & ~gpio_pins) | (gpio_pins & gpio_pins_init_value);   /* Accessing PORTA*/
		return_error = GPIO_E_OK;
		break;
		
		case GPIO_PORTC:
		/* Setting the pins direction: */
		DDRC_REG  =  (DDRC_REG & ~gpio_pins)  | (gpio_pins & gpio_pins_direction);     /* Accessing DDRA. */
		/* Setting the initial value: */
		PORTC_REG =  (PORTC_REG & ~gpio_pins) | (gpio_pins & gpio_pins_init_value);    /* Accessing PORTA*/
		return_error = GPIO_E_OK;
		break;
		
		case GPIO_PORTD:
		/* Setting the pins direction: */
		DDRD_REG  = (DDRD_REG & ~gpio_pins)   | (gpio_pins & gpio_pins_direction);     /* Accessing DDRA. */
		/* Setting the initial value: */
		PORTD_REG =  (PORTD_REG & ~gpio_pins) | (gpio_pins & gpio_pins_init_value);    /* Accessing PORTA*/
		return_error = GPIO_E_OK;
		break;
		
		default:
		return_error = GPIO_E_NOT_OK;
		break;
	}
	
	return return_error;
}


/*********************************************************************************************************************
** Function Name:
*  gpio_pin_config
*
** Description:
*  The following function is used to initialize a single pin as input or output. In case of setting the pin as output,
*  the initial_state sets the initial value of the pin as HIGH or LOW.  And in case of setting the pin as input, the
*  init value can be used to enable pull-up resistor on that pin.
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
*********************************************************************************************************************/
gpio_std_return_error_t gpio_pin_config(gpio_port_t gpio_port, gpio_pin_t gpio_pin, gpio_direction_t gpio_pin_direction, gpio_pin_level_t gpio_pin_init_level)
{
	gpio_std_return_error_t return_error = GPIO_E_NOT_OK;

	switch(gpio_port)
	{
		case GPIO_PORTA:
		/* Setting the pin's direction: */
		DDRA_REG  =  ((DDRA_REG  & ~(1<<gpio_pin)) | (gpio_pin_direction & (1<<gpio_pin)));   /* Accessing DDRA */
		/* Setting the pin's initial value: */
		PORTA_REG =  ((PORTA_REG & ~(1<<gpio_pin)) | (gpio_pin_init_level << gpio_pin));      /* Accessing PORTA */
		return_error = GPIO_E_OK;
		break;
		
		case GPIO_PORTB:
		/* Setting the pin's direction: */
		DDRB_REG  =  ((DDRB_REG  & ~(1<<gpio_pin)) | (gpio_pin_direction & (1<<gpio_pin)));   /* Accessing DDRA */
		/* Setting the pin's initial value: */
		PORTB_REG =  ((PORTB_REG & ~(1<<gpio_pin)) | (gpio_pin_init_level << gpio_pin));      /* Accessing PORTA */
		return_error = GPIO_E_OK;
		break;
		
		case GPIO_PORTC:
		/* Setting the pin's direction: */
		DDRC_REG  =  ((DDRC_REG  & ~(1<<gpio_pin)) | (gpio_pin_direction & (1<<gpio_pin)));   /* Accessing DDRA */
		/* Setting the pin's initial value: */
		PORTC_REG =  ((PORTC_REG & ~(1<<gpio_pin)) | (gpio_pin_init_level << gpio_pin));      /* Accessing PORTA */
		return_error = GPIO_E_OK;
		break;
		
		case GPIO_PORTD:
		/* Setting the pin's direction: */
		DDRD_REG  =  ((DDRD_REG  & ~(1<<gpio_pin)) | (gpio_pin_direction & (1<<gpio_pin)));   /* Accessing DDRA */
		/* Setting the pin's initial value: */
		PORTD_REG =  ((PORTD_REG & ~(1<<gpio_pin)) | (gpio_pin_init_level << gpio_pin));      /* Accessing PORTA */
		return_error = GPIO_E_OK;
		break;
		
		default:
		return_error = GPIO_E_NOT_OK;
		break;
	}
	
	return return_error;
}

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
*********************************************************************************************************************/
gpio_std_return_error_t gpio_port_write(gpio_port_t gpio_port, uint8_t gpio_port_value)
{
	gpio_std_return_error_t return_error = GPIO_E_NOT_OK;
	
	switch (gpio_port)
	{
		
		case GPIO_PORTA:
		PORTA_REG = gpio_port_value;
		return_error = GPIO_E_OK;
		break;
		
		case GPIO_PORTB:
		PORTB_REG =  gpio_port_value;
		return_error = GPIO_E_OK;
		break;
		
		case GPIO_PORTC:
		PORTC_REG =  gpio_port_value;
		return_error = GPIO_E_OK;
		break;
		
		case GPIO_PORTD:
		PORTD_REG =  gpio_port_value;
		return_error = GPIO_E_OK;
		break;
		
		default:
		return_error = GPIO_E_NOT_OK;
		break;
	}
	
	return return_error;
}


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
*    This parameter is used to pass the certain port to be configured to the function. Example: GPIO_PORTA.
*  - gpio_pins: uint8_t
*    This parameter passes the group of the selected pins to the function. Example: ((1<<GPIO_PIN3)|(1<<GPIO_PIN4)).
*  - gpio_pins_value: uint8_t
*    This parameter is used to set the state of the pins as HIGH or LOW, in case the port is configured to be output,
*    or to set pull-up resistors on some/all pins, in case the port is configured to be output.
*
** Return Value:
*  - gpio_std_return_error_t
*    Returns 'GPIO_E_OK' for a correct port, and 'GPIO_E_NOT_OK' for a wrong value.
*********************************************************************************************************************/
gpio_std_return_error_t gpio_pins_write(gpio_port_t gpio_port, uint8_t gpio_pins, uint8_t gpio_pins_value)
{
    gpio_std_return_error_t return_error = GPIO_E_NOT_OK;
	
	switch (gpio_port)
	{
		case GPIO_PORTA:
		PORTA_REG = ((PORTA_REG & ~gpio_pins) | (gpio_pins & gpio_pins_value));
		return_error = GPIO_E_OK;
		break;
		
		case GPIO_PORTB:
		PORTB_REG = ((PORTB_REG & ~gpio_pins) | (gpio_pins & gpio_pins_value));
		return_error = GPIO_E_OK;
		break;
		
		case GPIO_PORTC:
		PORTC_REG = ((PORTC_REG & ~gpio_pins) | (gpio_pins & gpio_pins_value));
		return_error = GPIO_E_OK;
		break;
		
		case GPIO_PORTD:
		PORTD_REG = ((PORTD_REG & ~gpio_pins) | (gpio_pins & gpio_pins_value));
		return_error = GPIO_E_OK;
		break;
		
		default:
		return_error = GPIO_E_NOT_OK;
		break;
	}
	
	return return_error;
}


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
*********************************************************************************************************************/
gpio_std_return_error_t gpio_pin_write(gpio_port_t gpio_port, gpio_pin_t gpio_pin, gpio_pin_level_t gpio_pin_level) //tested
{
	  gpio_std_return_error_t return_error = GPIO_E_NOT_OK;
	  
	  if((PORT_MAX_PIN_COUNT>gpio_pin) && ((GPIO_PIN_HIGH == gpio_pin_level)||(GPIO_PIN_LOW == gpio_pin_level)))
	  {
		  switch (gpio_port)
		  {
		    case GPIO_PORTA:
		    PORTA_REG = ((PORTA_REG & ~(1<<gpio_pin)) | (gpio_pin_level << gpio_pin));
			return_error = GPIO_E_OK;
		    break;
		    
		    case GPIO_PORTB:
		    PORTB_REG = ((PORTB_REG & ~(1<<gpio_pin)) | (gpio_pin_level << gpio_pin));
			return_error = GPIO_E_OK;
		    break;
		    
		    case GPIO_PORTC:
		    PORTC_REG = ((PORTC_REG & ~(1<<gpio_pin)) | (gpio_pin_level << gpio_pin));
			return_error = GPIO_E_OK;
		    break;
		    
		    case GPIO_PORTD:
		    PORTD_REG = ((PORTD_REG & ~(1<<gpio_pin)) | (gpio_pin_level << gpio_pin));
			return_error = GPIO_E_OK;
		    break;
		    
		    default:
			return_error = GPIO_E_NOT_OK; /* Wrong Port */
		    break;
		  }
	  }
	  else
	  {
		  return_error = GPIO_E_NOT_OK;  /* Wrong pin or pin level */
	  }
	  
	  return return_error;
}


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
*********************************************************************************************************************/
gpio_std_return_error_t gpio_port_read(gpio_port_t gpio_port, uint8_t* gpio_port_value) 
{
    gpio_std_return_error_t return_error = GPIO_E_NOT_OK;
	
	switch (gpio_port)
	{
		case GPIO_PORTA:
		*gpio_port_value = PINA_REG ;
		return_error = GPIO_E_OK;
		break;
		
		case GPIO_PORTB:
		*gpio_port_value = PINB_REG ;
		return_error = GPIO_E_OK;
		break;
		
		case GPIO_PORTC:
		*gpio_port_value = PINC_REG ;
		return_error = GPIO_E_OK;
		break;
		
		case GPIO_PORTD:
		*gpio_port_value = PIND_REG ;
		return_error = GPIO_E_OK;
		break;
		
		default:
		return_error = GPIO_E_NOT_OK; /* Wrong Port */
		break;
	}
	
	return return_error;
}

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
*    This a pointer to read back the value of the port pins in the caller function.
*
** Return Value:
*  - gpio_std_return_error_t
*    Returns 'GPIO_E_OK' for correct port, and 'GPIO_E_NOT_OK' for wrong value.
*********************************************************************************************************************/
gpio_std_return_error_t gpio_pins_read(gpio_port_t gpio_port, uint8_t gpio_pins, uint8_t* gpio_pins_value)
{
    gpio_std_return_error_t return_error = GPIO_E_NOT_OK;

    switch (gpio_port)
    {
      case GPIO_PORTA:
      *gpio_pins_value = (PINA_REG & gpio_pins) ;
	  return_error = GPIO_E_OK;
      break;
      
      case GPIO_PORTB:
      *gpio_pins_value = (PINB_REG & gpio_pins) ;
	  return_error = GPIO_E_OK;
      break;
      
      case GPIO_PORTC:
      *gpio_pins_value = (PINC_REG & gpio_pins) ;
	  return_error = GPIO_E_OK;
      break;
      
      case GPIO_PORTD:
      *gpio_pins_value = (PIND_REG & gpio_pins) ;
      break;
      
      default:
      return_error = GPIO_E_NOT_OK; /* Wrong Port*/
      break;
    }
    
	return return_error;
}


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
*********************************************************************************************************************/
gpio_std_return_error_t gpio_pin_read(gpio_port_t gpio_port, gpio_pin_t gpio_pin, gpio_pin_level_t* pin_level) 
{
	gpio_std_return_error_t return_error = GPIO_E_NOT_OK;
	
	if(PORT_MAX_PIN_COUNT>gpio_pin)
	{
		
		switch (gpio_port)
		{
			case GPIO_PORTA:
			*pin_level = (PINA_REG>>gpio_pin) & 0x01;
			return_error = GPIO_E_OK;
			break;
			
			case GPIO_PORTB:
			*pin_level = (PINB_REG>>gpio_pin) & 0x01;
			return_error = GPIO_E_OK;
			break;
			
			case GPIO_PORTC:
			*pin_level = (PINC_REG>>gpio_pin) & 0x01;
			return_error = GPIO_E_OK;
			break;
			
			case GPIO_PORTD:
			*pin_level = (PIND_REG>>gpio_pin) & 0x01;
			return_error = GPIO_E_OK;
			break;
			
			default:
			return_error = GPIO_E_NOT_OK; /* Wrong Port*/
			break;
		}
	}
	else
	{
		return_error = GPIO_E_NOT_OK;  /* Wrong pin*/
	}
	  
	return return_error;
}

/*********************************************************************************************************************
                                                << End of File >>
*********************************************************************************************************************/