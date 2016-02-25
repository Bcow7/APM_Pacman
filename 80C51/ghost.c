#include <stdlib.h>
#include "test.h"
#include "bdd.h"
#include "t6963c.h"
#include "gameboard.h"
#include "ghost.h"
#include "main.h"


/**
 * Modifie les coordonn�es du serpent selon sa direction.
 * @param GHOST La description du serpent.
 */
 bool GHOST_isFreeSpace(unsigned char x, unsigned char y)
 {
	unsigned char c;
	c = T6963C_readFrom(x, y);
	
	if (c >= CORNER_TOP_LEFT && c <= CORNER_BOTTOM_RIGHT_RIGHT) 
	{
	   // V�rification que ce n'est pas un mur
	   return false;
	   
	}/* else if (c == GHOST) {
	   // Il y a d�j� un fantome sur cette case
	   return false;
	}*/
	
	return true;
}	

/**
 * Modifie les coordonn�es du ghost selon sa direction.
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

	
	// V�rification que ce n'est pas un mur
	if (GHOST_isFreeSpace(newPosition.x, newPosition.y)) 
	{
	   ghost->position.x = newPosition.x;
	   ghost->position.y = newPosition.y;
	} 
	else 
	{
	   // C'est un mur, il faut changer de direction
	   while (currentDirection == ghost->direction)
	   {
	      GHOST_turnRandomDirection(ghost);
	   }
	}
	
	// V�rification du compte � rebours
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
 * @param GHOST La d�finition du ghost.
 */
void GHOST_show(Ghost *ghost) 
{	   
   unsigned char c;
   
   if (ghost->direction == MOVES_NONE)
   {
      T6963C_writeAt(ghost->position.x, ghost->position.y, GHOST);
      
   } else {

      // On v�rifie s'il faut remettre un coin ou laisser vide l'ancien emplacement
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
 * D�cide de varier la direction du serpent selon la direction indiqu�e.
 * Le serpent ne peut jamais tourner de 180� en un mouvement.
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
 * Effectue une it�ration dans la vie du ghost.
 * @param GHOST La d�finition du ghost.
 * @return L'�tat du ghost apr�s l'it�ration.
 */
Status GHOST_iterate(Ghost *ghost) {
	GHOST_show(ghost);
	GHOST_move(ghost);

	return ghost->status;
}

#ifdef TEST

// ========================== Tests unitaires =================================
// Chaque test v�rifie le comportement d'une fonctionnalit� en �tablissant
// un �tat initial et en v�rifiant l'�tat final.



int testGhostTurns() {
        int testsInError = 0;
	Ghost ghost;
	Direction currentDirection;

	ghost.position.x = 7;
	ghost.position.y = 11;
        ghost.direction = MOVES_DOWN;
	currentDirection = ghost.direction;
        T6963C_writeAt(ghost.position.x+1, ghost.position.y, CORNER_TOP_LEFT);
        T6963C_writeAt(ghost.position.x-1, ghost.position.y, CORNER_TOP_LEFT);
	T6963C_writeAt(ghost.position.x, ghost.position.y+1, CORNER_TOP_LEFT);
	while (currentDirection == ghost.direction)
	{
	   GHOST_turnRandomDirection(&ghost);
	}
	testsInError += assertEquals(ghost.direction,MOVES_UP, "GT001");
   
   	ghost.position.x = 7;
	ghost.position.y = 8;
        ghost.direction = MOVES_UP;
	currentDirection = MOVES_UP;
        T6963C_writeAt(ghost.position.x+1, ghost.position.y, CORNER_TOP_LEFT);
        T6963C_writeAt(ghost.position.x-1, ghost.position.y, CORNER_TOP_LEFT);
	T6963C_writeAt(ghost.position.x, ghost.position.y-1, CORNER_TOP_LEFT);
	while (currentDirection == ghost.direction)
	{
	   GHOST_turnRandomDirection(&ghost);
	}
	testsInError += assertEquals(ghost.direction,MOVES_DOWN, "GT002");
	 
	ghost.position.x = 7;
	ghost.position.y = 5;
        ghost.direction = MOVES_UP;
	currentDirection = MOVES_UP;
        T6963C_writeAt(ghost.position.x, ghost.position.y+1, CORNER_TOP_LEFT);
        T6963C_writeAt(ghost.position.x, ghost.position.y-1, CORNER_TOP_LEFT);
	T6963C_writeAt(ghost.position.x+1, ghost.position.y, CORNER_TOP_LEFT);
	while (currentDirection == ghost.direction)
	{
	   GHOST_turnRandomDirection(&ghost);
	}
	testsInError += assertEquals(ghost.direction,MOVES_LEFT, "GT003");
	
	ghost.position.x = 7;
	ghost.position.y = 2;
        ghost.direction = MOVES_UP;
	currentDirection = MOVES_UP;
        T6963C_writeAt(ghost.position.x, ghost.position.y+1, CORNER_TOP_LEFT);
        T6963C_writeAt(ghost.position.x, ghost.position.y-1, CORNER_TOP_LEFT);
	T6963C_writeAt(ghost.position.x-1, ghost.position.y, CORNER_TOP_LEFT);
	while (currentDirection == ghost.direction)
	{
	   GHOST_turnRandomDirection(&ghost);
	}
	testsInError += assertEquals(ghost.direction,MOVES_RIGHT, "GT004");

	return testsInError;
}
// V�rifie que le ghost ce d�place bien dans les 4 direction
int testGhostMoves() {
	int testsInError = 0;

	
	Ghost ghost;

	ghost.position.x = 10;
	ghost.position.y = 10;

	ghost.direction = MOVES_UP;
	GHOST_move(&ghost);
	testsInError += assertEquals(9, ghost.position.y, "GM001");

	ghost.direction = MOVES_DOWN;
	GHOST_move(&ghost);
	testsInError += assertEquals(10, ghost.position.y, "GM002");

	ghost.direction = MOVES_LEFT;
	GHOST_move(&ghost);
	testsInError += assertEquals( 9, ghost.position.x, "GM003");

	ghost.direction = MOVES_RIGHT;
	GHOST_move(&ghost);
	testsInError += assertEquals(10, ghost.position.x, "GM004");

	return testsInError;
}

int testGhostHitsABorder() {
	int testsInError = 0;
	int i;
	
	Ghost ghost;
	 
   
	// Test Si il touche un mur
	
        ghost.position.x = 5;
	ghost.position.y = 10;
        T6963C_writeAt(ghost.position.x+1, ghost.position.y, CORNER_TOP_LEFT);
	for (i = 1 ; i < 17 ;i++){
	    ghost.direction = MOVES_RIGHT;
	    GHOST_move(&ghost);
	    
	    testsInError += assertEquals(ghost.position.x, 5, "GHAB01");
	    ghost.position.x = 5;
	    T6963C_writeAt(ghost.position.x+1, ghost.position.y, CORNER_TOP_LEFT+1);
	}

	return testsInError;
}
/*
// =========================== Tests de comportement ============================
// Chaque test:
// 1- �tablit un �tat initial.
// 2- Simule un sc�nario qu'un utilisateur pourrait r�aliser manuellement.
// 3- V�rifie, en contr�lant le contenu de l'�cran, que ce 
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
		GHOST_iterate(&ghost);//, ARROW_NEUTRAL);
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

	//A cr�er

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
		GHOST_iterate(&ghost);//, ARROW_NEUTRAL);
	}
	for (n = 0; n < 3; n++) {
		GHOST_iterate(&ghost);//, ARROW_DOWN);
	}
	for (n = 0; n < 3; n++) {
		GHOST_iterate(&ghost);//, ARROW_LEFT);
	}

	return BDD_assert(c, "SNTF");
}

/**
 * Collection de tests.
 * Les tests en erreur sont affich�s � l'�cran.
 * @return Le nombre de tests �chou�s.
 */
int testGhost() {
	int testsInError = 0;

	// Tests unitaires:
	testsInError += testGhostTurns();
	testsInError += testGhostMoves();
	testsInError += testGhostHitsABorder();

	// Tests de comportement:
	//testsInError += bddGhostHitsAnObstacle();
	//testsInError += bddGhostHitsAGhost();
	//testsInError += testGhostEatsACoin();
	//testsInError += bddGhostMovesTurnsAndCatchesACoin();

	// Nombre de tests en erreur:
	return testsInError;
}

#endif