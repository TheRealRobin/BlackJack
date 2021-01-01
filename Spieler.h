#pragma once
#include <string>
#include <vector>
#include "Karte.h"

class Spieler
{
public:
	//Menschliche Spieler sollen am Anfang ihren Namen wählen können
	string name;
	//Verbleibendes Geld im Geldbeutel/zur Verfügung
	int geldchips;
	//Liste der Karten auf der Hand
	vector<Karte> hand;
	//Wenn false, dann ist der Spieler computergesteuert / der Casinodealer
	bool isHuman;
	//Zieht zwei Karten, eine verdeckt ist der Spieler not human
	void startHand();
	//Zieht eine Karte
	void drawCard();
	//Gibt die hand zurück
	vector<Karte> getHand() {return hand;}
	//Deckt die Hand auf
	void handAufdecken();
	//Hand zusammenzählen
	int getPunkte();
	//Startparameter für Spieler
	Spieler(bool human) {
		geldchips = 1000;
		isHuman = human;
	}
};