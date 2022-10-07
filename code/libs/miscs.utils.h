/*H**********************************************************************
 * FILENAME: miscs.utils.h
 *
 * DESCRIPTION :
 *       Miscellaneous things for our app
 *
 * NOTES :
 *       Copyright Groupe 19. 2022. All rights reserved.
 *
 * AUTHORS : Raphael BIRON, Kilian ALVES, Maram ZITOUNI, Lucas PIERRE, Corentin LECHENE
 * START DATE : 07/10/2022
 *
 *H***********************************************************************/

/*=====================================================*/

// RESET / BLACK / RED / GREEN / VIOLET / CYAN / YELLOW / BLUE
static wchar_t *CONSOLE_COLORS[] = {L"\033[0;0m", L"\033[0;30m", L"\033[0;31m", L"\033[0;32m", L"\033[0;33m", L"\033[0;34m", L"\033[0;35m", L"\033[0;36m"};
// 0: '♕' - 1: '⦿' - 2: '♟' - 3: '→'
static wchar_t *SPECIALS_CHARS[] = {L"\x2655", L"\x29BF", L"\x265F", L"\x2192"};

/*=====================================================*/

typedef struct {
	unsigned short rows;
	unsigned short columns;
	unsigned short align_to_win;
	unsigned short player_count;
} Config;

typedef struct {
    wchar_t *name;
    wchar_t color[11];
    unsigned short id;
    unsigned short placed_pawns;
} Player;

typedef struct {
    short **map;
    unsigned short rows;
    unsigned short columns;
    Player *turn_of;
    Player *winner;
    unsigned short player_count;
    Player **players;
    unsigned short selected_column;
	Config *config;
	bool null_match;
} Board;
