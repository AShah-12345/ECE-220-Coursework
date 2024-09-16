//partners: devdp2, loganeh2
//Aryan Shah
//ECE 220, FA22

/*The purpose of this code is to execute Pascal's Triangle.
The first loop executes the row and the second loop cycles 
through the elements in the row, which links up with the
modified combination function to allow easy computation
without worrying about integer multiplication and division.*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int row; //define the row

  printf("Enter a row index: "); //ask for input
  scanf("%d", &row); //scan input
  unsigned long output = 1; //define output variable
  int i, j; //define loop variables
  for(i = 0 ; i <= row; i++) //loop through rows
    {
      for(j = 1; j <= (row - i); j++) //loop through elements in the row
	{
	  output = output * (row + 1 - j);
	  output = output / j; //perform Pascal's triangle computation
	}
      printf("%lu ", output); //print output
      output = 1;
    }
  printf("\n"); //print newline 
  return 0; //return statement
}
