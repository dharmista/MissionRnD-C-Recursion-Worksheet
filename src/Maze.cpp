/*
Find if there is a connecting path between two given points in the maze.
The maze is a matrix of order MxN, check if there exists a path between (x1,y1) and (x2,y2).
Two points are said to connected if there is a series of 1's non-diagonally.
Example:
Maze of order 4x4:

1	0	1	0
1	1	0	0
0	1	0	1
0	1	1	1

(x1,y1):(0,0)
(x2,y2):(2,3)

In this case, there exists a connected path:
1
1	1
	1		1
	1	1	1

Since there is a connected path, your function has to return 1.
If a path doesn't exist between two co-ordinates then return 0.
If the co-ordinates are invalid or size of the matrix is invalid then return 0.

Function Prototype :path_exists(int *maze, int rows, int columns, int x1, int y1, int x2, int y2) ;
Maze: Pointer to first element of an array .
rows : No of rows
columns : Columns
x1,x2,y1,y2: Co-ordinates

Hint : You can use path_exists as a wrapper function for your original recursive function which might take
more parameters .
*/

#include<stdlib.h>

/*
Prev positions :
	 1
2	 x   -2
	-1

-1 for initial conditions
*/

int pos(int x, int y, int rows, int cols){
	//Returning the index based on row and coolumn number
	return ((x)*(cols)+y + 1) - 1;
}

bool findPath(int * maze, int rows, int cols, int prev_pos, int cur_r, int cur_c, int targ_r, int targ_f, bool * found){
	if (cur_r == -1 || cur_c == -1 || cur_r == rows || cur_c == cols)
		return false;
	else if (cur_r == targ_r && cur_c == targ_f)
	{
		*found = true;
		return true;
	}
	else{
		//Should move in opposite direction from its previous one, since there may be occurence of infinate loop.
		if (cur_r != 0 && prev_pos != -1 && maze[pos(cur_r - 1, cur_c, rows, cols)] == 1 && findPath(maze, rows, cols, 1, cur_r - 1, cur_c, targ_r, targ_f, found))
			return true;
		else if (cur_c != cols && prev_pos != 2 && maze[pos(cur_r, cur_c + 1, rows, cols)] == 1 && findPath(maze, rows, cols, -2, cur_r, cur_c + 1, targ_r, targ_f, found))
			return true;
		else if (cur_r != rows && prev_pos != 1 && maze[pos(cur_r + 1, cur_c, rows, cols)] == 1 && findPath(maze, rows, cols, -1, cur_r + 1, cur_c, targ_r, targ_f, found))
			return true;
		else if (cur_c != 0 && prev_pos != -2 && maze[pos(cur_r, cur_c - 1, rows, cols)] == 1 && findPath(maze, rows, cols, 2, cur_r, cur_c - 1, targ_r, targ_f, found))
			return true;
	}
	return false;
}

int path_exists(int *maze, int rows, int columns, int x1, int y1, int x2, int y2)
{
	bool found = false;
	findPath(maze, rows, columns, -1, x1, y1, x2, y2, &found);
	return found == false ? 0 : 1;
}