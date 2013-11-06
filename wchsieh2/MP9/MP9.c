#include "MP9.h"

/* 
INTRO: 
I did each part to its description. I first read from the 2 files and populated the matrices.
Then I recursively ran the maleOptimalSolution followed by merging it. 
In the merge, I checked to see if there was any initial conflict, 1 woman being paired to 2 men.
Then gave preference to the woman. I do this twice. And I finally check it there are any more conflicts, in which 
merge will run again.
*/
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
	FILE *fileMen; 
	FILE *fileWomen; 
	fileMen = fopen(menPrefs,"r"); 
	fileWomen = fopen(womenPrefs,"r"); 
	int x,y; 
	for(x=0;x<size;x++) 
	{ 
		for(y=0;y<size;y++) 
		{ 
			fscanf(fileMen,"%d", &men[x][y]); 
			fscanf(fileWomen,"%d", &women[x][y]); 
		} 
	}
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
	if(size==1)
	{
		solution[start]=men[start][0];
	}
	else
	{
		maleOptimalSolution(men, women, solution, start, (start+end)/2,size/2); // Player 1// 
		maleOptimalSolution(men, women, solution, ((start+end)/2) + 1, end, size/2); // Player 2 // 
		maleOptimalMerge(men, women, solution, start, end, size);
	 
	 }
}

// This function handles the merging of the solutions to two sub problems
// The parameters passed to this function have the same meaning as the maleOptimalSolution function
void maleOptimalMerge(int **men,int **women,int *solution, int start, int end, int size)
{ 
	int x,y;
	int checker=0; //see if there is any conflict 
	for(x=0;x<size;x++) 
	{ 
		for(y=0;y<size;y++) 
		{ /* Check for conflicts, EX: if one woman is paired to two men, it needs to be corrected. */ 
			if( (solution[x]==solution[y])&&(x!=y)) 
			{ 
				int k; 
				for(k=0;k<size;k++) 
				{ /* If woman prefers man x, find the next preference of the man y and give to him */ 
					if(women[solution[x]][k]==x) 
					{ 
						int l; 
						for(l=0;l<size;l++) 
						{ 
							if(solution[y]==men[y][l]) 
							{ 
								solution[y]=men[y][l+1]; 
								checker=1; 
								break; 
							} 
							if(checker==1) 
							{
								break;
							} 
							
							
						} 
					} /* If woman prefers man j, find the next preference of the man i and give to him */ 
					else if(women[solution[y]][k]==y) 
					{ 
						int m; 
						for(m=0;m<size;m++) 
						{ 
							if(solution[x]==men[x][m]) 
							{ 
								solution[x]=men[x][m+1]; 
								checker=1; 
								break; 
							} 
							if(checker==1) 
							{
								break;
							} 
						} 
					} 
				} 
			} 
		}	 
	} 
	if(checker==1) //if there is still a conflict
	{ 
		maleOptimalMerge(men, women, solution, start, end, size); 
	} 
}
void femaleOptimalSolution(int **men, int **women, int *solution, int start, int end, int size)
{
}

void femaleOptimalMerge(int **men, int **women, int *solution, int start, int end, int size)
{
}
