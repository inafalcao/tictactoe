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

#define VALID_COORD(x,y) ((x < 0 || x > N-1 || y < 0 || y > N-1) ? FALSE : TRUE)
#define IS_EMPTY(square) (square == ' ' ? TRUE : FALSE)
#define OTHER(player) (player == PLAYER_X ? PLAYER_O : PLAYER_X)


void init_board(char board[N][N]);
void print_board(char board[N][N]);
void print_initial_information();
int choose_mode();
char choose_player_character();

void user_computer();
int valid_square(char c, int number);
int player_move(char board[N][N], char player);
int comp_move(char board[N][N], char player);
int enter_grid_move(char board[N][N], char player, char c, int number);
int enter_coord_move(char board[N][N], char player, int x, int y);
int check_winner(char board[N][N], char player);
int my_max(char board[N][N], char player);
int my_min(char board[N][N], char player);
void minimax(char board[N][N], char player);


void computer_computer();
int check_winner_2(char board[N][N]);
void random_move(char board[N][N], char ch);
int block_line_1(char board[N][N], char ch);
int block_line_2(char board[N][N], char ch);
int block_line_3(char board[N][N], char ch);
int block_player(char board[N][N], char ch);
int draw_game(char board[N][N]);
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
    return choice;
}

int player_move(char board[N][N], char player)
{
	int grid_num; //celula
	char character;
	int number;
	while(TRUE)
	{
		printf("Enter coordenates. ex: A,2\n");
		scanf("%c,%d", &character, &number);
		//printf("\t\t\tYOUR TURN\n");	
	
    	if(enter_grid_move(board, player, character, number) == 0)
			break;

		// Invalid move location
		printf("Incorrect choice, Try Again\n");
	}

	print_board(board);

	int play = check_winner(board, player);
	if(play == WIN){
		printf("\nCongratulations, you are the winner\n");
		return TRUE;
	}else if(play == DRAW){
		printf("\nIt's a Draw\n");
		return TRUE;
	}
	return FALSE;
}

int valid_square(char character, int number) {
    character = tolower(character);
    int int_value_character = character;
    int int_value_a = 'a';
    int int_value_c = 'c';
    if(  (int_value_character > int_value_c || int_value_character < int_value_a)   ||  ( number > 3 || number < 1 ) )
       return FALSE;
    return TRUE;
        
}

int comp_move(char board[N][N], char player)
{
	//printf("\t\t\tCOMPUTER'S TURN\n");

	minimax(board, player);
	print_board(board);

	int play = check_winner(board, player);
	if(play == WIN)
	{
		printf("\nUnlucky, the computer wins\n");
		return TRUE;
	}else if(play == DRAW){
		printf("\nIt's a Draw\n");
		return TRUE;
	}
	return FALSE;
}

int enter_grid_move(char board[N][N], char player, char character, int number) {
	if(valid_square(character, number) == FALSE)
		return TRUE;
	
    //Calculates corresponding i,j coordinates. i = line, j = row
	//a = 97 / b = 98 / c = 99
	int i,j;
	int int_value_character = character;
	if(int_value_character == 97){
		i = 0;
	}else if(int_value_character == 98){
		i = 1;
	}else{
		i = 2;
	}
	
	j = number-1;
	
	if(IS_EMPTY(board[i][j]) == FALSE)
		return TRUE;
	board[i][j] = player;

	return FALSE;
}

int enter_coord_move(char board[N][N], char player, int x, int y)
{
	// Check that coordinates are valid
	if(VALID_COORD(x,y) == FALSE)
		return TRUE;
	//if(board[x][y] != ' ')
	if(IS_EMPTY(board[x][y]) == FALSE)
		return TRUE;
	board[x][y] = player;

	return FALSE;
}

int check_winner(char board[N][N], char player)
{
	int i, j;
	//Row and Column Checks
	for(i = 0; i < N; ++i)
	{
		//Row
		if(board[0][i] != EMPTY_CHAR)
		{
			if(board[0][i] == board[1][i] && board[1][i] == board[2][i])
				return board[0][i] == player ? WIN : LOSE;
		}
		//Column
		if(board[i][0] != EMPTY_CHAR)
		{
			if(board[i][0] == board[i][1] && board[i][1] == board[i][2])
				return board[i][0] == player ? WIN : LOSE;
		}
	}

	//Left Diagonal
	if(board[0][0] != EMPTY_CHAR && board[0][0] == board[1][1] && board[1][1] == board[2][2]){
		return board[0][0] == player ? WIN : LOSE;
	}

	//Right Diagonal
	if(board[2][0] != EMPTY_CHAR && board[2][0] == board[1][1] && board[1][1] == board[0][2]){
		return board[2][0] == player ? WIN : LOSE;
	}

	//Check for draw
	for(i = 0; i < N; ++i)
	{
		for(j = 0; j < N; ++j)
		{
			if(board[i][j] == EMPTY_CHAR)
				break;
		}
		if(board[i][j] == EMPTY_CHAR)
			break;
	}
	//Draw
	if(i*j==9)
		return DRAW;

	// Incomplete board
	return UNFINISHED;
}

int my_max(char board[N][N], char player)
{
	int result = check_winner(board, player);
	if(result != UNFINISHED)
		return result;

	int i, j, max;
	max = -10; // Only actually needs to be less than -1
	for(i = 0; i < N; ++i)
	{
		for(j = 0; j < N; ++j)
		{
			if(board[i][j] != ' ')
				continue;
			char new_board[N][N];
			int x, y;
			for(x = 0; x < N; ++x)
			{
				for(y = 0; y < N; ++y)
				{
					new_board[x][y] = board[x][y];
				}
			}
			if(new_board[i][j] != ' '){
				printf("MY_MAX overlap\n");
				exit(0);
			}
			new_board[i][j] = player;
			int temp = my_min(new_board, OTHER(player));
			if(temp > max)
				max = temp;
		}
	}
	return max;
}

int my_min(char board[N][N], char player)
{
	int result = check_winner(board, OTHER(player));
	if(result != UNFINISHED)
		return result;

	int i, j, min;
	min = 10; //Only actually has to be greater than 1
	for(i = 0; i < N; ++i)
	{
		for(j = 0; j < N; ++j)
		{
			if(board[i][j] != ' ')
				continue;
			char new_board[N][N];
			int x, y;
			for(x = 0; x < N; ++x)
			{
				for(y = 0; y < N; ++y)
				{
					new_board[x][y] = board[x][y];
				}
			}
			if(new_board[i][j] != ' '){
				printf("MY_MIN overlap\n"); //Debug
				exit(0);
			}
			new_board[i][j] = player;
			int temp = my_max(new_board, OTHER(player));
			if(temp < min)
				min = temp;
		}
	}
	return min;
}

void minimax(char board[N][N], char player)
{
	int i, j, max, max_i, max_j;
	max = -10;
	for(i = 0; i < N; ++i)
	{
		for(j = 0; j < N; ++j)
		{
			if(board[i][j] != ' ')
				continue;
			char new_board[N][N];
			int x,y;
			for(x = 0; x < N; ++x)
			{
				for(y = 0; y < N; ++y)
				{
					new_board[x][y] = board[x][y];
				}
			}
			new_board[i][j] = player;
			int temp = my_min(new_board, OTHER(player));
			// Max(Computer) is always the top of minimax tree
			// Finish with max result of my_min() recursive loop
			if(temp > max)
			{
				max = temp;
				max_i = i;
				max_j = j;
			}
		}
	}	
	if(enter_coord_move(board, player, max_i, max_j) == TRUE){
		printf("Minimax - Error entering move\n"); //Debug
		exit(0);
	}
}

















//coisas do filipe


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
int check_winner_2(char board[N][N]){
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
         final = check_winner_2(board);
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
     char board[N][N];
     init_board(board);
     while(TRUE)
	 {
		if(choice == PLAYER_X) {
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
