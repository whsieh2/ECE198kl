/*									tab:8
 *
 * prog5.c - source file for UIUC ECE198KL Spring 2013 Program 5
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
 * Creation Date:   7 February 2013
 * Filename:	    prog5.c
 * History:
 *	SL	1.00	7 February 2013
 *		First created.
 *	SL	1.01	9 February 2013
 *		Gold version and challenges ready completed.
 *	SL	1.02	9 February 2013
 *		Assignment version created.
 */

#include "prog5.h"

/*
INTRO: 

In this program, I created set_seed using the information given to use during
lab and the provided powerpoint. Using that algorithm, I was able to successfully 
compare the user's guessed values to the solutions, created by the library's random
number generater using a number the user provides (start_game). 
In make_guess I first make sure the user inputted 4 numbers, separated by spaces, that are between 1 and 8.
If none of the criterion were met, the user would get an invalid statement and could enter another guess.
I first compared each digit to it's corresponding solution. so if the solution was A B C D and the user
guessed a b c d, I would first compare A and a, B and b, and etc. This would ensure I would find any perfect
matches immediately. Then I checked purely for mismatches. Anything that wasn't a mismatch was assumed wrong.
To keep a status of whether A, B, C, D had been claimed as perfect, or mismatched, I used an array, correct[].
0 meant that particular solution had not found it's match at all. 1 meant it had found a perfect match. and 2
meant that there value existed, but was not in the correct location.
*/
/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * here to help you get started.
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables.  You may need others for solving the challenges.  A
 * sample for one variable of the code is shown below for you.
 */
static int32_t soln1;
static int32_t soln2;
static int32_t soln3;
static int32_t soln4;
static int32_t guessCount; //file scope for the guess count


/*
 * set_seed -- uses sscanf to find the random seed value, then initializes
 *             the random number generator by calling srand with the seed
 * INPUTS: seed_str -- a string entered by the user for the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (contains something
 *               other than a single integer), or 1 on success
 * SIDE EFFECTS: initializes pseudo-random number generation
 */
int32_t 
set_seed (const char* seed_str)	
{   //code given during lab.
	int seed;
	char post[2];
	if (1 == sscanf (seed_str, "%d%1s", &seed, post)) 
	{
		srand (seed);
		return 1;
	}
	prog5_printf ("set_seed: invalid seed\n");
	return 0;
}


/*
 * start_game -- creates the solution combination using the approach
 *               described in the assignment specification (using rand)
 * INPUTS: none
 * OUTPUTS: *one -- the first color value in thYour routine must validate the string in the same way that we did for sete code (between 1 and 8)
 *          *two -- the second color value in the code (between 1 and 8)
 *          *three -- the third color value in the code (between 1 and 8)
 *          *four -- the fourth color value in the code (between 1 and 8)
 * RETURN VALUE: 1 on success, or 0 on failure (should never fail, though)
 * SIDE EFFECTS: records the solution code for use by make_guess
 */
int32_t
start_game (int32_t* one, int32_t* two, int32_t* three, int32_t* four)
{
	//each solution is randomly selected based on a number the user selects.
	*one = (((rand())%8)+1);
	soln1 = *one;
    *two = (((rand())%8)+1);
    soln2 = *two;
    *three = (((rand())%8)+1);
    soln3 = *three;
    *four = (((rand())%8)+1);
    soln4 = *four;
    //prog5_printf("%d %d %d %d\n", soln1,soln2,soln3,soln4); For debugging purposes, 
    //solutions are printed(currently commented out)
    return 1;
}


/*
 * make_guess -- calculates the number of perfect and misplaced matches
 *               for a given guess, relative to the solution code recorded
 *               earlier by start_game
 * INPUTS: guess_str -- a string consisting of four numbers for the guess
 * OUTPUTS: the following are only valid if the function returns 1
 *          *one -- the first color value in the guessed code (between 1 and 8)
 *          *two -- the second color value in the guessed code (between 1 and 8)
 *          *three -- the third color value in the guessed code
 *                    (between 1 and 8)
 *          *four -- the fourth color value in the guessed code
 *                    (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (represents exactly four
 *               numbers between 1 and 8), or if it is not
 * SIDE EFFECTS: prints the number of matches found using prog5_printf
 *               (NOTE: the output format MUST MATCH EXACTLY)
 */
int32_t
make_guess (const char* guess_str, int32_t* one, int32_t* two, 
	    int32_t* three, int32_t* four)
{ 	

	//guess string is stored in each variable using the algorthim from seed.
	char post[2];
	
	//makes sure there are only 4 inputted numbers.
	if (4 == sscanf (guess_str, "%d%d%d%d%1s", &*one, &*two ,&*three,&*four,post)) 
	{
		int validNum = 0; //holds the number of perfect matches
		int misplace = 0; //holes the number of missplaced numbers
		int correct[4]; //initiated a array to store information on each soln's status
		// 0=not corrected/unchecked. 1= perfect match. 2= missplaced number.
		int i; //"‘for’ loop initial declarations are only allowed in C99 mode" so i initiated i here.
		for (i=0; i<4; i++)
			correct[i]=0; 
		
		//checks to make sure the numbers are all between 1-8.
		if (((*one >8) || (*one <1))||((*two >8) || (*two <1))||((*three <1)|| (*three>8))||((*four <1) ||(*four>8)))
		{
			prog5_printf("make_guess: invalid guess\n");
			return 0;
		}
		else
		{
			//First I checked purely for perfect matches.
			if (*one ==soln1)
			{
				correct[0]=1;
				validNum++;
			}
			if (*two ==soln2)
			{
				correct[1]=1;
				validNum++;
			}
			if (*three==soln3)
			{
				correct[2]=1;
				validNum++;		
			}
			if (*four==soln4)
			{
				correct[3]=1;
				validNum++;
			}
			
			//If no perfect matches are found, the corresponding correct[] will still be 0.
			//I check each guess with every single solution, then I will move on to the next
			//consecutive guess. If there are any matches, it is a missplaced number, and the correct[]
			//value will be changed to 2, making it so other guesses cannot be compared to this number.
			if ((*one == soln2)&&(correct[1]==0))
			{
				misplace++;
				correct[1]=2;
			}
			if ((*one == soln3)&&(correct[2]==0))
			{
				misplace++;
				correct[2]=2;
			}
			if ((*one == soln4)&&(correct[3]==0))
			{
				misplace++;
				correct[3]=2;
			}
			if (*two ==soln1)
			{
				if (correct[0] ==0)
				{
					misplace++;
					correct[0]=2;
				}
			}
			if (*two ==soln3)
			{
				if (correct[2]==0)
				{
					misplace++;
					correct[2]=2;
					
				}
			}
			if (*two ==soln4)
			{
				if (correct[3]==0)
				{
					misplace++;
					correct[3]=2;
				
				}
			}
			if (*three==soln1)
			{
				if (correct[0] ==0)
				{
					misplace++;
					correct[0]=2;
				}	
			}
			if (*three==soln2)
			{
				if (correct[1] ==0)
				{
					misplace++;
					correct[1]=2;
				
				}
			}
			if (*three==soln4)
			{
				if (correct[3]==0)
				{
					misplace++;
					correct[3]=2;
				}
			}			
		
			if (*four==soln1)
			{
				if (correct[0] ==0)
				{
					misplace++;
					correct[0]=2;
				}
			}
			if (*four==soln2)
			{
				if (correct[1] ==0)
				{
					misplace++;
					correct[1]=2;
				}
			}
			if (*four==soln3)
			{
				if (correct[2]==0)
				{
					misplace++;
					correct[2]=2;
				}
			}
			guessCount++;
			if (guessCount > 13)
			{
				prog5_printf("make_guess: invalid guess\n");
				return 0;
			}
			//feedback with the # of guesses, # of perfect matches, and # of misplaced matches
			prog5_printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n",guessCount, validNum, misplace);
			return 1;
		}
	}
	//One of the guesses was not between 1 and 8.
	else
	{
		prog5_printf("make_guess: invalid guess\n");
		return 0;
	}
}

/*
 * compare_guesses -- compares two guesses to check whether a new guess
 *                    might be the solution, given the feedback on a previous
 *                    guess in terms of perfect and misplaced matches
 * INPUTS: orig1-orig4 -- the original code (an earlier guess)
 *         n_perfect -- the number of perfect matches for original code
 *         n_misplaced -- the number of perfect matches for original code
 *                        (your printed response to make_guess is stored for
 *                         this purpose)
 *         guess1-guess4 -- the new guess
 * OUTPUTS: none
 * RETURN VALUE: 1 if the guess code *could* be the solution, as determined
 *               by the original code and the feedback given on it
 * SIDE EFFECTS: none
 */
int32_t 
compare_guesses (int32_t orig1, int32_t orig2, int32_t orig3, int32_t orig4, 
		 int32_t n_perfect, int32_t n_misplaced, int32_t guess1, 
		 int32_t guess2, int32_t guess3, int32_t guess4)
{
		//I used a little bit of my program from make_guess to get the 
		//# of perfects and mismatches in the new guess.
		int validNum = 0;
		int misplace = 0;
		int correct[4];
		int i;
		for (i=0; i<4; i++)
			correct[i]=0;
		if (((guess1 >8) || (guess1 <1))||((guess2 >8) || (guess2 <1))||((guess3 <1)|| (guess3>8))||((guess4 <1) ||(guess4>8)))
		{
			prog5_printf("make_guess: invalid guess\n");
			return 0;
		}
		else
		{
			if (guess1 ==soln1)
			{
				correct[0]=1;
				validNum++;
			}
			if (guess2 ==soln2)
			{
				correct[1]=1;
				validNum++;
			}
			if (guess3==soln3)
			{
				correct[2]=1;
				validNum++;
				
			}
			if (guess4==soln4)
			{
				correct[3]=1;
				validNum++;
			}
			if ((guess1 == soln2)&&(correct[1]==0))
			{
				misplace++;
				correct[1]=2;
			}
			if ((guess1 == soln3)&&(correct[2]==0))
			{
				misplace++;
				correct[2]=2;
			}
			if ((guess1 == soln4)&&(correct[3]==0))
			{
				misplace++;
				correct[3]=2;
			}
			if (guess2 ==soln1)
			{
				if (correct[0] ==0)
				{
					misplace++;
					correct[0]=2;
				}
			}
			if (guess2==soln3)
			{
				if (correct[2]==0)
				{
					misplace++;
					correct[2]=2;
					
				}
			}
			if (guess2 ==soln4)
			{
				if (correct[3]==0)
				{
					misplace++;
					correct[3]=2;
				
				}
			}
			if (guess3==soln1)
			{
				if (correct[0] ==0)
				{
					misplace++;
					correct[0]=2;
				}	
			}
			if (guess3==soln2)
			{
				if (correct[1] ==0)
				{
					misplace++;
					correct[1]=2;
				
				}
			}
			if (guess3==soln4)
			{
				if (correct[3]==0)
				{
					misplace++;
					correct[3]=2;
				}
			}			
		
			if (guess4==soln1)
			{
				if (correct[0] ==0)
				{
					misplace++;
					correct[0]=2;
				}
			}
			if (guess4==soln2)
			{
				if (correct[1] ==0)
				{
					misplace++;
					correct[1]=2;
				}
			}
			if (guess4==soln3)
			{
				if (correct[2]==0)
				{
					misplace++; 
					correct[2]=2;
				}
			}
			guessCount++;
			
			// I decided that a guess is always better if the number of perfect
			//matches increases
			if (validNum>n_perfect)
				return 1;
				
			//If the number of perfect matches doesn't increase, but the number of 
			//misplaced matches increase, you had a better guess because your pool of
			//correct numbers is increased.
			else if ((validNum==n_perfect)&&(misplace>n_misplaced))
				return 1;
			//anything else is considered a worse guess. Improvement only makes a better guess.
			else 
				return 0;
		}
	
}


/*
 * get_hint -- obtains a hint code (four values from 1 to 8) that matches
 *             the feedback on all previous guesses
 *                    might be the solution, given the feedback on a previous
 * INPUTS: hint -- pointer to an array of four integers for storing the hint
 * OUTPUTS: hint[0]-hint[3] -- the hint given (if 1 is returned)
 * RETURN VALUE: 1 if a hint has been offered, or 0 otherwise
 * SIDE EFFECTS: none
 *
 * NOTE: You will have to track previous guesses and feedback yourself.  
 * NO CREDIT will be given for a hint function that always returns the 
 * solution as a hint.
 */
int32_t
get_hint (int32_t* hint)
{
    return 0;
}

