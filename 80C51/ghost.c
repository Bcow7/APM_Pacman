#include <stdlib.h>
#include "test.h"
#include "bdd.h"
#include "t6963c.h"
#include "gameboard.h"
#include "ghost.h"
#include "main.h"


/**
 * Modifie les coordonnées du serpent selon sa direction.
 * @param GHOST La description du serpent.
 */
 bool GHOST_isFreeSpace(unsigned char x, unsigned char y)
 {
	unsigned char c;
	c = T6963C_readFrom(x, y);
	
	if (c >= CORNER_TOP_LEFT && c <= CORNER_BOTTOM_RIGHT_RIGHT) 
	{
	   // Vérification que ce n'est pas un mur
	   return false;
	   
	}/* else if (c == GHOST) {
	   // Il y a déjà un fantome sur cette case
	   return false;
	}*/
	
	return true;
}	

/**
 * Modifie les coordonnées du serpent selon sa direction.
 * @param GHOST La description du serpent.
 */
void GHOST_move(Ghost *ghost) {
	
	Direction currentDirection = ghost->direction;
   
	Position newPosition = {ghost->position.x, ghost->position.y};
   
	ghost->lastPosition.x = ghost->position.x;
	ghost->lastPosition.y = ghost->position.y;
   
	switch(ghost->direction) {
		case MOVES_UP:
			newPosition.y--;
			break;
		case MOVES_DOWN:
			newPosition.y++;
			break;
		case MOVES_LEFT:
			newPosition.x--;
			break;
		case MOVES_RIGHT:
			newPosition.x++;
			break;
	}

	
	// Vérification que ce n'est pas un mur
	if (GHOST_isFreeSpace(newPosition.x, newPosition.y)) 
	{
	   ghost->position.x = newPosition.x;
	   ghost->position.y = newPosition.y;
	} else {
	   // C'est un mur, il faut changer de direction
	   while (currentDirection == ghost->direction)
	   {
	      GHOST_turnRandomDirection(ghost);
	   }
	}
	
	// Vérification du compte à rebours
	if (ghost->countdown == 0) {
	   ghost->countdown = -1;
	   while (currentDirection == ghost->direction)
	   {
	      GHOST_turnRandomDirection(ghost);
	   }
	} else if (ghost->countdown > 0) {
	   ghost->countdown--;
	}
}


/**
 * Affiche le ghost.
 * @param GHOST La définition du ghost.
 */
void GHOST_show(Ghost *ghost) 
{	   
   unsigned char c;
   
   if (ghost->direction == MOVES_NONE)
   {
      T6963C_writeAt(ghost->position.x, ghost->position.y, GHOST);
      
   } else {

      // On vérifie s'il faut remettre un coin ou laisser vide l'ancien emplacement
      if (ghost->lastPositionWasACoin){
	 T6963C_writeAt(ghost->lastPosition.x, ghost->lastPosition.y, COIN);
      } else {
	 T6963C_writeAt(ghost->lastPosition.x, ghost->lastPosition.y, EMPTY);
      }
      
      // On regarde s'il y a un COIN au nouvel emplacement, et on dessine le GHOST
      c = T6963C_readFrom(ghost->position.x, ghost->position.y);
      if (c == COIN) {
	 ghost->lastPositionWasACoin = true;
      } else {
	 ghost->lastPositionWasACoin = false;
      }
      T6963C_writeAt(ghost->position.x, ghost->position.y, GHOST);
   }
}



/**
 * Décide de varier la direction du serpent selon la direction indiquée.
 * Le serpent ne peut jamais tourner de 180º en un mouvement.
 * @param GHOST La description du serpent.
 */
void GHOST_turnRandomDirection(Ghost *ghost) 
{   
   Direction newDirection = MOVES_NONE;

   newDirection = rand() % 4 + 1;

    if (newDirection == MOVES_UP && ghost->direction != MOVES_UP && GHOST_isFreeSpace(ghost->position.x, ghost->position.y-1))
    {
       ghost->direction = MOVES_UP;
    } 
    else if (newDirection == MOVES_LEFT && ghost->direction != MOVES_LEFT && GHOST_isFreeSpace(ghost->position.x-1, ghost->position.y))
    {
       ghost->direction = MOVES_LEFT;
    } 
    else if (newDirection == MOVES_RIGHT && ghost->direction != MOVES_RIGHT && GHOST_isFreeSpace(ghost->position.x+1, ghost->position.y))
    {
       ghost->direction = MOVES_RIGHT;
    } 
    else if (newDirection == MOVES_DOWN && ghost->direction != MOVES_DOWN && GHOST_isFreeSpace(ghost->position.x, ghost->position.y+1))
    {
       ghost->direction = MOVES_DOWN;
    }
    
}

/**
 * Effectue une itération dans la vie du ghost.
 * @param GHOST La définition du ghost.
 * @return L'état du ghost après l'itération.
 */
Status GHOST_iterate(Ghost *ghost) {
	GHOST_show(ghost);
	GHOST_move(ghost);

	return ghost->status;
}

#ifdef TEST

// ========================== Tests unitaires =================================
// Chaque test vérifie le comportement d'une fonctionnalité en établissant
// un état initial et en vérifiant l'état final.
int testGhostTurnsTo(Direction currentDirection, Arrow turn, Direction expectedResult, char *testCode) {
	Ghost ghost = {MOVES_RIGHT, {10, 10},{10,10}, ALIVE};
	ghost.direction = currentDirection;
	GHOST_turn(&ghost, turn);
	return assertEquals(expectedResult, ghost.direction, testCode);	
}

int testGhostTurns() {
	int testsInError = 0;
	// A Verifier
	testsInError += testGhostTurnsTo(MOVES_RIGHT, ARROW_RIGHT,	MOVES_RIGHT,"ST01");
	testsInError += testGhostTurnsTo(MOVES_RIGHT, ARROW_LEFT,	MOVES_RIGHT,"ST02");
	testsInError += testGhostTurnsTo(MOVES_RIGHT, ARROW_UP,		MOVES_UP, 	"ST03");
	testsInError += testGhostTurnsTo(MOVES_RIGHT, ARROW_DOWN, 	MOVES_DOWN, "ST04");

	testsInError += testGhostTurnsTo(MOVES_LEFT, ARROW_RIGHT, 	MOVES_LEFT, "ST11");
	testsInError += testGhostTurnsTo(MOVES_LEFT, ARROW_LEFT, 	MOVES_LEFT, "ST12");
	testsInError += testGhostTurnsTo(MOVES_LEFT, ARROW_UP, 		MOVES_UP, 	"ST13");
	testsInError += testGhostTurnsTo(MOVES_LEFT, ARROW_DOWN, 	MOVES_DOWN, "ST14");

	testsInError += testGhostTurnsTo(MOVES_UP, ARROW_RIGHT, 	MOVES_RIGHT,"ST21");
	testsInError += testGhostTurnsTo(MOVES_UP, ARROW_LEFT, 		MOVES_LEFT, "ST22");
	testsInError += testGhostTurnsTo(MOVES_UP, ARROW_UP, 		MOVES_UP, 	"ST23");
	testsInError += testGhostTurnsTo(MOVES_UP, ARROW_DOWN, 		MOVES_UP, 	"ST24");

	testsInError += testGhostTurnsTo(MOVES_DOWN, ARROW_RIGHT, 	MOVES_RIGHT,"ST31");
	testsInError += testGhostTurnsTo(MOVES_DOWN, ARROW_LEFT, 	MOVES_LEFT, "ST32");
	testsInError += testGhostTurnsTo(MOVES_DOWN, ARROW_UP, 		MOVES_DOWN, "ST33");
	testsInError += testGhostTurnsTo(MOVES_DOWN, ARROW_DOWN, 	MOVES_DOWN, "ST34");

	return testsInError;
}

int testGhostMoves() {
	int testsInError = 0;

	// A Verifier
	Ghost ghost;

	ghost.position.x = 10;
	ghost.position.y = 10;

	ghost.direction = MOVES_UP;
	GHOST_move(&ghost);
	testsInError += assertEquals(9, ghost.position.y, "SM001");

	ghost.direction = MOVES_DOWN;
	GHOST_move(&ghost);
	testsInError += assertEquals(10, ghost.position.y, "SM002");

	ghost.direction = MOVES_LEFT;
	GHOST_move(&ghost);
	testsInError += assertEquals( 9, ghost.position.x, "SM003");

	ghost.direction = MOVES_RIGHT;
	GHOST_move(&ghost);
	testsInError += assertEquals(10, ghost.position.x, "SM004");

	return testsInError;
}

int testGhostHitsABorder() {
	int testsInError = 0;
	
	// A corriger
	Ghost ghost;

	ghost.status = ALIVE;
	ghost.position.x = PACMAN_LIMIT_X0 + 1;
	ghost.position.y = PACMAN_LIMIT_Y0 + 1;
	GHOST_liveOrDie(&ghost);
	testsInError += assertEquals(ghost.status, ALIVE, "SO01");

	ghost.status = ALIVE;
	ghost.position.x = PACMAN_LIMIT_X0;
	ghost.position.y = PACMAN_LIMIT_Y0 + 1;
	GHOST_liveOrDie(&ghost);
	testsInError += assertEquals(ghost.status, BLOCKED, "SO02");

	ghost.status = ALIVE;
	ghost.position.x = PACMAN_LIMIT_X0 + 1;
	ghost.position.y = PACMAN_LIMIT_Y0;
	GHOST_liveOrDie(&ghost);
	testsInError += assertEquals(ghost.status, BLOCKED, "SO03");

	ghost.status = ALIVE;
	ghost.position.x = PACMAN_LIMIT_X1;
	ghost.position.y = PACMAN_LIMIT_Y1 - 1;
	GHOST_liveOrDie(&ghost);
	testsInError += assertEquals(ghost.status, BLOCKED, "SO04");

	ghost.status = ALIVE;
	ghost.position.x = PACMAN_LIMIT_X1 - 1;
	ghost.position.y = PACMAN_LIMIT_Y1;
	GHOST_liveOrDie(&ghost);
	testsInError += assertEquals(ghost.status, BLOCKED, "SO05");

	return testsInError;
}

// =========================== Tests de comportement ============================
// Chaque test:
// 1- Établit un état initial.
// 2- Simule un scénario qu'un utilisateur pourrait réaliser manuellement.
// 3- Vérifie, en contrôlant le contenu de l'écran, que ce 
//    que percevrait l'utilisateur est juste


int bddGhostHitsThisObstacle(char obstacle, char *testId) {
	BddExpectedContent c = {
		"  1114....",
		"..........",
		"..........",
		"..........",
		".........."
	};
	Ghost ghost = {MOVES_RIGHT, {BDD_SCREEN_X, BDD_SCREEN_Y}, ALIVE, 3};
	char n;

	BUFFER_clear();
	BDD_clear();
	T6963C_writeAt(BDD_SCREEN_X + 5, BDD_SCREEN_Y, obstacle);
	
	for (n = 0; n < 5; n++) {
		GHOST_iterate(&ghost, ARROW_NEUTRAL);
	}

	return BDD_assert(c, testId);
}

int bddGhostHitsAnObstacle() 
{
	int testsInError = 0;
	
	// Mis a jour le 22.01.2016 Seb
	testsInError += bddGhostHitsThisObstacle(CORNER_TOP_LEFT, "PMO-CTF");
	testsInError += bddGhostHitsThisObstacle(CORNER_BOTTOM_LEFT, "PMO-CBL");
	testsInError += bddGhostHitsThisObstacle(CORNER_TOP_RIGHT, "PMO-CTR");
	testsInError += bddGhostHitsThisObstacle(CORNER_BOTTOM_RIGHT, "PMO-CBR");

	testsInError += bddGhostHitsThisObstacle(T_TOP_HORIZONTAL, "PMO-TTH");
	testsInError += bddGhostHitsThisObstacle(T_BOTTOM_HORIZONTAL, "PMO-TBH");
	testsInError += bddGhostHitsThisObstacle(T_LEFT_VERTICAL, "PMO-TLV");
	testsInError += bddGhostHitsThisObstacle(T_RIGHT_VERTICAL, "PMO-TRV");

	testsInError += bddGhostHitsThisObstacle(LINE_TOP_HORIZONTAL, "PMO-LTH");
	testsInError += bddGhostHitsThisObstacle(LINE_CENTER_HORIZONTAL, "PMO-LCH");
	testsInError += bddGhostHitsThisObstacle(LINE_BOTTOM_HORIZONTAL, "PMO-LBH");

	testsInError += bddGhostHitsThisObstacle(LINE_LEFT_VERTICAL, "PMO-LLV");
	testsInError += bddGhostHitsThisObstacle(LINE_CENTER_VERTICAL, "PMO-LCV");
	testsInError += bddGhostHitsThisObstacle(LINE_RIGHT_VERTICAL, "PMO-LRV");

	return testsInError;
}

int bddGhostHitsAGhost() 
{
	int testsInError = 0;

	//A créer

	return testsInError;
}

int testGhostEatsACoin() {
	int testsInError = 0;
	//A faire

	return testsInError;	
}

int bddGhostMovesTurnsAndCatchesACoin() {
	BddExpectedContent c = {
		"      1...",
		"......2...",
		"......1...",
		"...3111...",
		".........."
	};
	Ghost ghost = {MOVES_RIGHT, {BDD_SCREEN_X, BDD_SCREEN_Y}, ALIVE, 3};
	char n;

	BUFFER_clear();
	BDD_clear();
	T6963C_writeAt(BDD_SCREEN_X + 6, BDD_SCREEN_Y + 1, COIN);
	
	for (n = 0; n < 6; n++) {
		GHOST_iterate(&ghost, ARROW_NEUTRAL);
	}
	for (n = 0; n < 3; n++) {
		GHOST_iterate(&ghost, ARROW_DOWN);
	}
	for (n = 0; n < 3; n++) {
		GHOST_iterate(&ghost, ARROW_LEFT);
	}

	return BDD_assert(c, "SNTF");
}

/**
 * Collection de tests.
 * Les tests en erreur sont affichés à l'écran.
 * @return Le nombre de tests échoués.
 */
int testGhost() {
	int testsInError = 0;

	// Tests unitaires:
	testsInError += testGhostTurns();
	testsInError += testGhostMoves();
	testsInError += testGhostHitsABorder();

	// Tests de comportement:
	testsInError += bddGhostHitsAnObstacle();
	testsInError += bddGhostHitsAGhost();
	testsInError += testGhostEatsACoin();
	testsInError += bddGhostMovesTurnsAndCatchesACoin();

	// Nombre de tests en erreur:
	return testsInError;
}

#endif
