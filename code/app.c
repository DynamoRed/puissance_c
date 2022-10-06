#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <fcntl.h>
#include <conio.h>
#include "libs/game.utils.h"
#include "libs/display.utils.h"

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
	wcscpy(null_player->color, CONSOLE_COLORS[4]);
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
		new_player->name = calloc(255, sizeof(wchar_t));
		wcscpy(new_player->color, CONSOLE_COLORS[i]);
		new_player->placed_pawns = 0;
		new_player->id = i;
		board->players[i] = new_player;
	}

    return board;
}

int _get_players_names(Board *board){
	wprintf(L"\e[1;1H\e[2J");
	wprintf(L"%s---=== PUISSANCE C ===---%s\n", CONSOLE_COLORS[0], CONSOLE_COLORS[5]);
	wchar_t *first = L"first";
	wchar_t *next = L"next";
	for(int i = 0; i < board->player_count; i++){
		wchar_t *name = calloc(255, sizeof(wchar_t));

		int len = 0;
		do {
			wprintf(L"\n\n\x2192 Enter %s player name: ", i == 0 ? first : next);
			wscanf(L"%s", name);
			len = wcslen(name);
			if(len < 2) wprintf(L"\n%sIncorrect name! Retry...%s\n", CONSOLE_COLORS[0], CONSOLE_COLORS[5]);
		} while(len < 2);

		wcscpy(board->players[i]->name, name);
		wprintf(L"\e[1;1H\e[2J");
		fflush(stdin);
		free(name);
		wprintf(L"Welcome onboard %s%s %s!", board->players[i]->color, board->players[i]->name, CONSOLE_COLORS[5]);
	}
	return 1;
}

int is_moving(int c) {
    return c == 77 || c == 75;
}

void _move_cursor(Board *board, int new_pos) {
    if(new_pos == 77 && board->selected_column + 1 < board->columns) {
        board->selected_column += 1;
    } else if(new_pos == 75 && board->selected_column - 1 >= 0) {
        board->selected_column -= 1;
    }
}

int _start_game(Board *board) {
    int start_game = 1;
    int event;

    event = getch();
    if(event == 80) return 0;

    if(is_moving(event)) {
        system("cls");
        _move_cursor(board, event);
        display_board(board);
    }


    return start_game;
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
    int start_game = 1;

    Board *board = _generate_board(config.rows, config.columns, config.player_count);

    display_board(board);
	if(_get_players_names(board)) {
        while (start_game) {
            start_game = _start_game(board);
        }
    } else {
		wprintf(L"\e[1;1H\e[2J");
		wprintf(L"\n%sAn error occured!");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
