/*
There is a general and he has N Snipers in his control . He has a battefield of NxN Blocks .
He now has to place all N snipers in the battle field such that he can have control of all Blocks,
ie each block should atleast have One sniper having control on it .

A Sniper has control of all blocks in line in all 4 directions . and also all blocks in all 4 diagonals
from his position .

Example :

. C C C
C C S C
. C C C
C . C .

In the above field if Sniper S is placed at (1,2) He has control of all blocks denoted by C .
But their is a problem for the General. All his snipers dont like each other So if any sees any
other sniper in his field of view (Control Blocks) ,he will instantly kill the other sniper .So
Your task is to help the general to place all his N Snipers on NxN field such that ,No sniper can
kill other sniper,but still have control of all the Blocks .

Input : A NxN board , which is all 0's , and N (number of snipers )
Output : Return 1 if its General can place all N snipers or else return 0 .
		 Also modify the battlefield ,such that Blocks which have sniper placed are denoted by 1
		 and all other blocks as 0.

		 Note : If there are multiple correct arrangements ,Arrange in any 1 of the possible ways.
Example Input :
int battle_field[4][4]={0};
solve_nsnipers(&battle_field[0][0],4);

Example Output :
Returns 1 , and modifies battle_field as follows .
0 1 0 0
0 0 0 1
1 0 0 0
0 0 1 0


Read :How to access elements in 2D array when its first element address is passed : http://www.geeksforgeeks.org/pass-2d-array-parameter-c/

P.S: The Above Problem is just a modified version of a popular BackTracking problem .
*/

#include "stdafx.h"
bool checkSurroundings(int * battlefiled, int x, int y, int n){
	//Check horizantal line...
	for (int i = 0; i < n; i++){
		if (*((battlefiled + x*n) + i) == 1)
			return false;
	}
	//Check vertical ones...
	for (int i = 0; i < x; i++){
		if (*((battlefiled + i*n) + y) == 1)
			return false;
	}
	//Check ^\ cross (<-)
	int tx = x, ty = y;
	while (tx != -1 && ty != -1){
		if (*((battlefiled + tx*n) + ty) == 1)
			return false;
		tx--; ty--;
	}tx = x, ty = y;
	//check /^ cross (->)
	while (tx != -1 && ty != n){
		if (*((battlefiled + tx*n) + ty) == 1)
			return false;
		tx--; ty++;
	}
	return true;
}

bool tracePath(int * battlefield, int n, int x, int y, bool * compl){
	if (x == n || y == n)
		return false;
	else{
		if (checkSurroundings(battlefield, x, y, n)){
			*((battlefield + x*n) + y) = 1;
			if (x == n - 1)
			{
				*compl = true;
				return true;
			}
			bool res = tracePath(battlefield, n, x + 1, 0, compl);
			if (res)
				return true;
			else{
				*((battlefield + x*n) + y) = 0;
				tracePath(battlefield, n, x, y + 1, compl);
			}
		}
		else{
			bool res = tracePath(battlefield, n, x, y + 1, compl);
			if (res && !compl){
				*((battlefield + x*n) + y) = 1;
				return tracePath(battlefield, n, x + 1, 0, compl);
			}
			else{
				if (!(*compl)){
					*((battlefield + x*n) + y) = 0;
					return false;
				}
			}
			return true;
		}
	}
}


int solve_nsnipers(int *battlefield, int n){
	if (n == 2 || n == 3 || n <= 0 || battlefield == NULL)
		return 0;
	bool compl = false;
	bool ans = tracePath(battlefield, n, 0, 0, &compl);
	return ans ? 1 : 0;
}