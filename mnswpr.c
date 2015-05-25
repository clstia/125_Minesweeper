/*
mnswpr.c - main file
Minesweeper - A basic implementation of the traditional minesweeper game for ICS-OS.

Eurolfan, Jan Ellis D. 10-29160
Tecson, Christan Dan P. 10-53508
CMSC 125 ST-2L AY 14-15
*/

// includes
#include "../../sdk/dexsdk.h"
#include "GameInterface.h"
#include "GameLogic.h"

// constants
#define start '1'
#define quit '2'
#define still_continue '3'

#define reset_key 'r'
#define quit_key 'x'

#define ROWS 8
#define COLS 8

// function prototypes
void move_on_array (char keypress, int **board, int *board_x, int *board_y, int *value);

int main ()
{
	char keypress = start, game_continue = still_continue, movement;
	int board_x = 0, board_y = 0, value = 0, mine_count = 0, i;
	int **board;

	//initialize arrays
	board = (int**) malloc (sizeof(int*)*ROWS);

	for (i = 0; i < ROWS; i++)
	{
		board[i] = (int*) malloc (sizeof(int)*COLS);
	}

	set_graphics (VGA_320X200X256); // set screen with 320 x 200 with 256 colors

	// on game start
	do
	{
		show_main (); // show main menu
		keypress = (char) getch (); // get input
		
		// if start
		if (keypress == start)
		{
			erase (); // "clear" screen
			new_game (board, &mine_count);
			print_board (board, board_x, board_y);
			show_board (); // show main board
			do
			{
				game_continue = (char) getch (); // get input
				move_on_array (game_continue, board, &board_x, &board_y, &value); // reflect changes on array
				move_on_board (game_continue, value, board, board_x, board_y);
			}
			while (game_continue != quit_key);
		}
	}
	while (keypress != quit);

	set_graphics (VGA_TEXT80X25X16); // text mode
	clrscr (); // clear screen

	// free
	for (i = 0; i < ROWS; i++)
	{
		board[i];
	}

	free (board);

	return 0;
}

// get value at board[x][y]
void move_on_array (char keypress, int **board, int *board_x, int *board_y, int *value)
{
	switch (keypress)
	{
		case up_key:
			if (*board_x > 0)
			{
				*value = board[--*board_x][*board_y];
			}
		break;

		case down_key:
			if (*board_x < 7)
			{
				*value = board[++*board_x][*board_y];
			}
		break;

		case left_key:
			if (*board_y > 0)
			{
				*value = board[*board_x][--*board_y];
			}
		break;

		case right_key:
			if (*board_y < 7)
			{
				*value = board[*board_x][++*board_y];
			}
		break;
	}
}