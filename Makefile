CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Werror

LIB =

BIN = ./code/app.c

DEST = ./executable/app.exe

all:
	${CC} ${CFLAGS} ${BIN} -o ${DEST} ${LIB}

clean:
	${RM} ${OBJ} ${DEST}
