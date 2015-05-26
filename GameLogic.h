/*
GameLogic.h
contains the logic of the minesweeper game

Eurolfan, Jan Ellis D. 10-29160
Tecson, Christan Dan P. 10-53508
CMSC 125 ST-2L AY 14-15
*/

// boolean constants
#define TRUE 1
#define FALSE 0

#define ROWS 8
#define COLS 8

// global variables
int i, j;

/*
for visible array:
0 - invisible
1 - visible
2 - marked with flag
*/

// function prototypes
void click(int x, int y, int **board, int **visible);
void uncover (int x, int y, int **board, int **visible);
int checkWon(int **board, int **visible);

void new_game (int **board, int *mine_count);
void init_visible (int **visible);
void mark_flag(int x, int y, int **visible);
void mini_flip (int x, int y, int **visible);

void init_visible (int **visible)
{
	int i, j;

	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLS; j++)
			visible[i][j] = 0;
}

void new_game (int **board, int *mine_count)
{
	int i, j;
	//set board values to FALSE
	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLS; j++)
			board[i][j] = FALSE;
	
	// seed rand
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

// marks an area with a flag. works for invisible units only
void mark_flag(int x, int y, int **visible)
{
	if(visible[x][y] == 0)
		visible[x][y] = 2;
	if(visible[x][y] == 2)
		visible[x][y] = 0;
}

// similar to flip in GameInterface
void click(int x, int y, int **board, int **visible)
{
	if(board[x][y])
	{
		//insert game over code here
		return;
	}
	else
	{
		visible[i][j] = 1;
	}
	//uncover(x, y, board, visible);
}

// reveals the content of selected tile
void uncover(int x, int y, int **board, int **visible){
	if(board[x][y])
	{
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

// winning condition
int checkWon(int **board, int **visible)
{
	int i, j;
	for(i = 0; i < 8; i++)
	{
		for(j = 0; j < 8; j++)
		{
			if(visible[i][j] == 0 && !board[i][j])
				return FALSE;
		}
	}
	return TRUE;
}