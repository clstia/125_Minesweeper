/*
GameLogic.h
contains the logic of the minesweeper game

Eurolfan, Jan Ellis D. 10-29160
Tecson, Christan Dan P. 10-53508
CMSC 125 ST-2L AY 14-15

Coded mainly by Tecson
*/

#include "../../sdk/dexsdk.h"

#define TRUE 1
#define FALSE 0

//int board[8][8]
//int adjacents[8][8];
//int visible[8][8]; //0 - invisible, 1 - visible, 2 - has flag
//int minesCount = 0, i = 0, j = 0;

int i, j;

void newGame(int board[8][8], int adjacents[8][8], int minesCount);
void markFlag(int x, int y, int visible[8][8]);
void click(int x, int y, int board[8][8], int visible[8][8]);
void print_textboard ();
void uncover (int x, int y, int board[8][8], int visible[8][8]);
int checkWon(int board[8][8], int visible[8][8]);

void newGame(int board[8][8], int adjacents[8][8], int minesCount){
	
	//fill board with mines
	minesCount = rand()/5000 + 10;
	
	for(i = 0; i < minesCount; i++){
		int x = rand()/4096;
		int y = rand()/4096;
		
		//while there is a mine in random number generated, change x and y
		while(board[x][y] == TRUE){
			x = rand()/4096;
			y = rand()/4096;
		}
		
		board[x][y] = TRUE;
	}
	
	//count adjacent mines for each tile	
	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			//this tile is a mine
			if(board[i][j] == TRUE)
				continue;
			
			//up down
			if(board[i][j+1] && j + 1 < 8){
				adjacents[i][j] += 1;
			}
			if(board[i][j-1] && j - 1 > 0){
				adjacents[i][j] += 1;
			}
			
			//left right
			if(board[i+1][j] && i + 1 < 8){
				adjacents[i][j] += 1;
			}
			if(board[i-1][j] && i - 1 > 0){
				adjacents[i][j] += 1;
			}
			
			//upper left upper right
			if(board[i-1][j+1] && j + 1 < 8 && i - 1 > 0){
				adjacents[i][j] += 1;
			}
			if(board[i+1][j+1] && j + 1 < 8 && i + 1 < 8){
				adjacents[i][j] += 1;
			}
			
			//lower left lower right
			if(board[i-1][j-1] && j - 1 > 8 && i - 1 > 0){
				adjacents[i][j] += 1;
			}
			if(board[i+1][j-1] && j - 1 > 0 && i + 1 < 8){
				adjacents[i][j] += 1;
			}
		}
	}
}

void markFlag(int x, int y, int visible[8][8]){
	if(visible[x][y] == 0)
		visible[x][y] == 2;
	if(visible[x][y] == 2)
		visible[x][y] == 0;
}

void click(int x, int y, int board[8][8], int visible[8][8]){
	if(board[x][y]){
		//insert game over code here
		return;
	}
	uncover(x, y, board, visible);
}

void uncover(int x, int y, int board[8][8], int visible[8][8]){
	if(board[x][y]){
		return;
	}
	visible[x][y] = 1;
	
	//uncover left
	if(x - 1 > 0 && !board[x-1][y])
		uncover(x - 1, y, board, visible);
	//uncover right
	if(x + 1 < 8 && !board[x+1][y])
		uncover(x + 1, y, board, visible);
	//uncover up
	if(y + 1 < 8 && !board[x][y+1])
		uncover(x, y + 1, board, visible);
	//uncover down
	if(y - 1 > 0 && !board[x][y-1])
		uncover(x, y - 1, board, visible);
		
	//uncover lower left
	if(y - 1 > 0 && x - 1 > 0 && !board[x - 1][y-1])
		uncover(x - 1, y - 1, board, visible);
	//uncover lower right
	if(y - 1 > 0 && x + 1 < 8 && !board[x + 1][y-1])
		uncover(x + 1, y - 1, board, visible);
	//uncover upper left
	if(y + 1 < 8 && x - 1 > 0 && !board[x - 1][y+1])
		uncover(x - 1, y + 1, board, visible);
	//uncover upper right
	if(y + 1 < 8 && x + 1 < 8 && !board[x + 1][y+1])
		uncover(x + 1, y + 1, board, visible);
}

int checkWon(int board[8][8], int visible[8][8]){
	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			if(visible[i][j] == 0 && !board[i][j])
				return FALSE;
		}
	}
	return TRUE;
}