/*
gameOperations.h
contains basic game ui operations for mnspwr.c

Eurolfan, Jan Ellis D. 10-29160
Tecson, Christan Dan P. 10-53508
CMSC 125 ST-2L AY 14-15

Coded mainly by Eurolfan
*/

#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"

// colors
#define WHITE 63
#define GRAY 56
#define YELLOW 54

// controls
#define up_key 'w'
#define down_key 's'
#define left_key 'a'
#define right_key 'd'
#define flip_key 'o'

// function prototypes
void show_board ();
void show_main ();
void erase ();
void print_board ();

// controls
void keypress_up ();
void keypress_down ();
void keypress_left ();
void keypress_right ();
void keypress_reset ();
void keypress_flip ();

// global variables
int new_x, new_y, old_x, old_y;

// shows the whole playing field
void show_board ()
{
	int i, j, a;

	// show initial board
	print_board ();

	// show commands
	write_text ("Up - W", 5, 37, WHITE, 0);
	write_text ("Down - S", 5, 47, WHITE, 0);
	write_text ("Left - A", 5, 57, WHITE, 0);
	write_text ("Right - D", 5, 67, WHITE, 0);
	write_text ("Reset - R", 5, 77, WHITE, 0);
	write_text ("Exit - X", 5, 87, WHITE, 0);
	write_text ("Flip - O", 5, 107, WHITE, 0);
}

/*
working colors from dexsdk
LIGHTBLUE
BLUE
GREEN
CYAN
RED
MAGENTA
LIGHTGRAY
LIGHTGREEN
LIGHTCYAN / BRIGHT NA BLUE
LIGHTRED / MAROON
LIGHTMAGENTA / BRIGHTPURPLE
BROWN / LIGHT NA BROWN
YELLOW / USE LIGHTS.C YELLOW
WHITE / USE LIGHTS.C WHITE
*/

void print_tile (int x, int y)
{
	int i, j;

	for (i = x; i <= (x+20); i++)
		for (j = 10+y; j <= (y+25); j++)
			write_pixel (i, j, WHITE);
}

void print_board ()
{
	int i, j, a;

	// set background
	for (i = 0; i < 320; i++) 
		for (j = 0; j < 200; j++) 
			write_pixel (i, j, LIGHTGREEN);

	// alternate print
	for (i = 100; i <= 275; i += 25)
		for (j = 0; j < 176; j += 22)
			print_tile (i, j);
	// initial print
	/*	
	// print the tiles of the game
	for (a = 0; a < 160; a += 20)
	{
		if (a > 0)
		{
			a += 2;
		}

		for (i = 100; i <= 120; i++) for (j = 10 + a; j <= 25 + a; j++) write_pixel (i, j, WHITE);		
		for (i = 125; i <= 145; i++) for (j = 10 + a; j <= 25 + a; j++) write_pixel (i, j, WHITE);
		for (i = 150; i <= 170; i++) for (j = 10 + a; j <= 25 + a; j++) write_pixel (i, j, WHITE);
		for (i = 175; i <= 195; i++) for (j = 10 + a; j <= 25 + a; j++) write_pixel (i, j, WHITE);
		for (i = 200; i <= 220; i++) for (j = 10 + a; j <= 25 + a; j++) write_pixel (i, j, WHITE);
		for (i = 225; i <= 245; i++) for (j = 10 + a; j <= 25 + a; j++) write_pixel (i, j, WHITE);
		for (i = 250; i <= 270; i++) for (j = 10 + a; j <= 25 + a; j++) write_pixel (i, j, WHITE);
		for (i = 275; i <= 295; i++) for (j = 10 + a; j <= 25 + a; j++) write_pixel (i, j, WHITE);
	}*/
}

// shows the main menu
void show_main ()
{
	erase ();
	write_text ("MINESWEEPER", 100, 40, WHITE, 1);
	write_text ("1 - START", 40, 120, WHITE, 1);
	write_text ("2 - QUIT", 210, 120, WHITE, 1);
}

// fills the area with a black rectangle. lifted from lights.c by Ibay, JP (07-67611) and De La Vina, A. (07-67724)
void erase ()
{
	int i, j;

	for (i = 1; i <= (221); i++)
	{
		for (j = 1; j <= (401); j++)
		{
			write_pixel (j, i, 100);
		}
	}
}