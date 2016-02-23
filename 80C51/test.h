#ifndef ___TEST_H
#define ___TEST_H

#ifdef TEST
	const char* getSatusInString(int status);

	int assertEquals(int value, int expectedValue, char *testId);
	int assertEqualsStatusString(int value, int expectedValue, char *testId);
	int assertNotEquals(int value, int notExpectedValue, char *testId);

#endif

#endif
