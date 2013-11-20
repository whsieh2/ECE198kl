/*! File module

    Provides level loading functionality through a function that creates a game from a
    level file.  Also provides a function for destroying the game instance for use during
    teardown.
*/
/*
INTRO:

I used the website as a guide for all my functions. create_game simply reads the input file and converts the chars into information for the set up of the game
It also creates the snake and board inside the create_game function. In destroy game I call the destroy snake and destroy board helper functions.





*/
#include "game.h"
#include "file.h"

#include <stdio.h>
#include <stdlib.h>

game * create_game(const char * file_name)
/*! Load an input level file with given file_name with format specified in levels/README.txt,
    and transform the serialized data within into a game data structure, specified in game.h
    Return a pointer to the game instance on success, NULL on failure.

    Note that error handling is not required for credit, but may help with testing.

    The game and structures it points to should be allocated with the malloc family of
    functions.  Make sure to take advantage of allocation functions provided by the game module.
*/

{
    //this program takes input files from file_name and then creates the game out of the other functions. this one specifically calls those functions and creates the board based on the character present on the input file
    
    FILE*inputFile = fopen(file_name, "r"); // reads file
    game * my_game = malloc(sizeof(game)); // allocates memory for the game
    int rows, cols,i,j;
    char currentchar;
    cell* currentcell;
    fscanf(inputFile, "%d %d %f %f %d", &rows, &cols, &my_game->time_step, &my_game->food_probability, &my_game->growth_per_food);
    my_game->board = create_board(rows, cols); // calls create_board to create a game
    char cellarray[rows][cols+1];

    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols + 1; j++)
        {
        	fscanf(inputFile, "%c", &cellarray[i][j]); // takes input and stores it in the cell array
            currentchar = cellarray[i][j];
            currentcell = board_cell(my_game->board, i, j); // calls board using board_cell and sets it as the current cell to see what the game should do with that cell
            if(currentchar != '\n')
            {
                switch(currentchar) // uses a switch case to figure out what each individual cell should be based on the current character
                {
                    case 'X':
                        *currentcell = CELL_WALL;
                        break;
                    case '-':
                        *currentcell = CELL_OPEN;
                        break;
                        
                    case 'n':
                        my_game->human_snake = create_snake(my_game->board, i, j, NORTH, 0);
                        break;
                    case 's':
                        my_game->human_snake = create_snake(my_game->board, i, j, SOUTH, 0);
                        break;
                    case 'e':
                        my_game->human_snake = create_snake(my_game->board, i, j, EAST, 0);
                        break;
                    case 'w':
                        my_game->human_snake = create_snake(my_game->board, i, j, WEST, 0);
                        break;
                        
                    case 'N':
                        my_game->computer_snake = create_snake(my_game->board, i, j, NORTH, 0);
                        break;
                    case 'S':
                        my_game->computer_snake = create_snake(my_game->board, i, j, SOUTH, 0);
                        break;
                    case 'E':
                        my_game->computer_snake = create_snake(my_game->board, i, j, EAST, 0);
                        break;
                    case 'W':
                        my_game->computer_snake = create_snake(my_game->board, i, j, WEST, 0);
                        break;
                }
            }
        }
    }
    fclose(inputFile); // close the file, the game has been made.
    return my_game; /* return game */

}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains.  Make sure to take
    advantage of deallocation functions provided by the game module. */
{
	destroy_snake(cur_game->computer_snake);
	destroy_board(cur_game->board);
	destroy_snake(cur_game->human_snake);
	
	free(cur_game);
}
