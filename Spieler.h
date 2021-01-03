#pragma once
#include <string>
#include <vector>
#include "Karte.h"

class Spieler
{
public:
	//Verbleibendes Geld im Geldbeutel/ Wettgeld
	int geldchips;
	int bet_amount = 0;
	//Wird true wenn das Spiel verlassen wird
	bool quitsQame;
	//Wird true wenn der Spieler �berkauft hat (Mehr als 21 Punkte)
	bool over21 = false;
	bool over21Split = false;
	//Liste der Karten auf der Hand
	vector<Karte> hand;
	//Wird nur beim spielzug Split verwendet. Speichert die zweite Hand
	vector<Karte> splitHand;
	bool hasSplitHand;
	//Wenn false, dann ist der Spieler computergesteuert / der Casinodealer
	bool isHuman;
	//Zieht zwei Karten, eine verdeckt ist der Spieler not human
	void startHand();
	//Zieht eine Karte
	void drawCard();
	void drawSplitCard();
	//Gibt die hand zur�ck
	vector<Karte> getHand() { return hand; }
	//Deckt die Hand auf
	void handAufdecken();
	//Hand zusammenz�hlen
	int getPunkte(vector<Karte> h);
	//Die letzten Gewinne/verluste des Spielers
	vector<vector<int>> winHistory;
	int runde;
	//Startparameter f�r Spieler
	Spieler(bool human) {
		geldchips = 1000;
		isHuman = human;
		runde = 1;
	}
};