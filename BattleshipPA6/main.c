#include "header.h"
#include "stats.h" 

/*
	AU: Dylan Hale

	Desc: This program simulates the battleship boardgame. It allows the user to 
	play against a computer that will randomly place it's ships and randomly attacks
	cells on the user's gameboard. Once all of the ships on one player's board are gone,
	the game ends.

	It also logs each move into the battleship.log file.
*/


int main(void)
{
	int option = 0;

	while (option != 3) 
	{
		int option = welcome_options();//prompts user with menu choice input. loop continues based on input

		if (option == 1)
		{
			game_loop();
		}
		else if (option == 2)
		{
			print_rules();
		}
		else if (option == 3)
		{
			printf("GOODBYE");
			exit(0);
		}

	}

}