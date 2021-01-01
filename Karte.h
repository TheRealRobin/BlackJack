#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;


//Die Leerzeichen nach den Worten sind zur besseren Einrückung und dienen der Übersichtlichkeit.
const vector<string> Farben = { "Kreuz", "Karo ", "Pik  ", "Herz " };
const vector<string> Zeichen { "Ass   ", "Zwei  ", "Drei  ", "Vier  ", "Fuenf ", "Sechs ", "Sieben", "Acht  ", "Neun  ", "Zehn  ", "Bube  ", "Dame  ", "Koenig"};

//Es wird davon ausgegangen, dass es zwar eine unendliche Anzahl an Karten gibt,
//bei einer Ziehung ist allerdings jede Karte gleich wahrscheinlich.

class Karte
{
private:
	string farbe;
	string zeichen;
	int zufallsZahlZwischen(int x, int y);
public:
	bool verdeckt;
	Karte() {
		string f = Farben.at(zufallsZahlZwischen(0, 3));
		string z = Zeichen.at(zufallsZahlZwischen(0, 12));
		farbe = f;
		zeichen = z;
		verdeckt = false;
	}
	Karte(bool v) {
		string f = Farben.at(zufallsZahlZwischen(0, 3));
		string z = Zeichen.at(zufallsZahlZwischen(0, 12));
		farbe = f;
		zeichen = z;
		verdeckt = v;
	}
	//nur zum testen der punkteberechnung gedacht
	Karte(string f, string z, bool v) {
		farbe = f;
		zeichen = z;
		verdeckt = v;
	}
	//Zum Ausgeben in der Konsole verwendet
	string getFarbe() { if (verdeckt) { return "?????"; } else return farbe; }
	string getZeichen() { if (verdeckt) { return "??????"; } else return zeichen; }
};