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

// function prototypes
void move_on_board (char keypress, int value);
void move_on_array (char keypress);

// global variables
int board[8][8], visible[8][8], adjacents[8][8];
int board_x = 0, board_y = 0, value;

int main ()
{
	char keypress = start, game_continue = still_continue, movement;
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
			show_board (); // show main board
			//newGame (&board, &adjacents);
			do
			{
				game_continue = (char) getch (); // get input
				move_on_array (game_continue);
				move_on_board (game_continue, value);
			}
			while (game_continue != quit_key);
		}
	}
	while (keypress != quit);

	set_graphics (VGA_TEXT80X25X16); // text mode
	clrscr (); // clear screen
	return 0;
}

// get value at board[x][y]
void move_on_array (char keypress)
{
	switch (keypress)
	{
		case up_key:
			if (--board_x >= 0)
			{
				board_x--;
			}
		break;

		case down_key:
			if (++board_x <= 8)
			{
				board_x++;
			}

		break;

		case left_key:
			if (--board_y >= 0)
			{
				board_y--;
			}

		break;

		case right_key:
			if (++board_y <= 8)
			{
				board_y++;
			}
		break;

	}

	value = board[board_x][board_y];
}