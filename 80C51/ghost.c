#include <stdlib.h>
#include "test.h"
#include "bdd.h"
#include "t6963c.h"
#include "buffer.h"
#include "gameboard.h"
#include "pacman.h"
#include "ghost.h"


/**
 * Modifie les coordonnées du GHOST selon sa direction.
 * @param x et y, position future du GHOST.
 */

 bool GHOST_isFreeSpace(unsigned char x, unsigned char y)
 {
	unsigned char c;
	c = T6963C_readFrom(x, y);
	
	//chararctère de base qui fait office de mur
	if (c >= CORNER_TOP_LEFT && c <= LINE_RIGHT_VERTICAL) 
	{
	   return false;	   
	}
	
	//caractère ajouter par la suite qui fait office de mur
	if (c == CORNER_BOTTOM_LEFT_LEFT ||
		c == CORNER_BOTTOM_RIGHT_RIGHT ||
		c == SPECIAL_P)
	{
	   return false;	   
	}

	// Il y a déjà un fantome sur cette case
	if (c == GHOST) 
	{
	   return false;
	}
	
	return true;
}	

/**
 * Modifie les coordonnées du ghost selon sa direction.
 * @param GHOST La description du ghost.
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
	} 
	else 
	{
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
 * Décide de varier la direction du ghost aléatoirement.
 * change de direction si il n'y a pas d'obstacle
 * @param GHOST La description du ghost.
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

// test que le ghost tourne dans la bonne direction quand on lui bloque les 3 autres directions
int testGhostTurns() 
{
    int testsInError = 0;
	Ghost ghost;
	Direction currentDirection;

	// doit aller en haut
	ghost.position.x = BDD_SCREEN_X +2;
	ghost.position.y = BDD_SCREEN_Y +2;
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
	BDD_clear();

	// doit aller en bas 
	ghost.position.x = BDD_SCREEN_X +2;
	ghost.position.y = BDD_SCREEN_Y +2;
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
	BDD_clear();

	// doit aller à gauche	 
	ghost.position.x = BDD_SCREEN_X +2;
	ghost.position.y = BDD_SCREEN_Y +2;
    ghost.direction = MOVES_UP;

	currentDirection = MOVES_UP;

    T6963C_writeAt(ghost.position.x, ghost.position.y +1, CORNER_TOP_LEFT);
    T6963C_writeAt(ghost.position.x, ghost.position.y -1, CORNER_TOP_LEFT);
	T6963C_writeAt(ghost.position.x+1, ghost.position.y, CORNER_TOP_LEFT);

	// La boucle while n'est pas dans la fonction car cela n'est pas possible à cause du compliateur "excedent de ram"
	while (currentDirection == ghost.direction)
	{
	   GHOST_turnRandomDirection(&ghost);
	}
	testsInError += assertEquals(ghost.direction,MOVES_LEFT, "GT003");
	BDD_clear();
	
	// doit aller à droite	
	ghost.position.x = BDD_SCREEN_X +2;
	ghost.position.y = BDD_SCREEN_Y +2;
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
	BDD_clear();

	return testsInError;
}

// Vérifie que le ghost ce déplace bien dans les 4 direction
int testGhostMoves()
{
	int testsInError = 0;

	
	Ghost ghost;

	ghost.position.x = 5;
	ghost.position.y = 5;

	ghost.direction = MOVES_UP;
	GHOST_move(&ghost);
	testsInError += assertEquals(4, ghost.position.y, "GM001");

	ghost.direction = MOVES_DOWN;
	GHOST_move(&ghost);
	testsInError += assertEquals(5, ghost.position.y, "GM002");

	ghost.direction = MOVES_LEFT;
	GHOST_move(&ghost);
	testsInError += assertEquals(4, ghost.position.x, "GM003");

	ghost.direction = MOVES_RIGHT;
	GHOST_move(&ghost);
	testsInError += assertEquals(5, ghost.position.x, "GM004");

	return testsInError;
}

int testGhostHitsABorderTo(char obstacle,char *testCode){
	 
	 
   	int testsError;
   
	Ghost ghost;
	ghost.position.x = BDD_SCREEN_X + 2;
	ghost.position.y = BDD_SCREEN_Y + 2;
   
        T6963C_writeAt(ghost.position.x+1, ghost.position.y, obstacle );
	ghost.direction = MOVES_RIGHT;
	GHOST_move(&ghost);	
	testsError += assertEquals(ghost.position.x, BDD_SCREEN_X + 2, testCode);
	BDD_clear();
	return testsError ;     
   
}
// Véifie que le Pacman lorsque qu'il touche un mur ne meure pas et s'arrete
int testGhostHitsABorder() {
	int testsInError = 0;
	int i;
	char obstacle; 

	Ghost ghost;
    
        // si il touche un mur 
   
	testsInError += testGhostHitsABorderTo(CORNER_TOP_LEFT, "GHAB02");
	testsInError += testGhostHitsABorderTo(CORNER_BOTTOM_LEFT, "GHAB03");
	testsInError += testGhostHitsABorderTo(CORNER_TOP_RIGHT, "GHAB04");
	testsInError += testGhostHitsABorderTo(CORNER_BOTTOM_RIGHT, "GHAB05");

	testsInError += testGhostHitsABorderTo(T_TOP_HORIZONTAL, "GHAB06");
	testsInError += testGhostHitsABorderTo(T_BOTTOM_HORIZONTAL, "GHAB07");
	testsInError += testGhostHitsABorderTo(T_LEFT_VERTICAL, "GHAB08");
	testsInError += testGhostHitsABorderTo(T_RIGHT_VERTICAL, "GHAB09");

	testsInError += testGhostHitsABorderTo(LINE_TOP_HORIZONTAL, "GHAB10");
	testsInError += testGhostHitsABorderTo(LINE_CENTER_HORIZONTAL, "GHAB11");
	testsInError += testGhostHitsABorderTo(LINE_BOTTOM_HORIZONTAL, "GHAB12");

	testsInError += testGhostHitsABorderTo(LINE_LEFT_VERTICAL, "GHAB13");
	testsInError += testGhostHitsABorderTo(LINE_CENTER_VERTICAL, "GHAB14");
	testsInError += testGhostHitsABorderTo(LINE_RIGHT_VERTICAL, "GHAB15");
	testsInError += testGhostHitsABorderTo(CORNER_BOTTOM_LEFT_LEFT, "GHAB16");
	testsInError += testGhostHitsABorderTo(CORNER_BOTTOM_RIGHT_RIGHT, "GHAB17");
	testsInError += testGhostHitsABorderTo(SPECIAL_P, "GHAB18");

	return testsInError;
}
// Véifie que le Ghost vit et passe sur le COIN  
int testGhostHitsACoin()
{

	int testsInError = 0;

	Pacman pacman;

	pacman.position.x = 10;
	pacman.position.y = 10;
	pacman.status = ALIVE;

    T6963C_writeAt(pacman.position.x+1, pacman.position.y, COIN);
   	pacman.direction = MOVES_RIGHT;
	PACMAN_move(&pacman);
	PACMAN_liveOrDie(&pacman);

	testsInError += assertEquals(pacman.status, EATING, "GHAC01");
	testsInError += assertEqualsStatusString(pacman.status, EATING, "GHAC01");

	return testsInError;
}
/*
// =========================== Tests de comportement ============================
// Chaque test:
// 1- Établit un état initial.
// 2- Simule un scénario qu'un utilisateur pourrait réaliser manuellement.
// 3- Vérifie, en contrôlant le contenu de l'écran, que ce 
//    que percevrait l'utilisateur est juste

/**
 * Vérifie que le pacman s'arrête si il y a un mur dans sa position futur
 * @param obstacle, obstacle dessiner dans le gameboard
 * @param testId, code d'erreur affiché si l'ecran, à la fin du test,  ne correspond pas au BddExpectedContent
 */
int bddGhostHitsThisObstacle(char obstacle, char *testId) 
{

	BddExpectedContent c = {
		{'.','.','.','.',obstacle + 32,'.','.','.','.','.'},
		{'.','.','.',obstacle + 32,' ',obstacle + 32,'.','.','.','.'},
		{'.','.','.','.','9','.','.','.','.','.'},
		"..........",
		".........."
	};
	
	Ghost ghost = {MOVES_NONE, {BDD_SCREEN_X+4, BDD_SCREEN_Y+1}, {BDD_SCREEN_X, BDD_SCREEN_Y},  HUNTER};

	char n;

	BUFFER_clear();
	BDD_clear();
	
	T6963C_writeAt(BDD_SCREEN_X + 4, BDD_SCREEN_Y, obstacle);
	T6963C_writeAt(BDD_SCREEN_X + 5, BDD_SCREEN_Y+1, obstacle);
	T6963C_writeAt(BDD_SCREEN_X + 3, BDD_SCREEN_Y+1, obstacle);
	for (n = 0; n < 3; n++) {
		GHOST_iterate(&ghost);	
	}

	return BDD_assert(c, testId);
}


// Vérifie que le Ghost s'arrête pour chaque obstacle crée pour dessiner le jeu
int bddGhostHitsAnObstacle() 
{
	int testsInError = 0;
	
	testsInError += bddGhostHitsThisObstacle(CORNER_TOP_LEFT, "GHO-CTF");
	testsInError += bddGhostHitsThisObstacle(CORNER_BOTTOM_LEFT, "GHO-CBL");
	testsInError += bddGhostHitsThisObstacle(CORNER_TOP_RIGHT, "GHO-CTR");
	testsInError += bddGhostHitsThisObstacle(CORNER_BOTTOM_RIGHT, "GHO-CBR");

	testsInError += bddGhostHitsThisObstacle(T_TOP_HORIZONTAL, "GHO-TTH");
	testsInError += bddGhostHitsThisObstacle(T_BOTTOM_HORIZONTAL, "GHO-TBH");
	testsInError += bddGhostHitsThisObstacle(T_LEFT_VERTICAL, "GHO-TLV");
	testsInError += bddGhostHitsThisObstacle(T_RIGHT_VERTICAL, "GHO-TRV");

	testsInError += bddGhostHitsThisObstacle(LINE_TOP_HORIZONTAL, "GHO-LTH");
	testsInError += bddGhostHitsThisObstacle(LINE_CENTER_HORIZONTAL, "GHO-LCH");
	testsInError += bddGhostHitsThisObstacle(LINE_BOTTOM_HORIZONTAL, "GHO-LBH");

	testsInError += bddGhostHitsThisObstacle(LINE_LEFT_VERTICAL, "GHO-LLV");
	testsInError += bddGhostHitsThisObstacle(LINE_CENTER_VERTICAL, "GHO-LCV");
	testsInError += bddGhostHitsThisObstacle(LINE_RIGHT_VERTICAL, "GHO-LRV");
	testsInError += bddGhostHitsThisObstacle(CORNER_BOTTOM_LEFT_LEFT, "GHO-CBLL");
	testsInError += bddGhostHitsThisObstacle(CORNER_BOTTOM_RIGHT_RIGHT, "GHO-CBRR");
	testsInError += bddGhostHitsThisObstacle(SPECIAL_P, "GHO-S_P");

	return testsInError;
}

// Vérifie que le Ghost change de direction si c'est un autre Ghost
int bddGhostHitsAGhost() 
{
	int testsInError = 0;

	testsInError += bddGhostHitsThisObstacle(GHOST, "GHO-GHOST");

	return testsInError;
}

// Vérifie que le ghost continue son chemmin et ne mange pas le COIN
int bddGhostHitsACoin() 
{
	int testsInError = 0;
	char *testId ="GHO-COIN";

	BddExpectedContent c = {
		{'.','.','.','.',CORNER_TOP_LEFT + 32,'.','.','.','.','.'},
		{'.','.','.',CORNER_TOP_LEFT + 32,' ',CORNER_TOP_LEFT + 32,'.','.','.','.'},
		{'.','.','.',CORNER_TOP_LEFT + 32,COIN + 32,CORNER_TOP_LEFT + 32,'.','.','.','.'},
		{'.','.','.','.','9','.','.','.','.','.'},
		".........."
	};
	
	Ghost ghost = {MOVES_NONE, {BDD_SCREEN_X+4, BDD_SCREEN_Y+1}, {BDD_SCREEN_X, BDD_SCREEN_Y},  HUNTER};

	char n;

	BUFFER_clear();
	BDD_clear();
	
	T6963C_writeAt(BDD_SCREEN_X + 4, BDD_SCREEN_Y, CORNER_TOP_LEFT);
	T6963C_writeAt(BDD_SCREEN_X + 5, BDD_SCREEN_Y+1, CORNER_TOP_LEFT);
	T6963C_writeAt(BDD_SCREEN_X + 3, BDD_SCREEN_Y+1, CORNER_TOP_LEFT);
	T6963C_writeAt(BDD_SCREEN_X + 5, BDD_SCREEN_Y+2, CORNER_TOP_LEFT);
	T6963C_writeAt(BDD_SCREEN_X + 3, BDD_SCREEN_Y+2, CORNER_TOP_LEFT);
	T6963C_writeAt(BDD_SCREEN_X + 4, BDD_SCREEN_Y+2, COIN);

	for (n = 0; n < 4; n++) {
		GHOST_iterate(&ghost);	
	}

	return BDD_assert(c, testId);
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
	testsInError += bddGhostHitsACoin();

	// Nombre de tests en erreur:
	return testsInError;
}

#endif