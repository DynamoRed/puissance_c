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

Board *_generate_board(Config *config){
	Board *board = malloc(sizeof(Board));

	board->config = config;

	board->columns = board->config->columns;
	board->rows = board->config->rows;
	board->map = calloc(board->rows, sizeof(short *));
	for(short i = 0; i < board->rows; i++){
		board->map[i] = calloc(board->columns, sizeof(short));
		for(short y = 0; y < board->columns; y++) board->map[i][y] = -1;
	}
	board->selected_column = 0;

    Player *null_player = malloc(sizeof(Player));
    null_player->name = NULL;
    wcscpy(null_player->color, CONSOLE_COLORS[4]);
    null_player->id = -1;
    null_player->placed_pawns = -1;

	board->player_count = board->config->player_count;
	board->players = calloc(board->player_count+1, sizeof(Player));
	board->turn_of = 0;
	board->winner = calloc(1, sizeof(Player));
	board->winner = null_player;

	board->players[board->player_count] = null_player;
	for(short i = 0; i < board->player_count; i++){
		Player *new_player = calloc(1, sizeof(Player));
		new_player->name = calloc(255, sizeof(wchar_t));
		wcscpy(new_player->color, CONSOLE_COLORS[i]);
		new_player->placed_pawns = 0;
		new_player->id = i;
		board->players[i] = new_player;
	}

    board->turn_of = board->players[0];
    board->winner = calloc(1, sizeof(Player));
    board->winner = null_player;

    board->players[player_count] = null_player;

    return board;
}

int _get_players_names(Board *board){
	wprintf(L"\e[1;1H\e[2J");
	wprintf(L"%s---=== PUISSANCE C ===---%s\n", CONSOLE_COLORS[0], CONSOLE_COLORS[5]);
	wchar_t *first = L"first";
	wchar_t *next = L"next";
	for(short i = 0; i < board->player_count; i++){
		wchar_t *name = calloc(255, sizeof(wchar_t));

		short len = 0;
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
	wprintf(L"\e[1;1H\e[2J");
	return 1;
}

int is_moving(int c) {
    return c == 77 || c == 75;
}

int is_put_pawn(int c) {
    return c == 13;
}

int _verif_winner_y(Board *board, int columns) {
    for (int y = 0; y < board->rows; y++) {
        if (board->map[y][columns] != -1) {
            int player = board->map[y][columns];
            int count = 0;

            while (board->map[y + 1][columns] == player && y + 1 < board->rows) {
                if (count == 4) {
                    return 1;
                }

                count++;
            }

        }
    }

    return 0;
}

int _verif_winner_x(Board *board, int rows) {
    for (int x = 0; x < board->columns; x++) {
        if (board->map[rows][x] != -1) {
            int player = board->map[rows][x];
            int count = 0;

            while (board->map[rows][x + 1] == player && x + 1 < board->columns) {
                if (count == 4) {
                    return 1;
                }

                count++;
            }

        }
    }

    return 0;

}

int _verif_winner(Board *board) {
    int index = 0;
    for (int i = 0; i < board->rows; ++i) {
        int value = board->rows[i][j];
        for (int j = i + 1; j <= board->columns; ++j) {
            if(value == board->rows[i][j]) {
                index++;
            }
            if(index == board->align_to_win) {
                return value;
            }
        }
    }
    return -1;
}

void _move_cursor(Board *board, int new_pos) {
    if (new_pos == 77 && board->selected_column + 1 < board->columns) {
        board->selected_column += 1;
    } else if (new_pos == 75 && board->selected_column - 1 >= 0) {
        board->selected_column -= 1;
    }
}

void _put_pawn(Board *board) {
    int selected_column = board->selected_column;
    int index = 0;

    while (board->map[index][selected_column] == -1) {
        if (index == board->rows - 1) {
            break;
        }
        index++;
    }

    if (index == 0) {
        return;
    }

    if (index == board->rows - 1 && board->map[index][selected_column] == -1) {
        index++;
    }

    board->map[index - 1][selected_column] = board->turn_of->id;

    if (board->turn_of->id + 1 >= board->player_count) {
        board->turn_of = board->players[0];
    } else {
        board->turn_of = board->players[board->turn_of->id + 1];
    }
}

int _start_game(Board *board) {
    int event;

    event = getch();
    if (event == 80) return 0;

    if (is_moving(event)) {
        clear_console();
        _move_cursor(board, event);
        if(_verif_winner_x(board, 0) || _verif_winner_x(board, 1)) {
            return 0;
        }
        display_board(board);
    }

    if (is_put_pawn(event)) {
        clear_console();
        _put_pawn(board);
        display_board(board);
    }


    return 1;
}


int main(int argc, char *argv[]) {
    _setmode(_fileno(stdout), 0x00020000);

	// INIT CONFIG
	Config *config = calloc(1, sizeof(Config));
	config->rows = 6;
	config->columns = 7;
	config->align_to_win = 4;
	config->player_count = 2;

	if(config->rows < 2 || config->columns < 2 || config->align_to_win < 2 || config->player_count < 2){
		wprintf(L"%sInvalid configuration! (Every field must be at least equal to 2)%s", CONSOLE_COLORS[0], CONSOLE_COLORS[5]);
		return EXIT_FAILURE;
	}

	Board *board = _generate_board(config);


    //
    //board->map[0][5] = 1;
    //board->map[4][0] = 1;

    if (_get_players_names(board)) {
        clear_console();
        display_board(board);
        while (start_game) {
            start_game = _start_game(board);
        }
    } else {
        wprintf(L"%sAn error occured!", CONSOLE_COLORS[1]);
        return EXIT_FAILURE;
    }

	return EXIT_SUCCESS;
}
