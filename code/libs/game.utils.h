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

typedef struct {
    char *name;
    char *color;
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
    int selected_columns;
} Board;
