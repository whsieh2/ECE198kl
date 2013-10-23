/*									tab:8
 *
 * util.c - source file for UIUC ECE198KL Spring 2013 Program 8 utilities
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
 * Filename:	    util.c
 * History:
 *	SL	1.00	10 March 2013
 *		First created.
 */

#include <math.h>
#include <stdlib.h>

#include "prog8.h"

/*
 * sample_exp -- sample an exponential distribution; the exponential 
 *               distribution is memoryless (events are independent of 
 *               past/future events), and using it for interarrival times
 *               (as in a Poisson process) makes analysis easier
 * INPUTS: lambda -- parameter value for the distribution
 * OUTPUTS: none
 * RETURN VALUE: random sample from f(t) = lambda * exp (- lambda * t)
 * SIDE EFFECTS: none
 */
double
sample_exp (double lambda)
{
    return (- log (1 - drand48 ()) / lambda);
}


