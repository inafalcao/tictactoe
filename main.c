/**
*	Tic Tac Toe Game
*	
*
*		@authors Inaciane Monteiro - 344079, Joaquim Filipe - 344066
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
#define EXIT '3'

#define VALID_COORD(x,y) ((x < 0 || x > N-1 || y < 0 || y > N-1) ? FALSE : TRUE)
#define IS_EMPTY(square) (square == ' ' ? TRUE : FALSE)
#define OTHER(player) (player == PLAYER_X ? PLAYER_O : PLAYER_X)


void init_board(char board[N][N]);
void print_board(char board[N][N]);
void print_initial_information();
int choose_mode();
int who_goes_first();
char character_choose();
void winner_counter(char ch);
int play_again();

void user_computer();
int valid_square(char c, int number);
int player_move(char board[N][N], char player);
void tip(char board[N][N], char player);
int preview_computer_win(char board[N][N], char user, char computer);
int comp_move(char board[N][N], char player);
int enter_grid_move(char board[N][N], char player, char c, int number);
int enter_coord_move(char board[N][N], char player, int x, int y);
int check_winner(char board[N][N], char player);
int my_max(char board[N][N], char player);
int my_min(char board[N][N], char player);
void minimax(char board[N][N], char player);
void computer_computer();

/*
* Counters
*/
int win_x = 0, win_o = 0;

/*
*   Main code
*
*/

int main()
{

	char board[N][N];
	char choice;

	init_board(board);
	print_initial_information();
	
	print_board(board);
	
    switch(choose_mode()) {
        case 1: computer_computer(); break;
        case 2: user_computer(); break;
        default:  ;
    }

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
        printf("Choose:\n[1] Computer x Computer \n[2] User x Computer \n[3] Exit\n");
        scanf("%d", &mode);
        __fpurge(stdin);
        if(mode == 1 || mode == 2 || mode == 3) {
            break;
        }
        printf("\nIncorrect choice, Please Try Again\n\n");
    }
    return mode;
}

/*
*  Performs the user moves, asks about the use of tips and informs victory
*
*   @return true if the user won or if it's a draw game, false otherwise
*/

int player_move(char board[N][N], char player)
{
	int grid_num;
	char character;
	int number;
	while(TRUE)
	{
        printf("\nEnter ? for tip.\nOR\n");
		printf("Enter coordenates. ex: A,2\n");
		scanf("%c,%d", &character, &number);
		__fpurge(stdin);
         
	    if(character == '?'){
            tip(board, player);
            break;
        }

        //if exit
        if(character == EXIT)
            exit(0);
        
        if(enter_grid_move(board, player, character, number) == FALSE)
    			break;
    
    		// Invalid move location
    		printf("Incorrect choice, Try Again\n");
	}

	print_board(board);

	int play = check_winner(board, player);
	if(play == WIN){
		printf("\nCongratulations, you are the winner\n");
		winner_counter(player);
		return TRUE;
	}else if(play == DRAW){
		printf("\nIt's a Draw\n");
		return TRUE;
	}
	return FALSE;
}

/*
* Generates and prints the tip for the user. 
*
*/
void tip(char board[N][N], char player) {
    char other_board[N][N];
    int i, j;
    char choice;
    
    for(i=0; i<N; i++){
             for(j=0; j<N; j++){
                      other_board[i][j] = board[i][j];
             }
    }
    
    minimax(other_board, player);
    
    printf("\nDo you want to make this move below? (y/n)\n\n");
    print_board(other_board);
    
    while(TRUE){
        scanf("%c", &choice);
        __fpurge(stdin);
        choice = tolower(choice);
        if(choice == 'y'){
              minimax(board, player);
              break;
        }
        if(choice == 'n') break;
        
        if(choice == EXIT) exit(0);
                
        printf("Incorrect choice. Try again.\n");
    }
}


/*
* Checks if the user is blocked, and the computer will win.
*
* @returns true if the computer won, false otherwise.
*/
int preview_computer_win(char board[N][N], char user, char computer) {
    char other_board[N][N];
    int i, j;
    
    for(i=0; i<N; i++){
             for(j=0; j<N; j++){
                      other_board[i][j] = board[i][j];
             }
    }
    minimax(other_board, computer);
    minimax(other_board, user);
    minimax(other_board, computer);
    
    int play = check_winner(other_board, computer);
	if(play == WIN){
        minimax(board, computer);
        print_board(board);
		printf("\nYou're blocked, the computer wins.\n");
		winner_counter(computer);
		return TRUE;
    }
    return FALSE;
     
}

/*
*  Validate the coordinates given by the user.
*
* @returns true if it is valid, false otherwise.
*/
int valid_square(char character, int number) {
    character = tolower(character);
    /* Coordinate character given by the user. */
    int int_value_character = character;
    int int_value_a = 'a';
    int int_value_c = 'c';
    if(  (int_value_character > int_value_c || int_value_character < int_value_a)   ||  ( number > N || number < 1 ) )
       return FALSE;
    return TRUE;
        
}

/*
*  Performs computer moves and counts whether the computer won.
*
* @returns true if the computer won or if it's a draw, false otherwise.
*/
int comp_move(char board[N][N], char player)
{
	minimax(board, player);
	print_board(board);
	
	int play = check_winner(board, player);
	if(play == WIN)
	{
		printf("\nUnlucky, the computer wins\n");
		winner_counter(player);
		return TRUE;
	}else if(play == DRAW){
		printf("\nIt's a Draw\n");
		return TRUE;
	}
	return FALSE;
}

/*
*  Translates user coordinates to integers i,j representing the board position.
*
* @returns true or false
*/
int enter_grid_move(char board[N][N], char player, char character, int number) {
	if(valid_square(character, number) == FALSE)
		return TRUE;
	
    //Calculates corresponding i,j coordinates. i = line, j = row
	//a = 97 / b = 98 / c = 99
	int i,j;
	int int_value_character = tolower(character);
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

/*
*  Checks if computer's moves are valid.
*/
int enter_coord_move(char board[N][N], char player, int x, int y)
{
	// Check that coordinates are valid
	if(VALID_COORD(x,y) == FALSE)
		return TRUE;
	if(IS_EMPTY(board[x][y]) == FALSE)
		return TRUE;
	board[x][y] = player;
        
	return FALSE;
}

/*
*  Checks whether the player (computer or user, specified by the "player" function parameter)
*  won, and checks for draw.
*
*/
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


/*
*  Used for computer's logic.
*
*/
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


/*
*  Used for computer's logic.
*
*/
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

/*
*  Used for computer's logic.
*
*/
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
	
	enter_coord_move(board, player, max_i, max_j);
	
	//if(enter_coord_move(board, player, max_i, max_j) == TRUE){
		//printf("Minimax - Error entering move\n"); //Debug
		//exit(0);
	//}
}

/*
* Function that allows the user to choose x or o.
*
* @returns char representing the choice
*/
char character_choose(){
     char ch;
     
     printf("Do you prefer playing with X or O? \n");
     
     while(TRUE){
         scanf("%c", &ch);
         __fpurge(stdin);
         ch = toupper(ch);
         
         if(ch == PLAYER_X){
               return PLAYER_X;
               break;
         }
         if(ch == PLAYER_O){
               return PLAYER_O;
               break;
         }
         if(ch == EXIT) exit(0);
         
         printf("Incorrect Choice, Please try again: \n");
     }
}     
/*
*  Decides randomly who is the first to play
*
*  @returns true if the user starts playing, false otherwise
*/
int who_goes_first(){
    int n;
    char ch;
    
    printf("Choose between an even and an odd number (e/o): \n");
    while(TRUE){
        scanf("%c", &ch);
        __fpurge(stdin);
        ch = tolower(ch);
        if((ch == 'e') || (ch == 'o'))
            break;
        if(ch == EXIT) exit(0);
        printf("Incorrect choice. Try again.\n");
    }
    
    n = rand()%11;
    if(ch == 'e'){
          if((n%2) == 0){
                   printf("You go first!\n");
                   return TRUE;
          }
    }
    if(ch == 'o'){
          if((n%2) != 0){
                   printf("You go first!\n");
                   return TRUE;
          }
    }
    
    printf("The computer goes first!\n");
    return FALSE;
}

/*
*  Counts the number of wins
*
*/
void winner_counter(char ch){
     
     if(ch == PLAYER_X) win_x++;
     if(ch == PLAYER_O) win_o++;
     
     printf("Wins:   X = %d   |   O = %d\n", win_x, win_o);

}

/*
* Checks if the user wants to keep playing.
*
*/

int play_again(){
    char choice;
    
    printf("Do you want to play another game? (y/n): \n");
    
    while(TRUE){
        scanf("%c", &choice);
        __fpurge(stdin);
        choice = tolower(choice);
        
        if(choice == 'y'){
                  return TRUE;
                  break;
        }
        if(choice == 'n'){
                  return FALSE;
                  break;
        }
        if(choice == EXIT) exit(0);
        
        printf("Incorrect choice. Try Again.\n");
        
    }
    
    return FALSE;   
}
    
/*
*  Function with the demonstration (Computer x Computer game) logic
*
*/
void computer_computer() {
     char ch = PLAYER_X; 
     int final;
     char board[N][N];
     
     init_board(board);
     do{
         comp_move(board, ch);
         print_board(board);
         final = check_winner(board, ch);
         if(ch == PLAYER_X){
             ch = PLAYER_O;
         }
         else{
             ch = PLAYER_X;
         }
         getchar();
     }while(final == UNFINISHED);
     
}

/*
*  Contains the logic for the player x computer game
*
*/
void user_computer() {
     char choice, computer;
     char cont;
     choice = character_choose();
     if(choice == PLAYER_X) computer = PLAYER_O;
     if(choice == PLAYER_O) computer = PLAYER_X; 
     char board[N][N];
     while(TRUE){
             int first = who_goes_first();
             init_board(board);
             while(TRUE)
             {
                    if(first == TRUE){
                             if(player_move(board, choice) == TRUE) break;
                             if (preview_computer_win(board, choice, computer) == TRUE) break;
                             if(comp_move(board, computer) == TRUE) break;
                    }
                    else{
                         if(comp_move(board, computer) == TRUE) break;
                         if(player_move(board, choice) == TRUE) break;
                         if (preview_computer_win(board, choice, computer) == TRUE) break;
                    }
             }
             
             cont = play_again();
             if(cont == FALSE) break;
     }     
}
 
/*
* Initialize the board.
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
* Prints the board
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
