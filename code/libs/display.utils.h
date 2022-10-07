/*H**********************************************************************
 * FILENAME: display.utils.h
 *
 * DESCRIPTION :
 *       Utils display functions for our app
 *
 * NOTES :
 *       Copyright Groupe 19. 2022. All rights reserved.
 *
 * AUTHORS : Raphael BIRON, Kilian ALVES, Maram ZITOUNI, Lucas PIERRE, Corentin LECHENE
 * START DATE : 07/10/2022
 *
 *H***********************************************************************/

/*=====================================================*/

void clear_console();
void display_board(Board *board);
void _display_player(Player *player);
void _display_winner(Player *winner);
void _display_cursor(Board *board);
void _display_board_header(Board *board);
void _display_board_footer(Board *board);

/*=====================================================*/

void clear_console() {
    wprintf(L"\e[1;1H\e[2J");
}

void _display_player(Player *player){
    wprintf(L"It's %s%s  %s%s's turn:\n\n", player->color, SPECIALS_CHARS[2], player->name, CONSOLE_COLORS[5]);
}

void _display_winner(Player *winner){
    wprintf(L"%s%s%s  %s %swon in %d turns !%s\n\n\n", CONSOLE_COLORS[6], SPECIALS_CHARS[0], winner->color, winner->name, CONSOLE_COLORS[6], winner->placed_pawns, CONSOLE_COLORS[5]);
}

void _display_cursor(Board *board){
    wprintf(L"  ");
    for(short i = 0 ; i <= board->columns ; i++) {
        if(board->selected_column == i) {
            wprintf(L"%s%s%s", board->turn_of->color, SPECIALS_CHARS[1], CONSOLE_COLORS[5]);
            break;
        } else {
            wprintf(L"    ");
        }
    }
    wprintf(L"\n");
}

void _display_board_header(Board *board){
	if(board->winner->name != NULL) {
        _display_winner(board->winner);
    } else {
        _display_player(board->turn_of);
        _display_cursor(board);
    }

	for(short i = 0; i < board->columns; i++){
		if(i == 0) wprintf(L"╒");
		else wprintf(L"╤");

		if(board->map[0][i] != -1 || board->winner->id != -1) wprintf(L"═══");
		else wprintf(L"   ");

		if(i == board->columns-1) wprintf(L"╕\n");
	}
}

void _display_board_footer(Board *board){
	for(short i = 0; i < board->columns; i++){
		if(i == 0) wprintf(L"╘");
		else wprintf(L"╧");
		wprintf(L"═══");
		if(i == board->columns-1) wprintf(L"╛\n");
	}

	wprintf(L"\n\n═════════════════════════════════════════════════════════\n");
	wprintf(L"    %s• Use your arrows '<-' and '->' to move your pawn\n    • Press 'Enter' to validate your choice\n    • Press 'Esc' to quit the game%s\n", CONSOLE_COLORS[6], CONSOLE_COLORS[5]);
	wprintf(L"═════════════════════════════════════════════════════════\n");
}

void display_board(Board *board){
	clear_console();
    _display_board_header(board);

    for (int i = 0; i < board->rows; ++i) {
        int index = 0;
        for (int j = 0; j <= board->columns * 2; ++j) {
            if(j % 2 == 0) {
                wprintf(L"│");
            } else {
                int t = board->map[i][index++];
                if(t == -1) {
                    wprintf(L"   ");
                } else {
                    wprintf(L" %s%s%s ", board->players[t]->color, SPECIALS_CHARS[1], CONSOLE_COLORS[5]);
                }
            }
        }
        wprintf(L"\n");
    }

	_display_board_footer(board);
}
