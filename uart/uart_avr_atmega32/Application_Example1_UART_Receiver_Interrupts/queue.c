/*********************************************************************************************************************
* Author : Alsayed Alsisi
* Date   : Thursday, May 06, 2021
* Version: 1.0
* Contact: alsayed.alsisi@gmail.com
* License:
* You have the right to use the file as you wish in educational or commercial purposes under the following
* conditions:
* - This file is to be used as is. No modifications are to be made to any part of the file, including this section.
* - This section is not to be removed under any circumstances.
* - Parts of the file may be used separately under the condition that are not modified, and preceded by this section.
* - Any bug that is found in this file or parts of it should be reported to the email address given above.
*********************************************************************************************************************/
/*********************************************************************************************************************
* File Information:
** File Name:
*  queue.c
*
** File Description:
*  This file contains the implementation of the queue function library.
*********************************************************************************************************************/

/*********************************************************************************************************************
                                         << File Inclusions >>
*********************************************************************************************************************/
#include "queue.h"


/*********************************************************************************************************************
                                  << Public Function Definitions >>
*********************************************************************************************************************/
/*********************************************************************************************************************
** Function Name:
*  queue_enqueue
*
** Purpose:
*  This function is used to add a value to rear of the queue. If the value is successfuly added to the rear, in other
*  words if the queue is not full, the rear index will then point to the next empty location at the queue data buffer.
*
** Input Parameters:
*  - my_queue: queue_t
*    This is a pointer to the queue structure that contains all of the queue data.
*  - queue_new_rear_value: uint8_t
*    This is the new value that is to be added to the rear of the queue. 
*
** Return Value:
*  - queue_std_return_value_t
*    Returns operation status, "QUEUE_OPERATION_SUCCESSFUL" for successful "enqueue" operation, or "QUEUE_IS_FULL", in
*    which case the "enqueue" operation failed.
*
** Use Example:
*  [1] Checking if the queue isn't full before adding more values.
*      if(QUEUE_NOT_FULL == queue_isFull(&my_queue))
*       {
*          queue_enqueue(&lcd_queue, new_rear_char);
*       }
*********************************************************************************************************************/
queue_std_return_value_t queue_enqueue(queue_t* my_queue, uint8_t queue_new_rear_value)
{
  queue_std_return_value_t queue_current_status = queue_isFull(my_queue);
  /* Check if the queue is not full: */
  if(QUEUE_IS_FULL != queue_current_status)
  {
      /* then, store the new value at the rear of the queue: */
      my_queue ->data_buffer[my_queue->rear_index] = queue_new_rear_value;
      /* The rear index now points to the next empty cell: */
      my_queue->rear_index = (my_queue->rear_index) + 1;
      /* The enqueue operation is successful*/
      queue_current_status = QUEUE_OPERATION_SUCCESSFUL;
  }
  /*returns "QUEUE_OPERATION_SUCCESSFUL", or "QUEUE_IS_FULL"*/
  return queue_current_status; 
}

/*********************************************************************************************************************
** Function Name:
*  "queue_dequeue"
*
** Purpose:
*  This function is used to read a value from the front of the queue. If the value is successfuly read, in other words
*  if the queue is not empty, the front index will then point to the next front value in the queue.
*
** Input Parameters:
*  - my_queue: queue_t*
*    This is a pointer to the queue structure that contains all of the queue data.
*  - "queue_front_value": uint8_t*
*    This is a pointer to the variable that will be loaded with the front value of the queue.
*
** Return Value:
*  - queue_std_return_value_t
*    Returns operation status, "QUEUE_OPERATION_SUCCESSFUL" for successful "dequeue" operation, or "QUEUE_IS_EMPTY", in
*    which case the "dequeue" operation failed.
*
** Use Example:
*  [1] Checking if the queue isn't empty before reading data
*      if(QUEUE_NOT_EMPTY == queue_isEmpty(&my_queue))
*       {
*          queue_dequeue(&lcd_queue, &current_front_char);
*       }
*********************************************************************************************************************/
queue_std_return_value_t queue_dequeue(queue_t* my_queue, uint8_t* queue_front_value)
{
    queue_std_return_value_t queue_current_status = queue_isEmpty(my_queue);

    /* Checking if the queue is not empty*/
    if(QUEUE_NOT_EMPTY == queue_current_status)
    {
        /* then return back the value at the front of the queue: */
        *queue_front_value = my_queue->data_buffer[my_queue->front_index];
        /* increment the front index to point to the next data cell: */
        my_queue->front_index = (my_queue->front_index)+1;
        /* declare operation to be successful: */
        queue_current_status = QUEUE_OPERATION_SUCCESSFUL;

        /* checking if all the data cells has been read: */
        if(my_queue->front_index == my_queue->rear_index)
        {
            /* Start filling again from the start of the queue: */
            my_queue->rear_index  = 0;
            my_queue->front_index = 0;
        }
    }

    return queue_current_status;
}

/*********************************************************************************************************************
** Function Name:
*  queue_isEmpty
*
** Description:
*  This function indicates whether the queue is empty or not.
*  
** Input Parameters:
*  - my_queue: queue_t*
*    This is a pointer to the queue structure that contains all of the queue data.
*
** Return Value:
*  - queue_std_return_value_t
*    Returns "QUEUE_IS_EMPTY" or "QUEUE_NOT_EMPTY" based on the current status of the queue.
* 
** Use Example:
*  [1] Checking if the queue isn't empty before reading data
*      if(QUEUE_NOT_EMPTY == queue_isEmpty(&my_queue))
*       {
*          queue_dequeue(&lcd_queue, &current_front_char);
*       }
*********************************************************************************************************************/
queue_std_return_value_t queue_isEmpty(queue_t* my_queue)
{
  queue_std_return_value_t return_value = QUEUE_NOT_EMPTY;
  if(0 == (my_queue->rear_index))
  {
      return_value = QUEUE_IS_EMPTY;
  }
  return return_value;
}

/*********************************************************************************************************************
** Function Name:
*  queue_isFull
*
** Description:
*  This function indicates whether the queue is full or not.
*
** Input Parameters:
*  - my_queue: queue_t*
*    This is a pointer to the queue structure that contains all of the queue data.
*
** Return Value:
*  - queue_std_return_value_t
*    Returns "QUEUE_IS_FULL" or "QUEUE_NOT_FULL" based on the current status of the queue.
* 
*
** Use Example:
*  [1] Checking if the queue isn't full before adding more values.
*      if(QUEUE_NOT_FULL == queue_isFull(&my_queue))
*       {
*          queue_enqueue(&lcd_queue, new_rear_char);
*       }
*********************************************************************************************************************/
queue_std_return_value_t queue_isFull(queue_t* my_queue)
{
  queue_std_return_value_t return_value = QUEUE_NOT_FULL;
  if((my_queue->queue_size) == (my_queue->rear_index))
  {
      return_value = QUEUE_IS_FULL;
  }
  return return_value;
}

/*********************************************************************************************************************
** Function Name:
*  queue_peek
*
** Description:
*  Returns the value at the front of the queue without dequeuing it.
*
*  - my_queue: queue_t*
*    This is a pointer to the queue structure that contains all of the queue data.
*  - queue_front_value: uint8_t*
*    This is pointer to the variable in which the function will return the value at the front of the queue. If the 
*    queue is empty, the variable won't be changed by the function.
*
** Return Value:
*  - queue_std_return_value_t
*    Returns "QUEUE_OPERATION_SUCCESSFUL" if the "peek" operation was successful or "QUEUE_IS_EMPTY' in case the queue
     is empty, which means there were no value to read and the "peek" operation failed.
*********************************************************************************************************************/
queue_std_return_value_t  queue_peek(queue_t* my_queue, uint8_t* queue_front_value)
{
    queue_std_return_value_t return_value = QUEUE_IS_EMPTY;

    /* Checking if the queue is not empty: */
    if(QUEUE_NOT_EMPTY == queue_isEmpty(my_queue))
    {
        /* then send back the front value of the queue: */
        *queue_front_value = my_queue->data_buffer[my_queue->front_index];
        return_value = QUEUE_OPERATION_SUCCESSFUL;
    }

    return return_value;
}

/*********************************************************************************************************************
                                               << End of File >>
*********************************************************************************************************************/