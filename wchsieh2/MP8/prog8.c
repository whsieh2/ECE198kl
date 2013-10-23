/*									tab:8
 *
 * prog8.c - source file for UIUC ECE198KL Spring 2013 Program 8 main program
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
 * Creation Date:   8 March 2013
 * Filename:	    prog8.c
 * History:
 *	SL	1.00	8 March 2013
 *		First created.
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "prog8.h"


/*
 * main -- the main program for discrete event simulation of a store
 * INPUTS: argc -- number of command-line arguments (includes executable name)
 *         argv -- array of command-line arguments (strings)
 * OUTPUTS: none
 * RETURN VALUE: 0=success, 2=bad arguments, 3=panic
 * SIDE EFFECTS: prints simulation results
 */
int
main (int argc, char* argv[])
{
    char    trash[2];	/* catches trailing trash in arguments             */
    int32_t store_type;	/* 0=distributed, 1=centralized                    */
    int32_t n_queues;	/* number of queues to simulate                    */
    double  arr_rate;   /* arrival rate to simulate (total)                */
    double  serv_rate;  /* service rate to simulate (total)                */
    double  start_time; /* measurement start (sim. starts at 0)            */
    double  end_time;	/* measurement end (sim. stops when last finishes) */
    int32_t n_runs;	/* number of simulation runs (for smoother curves) */
    int32_t run;	/* simulation run counter                          */
    double  time;	/* time for a single event                         */
    int32_t queue_num;	/* queue number for a single event                 */
    int32_t type;	/* type of a single event (arrival/departure)      */
    double  arrival;	/* original arrival time for a single event        */

    /* Randomize (in a deterministic way). */
    srand (12312410);
    srand48 (53412312);

    /* Check and interpret command-line arguments. */
    if (8 != argc) {
        fprintf (stderr, "syntax:\n   %s <type> <# queues> <arr. rate> <serv. "
		 "rate> <start> <stop> <# runs>\n", argv[0]);
	return 2;
    }
    if (0 == strcmp (argv[1], "d") || 0 == strcmp (argv[1], "distributed")) {
        store_type = 0;
    } else if (0 == strcmp (argv[1], "c") || 
	       0 == strcmp (argv[1], "centralized")) {
        store_type = 1;
    } else {
        fputs ("type must be (d)istributed or (c)entralized\n", stderr);
	return 2;
    }
    if (1 != sscanf (argv[2], "%d%1s", &n_queues, trash) ||
        1 > n_queues || MAX_QUEUES < n_queues) {
        fprintf (stderr, "number of queues must be between 1 and %d\n",
		 MAX_QUEUES);
        return 2;
    }
    if (1 != sscanf (argv[3], "%lf%1s", &arr_rate, trash) || 0 >= arr_rate) {
        fputs ("arrival rate must be positive\n", stderr);
        return 2;
    }
    if (1 != sscanf (argv[4], "%lf%1s", &serv_rate, trash) || 
    	arr_rate >= serv_rate) {
        fputs ("service rate must be greater than arrival rate\n", stderr);
        return 2;
    }
    if (1 != sscanf (argv[5], "%lf%1s", &start_time, trash) || 
    	0 > start_time) {
        fputs ("start time must be non-negative\n", stderr);
        return 2;
    }
    if (1 != sscanf (argv[6], "%lf%1s", &end_time, trash) || 
    	start_time >= end_time) {
        fputs ("end time must be greater than start time\n", stderr);
        return 2;
    }
    if (1 != sscanf (argv[7], "%d%1s", &n_runs, trash) ||
        1 > n_runs || MAX_RUNS < n_runs) {
        fprintf (stderr, "number of runs must be between 1 and %d\n",
		 MAX_RUNS);
        return 2;
    }

    /* Initialize the histogram. */
    if (!hist_init ()) {
        fputs ("Histogram initialization failed.\n", stderr);
	return 3;
    }

    /* Perform the requested number of runs. */
    for (run = 0; n_runs > run; run++) {

    	/* Initialize the requested store model. */
	if ((1 == store_type &&
	     !centralized_store_init (n_queues, arr_rate, serv_rate,
	     			      start_time, end_time)) ||
	    (0 == store_type &&
	     !distributed_store_init (n_queues, arr_rate, serv_rate, 
				      start_time, end_time))) {
	    fputs ("Model initialization failed.\n", stderr);
	    return 3;
	}

	/* Execute the simulation until it terminates. */
	while (heap_get_min (&time, &queue_num, &type, &arrival) &&
	       !store_model (time, queue_num, type, arrival)) {
	}
    }

    /* Dump the results. */
    if (!hist_dump ()) {
        fputs ("Histogram dump failed.\n", stderr);
	return 3;
    }

    /* Success! */
    return 0;
}

