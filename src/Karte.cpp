#include "Karte.h"
#include <random>
#include <string>

using namespace std;

int Karte::zufallsZahlZwischen(int x, int y) {
	random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(x, y); // define the range
	int zufallsZahl = distr(gen); //Zufallszahl wird generiert

	return zufallsZahl;
}