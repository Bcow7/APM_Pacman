#include <mcs51reg.h>
#include <stdio.h>
#include "test.h"
#include "t6963c.h"
#include "pacman.h"

#ifdef TEST

/**
 *Converti le Enum en string des Status
 **/
const char* getSatusInString(int status){
	
	switch (status) 
	{
		case 0: return "ALIVE";
		case 1: return "DEAD";
		case 2: return "EATING";
    }

}


/**
 * Contrôle l'identité de deux valeurs, et signale un code
 * d'erreur le cas échéant.
 * @param value Valeur obtenue.
 * @param expectedValue Valeur attendue.
 * @param testId Identifiant du test affiché si il échoue.
 * @return 1 Si le test est en erreur, 0 autrement.
 **/
int assertEquals(int value, int expectedValue, char *testId) {
	if (value != expectedValue) {
		printf("%s: attendu %d, trouvé %d\r\n", testId, expectedValue, value);
		return 1;
	}
	return 0;
}


/**
 * Contrôle l'identité de deux valeurs, et signale un code
 * d'erreur le cas échéant.
 * @param value Valeur obtenue.
 * @param expectedValue Valeur attendue.
 * @param testId Identifiant du test affiché si il échoue.
 * @return 1 Si le test est en erreur, 0 autrement.
 **/
int assertEqualsStatusString(int value, int expectedValue, char *testId) {
	if (value != expectedValue) {
		printf("%s: attendu %s,\r\n        trouvé  %s\r\n", testId, getSatusInString(expectedValue), getSatusInString(value));
		return 1;
	}
	return 0;
}

/**
 * Contrôle que deux valeurs ne sont pas identiques, et signale un code
 * d'erreur le cas échéant.
 * @param value Valeur obtenue.
 * @param expectedValue Valeur attendue.
 * @param testId Identifiant du test affiché si il échoue.
 * @return 1 Si le test est en erreur, 0 autrement.
 **/
int assertNotEquals(int value, int notExpectedValue, char *testId) {
	if (value == notExpectedValue) {
		printf("%s: ne devrait pas egal a %d\r\n", testId, notExpectedValue);
		return 1;
	}
	return 0;
}

#endif
