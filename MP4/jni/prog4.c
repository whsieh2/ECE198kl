/*									tab:8
 *
 * prog4.c - source file for UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION
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
 * Version:	    1.02
 * Creation Date:   2 February 2013
 * Filename:	    prog4.c
 * History:
 *	SL	1.00	2 February 2013
 *		First created.
 *	SL	1.01	3 February 2013
 *		Gold version completed.
 *	SL	1.02	3 February 2013
 *		Assignment version created.
 */

#include <math.h>

#include "prog4.h"


/*
 * Explanation of the calculator's finite state machine:
 *
 * has_error: indicates that an error has occurred in the current value;
 *            until the user presses one of the 'clear' buttons to clear
 *            the error, nothing happens (memory clear can be performed,
 *            but the error in the current value remains in this case)
 *
 * The two main bits of state are has_value and is_entering:
 *   has_value: indicates the the user entered a value and a binary operator
 *              when true (not 0), first_value holds the first operand of 
 *              the binary operator, and first_op holds the key value of the
 *              operand (for example, BUTTON_PLUS); first_value and first_op
 *              are undefined when has_value is false (0)
 *   is_entering: the user has started to enter a number
 *       when false (0), neg_prefix indicates that BUTTON_MINUS or 
 *                       BUTTON_NEGATE has been pressed, so number should
 *                       be negative 
 *       when true (not 0), can_extend indicates the more digits or
 *                          a decimal point (but see has_dec_pt) can be
 *                          added; if can_extend is true, has_exp indicates
 *                          that the number includes an exponent, and 
 *			    start_exp indicates the user has just started 
 *			    entering the exponent (and can press a minus 
 *			    sign)
 *       (note that neg_prefix and can_extend are undefined in the state
 *        of is_entering in which they are not mentioned)
 *
 *   has_dec_pt: indicates that the number being entered has a decimal point
 *       in it, so additional presses should be ignored (if is_entering is 
 *       false, the decimal point is implicitly at the start of the number);
 *       set to true when entering exponents, even if no decimal place
 *       appears in number (to keep the user from placing a decimal point in
 *       the exponent)
 */

static int32_t has_error   = 0; /* display is currently showing an error   */
static int32_t has_value   = 0; /* have a stored value (first operand)?    */
static double  first_value;     /* the first operand value (see has_value) */
static int32_t first_op;        /* the first operator (see has_value)      */
static int32_t is_entering = 0; /* has user started entering a value?      */
static int32_t neg_prefix  = 0; /* value starts with minus sign            */
static int32_t can_extend  = 0; /* number entered can be extended          */
static int32_t has_exp     = 0; /* number entered has an exponent          */
static int32_t start_exp   = 0; /* user has just started the exponent      */
static int32_t has_dec_pt  = 0; /* number entered has a decimal point      */


/* 
 * Function to be written for your Program 4 (skeletal code appears below).
 */
static double execute_operator (int32_t key, double arg1, double arg2);


/* 
 * Functions defined in this file for handling classes of keys.
 */

/* Perform state machine updates for digits and the decimal point. */
static int32_t handle_basic_entry (int32_t key, double* value);

/* Perform state machine updates for binary operator buttons. */
static int32_t handle_binary_operator (int32_t key, double* value);

/* Perform state machine updates for unary operator buttons. */
static int32_t handle_unary_operator (int32_t key, double* value);

/* Perform state machine updates for memory buttons. */
static int32_t handle_memory_buttons (int32_t key, double* value);


/*
 * handle_key -- function called each time a key is pressed to determine 
 * 		 what should be done in response
 * INPUTS: key -- the key pressed (one of the BUTTON_ constants)
 *         *value -- the number currently displayed (may not be meaningful 
 *		     if the last key resulted in an error)
 * OUTPUTS: *value -- the number that * should appear on the display 
 *                    when RESPONSE_REPLACE is returned (otherwise ignored)
 * RETURN VALUE: one of the RESPONSE_ values
 * SIDE EFFECTS: updates finite state machine for calculator
 */
int32_t 
handle_key (int32_t key, double* value)
{
    if (BUTTON_ALL_CLEAR == key) {
	/* Note: does not reset stored 'memory' value. */
        has_error     = 0;
	has_value     = 0;
	is_entering   = 0;
	neg_prefix    = 0;
	has_dec_pt    = 0;
	*value        = 0;
	return RESPONSE_REPLACE;
    }
    if (BUTTON_CLEAR_ENTRY == key) {
        /* This button is currently ignored. */
	return RESPONSE_IGNORE;
    }
    /* If we see infinity or not-a-number, return an error. */
    if (INFINITY == *value || -INFINITY == *value || *value != *value) {
	has_error = 1;
        return RESPONSE_ERROR;
    }
    if (has_error && BUTTON_MEM_CLEAR != key) {
	/* Remain in error state until CLEAR is pressed. */
        return RESPONSE_ERROR;
    }
    if (BUTTON_EXP >= key) {
        return handle_basic_entry (key, value);
    }
    if (BUTTON_PLUS <= key && BUTTON_X_TO_Y >= key) {
        return handle_binary_operator (key, value);
    }
    if (BUTTON_NEGATE <= key && BUTTON_E_TO_X >= key) {
        return handle_unary_operator (key, value);
    }
    if (BUTTON_MEM_ADD <= key && BUTTON_MEM_CLEAR >= key) {
	return handle_memory_buttons (key, value);
    }
    has_error = 1;
    return RESPONSE_ERROR;
}


/*
 * handle_basic_entry -- function called by handle_key to perform state 
 *			 machine updates for digits, decimal point, and
 *     			 base 10 exponents
 * INPUTS: key -- the key pressed (one of the BUTTON_ constants)
 *         *value -- the number currently displayed (may not be meaningful 
 *		     if the last key resulted in an error)
 * OUTPUTS: *value -- the number that * should appear on the display 
 *                    when RESPONSE_REPLACE is returned (otherwise ignored)
 * RETURN VALUE: one of the RESPONSE_ values
 * SIDE EFFECTS: updates finite state machine for calculator
 */
static int32_t 
handle_basic_entry (int32_t key, double* value)
{
    int32_t ret_val = RESPONSE_IGNORE;

    /* If number cannot be extended, we replace it. */
    if (is_entering && !can_extend) {
	is_entering = 0;
	neg_prefix  = 0;
	has_dec_pt  = 0;
	*value      = 0;
	ret_val     = RESPONSE_REPLACE;
    }
    if (!is_entering) {
	if (BUTTON_0 == key || BUTTON_EXP == key) {
	    /* 
	     * Ignore leading zeroes and exponents for 0
	     * (but may need to show the 0 on display).
	     */
	    *value = 0;
	    return RESPONSE_REPLACE;
	}
	if (BUTTON_DEC_PT == key) {
	    has_dec_pt = 1;
	    return ret_val;
	}
	/* Start entering a number. */
	is_entering = 1;
	can_extend  = 1;
	has_exp     = 0;
	start_exp   = 0;
	*value = (double)(key - BUTTON_0);
	/* Handle negation and decimal point entered before first digit. */
	if (neg_prefix) {
	    *value = -*value;
	}
	if (has_dec_pt) {
	    *value = *value / 10.0;
	}
	return RESPONSE_REPLACE;
    }
    /* Continue entering a number. */
    if (BUTTON_DEC_PT == key) {
	if (has_dec_pt) {
	    return RESPONSE_IGNORE;
	}
	has_dec_pt = 1;
    } else if (BUTTON_EXP == key) {
	if (has_exp) {
	    return RESPONSE_IGNORE;
	}
        /* Go into exponent mode. */
	has_exp    = 1;
	start_exp  = 1;
	has_dec_pt = 1;
    } else {
        start_exp  = 0;
    }
    return RESPONSE_ECHO_KEY;
}


/*
 * handle_binary_operator -- function called by handle_key to perform
 *                           state machine updates for binary operators
 * INPUTS: key -- the key pressed (one of the BUTTON_ constants)
 *         *value -- the number currently displayed (may not be meaningful 
 *		     if the last key resulted in an error)
 * OUTPUTS: *value -- the number that * should appear on the display 
 *                    when RESPONSE_REPLACE is returned (otherwise ignored)
 * RETURN VALUE: one of the RESPONSE_ values
 * SIDE EFFECTS: updates finite state machine for calculator
 */
static int32_t 
handle_binary_operator (int32_t key, double* value)
{
    /* Special cases for the MINUS button. */
    if (BUTTON_MINUS == key) {
	/* 
	 * Second case below corresponds to doing one binary operation,
	 * pressing equals, and then starting a subtraction (rather
	 * than discarding result and entering a negative number).
	 */
	if (!is_entering && (!has_value || BUTTON_EQUALS != first_op)) {
	    neg_prefix = !neg_prefix;
	    return RESPONSE_IGNORE;
	} 
	/* Start a negative exponent. */
	if (is_entering && can_extend && has_exp && start_exp) {
	    start_exp = 0;
	    return RESPONSE_ECHO_KEY;
	}
    }

    /* 
     * In second case, no number is being entered, but we go ahead and
     * execute op using value shown on display (possibly 0) as second arg. 
     */
    if (is_entering ||
        (has_value && BUTTON_EQUALS == key && BUTTON_EQUALS != first_op)) {

	/* If the 'op' was equals, we just replace it. */
	if (has_value && BUTTON_EQUALS != first_op) {
	    /* 
	     * Call the student's operator execution code on the 
	     * stored operand and operator. 
	     */
	    *value = execute_operator (first_op, first_value, *value);
	    if (BAD_OPERATION == *value) {
		has_error = 1;
		return RESPONSE_ERROR;
	    }
	    /* Prepare for the next operation. */
	} else {
	    has_value = 1;
	}
	first_value = *value;
	first_op    = key;
	is_entering = 0;
	neg_prefix  = 0;
	has_dec_pt  = 0;
	return RESPONSE_REPLACE;
    } else if (has_value) {
	/* Replace previously selected operator. */
	first_op = key;
	return RESPONSE_IGNORE;
    }
    /*
     * No stored operation, and no number entered.  
     * Treat first argument as value shown on display.
     */
    has_value   = 1;
    first_value = *value;
    first_op    = key;
    is_entering = 0;
    neg_prefix  = 0;
    has_dec_pt  = 0;
    return RESPONSE_IGNORE;
}


/*
 * handle_unary_operator -- function called by handle_key to perform
 *                          state machine updates for unary operators
 * INPUTS: key -- the key pressed (one of the BUTTON_ constants)
 *         *value -- the number currently displayed (may not be meaningful 
 *		     if the last key resulted in an error)
 * OUTPUTS: *value -- the number that * should appear on the display 
 *                    when RESPONSE_REPLACE is returned (otherwise ignored)
 * RETURN VALUE: one of the RESPONSE_ values
 * SIDE EFFECTS: updates finite state machine for calculator
 */
static int32_t 
handle_unary_operator (int32_t key, double* value)
{
    /* 
     * Unary operators operate on whatever is being displayed.
     * So if you enter "1234+", then press a unary operator, your
     * second operand to the '+' will be operator(1234).
     * 
     * NEGATE is an exception--it is used as a negative prefix for a 
     * new value, or for the start of an exponent.
     */
    if (BUTTON_NEGATE == key) {
	if (!is_entering && 0 == *value) {
	    neg_prefix = !neg_prefix;
	    return RESPONSE_IGNORE;
	}
	/* Start a negative exponent. */
	if (is_entering && can_extend && has_exp && start_exp) {
	    start_exp = 0;
	    return RESPONSE_ECHO_KEY;
	}
    }

    /* Call the student's operator execution code. */
    *value = execute_operator (key, *value, 0);
    if (BAD_OPERATION == *value) {
	has_error = 1;
        return RESPONSE_ERROR;
    }

    /* Success: new value is ready, so just show it on the display. */
    is_entering = 1;
    can_extend  = 0;
    return RESPONSE_REPLACE;
}


/*
 * handle_memory_buttons -- function called by handle_key to perform
 *                          state machine updates for memory buttons
 * INPUTS: key -- the key pressed (one of the BUTTON_ constants)
 *         *value -- the number currently displayed (may not be meaningful 
 *		     if the last key resulted in an error)
 * OUTPUTS: *value -- the number that * should appear on the display 
 *                    when RESPONSE_REPLACE is returned (otherwise ignored)
 * RETURN VALUE: one of the RESPONSE_ values
 * SIDE EFFECTS: updates finite state machine for calculator
 */
static int32_t 
handle_memory_buttons (int32_t key, double* value)
{
    /* Calculator memory buttons are ignored in distribution version. */
    return RESPONSE_IGNORE;
}


/*
 * execute_operator -- function to be written by students for Program 4;
 *                     called when necessary to execute an operation
 * INPUTS: key -- the operation key (one of the BUTTON_ constants)
 *         arg1 -- the first argument to the operation
 *         arg2 -- the second argument to the operation (not defined for
 * 		   unary operators)
 * OUTPUTS: none
 * RETURN VALUE: the result of the operation, or BAD_OPERATION if no 
 *               result can be given (as with the square root of a negative
 *               number, for example)
 * SIDE EFFECTS: none
 */
 
 /* INTRO: I used switch statements for each button command. Each case has a specific 
 * function for that specific button. Used if statements for certain invalid usages.
 */
static double
execute_operator (int32_t key, double arg1, double arg2)
{
		int pi= 3.141592654;
	switch (key) 
	{ 
		//This will add 2 given arguments.
		case BUTTON_PLUS: 
		{ 
			return arg1+arg2; 
		} 
		//This will subtract 2 given arguments.
		case BUTTON_MINUS: 
		{
			return arg1-arg2;
		} 
		//This will mutiply 2 given arguments.
		case BUTTON_TIMES: 
		{
			return arg1*arg2; 
		}
		//This will divide 2 given arguments unless the 2nd one is a zero.
		case BUTTON_DIVIDE: 
		{ 
			if(arg2==0) 
				{
					return BAD_OPERATION;
				}
			return arg1/arg2; 
		} 
		//This will make the current argument by -1
		case BUTTON_NEGATE: 
		{ 
			return (-arg1); 
		} 
		//This will invert the arguemnt (1/arg1)
		case BUTTON_INVERT: 
		{ 
			if(arg1==0) 
			{
				return BAD_OPERATION;
			} 
				return (1/arg1); 
		} 
		//This will square the argument by multiply the arg by itself.
		case BUTTON_SQUARE:
		{ 
			return arg1*arg1; 
		} 
		//This will do arg1 to the power of arg2
		case BUTTON_X_TO_Y: 
		{ 
			return pow(arg1,arg2);
		} 
		//This will take the degree value and convert it to radians and do the sin func.
		case BUTTON_SIN: 
		{ 
			return sin((arg1*pi)/180); 
		}
		//This will take the degree value and convert it to radians and do the cos func.
		case BUTTON_COS: 
		{  
			return cos((arg1*pi)/180); 
		} 
		// Divide sin func over cos func to implement tan function.
		case BUTTON_TAN: 
		{
			return ((sin(arg1*pi/180))/(cos(arg1*pi/180))); 
		} 
		//This will give the natural log of arg1 if it's not 0
		case BUTTON_LN: 
		{ 
			if(arg1<=0) 
			{
				return BAD_OPERATION;
			} 
			return log(arg1); 
		}
		//This will take the e power of arg1
		case BUTTON_EXP: 
		{ 
			return exp(arg1); 
		} 
		//This will take the square of arg1
		case BUTTON_SQRT: 
		{ 
			if(arg1<0) 
			{
				return BAD_OPERATION;
			}
			return sqrt(arg1); 
		} 
		//This will take the cube root of arg1
		case BUTTON_CBRT: 
		{
			return pow(arg1,(1/3)); 
		} 
		//I used a for loop to implement the factorial. If it is a double, it will take the next lowest int.
		case BUTTON_FACT:
		{
			if (arg1 >= 0)
			{
				int y = 1;
				for (int x = 1; x <= arg1; x++)
				{
					y = y*x;
				}
				return y;
			}
			else 
				return BAD_OPERATION;
			
		}
    /* By default, the calculator marks all operations as bad. */
    	return BAD_OPERATION;
    	}
}
