#include "Karte.h"
#include "Spieler.h"
#include "Spieler.cpp"
#include <iostream>

using namespace std;

void printHand(Spieler s, Spieler c) {
	cout << "\nEigene Hand" << "\n\n";
	
	for (Karte k : s.hand) {
		cout << "  " << k.getFarbe() << "  "
			<< k.getZeichen() << "\n";
	}
	cout << "Aktuelle Punkte: " << s.getPunkte() << "\n";
	
	cout << "\nGegner Hand" << "\n\n";
	for (int i = 0; i < c.hand.size(); i++) {
		cout << "DEALER " << c.hand.at(i).getFarbe() << " "
			<< c.hand.at(i).getZeichen() << "\n";
	}
	cout << "Aktuelle Punkte: " << c.getPunkte() << "\n";
}

int main() {
	system("cls");
	Spieler s = Spieler(true);
	Spieler c = Spieler(false);

	s.startHand();
	c.startHand();
	printHand(s, c);
	system("pause");
	system("cls");
	s.drawCard();
	printHand(s, c);
	system("pause");
	system("cls");
	c.handAufdecken();
	printHand(s, c);
	system("pause");
	//Spieler setzt Geldchips (Minimaleinsatz?)

	//Karten austeilen, Dealer hat 1 verdeckte, Spieler alle offen

	//Weitere Karte oder nicht?

	//Gewinn/Verlieren/ Repeat?

	
}



void updateScreen() {

}
