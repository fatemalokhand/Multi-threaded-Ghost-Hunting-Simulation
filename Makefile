OPT = -Wall -Wextra
OBJ = main.o ghost.o room.o house.o hunter.o logger.o utils.o evidence.o

fp:			${OBJ}
			gcc ${OPT} -g -o fp ${OBJ}

main.o:		main.c defs.h
			gcc ${OPT} -c main.c

ghost.o:	ghost.c defs.h
			gcc ${OPT} -c ghost.c

room.o:		room.c defs.h
			gcc ${OPT} -c room.c

house.o:	house.c defs.h
			gcc ${OPT} -c house.c

hunter.o:	hunter.c defs.h
			gcc ${OPT} -c hunter.c

logger.o:	logger.c defs.h
			gcc ${OPT} -c logger.c

utils.o:	utils.c defs.h
			gcc ${OPT} -c utils.c

evidence.o:	evidence.c defs.h
			gcc ${OPT} -c evidence.c

clean:
			rm -f ${OBJ}