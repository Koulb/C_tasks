#include <stdio.h>
#include <stdlib.h>
#define SIZE  8
#define POSSIBLE_TURN 8

int xturn[POSSIBLE_TURN] = {2, 1, -1, -2, -2, -1, 1, 2};
int yturn[POSSIBLE_TURN] = {1, 2, 2, 1, -1, -2, -2, -1};

/* Show desk */
void desk(int grid[SIZE][SIZE]){

	int i, j;

	for(i = 0; i < SIZE; i++){
		for ( j = 0; j < SIZE; j++)
			printf("%d \t", grid[i][j]);
		printf("\n");
	}

}

/* Calculation of possible turns from x, y */
int possibleTurnNumber(int grid[SIZE][SIZE], int x, int y){

	int xnew ,ynew, i = 0, optionTurn = POSSIBLE_TURN; 

	for (i = 0; i < POSSIBLE_TURN; i++){
		xnew = x + xturn[i];
		ynew = y + yturn[i];

		if ((xnew < 0) || (ynew < 0) || (xnew > SIZE - 1) || (ynew > SIZE - 1) || (grid[xnew][ynew] != 0))
			optionTurn--;
	}
	
	return optionTurn;

}

/* Enumeration of all options for solving knight tour problem  */
void knight(int grid[SIZE][SIZE], int x0, int y0 , int turn ){

	int i, xnew, ynew ;

	grid[x0][y0] = turn++;

	if (turn > SIZE * SIZE){
	desk(grid);
	exit(0);
	}

	for(i = 0; i < POSSIBLE_TURN; i++){

		xnew = x0 + xturn[i];
		ynew = y0 + yturn[i];

		if ((xnew < 0) || (ynew < 0) || (xnew > SIZE - 1) || (ynew > SIZE - 1) || (grid[xnew][ynew] != 0))
			continue;

		knight(grid, xnew, ynew, turn);
		grid[xnew][ynew] = 0;
	}

}

/* Solving knight tour problem using  Warnsdorff method  */
int knight_Warnsdorff(int grid[SIZE][SIZE], int x0, int y0 , int turn ){

	int i, xnew, ynew, turnTmp,turnRating=POSSIBLE_TURN, turnIndex = 0 ;

	grid[x0][y0] = turn++;

	if (turn > SIZE * SIZE){
	desk(grid);
	exit(0);
	}

	for(i = 0; i < POSSIBLE_TURN; i++){

		xnew = x0 + xturn[i];
		ynew = y0 + yturn[i];

		if ((xnew < 0) || (ynew < 0) || (xnew > SIZE - 1) || (ynew > SIZE - 1) || (grid[xnew][ynew] != 0))
			continue;

		turnTmp = possibleTurnNumber(grid,xnew,ynew); 

		if (turnTmp <= turnRating){
			turnRating = turnTmp;
			turnIndex = i;
		}	
	}
	if ((turnRating == 0) && (turn != SIZE*SIZE)){
		printf("Warnsdorff gave wrong solution, trying enumeration of all possible options \n");
		return 0;
	}	

	knight_Warnsdorff(grid, x0 + xturn[turnIndex], y0 + yturn[turnIndex], turn);


	return 0;
}


int main(){

	int x0, y0, board[SIZE][SIZE] = {};

	printf("Knight tour problem. Enter initial position (x0, y0 from 1 to 8) of Knight () \n" );
	scanf("%d,%d", &y0, &x0);
	x0 = SIZE - x0  ;
	y0 = y0 - 1 ;
	board[x0][y0] = 1;
	printf("Initial board: \n" );
	printf("__________________________________________________________ \n");
	desk(board);
	board[x0][y0] = 0;
	printf("__________________________________________________________ \n");
	printf("Solved board: \n" );
	knight_Warnsdorff(board,x0,y0,1);
	knight(board,x0,y0,1);

	return 0;
}