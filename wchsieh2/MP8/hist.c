/*									tab:8
 *
 * hist.c - source file for UIUC ECE198KL Spring 2013 Program 8 histogram
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
 * Creation Date:   10 March 2013
 * Filename:	    hist.c
 * History:
 *	SL	1.00	10 March 2013
 *		First created.
 */

#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "prog8.h"


/*
 * A simple histogram that tracks 200 bins of 0.5 time units and has an
 * extra bin for anything larger.
 */
static int32_t hist[201];	/* the histogram     */
static int32_t hist_cnt;	/* total of all bins */


/*
 * hist_init -- initialize the histogram
 * INPUTS: none
 * OUTPUTS: none
 * RETURN VALUE: 1 on success, or 0 on failure
 * SIDE EFFECTS: fills all bins with 0
 */
int32_t
hist_init ()
{
    memset (hist, 0, sizeof (hist));
    hist_cnt = 0;
    return 1;
}


/*
 * hist_record_delay -- record one delay value in the histogram
 * INPUTS: val -- the delay (in some unit of time)
 * OUTPUTS: none
 * RETURN VALUE: 1 on success, or 0 on failure
 * SIDE EFFECTS: increments an appropriate bin
 */
int32_t
hist_record_delay (double val)
{
    /* Note that the bins are spaced at 0.5 time units. */
    int32_t idx = (int32_t)(val * 2);
    if (0 > idx || 200 < idx) {
        idx = 200;
    }
    hist[idx]++;
    hist_cnt++;
    return 1;
}


/*
 * hist_dump -- print histogram as a probability distribution
 * INPUTS: none
 * OUTPUTS: none
 * RETURN VALUE: 1 on success, or 0 on failure
 * SIDE EFFECTS: prints to stdout
 */
int32_t
hist_dump ()
{
    int32_t idx;
    
    printf ("# entries = %d\n", hist_cnt);
    for (idx = 0; 200 >= idx; idx++) {
        printf ("%.6lf %.6lf\n", idx / 2.0, 2 * hist[idx] / (double)hist_cnt);
    }
    return 1;
}

