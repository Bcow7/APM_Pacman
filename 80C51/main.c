#include <mcs51reg.h>
#include "stdio-t6963c.h"
#include "test.h"
#include "pacman.h"
#include "ghost.h"
#include "keyboard.h"
#include "gameboard.h"
#include "t6963c.h"

// PacMan

#ifndef TEST

void pause(unsigned int t) {
	unsigned int n;
	for (n = 0; n < t; n++);
}

void initialize() {
	STDIO_initialize();
	GMB_initialize();
}

void play() {
	Pacman pacman = {MOVES_NONE, {10, 10},{10,10}, ALIVE};
	Ghost ghost1 = {MOVES_NONE, {17, 7},{17,7}, HUNTER, 10};
	Ghost ghost2 = {MOVES_NONE, {17, 9},{17,9}, HUNTER, 25};
	unsigned char *keyboard = (unsigned char __xdata *) 0x3000;
	Arrow arrow;
	
	GMB_DrawLab(26,PACMAN_LIMIT_X0, PACMAN_LIMIT_Y0,PACMAN_LIMIT_X1, PACMAN_LIMIT_Y1);
	
	
	do {
		arrow = KEYBOARD_readArrows(keyboard);
	
		PACMAN_iterate(&pacman, arrow);
		GHOST_iterate(&ghost2);
	    GHOST_iterate(&ghost1);

		pause(20000);
	} while (pacman.status != DEAD);

	GMB_display(8, 7, " GAME OVER ");
}

void main(void) {

	initialize();

	play();

	while(1);
}

#else
#include <stdio.h>
void main(void) {
	int testsInError = 0;
	STDIO_initialize();

	testsInError += testGameboard();
	testsInError += testPacman();
	testsInError += testGhost();

	printf("%d tests en erreur", testsInError);

	while(1);
}
#endif
