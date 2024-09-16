//partners: devdp2, loganeh2
//Aryan Shah
//ECE 220 FA22

/*The purpose of this program is to implement an efficient data structure to store sparse matrices in 1D arrays as opposed to 2D. 
The function load_tuples uses C's fopen and fscanf commands to load in values from an input file, and calls set_tuples accordingly.
The function gv_tuples returns the value of a tuple at a given row, col. Set_tuples makes use of conditional logic to traverse linked lists
and insert a tuple based on the given restrictions in the course wiki. The function save_tuples rewrites the tuples to a given file,
similar to the opposite of load_tuples. Add_tuples traversed the linked list and added matA and matB by defining a matC to hold values
from matA and then calling the gv_tuples function to get its corresponding values and the set_tuples function to fill in the sums
into matC. Lastly, the function destroy_tuples simply calls the free function to destroy all nodes and lists, freeing up the memory.*/

#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>




sp_tuples * load_tuples(char* input_file)
{
    int countRows, countCols; //define vars for dimensions of matrix
    FILE *file = fopen(input_file, "r"); //open file in read-only mode
    sp_tuples *sparseMat = (sp_tuples *) malloc(sizeof(sp_tuples)); //allocate size using malloc and sizeof
    fscanf(file, "%d %d\n", &countRows, &countCols); //scan each row and col based on how its written in the file (with newspace)

    sparseMat->m = countRows; //initialize m as width value of matrix with rows
    sparseMat->n = countCols; //initialize n height value of matrix with cols
    sparseMat->nz = 0; //set nonzero value
    sparseMat->tuples_head = NULL; //set tuples_head to null

    int rows, cols; //set var to read in matrix rows and cols
    double val; //set double variable to represent value at matrix
    int tuple = fscanf(file, "%d %d %lf\n", &rows, &cols, &val); //scan in tuple from file, using respective formatting
    while(tuple != 0 && tuple != EOF) //check to make sure tuple is not invalid
    {
        set_tuples(sparseMat, rows, cols, val); //call set_tuples function
        tuple = fscanf(file, "%d %d %lf\n", &rows, &cols, &val); //continue scanning while there can be more tuples
    }
    
    fclose(file); //close file
    return sparseMat; //return matrix
}


double gv_tuples(sp_tuples * mat_t,int row,int col)
{
    sp_tuples_node* tuple = mat_t->tuples_head; //set a tuple var to tuples_head
    while(tuple != NULL){ //loop through while tuple is not NULL
        if(tuple->row == row && tuple->col == col){ //check if row, col correspond
            return tuple->value; //return val
        }
        else 
        {
            tuple = tuple->next; //go to next value
        }
    }
    return 0;
    

}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    sp_tuples_node *original_tuple = mat_t->tuples_head;
    //FIRST PASS IS TO TEST IF THE ROW AND COLUMN ALREADY EXIST IN THE LINKED LIST
    if(original_tuple==NULL){ //if our head is null, we make a new node to set it as the head
        mat_t->tuples_head= (sp_tuples_node *) malloc(sizeof(sp_tuples_node));
        mat_t->tuples_head->value = value;
        mat_t->tuples_head->row = row;
        mat_t->tuples_head->col = col;
        mat_t->tuples_head->next = NULL;
        original_tuple = mat_t->tuples_head;
    }
    sp_tuples_node *previous_tuple = NULL;

    while(original_tuple!=NULL){
        if(previous_tuple==NULL && original_tuple->row==row && original_tuple->col==col){
            if(previous_tuple==NULL){ //we are at the head
                if(value==0){//delete the head
                    mat_t->tuples_head=mat_t->tuples_head->next; //skip node to delete. Original set to skipped node
                    free(original_tuple); //free original to remove the value
                    mat_t->nz--; //reduce the headcount of non-null nodes
                    return;
                }
                else{
                    original_tuple->value = value; //replace the existing head value with a new value;
                    return;
                }
            }
        }
        else if(original_tuple->row==row && original_tuple->col==col){ //we are not at the head;
                if(value==0){ //delete the node by setting the old pointer to the next one
                    previous_tuple->next = original_tuple->next;
                    free(original_tuple);
                    mat_t->nz--; //reduce the headcount of non-null nodes
                    return;
                }
                original_tuple->value = value; //replace the existing head value with a new value;
                return;
            }
        
        previous_tuple = original_tuple;
        original_tuple = original_tuple->next;


    }
    if(value ==0){
        return; //we've passed through the loop, haven't found it, so don't bother continuing.
    }
    //SECOND PASS IS TO INSERT THE NEW NODE AT THE LINKED LIST
    //we know the head already exists
    //we know the node we have to insert is not already in the sorted list
    sp_tuples_node *newNode = (sp_tuples_node *) malloc(sizeof(sp_tuples_node));
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;

    
    sp_tuples_node *original_tuple_new = mat_t->tuples_head;
    sp_tuples_node *next_tuple_new = original_tuple_new->next;

    while(original_tuple_new != NULL){
        int original_tuple_new_loc = (original_tuple_new->row)*(mat_t->n)+(original_tuple_new->col); //change row-col to int for easier sort
        
        int newNode_loc = (newNode->row)*(mat_t->n)+(newNode->col);
        int head_loc = (mat_t->tuples_head->row)*(mat_t->n)+(mat_t->tuples_head->col);
        if(newNode_loc < head_loc){ //we are inserting at the head of the function
            newNode->next=mat_t->tuples_head;
            mat_t->tuples_head = newNode;
            mat_t->nz++;
            return;
        }
        if(newNode_loc > original_tuple_new_loc && next_tuple_new==NULL){ //we are inserting at the tail of the function
            original_tuple_new->next = newNode;
            newNode->next = NULL;
            mat_t->nz++;
            return;
        }
        int next_tuple_new_loc = (next_tuple_new->row)*(mat_t->n)+(next_tuple_new->col);
        if(newNode_loc > original_tuple_new_loc && newNode_loc<next_tuple_new_loc){ //insert normally
            original_tuple_new->next = newNode;
            newNode->next = next_tuple_new;
            mat_t->nz++;
            return;
        }
        original_tuple_new = next_tuple_new;
        if(next_tuple_new !=NULL){
            next_tuple_new = next_tuple_new->next;
        }

    }
    

}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
    FILE *file = fopen(file_name, "w"); //open file in write-only format
    fprintf(file, "%d %d\n", mat_t->m, mat_t->n); //print number of rows, cols to file in given format
    while(mat_t->tuples_head != NULL) //while tuples_head is not NULL
    {
        fprintf(file, "%d %d %lf\n", mat_t->tuples_head->row, mat_t->tuples_head->col, mat_t->tuples_head->value); //print each row, col, and value to file in given format
        mat_t->tuples_head = mat_t->tuples_head->next; //iterate to next tuple_head
    }
    return;
}

sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){

	if (matA->m == matB->m && matA->n == matB->n) //make sure that inputs are of valid size n1 == m2
    {
	    sp_tuples* matC = (sp_tuples*)malloc(sizeof(sp_tuples)); //allocate size and init matC
	    matC->m = matA->m; //set matC to have mA
	    matC->n = matB->n; //set matC to have nB
        matC->nz = 0; //set nz = 0
        matC->tuples_head = NULL; //set tuples_head to NULL
        double val; //set a temp val value to calculate sum
        sp_tuples_node* matA_ptr = matA->tuples_head; //set pointer for matA
        sp_tuples_node* matB_ptr = matB->tuples_head; //set pointer for matB
        sp_tuples_node** matC_ptr = &(matC->tuples_head); //set double pointer to point to value of matC
        while(matA_ptr != NULL && matA_ptr != 0) //for every nonzero entry in A
        {
            *matC_ptr = matA_ptr; //copy member values of matA to matC
            matC_ptr = &((*matC_ptr)->next); //iterate matrix C to next
            matA_ptr = matA_ptr->next; //iterate matrix A to next
        }
        while(matB_ptr != NULL && matB_ptr != 0) //for every nonzero entry in B
        {
            val = gv_tuples(matC,matB_ptr->row,matB_ptr->col) + matB_ptr->value; //get value of matC at matB's members
            set_tuples(matC,matB_ptr->row,matB_ptr->col, val); //set matC to the sum
            matB_ptr = matB_ptr->next; //iterate matB
        }	  
        return matC;
        }
    else //if invalid inputs
    {
        return NULL;
    }
}

/*
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    return retmat;

}
*/

    
void destroy_tuples(sp_tuples * mat_t){
    free(mat_t); //delete all nodes and lists
    return; //return nothing
}