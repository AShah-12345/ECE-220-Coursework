//partners: devdp2, loganeh2
//Aryan Shah
//ECE 220, FA22

/*The purpose of this code is to implement the necessary functions to create
a game similar to that of the Game of Life, by John Horton Conway. The function 
countLiveNeighbor iterates through each cell to test for neighbors and changes the 
board accordingly. Next, the function updateBoard sets a copy of the passed board,
and makes use of conditionals and for loops to check whether
the current cell is alive or dead. Finally, the aliveStable
function also creates a copy of the passed board, calls the
function updateBoard, and checks whether there are any differences
so the program can tell if the alive cells change for the next step.
*/

/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
int i;
int j;
int top = 0;
int bot = 0;
int right  = 0;
int left = 0;
int notCor = 0;
int LiveN = 0;
     if(row == boardRowSize-1) //test for neighbors and to revive different layers of cells
    {
        bot = 1;
        notCor = 1;
    }
     if(row == 0)
    {
      top = 1;
        notCor = 1;
    }
     if(col == boardColSize-1)
     {
      right = 1;
        notCor = 1;
     }
     if(col == 0)
     {
       left = 1;
        notCor = 1;
      }
  if(notCor == 0) //not corner
  {
    for (i = -1; i<2; i++) // runs tests for corners
    {
      for (j = -1; j <2; j++)
      {
        if (j ==0 && i == 0)
        {
          continue;
        }
        else
          {
            if (board[(row + i)*boardColSize + (col + j)] == 1)
            {
            LiveN++;
            }
          }
       
       }
    }
   }
  if(left == 1 && top == 0 && bot == 0) //left column
  {
    for (i = -1; i<2; i++)
    {
      for (j = 0; j <2; j++)
      {
        if (j ==0 && i == 0)
        {
          continue;
        }
        else
        {
          if (board[(row + i)*boardColSize + (col + j)] == 1)
          {
            LiveN++;
          }
        }
      }
    }
  }
  if(right == 1 && top == 0 && bot == 0) //right column
  {
    for (i = -1; i<2; i++)
    {
      for (j = -1; j <1; j++)
      {
        if (j ==0 && i == 0)
        {
          continue;
        }
        else
        {
          if (board[(row + i)*boardColSize + (col + j)] == 1)
          {
            LiveN++;
          }
        }
      }
    }
  }
  if(top == 1 && left != 1 && right != 1) //top row
  {
    for (i = 0; i<2; i++)
    {
      for (j = -1; j <2; j++)
      {
        if (j ==0 && i == 0)
        {
          continue;
        }
        else
        {
          if (board[(row + i)*boardColSize + (col + j)] == 1)
          {
            LiveN++;
          }
        }
      }
    }
  }
  if(bot == 1 && left != 1 && right != 1) //bottom row
  {
    for (i = -1; i<1; i++)
    {
      for (j = -1; j <2; j++)
      {
        if (j ==0 && i == 0)
        {
          continue;
        }
        else
        {
          if (board[(row + i)*boardColSize + (col + j)] == 1)
          {
            LiveN++;
          }
        }
      }
    }
  }
  if(top == 1 && left == 1) //top left corner
  {
   
    for (i = 0; i<2; i++) //row
    {
      for (j = 0; j <2; j++) //column
      {
        if (j ==0 && i == 0)
        {
          continue;
        }
        else
        {
          if (board[(row + i)*boardColSize + (col + j)] == 1)
          {
            LiveN++;
          }
        }
      }
    }
  }
   if(top == 1 && left != 1 &&right == 1) //top right corner
  {
    for (i = 0; i<2; i++) //row
    {
      for (j = -1; j <1; j++) //column
      {
        if (j ==0 && i == 0)
        {
          continue;
        }
        else
        {
          if (board[(row + i)*boardColSize + (col + j)] == 1)
          {
            LiveN++;
          }
        }
      }
    }
  }
  if(bot == 1 && top != 1 && left == 1) //bottom left corner
  {
    for (i = -1; i<1; i++) //row
    {
      for (j = 0; j <2; j++) //column
      {
        if (j ==0 && i == 0)
        {
          continue;
        }
        else
        {
          if (board[(row + i)*boardColSize + (col + j)] == 1)
          {
            LiveN++;
          }
        }
      }
    }
  }
 
  if(bot == 1 && top != 1 && left !=1 && right == 1) //bottom right corner
  {
    for (i = -1; i<1; i++) //row
    {
      for (j = -1; j <1; j++) //column
      {
        if (j ==0 && i == 0)
        {
          continue;
        }
        else
        {
          if (board[(row + i)*boardColSize + (col + j)] == 1)
          {
            LiveN++;
          }
        }
      }
    }
  }
  return LiveN;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
    int numcells;//live cell counter
    int totalsize = boardRowSize * boardColSize; //make copy
    int boardcopy[totalsize]; //define array of copy
    for(int i = 0; i < boardRowSize; i++){
        for(int j=0; j < boardColSize; j++){
            numcells=countLiveNeighbor(board,boardRowSize,boardColSize,i,j);
            if(board[i*boardColSize+j]==1){ //check if alive
                
                if(numcells==2||numcells==3){
                    boardcopy[i*boardColSize+j]=1;//set copy case to new val
                    //this way it doesn't affect the original board
                }
                else{
                    boardcopy[i*boardColSize+j]=0;
                }
            }
            else if(board[i*boardColSize+j]==0){ //check dead
                if(numcells==3){
                    boardcopy[i*boardColSize+j]=1;  
                }
                else{
                    boardcopy[i*boardColSize+j]=0;
                }
            }
        }
    }
    for(int k =0; k< totalsize; k++){
        board[k] = boardcopy[k]; //transfer to original
    }
}
/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
    int boardSize = boardRowSize * boardColSize; //N*M elements for total size
    int boardCopy[boardSize]; //initialize copy for board with its size
    int return_status; //initialize variable for output status
    int i, j; //initialize variables for loop
    for(i = 0; i < boardRowSize; i++) //loop through rows
    {
        for(j = 0; j < boardColSize; j++) //loop through columns
        {
            boardCopy[i * boardColSize + j] = board[i * boardColSize + j]; //set each element of board to its copy
        }
    }
    updateBoard(boardCopy,boardRowSize,boardColSize); //update original board to check for next step
    int k; //iniitalize loop variable
    for(k = 0; k < boardSize; k++){ //loop through entire board
        if(boardCopy[k] == board[k]) //check each index of each board to see if they are the same
            {
                return_status=1; //if they are same, set and keep status to 1
            }
        else
            {
                return_status=0; //if any difference, change status to 0
                return return_status; //if any difference, we can just return 0 and end
            }
    }
    return return_status; //return 1 if doesn't reach the else case
}