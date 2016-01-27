#ifndef __PACMAN_H
#define __PACMAN_H

#include "keyboard.h"
#include "main.h"

typedef enum {
	MOVES_NONE,
	MOVES_UP,
	MOVES_DOWN,
	MOVES_LEFT,
	MOVES_RIGHT
} Direction;

typedef enum {
	ALIVE,
	DEAD,
	EATING
} Status;

typedef struct {
	Direction direction;
	Position position;
	Position lastPosition;
	Status status;
} Pacman;

void PACMAN_move(Pacman *pacman);
void PACMAN_liveOrDie(Pacman *pacman);
void PACMAN_show(Pacman *pacman);
void PACMAN_turn(Pacman *pacman, Arrow arrow);
Status PACMAN_iterate(Pacman *pacman, Arrow arrow);

#ifdef TEST
int testPacman();
#endif

#endif
