#include "MP9.h"
// reads in the two preference files and populates the preference matrices.
// INPUT: 
// menPrefs: men preference file name
// womenPrefs: women preference file name
// size: The number of men or women
// men: empty men preference array
// women: empty women preference array
// SIDE EFFECTS:
// men: populated men preference array where men[i][j] is the jth preference of the ith man
// women: populated women preference array where women[i][j] is the jth preference of the jth woman

void readPrefFiles(char *menPrefs, char *womenPrefs, int size, int **men, int **women)
{
}

//This function recursively solves the stable marriage problem
//INPUTS:
//men- populated preference array for men
//women- populated preference array for women
//solution- the 1-dimensional solution array where solution[i] is the wife of man i
//size- Number of men or women
//start- Start of the subarray
//end- End of subarray
void maleOptimalSolution(int **men, int **women, int *solution, int start, int end, int size)
{
}

// This function handles the merging of the solutions to two sub problems
// The parameters passed to this function have the same meaning as the maleOptimalSolution function
void maleOptimalMerge(int **men,int **women,int *solution, int start, int end, int size)
{
}

void femaleOptimalSolution(int **men, int **women, int *solution, int start, int end, int size)
{
}

void femaleOptimalMerge(int **men, int **women, int *solution, int start, int end, int size)
{
}
