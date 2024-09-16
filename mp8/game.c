//partners: devdp2, loganeh2
//Aryan Shah
//ECE 220
//FA22

/*The purpose of this program is to implement the game 2048 in C. The function make_game initializes the proper elements and returns a pointer and
remake_game changes the game board to have the proper rows and columns. The function get_cell returns a pointer to a corresponding cell and a helper
function getIntCell was written to pull an integer value from the given row and column of a cell. The move functions (w, s, a, and d)
were implemented utilizing pointer logic, conditionals, and for loops to properly perge the necessary rows/columns after each keypress.
Finally, the legal_move_check function makes use of conditional logic to ensure that the user's moves are not invalid according to the game rules.*/

#include "game.h"


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame->rows = rows; //create row pointer variable
    mygame->cols = cols; //create column pointer variable
    for(int i = 0; i < rows * cols; i++) //loop through all cells
    {
        mygame->cells[i] = -1; //initialized elements to -1
    }
    return mygame; //return a pointer
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
    (*_cur_game_ptr)->rows = new_rows; //given rows
    (*_cur_game_ptr)->cols = new_cols; //given columns
    (*_cur_game_ptr)->score = -1; //initialize score to -1
    for(int i = 0; i < new_rows * new_cols; i++)
    {
        (*_cur_game_ptr)->cells[i] = -1; //set all elements in the cell to -1
    }
	return;	//return nothing, void
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    if(row > cur_game->rows || row < 0 || col > cur_game->cols || col < 0) //check if given row or col is out of bounds of current game
    {
        return NULL; //if so, return null
    }
    return &(cur_game->cells[row * (cur_game->cols) + col]); //if not, returns pointer to corresponding cell
};

int getIntCell(game * cur_game, int row, int column) //helper method to pull integer value from a cell given its row and column
{
    if(row > cur_game->rows || row < 0 || column > cur_game->cols || column < 0) //check if given row or col is out of bounds of current game
    {
        return 0; //if so, return null
    }
    return (cur_game->cells[row * (cur_game->cols) + column]); //if not, returns pointer to corresponding int at cell
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
int rows = cur_game->rows; //row variable to pointer of number of rows in cur_game board
int cols = cur_game->cols; //col variable to pointer of number of cols in cur_game board
int ret = 0; //return value for w being invalid/valid move (0 = invalid, 1 = valid)
int flag = 0; //flag to check if change occurred
for(int i = 0; i < rows; i++) //loop through rows
{
    for(int j = 0; j < cols; j++) //loop through cols
    { 
        cell *currentCell = get_cell(cur_game, i, j);
        if(*currentCell != -1) //accesing each element of 1D array in cur_game board
        {  
	        for(int ishiftrow = 0; ishiftrow<i; ishiftrow++) //loop through columns in the currently accessed row
            { 
                cell *currentCell2 = get_cell(cur_game, ishiftrow, j);
	            if((*currentCell2 == -1) && flag != 1) //if there are occupied values in the above row
                {
	                *currentCell2 = *currentCell; //set ishiftrow into corresponding i row value
	                *currentCell = -1; //set initial row to -1 to indicate modification
	                ret = 1; //return 1 if valid
	                flag++;  //flag so that code does not run in an infinite loop
	            }
	        } 
        }
    }
}

  for(int i = 0; i < (rows-1); i++) //loop through rows except for changed row
  { 
    for (int j = 0; j < cols; j++) //loop through columns
    {
      int currentInt = getIntCell(cur_game, i, j); //set cell value at current row, col
      int nextInt = getIntCell(cur_game, i+1, j); //set cell value at next row, col
      if(currentInt == nextInt && currentInt != 1 && currentInt != -1) //check if currentInt is a valid number and equal to nextInt
      {
        (cur_game->cells[(i+1)*(cur_game->cols)+j]) = currentInt*2; //set integer value of  nextInt cell to currentInt*2
	    (cur_game->cells[i*(cur_game->cols)+j]) = -1; //set int value of current int to -1 (merge complete)
	    ret = 1; //return flag to 1 to signify change in cell calye
	    (cur_game->score)+= getIntCell(cur_game, i+1, j); //update score with new value in combined next cell
      }
    }
  }

 for(int i = 0; i < rows; i++) //loop through rows
{
    for(int j = 0; j < cols; j++) //loop through cols
    { 
        cell *currentCell = get_cell(cur_game, i, j);
        if(*currentCell != -1) //accesing each element of 1D array in cur_game board
        {  
	        for(int ishiftrow = 0; ishiftrow<i; ishiftrow++) //loop through columns in the currently accessed row
            { 
                cell *currentCell2 = get_cell(cur_game, ishiftrow, j);
	            if(*currentCell2 == -1) //if there are occupied values in the above row
                {
	                *currentCell2 = *currentCell; //set ishiftrow into corresponding i row value
	                *currentCell = -1; //set initial row to -1 to indicate modification
	                ret = 1; //return 1 if valid
	                break;  //flag so that code does not run in an infinite loop
	            }
	        } 
        }
    }
}
    return ret;
};

int move_s(game * cur_game)
{
    //YOUR CODE STARTS HERE
int rows = cur_game->rows; //row variable to pointer of number of rows in cur_game board
int cols = cur_game->cols; //col variable to pointer of number of cols in cur_game board
int ret = 0; //return value for w being invalid/valid move (0 = invalid, 1 = valid)
int flag = 0; //flag to check if change occurred
for(int i = rows-1; i >= 0; i--) //loop through rows inverted
{
    for(int j = cols-1; j >= 0; j--) //loop through cols inverted
    { 
        cell *currentCell = get_cell(cur_game, i, j);
        if(*currentCell != -1) //accesing each element of 1D array in cur_game board
        {  
	        for(int ishiftrow = rows-1; ishiftrow>i; ishiftrow--) //loop through columns in the currently accessed row (inverted)
            { 
                cell *currentCell2 = get_cell(cur_game, ishiftrow, j);
	            if((*currentCell2 == -1) && flag != 1) //if there are occupied values in the above row
                {
	                *currentCell2 = *currentCell; //set ishiftrow into corresponding i row value
	                *currentCell = -1; //set initial row to -1 to indicate modification
	                ret = 1; //return 1 if valid
	                flag++;  //flag so that code does not run in an infinite loop
	            }
	        } 
        }
    }
} //same as move_w, but we go down to up since we shift down instead of up
//effectively invert all of the for loops

  for(int i = (rows-1); i > 0; i--) //loop through rows except for changed row
  { 
    for (int j = 0; j < cols; j++) //loop through columns (normal because of the merge)
    {
      int currentInt = getIntCell(cur_game, i, j); //set cell value at current row, col
      int nextInt = getIntCell(cur_game, i-1, j); //set cell value at next row, col
      if(currentInt == nextInt && currentInt != 1 && currentInt != -1) //check if currentInt is a valid number and equal to nextInt
      {
        (cur_game->cells[(i-1)*(cur_game->cols)+j]) = currentInt*2; //set integer value of  nextInt cell to currentInt*2
	    (cur_game->cells[i*(cur_game->cols)+j]) = -1; //set int value of current int to -1 (merge complete)
	    ret = 1; //return flag to 1 to signify change in cell calye
	    (cur_game->score)+= getIntCell(cur_game, i-1, j); //update score with new value in combined next cell
      }
    }
  }

 for(int i = rows-1; i >= 0; i--) //loop through rows inverted
{
    for(int j = cols-1; j >= 0; j--) //loop through cols
    { 
        cell *currentCell = get_cell(cur_game, i, j);
        if(*currentCell != -1) //accesing each element of 1D array in cur_game board
        {  
	        for(int ishiftrow = rows-1; ishiftrow>i; ishiftrow--) //loop through columns in the currently accessed row
            { 
                cell *currentCell2 = get_cell(cur_game, ishiftrow, j);
	            if(*currentCell2 == -1) //if there are occupied values in the above row
                {
	                *currentCell2 = *currentCell; //set ishiftrow into corresponding i row value
	                *currentCell = -1; //set initial row to -1 to indicate modification
	                ret = 1; //return 1 if valid
	                break;  //flag so that code does not run in an infinite loop
	            }
	        } 
        }
    }
}
    return ret;
};
int move_a(game * cur_game) 
{
    int rows = cur_game->rows; //row variable to pointer of number of rows in cur_game board
    int cols = cur_game->cols; //col variable to pointer of number of cols in cur_game board
    int ishiftcols; //loop variable, explained below
    int flag = 0; //flag variable to check status of previously merged column
    int flag2 = 0; //flag variable to prevent infinite loop
    int ret = 0; //return value for d being invalid/valid move (0 = invalid, 1 = valid)
    for(int i = 0; i < rows; i++) //loop through rows
    {
        flag = -1; //set previously merged column to -1, no columns have been merged yet
        for(int j = 0; j < cols; j++) //loop through cols
        {
          cell *currentCell = get_cell(cur_game, i, j); //use helper function to define cell at current row,col
          if(*currentCell != -1) //check if cell is occupied
          {
            for(ishiftcols = 0; ishiftcols < j; ishiftcols++) //loop through rows in the currently accessed column
            {
              cell *nextCell = get_cell(cur_game, i, ishiftcols); //define variable for next cell in the column
              if(*nextCell == -1 && flag2 != 1) //check if unoccupied
              {
                *nextCell = *currentCell; //set next cell to original cell
                *currentCell = -1; //indicate original cell is unoccupied
                ret = 1; //indicate valid change
                flag2++; //increment flag to halt infinite loop
              }
            }
                if((ishiftcols - 1) != flag) //check if shifted columns is not equal to columns that have not been merged yet
                {
                    cell *lastCell = get_cell(cur_game, i, ishiftcols - 1); //set a variable for the last cell in the previous column
                    cell *nextCellCopy = get_cell(cur_game, i, ishiftcols); //redefine variable for next cell since it cannot be accessed in this if statement
                    if(*lastCell == *nextCellCopy) //check if last and next are equal
                    {
                        *lastCell = 2* *nextCellCopy; //if so, set last to 2 times the next cell
                        *nextCellCopy = -1; //set the next cell to indicate it is unoccupied
                        cur_game -> score += *lastCell; //update score
                        flag = ishiftcols - 1; //update unmerged columns 
                        ret = 1; //indicate valid change
                    }
                }
            }
        }
    }

    return ret; //return valid/invalid
};

int move_d(game * cur_game){ 
    int rows = cur_game->rows; //row variable to pointer of number of rows in cur_game board
    int cols = cur_game->cols; //col variable to pointer of number of cols in cur_game board
    int ishiftcols; //loop variable, explained below
    int flag = 0; //flag variable to check status of previously merged column
    int ret = 0; //return value for d being invalid/valid move (0 = invalid, 1 = valid)
    for(int i = 0; i < rows; i++) //loop through rows
    {
        flag = cols; //set currently merged columns to max columns, we are now counting down
        for(int j = (cols - 1); j >= 0; j--) //loop columns in reverse order
        {
          cell *currentCell = get_cell(cur_game, i, j); //set variable for current cell
          if(*currentCell != -1) //check if occupied
          {
            for(ishiftcols = (cols - 1); ishiftcols > j; ishiftcols--) //loop through rows of accessed column in reverse order
            {
              cell *nextCell = get_cell(cur_game, i, ishiftcols); //set variable for next cell
              if(*nextCell == -1) //check if unoccupied
              {
                *nextCell = *currentCell; //copy next cell into current cell
                *currentCell = -1; //set current cell unoccupied
                ret = 1; //set return value 1 for valid change
                break; //break out of infinite loop after 1x
              }
            }
            if((ishiftcols + 1) != flag) //check for merge
            {
              cell *nextNextCell = get_cell(cur_game, i, (ishiftcols + 1)); //set variable for ishiftcols + 1 cell
              cell *nextCellCopy = get_cell(cur_game, i, ishiftcols); //set copy for next cell as it cannot be accessed in the if statement
              if(*nextNextCell == *nextCellCopy) //check if ishiftcols + 1 == ishiftcols
              {
                *nextNextCell = 2* (*nextNextCell); //double cell at pos ishiftcols+1
                *nextCellCopy = -1; //set ishiftcols unnocupied
                cur_game -> score += *nextNextCell; //update game score
                flag = ishiftcols + 1; //update unmerged columns flag
                ret = 1; //set return value to indicate valid change
              }
            }
          }
        }
    }

    return ret; //return valid/invalid
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
Return 1 if there are possible legal moves, 0 if there are none.
 */
{
  //initialize the cell
  cell *nptr = (cell*) malloc(sizeof(cell) * (cur_game->rows * cur_game->cols));
  for(int i =0; i < cur_game->rows;i++){
    for(int j = 0; j < cur_game->cols;j++){
      nptr[i * (cur_game->cols) + j] = *get_cell(cur_game,i,j);
    }

  }
  //create a a test game to test with if statement further down
  game newgame;
  newgame.cols = cur_game->cols;//copy current game's columns into newgame
  newgame.rows = cur_game->rows;//copy current game's rows into newgame
  newgame.score = cur_game->score;//copy current score into newgame
  newgame.cells = nptr; //use the new pointer to put cells into newgame
   //check if you can move in new game
  if(!move_a(&newgame) && !move_d(&newgame) && !move_s(&newgame) && !move_w(&newgame))
    {
      //free nptr in memory
      free(nptr);
      return 0;//return 0 if test fails
    }
 
//free nptr in memory
free(nptr);
 return 1;//return 1 if test succeeds
}
/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}