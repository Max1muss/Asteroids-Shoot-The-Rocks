#include "generateBigAsteroid.h" // getting random numbers from here

int genRandNum()
{
	return rand() % 4;
}

int genRandX()
{
	return rand() % 849;
}

int genRandY()
{
	return rand() % 478;
}

int genRandDir()
{
	return rand() % 4;
}

int genRandAsteroid()
{
	return rand() % 2;
}

int genRandIndex()
{
	return rand() % 2;
}

float genRandImpulse()
{
	float num;
	num = 1 + rand() % 10;
	return num / 100;
}

int getRandomSpawnTime()
{
	return 1 + rand() % 4;
}

int genRandomNumber()
{
	return 1 + rand() % 100;
}