#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;


//Die Leerzeichen nach den Worten sind zur besseren Einr�ckung bei printHand() (siehe BlackJack.cpp) 
//und dienen der �bersichtlichkeit.
const vector<string> Farben = { "Kreuz", "Karo ", "Pik  ", "Herz " };
const vector<string> Zeichen { "Ass   ", "Zwei  ", "Drei  ", "Vier  ", "Fuenf ", "Sechs ", "Sieben", "Acht  ", "Neun  ", "Zehn  ", "Bube  ", "Dame  ", "Koenig"};

//Es wird davon ausgegangen, dass es eine unendliche Anzahl an Karten gibt, 
//aus denen gezogen wird (also 2 identische Karten k�nnen auftauchen, als wenn mehrere Decks verwendet w�rden.)
//bei einer Ziehung ist allerdings jede Karte gleich wahrscheinlich.

class Karte
{
private:
	string farbe;
	string zeichen;
	int zufallsZahlZwischen(int x, int y);
public:
	//Wenn true wird die Karte als ????? ?????? ausgegeben, da sie sozusagen umgedreht ist.
	bool verdeckt;
	//Konstruktoren f�r verdeckte und nichtverdeckte Karten
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
	//nur zum testen der punkteberechnung / splits gedacht
	//hiermit l�sst sich eine bestimmte Karte erzeugen.
	//Auf die richtige Formatierung der strings ist zu achten, sonst werden die Punkte nicht richtig gez�hlt.
	Karte(string f, string z, bool v) {
		farbe = f;
		zeichen = z;
		verdeckt = v;
	}
	//Zum Ausgeben in der Konsole verwendet, wenn die Karte verdeckt
	//ist, werden Fragezeichen zur�ckgegeben.
	string getFarbe() { if (verdeckt) { return "?????"; } else return farbe; }
	string getZeichen() { if (verdeckt) { return "??????"; } else return zeichen; }
};