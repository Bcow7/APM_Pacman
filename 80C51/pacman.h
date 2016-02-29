#ifndef __PACMAN_H
#define __PACMAN_H

#include "keyboard.h"
#include "main.h"
#include "stdbool.h"

#define NB_OF_COINS_TO_EAT 231 // nombre de pièce 231

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
	EATING,
	WON
} Status;

typedef struct {
	Direction direction;
	Position position;
	Position lastPosition;
	Status status;
	unsigned char eatenCoins;
} Pacman;

bool PACMAN_isFreeSpace(unsigned char x, unsigned char y);
void PACMAN_move(Pacman *pacman);
void PACMAN_liveOrDie(Pacman *pacman);
void PACMAN_show(Pacman *pacman);
void PACMAN_turn(Pacman *pacman, Arrow arrow);
Status PACMAN_iterate(Pacman *pacman, Arrow arrow);

#ifdef TEST
int testPacman();
#endif

#endif
