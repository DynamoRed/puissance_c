#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <fcntl.h>
#include "libs/game.utils.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
	#include <io.h>
#elif __APPLE__
	#include <sys/uio.h>
#elif __linux__ || __unix__
	#include <sys/io.h>
#else
	#error "Unknown compiler"
#endif


/*H**********************************************************************
* FILENAME: app.c
*
* DESCRIPTION :
*       Main file of our app
*
* PUBLIC FUNCTIONS :
*       int main(...)
*
* NOTES :
*       ...command to compile
*       Copyright Groupe 19. 2022. All rights reserved.
*
* AUTHORS : Raphael BIRON, Kilian ALVES, Maram ZITOUNI, Lucas PIERRE, Corentin LECHENE
* START DATE : 06/10/2022
*
*H***********************************************************************/

int main(int argc, char *argv[]){
	_setmode(_fileno(stdout), 0x00020000);

	return EXIT_SUCCESS;
}
