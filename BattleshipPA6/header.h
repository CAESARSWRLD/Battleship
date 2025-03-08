#ifndef SEARCHES_SORTS_H
#define SEARCHES_SORTS_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h> // strlen (), strcpy (), strncpy (), strcat (), strncat (),
// strcmp (), strtok ()
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "stats.h" 


#define MAX_ROWS 10
#define MAX_COLS 10

#define CARRIER_LENGTH 5
#define BATTLESHIP_LENGTH 4
#define CRUISER_LENGTH 3
#define SUBMARINE_LENGTH 3
#define DESTROYER_LENGTH 2


// the below declarations help w/ Battleship
int game_loop(void);


void initialize_game_board(char board[][MAX_COLS], int row_size, int col_size, char symbol);
void print_board(char board[][MAX_COLS], int row_size, int col_size);


void random_placement(char board[][MAX_COLS], int ship, char symbol);
int welcome_options();
void print_rules();
void clear_the_screen();
void prompt_continue();



void place_rand_ships(char board[][MAX_COLS]);
void place_ships_manually(char board[][MAX_COLS]);

int place_ship(char board[][MAX_COLS], char ship_type, int ship_length);



void p_two_board_hidden(char board[][MAX_COLS], char p2_board_h[][MAX_COLS], int bomb_x, int bomb_y, bool hidden_board_created, int* one_hits, int* one_misses, int* two_hits, int* two_misses, int player_turn, Stats* player1_stats, Stats* player2_stats);
int check_for_winner(char board[][MAX_COLS]);








#endif