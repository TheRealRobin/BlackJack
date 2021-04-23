#include "Spieler.h"
#include "Karte.h"
#include <iostream>

//Gibt dem Spieler 2 zufällige Karten (1 verdeckt beim Dealer); over21 speichert, ob der Spieler über 21 Punkte hat,
//da er dann automatisch sofort verloren hat. Da startHand nur beim Anfang einer neuen Runde aufgerufen wird,
//kann man over21 hier zurücksetzen:
inline void Spieler::startHand() {
	over21 = false;
	over21Split = false;
	hasSplitHand = false;
	hand.clear();
	if (isHuman) {
		Karte k1 = Karte();
		Karte k2 = Karte();
		hand.push_back(k1);
		hand.push_back(k2);
	} 
	else {
		Karte k1 = Karte();
		Karte k2 = Karte(true); //verdeckte  Karte
		hand.push_back(k1);
		hand.push_back(k2);
	}
}

//Zieht eine Karte und nimmt sie auf die Hand (unverdeckt)
inline void Spieler::drawCard() {
	Karte k = Karte();
	hand.push_back(k);
}
//Macht dasselbe für die zweite Hand
inline void Spieler::drawSplitCard() {
	Karte k = Karte();
	splitHand.push_back(k);
}
//deckt alle Karten in einer Hand auf.
inline void Spieler::handAufdecken() {
	for (int i = 0; i < hand.size(); i++) {
		hand.at(i).verdeckt = false;
		//cout << "Karte aufgedeckt: " << i << "\n";
	}
}

//Zählt die Punkte auf einer gegebenen Hand zusammen, mit Rücksicht auf die Ass = (11 oder 1) Regel
inline int Spieler::getPunkte(vector<Karte> h) {
	int total = 0;
	int aces = 0; //Zählt die Asse, um später möglicherweise die Punktzahl anzupassen
	for (int i = 0; i < h.size(); i++) {
		string z = h.at(i).getZeichen();
		if (z == "Zwei  ") { total += 2; }
		else if (z == "Drei  ") { total += 3; }
		else if (z == "Vier  ") { total += 4; }
		else if (z == "Fuenf ") { total += 5; }
		else if (z == "Sechs ") { total += 6; }
		else if (z == "Sieben") { total += 7; }
		else if (z == "Acht  ") { total += 8; }
		else if (z == "Neun  ") { total += 9; }
		else if (z == "Zehn  ") { total += 10; }
		else if (z == "Bube  ") { total += 10; }
		else if (z == "Dame  ") { total += 10; }
		else if (z == "Koenig") { total += 10; }
		else if (z == "Ass   ") { total += 11; aces++; }
	}
	if (total > 21 && aces > 0) { //Prüft, ob Anzahl angepasst werden muss, manche Asse müssen als 1 gezählt werden
		for (int i = 0; i < h.size(); i++) {
			if (h.at(i).getZeichen() == "Ass   ") {
				total -= 11;
				total += 1;
			}
			if (total <= 21) {
				break;
			}
		}
	}
	return total;
}