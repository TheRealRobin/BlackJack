#pragma once
#include <string>
#include <vector>
#include "Karte.h"

class Spieler
{
public:
	//Menschliche Spieler sollen am Anfang ihren Namen w�hlen k�nnen
	string name;
	//Verbleibendes Geld im Geldbeutel/zur Verf�gung
	int geldchips;
	//Liste der Karten auf der Hand
	vector<Karte> hand;
	//Wenn false, dann ist der Spieler computergesteuert / der Casinodealer
	bool isHuman;
	//Zieht zwei Karten, eine verdeckt ist der Spieler not human
	void startHand();
	//Zieht eine Karte
	void drawCard();
	//Gibt die hand zur�ck
	vector<Karte> getHand() {return hand;}
	//Deckt die Hand auf
	void handAufdecken();
	//Hand zusammenz�hlen
	int getPunkte();
	//Startparameter f�r Spieler
	Spieler(bool human) {
		geldchips = 1000;
		isHuman = human;
	}
};