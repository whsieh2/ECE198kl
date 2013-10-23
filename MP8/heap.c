/*									tab:8
 *
 * heap.c - source file for UIUC ECE198KL Spring 2013 Program 8 heap
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
 * Version:	    1.01
 * Creation Date:   25 February 2013
 * Filename:	    heap.c
 * History:
 *	SL	1.00	25 February 2013
 *		First written.
 *	SL	1.01	10 March 2013
 *		Adapted to store models.
 */

#include <stdint.h>

#include "prog8.h"


/*
 * The four arrays below are managed together as a heap with length given
 * by event_heap_len.  For a given event (an index used into each of the 
 * arrays), the event_time specifies the time at which the event occurs
 * and the event_type specifies an arrival or a departure.  
 *
 * Arrival events generate new people (and create another arrival event),
 * while departures mark the time at which a given individual leaves a 
 * queue.  
 *
 * The event_queue_num and event_arrival array are thus only defined
 * for departure events, and correspond to the queue number in which the
 * person is waiting and the person's original arrival time to the system 
 * as a whole.  The latter allows us to measure the time that it takes for 
 * the person to pass through the system.
 */
static uint32_t event_heap_len = 0;
static double   event_time[MAX_HEAP_LEN];
static int32_t  event_queue_num[MAX_HEAP_LEN];
static int32_t  event_type[MAX_HEAP_LEN];
static double   event_arrival[MAX_HEAP_LEN];


/*
 * heap_init -- empty the heap
 * INPUTS: none
 * OUTPUTS: none
 * RETURN VALUE: 1 on success, or 0 on failure
 * SIDE EFFECTS: eliminates any events from the heap
 */
int32_t
heap_init ()
{
    event_heap_len = 0;
    return 1;
}


/*
 * copy_heap_index -- copy one entry (all four arrays) from one position
 *                    in the heap to another
 * INPUTS: dst -- the destination index
 *         src -- the source index
 * OUTPUTS: none
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
static void
copy_heap_index (int32_t dst, int32_t src)
{
    event_time[dst]      = event_time[src];
    event_queue_num[dst] = event_queue_num[src];
    event_type[dst]      = event_type[src];
    event_arrival[dst]   = event_arrival[src];
}


/*
 * heap_insert -- insert a new event into the heap
 * INPUTS: time -- the time of the new event
 *	   queue_num -- the queue number of the new event
 *	   type -- the type of the new event
 *	   arrival -- the original arrival time of the new event
 * OUTPUTS: none
 * RETURN VALUE: 1 on success, or 0 on failure
 * SIDE EFFECTS: none
 */
int32_t
heap_insert (double time, int32_t queue_num, int32_t type, double arrival)
{
    uint32_t pt = event_heap_len;
    uint32_t parent;

    if (MAX_HEAP_LEN == pt) {
	/* The heap is full! */
        return 0;
    }
    event_heap_len++;
    while (0 != pt) {
	parent = (pt - 1) / 2;
	if (time >= event_time[parent]) {
	    break;
	}
	copy_heap_index (pt, parent);
	pt = parent;
    }
    event_time[pt]      = time;
    event_queue_num[pt] = queue_num;
    event_type[pt]      = type;
    event_arrival[pt]   = arrival;
    return 1;
}


/*
 * heap_peek_min -- peek at the first event in the heap
 * INPUTS: time_ptr -- location to store the time of the first event
 * OUTPUTS: *time_ptr -- time of the first event (on success only)
 * RETURN VALUE: 1 on success, or 0 on failure
 * SIDE EFFECTS: none
 */
int32_t
heap_peek_min (double* time_ptr)
{
    if (0 == event_heap_len) {
        return 0;
    }
    *time_ptr = event_time[0];
    return 1;
}


/*
 * heap_get_min -- extract the first event from the heap
 * INPUTS: time_ptr -- location to store the time of the first event
 *         queue_num_ptr -- location to store the queue number
 *         type_ptr -- location to store the type
 *         arrival_ptr -- location to store the original arrival time
 * OUTPUTS: *time_ptr -- time of the first event (on success only)
 *          *queue_num_ptr -- queue number of the first event (on success only)
 *          *type_ptr -- type of the first event (on success only)
 *          *arrival_ptr -- original arrival time (on success only)
 * RETURN VALUE: 1 on success, or 0 on failure
 * SIDE EFFECTS: none
 */
int32_t
heap_get_min (double* time_ptr, int32_t* queue_num_ptr, int32_t* type_ptr, 
	      double* arrival_ptr)
{
    double   time;
    int32_t  queue_num;
    int32_t  type;
    double   arrival;
    uint32_t pt;
    uint32_t left;
    uint32_t right;

    if (0 == event_heap_len) {
	/* The heap is empty! */
        return 0;
    }
    *time_ptr      = event_time[0];
    *queue_num_ptr = event_queue_num[0];
    *type_ptr      = event_type[0];
    *arrival_ptr   = event_arrival[0];
    if (0 < --event_heap_len) {
	time      = event_time[event_heap_len];
	queue_num = event_queue_num[event_heap_len];
	type      = event_type[event_heap_len];
	arrival   = event_arrival[event_heap_len];
	pt        = 0;
	while (event_heap_len > (left = 2 * pt + 1)) {
	    right = left + 1;
	    if (event_heap_len > right && time > event_time[right] && 
	    	event_time[left] > event_time[right]) {
		copy_heap_index (pt, right);
		pt = right;
		continue;
	    }
	    if (time <= event_time[left]) {
		break;
	    }
	    copy_heap_index (pt, left);
	    pt = left;
	}
	event_time[pt]      = time;
	event_queue_num[pt] = queue_num;
	event_type[pt]      = type;
	event_arrival[pt]   = arrival;
    }
    return 1;
}

