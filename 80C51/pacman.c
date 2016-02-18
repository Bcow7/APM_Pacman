#include "test.h"
#include "bdd.h"
#include "t6963c.h"
#include "buffer.h"
#include "gameboard.h"
#include "pacman.h"


/**
 * Modifie les coordonnées du serpent selon sa direction.
 * @param PACMAN La description du serpent.
 */
 bool PACMAN_isFreeSpace(unsigned char x, unsigned char y)
 {
	unsigned char c;
	c = T6963C_readFrom(x, y);
	// Vérification que ce n'est pas un mur
	if (c >= CORNER_TOP_LEFT && c <= CORNER_BOTTOM_RIGHT_RIGHT) 
	{
	   return false;
	}
	
	return true;
}	

/**
 * Modifie les coordonnées du serpent selon sa direction.
 * @param PACMAN La description du serpent.
 */
void PACMAN_move(Pacman *pacman) {
   
	Position newPosition = {pacman->position.x, pacman->position.y};
   
	pacman->lastPosition.x = pacman->position.x;
	pacman->lastPosition.y = pacman->position.y;
   
	switch(pacman->direction) {
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
	if (PACMAN_isFreeSpace(newPosition.x, newPosition.y)) 
	{
	   pacman->position.x = newPosition.x;
	   pacman->position.y = newPosition.y;
	}
}

/**
 * Décide si le serpent vit ou meurt, ou mange un fruit, selon
 * sa position et ce qui se trouve à cet endroit.
 * @param PACMAN La description du serpent.
 */
void PACMAN_liveOrDie(Pacman *pacman) {
   
   unsigned char c;
   c = T6963C_readFrom(pacman->position.x, pacman->position.y);
   
   switch(c){
     case COIN:
	 pacman->status = EATING;
	 break;
      case EMPTY:
	 pacman->status = ALIVE;
	 break;
      case GHOST:
	 pacman->status = DEAD;
	 break;
      default:
	 pacman->status = ALIVE;
	 break;
   }
   
   // On vérifie  que le Pacman est dans l'espace de jeu
   if(pacman->position.x <= PACMAN_LIMIT_X0 ||
      pacman->position.x >= PACMAN_LIMIT_X1 ||
      pacman->position.y <= PACMAN_LIMIT_Y0 ||
      pacman->position.y >= PACMAN_LIMIT_Y1)
   {
      pacman->status = DEAD;
   }
}

/**
 * Affiche le pacman.
 * @param PACMAN La définition du pacman.
 */
void PACMAN_show(Pacman *pacman) 
{	
   unsigned char c;
   
   if (pacman->direction == MOVES_NONE)
   {
      // Pas d'alternance d'image
      T6963C_writeAt(pacman->position.x, pacman->position.y, PACMAN_NO_MOVE);
      
   } else {
      c = T6963C_readFrom(pacman->lastPosition.x, pacman->lastPosition.y);
   
      // On efface l'ancienne position
      T6963C_writeAt(pacman->lastPosition.x, pacman->lastPosition.y, EMPTY);
      
      // Si le pacman est bloqué on alterne pas l'image
      if (c == PACMAN_EAT || (pacman->position.x == pacman->lastPosition.x && pacman->position.y == pacman->lastPosition.y)) 
      {
	 switch(pacman->direction) {
		   case MOVES_UP:
			   T6963C_writeAt(pacman->position.x, pacman->position.y, PACMAN_GO_UP);
			   break;
		   case MOVES_DOWN:
			   T6963C_writeAt(pacman->position.x, pacman->position.y, PACMAN_GO_DOWN);
			   break;
		   case MOVES_LEFT:
			   T6963C_writeAt(pacman->position.x, pacman->position.y, PACMAN_GO_LEFT);
			   break;
		   case MOVES_RIGHT:
			   T6963C_writeAt(pacman->position.x, pacman->position.y, PACMAN_GO_RIGHT);
			   break;
	   }
      } else { 
	 T6963C_writeAt(pacman->position.x, pacman->position.y, PACMAN_EAT);
      }
   }
}

/**
 * Décide de varier la direction du Pacman selon la direction indiquée.
 * Le Pacman ne peut tourner de 180º en un mouvement.
 * @param PACMAN La description du Pacman.
 * @param arrow La direction désirée.
 */
void PACMAN_turn(Pacman *pacman, Arrow arrow) 
{   
   if (arrow == ARROW_UP && PACMAN_isFreeSpace(pacman->position.x, pacman->position.y-1))
   {
       pacman->direction = MOVES_UP;
   } 
   else if (arrow == ARROW_LEFT && PACMAN_isFreeSpace(pacman->position.x-1, pacman->position.y))
   {
       pacman->direction = MOVES_LEFT;
   } 
   else if (arrow == ARROW_RIGHT && PACMAN_isFreeSpace(pacman->position.x+1, pacman->position.y))
   {
       pacman->direction = MOVES_RIGHT;
   } 
   else if (arrow == ARROW_DOWN && PACMAN_isFreeSpace(pacman->position.x, pacman->position.y+1))
   {
       pacman->direction = MOVES_DOWN;
   }
}

/**
 * Effectue une itération dans la vie du pacman.
 * @param PACMAN La définition du pacman.
 * @return L'état du pacman après l'itération.
 */
Status PACMAN_iterate(Pacman *pacman, Arrow arrow) {
	PACMAN_show(pacman);
	PACMAN_turn(pacman, arrow);
	PACMAN_move(pacman);
	PACMAN_liveOrDie(pacman);

	return pacman->status;
}

#ifdef TEST

// ========================== Tests unitaires =================================
// Chaque test vérifie le comportement d'une fonctionnalité en établissant
// un état initial et en vérifiant l'état final.
int testPacmanTurnsTo(Direction currentDirection, Arrow turn, Direction expectedResult, char *testCode) {
	Pacman pacman = {MOVES_RIGHT, {10, 10},{10,10}, ALIVE};
	pacman.direction = currentDirection;
	PACMAN_turn(&pacman, turn);
	return assertEquals(expectedResult, pacman.direction, testCode);	
}

// Test que le pacman peut ce diriger dans tout les direction quelque soit sont sens de déplacment

int testPacmanTurns() {
	int testsInError = 0;
	
	testsInError += testPacmanTurnsTo(MOVES_RIGHT, ARROW_RIGHT,	MOVES_RIGHT,"ST01");
	testsInError += testPacmanTurnsTo(MOVES_RIGHT, ARROW_LEFT,	MOVES_LEFT,"ST02");
	testsInError += testPacmanTurnsTo(MOVES_RIGHT, ARROW_UP,	MOVES_UP, "ST03");
	testsInError += testPacmanTurnsTo(MOVES_RIGHT, ARROW_DOWN, 	MOVES_DOWN, "ST04");

	testsInError += testPacmanTurnsTo(MOVES_LEFT, ARROW_RIGHT, 	MOVES_RIGHT, "ST11");
	testsInError += testPacmanTurnsTo(MOVES_LEFT, ARROW_LEFT, 	MOVES_LEFT, "ST12");
	testsInError += testPacmanTurnsTo(MOVES_LEFT, ARROW_UP, 	MOVES_UP, "ST13");
	testsInError += testPacmanTurnsTo(MOVES_LEFT, ARROW_DOWN, 	MOVES_DOWN, "ST14");

	testsInError += testPacmanTurnsTo(MOVES_UP, ARROW_RIGHT, 	MOVES_RIGHT,"ST21");
	testsInError += testPacmanTurnsTo(MOVES_UP, ARROW_LEFT, 	MOVES_LEFT, "ST22");
	testsInError += testPacmanTurnsTo(MOVES_UP, ARROW_UP, 		MOVES_UP,"ST23");
	testsInError += testPacmanTurnsTo(MOVES_UP, ARROW_DOWN, 	MOVES_DOWN,"ST24");

	testsInError += testPacmanTurnsTo(MOVES_DOWN, ARROW_RIGHT, 	MOVES_RIGHT,"ST31");
	testsInError += testPacmanTurnsTo(MOVES_DOWN, ARROW_LEFT, 	MOVES_LEFT, "ST32");
	testsInError += testPacmanTurnsTo(MOVES_DOWN, ARROW_UP, 	MOVES_UP, "ST33");
	testsInError += testPacmanTurnsTo(MOVES_DOWN, ARROW_DOWN, 	MOVES_DOWN, "ST34");

	return testsInError;
}
	// Vérifie que le pacamn ce déplace bien dans les 4 direction

int testPacmanMoves() {
	int testsInError = 0;

	Pacman pacman;

	pacman.position.x = 10;
	pacman.position.y = 10;

	pacman.direction = MOVES_UP;
	PACMAN_move(&pacman);
	testsInError += assertEquals(9, pacman.position.y, "SM001");

	pacman.direction = MOVES_DOWN;
	PACMAN_move(&pacman);
	testsInError += assertEquals(10, pacman.position.y, "SM002");

	pacman.direction = MOVES_LEFT;
	PACMAN_move(&pacman);
	testsInError += assertEquals( 9, pacman.position.x, "SM003");

	pacman.direction = MOVES_RIGHT;
	PACMAN_move(&pacman);
	testsInError += assertEquals(10, pacman.position.x, "SM004");

	return testsInError;
}
// Véifie que le Pacman lorsque qu'il touche un mur ne meure pas et s'arrete 

int testPacmanHitsABorder() {
	int testsInError = 0;
	
	
	Pacman pacman;
   // Test Si il est dans le jeux
	pacman.status = ALIVE;
	pacman.position.x = PACMAN_LIMIT_X0 + 1;
	pacman.position.y = PACMAN_LIMIT_Y0 + 1;
	PACMAN_liveOrDie(&pacman);
	testsInError += assertEquals(pacman.status, ALIVE, "SO01");
   
     	pacman.position.x = 10;
	pacman.position.y = 10; 
	pacman.status = ALIVE;
        T6963C_writeAt(pacman.position.x+1, pacman.position.y, T_TOP_HORIZONTAL);
   	pacman.direction = MOVES_RIGHT;
	PACMAN_move(&pacman);
	testsInError += assertEquals(1, 10, "SO11");
	testsInError += assertEquals(pacman.status, ALIVE, "SO02");
	
	
      	pacman.position.x = 10;
	pacman.position.y = 10;
	pacman.status = ALIVE;
        T6963C_writeAt(pacman.position.x+1, pacman.position.y, GHOST);
   	pacman.direction = MOVES_RIGHT;
	PACMAN_move(&pacman);
	testsInError += assertEquals(10, 10, "SO12");
	testsInError += assertEquals(pacman.status, DEAD, "SO03"); 
   
   
/*
	pacman.status = ALIVE;
	pacman.position.x = PACMAN_LIMIT_X0;
	pacman.position.y = PACMAN_LIMIT_Y0 + 1;
	PACMAN_liveOrDie(&pacman);
	testsInError += assertEquals(pacman.status, BLOCKED, "SO02");

	pacman.status = ALIVE;
	pacman.position.x = PACMAN_LIMIT_X0 + 1;
	pacman.position.y = PACMAN_LIMIT_Y0;
	PACMAN_liveOrDie(&pacman);
	testsInError += assertEquals(pacman.status, BLOCKED, "SO03");

	pacman.status = ALIVE;
	pacman.position.x = PACMAN_LIMIT_X1;
	pacman.position.y = PACMAN_LIMIT_Y1 - 1;
	PACMAN_liveOrDie(&pacman);
	testsInError += assertEquals(pacman.status, BLOCKED, "SO04");

	pacman.status = ALIVE;
	pacman.position.x = PACMAN_LIMIT_X1 - 1;
	pacman.position.y = PACMAN_LIMIT_Y1;
	PACMAN_liveOrDie(&pacman);
	testsInError += assertEquals(pacman.status, BLOCKED, "SO05");
*/
	return testsInError;
}
/*
// =========================== Tests de comportement ============================
// Chaque test:
// 1- Établit un état initial.
// 2- Simule un scénario qu'un utilisateur pourrait réaliser manuellement.
// 3- Vérifie, en contrôlant le contenu de l'écran, que ce 
//    que percevrait l'utilisateur est juste

/*
int bddPacmanHitsThisObstacle(char obstacle, char *testId) {
	BddExpectedContent c = {
		"  1114....",
		"..........",
		"..........",
		"..........",
		".........."
	};
	Pacman pacman = {MOVES_RIGHT, {BDD_SCREEN_X, BDD_SCREEN_Y}, ALIVE, 3};
	char n;

	BUFFER_clear();
	BDD_clear();
	T6963C_writeAt(BDD_SCREEN_X + 5, BDD_SCREEN_Y, obstacle);
	
	for (n = 0; n < 5; n++) {
		PACMAN_iterate(&pacman, ARROW_NEUTRAL);
	}

	return BDD_assert(c, testId);
}

int bddPacmanHitsAnObstacle() 
{
	int testsInError = 0;
	
	// Mis a jour le 22.01.2016 Seb
	testsInError += bddPacmanHitsThisObstacle(CORNER_TOP_LEFT, "PMO-CTF");
	testsInError += bddPacmanHitsThisObstacle(CORNER_BOTTOM_LEFT, "PMO-CBL");
	testsInError += bddPacmanHitsThisObstacle(CORNER_TOP_RIGHT, "PMO-CTR");
	testsInError += bddPacmanHitsThisObstacle(CORNER_BOTTOM_RIGHT, "PMO-CBR");

	testsInError += bddPacmanHitsThisObstacle(T_TOP_HORIZONTAL, "PMO-TTH");
	testsInError += bddPacmanHitsThisObstacle(T_BOTTOM_HORIZONTAL, "PMO-TBH");
	testsInError += bddPacmanHitsThisObstacle(T_LEFT_VERTICAL, "PMO-TLV");
	testsInError += bddPacmanHitsThisObstacle(T_RIGHT_VERTICAL, "PMO-TRV");

	testsInError += bddPacmanHitsThisObstacle(LINE_TOP_HORIZONTAL, "PMO-LTH");
	testsInError += bddPacmanHitsThisObstacle(LINE_CENTER_HORIZONTAL, "PMO-LCH");
	testsInError += bddPacmanHitsThisObstacle(LINE_BOTTOM_HORIZONTAL, "PMO-LBH");

	testsInError += bddPacmanHitsThisObstacle(LINE_LEFT_VERTICAL, "PMO-LLV");
	testsInError += bddPacmanHitsThisObstacle(LINE_CENTER_VERTICAL, "PMO-LCV");
	testsInError += bddPacmanHitsThisObstacle(LINE_RIGHT_VERTICAL, "PMO-LRV");

	return testsInError;
}
/*
int bddPacmanHitsAGhost() 
{
	int testsInError = 0;

	//A créer

	return testsInError;
}

int testPacmanEatsACoin() {
	int testsInError = 0;
	//A faire

	return testsInError;	
}

int bddPacmanMovesTurnsAndCatchesACoin() {
	BddExpectedContent c = {
		"      1...",
		"......2...",
		"......1...",
		"...3111...",
		".........."
	};
	Pacman pacman = {MOVES_RIGHT, {BDD_SCREEN_X, BDD_SCREEN_Y}, ALIVE, 3};
	char n;

	BUFFER_clear();
	BDD_clear();
	T6963C_writeAt(BDD_SCREEN_X + 6, BDD_SCREEN_Y + 1, COIN);
	
	for (n = 0; n < 6; n++) {
		PACMAN_iterate(&pacman, ARROW_NEUTRAL);
	}
	for (n = 0; n < 3; n++) {
		PACMAN_iterate(&pacman, ARROW_DOWN);
	}
	for (n = 0; n < 3; n++) {
		PACMAN_iterate(&pacman, ARROW_LEFT);
	}

	return BDD_assert(c, "SNTF");
}

/**
 * Collection de tests.
 * Les tests en erreur sont affichés à l'écran.
 * @return Le nombre de tests échoués.
 */
int testPacman() {
	int testsInError = 0;

	// Tests unitaires:
	testsInError += testPacmanTurns();
	testsInError += testPacmanMoves();
	testsInError += testPacmanHitsABorder();
	 T6963C_writeAt(15, 15, GHOST);
	// Tests de comportement:
	//testsInError += bddPacmanHitsAnObstacle();
	//testsInError += bddPacmanHitsAGhost();
	//testsInError += testPacmanEatsACoin();
	//testsInError += bddPacmanMovesTurnsAndCatchesACoin();
//
	// Nombre de tests en erreur:
	return testsInError;
}

#endif
