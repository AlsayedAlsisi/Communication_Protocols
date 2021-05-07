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
*  bit_math.h
*
** File Description:
*  This file contains the software library for bit manipulation.
*********************************************************************************************************************/
/*********************************************************************************************************************
                                               << Header Guard >>
*********************************************************************************************************************/
#ifndef BIT_MATH_H_
#define BIT_MATH_H_

/*****************************************************************
********************* File Inclusions ****************************
******************************************************************/


/*****************************************************************
********************* Public Constants ***************************
******************************************************************/

/*****************************************************************
********************* Function-Like Macros ***********************
******************************************************************/
#define   BIT_SET(VAR, BIT_NUMBER)      (VAR = (VAR | (1<<BIT_NUMBER)))
#define   BIT_CLEAR(VAR, BIT_NUMBER)    (VAR = (VAR & (~(1<<BIT_NUMBER))))
#define   BIT_GET(VAR, BIT_NUMBER)      ((VAR>>BIT_NUMBER) & 1)
#define   BIT_TOGGLE(VAR, BIT_NUMBER)   (VAR = (VAR ^ (1<<BIT_NUMBER)))

/*****************************************************************
********************* Public Data Types **************************
******************************************************************/


/*****************************************************************
********************* Public Variable Declarations ***************
******************************************************************/


/*****************************************************************
********************* Public Function Prototypes *****************
******************************************************************/




#endif /* BIT_MATH_H_ */

/*****************************************************************
--------------------- End of File --------------------------------
******************************************************************/