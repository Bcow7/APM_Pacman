#include "test.h"
#include "bdd.h"
#include "t6963c.h"

#include "gameboard.h"
#include "pacman.h"
#include "ghost.h"


/**
 * Modifie les coordonnées du PACMAN selon sa direction.
 * @param x et y, position future du pacman.
 */
 bool PACMAN_isFreeSpace(unsigned char x, unsigned char y)
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
	   return true;
	}
	return true;
}

/**
 * Modifie les coordonnées du PACMAN selon sa direction.
 * @param PACMAN La description du pacman.
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

	// PACMAN prend un tunnel
	if(newPosition.x <= PACMAN_LIMIT_X0) {
	    newPosition.x = PACMAN_LIMIT_X1;
	} else if (newPosition.x >= PACMAN_LIMIT_X1) {
	    newPosition.x = PACMAN_LIMIT_X0;
	} else if (newPosition.y <= PACMAN_LIMIT_Y0) {
	    newPosition.y = PACMAN_LIMIT_Y1;
	} else if (newPosition.y >= PACMAN_LIMIT_Y1) {
	    newPosition.y = PACMAN_LIMIT_Y0;
	}


	// Vérification que ce n'est pas un mur
	if (PACMAN_isFreeSpace(newPosition.x, newPosition.y))
	{
	   pacman->position.x = newPosition.x;
	   pacman->position.y = newPosition.y;
	}
}

/**
 * Décide si le PACMAN vit ou meurt, ou mange un coin, selon
 * sa position et ce qui se trouve à cet endroit.
 * @param PACMAN La description du PACMAN.
 */
void PACMAN_liveOrDie(Pacman *pacman) {

   unsigned char c;

   
   // Si le status est déjà DEAD, on ne change pas!
   if(pacman->status == DEAD || pacman->status == WON)
      return;
   

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
	 case '.':
		 pacman->status = ALIVE;
		 break;
      default:
	 pacman->status = ALIVE;
	 break;
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

      
   } 
   else 

   {
      // On regarde s'il y a un COIN au nouvel emplacement
      c = T6963C_readFrom(pacman->position.x, pacman->position.y);
      if (c == COIN) {
	 pacman->eatenCoins++;
      }
      if (pacman->eatenCoins == NB_OF_COINS_TO_EAT) {
	 pacman->status = WON;
      }
      
      
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

       } 
	   else 
	   { 

		   T6963C_writeAt(pacman->position.x, pacman->position.y, PACMAN_EAT);
       }
   }
}

/**
 * Décide de varier la direction du PACMAN selon la direction indiquée.
 * @param PACMAN La description du PACMAN.
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
	PACMAN_liveOrDie(pacman);
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

//Test des différent etat du pacman
int testPacmanLiveOrDive() {
	int testsInError = 0;

	Pacman pacman;

	pacman.position.x = BDD_SCREEN_X + 2;
	pacman.position.y = BDD_SCREEN_Y + 2;
	pacman.status = ALIVE;

	// Test Si il est sur un COIN
    T6963C_writeAt(pacman.position.x, pacman.position.y, COIN);
	PACMAN_liveOrDie(&pacman);
	testsInError += assertEquals(pacman.status, EATING, "PLOD01");
	testsInError += assertEqualsStatusString(pacman.status, EATING, "PLOD01");
	
	// Test Si il est sur un EMPTY
    T6963C_writeAt(pacman.position.x, pacman.position.y, EMPTY);
	PACMAN_liveOrDie(&pacman);
	testsInError += assertEquals(pacman.status, ALIVE, "PLOD02");
	testsInError += assertEqualsStatusString(pacman.status, ALIVE, "PLOD02");

	// Test Si il est sur un GHOST
    T6963C_writeAt(pacman.position.x, pacman.position.y, GHOST);
	PACMAN_liveOrDie(&pacman);
	testsInError += assertEquals(pacman.status, DEAD, "PLOD03");
	testsInError += assertEqualsStatusString(pacman.status, DEAD, "PLOD03");

	BDD_clear();
	return testsInError;
}
/**
 * Test si le pacman gagne
 * @param currentDirection, direction courrant du pacman
 */
int testPacmanEatCoinAndWon(){
	 
	int testsInError = 0;
   	Pacman pacman;

	pacman.position.x = BDD_SCREEN_X + 2;
	pacman.position.y = BDD_SCREEN_Y + 2;
	pacman.eatenCoins = 23;
   	pacman.direction = MOVES_RIGHT;
   
	T6963C_writeAt(pacman.position.x+1, pacman.position.y, COIN);
	T6963C_writeAt(pacman.position.x+2, pacman.position.y, COIN);
	PACMAN_iterate(&pacman, ARROW_NEUTRAL);
	PACMAN_iterate(&pacman, ARROW_NEUTRAL);
        PACMAN_iterate(&pacman, ARROW_NEUTRAL);
   
 	testsInError += assertEquals(pacman.eatenCoins, NB_OF_COINS_TO_EAT, "PECAW01");
        return testsInError;
}



/**
 * Test si le pacman tourne vers la bonne direction
 * @param currentDirection, direction courrant du pacman
 * @param turn La direction désirée.
 * @param expectedResult, resultat espéré
 * @param testCode, code d'erreur affiché si pacman.direction != expectedResult
 */
int testPacmanTurnsTo(Direction currentDirection, Arrow turn, Direction expectedResult, char *testCode) {
	Pacman pacman = {MOVES_RIGHT, {10, 10},{10,10}, ALIVE};
	pacman.direction = currentDirection;
	PACMAN_turn(&pacman, turn);
	return assertEquals(expectedResult, pacman.direction, testCode);
}

// Test que le pacman peut ce diriger dans tout les direction quelque soit sont sens de déplacment
int testPacmanTurns() {
	int testsInError = 0;

	testsInError += testPacmanTurnsTo(MOVES_RIGHT, ARROW_RIGHT,	MOVES_RIGHT,"PT01");
	testsInError += testPacmanTurnsTo(MOVES_RIGHT, ARROW_LEFT,	MOVES_LEFT,"PT02");
	testsInError += testPacmanTurnsTo(MOVES_RIGHT, ARROW_UP,	MOVES_UP, "PT03");
	testsInError += testPacmanTurnsTo(MOVES_RIGHT, ARROW_DOWN, 	MOVES_DOWN, "PT04");

	testsInError += testPacmanTurnsTo(MOVES_LEFT, ARROW_RIGHT, 	MOVES_RIGHT, "PT11");
	testsInError += testPacmanTurnsTo(MOVES_LEFT, ARROW_LEFT, 	MOVES_LEFT, "PT12");
	testsInError += testPacmanTurnsTo(MOVES_LEFT, ARROW_UP, 	MOVES_UP, "PT13");
	testsInError += testPacmanTurnsTo(MOVES_LEFT, ARROW_DOWN, 	MOVES_DOWN, "PT14");

	testsInError += testPacmanTurnsTo(MOVES_UP, ARROW_RIGHT, 	MOVES_RIGHT,"PT21");
	testsInError += testPacmanTurnsTo(MOVES_UP, ARROW_LEFT, 	MOVES_LEFT, "ST22");
	testsInError += testPacmanTurnsTo(MOVES_UP, ARROW_UP, 		MOVES_UP,"PT23");
	testsInError += testPacmanTurnsTo(MOVES_UP, ARROW_DOWN, 	MOVES_DOWN,"PT24");

	testsInError += testPacmanTurnsTo(MOVES_DOWN, ARROW_RIGHT, 	MOVES_RIGHT,"PT31");
	testsInError += testPacmanTurnsTo(MOVES_DOWN, ARROW_LEFT, 	MOVES_LEFT, "PT32");
	testsInError += testPacmanTurnsTo(MOVES_DOWN, ARROW_UP, 	MOVES_UP, "PT33");
	testsInError += testPacmanTurnsTo(MOVES_DOWN, ARROW_DOWN, 	MOVES_DOWN, "PT34");

	return testsInError;
}

// Vérifie que le pacamn ce déplace bien dans les 4 direction
int testPacmanMoves() {
	int testsInError = 0;

	Pacman pacman;

	pacman.position.x = BDD_SCREEN_X + 2;
	pacman.position.y = BDD_SCREEN_Y + 2;

	pacman.direction = MOVES_UP;
	PACMAN_move(&pacman);
	testsInError += assertEquals(pacman.position.y, BDD_SCREEN_Y + 1, "PM001");

	pacman.direction = MOVES_DOWN;
	PACMAN_move(&pacman);
	testsInError += assertEquals(pacman.position.y, BDD_SCREEN_Y + 2, "PM002");

	pacman.direction = MOVES_LEFT;
	PACMAN_move(&pacman);
	testsInError += assertEquals(pacman.position.x, BDD_SCREEN_X + 1, "PM003");

	pacman.direction = MOVES_RIGHT;
	PACMAN_move(&pacman);
	testsInError += assertEquals(pacman.position.x, BDD_SCREEN_X + 2, "PM004");

	BDD_clear();
	return testsInError;
}

int testPacmanHitsABorderTo(char obstacle,char *testCode){
	 
	 
   	int testsError;
   
	Pacman pacman;
	pacman.position.x = BDD_SCREEN_X + 2;
	pacman.position.y = BDD_SCREEN_Y + 2;
   
        T6963C_writeAt(pacman.position.x+1, pacman.position.y, obstacle );
	pacman.direction = MOVES_RIGHT;
	PACMAN_move(&pacman);	
	testsError += assertEquals(pacman.position.x, BDD_SCREEN_X + 2, testCode);
	BDD_clear();
	return testsError ;     
   
}
// Véifie que le Pacman lorsque qu'il touche un mur ne meure pas et s'arrete
int testPacmanHitsABorder() {
	int testsInError = 0;
	int i;
	char obstacle; 

	Pacman pacman;
    
	// Test Si il est dans le jeux
	pacman.status = ALIVE;
	pacman.position.x = PACMAN_LIMIT_X0 + 1;
	pacman.position.y = PACMAN_LIMIT_Y0 + 1;
	PACMAN_liveOrDie(&pacman);
	testsInError += assertEquals(pacman.status, ALIVE, "PHAB01");
	testsInError += assertEqualsStatusString(pacman.status, ALIVE, "PHAB01");

    // si il touche un mur 
   
	testsInError += testPacmanHitsABorderTo(CORNER_TOP_LEFT, "PHAB02");
	testsInError += testPacmanHitsABorderTo(CORNER_BOTTOM_LEFT, "PHAB03");
	testsInError += testPacmanHitsABorderTo(CORNER_TOP_RIGHT, "PHAB04");
	testsInError += testPacmanHitsABorderTo(CORNER_BOTTOM_RIGHT, "PHAB05");

	testsInError += testPacmanHitsABorderTo(T_TOP_HORIZONTAL, "PHAB06");
	testsInError += testPacmanHitsABorderTo(T_BOTTOM_HORIZONTAL, "PHAB07");
	testsInError += testPacmanHitsABorderTo(T_LEFT_VERTICAL, "PHAB08");
	testsInError += testPacmanHitsABorderTo(T_RIGHT_VERTICAL, "PHAB09");

	testsInError += testPacmanHitsABorderTo(LINE_TOP_HORIZONTAL, "PHAB10");
	testsInError += testPacmanHitsABorderTo(LINE_CENTER_HORIZONTAL, "PHAB11");
	testsInError += testPacmanHitsABorderTo(LINE_BOTTOM_HORIZONTAL, "PHAB12");

	testsInError += testPacmanHitsABorderTo(LINE_LEFT_VERTICAL, "PHAB13");
	testsInError += testPacmanHitsABorderTo(LINE_CENTER_VERTICAL, "PHAB14");
	testsInError += testPacmanHitsABorderTo(LINE_RIGHT_VERTICAL, "PHAB15");
	testsInError += testPacmanHitsABorderTo(CORNER_BOTTOM_LEFT_LEFT, "PHAB16");
	testsInError += testPacmanHitsABorderTo(CORNER_BOTTOM_RIGHT_RIGHT, "PHAB17");
	testsInError += testPacmanHitsABorderTo(SPECIAL_P, "PHAB18");

	return testsInError;
}

// Véifie que le Pacman meure lorsque qu'il touche un Ghost  
int testPacmanHitsAGhost(){

	int testsInError = 0;

	Pacman pacman;

	pacman.position.x = BDD_SCREEN_X + 2;
	pacman.position.y = BDD_SCREEN_Y + 2;
	pacman.status = ALIVE;

    T6963C_writeAt(pacman.position.x+1, pacman.position.y, GHOST);
   	pacman.direction = MOVES_RIGHT;
	PACMAN_move(&pacman);
	PACMAN_liveOrDie(&pacman);

	testsInError += assertEquals(pacman.status, DEAD, "PHAG03");
	testsInError += assertEqualsStatusString(pacman.status, DEAD, "PHAG03");
	
	BDD_clear();
	return testsInError;
}

// Véifie que le Pacman vit et passe en status EATING lorsque qu'il touche un coin  
int testPacmanHitsACoin(){

	int testsInError = 0;

	Pacman pacman;

	pacman.position.x = BDD_SCREEN_X + 2;
	pacman.position.y = BDD_SCREEN_Y + 2;
	pacman.status = ALIVE;

	T6963C_writeAt(pacman.position.x+1, pacman.position.y, COIN);
   	pacman.direction = MOVES_RIGHT;
	PACMAN_move(&pacman);
	PACMAN_liveOrDie(&pacman);

	testsInError += assertEquals(pacman.status, EATING, "PHAG03");
	testsInError += assertEqualsStatusString(pacman.status, EATING, "PHAG03");

	BDD_clear();
	return testsInError;
}

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

int bddPacmanHitsThisObstacle(char obstacle, char *testId) 
{
	BddExpectedContent c = {
		{' ',' ',' ',' ','0',obstacle + 32,'.','.','.','.'},
		"..........",
		"..........",
		"..........",
		".........."
	};
	
	Pacman pacman = {MOVES_RIGHT, {BDD_SCREEN_X, BDD_SCREEN_Y}, {BDD_SCREEN_X, BDD_SCREEN_Y}, ALIVE};
	char n;

	
	BDD_clear();
	
	T6963C_writeAt(BDD_SCREEN_X + 5, BDD_SCREEN_Y, obstacle);
	for (n = 0; n < 7; n++) {
		PACMAN_iterate(&pacman, ARROW_NEUTRAL);
	}

	return BDD_assert(c, testId);
}

// Vérifie que le pacman s'arrête pour chaque obstacle crée pour dessiner le jeu
int bddPacmanHitsAnObstacle()
{
	int testsInError = 0;

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
	testsInError += bddPacmanHitsThisObstacle(CORNER_BOTTOM_LEFT_LEFT, "PMO-CBLL");
	testsInError += bddPacmanHitsThisObstacle(CORNER_BOTTOM_RIGHT_RIGHT, "PMO-CBRR");
	testsInError += bddPacmanHitsThisObstacle(SPECIAL_P, "PMO-S_P");

	return testsInError;
}

// Vérifie que le pacman s'arrête si l'obstacle et un GHOST
int bddPacmanHitsAGhost()
{
	int testsInError = 0;
	char *testId ="PMO-COIN";

	BddExpectedContent c = {
			{' ',' ',' ',' ',' ',' ','0','.','.','.'},
			"..........",
			"..........",
			"..........",
			".........."
		};
	
	Pacman pacman = {MOVES_RIGHT, {BDD_SCREEN_X, BDD_SCREEN_Y}, {BDD_SCREEN_X, BDD_SCREEN_Y}, ALIVE};
	char n;

	
	BDD_clear();
	
	T6963C_writeAt(BDD_SCREEN_X + 5, BDD_SCREEN_Y, GHOST);
	for (n = 0; n < 7; n++) {
		PACMAN_iterate(&pacman, ARROW_NEUTRAL);
	}

	testsInError = BDD_assert(c, testId);

	return testsInError;
}

// Vérifie que le pacman continue son chemmin et mange le COIN
int bddPacmanEatsACoin()
{
	int testsInError = 0;
	char *testId ="PMO-COIN";

	BddExpectedContent c = {
			{' ',' ',' ',' ',' ',' ','0','.','.','.'},
			"..........",
			"..........",
			"..........",
			".........."
		};
	
	Pacman pacman = {MOVES_RIGHT, {BDD_SCREEN_X, BDD_SCREEN_Y}, {BDD_SCREEN_X, BDD_SCREEN_Y}, ALIVE};
	char n;

	
	BDD_clear();
	
	T6963C_writeAt(BDD_SCREEN_X + 5, BDD_SCREEN_Y, COIN);
	for (n = 0; n < 7; n++) {
		PACMAN_iterate(&pacman, ARROW_NEUTRAL);
	}

	testsInError = BDD_assert(c, testId);

	return testsInError;
}

//test d'un déplacement avec plusieur direction et mange bien le COIN sur son chemin
int bddPacmanMovesTurnsAndCatchesACoin() {
	BddExpectedContent c = {
		"       ...",
		"...... ...",
		"...... ...",
		"....5  ...",
		".........."
	};
	Pacman pacman = {MOVES_RIGHT, {BDD_SCREEN_X, BDD_SCREEN_Y}, {BDD_SCREEN_X, BDD_SCREEN_Y}, ALIVE};
	char n;

	
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

	return BDD_assert(c, "PMO-TACAC");
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
	testsInError += testPacmanLiveOrDive();
	testsInError += testPacmanHitsABorder();
	testsInError += testPacmanHitsAGhost();
	testsInError += testPacmanHitsACoin();
        testsInError += testPacmanEatCoinAndWon();
	
	
	// Tests de comportement:
	testsInError += bddPacmanHitsAnObstacle();
	testsInError += bddPacmanHitsAGhost();
	testsInError += bddPacmanEatsACoin();
	testsInError += bddPacmanMovesTurnsAndCatchesACoin();

	// Nombre de tests en erreur:
	return testsInError;
}

#endif
