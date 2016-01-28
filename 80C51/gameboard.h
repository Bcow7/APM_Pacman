#ifndef ___GAMEBOARD_H
#define ___GAMEBOARD_H

#ifdef TEST
#define CHAR_BASE 0x00
int testGameboard();
#else
#define CHAR_BASE 0x80
#endif


#define EMPTY 0x00

#define PACMAN_GO_RIGHT			(0x10 + CHAR_BASE)
#define PACMAN_NO_MOVE  		(0x11 + CHAR_BASE)
#define PACMAN_GO_UP 			(0x12 + CHAR_BASE)
#define PACMAN_GO_LEFT 			(0x13 + CHAR_BASE)
#define PACMAN_GO_DOWN 			(0x14 + CHAR_BASE)
#define PACMAN_EAT				(0x15 + CHAR_BASE)
#define PACMAN_DEAD				(0x16 + CHAR_BASE)

#define GHOST 					(0x19 + CHAR_BASE)
#define COIN 					(0x20 + CHAR_BASE)

#define CORNER_TOP_LEFT 		(0x21 + CHAR_BASE)
#define CORNER_BOTTOM_LEFT 		(0x22 + CHAR_BASE)
#define CORNER_TOP_RIGHT 		(0x23 + CHAR_BASE)
#define CORNER_BOTTOM_RIGHT 	(0x24 + CHAR_BASE)

#define T_TOP_HORIZONTAL 		(0x25 + CHAR_BASE)
#define T_BOTTOM_HORIZONTAL 	(0x26 + CHAR_BASE)
#define T_LEFT_VERTICAL 		(0x27 + CHAR_BASE)
#define T_RIGHT_VERTICAL 		(0x28 + CHAR_BASE)

#define LINE_TOP_HORIZONTAL 	(0x29 + CHAR_BASE)
#define LINE_CENTER_HORIZONTAL 	(0x30 + CHAR_BASE)
#define LINE_BOTTOM_HORIZONTAL 	(0x31 + CHAR_BASE)

#define LINE_LEFT_VERTICAL		(0x32 + CHAR_BASE)
#define LINE_CENTER_VERTICAL	(0x33 + CHAR_BASE)
#define LINE_RIGHT_VERTICAL		(0x34 + CHAR_BASE)


void GMB_initialize();
void GMB_draw(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1);
void GMB_clear(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1);
void GMB_display(unsigned char x0, unsigned char y0, char *text);

#endif
