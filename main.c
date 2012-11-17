/**
*	Tic Tac Toe Game
*	
*
*		@author Inaciane Monteiro, Joaquim Filipe
*/

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define PLAYER_X 'X'
#define PLAYER_O 'O'
#define EMPTY_CHAR ' '
#define WIN 1
#define DRAW 0
#define LOSE -1
#define UNFINISHED 2
#define N 3


void init_board(char board[N][N]);
void print_board(char board[N][N]);

int main()
{

	char board[N][N];
	char choice;

	init_board(board);
	print_board(board);

    system("pause");

}


void init_board(char board[N][N])
{
	int i, j;
	for(i = 0; i < N; ++i)
	{
		for(j = 0; j < N; ++ j)
		{
			board[i][j] = EMPTY_CHAR;
		}
	}
}

void print_board(char board[N][N])
{
	printf("\n");
	printf("   A   B   C  \n\n");
	
	int i;
	for(i = 0; i < N; ++i)
	{
		printf("%d  %c | %c | %c  %d\n", i+1, board[0][i], board[1][i], board[2][i], i+1);
		if(i!=2) {
			printf("  ---+---+---\n");
		}
	}
	
	printf("\n   A   B   C  \n");
	printf("\n");
}
