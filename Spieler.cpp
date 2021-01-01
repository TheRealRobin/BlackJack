#include "Spieler.h"
#include "Karte.h"
#include <iostream>

inline void Spieler::startHand() {
	hand.clear();
	if (isHuman) {
		Karte k1 = Karte();
		Karte k2 = Karte();
		hand.push_back(k1);
		hand.push_back(k2);
	} 
	else {
		Karte k1 = Karte();
		Karte k2 = Karte(true);
		hand.push_back(k1);
		hand.push_back(k2);
	}
}

inline void Spieler::drawCard() {
	Karte k = Karte();
	hand.push_back(k);
}

inline void Spieler::handAufdecken() {
	for (int i = 0; i < hand.size(); i++) {
		hand.at(i).verdeckt = false;
		//cout << "Karte aufgedeckt: " << i << "\n";
	}
}

inline int Spieler::getPunkte() {
	int total = 0;
	int aces = 0;
	for (int i = 0; i < hand.size(); i++) {
		string z = hand.at(i).getZeichen();
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
	if (total > 21 && aces > 0) {
		for (int i = 0; i < hand.size(); i++) {
			if (hand.at(i).getZeichen() == "Ass   ") {
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