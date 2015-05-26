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

#define flip_key 'o'
#define reset_key 'r'
#define exit_key 'x'

#define ROWS 8
#define COLS 8

// function prototypes
void move_on_array (char keypress, int **board, int *board_x, int *board_y, int *board_value);
void init_visible (int **visible);

int main ()
{
	char keypress = start, game_continue = still_continue, movement;
	int board_x = 0, board_y = 0, board_value = 0, mine_count = 0, i;
	int **board, **visible;

	//initialize arrays
	board = (int**) malloc (sizeof(int*)*ROWS);
	visible = (int**) malloc (sizeof(int*)*ROWS);

	for (i = 0; i < ROWS; i++)
	{
		board[i] = (int*) malloc (sizeof(int)*COLS);
		visible[i] = (int*) malloc (sizeof(int)*COLS);
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
			new_game (board, &mine_count); // initialize board array
			init_visible (visible);
			print_board (board, board_x, board_y);
			show_board (); // show main board
			moving_on_board (100, 0, visible, board_x, board_y);
			
			do
			{
				game_continue = (char) getch (); // get input
				move_on_array (game_continue, board, &board_x, &board_y, &board_value); // reflect changes on array
				
				if (game_continue == flip_key)
				{
					click (board_x, board_y, board, visible);
				}

				move_on_board (game_continue, board_value, visible, board_x, board_y);

				// reset
				if (game_continue == reset_key)
				{
					new_game (board, &mine_count);
					init_visible (visible);
					print_board (board, board_x, board_y);
					show_board ();
				}
			}while (game_continue != exit_key);
		}
	}
	while (keypress != quit);

	// free
	for (i = 0; i < ROWS; i++)
	{
		board[i];
		visible[i];
	}

	free (board);
	free (visible);

	set_graphics (VGA_TEXT80X25X16); // text mode
	clrscr (); // clear screen

	return 0;
}

// get board_value at board[x][y]
void move_on_array (char keypress, int **board, int *board_x, int *board_y, int *board_value)
{
	switch (keypress)
	{
		case up_key:
			if (*board_x > 0)
			{
				*board_value = board[--*board_x][*board_y];
			}
		break;

		case down_key:
			if (*board_x < 7)
			{
				*board_value = board[++*board_x][*board_y];
			}
		break;

		case left_key:
			if (*board_y > 0)
			{
				*board_value = board[*board_x][--*board_y];
			}
		break;

		case right_key:
			if (*board_y < 7)
			{
				*board_value = board[*board_x][++*board_y];
			}
		break;
	}
}