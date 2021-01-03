#include "Karte.h"
#include <random>
#include <chrono>
#include <string>

using namespace std;

//http://www.cplusplus.com/reference/random/uniform_int_distribution/
//Die Zufallszahlen werden mit std::random und der Systemzeit berechnet.
int Karte::zufallsZahlZwischen(int x, int y) {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count(); //unixepoch als seed
	default_random_engine gen(seed); 
	uniform_int_distribution<int> dist(x,y);

	int zufallsZahl = dist(gen); //Zufallszahl wird generiert

	return zufallsZahl;
}