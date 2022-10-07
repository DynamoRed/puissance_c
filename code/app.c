#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <wchar.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <io.h>
#include <conio.h>
#include <winsock2.h>
#else
#error "Unsupported compiler (Windows only)"
#endif

#include "libs/miscs.utils.h"
#include "libs/display.utils.h"
#include "libs/game.utils.h"
#include "libs/config.utils.h"


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

/*=====================================================*/

int main(int argc, char *argv[]);
bool _get_players_names(Board *board);
int end(Board *board, Config *config, int failure);

/*=====================================================*/

int main(int argc, char *argv[]){
    _setmode(1, 0x00020000);

	unsigned short socket_mode = 0;

	for(int i = 0; i < argc && !socket_mode; i++){
		if(strcmp(argv[i], "-c") == 0) socket_mode = 1;
		if(strcmp(argv[i], "-s") == 0) socket_mode = 2;
	}

	bool game_run = true;
    Config *config = calloc(1, sizeof(Config));
	Board *board = calloc(1, sizeof(Board));
	config->mode = socket_mode;

	if(!get_config(config, "app.config")){
		wprintf(L"%sInvalid app.config file!%s", CONSOLE_COLORS[2], CONSOLE_COLORS[0]);
		return end(NULL, config, 1);
	}

	if(config->rows < 2 || config->columns < 2 || config->align_to_win < 2 || config->player_count < 2){
		wprintf(L"%sInvalid configuration! (Every field must be at least equal to 2)%s", CONSOLE_COLORS[2], CONSOLE_COLORS[0]);
		return end(NULL, config, 1);
	}

	if(config->player_count > 5){
		wprintf(L"%sYou can play with up to 5 players maximum!%s", CONSOLE_COLORS[2], CONSOLE_COLORS[0]);
		return end(NULL, config, 1);
	}

	if(config->rows < config->align_to_win || config->columns < config->align_to_win){
		wprintf(L"%sInvalid rows or columns values! Your rows and columns must be at least equal to ALIGN_TO_WIN%s", CONSOLE_COLORS[2], CONSOLE_COLORS[0]);
		return end(NULL, config, 1);
	}

	board = generate_board(config);

    if(_get_players_names(board)){
        display_board(board);
        while(game_run) game_run = run_game(board);
    } else {
		wprintf(L"%sAn error occured!%s", CONSOLE_COLORS[2], CONSOLE_COLORS[0]);
		return end(board, NULL, 1);
	}

    return end(board, NULL, 0);
}

int end(Board *board, Config *config, int failure){
	if(config != NULL) free(config);
	if(board != NULL){
		for(int i = 0; i < board->player_count; i++){
			free(board->players[i]->name);
			free(board->players[i]);
		}

		for(int i = 0; i < board->rows; i++) free(board->map[i]);

		free(board->winner->name);
		free(board->winner);
		free(board->turn_of->name);
		free(board->turn_of);
		if(config == NULL) free(board->config);
		free(board);
	}

	return failure;
}

bool _get_players_names(Board *board){
	clear_console();
	wchar_t *local = L"Local Multiplayer";
	wchar_t *host = L"Host";
	wchar_t *guest = L"Guest";

	wprintf(L"%s---=== PUISSANCE C (%s) ===---%s", CONSOLE_COLORS[4], board->config->mode ? (board->config->mode == 1 ? guest : host) : local, CONSOLE_COLORS[0]);
	wchar_t *first = L"the first";
	wchar_t *next = L"next";
	for(short i = 0; i < board->player_count; i++){
		wchar_t *name = calloc(255, sizeof(wchar_t));

		bool correct = false;
		do {
			correct = true;
			wprintf(L"\n\n\x2192 Enter %s player name: %s", i == 0 ? first : next, board->players[i]->color);
			wscanf(L"%s", name);
			int len = wcslen(name);
			if(len < 2){
				wprintf(L"\n%sIncorrect name! Retry...%s\n", CONSOLE_COLORS[2], CONSOLE_COLORS[0]);
				correct = false;
			}
			for(short y = 0; y < board->player_count; y++){
				if(wcscmp(board->players[y]->name, name) == 0){
					wprintf(L"\n%sThis name is already taken! Retry...%s\n", CONSOLE_COLORS[2], CONSOLE_COLORS[0]);
					correct = false;
					break;
				}
			}
		} while(!correct);

		wcscpy(board->players[i]->name, name);
		clear_console();
		fflush(stdin);
		free(name);
		wprintf(L"%sWelcome onboard %s%s %s!", CONSOLE_COLORS[0], board->players[i]->color, board->players[i]->name, CONSOLE_COLORS[0]);
	}

	clear_console();
	return true;
}
