void _display_player(Board *board) {
    wprintf(L"%s%s %s%s\n", board->turn_of->color, SPECIALS_CHARS[2], board->turn_of->name, CONSOLE_COLORS[5]);
}

void display_winner(Board *board) {
    wprintf(L"%s%s %s a gagné %s\n", board->turn_of->color, SPECIALS_CHARS[0], board->turn_of->name, CONSOLE_COLORS[5]);
}

void _display_cursor(Board *board) {
    wprintf(L"  ");
    for(int i = 0 ; i <= board->columns ; i++) {
        if(board->selected_column == i) {
            wprintf(L"%s%s%s", board->turn_of->color, SPECIALS_CHARS[1], CONSOLE_COLORS[5]);
            break;
        } else {
            wprintf(L"    ");
        }
    }
    wprintf(L"\n");
}

void display_board(Board *board) {
    _display_player(board);
    _display_cursor(board);
    for (int i = 0; i < board->rows; ++i) {
        int index = 0;
        for (int j = 0; j <= board->columns * 2; ++j) {
            if(j % 2 == 0) {
                wprintf(L"|");
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
}
void clear_console() {
    system("cls");
}
