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

int start_game(Board *board);
Board *generate_board(Config *config);
int _move_cursor(Board *board, int move_to);
int _put_pawn(Board *board);

/*=====================================================*/

int _move_cursor(Board *board, int move_to){
	if((move_to == 77 && board->selected_column +1 >= board->columns) || (move_to == 75 && board->selected_column-1 < 0)) return 0;

    if(move_to == 77) board->selected_column += 1;
    else if(move_to == 75) board->selected_column -= 1;

	return 1;
}

int _put_pawn(Board *board){
    int index = 0;

    while (board->map[index][board->selected_column] == -1) {
        if(index == board->rows - 1) break;
        index++;
    }
    if(index == 0) return 0;

    if(index == board->rows - 1 && board->map[index][board->selected_column] == -1) index++;
    board->map[index - 1][board->selected_column] = board->turn_of->id;

    if(board->turn_of->id + 1 >= board->player_count) board->turn_of = board->players[0];
    else board->turn_of = board->players[board->turn_of->id + 1];

	board->selected_column = 0;
	return 1;
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
	wcscpy(null_player->color, CONSOLE_COLORS[4]);
	null_player->id = -1;
	null_player->placed_pawns = -1;

    board->player_count = config->player_count;
    board->players = calloc(config->player_count+1, sizeof(Player));

    for(int i = 0; i < config->player_count; i++){
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

	board->players[config->player_count] = null_player;

    return board;
}

int run_game(Board *board){
    int event = getch();

	switch(event){
		case 77:
		case 75:
			if(_move_cursor(board, event)) display_board(board);
			break;

		case 13:
			if(_put_pawn(board)) display_board(board);
			break;

		case 27:
			return 0;
	}

    return 1;
}
