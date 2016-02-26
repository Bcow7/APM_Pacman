#include <mcs51reg.h>
#include "stdio-t6963c.h"
#include "test.h"
#include "buffer.h"
#include "pacman.h"
#include "ghost.h"
#include "keyboard.h"
#include "gameboard.h"

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
	Ghost ghost2 = {MOVES_NONE, {17, 8},{17,8}, HUNTER, 25};
	unsigned char *keyboard = (unsigned char __xdata *) 0x3000;
	Arrow arrow;

	GMB_draw(PACMAN_LIMIT_X0, PACMAN_LIMIT_Y0, PACMAN_LIMIT_X1, PACMAN_LIMIT_Y1);
	
	do {
		arrow = KEYBOARD_readArrows(keyboard);
	
		PACMAN_iterate(&pacman, arrow);
		GHOST_iterate(&ghost1);
	        GHOST_iterate(&ghost2);

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

	//testsInError += testBuffer();
	//testsInError += testSnake();
	//testsInError += testKeyboard();
	//testsInError += testFruit();
	testsInError += testGameboard();
	testsInError += testPacman();
	testsInError += testGhost();

	printf("%d tests en erreur", testsInError);

	while(1);
}
#endif
