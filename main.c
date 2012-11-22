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
void print_initial_information();
int choose_mode();
char choose_player_character();
void user_computer();
void computer_computer();
void random_move(char board[N][N], char ch);
int block_line_1(char board[N][N], char ch);
int block_line_2(char board[N][N], char ch);
int block_line_2(char board[N][N], char ch);
int block_player(char board[N][N], char ch);
int draw_game(char board[N][N]);
int check_winner(char board[N][N]);
void move_computer(char board[N][N], char ch);

int main()
{

	char board[N][N];
	char choice;

	init_board(board);
	print_initial_information();
	
	print_board(board); //Retirar depois
	
    switch(choose_mode()) {
        case 1: computer_computer() /*executar modo 1 = computer x computer*/ ; break;
        case 2: user_computer(); break;
        default:  ;
    }
    
   
    system("pause");

}


/*
* Prints initial information.
*
*/
void print_initial_information() {
    printf("Tic Tac Toe Game \n");
}

/*
* Verify whether the user wants to play or to watch.
*
* @returns integer representing the choice
*/
int choose_mode() {
    int mode;
    while(TRUE) {
        printf("Choose Mode:\n[1] Computer x Computer \n[2] User x Computer\n");
        scanf("%d", &mode);
        fflush(stdin);
        if(mode == 1 || mode == 2) {
            break;
        }
        printf("\nIncorrect choice, Please Try Again\n\n");
    }
    return mode;
}

char choose_player_character() {
    char choice;
    while(TRUE) {
        printf("\nWould you like to play as X and go first? (y/n): ");
        scanf("%c", &choice);
        choice = tolower(choice);
        if(choice == 'y' || choice == 'n') {
        	choice = (choice == 'y' ? PLAYER_X : PLAYER_O);
        	break;
        }
        printf("\nIncorrect choice, Please Try Again\n\n");
    }
    //79 é o e 88 é x
    printf("%d \n", choice); //tirar depois
    return choice;
}

/*
*
*
*/
void random_move(char board[N][N], char ch){
     int x, y;
     
     do{
         x = rand()%3;
         y = rand()%3;
     }while(board[x][y] != EMPTY_CHAR);
     
     board[x][y] = ch;
}

/*
*
*
*/
int block_line_1(char board[N][N], char ch){
    if(board[0][0] == EMPTY_CHAR){
       if(((board[0][1] == board[0][2]) && (board[0][1] != EMPTY_CHAR)) ||
          ((board[1][0] == board[2][0]) && (board[1][0] != EMPTY_CHAR)) ||
          ((board[1][1] == board[2][2]) && (board[1][1] != EMPTY_CHAR))){
                        board[0][0] = ch;
                        return TRUE;
          }
    }
    
    if(board[0][1] == EMPTY_CHAR){
       if(((board[0][0] == board[0][2]) && (board[0][0] != EMPTY_CHAR)) ||
          ((board[1][1] == board[2][1]) && (board[1][1] != EMPTY_CHAR))){
                        board[0][1] = ch;
                        return TRUE;
          }
    }
    
    if(board[0][2] == EMPTY_CHAR){
       if(((board[0][0] == board[0][1]) && (board[0][0] != EMPTY_CHAR)) ||
          ((board[1][2] == board[2][2]) && (board[1][2] != EMPTY_CHAR)) ||
          ((board[1][1] == board[2][0]) && (board[1][1] != EMPTY_CHAR))){
                        board[0][2] = ch;
                        return TRUE;
          }
    }
    
    return FALSE;
}

/*
*
*
*/
int block_line_2(char board[N][N], char ch){
    if(board[1][0] == EMPTY_CHAR){
       if(((board[1][1] == board[1][2]) && (board[1][1] != EMPTY_CHAR)) ||
          ((board[0][0] == board[2][0]) && (board[0][0] != EMPTY_CHAR))){
                        board[1][0] = ch;
                        return TRUE;
          }
    }
    
    if(board[1][1] == EMPTY_CHAR){
       if(((board[1][0] == board[1][2]) && (board[1][0] != EMPTY_CHAR)) ||
          ((board[0][1] == board[2][1]) && (board[0][1] != EMPTY_CHAR)) ||
          ((board[0][2] == board[2][0]) && (board[0][2] != EMPTY_CHAR))){
                        board[1][1] = ch;
                        return TRUE;
          }
    }
    
    if(board[1][2] == EMPTY_CHAR){
       if(((board[1][0] == board[1][1]) && (board[1][0] != EMPTY_CHAR)) ||
          ((board[0][2] == board[2][2]) && (board[0][2] != EMPTY_CHAR))){
                        board[1][2] = ch;
                        return TRUE;
          }
    }
    
    return FALSE;
}

/*
*
*
*/
int block_line_3(char board[N][N], char ch){
    if(board[2][0] == EMPTY_CHAR){
       if(((board[2][1] == board[2][2]) && (board[2][1] != EMPTY_CHAR)) ||
          ((board[0][0] == board[1][0]) && (board[0][0] != EMPTY_CHAR)) ||
          ((board[0][2] == board[1][1]) && (board[0][2] != EMPTY_CHAR))){
                        board[2][0] = ch;
                        return TRUE;
          }
    }
    
    if(board[2][1] == EMPTY_CHAR){
       if(((board[2][0] == board[2][2]) && (board[2][0] != EMPTY_CHAR)) ||
          ((board[0][1] == board[1][1]) && (board[0][1] != EMPTY_CHAR))){
                        board[2][1] = ch;
                        return TRUE;
          }
    }
    
    if(board[2][2] == EMPTY_CHAR){
       if(((board[2][0] == board[2][1]) && (board[2][0] != EMPTY_CHAR)) ||
          ((board[0][2] == board[1][2]) && (board[0][2] != EMPTY_CHAR)) ||
          ((board[0][0] == board[1][1]) && (board[0][0] != EMPTY_CHAR))){
                        board[2][2] = ch;
                        return TRUE;
          }
    }
    
    return FALSE;
}

/*
*
*
*/
int block_player(char board[N][N], char ch){
    
    if(block_line_1(board, ch) || block_line_2(board, ch) || block_line_3(board, ch)) return TRUE;
    return FALSE;
}

/*
*
*
*/
int draw_game(char board[N][N]){
    int i, j;
    
    for(i=0; i < N; i++){
          for(j=0; j < N; j++){
              if(board[i][j] == EMPTY_CHAR) return FALSE;
          }
    }
    
    return TRUE;
} 
 
/*
*
*
*/
int check_winner(char board[N][N]){
    int i;
    
    for(i = 0; i < 3; i++){
          if((board[i][0] == board[i][1]) && (board[i][0] == board[i][2])){
              return board[i][0];
          }
    }
    
    for(i = 0; i < 3; i++){
          if((board[0][i] == board[1][i]) && (board[0][i] == board[2][i])){
               return board[0][i];
          }
    }
    
    if((board[0][0] == board[2][2]) && (board[1][1] == board[2][2])){
         return board[1][1];
    }
    if((board[1][1] == board[0][2]) && (board[1][1] == board[2][0])){
         return board[1][1];
    }
     
    if(draw_game(board)) return 'V';
    
    return EMPTY_CHAR;
}

/*
*
*
*/
void move_computer(char board[N][N], char ch){
     if(block_player(board, ch)) return;
     random_move(board, ch);
}

/*
*
*
*/
void computer_computer() {
     char ch = PLAYER_X; // Somente para teste
     char final;
     char board[N][N];
     
     init_board(board);
     do{
         move_computer(board, ch);
         print_board(board);
         final = check_winner(board);
         if(ch == PLAYER_X){
             ch = PLAYER_O;
         }
         else{
             ch = PLAYER_X;
         }
         getchar();
     }while(final == EMPTY_CHAR);
     
}

void user_computer() {
     char choice;
     choice = choose_player_character();
     printf("Faz nada ainda\n");
     /*while(TRUE)
	{
		if(choice == PLAYER_X)
		{
			if(player_move(board, PLAYER_X) == TRUE)
				break;
			if(comp_move(board, PLAYER_O) == TRUE)
				break;
		}else{
			if(comp_move(board, PLAYER_X) == TRUE)
				break;		
			if(player_move(board, PLAYER_O) == TRUE)
				break;
		}
	}

	return 0;*/
     
}
 
/*
*
*
*/
void init_board(char board[N][N]) {
	int i, j;
	for(i = 0; i < N; ++i) {
		for(j = 0; j < N; ++ j) {
			board[i][j] = EMPTY_CHAR;
		}
	}
}

/*
*
*
*/
void print_board(char board[N][N]) {
	printf("\n");
	printf("   A   B   C  \n\n");
	
	int i;
	for(i = 0; i < N; ++i) {
		printf("%d  %c | %c | %c  %d\n", i+1, board[0][i], board[1][i], board[2][i], i+1);
		if(i!=2) {
			printf("  ---+---+---\n");
		}
	}
	
	printf("\n   A   B   C  \n");
	printf("\n");
}
