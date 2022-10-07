/*H**********************************************************************
 * FILENAME: config.utils.h
 *
 * DESCRIPTION :
 *       Configurations utils for our app
 *
 * NOTES :
 *       Copyright Groupe 19. 2022. All rights reserved.
 *
 * AUTHORS : Raphael BIRON, Kilian ALVES, Maram ZITOUNI, Lucas PIERRE, Corentin LECHENE
 * START DATE : 07/10/2022
 *
 *H***********************************************************************/

/*=====================================================*/

bool get_config(Config *config, char *config_file);

/*=====================================================*/

bool get_config(Config *config, char *config_file){
	if(strlen(config_file) < strlen("app.config")) return false;

    char line[256];
    unsigned short line_number = 0;
    int i = 0, k = 0;
    FILE *file = fopen(config_file, "r");
    char *key, *value;

	if(file == NULL){
		fclose(file);
		file = fopen(config_file, "w+");
		fprintf(file, "ROWS=6\nCOLUMNS=7\nALIGN_TO_WIN=4\nPLAYER_COUNT=2\n");
		rewind(file);
	}

    while (fgets(line, 256, file) != NULL){
        line_number++;
        while (line[i] != '\0'){
            if (line[i] == 61){
                key = malloc(sizeof(char) * 256);
                value = malloc(sizeof(char) * 256);

                for (int j = 0; j < i; j++){
                    key[j] = line[j];
                }
                key[i] = '\0';

                for (k = 0; line[i + 1 + k] != '\0'; k++){
                    value[k] = line[i + 1 + k];
                }
                value[k] = '\0';

                break;
            }
            i++;
        }

        i = 0;
        k = 0;

        if (strcmp(key, "ROWS") == 0){
            config->rows = atoi(value);
        } else if (strcmp(key, "COLUMNS") == 0){
            config->columns = atoi(value);
        } else if (strcmp(key, "ALIGN_TO_WIN") == 0){
            config->align_to_win = atoi(value);
        } else if (strcmp(key, "PLAYER_COUNT") == 0){
            config->player_count = atoi(value);
        }
    }

    fclose(file);
	return true;
}
