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
	//Wird true wenn der Spieler überkauft hat (Mehr als 21 Punkte)
	bool over21 = false;
	bool over21Split = false;
	//Liste der Karten auf der Hand
	vector<Karte> hand;
	//Wird nur beim spielzug Split verwendet. Speichert die zweite Hand
	//hasSplitHand ist true, wenn die zweite Hand bei der Punkteberechnung berücksichtigt werden soll.
	vector<Karte> splitHand;
	bool hasSplitHand;
	//Wenn false, dann ist der Spieler computergesteuert / der Casinodealer und agiert dementsprechend
	bool isHuman;
	//Zieht zwei Karten, eine verdeckt ist der Spieler not human
	void startHand();
	//Zieht eine Karte
	void drawCard();
	void drawSplitCard();
	//Gibt die hand zurück
	vector<Karte> getHand() { return hand; }
	//Deckt die Hand auf
	void handAufdecken();
	//Hand zusammenzählen
	int getPunkte(vector<Karte> h);
	//Die letzten Gewinne/verluste des Spielers und der Rundenzähler
	vector<vector<int>> winHistory;
	int runde;
	//Startparameter für Spieler
	Spieler(bool human) {
		geldchips = 1000; //Startchips
		isHuman = human; 
		runde = 1; //Damit der Rundenzähler nicht bei 0 anfängt
	}
};