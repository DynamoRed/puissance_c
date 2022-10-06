
void _display_cursor(Board *board) {
    wprintf(L"  ");
    for(int i = 0 ; i <= board->columns ; i++) {
        if(board->selected_column == i) {
            wprintf(L"0");
            break;
        } else {
            wprintf(L"    ");
        }
    }
    wprintf(L"\n");
}

void display_board(Board *board) {
    _display_cursor(board);
    for (int i = 0; i < board->rows; ++i) {
        for (int j = 0; j <= board->columns * 2; ++j) {
            if(j % 2 == 0) {
                wprintf(L"|");
            } else {
                wprintf(L"   ");
            }
        }
        wprintf(L"\n");
    }
}