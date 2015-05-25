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

void new_game (int **board, int *mine_count)
{
	int i, j;
	time_t t;
	//set board values to FALSE
	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLS; j++)
			board[i][j] = FALSE;
	
	//set adjacents values
	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLS; j++)
			adjacents[i][j] = 0;

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
	int **board, **adjacents;

	board = (int**) malloc (sizeof(int*)*ROWS);
	adjacents = (int**) malloc (sizeof(int*)*ROWS);
	
	for (i = 0; i < ROWS; i++)
	{
		board[i] = (int*) malloc (sizeof(int)*COLS);
		adjacents[i] = (int*) malloc (sizeof(int)*COLS);
	}

	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLS; j++)
			board[i][j] = adjacents[i][j] = 0;
	
	new_game (board, adjacents, &mine_count);

	printf ("minefield, mine_count %d\n", mine_count);

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			printf ("%d\t", board[i][j]);
		}
		printf ("\n");
	}
	
	printf ("adjacents\n");

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			printf ("%d\t", adjacents[i][j]);
		}
		printf ("\n");
	}

	for (i = 0; i < ROWS; i++)
	{
		free (board[i]);
		free (adjacents[i]);
	}

	free (adjacents);
	free (board);
	
	return 0;
}