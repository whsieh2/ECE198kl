/*									tab:8
 *
 * prog4.h - header file for UIUC ECE198KL Spring 2013 Program 4
 *           student code
 *
 * "Copyright (c) 2013 by Steven S. Lumetta."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice and the following
 * two paragraphs appear in all copies of this software.
 * 
 * IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO 
 * ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL 
 * DAMAGES ARISING OUT  OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, 
 * EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE 
 * PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
 * THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE, 
 * SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Author:	    Steve Lumetta
 * Version:	    1.00
 * Creation Date:   2 February 2013
 * Filename:	    prog4.h
 * History:
 *	SL	1.00	2 February 2013
 *		First created.
 */

#if !defined(PROG4_)
#define PROG4_

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif //defined(__cplusplus)


/*
 * Error code for operation execution on bad arguments. 
 */
#define BAD_OPERATION INFINITY


/* 
 * The button names below are delivered when the user presses one of
 * the buttons on the calculator.  We'll talk about enumerations (enum)
 * later in the class.  For now, think of the enumeration below as
 * equivalent to using #define to assign each symbolic name a value. 
 */
enum {
    /* Buttons for digits, decimal point, and (base 10) exponent. */
    BUTTON_0           =  0, /* the '0' button                        */
    BUTTON_1           =  1, /* the '1' button                        */
    BUTTON_2           =  2, /* the '2' button                        */
    BUTTON_3           =  3, /* the '3' button                        */
    BUTTON_4           =  4, /* the '4' button                        */
    BUTTON_5           =  5, /* the '5' button                        */
    BUTTON_6           =  6, /* the '6' button                        */
    BUTTON_7           =  7, /* the '7' button                        */
    BUTTON_8           =  8, /* the '8' button                        */
    BUTTON_9           =  9, /* the '9' button                        */
    BUTTON_DEC_PT      = 10, /* the decimal point button              */
    BUTTON_EXP         = 11, /* the sci. notation exponent (E) button */ 

    /* Buttons for clearing state. */
    BUTTON_CLEAR_ENTRY = 12, /* the clear entry (CE) button           */
    BUTTON_ALL_CLEAR   = 13, /* the all clear (AC) button             */

    /* 
     * Buttons for binary operators (equals masquerades as a binary 
     * operator to display previous results).
     */
    BUTTON_PLUS        = 14, /* the addition (+) button               */
    BUTTON_MINUS       = 15, /* the subtraction (-) button            */
    BUTTON_TIMES       = 16, /* the multiplication (*) button         */
    BUTTON_DIVIDE      = 17, /* the division (/) button               */
    BUTTON_EQUALS      = 18, /* the equals (=) button                 */
    BUTTON_X_TO_Y      = 19, /* the exponentiation (x^y) button       */

    /* Buttons for unary operators. */
    BUTTON_NEGATE      = 20, /* the negation (+/-) button             */
    BUTTON_INVERT      = 21, /* the inversion (1/x) button            */
    BUTTON_SQUARE      = 22, /* the square (x^2) button               */
    BUTTON_FACT        = 23, /* the factorial (n!) button             */
    BUTTON_CBRT        = 24, /* the cube root (crt) button            */
    BUTTON_SQRT        = 25, /* the square root (sqt) button          */
    /* Calculate these functions using DEGREES, not radians. */
    BUTTON_SIN         = 26, /* the sine (sin) button                 */
    BUTTON_COS         = 27, /* the cosine (cos) button               */
    BUTTON_TAN         = 28, /* the tangent (tan) button              */
    BUTTON_LN          = 29, /* the natural logarithm (ln) button     */
    BUTTON_E_TO_X      = 30, /* the e-to-the-x (e^x) button           */

    /* Buttons for stored 'memory' value. */
    BUTTON_MEM_ADD     = 31, /* the memory add (M+) button            */
    BUTTON_MEM_SUB     = 32, /* the memory subtract (M-) button       */
    BUTTON_MEM_RECALL  = 33, /* the memory recall (MR) button         */
    BUTTON_MEM_CLEAR   = 34  /* the memory clear (MC) button          */
};


/*
 * These values specify the behavior selected by the handle_key function
 * in response to each key pressed on the calculator.
 */
enum {
    RESPONSE_IGNORE   = 0, /* key was ignored--do nothing */
    RESPONSE_ECHO_KEY = 1, /* add key to displayed value  */
    RESPONSE_REPLACE  = 2, /* replace displayed value     */
    RESPONSE_ERROR    = 3  /* display the word "Error."   */
};


/*--------------------------------------------------------------------------*/
/*                                                                          */
/*                   PROGRAM 4 EXTERNALLY VISIBLE FUNCTION                  */
/*                                                                          */
/*--------------------------------------------------------------------------*/

/* 
 * Called each time a key is pressed to determine what should be done in
 * response.  The value argument points to the number currently displayed
 * (may not be meaningful if the last key resulted in an error).  The
 * return value must be one of the RESPONSE_ symbols.  If RESPONSE_REPLACE
 * is returned, set the double pointed to by value to the number that
 * should appear on the display before returning.
 */
int32_t handle_key (int32_t key, double* value);


#if defined(__cplusplus)
}
#endif //defined(__cplusplus)

#endif /* PROG4_ */
