#ifndef __GHOST_H
#define __GHOST_H

#include "keyboard.h"
#include "main.h"
#include "pacman.h"


typedef enum {
	HUNTER,
	HUNTED,
} GhostStatus;

typedef struct {
	Direction direction;
	Position position;
	Position lastPosition;
	unsigned char lastPositionWasACoin;
	GhostStatus status;
} Ghost;

bool GHOST_isFreeSpace(unsigned char x, unsigned char y);
void GHOST_move(Ghost *ghost);
void GHOST_show(Ghost *ghost);
void GHOST_turnRandomDirection(Ghost *ghost);
Status GHOST_iterate(Ghost *ghost);

#ifdef TEST
int testGhost();
#endif

#endif
