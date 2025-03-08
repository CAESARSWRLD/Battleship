#include "header.h"
#include "stats.h"

//stats structs for battleship.log
Stats player1_stats = { 0, 0, 0, 0.0, false };
Stats player2_stats = { 0, 0, 0, 0.0, false };





//gameloop
int game_loop(void)
{



	//integers for tracking player stats
	int one_hits, one_misses, two_hits, two_misses;


	//for random numbers
	srand(time(NULL));

	//clear screen when game loop begins
	clear_the_screen();

	//CREATE THE BOARDS
	char p1_board[MAX_ROWS][MAX_COLS];
	char p2_board[MAX_ROWS][MAX_COLS];
	char p2_board_hidden[MAX_ROWS][MAX_COLS];


	





	int rand_or_manual = 0;
	printf("Would you like to manually place you ships or have them randomly placed: \n1. Manual placement\n2. Random placement\n");
	scanf("%d", &rand_or_manual);


	if (rand_or_manual == 1)
	{

		initialize_game_board(p1_board, MAX_ROWS, MAX_COLS, '~');

		//PLACE SHIPS MANUALLY
		place_ships_manually(p1_board);


		
		//PRINT THE GAME BOARD
		printf("\nPlayer1's Board:\n");
		print_board(p1_board, MAX_ROWS, MAX_COLS);


	}
	else if(rand_or_manual == 2)
	{

		initialize_game_board(p1_board, MAX_ROWS, MAX_COLS, '~');


		//PLACE SHIPS RANDOMLY
		place_rand_ships(p1_board);

		//PRINT THE GAME BOARD
		print_board(p1_board, MAX_ROWS, MAX_COLS);

	}
	else
	{
		printf("Invalid input");
		exit(0);
	}


	

	

	////////////////////////////////
	//CREATE ENEMY GAMEBOARD
	initialize_game_board(p2_board, MAX_ROWS, MAX_COLS, '~');

	//randomly places ships
	place_rand_ships(p2_board);

	printf("\nEnemy battleships generated. They are hidden\n");

	//shows the p2 board but keeps ship locations hidden
	p_two_board_hidden(p2_board, p2_board_hidden, 88, 88, false, &one_hits, &one_misses, &two_hits, &two_misses, 1, &player1_stats, &player2_stats);//false indicates that the hidden board hasnt been created yet, so the coordinates are ignored and the hidden board is created.
																// This function will also be used for editing the hidden game board to show hits and misses. the boolean value will be true in the case that the board has already been created



	printf("\nPlayer 2 board:\n\n");
	print_board(p2_board_hidden, MAX_ROWS, MAX_COLS);

	













	///random selection of starting player
	int turn = rand() % 2;

	if (turn == 0) //if statement handles the first turn of the match
	{
		int x, y;
		printf("\n\nPlayer1 has been randomly selected to start the game\nEnter the coordinates of your first strike (example:3 7): ");
		scanf("%d %d", &x, &y);

		//clear screen
		clear_the_screen();

		p_two_board_hidden(p2_board, p2_board_hidden, x, y, true, &one_hits, &one_misses, &two_hits, &two_misses, 0, &player1_stats, &player2_stats);

		p_two_board_hidden(p2_board, p2_board, x, y, true, &one_hits, &one_misses, &two_hits, &two_misses, 1, &player1_stats, &player2_stats);



		//show boards after first turn
		printf("Player 1 board:\n");
		print_board(p1_board, MAX_ROWS, MAX_COLS);

		printf("\n\nPlayer 2 board:\n");
		print_board(p2_board_hidden, MAX_ROWS, MAX_COLS);


		turn = 1;
	}
	else if (turn == 1)
	{
		int x = random_number();
		int y = random_number();

		printf("\n\nPlayer2 has been randomly selected to start the game\n");
	

		printf("\n They chose: %d %d\n\n", x, y);

		//press enter to continue
		prompt_continue();

		//clear screen
		clear_the_screen();

		p_two_board_hidden(p1_board, p1_board, x, y, true, &one_hits, &one_misses, &two_hits, &two_misses, 0, &player1_stats, &player2_stats);



		//show boards after first turn
		printf("Player 1 board:\n");
		print_board(p1_board, MAX_ROWS, MAX_COLS);

		printf("\n\nPlayer 2 board:\n");
		print_board(p2_board_hidden, MAX_ROWS, MAX_COLS);

		turn = 0;
	}





	//press enter to continue
	prompt_continue();

	//clear screen
	clear_the_screen();

	


	



	
	///MAIN LOOP OF GAME LOOP
	bool game_over = false;


	while(game_over == false)
	{

		int is_winner = 0;
		int rounds = 2;
		while (is_winner == 0)//while this block is looping the players are swapping turns by incrementing up 1 after player one strikes and down one after player two strike. The 'turn' variable goes up and down by one continuously until the game ends. game ends when a player loses their ships
		{
			

			printf("\nROUND: %d\n", rounds);
			//press enter to contninue
			prompt_continue();
			//clear screen
			clear_the_screen();


			if (turn == 0)//when turn == 0 its player ones turn and when turn == 1 its platers twos turn
			{
				///PLAYER ONES TURN

				int x, y;
				printf("\nPlayer1's turn (example:3 7): ");
				scanf("%d %d", &x, &y);

				//clear screen
				clear_the_screen();

				p_two_board_hidden(p2_board, p2_board_hidden, x, y, true, &one_hits, &one_misses, &two_hits, &two_misses, 1, &player1_stats, &player2_stats);


				//show boards
				printf("Player 1 board:\n");
				print_board(p1_board, MAX_ROWS, MAX_COLS);

				printf("\n\nPlayer 2 board:\n");
				print_board(p2_board_hidden, MAX_ROWS, MAX_COLS);





				////TESTING 
				/*printf("\n\nPlayer 2 actual board:\n");
				print_board(p2_board, MAX_ROWS, MAX_COLS);*/



				turn = 1;
			}
			else if (turn == 1)
			{

				///PLAYER TWOS TURN
				int x = random_number();
				int y = random_number();

				printf("\nPlayer2's turn\n");


				printf("\n They chose: %d %d\n\n", x, y);

				//press enter to continue
				prompt_continue();

				//clear screen
				clear_the_screen();

				p_two_board_hidden(p1_board, p1_board, x, y, true, &one_hits, &one_misses, &two_hits, &two_misses, 0, &player1_stats, &player2_stats);



				//show boards
				printf("Player 1 board:\n");
				print_board(p1_board, MAX_ROWS, MAX_COLS);

				printf("\n\nPlayer 2 board:\n");
				print_board(p2_board_hidden, MAX_ROWS, MAX_COLS);





				turn = 0;



			}

			////check for a winner
			int winner_p1 = check_for_winner(p1_board);
			int winner_p2 = check_for_winner(p2_board);


			if (winner_p1 == 9)
			{
				printf("\nPlayer 2 wins");
				is_winner = 1;
			}
			else if (winner_p2 == 9)
			{
				printf("\nPlayer 1 wins");
				is_winner = 1;
			}
			else
			{

			}

			//add one to rounds
			rounds++;

			

	

			

		}

	
		

		game_over = true;//exit game loop when game_over bool is set to true

	}

	printf("\n\nGame over");

	FILE* battleshiplog = fopen("battleship.log", "w");



	////IMPORTANT: in battleship.log player one is logged as Player 0 and player 2 is logged as Player 1
	
	////ADDS DATA TO battleship.log FILE:
	fprintf(battleshiplog, "Player 1 stats: Hits: %d, Misses: %d, Shots: %d, Hit/Miss Ratio: %.2f, Result: %s\n", one_hits, one_misses, two_hits, two_misses);
	//	player1_stats.total_hits, player1_stats.total_misses, player1_stats.total_shots,
	//	player1_stats.hits_to_misses_ratio, player1_stats.result);

	//fprintf(battleshiplog, "Player 2 stats: Hits: %d, Misses: %d, Shots: %d, Hit/Miss Ratio: %.2f, Result: %s\n",
	//	player2_stats.total_hits, player2_stats.total_misses, player2_stats.total_shots,
	//	player2_stats.hits_to_misses_ratio, player2_stats.result);

	fclose(battleshiplog);

	printf("\nStatistics outputted to logfile successfully!\n\n\n\n");

	//press enter to continue
	prompt_continue();

	//clear screen
	clear_the_screen();

}

//press enter to continue function
void prompt_continue() {
	printf("Press Enter to continue...");
	while (getchar() != '\n');
	getchar();
}

//creates gameboard to represent the p2 gameboard from p1 perspective
//this function also takes the user input and shows where the player made hits and misses.
//ive also adjusted this to allow it to be used to adjust the player 1 gameboard
void p_two_board_hidden(char board[][MAX_COLS], char p2_board_h[][MAX_COLS], int bomb_x, int bomb_y, bool hidden_board_created, int* one_hits, int* one_misses, int* two_hits, int* two_misses, int player_turn, Stats* player1_stats, Stats* player2_stats)
{
	if (!hidden_board_created) {
		// initializing hidden board
		for (int i = 0; i < MAX_ROWS; i++)
		{
			for (int j = 0; j < MAX_COLS; j++)
			{
				p2_board_h[i][j] = '~';
			}
		}
	}
	else {
		bool valid_placement = false;

		while (!valid_placement)
		{
			if ((bomb_x >= 0 && bomb_x < MAX_ROWS && bomb_y >= 0 && bomb_y < MAX_COLS))
			{
				/////log the targeted position
				FILE* battleshiplog = fopen("battleship.log", "a"); 

				fprintf(battleshiplog, "Player %d targeted: (%d, %d)\n", player_turn, bomb_x, bomb_y);

				// check if it hit a part of a ship
				if (board[bomb_x][bomb_y] != '~')
				{
					char ship_type = board[bomb_x][bomb_y];
					printf("\nHIT!\n");

					// Log the hit
					fprintf(battleshiplog, "Hit on ship: %c\n", ship_type);

					// Increment the hit count for the current player
					if (player_turn == 1)
					{
						(*one_hits)++;
						player1_stats->hits++;
					}
					else
					{
						(*two_hits)++;
						player2_stats->hits++;
					}

					//////mark every part of the ship as hit
					for (int i = 0; i < MAX_ROWS; i++)
					{
						for (int j = 0; j < MAX_COLS; j++)
						{
							if (board[i][j] == ship_type)
							{
								p2_board_h[i][j] = '*';
							}
						}
					}

					// Check if the ship has sunk (all parts marked as hit)
					bool ship_sunk = true;
					for (int i = 0; i < MAX_ROWS; i++)
					{
						for (int j = 0; j < MAX_COLS; j++)
						{
							if (board[i][j] == ship_type)
							{
								ship_sunk = false;
								break;
							}
						}
						if (!ship_sunk) break;
					}

					if (ship_sunk) {
						fprintf(battleshiplog, "Ship %c has sunk!\n", ship_type);
					}

					valid_placement = true;
				}
				else if (board[bomb_x][bomb_y] == '*' || board[bomb_x][bomb_y] == 'm')//PREVENTS THE REUSE OF COORDINATES
				{
					printf("Canno reuse coordinates");
					valid_placement = false;
				}
				// Miss
				else
				{
					p2_board_h[bomb_x][bomb_y] = 'm';
					printf("\nMiss!\n");

					// log the miss
					fprintf(battleshiplog, "Miss at: (%d, %d)\n", bomb_x, bomb_y);

					//increment miss count
					if (player_turn == 1)
					{
						(*one_misses)++;
						player1_stats->misses++;
					}
					else
					{
						(*two_misses)++;
						player2_stats->misses++;
					}

					valid_placement = true;
				}

				//close log file after the move
				fclose(battleshiplog);
			}
			else 
			{
				printf("Invalid placement. Try again\n\n");
			}
		}
	}
}

int place_ship(char board[][MAX_COLS], char ship_type, int ship_length)
{
	int* coords = malloc(ship_length * 2 * sizeof(int));  // using malloc to store coordinates
	if (coords == NULL)
	{
		printf("Memory allocation failed.\n");
		return 1;  // failure due to memory allocation issue
		//idk how to use malloc but i think this works
	}

	int valid_input = 0; //check if input is valid
	while (!valid_input)
	{
		// Prompt user for coordinates
		printf("\nPlease enter the %d cells to place the %s:\n",
			ship_length,
			(ship_type == 'C' ? "Carrier" :
				ship_type == 'B' ? "Battleship" :
				ship_type == 'c' ? "Cruiser" :
				ship_type == 'S' ? "Submarine" : "Destroyer"));

		printf("Example: ");
		for (int i = 0; i < ship_length; i++)
		{
			printf("%d %d ", i, i + 1); 
		}
		printf("\n");

		// Read coordinates for the ship
		int input_valid = 1;  
		for (int i = 0; i < ship_length * 2; i++)
		{
			if (scanf("%d", &coords[i]) != 1)
			{
				printf("Invalid input. Enter integer values only.\n");
				input_valid = 0;
				break;
			}
		}

		if (!input_valid)
		{
			while (getchar() != '\n');
			continue;  // Retry input after invalid entry
		}

		// Validate and place the ship on the board
		valid_input = 1;  // Assume input is valid initially
		for (int i = 0; i < ship_length * 2; i += 2)
		{
			int row = coords[i];
			int col = coords[i + 1];

			// Check if coordinates are within bounds and not overlapping
			if (row >= 0 && row < MAX_COLS && col >= 0 && col < MAX_COLS)
			{
				if (board[row][col] == '~')
				{
					board[row][col] = ship_type;  // Place ship symbol
				}
				else
				{
					printf("Error: Coordinate (%d, %d) overlaps with another ship. Please re-enter.\n", row, col);
					valid_input = 0; 
					break;
				}
			}
			else
			{
				printf("Error: Coordinate (%d, %d) is out of bounds. Please re-enter.\n", row, col);
				valid_input = 0;  
				break;
			}
		}
	}

	free(coords);  
	return 0;  
}

//the main game loop will continually use this function to check if either of the players have lost all of their ships. returns 9 if the board used as an input paramter has no more ships
int check_for_winner(char board[][MAX_COLS])
{
	for (int r = 0; r < MAX_ROWS; r++) 
	{
		for (int c = 0; c < MAX_COLS; c++) 
		{
			// Check if any of the ship symbols are present on the board
			if (board[r][c] == 'C' || board[r][c] == 'B' || board[r][c] == 'c' || board[r][c] == 'S' || board[r][c] == 'D')
			{
				return 0; 
			}
			
		}
	}

	return 9; // return 9 if no ships are found on the board

}

void place_ships_manually(char board[][MAX_COLS]) 
{
	printf("Manual Placement:\n");

	//allows user to place ships manually using the place_ship function for each ship
	//loops allows the program to reprompt the users manual ship placement input if their initial input was invalid


	place_ship(board, 'C', CARRIER_LENGTH);
	
	place_ship(board, 'B', BATTLESHIP_LENGTH);

	place_ship(board, 'c', CRUISER_LENGTH);

	place_ship(board, 'S', SUBMARINE_LENGTH);

	place_ship(board, 'd', DESTROYER_LENGTH);
}

//randomly places player one ships
void place_rand_ships(char board[][MAX_COLS])
{
	


	//ADD SHIPS RANDOMLY
	random_placement(board, 5, 'C');//carrier

	random_placement(board, 4, 'b');//battleship

	random_placement(board, 3, 'c');//cruiser

	random_placement(board, 3, 'S');//sub

	random_placement(board, 2, 'd');//destroyer




}

//clear screen
void clear_the_screen()
{
	system("cls");
}

//random number generator 
int random_number(void) {
	return (rand() % 9) + 1;
};

/////////////////////////////////////////////////////////////////////////////////////////
//random ship placement//////////////////////////////////////////////////////////////////

//this function takes a number as a parameter 
//void random_placement(char board[][MAX_COLS], int ship ,char symbol)
//{
//
//	////int carrier = 1, battleship = 2, cruiser = 3, sub = 4, destroyer = 5;
//
//	
//
//	///placing the carrier
//	if (ship == 1)
//	{
//		///placing the carrier
//
//
//
//		int c = random_number();
//		int r = random_number();
//
//
//		// Print the modified array with "O" replacing 1s
//		if (r <= 5)
//		{
//
//			
//
//
//			for (int row = 0; row < 5; row++)
//			{
//				if (board[r][c] == '~')
//				{
//					board[r][c] = symbol;
//					r++;
//				}
//
//			}
//
//		}
//		else if (r > 5)
//		{
//
//		
//
//
//			for (int row = 0; row < 5; row++)
//			{
//				if (board[r][c] == '~')
//				{
//					board[r][c] = symbol;
//					r--;
//				}
//
//			}
//		}
//	}
//	else if (ship == 2) ////placing the battleship
//	{
//
//
//
//		int c = random_number();
//		int r = random_number();
//
//		while (board[r][c] == '~');
//
//
//	
//
//		
//		
//
//
//
//		if (r <= 5)
//		{
//			for (int row = 0; row < 4; row++)
//			{
//				if (board[r][c] == '~')
//				{
//					board[r][c] = symbol;
//					r++;
//				}
//
//			}
//
//		}
//		else
//		{
//			for (int row = 0; row < 4; row++)
//			{
//				if (board[r][c] == '~')
//				{
//					board[r][c] = symbol;
//					r--;
//				}
//
//			}
//		}
//
//
//
//
//
//
//	}
//	else if (ship == 3) ////placing the cruiser
//	{
//
//
//
//
//		int c = random_number();
//		int r = random_number();
//
//		// Print the modified array with "O" replacing 1s
//		if (r <= 7)
//		{
//			for (int j = 0; j < 3; j++)
//			{
//				if (board[r][c] == '~')
//				{
//					board[r][c] = symbol;
//					r--;
//				}
//
//
//			}
//
//		}
//		else
//		{
//			for (int j = 0; j < 3; j++)
//			{
//				if (board[r][c] == '~')
//				{
//					board[r][c] = symbol;
//					r++;
//				}
//
//			}
//		}
//	}
//	else if (ship == 4) ////placing the subs
//	{
//
//
//
//
//		int c = random_number();
//		int r = random_number();
//
//		// Print the modified array with "O" replacing 1s
//		if (r <= 7)
//		{
//			for (int j = 0; j < 3; j++)
//			{
//				if (board[r][c] == '~')
//				{
//					board[r][c] = symbol;
//					r--;
//				}
//
//
//			}
//
//		}
//		else
//		{
//			for (int j = 0; j < 3; j++)
//			{
//				if (board[r][c] == '~')
//				{
//					board[r][c] = symbol;
//					r++;
//				}
//
//			}
//		}
//	}
//	else if (ship == 5) ////placing the destoyer
//	{
//
//
//
//
//		int c = random_number();
//		int r = random_number();
//
//		// Print the modified array with "O" replacing 1s
//		if (r <= 7)
//		{
//			for (int j = 0; j < 2; j++)
//			{
//				if (board[r][c] == '~')
//				{
//					board[r][c] = symbol;
//					r--;
//				}
//
//
//			}
//
//		}
//		else
//		{
//			for (int j = 0; j < 2; j++)
//			{
//				if (board[r][c] == '~')
//				{
//					board[r][c] = symbol;
//					r++;
//				}
//
//			}
//		}
//	}
//	
//	
//}

void random_placement(char board[][MAX_COLS], int ship_length, char symbol) {
	int start_row, start_col;
	bool placed = false;
	int direction;  

	while (!placed) {
		start_row = random_number(); 
		start_col = random_number();  
		direction = rand() % 2;       // vert or horiz, 0 for vertical, 1 for horizontal

		// Check if the ship can be placed at this starting position in the selected direction
		bool can_place = true;

		if (direction == 0) 
		{  // Vertical placement
			//ensure ship fits vertically within grid
			if (start_row + ship_length <= MAX_ROWS) 
			{
				//checks if the cells in the column are available
				for (int i = 0; i < ship_length; i++) 
				{
					if (board[start_row + i][start_col] != '~') 
					{
						can_place = false;
						break;
					}
				}
			}
			else 
			{
				can_place = false;
			}
		}
		else 
		{  // horizontal placement
			// ensures ship fits horizontally
			if (start_col + ship_length <= MAX_COLS) 
			{
				// Checks cell availablility
				for (int i = 0; i < ship_length; i++) 
				{
					if (board[start_row][start_col + i] != '~') 
					{
						can_place = false;
						break;
					}
				}
			}
			else 
			{
				can_place = false;
			}
		}

		// If a spot is found that conatins only tildes, this nested if-else block places the ship
		if (can_place) 
		{
			if (direction == 0) 
			{  //vertically
				for (int i = 0; i < ship_length; i++) 
				{
					board[start_row + i][start_col] = symbol;
				}
			}
			else 
			{  //horizontally
				for (int i = 0; i < ship_length; i++) 
				{
					board[start_row][start_col + i] = symbol;
				}
			}
			placed = true;
		}
	}
}

//welcome screen
int welcome_options()
{
	int welcome_choice = 0;
	printf("Welcome to Battleship: \n\n1. Type 1 to play game\n2. Type 2 to see the rules\n3. Type 3 to exit\n");
	scanf(" %d", &welcome_choice);
	return welcome_choice;

}

//print rules
void print_rules(void)
{
	printf("Battleship is a two player Navy game. The objective of the game is to sink\n"
		"all ships in your enemy's fleet. The player to sink his/her enemy's fleet\n"
		"first wins. Both players' fleets consist of 5 ships that are hidden from\n"
		"the enemy. Each ship may be differentiated by its \"size\" (besides the\n"
		"Cruiser and Submarine) or number of cells it expands on the game board.\n"
		"The Carrier has 5 cells, Battleship has 4 cells, Cruiser has 3 cells,\n"
		"Submarine has 3 cells, and the Destroyer has 2 cells.\n");
		


}

// initializes the 2-D game board for PA 6 to the symbol passed in as a parameter
// the symbol is the water symbol ('~') in this case.
void initialize_game_board(char board[][MAX_COLS], int row_size, int col_size, char symbol)
{
	int row_index = 0, col_index = 0;

	for (; row_index < row_size; ++row_index) // controls the row
	{
		for (col_index = 0; col_index < col_size; ++col_index) // controls the column
		{
			board[row_index][col_index] = symbol;
			
		
		}
	}
}

//make gameboard with randomly selected ship placement
//void adjust_game_board_w_randoms(char board[][MAX_COLS], int row_size, int col_size, char symbol)
//{
//	int row_index = 0, col_index = 0;
//	int which_case = random_number();
//
//	for (; row_index < row_size; ++row_index) // controls the row
//	{
//		for (col_index = 0; col_index < col_size; ++col_index) // controls the column
//		{
//			board[row_index][col_index] = symbol;
//			
//
//			switch (which_case)
//			{
//				case 1:
//				
//
//
//			}
//		}
//	}
//}

// shows a way to print out the the game board
void print_board(char board[][MAX_COLS], int row_size, int col_size)
{
	int row_index = 0, col_index = 0;

	printf("%3d%2d%2d%2d%2d%2d%2d%2d%2d%2d\n", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
	for (; row_index < row_size; ++row_index) // controls the row
	{
		printf("%-2d", row_index);
		for (col_index = 0; col_index < col_size; ++col_index) // controls the column
		{
			printf("%-2c", board[row_index][col_index]);
		}
		putchar('\n');
	}
}

//diplay game boards
int display_boards(void)
{

	printf("your game board: \n\n");
	char p1_board[MAX_ROWS][MAX_COLS];
	initialize_game_board(p1_board, MAX_ROWS, MAX_COLS, '~');
	print_board(*p1_board, MAX_ROWS, MAX_COLS);

	printf("\n\n");
	printf("enemy game board: \n\n");
	char p2_board[MAX_ROWS][MAX_COLS];
	initialize_game_board(p2_board, MAX_ROWS, MAX_COLS, '~');
	print_board(*p2_board, MAX_ROWS, MAX_COLS);

}




