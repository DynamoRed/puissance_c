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

static char *CONSOLE_COLORS[] = {"\033[0;31m", "\033[0;32m", "\033[0;34m", "\033[0;35m", "\033[0;30m"};
// 0: ♕ - 1: ⦿ - 2: ♟
static wchar_t *SPECIALS_CHARS[] = {L"\x2655", L"\x29BF", L"\x265F"};

typedef struct {
	int rows;
	int columns;
	int align_to_win;
	int player_count;
} Config;

typedef struct {
    char *name;
    char color[11];
    int id;
    int placed_pawns;
} Player;

typedef struct {
    int **map;
    int rows;
    int columns;
    Player *turn_of;
    Player *winner;
    int player_count;
    Player **players;
    int selected_column;
} Board;
