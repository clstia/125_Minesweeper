#include <stdio.h>
#include <stdlib.h>

#define ROWS 8
#define COLS 8
#define TRUE 1
#define FALSE 0

#define up_key 'w'
#define down_key 's'
#define left_key 'a'
#define right_key 'd'
#define flip_key 'o'

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

void printArray (int **board)
{
	int i, j;
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			printf("%d\t", board[i][j]);
		}
		printf("\n");
	}
}

void init_visible (int **visible)
{
	int i, j;

	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLS; j++)
			visible[i][j] = 0;
}

void flip (int **visible, int **board, int x, int y)
{
	if (visible[x][y] == 0 && board[x][y] != 1)
	{
		visible[x][y] = 1;
	}
}

void new_game (int **board, int *mine_count)
{
	int i, j;
	time_t t;
	//set board values to FALSE
	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLS; j++)
			board[i][j] = FALSE;

	srand (time(NULL));
	//fill board with mines
	*mine_count = rand() % 30 + 10;
	
	for(i = 0; i < *mine_count; i++)
	{
		int x = rand() % 8;
		int y = rand() % 8;
		
		//while there is a mine in random number generated, change x and y
		while(board[x][y] == TRUE)
		{
			x = rand() % 8;
			y = rand() % 8;
		}
		
		board[x][y] = TRUE;
	}
}

int main ()
{
	int mine_count = 0, i, j;
	int **board, **visible, board_x = 0, board_y = 0, value = 0;
	char keypress;

	board = (int**) malloc (sizeof(int*)*ROWS);
	visible = (int**) malloc (sizeof(int*)*ROWS);
	
	for (i = 0; i < ROWS; i++)
	{
		board[i] = (int*) malloc (sizeof(int)*COLS);
		visible[i] = (int*) malloc (sizeof(int)*COLS);
	}
	
	new_game (board, &mine_count);
	while (keypress != 'q')
	{
		printf ("minefield, mine_count %d\n", mine_count);
		printArray (board);
	
		printf ("visible\n");
		printArray (visible);

		printf ("\nEnter move: ");
		scanf (" %c", &keypress);

		if (keypress == flip_key)
		{
			flip (visible, board, board_x, board_y);
		}

		move_on_array (keypress, board, &board_x, &board_y, &value);
	}

	for (i = 0; i < ROWS; i++)
	{
		free (board[i]);
		free (visible[i]);
	}

	free (visible);
	free (board);
	
	return 0;
}