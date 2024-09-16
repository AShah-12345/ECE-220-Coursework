//partners: devdp2, loganeh2
//Aryan Shah
//ECE 220, FA22

/*The purpose of this program is to implement functions for a  given sudoku solver program. 
Functions to check whether the board was full, there is an empty spot on the board, if a 
target value is in a given row/column, if a value is given within a 3x3 perimeter, if a 
value is valid to be filled in, solve the sudoku instance, and parse and print the sudoku 
board. The functions primarily utilized conditionals and for loops for its intended purpose. 
However, as described in the pseudocode from the course wiki, recursion logic was also used to 
implement the solve_sudoku function.*/

#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.
int is_board_full(const int sudoku[9][9]){ //function to check if board is full
  for(int i=0; i<9; i++){ 
    for(int j=0;j<9;j++){ 
      if(sudoku[i][j]==0){ //if each row,col is 0
        return 0;
      }
    }
  }
  return 1;
}

int find_empty_spot(const int sudoku[9][9], int *i_loc, int *j_loc){ //use ref to modify val directly
//effectively returns 2 vars without 2 functions
  for(int i=0; i<9; i++){
    for(int j=0;j<9;j++){
      if(sudoku[i][j]==0){ //loop through board, check for first empty spot
        *i_loc=i; //set row pointer accordingly
        *j_loc=j; //set col pointer accordingly
        return 1; //stops repeated loops
      }
    }
  }
  return 0;
}
// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);
  for(int a=0;a<9;a++){
    if(sudoku[i][a]==val){ //check if target value is at index
      return 1;
    }
  }
  // BEG TODO
  
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);
  for(int a=0;a<9;a++){
    if(sudoku[a][j]==val){ //check for target value at index
      return 1;
    }
  }
  // BEG TODO
  
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
  assert(i>=0 && i<9);
  int c = i/3; //determines row section (either 0,1,2)
  int d = j/3; //determins col section (either 0,1,2)
  for(int a=c*3; a< ((3*c)+3);a++){ //jump back to section +3 row
    for(int b=d*3; b< ((3*d)+3);b++){ //jump back to section +3 col
      if(sudoku[a][b]==val){
        return 1;
      }
    }
  }  
  return 0;
  // END TODO
  
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);
  if(is_val_in_col(val,j,sudoku)==1){
    return 0;
  }
  else if(is_val_in_row(val,i,sudoku)==1){
    return 0;
  }
  else if(is_val_in_3x3_zone(val,i,j,sudoku)==1){
    return 0;
  }
  else{// BEG TODO
  return 1;
  }
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int row_fin = 0;
  int col_fin=0;
  if(is_board_full(sudoku)==1){
    return 1;
  }
  else{
    int o = find_empty_spot(sudoku,&row_fin,&col_fin); //dummy var
    //printf("%i",i);
    //printf("%i , ",j);
    //printf("\n");
    for(int num=1;num<=9;num++){
      if(is_val_valid(num,row_fin,col_fin,sudoku)==1 && sudoku[row_fin][col_fin]==0){
        sudoku[row_fin][col_fin]=num;
        if(solve_sudoku(sudoku)==1){
          return 1;
        }
        sudoku[row_fin][col_fin]=0;
      }
    }
  }
  
  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}