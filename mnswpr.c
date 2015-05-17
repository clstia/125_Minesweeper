/*
mnswpr.c - main file
Minesweeper - A basic implementation of the traditional minesweeper game for ICS-OS.

Eurolfan, Jan Ellis D. 10-29160
Tecson, Christan Dan P. 10-53508
CMSC 125 ST-2L AY 14-15
*/


// includes
#include "../../sdk/dexsdk.h"
#include "gameOperations.h"
//#include "GameLogic.h"

// constants
#define start '1'
#define quit '2'
#define still_continue '3'

#define reset_key 'r'
#define quit_key 'x'

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
			do
			{
				game_continue = (char) getch (); // get input
			}
			while (game_continue != quit_key);
		}
	}
	while (keypress != quit);

	set_graphics (VGA_TEXT80X25X16); // text mode
	clrscr (); // clear screen
	return 0;
}