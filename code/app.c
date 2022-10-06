#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <fcntl.h>
#include "libs/game.utils.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
	#include <io.h>
#elif __APPLE__
	#include <sys/uio.h>
#elif __linux__ || __unix__
	#include <sys/io.h>
#else
	#error "Unknown compiler"
#endif


/*H**********************************************************************
* FILENAME: app.c
*
* DESCRIPTION :
*       Main file of our app
*
* PUBLIC FUNCTIONS :
*       int main(...)
*
* NOTES :
*       ...command to compile
*       Copyright Groupe 19. 2022. All rights reserved.
*
* AUTHORS : Raphael BIRON, Kilian ALVES, Maram ZITOUNI, Lucas PIERRE, Corentin LECHENE
* START DATE : 06/10/2022
*
*H***********************************************************************/

Board *_generate_board(unsigned short rows, unsigned short columns, unsigned short player_count){
	Board *board = malloc(sizeof(Board));

	board->columns = columns;
	board->rows = rows;
	board->map = calloc(rows, sizeof(int *));
	for(int i = 0; i < rows; i++){
		board->map[i] = calloc(columns, sizeof(int));
		for(int y = 0; y < columns; y++) board->map[i][y] = -1;
	}
	board->selected_column = 0;

	Player *null_player = malloc(sizeof(Player));
	null_player->name = NULL;
	strcpy(null_player->color, CONSOLE_COLORS[4]);
	null_player->id = -1;
	null_player->placed_pawns = -1;

	board->player_count = player_count;
	board->players = calloc(player_count+1, sizeof(Player));
	board->turn_of = 0;
	board->winner = calloc(1, sizeof(Player));
	board->winner = null_player;

	board->players[player_count] = null_player;
	for(int i = 0; i < player_count; i++){
		Player *new_player = calloc(1, sizeof(Player));
		new_player->name = NULL;
		strcpy(new_player->color, CONSOLE_COLORS[i]);
		new_player->placed_pawns = 0;
		new_player->id = i;
		board->players[i] = new_player;
	}

	return board;
}

int main(int argc, char *argv[]){
	_setmode(_fileno(stdout), 0x00020000);

	// INIT CONFIG
	Config config = {
		.rows = 6,
		.columns = 7,
		.align_to_win = 4,
		.player_count = 4
	};

	Board *board = _generate_board(config.rows, config.columns, config.player_count);

	return EXIT_SUCCESS;
}
