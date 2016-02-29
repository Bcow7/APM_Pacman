#include <string.h>
#include "main.h"
#include "t6963c.h"
#include "bdd.h"
#include "gameboard.h"

#define ROM_CG_ADDRESS 0x0000

/**
 * Copie la d�finition d'un caract�re depuis la ROM vers la zone de d�finition
 * des caract�res du T6963C.
 * @param positionInRom Position du caract�re dans la ROM.
 * @param cgCode Code du caract�re dans le t6963c.
 */
void GMB_copyFromRomToCg(unsigned char positionInRom, unsigned char cgCode) {
	unsigned char *rom_cg_address = (unsigned char __xdata *) (ROM_CG_ADDRESS + positionInRom * 8);
	unsigned int video_cg_address = cgCode * 8 + T6963C_ZONE_CG;
	T6963C_autoWrite(video_cg_address, rom_cg_address, 8);
}

/**
* Copie la d�finition du labyrinthe depuis la ROM vers la zone de d�finition
* des caract�res du T6963C.
* @param start_rom Position de d�part du labyrinthe dans la ROM.
* @param x0 abscisse de d�part de l'�cran
* @param y0 ordonn� de d�part de l'�cran
* @param x1 abscisse de fin de l'�cran
* @param y1 ordonn� de fin de l'�cran
*/

void GMB_DrawLab(unsigned char start_rom, unsigned char x0, unsigned char y0,
unsigned char x1, unsigned char y1)
{
   
   
   unsigned char x,y;
   unsigned short int pos_rom = 0;
   for(y=y0;y<=y1;y++)
   {
      for(x=x0;x<=x1;x++)
      {
	 unsigned char *rom_cg_address = (unsigned char __xdata *) (ROM_CG_ADDRESS + (start_rom*8)+pos_rom);
	 T6963C_writeAt(x, y, *(rom_cg_address));
	 pos_rom ++;
      }
   }
	 
	
}
/**
 * Initialise les caract�res utilis�s pendant le jeu.
 */
void GMB_initialize() 
{
	GMB_copyFromRomToCg( 14, PACMAN_GO_RIGHT);	
	GMB_copyFromRomToCg( 15, PACMAN_NO_MOVE);
	GMB_copyFromRomToCg( 16, PACMAN_GO_UP);
	GMB_copyFromRomToCg( 17, PACMAN_GO_LEFT);
	GMB_copyFromRomToCg( 18, PACMAN_GO_DOWN);
	GMB_copyFromRomToCg( 19, PACMAN_EAT);
	GMB_copyFromRomToCg( 20, PACMAN_DEAD);

	GMB_copyFromRomToCg( 21, GHOST);
	GMB_copyFromRomToCg( 22, COIN);

	GMB_copyFromRomToCg( 0, CORNER_TOP_LEFT);
	GMB_copyFromRomToCg( 1, CORNER_BOTTOM_LEFT);
	GMB_copyFromRomToCg( 2, CORNER_TOP_RIGHT);
	GMB_copyFromRomToCg( 3, CORNER_BOTTOM_RIGHT);
	
	GMB_copyFromRomToCg( 4, T_TOP_HORIZONTAL);
	GMB_copyFromRomToCg( 5, T_BOTTOM_HORIZONTAL);
	GMB_copyFromRomToCg( 6, T_LEFT_VERTICAL);
	GMB_copyFromRomToCg( 7, T_RIGHT_VERTICAL);
	GMB_copyFromRomToCg(23,CORNER_BOTTOM_LEFT_LEFT);
	GMB_copyFromRomToCg(24,CORNER_BOTTOM_RIGHT_RIGHT);
	GMB_copyFromRomToCg(25,SPECIAL_P);

	GMB_copyFromRomToCg( 8, LINE_TOP_HORIZONTAL);
	GMB_copyFromRomToCg( 9, LINE_CENTER_HORIZONTAL);
	GMB_copyFromRomToCg( 10, LINE_BOTTOM_HORIZONTAL);

	GMB_copyFromRomToCg( 11, LINE_LEFT_VERTICAL);
	GMB_copyFromRomToCg( 12, LINE_CENTER_VERTICAL);
	GMB_copyFromRomToCg( 13, LINE_RIGHT_VERTICAL);
	
	
}




/**
 * Remplit avec des espaces le rectangle d�fini par les coordonn�es.
 * Permet de nettoyer l'int�rieur du rectangle dessin� avec GMB_draw.
 * @param x0, y0: Coordonn�es de l'angle sup�rieur droit.
 * @param x1, y1: Coordonn�es de l'angle inf�rieur gauche.
 */
void GMB_clear(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1) {
	
   unsigned char x,y;
   for (x = x0; x <= x1; x++) {
      for (y = y0; y <= y1; y++) {
	 T6963C_writeAt(x, y, EMPTY);
      }
   } 
}

/**
 * Affiche un texte entour� d'un rectangle.
 * La largeur du rectangle est d�finie par la longueur du texte.
 * La fonction ne v�rifie pas si le texte d�passe les bords de l'�cran.
 * @param x0, y0 L'angle sup�rieur droit du rectangle.
 * @param text Le texte � afficher.
 */
void GMB_display(unsigned char x0, unsigned char y0, char *text) {

   
   unsigned char i;
   
   //GMB_draw(x0, y0, x0 + strlen(text) + 1, y0 + 2);
   T6963C_writeAt(x0,y0,CORNER_TOP_LEFT);
   T6963C_writeAt(x0,y0+2,CORNER_BOTTOM_LEFT);
   T6963C_writeAt(x0+strlen(text)+1,y0,CORNER_TOP_RIGHT);
   T6963C_writeAt(x0+strlen(text)+1,y0+2,CORNER_BOTTOM_RIGHT);
   T6963C_writeAt(x0,y0+1,LINE_LEFT_VERTICAL);
   T6963C_writeAt(x0+strlen(text)+1,y0+1,LINE_RIGHT_VERTICAL);
   for(i = 0; i<strlen(text); i++)
   {
      T6963C_writeAt(x0+1+i, y0+1, text[i]-0x20);
      T6963C_writeAt(x0+1+i,y0,LINE_TOP_HORIZONTAL);
      T6963C_writeAt(x0+1+i,y0+2,LINE_BOTTOM_HORIZONTAL);
      
      
   }
   
}

#ifdef TEST
int bddGameboardDraw() {
	BddExpectedContent c = {
		"ABCDEFGHIP",
		"QRSTUVW901",
		"23456@....",
		"..........",
		".........."
	};

	BDD_clear();
	GMB_DrawLab(86,BDD_SCREEN_X, BDD_SCREEN_Y, BDD_SCREEN_X + BDD_SCREEN_WIDTH - 1, BDD_SCREEN_Y + BDD_SCREEN_HEIGHT - 1);
	return BDD_assert(c, "GMBD");
}

int bddGameboardClear() {
	BddExpectedContent c = {
		"..........",
		".        .",
		".        .",
		".        .",
		".........."
	};

	BDD_clear();
	GMB_clear(BDD_SCREEN_X + 1, BDD_SCREEN_Y + 1, BDD_SCREEN_X + BDD_SCREEN_WIDTH - 2, BDD_SCREEN_Y + BDD_SCREEN_HEIGHT - 2);
	return BDD_assert(c, "GMBC");
}

int bddGameboardDisplay() {
	BddExpectedContent c = {
		"..........",
		".AIIIIIC..",
		".R TXT T..",
		".BQQQQQD..",
		".........."
	};

	BDD_clear();
	GMB_display(BDD_SCREEN_X + 1, BDD_SCREEN_Y + 1, " TXT ");
	return BDD_assert(c, "GMBT");
}

int testGameboard() {
	int testsInError = 0;

	testsInError += bddGameboardDraw();
	testsInError += bddGameboardClear();
	testsInError += bddGameboardDisplay();
	BDD_clear;
	GMB_clear(BDD_SCREEN_X + 1, BDD_SCREEN_Y + 1, BDD_SCREEN_X + BDD_SCREEN_WIDTH - 2, BDD_SCREEN_Y + BDD_SCREEN_HEIGHT - 2);

	return testsInError;
}
#endif
