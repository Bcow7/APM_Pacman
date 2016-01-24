#ifndef ___COIN_H
#define ___COIN_H

void COIN_placeInFreeSpace(Position *position);
void COIN_random(Position *position);
void COIN_place();

#ifdef TEST
int testCOIN();
#endif

#endif
