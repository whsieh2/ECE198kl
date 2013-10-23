/*									tab:8
 *
 * store.c - source file for UIUC ECE198KL Spring 2013 Program 8 store model
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
 * Creation Date:   10 March 2013
 * Filename:	    store.c
 * History:
 *	SL	1.00	10 March 2013
 *		First created.
 *	SL	1.01	11 March 2013
 *		Centralized store added.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "prog8.h"


/* 
 * Two types of stores: the main difference is whether a customer, on 
 * arriving, picks a queue with the fewest number of people waiting
 * (DISTRIBUTED) or picks a queue that will be empty the soonest
 * (CENTRALIZED).  This difference models the usual store strategy
 * in the distributed case, and the holiday-time strategy of pooling
 * customers in a single line and only forwarding them to an actual
 * line when that line is empty in the centralized case.
 */
enum {
    DISTRIBUTED,
    CENTRALIZED
};

static int32_t s_type;			/* DISTRIBUTED or CENTRALIZED      */
static double  s_num_queues;		/* number of queues                */
static double  s_q_len[MAX_QUEUES];	/* queue length (per queue)        */
static double  s_q_finish[MAX_QUEUES];	/* queue finish time (per queue)   */
static double  s_arrival_rate;		/* arrival rate                    */
static double  s_service_rate;		/* service rate (per queue)        */
static double  s_measure_start;		/* measurement start time   	   */
static double  s_measure_end;		/* measurement end time 	   */
static int32_t s_measured_count;	/* number of people being measured */


/*
 * store_init_internal -- initialize a store model (called from external
 *                        functions to check arguments and to do most of the
 *                        work of initialization)
 * INPUTS: n_queues -- number of queues in the store
 *         arrival_rate -- expected arrivals per time unit
 *         service_rate -- total expected customers served per time unit
 *         measure_start -- simulation time to start measuring
 *         measure_end -- simulation time to end measuring
 * OUTPUTS: none
 * RETURN VALUE: 1 on success, or 0 on failure
 * SIDE EFFECTS: records settings in file-scope variables
 */
static int32_t
store_init_internal (int32_t n_queues,
		     double arrival_rate, double service_rate, 
		     double measure_start, double measure_end)
{
    int qnum;

    if (1 > n_queues || MAX_QUEUES < n_queues ||
        0 > arrival_rate || service_rate <= arrival_rate ||
        0 > measure_start || 0 > measure_end) {
	return 0;
    }
    s_num_queues     = n_queues;
    s_arrival_rate   = arrival_rate;
    s_service_rate   = service_rate / n_queues;
    s_measure_start  = measure_start;
    s_measure_end    = measure_end;
    s_measured_count = 0;
    if (!heap_init () ||
    	!heap_insert (sample_exp (s_arrival_rate), 0, EVENT_ARRIVAL, 0.0)) {
        return 0;
    }
    for (qnum = 0; s_num_queues > qnum; qnum++) {
	s_q_len[qnum]    = 0;
	s_q_finish[qnum] = 0.0;
    }
    return 1;
}


/*
 * distributed_store_init -- initialize a distributed store model
 * INPUTS: n_queues -- number of queues in the store
 *         arrival_rate -- expected arrivals per time unit
 *         service_rate -- total expected customers served per time unit
 *         measure_start -- simulation time to start measuring
 *         measure_end -- simulation time to end measuring
 * OUTPUTS: none
 * RETURN VALUE: 1 on success, or 0 on failure
 * SIDE EFFECTS: records settings in file-scope variables
 */
int32_t
distributed_store_init (int32_t n_queues,
		        double arrival_rate, double service_rate, 
			double measure_start, double measure_end)
{
    s_type = DISTRIBUTED;
    return store_init_internal (n_queues, arrival_rate, service_rate,
    				measure_start, measure_end);
}


/*
 * centralized_store_init -- initialize a centralized store model
 * INPUTS: n_queues -- number of queues in the store
 *         arrival_rate -- expected arrivals per time unit
 *         service_rate -- total expected customers served per time unit
 *         measure_start -- simulation time to start measuring
 *         measure_end -- simulation time to end measuring
 * OUTPUTS: none
 * RETURN VALUE: 1 on success, or 0 on failure
 * SIDE EFFECTS: records settings in file-scope variables
 */
int32_t
centralized_store_init (int32_t n_queues,
		        double arrival_rate, double service_rate, 
			double measure_start, double measure_end)
{
    s_type = CENTRALIZED;
    return store_init_internal (n_queues, arrival_rate, service_rate,
    				measure_start, measure_end);
}


/*
 * store_model -- handle one event for the store model
 * INPUTS: time -- time of the event
 *         queue_num -- queue_num for the event (EVENT_DEPARTURE only)
 *         type -- EVENT_ARRIVAL or EVENT_DEPARTURE
 *         arrival -- original arrival time (EVENT_DEPARTURE only)
 * OUTPUTS: none
 * RETURN VALUE: 1 if the measurement period has finished and all measured
 *               customers have left the store (in which case the simulation
 *               should terminate); 0 otherwise
 * SIDE EFFECTS: creates new events
 */
int32_t
store_model (double time, int32_t queue_num, int32_t type, double arrival)
{
    int32_t min_q;
    int32_t count;
    double  start_processing;
    double  completion_time;

    if (EVENT_ARRIVAL == type) {
	/* Start by inserting the next arrival. */
        if (!heap_insert (time + sample_exp (s_arrival_rate), 
			  0, EVENT_ARRIVAL, 0.0)) {
	    fputs ("heap insert failed\n", stderr);
	    return 1;
	}

	/* Find the shortest queue, breaking ties at random. */
	min_q = 0;
	if (DISTRIBUTED == s_type) {
	    count = 1;
	    for (queue_num = 1; s_num_queues > queue_num; queue_num++) {
		if (s_q_len[min_q] > s_q_len[queue_num]) {
		    min_q = queue_num;
		    count = 1;
		} else if (s_q_len[min_q] == s_q_len[queue_num] &&
			   0 == (rand () % ++count)) {
		    min_q = queue_num;
		}
	    }
	} else {
	    /* 
	     * Ties do not matter for this model (and are also exceedingly
	     * unlikely to occur).
	     */
	    for (queue_num = 1; s_num_queues > queue_num; queue_num++) {
		if (s_q_finish[min_q] > s_q_finish[queue_num]) {
		    min_q = queue_num;
		}
	    }
	}
	/* 
	 * Find the time at which the queue can start processing this
	 * arrival, which is the later of the previous person's time
	 * and the actual arrival.
	 */
	start_processing = s_q_finish[min_q];
	if (start_processing < time) {
	    start_processing = time;
	}
	/*
	 * We add a randomly distributed service time to find the
	 * completion time, then mark the queue as being ready for the
	 * next person at that time.
	 */
	completion_time = start_processing + sample_exp (s_service_rate);
	s_q_finish[min_q] = completion_time;
	s_q_len[min_q]++;
        if (!heap_insert (completion_time, min_q, EVENT_DEPARTURE, time)) {
	    fputs ("heap insert failed\n", stderr);
	    return 1;
	}
	/* If the new person should be measured, count them. */
	if (s_measure_start <= time && s_measure_end > time) {
	    s_measured_count++;
	}
	return 0;
    }
    /* 
     * This event marks a departure.  We may need to record a 
     * measurement, and we may need to indicate that the simulation
     * is done.
     */
    if (s_measure_start <= arrival && s_measure_end > arrival) {
	if (!hist_record_delay (time - arrival)) {
	    fputs ("Histogram failure!\n", stderr);
	    return 1;
	}
	s_measured_count--;
	s_q_len[queue_num]--;
    }
    return (s_measure_end <= time && 0 == s_measured_count);
}


