/*									tab:8
 *
 * prog8.h - header file for UIUC ECE198KL Spring 2013 Program 8
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
 * Creation Date:   8 March 2013
 * Filename:	    prog8.h
 * History:
 *	SL	1.00	8 March 2013
 *		First created.
 *	SL	1.01	11 March 2013
 *		Prepared for release.
 */

#if !defined(PROG_8_H)
#define PROG_8_H

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif //defined(__cplusplus)


/*--------------------------------------------------------------------------*/
/*                                                                          */
/*                           PROGRAM 8 CONSTANTS                            */
/*                                                                          */
/*--------------------------------------------------------------------------*/

#define MAX_QUEUES   32		/* maximum number of queues allowed */
#define MAX_RUNS     1000000000	/* maximum number of simulation run */
#define MAX_HEAP_LEN 1048576	/* maximum length of heap           */

/* event type classifications */
enum {
    EVENT_ARRIVAL,
    EVENT_DEPARTURE,
};

/*--------------------------------------------------------------------------*/
/*                                                                          */
/*                         PROGRAM 8 HEAP FUNCTIONS                         */
/*                                                                          */
/*--------------------------------------------------------------------------*/

/* Initialize the heap.  Returns 1 on success, or 0 on failure. */
int32_t heap_init ();

/* Insert an event into the heap.  Returns 1 on success, or 0 on failure. */
int32_t heap_insert (double time, int32_t queue_num, int32_t type, 
		     double arrival);

/* 
 * Peek at the first event in the heap.  Returns 1 if the heap is not 
 * empty, or 0 otherwise.  On success, *time_ptr holds the time of the
 * first event in the heap.
 */
int32_t heap_peek_min (double* time_ptr);

/* 
 * Extract the first event in the heap.  Returns 1 if the heap is not 
 * empty, or 0 otherwise.  On success, the event's values are stored at
 * the four addresses passed into the function.
 */
int32_t heap_get_min (double* time_ptr, int32_t* queue_num_ptr, 
		      int32_t* type_ptr, double* arrival_ptr);


/*--------------------------------------------------------------------------*/
/*                                                                          */
/*                       PROGRAM 8 HISTOGRAM FUNCTIONS                      */
/*                                                                          */
/*--------------------------------------------------------------------------*/

/* Initialize the histogram.  Returns 1 on success, or 0 on failure. */
int32_t hist_init ();

/* Record a single delay value.  Returns 1 on success, or 0 on failure. */
int32_t hist_record_delay (double val);

/* Record a single delay value.  Returns 1 on success, or 0 on failure. */
int32_t hist_dump ();


/*--------------------------------------------------------------------------*/
/*                                                                          */
/*                      PROGRAM 8 STORE MODEL FUNCTIONS                     */
/*                                                                          */
/*--------------------------------------------------------------------------*/

/* 
 * Initialize a distributed store model.  Returns 1 on success, 
 * or 0 on failure. 
 */
int32_t distributed_store_init (int32_t n_queues, 
				double arrival_rate, double service_rate, 
				double measure_start, double measure_end);

/* 
 * Initialize a centralized store model.  Returns 1 on success, 
 * or 0 on failure. 
 */
int32_t centralized_store_init (int32_t n_queues, double arrival_rate, 
				double service_rate, double measure_start, 
				double measure_end);

/* 
 * Deliver one event to the store model.  Returns 1 if the simulation 
 * should terminate (no more events left to track during measure period,
 * or some kind of error occurred), or 0 if the simulation should continue.
 */
int32_t store_model (double time, int32_t queue_num, int32_t type, 
		     double arrival);


/*--------------------------------------------------------------------------*/
/*                                                                          */
/*                        PROGRAM 8 UTILITY FUNCTION                        */
/*                                                                          */
/*--------------------------------------------------------------------------*/

/* 
 * Sample an exponential distribution with parameter lambda,
 * that is: lambda * exp (-lambda * t) 
 */
double sample_exp (double lambda);

#if defined(__cplusplus)
}
#endif //defined(__cplusplus)

#endif /* PROG_8_H */

