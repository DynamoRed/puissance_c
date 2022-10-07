/*H**********************************************************************
 * FILENAME: game.utils.h
 *
 * DESCRIPTION :
 *       Utils components for our app
 *
 * NOTES :
 *       Copyright Groupe 19. 2022. All rights reserved.
 *
 * AUTHORS : Raphael BIRON, Kilian ALVES, Maram ZITOUNI, Lucas PIERRE, Corentin LECHENE
 * START DATE : 06/10/2022
 *
 *H***********************************************************************/

/*=====================================================*/

bool start_game(Board *board);
Board *generate_board(Config *config);
bool _move_cursor(Board *board, int move_to);
bool _put_pawn(Board *board);
bool _is_out_of_bound(int y, int x, int rows, int cols);
bool _verify_winner(Board *board);
int _verif_winner_y(Board *board, int column);
int _verif_winner_x(Board *board, int row);
int _verif_winner_diag(Board *board, int row, int column);

/*=====================================================*/

bool _move_cursor(Board *board, int move_to){
	if((move_to == 77 && board->selected_column +1 >= board->columns) || (move_to == 75 && board->selected_column-1 < 0)) return false;

    if(move_to == 77) board->selected_column += 1;
    else if(move_to == 75) board->selected_column -= 1;

	return true;
}

bool _put_pawn(Board *board){
    int index = 0;

    while (board->map[index][board->selected_column] == -1) {
        if(index == board->rows - 1) break;
        index++;
    }
    if(!index) return false;

    if(index == board->rows - 1 && board->map[index][board->selected_column] == -1) index++;
    board->map[index - 1][board->selected_column] = board->turn_of->id;
	board->turn_of->placed_pawns++;

    if(board->turn_of->id + 1 >= board->player_count) board->turn_of = board->players[0];
    else board->turn_of = board->players[board->turn_of->id + 1];

	board->selected_column = 0;
	return true;
}

Board *generate_board(Config *config){
	Board *board = malloc(sizeof(Board));

	board->config = config;

	board->columns = config->columns;
	board->rows = config->rows;
	board->map = calloc(config->rows, sizeof(short *));
	for(short i = 0; i < config->rows; i++){
		board->map[i] = calloc(config->columns, sizeof(short));
		for(short y = 0; y < config->columns; y++) board->map[i][y] = -1;
	}
	board->selected_column = 0;

	Player *null_player = malloc(sizeof(Player));
	null_player->name = NULL;
	wcscpy(null_player->color, CONSOLE_COLORS[1]);
	null_player->id = -1;
	null_player->placed_pawns = -1;

    board->player_count = config->player_count;
    board->players = calloc(config->player_count+1, sizeof(Player));

    for(short i = 0; i < config->player_count; i++){
        Player *new_player = calloc(1, sizeof(Player));
        new_player->name = calloc(255, sizeof(wchar_t));
        wcscpy(new_player->color, CONSOLE_COLORS[2+i]);
        new_player->placed_pawns = 0;
        new_player->id = i;
        board->players[i] = new_player;
    }

    board->turn_of = board->players[0];
    board->winner = calloc(1, sizeof(Player));
    board->winner = null_player;
    board->null_match = false;

	board->players[config->player_count] = null_player;

    return board;
}

int _verif_winner_y(Board *board, int column){
    for(short y = 0; y < board->rows; y++){
        if(board->map[y][column] != -1){
            int player = board->map[y][column];
            int count = 1;

            while (y < board->rows && board->map[y][column] == player){
                if(count >= board->config->align_to_win) return player;

                count++;
                y++;
            }
        }
    }
    return -1;
}

int _verif_winner_x(Board *board, int row){
    for(int x = 0; x < board->columns; x++){
        if(board->map[row][x] != -1){
            int player = board->map[row][x];
            int count = 1;

            while (x < board->columns && board->map[row][x] == player){
                if(count >= board->config->align_to_win) return player;

                count++;
                x++;
            }
        }
    }
    return -1;
}

bool _is_out_of_bound(int y, int x, int rows, int cols){
	return x >= cols || y >= rows;
}

int _verif_winner_diag(Board *board, int row_input, int column_input){
	if (board->map[row_input][column_input] != -1){
		int player = board->map[row_input][column_input];
		int count = 1;
		int row = row_input + 1, col = column_input + 1;

		while(!_is_out_of_bound(row, col, board->rows, board->columns) && board->map[row][col] == player){
			row += 1;
			col += 1;
			count += 1;

			if(count >= board->config->align_to_win) return player;
		}

		count = 1;
		row = row_input + 1;
		col = column_input - 1;

		while (!_is_out_of_bound(row, col, board->rows, board->columns) && board->map[row][col] == player){
			row += 1;
			col -= 1;
			count += 1;
			if(count >= board->config->align_to_win) return player;
		}
	}

	return -1;
}

bool _verify_winner(Board *board) {
    int winner = -1;

    for(int i = 0; i < board->rows; ++i){
        winner = _verif_winner_x(board, i);
        if(winner != -1) {
            board->winner = board->players[winner];
            return true;
        }
    }

    for(int i = 0; i < board->columns; ++i){
        winner = _verif_winner_y(board, i);
        if(winner != -1){
            board->winner = board->players[winner];
            return true;
        }
    }

	for (int i = 0; i < board->rows; i++){
		for (int y = 0; y < board->columns; y++){
			winner = _verif_winner_diag(board, i, y);
			if(winner != -1){
				board->winner = board->players[winner];
				return true;
			}
		}
	}

	int last_null = 0;

	for (int i = 0; i < board->rows; i++){
		for (int y = 0; y < board->columns; y++){
			if(board->map[i][y] == -1) last_null++;
		}
	}

	board->null_match = !last_null;

    return board->null_match;
}

bool run_game(Board *board){
    int event = getch();

	switch(event){
		case 77:
		case 75:
			if(_move_cursor(board, event)) display_board(board);
			break;

		case 13:
			if(_put_pawn(board)){
				if (_verify_winner(board)) {
					display_board(board);
					return false;
				}
				display_board(board);
			}
			break;

		case 27:
			return false;
	}

    return true;
}
