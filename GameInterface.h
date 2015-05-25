/*
GameInterface.h
Contains the UI Operations for Minesweeper

Eurolfan, Jan Ellis D. 10-29160
Tecson, Christan Dan P. 10-53508
CMSC 125 ST-2L AY 14-15
*/

// Since the enum from dexsdk.h doesn't come out as expected, the int values are needed. Lifted from lights.c by Ibay, JP (07-67611) and De La Vina, A. (07-67724)
#define WHITE 63
#define GRAY 56
#define YELLOW 54

// controls
#define up_key 'w'
#define down_key 's'
#define left_key 'a'
#define right_key 'd'
#define flip_key 'o'
#define reset_key 'r'

// function prototypes
void show_board ();
void show_main ();
void erase ();
void print_board (int **board, int board_x, int board_y);
void print_tile (int x, int y, int **board, int board_x, int board_y);
void print_inner_tile (int x, int y, int **board, int board_x, int board_y);
void select_tile (int x, int y);
void reset ();
void flip (int x, int y, int value);
void move_on_board (char keypress, int value, int **board, int board_x, int board_y);
void number_box ();

// global variables
int new_x, new_y, old_x = 100, old_y = 0, limit_left = 100, limit_upper = 0, limit_lower = 154, limit_right = 275;

// shows the whole playing field
void show_board ()
{
	// show commands
	write_text ("Up - W", 5, 37, WHITE, 0);
	write_text ("Down - S", 5, 47, WHITE, 0);
	write_text ("Left - A", 5, 57, WHITE, 0);
	write_text ("Right - D", 5, 67, WHITE, 0);
	write_text ("Reset - R", 5, 77, WHITE, 0);
	write_text ("Exit - X", 5, 87, WHITE, 0);
	write_text ("Flip - O", 5, 107, WHITE, 0);

}

// opens a tile.
void flip (int x, int y, int value)
{
	int i, j;

	if (value)
	{
		for (i = x+2; i <= (x+18); i++)
			for (j = 12+y; j <= (y+23); j++)
				write_pixel (i, j, RED);	
	}
	else
	{
		for (i = x+2; i <= (x+18); i++)
			for (j = 12+y; j <= (y+23); j++)
				write_pixel (i, j, YELLOW);	
	}
}

// colors currently selected tile
void select_tile (int x, int y)
{
	int i, j;
	for (i = x+2; i <= (x+18); i++)
		for (j = 12+y; j <= (y+23); j++)
			write_pixel (i, j, LIGHTRED);
}

// colors the inner part of the tile
void print_inner_tile (int x, int y)
{
	int i, j;
	// inner tile
	for (i = x+2; i <= (x+18); i++)
		for (j = 12+y; j <= (y+23); j++)
			write_pixel (i, j, LIGHTCYAN);
}

// prints an array of 8x8 tiles
void print_tile (int x, int y\)
{
	int i, j;

	// base tile
	for (i = x; i <= (x+20); i++)
		for (j = 10+y; j <= (y+25); j++)
			write_pixel (i, j, WHITE);

	print_inner_tile (x, y);
}

// prints the board along with the background
void print_board ()
{
	int i, j, a;

	// set background
	for (i = 0; i < 320; i++) 
		for (j = 0; j < 200; j++) 
			write_pixel (i, j, LIGHTGREEN);

	// prints the 8x8 matrix
	for (i = 100; i <= 275; i += 25)
		for (j = 0; j < 176; j += 22)
			print_tile (i, j);

	// set 1st tile as selected	
	select_tile (old_x, old_y);
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
		for (j = 1; j <= (401); j++)
			write_pixel (j, i, 100);
}

// shows the current position of the marker
void move_on_board (char keypress, int value, int **board, int board_x, int board_y)
{
	switch (keypress)
	{
		case up_key:
			new_y = old_y - 22;

			if (new_y < limit_upper)
			{
				select_tile (old_x, limit_upper);
			}
			else
			{
				print_inner_tile (old_x, old_y);
				select_tile (old_x, new_y);
				old_y = new_y;
			}

		break;

		case down_key:
			new_y = old_y + 22;

			if (new_y > limit_lower)
			{
				select_tile (old_x, limit_lower);
			}
			else
			{
				print_inner_tile (old_x, old_y);
				select_tile (old_x, new_y);
				old_y = new_y;
			}

		break;

		case left_key:
			new_x = old_x - 25;

			if (new_x < limit_left)
			{
				select_tile (limit_left, old_y);
			}
			else
			{
				print_inner_tile (old_x, old_y);
				select_tile (new_x, old_y);
				old_x = new_x;
			}
		break;

		case right_key:
			new_x = old_x + 25;

			if (new_x > limit_right)
			{
				select_tile (limit_right, old_y);
			}
			else
			{
				print_inner_tile (old_x, old_y);
				select_tile (new_x, old_y);
				old_x = new_x;
			}
		break;

		case flip_key:
			
		break;

		case reset_key:

		break;
	}
}