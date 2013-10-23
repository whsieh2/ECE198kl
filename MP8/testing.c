/*									tab:8
 *
 * testing.c - source file for UIUC ECE198KL Spring 2013 Program 8 heap testing
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
 * Creation Date:   11 March 2013
 * Filename:	    testing.c
 * History:
 *	SL	1.00	11 March 2013
 *		First created.
 */

#include <stdint.h>
#include <stdio.h>

#include "prog8.h"


/*
 * test_heap_init -- call heap_init and test the results
 * INPUTS: ret_val -- expected return value
 * OUTPUTS: none
 * RETURN VALUE: 1 means the test passed, and 0 means it failed
 * SIDE EFFECTS: prints message on failure
 */
int32_t 
test_heap_init (int32_t ret_val)
{
    int32_t rv;

    rv = heap_init ();
    if (ret_val != rv) {
        fprintf (stderr, "heap_init returned %d instead of %d\n",
		 rv, ret_val);
	return 0;
    }
    return 1;
}


/*
 * test_heap_insert -- call heap_insert and test the results
 * INPUTS: time, queue_num, type, arrival -- passed to heap_insert
 *         ret_val -- expected return value
 * OUTPUTS: none
 * RETURN VALUE: 1 means the test passed, and 0 means it failed
 * SIDE EFFECTS: prints message on failure
 */
int32_t 
test_heap_insert (double time, int32_t queue_num, int32_t type, double arrival,
		  int ret_val)
{
    int32_t rv;

    rv = heap_insert (time, queue_num, type, arrival);
    if (ret_val != rv) {
        fprintf (stderr,
		 "heap_insert (%.6lf,%d,%d,%.6lf) returned %d instead of %d\n", 
		 time, queue_num, type, arrival,
		 rv, ret_val);
	return 0;
    }
    return 1;
}


/*
 * test_heap_peek_min -- call heap_peek_min and test the results
 * INPUTS: ret_val -- expected return value
 *         time -- expected time value (compared only if return value is 1)
 * OUTPUTS: none
 * RETURN VALUE: 1 means the test passed, and 0 means it failed
 * SIDE EFFECTS: prints message on failure
 */
int32_t 
test_heap_peek_min (int32_t ret_val, double time)
{
    int32_t rv;
    double  t;

    rv = heap_peek_min (&t);
    if (ret_val != rv) {
        fprintf (stderr, "heap_peek_min returned %d instead of %d\n", 
		 rv, ret_val);
	return 0;
    }
    if (1 == rv && time != t) {
        fprintf (stderr, "heap_peek_min found time %.6lf instead of %.6lf\n", 
		 t, time);
	return 0;
    }
    return 1;
}


/*
 * test_heap_get_min -- call heap_get_min and test the results
 * INPUTS: ret_val -- expected return value
 *         time -- expected time value (compared only if return value is 1)
 *         queue_num -- expected queue_num (compared only if return value is 1)
 *         type -- expected type (compared only if return value is 1)
 *         arrival -- expected arrival (compared only if return value is 1)
 * OUTPUTS: none
 * RETURN VALUE: 1 means the test passed, and 0 means it failed
 * SIDE EFFECTS: prints message on failure
 */
int32_t 
test_heap_get_min (int32_t ret_val, double time, int32_t queue_num,
		   int32_t type, double arrival)
{
    int32_t rv;
    double  t;
    int32_t qn;
    int32_t y;
    double  a;

    rv = heap_get_min (&t, &qn, &y, &a);
    if (ret_val != rv) {
        fprintf (stderr, "heap_get_min returned %d instead of %d\n", 
		 rv, ret_val);
	return 0;
    }
    if (1 == rv && 
        (time != t || qn != queue_num || y != type || a != arrival)) {
	fprintf (stderr, "heap_get_min found (%.6lf,%d,%d,%.6lf) instead of"
		 "(%.6lf,%d,%d,%.6lf)\n", t, qn, y, a, time, queue_num,
		 type, arrival);
	return 0;
    }
    return 1;
}


/*
 * main -- the main program for your test code
 * INPUTS: none
 * OUTPUTS: none
 * RETURN VALUE: 0=success, 3=failure
 * SIDE EFFECTS: prints messages
 */
int
main ()
{
    int32_t failed = 0;

    failed |= !test_heap_init (1);
    failed |= !test_heap_peek_min (0, 0.0);

    if (failed) {
	return 3;
    }
    puts ("All tests passed.");
    return 0;
}

