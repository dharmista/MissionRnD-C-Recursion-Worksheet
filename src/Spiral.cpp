/*
Write a program to generate elements of a matrix in spiral order.
Store the generated elements in single dimensional array and return that array.

Directions for Spiral are : Go Right ,Go Down ,Go Left, Go Up
Ex:

Matrix:
1	2	3
4	5	6
7	8	9

Spiral order:
1	2	3	6	9	8	7	4	5

Given matrix is a two dimensional array(input_array) with dimensions rows, columns.
If rows, columns are invalid then return NULL.
If input_array is NULL then return NULL.

Example Input :
int board[2][3]={
				 {4,6,7},
				 {1,3,8}
				};
spiral(2,2,(int **)board); // Rows followed by columns followed by board

Example Output : Return an array consisting of {4,6,7,8,3,1};

Note : Check the function Parameters ,Its a double pointer .

*/


#include "stdafx.h"
#include<stdlib.h>

/*
===== Direction =====
	 1
2	 x	 -2
	-1
*/

void tracePath(int * sol, int curr_row, int curr_col, int rows, int cols, int round, int ** input_array, int pos, int direction){
	if (direction == -2){
		sol[pos++] = input_array[curr_row][curr_col];
		if (curr_col != cols - round - 1)
			tracePath(sol, curr_row, curr_col + 1, rows, cols, round, input_array, pos, -2);
		else{
			if (curr_row == rows - round - 1)
				return;
			tracePath(sol, curr_row + 1, curr_col, rows, cols, round, input_array, pos, -1);
		}
		return;
	}
	else if (direction == -1){
		sol[pos++] = input_array[curr_row][curr_col];
		if (curr_row != rows - round - 1)
			tracePath(sol, curr_row + 1, curr_col, rows, cols, round, input_array, pos, -1);
		else{
			if (curr_col == round)
				return;
			tracePath(sol, curr_row, curr_col - 1, rows, cols, round, input_array, pos, 2);
		}
		return;
	}
	else if (direction == 1){
		sol[pos++] = input_array[curr_row][curr_col];
		if (curr_row != round + 1)
			tracePath(sol, curr_row - 1, curr_col, rows, cols, round, input_array, pos, 1);
		else{
			if (curr_col == cols - round - 1)
				return;
			tracePath(sol, curr_row, curr_col + 1, rows, cols, round + 1, input_array, pos, -2);
		}
		return;
	}
	else{
		sol[pos++] = input_array[curr_row][curr_col];
		if (curr_col != round)
			tracePath(sol, curr_row, curr_col - 1, rows, cols, round, input_array, pos, 2);
		else{
			if (curr_row == round)
				return;
			tracePath(sol, curr_row - 1, curr_col, rows, cols, round, input_array, pos, 1);
		}
		return;
	}
}

int *spiral(int rows, int columns, int **input_array)
{
	if (input_array == NULL || rows <= 0 || columns <= 0)
		return NULL;
	int * sol = (int *)malloc(sizeof(int)*rows*columns);
	tracePath(sol, 0, 0, rows, columns, 0, input_array, 0, -2);
	return sol;
}
