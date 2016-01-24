#include <stdlib.h>
#include "main.h"
#include "coin.h"
#include "t6963c.h"
#include "gameboard.h"
#include "test.h"

/**
 * Place un COIN à la position indiquée.
 * Si la position indiquée n'est pas libre, la fonction
 * cherche un endroit voisin qui soit libre.
 * @param position Position pour placer le COIN. Si nécessaire
 * le paramètre est mis à jour avec la position effective du COIN.
 */
void COIN_placeInFreeSpace(Position *position) 
{	
   //A créer
}

/**
 * Calcule une position aléatoire pour placer un COIN.
 * La fonction dois vérifier si la position est libre. 
 * elle ne dépasse pas le rectangle défini par les constantes 
 * PACMAN_LIMIT_X0, PACMAN_LIMIT_Y0 et PACMAN_LIMIT_X1, PACMAN_LIMIT_Y1.
 * @param position Paramètre de sortie, avec la position du COIN.
 */
void COIN_random(Position *position) 
{
	position->x = rand() % (PACMAN_LIMIT_X1 - PACMAN_LIMIT_X0) + PACMAN_LIMIT_X0;
	position->y = rand() % (PACMAN_LIMIT_Y1 - PACMAN_LIMIT_Y0) + PACMAN_LIMIT_Y0;
}

/**
 * Affiche un COIN à une position aléatoire, libre, et à l'intérieur
 * du rectangle de jeu défini par 
 * PACMAN_LIMIT_X0, PACMAN_LIMIT_Y0 et PACMAN_LIMIT_X1, PACMAN_LIMIT_Y1.
 */
void COIN_place() {
	Position position;
	COIN_random(&position);
	COIN_placeInFreeSpace(&position);
}

#ifdef TEST
int testCOINIsPlacedInFreeSpace() {
	int testsInError = 0;
	Position position = {10, 10};
	char c;

	T6963C_writeAt(position.x, position.y, EMPTY);

	COIN_placeInFreeSpace(&position);
	testsInError += assertEquals(position.x, 10, "FPF1");
	testsInError += assertEquals(position.y, 10, "FPF2");
	c = T6963C_readFrom(10, 10);
	testsInError += assertEquals(c, COIN, "FPF3");

	COIN_placeInFreeSpace(&position);
	testsInError += assertNotEquals(position.x, 10, "FPF4");
	c = T6963C_readFrom(position.x, position.y);
	testsInError += assertEquals(c, COIN, "FPF5");

	return testsInError;
}

int testCOINIsPlacedRandomly() {
	int testsInError = 0;

	Position position1 = {50, 50};
	Position position2 = {50, 50};
	
	COIN_random(&position1);
	COIN_random(&position2);

	testsInError += assertNotEquals(position1.x, 50, "FPR1");
	testsInError += assertNotEquals(position1.y, 50, "FPR2");
	testsInError += assertNotEquals(position2.x, 50, "FPR3");
	testsInError += assertNotEquals(position2.y, 50, "FPR4");
	
	testsInError += assertNotEquals(position1.x, position2.x, "FPR5");
	testsInError += assertNotEquals(position1.y, position2.y, "FPR6");


	return testsInError;
}

int testCOIN() {
	int testsInError = 0;
	
	testsInError += testCOINIsPlacedRandomly();
	testsInError += testCOINIsPlacedInFreeSpace();

	return testsInError;
}
#endif
