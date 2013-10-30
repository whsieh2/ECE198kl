#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void readPrefFiles(char *menPrefs, char *womenPrefs, int size, int **men, int **women);
void maleOptimalSolution(int **men, int **women, int *solution, int start, int end, int size);
void maleOptimalMerge(int **men,int **women,int *solution, int start, int end, int size);
void femaleOptimalSolution(int **men, int **women, int *solution, int start, int end, int size);
void femaleOptimalMerge(int **men,int **women,int *solution, int start, int end, int size);

