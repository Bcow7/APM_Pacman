#include <string.h>
#include "main.h"
#include "t6963c.h"
#include "bdd.h"
#include "gameboard.h"

#define ROM_CG_ADDRESS 0x0000

/**
 * Copie la définition d'un caractère depuis la ROM vers la zone de définition
 * des caractères du T6963C.
 * @param positionInRom Position du caractère dans la ROM.
 * @param cgCode Code du caractère dans le t6963c.
 */
void GMB_copyFromRomToCg(unsigned char positionInRom, unsigned char cgCode) {
	unsigned char *rom_cg_address = (unsigned char __xdata *) (ROM_CG_ADDRESS + positionInRom * 8);
	unsigned int video_cg_address = cgCode * 8 + T6963C_ZONE_CG;
	T6963C_autoWrite(video_cg_address, rom_cg_address, 8);
}

/**
 * Initialise les caractères utilisés pendant le jeu.
 */
void GMB_initialize() 
{
	GMB_copyFromRomToCg( 14, PACMAM_GO_RIGHT);	
	GMB_copyFromRomToCg( 15, PACMAM_NO_MOVE);
	GMB_copyFromRomToCg( 16, PACMAM_GO_UP);
	GMB_copyFromRomToCg( 17, PACMAM_GO_LEFT);
	GMB_copyFromRomToCg( 18, PACMAM_GO_DOWN);
	GMB_copyFromRomToCg( 19, PACMAC_EAT);
	GMB_copyFromRomToCg( 20, PACMAM_DEAD);

	GMB_copyFromRomToCg( 30, GHOST);
	GMB_copyFromRomToCg( 31, COIN);

	GMB_copyFromRomToCg( 0, CORNER_TOP_LEFT);
	GMB_copyFromRomToCg( 1, CORNER_BOTTOM_LEFT);
	GMB_copyFromRomToCg( 2, CORNER_TOP_RIGHT);
	GMB_copyFromRomToCg( 3, CORNER_BOTTOM_RIGHT);
	
	GMB_copyFromRomToCg( 4, T_TOP_HORIZONTAL);
	GMB_copyFromRomToCg( 5, T_BOTTOM_HORIZONTAL);
	GMB_copyFromRomToCg( 6, T_LEFT_VERTICAL);
	GMB_copyFromRomToCg( 7, T_RIGHT_VERTICAL);

	GMB_copyFromRomToCg( 8, LINE_TOP_HORIZONTAL);
	GMB_copyFromRomToCg( 9, LINE_CENTER_HORIZONTAL);
	GMB_copyFromRomToCg( 10, LINE_BOTTOM_HORIZONTAL);

	GMB_copyFromRomToCg( 11, LINE_LEFT_VERTICAL);
	GMB_copyFromRomToCg( 12, LINE_CENTER_VERTICAL);
	GMB_copyFromRomToCg( 13, LINE_RIGHT_VERTICAL);
}

/**
 * Dessine un rectangle entre les coordonnées spécifiées.
 * Le carré est dessiné avec des caractères OBSTACLE_*, pour
 * que le serpent ne puisse pas le traverser.
 * @param x0, y0: Coordonnées de l'angle supérieur droit.
 * @param x1, y1: Coordonnées de l'angle inférieur gauche.
 */
void GMB_draw(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1) {

   unsigned char i;
   
   T6963C_writeAt(x0, y0, CORNER_TOP_LEFT);
   T6963C_writeAt(x1, y0, CORNER_TOP_RIGHT);
   T6963C_writeAt(x0, y1, CORNER_BOTTOM_LEFT);
   T6963C_writeAt(x1, y1, CORNER_BOTTOM_RIGHT);
   
   for (i = x0+1; i <= x1-1; i++) {
      T6963C_writeAt(i, y0, LINE_TOP_HORIZONTAL);
      T6963C_writeAt(i, y1, LINE_BOTTOM_HORIZONTAL);
   }
   for (i = y0+1; i <= y1-1; i++) {
      T6963C_writeAt(x0, i, LINE_LEFT_VERTICAL);
      T6963C_writeAt(x1, i, LINE_RIGHT_VERTICAL);
   }
}

/**
 * Remplit avec des espaces le rectangle défini par les coordonnées.
 * Permet de nettoyer l'intérieur du rectangle dessiné avec GMB_draw.
 * @param x0, y0: Coordonnées de l'angle supérieur droit.
 * @param x1, y1: Coordonnées de l'angle inférieur gauche.
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
 * Affiche un texte entouré d'un rectangle.
 * La largeur du rectangle est définie par la longueur du texte.
 * La fonction ne vérifie pas si le texte dépasse les bords de l'écran.
 * @param x0, y0 L'angle supérieur droit du rectangle.
 * @param text Le texte à afficher.
 */
void GMB_display(unsigned char x0, unsigned char y0, char *text) {

   unsigned int address;
   unsigned char i;
   
   GMB_draw(x0, y0, x0 + strlen(text) + 1, y0 + 2);

   for(i = 0; i<strlen(text); i++)
   {
      T6963C_writeAt(x0+1+i, y0+1, text[i]-0x20);
   }
}

#ifdef TEST
int bddGameboardDraw() {
	BddExpectedContent c = {
		"ABBBBBBBBC",
		"D........E",
		"D........E",
		"D........E",
		"FGGGGGGGGH"
	};

	BDD_clear();
	GMB_draw(BDD_SCREEN_X, BDD_SCREEN_Y, BDD_SCREEN_X + BDD_SCREEN_WIDTH - 1, BDD_SCREEN_Y + BDD_SCREEN_HEIGHT - 1);
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
		".ABBBBBC..",
		".D TXT E..",
		".FGGGGGH..",
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

	return testsInError;
}
#endif
