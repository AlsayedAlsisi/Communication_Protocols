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
*  queue.h
*
** File Description:
*  This file contains the public interfaces, datatypes, and other information of the queue function library.
*********************************************************************************************************************/



/*********************************************************************************************************************
                                               << Header Guard >>
*********************************************************************************************************************/
#ifndef QUEUE_FUNC_LIB_H_INCLUDED
#define QUEUE_FUNC_LIB_H_INCLUDED


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
/*********************************************************************************************************************
** Datatype Name:
*  queue_t
*
** Description:
*  This is a structure datatype that will be used for creating a new queue.
*
** Datatype Elements:
*  [1] data_buffer: uint8_t* const
*      This is a const pointer that will be pointing to the data buffer array created for the queue.
*  [2] queue_size: const uint8_t
*      This element holds the size of the data buffer array created for the queue.
*  [3] front_index: uint8_t
*      This is to store the current front index of the queue data buffer.
*  [4] rear_index: uint8_t
*      This is to store the current rear index of the queue data buffer.
*
** Use Example:
*  [1] Create a queue called "lcd_queue" to store the data that will be displayed on an LCD.
*      #define LCD_QUEUE_BUFFER_SIZE 21
*      static uint8_t lcd_queue_buffer_array[LCD_QUEUE_BUFFER_SIZE] = {0};
*      static queue_t lcd_queue = {.data_buffer = lcd_queue_buffer_array,.rear_index = 0, .front_index = 0,
*                                  .queue_size = LCD_QUEUE_BUFFER_SIZE};
*********************************************************************************************************************/
typedef struct
{
    uint8_t* const data_buffer;
    const uint8_t queue_size;
    uint8_t front_index;
    uint8_t rear_index;

} queue_t;

/*********************************************************************************************************************
** Datatype Name:
*  queue_std_return_value_t
*
** Description:
*  This is an ENUM datatype that will be used for the return value of different queue operations to indicate the
*  status of the operation. Each operation return one or more of these operation codes. The return values need to be
*  checked carefully for successful queue operations.
*
** Datatype Elements:
*  [1] QUEUE_OPERATION_SUCCESSFUL
*      Indicates that the operation performed was successful.
*  [2] QUEUE_IS_EMPTY
*      Indicates that the queue is currently empty.
*  [3] QUEUE_NOT_EMPTY
*      Indicates that the queue currently contains data.
*  [4] QUEUE_IS_FULL
*      Indicates that the queue is currently full.
*  [5] QUEUE_NOT_FULL
*      Indicates that the queue is not currently full.
*********************************************************************************************************************/
typedef enum
{
    QUEUE_OPERATION_SUCCESSFUL = 0,
    QUEUE_IS_EMPTY,
    QUEUE_NOT_EMPTY,
    QUEUE_IS_FULL,
    QUEUE_NOT_FULL
} queue_std_return_value_t;

/*********************************************************************************************************************
                                          << Public Variable Declarations >>
*********************************************************************************************************************/


/*********************************************************************************************************************
                                           << Public Function Declarations >>
*********************************************************************************************************************/
extern queue_std_return_value_t  queue_enqueue(queue_t* my_queue, uint8_t queue_new_rear_value);
extern queue_std_return_value_t  queue_dequeue(queue_t* my_queue, uint8_t* queue_front_value);
extern queue_std_return_value_t  queue_isEmpty(queue_t* my_queue);
extern queue_std_return_value_t  queue_isFull(queue_t* my_queue);
extern queue_std_return_value_t  queue_peek(queue_t* my_queue, uint8_t* queue_front_value);


#endif // QUEUE_FUNC_LIB_H_INCLUDED
/*********************************************************************************************************************
                                               << End of File >>
*********************************************************************************************************************/
