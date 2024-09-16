//partners: devdp2, loganeh2
//Aryan Shah
//ECE 220 FA22

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/*The purpose of this program was to read in a maze from a filepath and solve it recursively.
Our first function, createMaze uses fscanf to read in the rows and cols, then uses pointers
to set each individual cell, which were allocated using malloc and calloc. A buffer was 
also set to read in the lines of the file properly. The function destroy maze loops through each cell and 
calls the free function to destroy each cell. The print maze function loops through each row and col of each cell
and prints it as specified in the wiki. Finally, the solveMazeDFS function
utilizes the recursive steps as explained in the wiki's pseudocode.*/

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.

    maze_t *maze = (maze_t*)malloc(sizeof(maze_t)); //use malloc to allocate memory for maze

    int rows, cols; //define variables for rows, cols
    FILE *file = fopen(fileName, "r"); //open file in read-only format
    fscanf(file, "%d%d", &cols, &rows); //get columns first int and rows second int of first line

    maze->width = cols; //set width variable for maze
    maze->height = rows; //set height variable for maze
    
    maze->cells = (char**)malloc(rows*sizeof(char*)); //use malloc to allocate memory for each possible rows

    for(int i = 0; i < rows; i++) //loop through rows
    {
        maze->cells[i] = (char*)malloc(cols*sizeof(char)); //for each cell's row, allocate memory for cols
        for(int j = 0; j < cols; j++) //loop through cols
        {
            char filechar = fgetc(file); //set character for reading from the input file
            while(filechar == '\n') //check for being a newline
            {
                filechar = fgetc(file); //skip and read next file
            }
            maze->cells[i][j] = filechar; //assign character from input file into each cell
            if(maze->cells[i][j] == 'S') //check if value is at start position
            {
                maze->startRow = i; //update starting row
                maze->startColumn = j; //update starting column
            }
            if(maze->cells[i][j] == 'E') //check if value is at end positoon
            {
                maze->endRow = i; //update ending row
                maze->endColumn = j; //update ending column
            }
        }
    }
    fclose(file); //close the file
    return maze; //return maze
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze) //remove allocated memory for cell, cell array, and maze
{
    // Your code here.
    for(int cols = 0; cols < maze->height; cols++) //loop through maze
    {
        free(maze->cells[cols]); //remove allocated memory for each cell, can get every cell without looping through both rows and cols
    }
    free(maze->cells); //remove allocated memory for the array of cells
    free(maze); //remove allocated memory for the maze
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    for(int cols = 0; cols < maze->height; cols++) //loop through cols
    {
        for(int rows = 0; rows < maze->width; rows++) //loop through rows
        {
            printf("%c", maze->cells[cols][rows]); //print each instance of every cell index as a character using printf
        }
        printf("\n"); //print a new line to look like course wiki example
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row) //use pseudocode from course wiki
{
    // Your code here. Make sure to replace following line with your own code.
    if(col >= maze->height || row >= maze->width || col < 0 || row < 0) //step 1, check out of bounds
    {
        return 0; //return false if outside of bounds
    }
    if(maze->cells[row][col] == 'E') //step 3, end of the maze
    {
        return 1; //return true if at the end of the maze
    }
    if(maze->cells[row][col] != ' ' && maze->cells[row][col] != 'S') //step 2, not an empty cell
    {
        return 0; //return false if not an empty cell
    }
    if(maze->cells[row][col] != 'S')
    {
    maze->cells[row][col] = '*'; //step 4, set col,row as part of solution path
    }
    if(solveMazeDFS(maze, col, row-1) == 1) //step 5, if left of col,row
    {
        return 1; //return true
    }
    if(solveMazeDFS(maze, col+1, row) == 1) //step 6, if right of col, row
    {
        return 1; //return true
    }
    if(solveMazeDFS(maze, col, row+1) == 1) //step 7, up of col, row
    {
        return 1; //return true
    }
    if(solveMazeDFS(maze, col-1, row) == 1) //step 8, down of col, row
    {
        return 1; //return true
    }
    if(maze->cells[row][col] != 'S')
    {
    maze->cells[row][col] = '~'; //step 9, unmark col,row as part of solution
    }
    return 0; //return false
}