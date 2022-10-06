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

// RED / GREEN / BLUE / VIOLET / BLACK / WHITE
static wchar_t *CONSOLE_COLORS[] = {L"\033[0;31m", L"\033[0;32m", L"\033[0;34m", L"\033[0;35m", L"\033[0;30m", L"\033[0;37m"};
// 0: ♕ - 1: ⦿ - 2: ♟ - 3:→
static wchar_t *SPECIALS_CHARS[] = {L"\x2655", L"\x29BF", L"\x265F", L"\x2192"};

typedef struct {
	int rows;
	int columns;
	int align_to_win;
	int player_count;
} Config;

typedef struct {
    wchar_t *name;
    wchar_t color[11];
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
