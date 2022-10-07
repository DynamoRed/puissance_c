#include "game.utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void get_config(Config *config)
{
    char line[256];
    int line_number = 0;
    int i = 0, k = 0;
    FILE *file = fopen("app.config", "r");
    char *key, *value;

    while (fgets(line, 256, file) != NULL)
    {

        line_number++;
        while (line[i] != '\0')
        {
            if (line[i] == 61)
            {

                key = malloc(sizeof(char) * 256);
                value = malloc(sizeof(char) * 256);

                for (int j = 0; j < i; j++)
                {
                    key[j] = line[j];
                }
                key[i] = '\0';

                for (k = 0; line[i + 1 + k] != '\0'; k++)
                {
                    value[k] = line[i + 1 + k];
                }
                value[k] = '\0';

                break;
            }
            i++;
        }
        i = 0;
        k = 0;
        if (strcmp(key, "rows") == 0)
        {
            config->rows = atoi(value);
        }
        else if (strcmp(key, "columns") == 0)
        {
            config->columns = atoi(value);
        }
        else if (strcmp(key, "align_to_win") == 0)
        {
            config->align_to_win = atoi(value);
        }
        else if (strcmp(key, "player_win") == 0)
        {
            config->player_count = atoi(value);
        }
    }

    fclose(file);
}