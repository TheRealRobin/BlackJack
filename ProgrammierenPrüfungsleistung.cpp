#include "Karte.h"
#include "Spieler.h"
#include "Spieler.cpp"
#include <iostream>
#include <Windows.h>

using namespace std;

//GameState ist f�r den main-loop/drawScreen zur Auswahl der n�chsten Schritte gedacht
const enum GameState {INIT, BET, DEAL, NEXTMOVE, PAYOUT, QUIT};
//Die m�glichen Spielz�ge eines menschlichen Spielers
const enum PlayerMove {DRAW, DRAWSPLIT, HOLD, SPLIT, DOUBLEDOWN, SURRENDER};

//Der minimale Wetteinsatz
const int minBet = 25;

//Schreibt die Hand eines gegebenen Spielers in die Konsole
void printHand(Spieler s) {
	if (s.isHuman && !s.hasSplitHand) {
		cout << "\nKarten (Spieler):" << "\n";
		for (Karte k : s.hand) {
			cout << k.getFarbe() << " "
				<< k.getZeichen() << "\n";
		}
		cout << "Aktuelle Punkte (Spieler): " << s.getPunkte(s.hand) << "\n";
	}
	if (s.isHuman && s.hasSplitHand) {
		cout << "\nKarten (Spieler, Hand 1):" << "\n";
		for (Karte k : s.hand) {
			cout << k.getFarbe() << " "
				<< k.getZeichen() << "\n";
		}
		cout << "Aktuelle Punkte (Spieler, Hand 1): " << s.getPunkte(s.hand) << "\n";

		cout << "\nKarten (Spieler, Hand 2):" << "\n";
		for (Karte k : s.splitHand) {
			cout << k.getFarbe() << " "
				<< k.getZeichen() << "\n";
		}
		cout << "Aktuelle Punkte (Spieler, Hand 2): " << s.getPunkte(s.splitHand) << "\n";
	}
	if (!s.isHuman) {
		cout << "\nKarten (Dealer):" << "\n";
		for (Karte k : s.hand) {
			cout << k.getFarbe() << " "
				<< k.getZeichen() << "\n";
		}
		cout << "Aktuelle Punkte (Dealer): " << s.getPunkte(s.hand) << "\n";
	}
}

//Entscheidet basierend auf userinput, was der menschliche Spieler als n�chstes tun wird.
PlayerMove askForNextMove() {
	bool redo = false;
	char c = ' '; //d f h s x q
	do {
		cout << "\n\nWas m\224chtest du tun?\nd -- Karte Ziehen\nf -- Karte Ziehen (Hand 2, nur bei Split)\nh -- Halten\ns -- Split(nur m\224glich bei doppelter Karte in Starthand; Deine beiden Karten werden nun als jeweils seprerate Hand gewertet, beide mit dem anf\204nglichen Einsatz.)\nx -- Verdoppeln (verdoppelt die Wette, zieht eine dritte Karte und beendet den Zug)\nq -- Aufgeben (Beendet das Spiel)\n[d/f/h/s/x/q]:";
		if (!(cin >> c) || !(c=='d'||c=='f'||c=='h'||c=='s'||c=='x'||c=='q')) {
			redo = true;
			cin.clear();
			cin.ignore(10000, '\n');
		}
	} while (redo);
	//DRAW DRAWSPLIT HOLD SPLIT DOUBLEDOWN SURRENDER
	//DRAW soll eine Karte in die Hand (1) ziehen.
	//DRAWSPLIT soll eine Karte in die Hand(2) ziehen.
	//HOLD soll keine Karte ziehen und abwarten, was der Dealer macht.
	//SPLIT soll, wenn m�glich, die Hand des Spielers in zwei gesonderte H�nde unterteilen, die seperat gespielt werden, um den maximalen Gewinn zu erh�hen.
	//DOUBLEDOWN soll den Einsatz verdoppeln, eine Karte in die Hand(1) ziehen und den Zug beenden. (Bei Split nicht m�glich)
	//SURRENDER soll das Spiel beenden.
	if (c == 'd') {
		return DRAW;
	}
	else if (c == 'f') {
		return DRAWSPLIT;
	}
	else if (c == 'h') {
		return HOLD;
	}
	else if (c == 's') {
		return SPLIT;
	}
	else if (c == 'x') {
		return DOUBLEDOWN;
	}
	else if (c == 'q') {
		return SURRENDER;
	}
}

//Schreibt basierend auf GameState verschiedene Dinge in die Konsole
void drawScreen(GameState state, Spieler s, Spieler c) {
	system("cls");
	switch (state) {
	case INIT:
		cout << "Willkommen bei BlackJack gegen den Computer. (Robin B\224hn, 2021))\n";
		Sleep(2000);
		break;
	case BET:
		cout << "Bitte w\204hle deinen Wetteinsatz.\n";
		Sleep(1000);
		break;
	case DEAL:
		cout << "Der aktuelle Wetteinsatz betr\204gt " << s.bet_amount << " Chips.\n"; 
		cout << "Die Karten wurden folgenderma\341en verteit:\n";
		Sleep(500);
		printHand(c);
		Sleep(500);
		printHand(s);
		break;
	case NEXTMOVE:
		cout << "Der aktuelle Wetteinsatz betr\204gt " << s.bet_amount << " Chips.\n";
		cout << "Die Karten wurden folgenderma\341en verteit:\n";
		printHand(c);
		printHand(s);
		break;
	case PAYOUT:
		if (!s.hasSplitHand) { cout << "Der aktuelle Wetteinsatz betr\204gt " << s.bet_amount << " Chips.\n"; }
		if (s.hasSplitHand) { cout << "Der aktuelle Wetteinsatz betr\204gt " << s.bet_amount*2 << " Chips.\n"; }
		cout << "Dealer spielt:\n";
		printHand(c);
		printHand(s);
		Sleep(500);
		break;
	case QUIT:
		cout << "Bitte warte, bis das Programm sich beendet........";
		Sleep(500);
		break;
	default:
		break;
	}
}

//Entscheidet basierend auf userinput, wie viel der Spieler einsetzt. Da das Geld als Chips z�hlt, ist die kleinste unterteilbare Einheit davon 1 (in anderen Worten, Chips sind ganzzahlig).
int askForBetAmount(Spieler s) {
	int amount;
	bool redo;
	do {
		system("cls");
		cout << "Der Minimaleinsatz betr\204gt " << minBet <<" Chips. Du hast aktuell noch "
			<< s.geldchips << " Chips.\nBei Gewinn wird im Verh\204ltnis 1:1 ausgezahlt, bei einem natural Black Jack 3:2.\n"
			<< "Wetteinsatz eingeben [" << minBet << "-" << s.geldchips << "]:";
		redo = false;
		//Userinput testen, ob eingabe eine Zahl zw. dem minimum und den verbleibenden geldchips ist.
		if ( (!(cin >> amount)) || (amount < minBet) || (amount > s.geldchips) ) {
			redo = true;
			cin.clear();
			cin.ignore(10000, '\n');
		}
	} while (redo);
	cout << "Der Einsatz diese Runde betr\204gt " << amount << " Chips.\n";
	return amount;
};

//Hier soll der genaue Spieler aus main() verwendet werden, daher Spieler &s
//Die Implementierung der oben beschriebenen Spielz�ge
bool doMove(Spieler &s, PlayerMove next) {
	bool playerFinished = false;
	if (next == DRAW) {
		s.drawCard();
		if (s.getPunkte(s.hand) > 21 && !s.hasSplitHand) { playerFinished = true; s.over21 = true; cout << "\nLeider \232berkauft!"; }
		if (s.getPunkte(s.hand) > 21 && s.hasSplitHand) {
			playerFinished = false;
			s.over21 = true;
			cout << "\nLeider \232berkauft!";
			if (s.getPunkte(s.splitHand) > 21) { playerFinished = true; }
		}
		else {
			cout << "\nEine Karte gezogen (Hand 1).";
		}
		Sleep(3000);
	}
	if (next == DRAWSPLIT) {
		if (s.hasSplitHand && (s.getPunkte(s.splitHand) < 21)) {
			s.drawSplitCard();
			if (s.getPunkte(s.splitHand) > 21) {
				playerFinished = false;
				s.over21Split = true;
				cout << "\nLeider \232berkauft (Split Hand)!";
				if (s.getPunkte(s.hand) > 21) { playerFinished = true; }
			}
			else {
				cout << "\nEine Karte gezogen (Hand 2).";
			}
		}
		else {
			cout << "\nKann nur bei aktivem Split funktionieren.";
			playerFinished = false;
		}
		Sleep(3000);
	}
	if (next == HOLD) {
		playerFinished = true;
		cout << "\nKarten werden gehalten.";
		Sleep(3000);
	}
	if (next == SPLIT) {
		if (s.hand.size() == 2 && s.hand.at(0).getZeichen() == s.hand.at(1).getZeichen() && (s.geldchips >= s.bet_amount*2)) {
			s.splitHand.push_back(s.hand.at(1));
			s.hand.erase(s.hand.begin() + 1);
			s.hasSplitHand = true;
			cout << "\nKarten gesplittet.";
		}
		else {
			cout << "\nSplitten ist zur Zeit nicht m\224glich.";
			playerFinished = false;
		}
		Sleep(3000);
	}
	if (next == DOUBLEDOWN) {
		if (!s.hasSplitHand) {
			s.drawCard();
			if (s.geldchips >= s.bet_amount * 2) {
				s.bet_amount *= 2;
				playerFinished = true;
				cout << "\nLetzte Karte gezogen, Wette verdoppelt";
			}
			else {
				playerFinished = false;
				cout << "\nNicht gen\201gend Chips verbleibend.";
			}
		}
		else {
			cout << "\nNur m\224glich wenn kein Split vorliegt.";
			playerFinished = false;
		}
		Sleep(3000);
	}
	if (next == SURRENDER) {
		cout << "Spiel wird verlassen.........";
		s.bet_amount = 0;
		s.quitsQame = true;
		playerFinished = true;
		Sleep(1500);
	}
	return playerFinished;
}

//Berechnet den Gewinn/Verlust f�r die Hand (und ggf. Split-hand) des Spielers
void determineResult(Spieler& s, Spieler& c) {
	int spunkte = s.getPunkte(s.hand);
	int cpunkte = c.getPunkte(c.hand);
	int splitpunkte = s.getPunkte(s.splitHand);
	//Spieler �berkauft
	if (s.over21) {
		cout << "\nVerloren. Du bekommst deinen Einsatz von " << s.bet_amount << " Chips nicht zur\201ck.";
		s.geldchips -= s.bet_amount;
		Sleep(5000);
	}
	//Spieler hat 21 und dealer nicht (Natural)
	else if (cpunkte != 21 && spunkte == 21) {
		cout << "\nDu hast " << (int)(s.bet_amount * 1.5) << " Chips GEWONNEN! Du bekommst deinen Einsatz im Verh\204ltnis 3:2 zur\201ck.";
		s.geldchips += (int)(s.bet_amount * 1.5);
		Sleep(5000);
	}
	//Spieler unter 21 aber Dealer �berkauft
	else if (cpunkte > 21 && spunkte < 21) {
		cout << "\nDu hast " << s.bet_amount << " Chips GEWONNEN! Du bekommst deinen Einsatz im Verh\204ltnis 1:1 zur\201ck.";
		s.geldchips += s.bet_amount;
		Sleep(5000);
	}
	//Spieler unter 21 aber mehr als Dealer
	else if (spunkte < 21 && (spunkte > cpunkte)) {
		cout << "\nDu hast " << s.bet_amount << " Chips GEWONNEN! Du bekommst deinen Einsatz im Verh\204ltnis 1:1 zur\201ck.";
		s.geldchips += s.bet_amount;
		Sleep(5000);
	}
	//Dealer gleicht Spieler
	else if (cpunkte == spunkte && !s.over21) {
		cout << "\nUnentschieden. Du beh\204lst deine Chips und hast noch " << s.geldchips << ".";
		Sleep(5000);
	}
	//Spieler hat weniger als 21 und weniger als Dealer
	else if (spunkte < 21 && (spunkte < cpunkte)) {
		cout << "\nVerloren. Du bekommst deinen Einsatz von " << s.bet_amount << " Chips nicht zur\201ck.";
		s.geldchips -= s.bet_amount;
		Sleep(5000);
	}
	//Alle oberen nochmal, aber f�r die zweite Hand falls vorher gesplittet wurde.
	if (s.hasSplitHand) {
		if (s.over21Split) {
			cout << "\n(Split) Verloren. Du bekommst deinen Einsatz von " << s.bet_amount << " Chips nicht zur\201ck.";
			s.geldchips -= s.bet_amount;
			Sleep(5000);
		}
		else if (cpunkte != 21 && splitpunkte == 21) {
			cout << "\n(Split) Du hast " << (int)(s.bet_amount * 1.5) << " Chips GEWONNEN! Du bekommst deinen Einsatz im Verh\204ltnis 3:2 zur\201ck.";
			s.geldchips += (int)(s.bet_amount * 1.5);
			Sleep(5000);
		}
		else if (cpunkte > 21 && splitpunkte < 21) {
			cout << "\n(Split) Du hast " << s.bet_amount << " Chips GEWONNEN! Du bekommst deinen Einsatz im Verh\204ltnis 1:1 zur\201ck.";
			s.geldchips += s.bet_amount;
			Sleep(5000);
		}
		else if (splitpunkte < 21 && (splitpunkte > cpunkte)) {
			cout << "\nDu hast " << s.bet_amount << " Chips GEWONNEN! Du bekommst deinen Einsatz im Verh\204ltnis 1:1 zur\201ck.";
			s.geldchips += s.bet_amount;
			Sleep(5000);
		}
		else if (cpunkte == splitpunkte && !s.over21Split) {
			cout << "\nUnentschieden. Du beh\204lst deine Chips und hast noch " << s.geldchips << ".";
			Sleep(5000);
		}
		else if (splitpunkte < 21 && (splitpunkte < cpunkte)) {
			cout << "\nVerloren. Du bekommst deinen Einsatz von " << s.bet_amount << " Chips nicht zur\201ck.";
			s.geldchips -= s.bet_amount;
			Sleep(5000);
		}
	}
}

//Main-Loop / Einstiegspunkt
int main() {
	bool run = true;
	GameState state = INIT;
	Spieler s = Spieler(true);
	Spieler c = Spieler(false);
	drawScreen(state, s, c);
	while (run) {
		//BET Spieler setzt Geldchips (Minimaleinsatz?)
		state = BET;
		drawScreen(state, s, c);
		s.bet_amount = askForBetAmount(s);
		Sleep(1500);
		//DEAL Alle bekommen ihre Starthand, Dealer hat 1 verdeckte, Spieler alle offen
		state = DEAL;
		s.startHand();
		c.startHand();
		drawScreen(state, s, c);
		//NEXTMOVE
		
		bool playerFinished = false;
		do {
			state = NEXTMOVE;
			drawScreen(state, s, c);
			PlayerMove next = askForNextMove();
			playerFinished = doMove(s, next);
			if (s.quitsQame) { run = false; state = QUIT; }
			drawScreen(state, s, c);
		} while (!playerFinished);
		
		//QUIT
		if (state == QUIT) { return 0; }

		//PAYOUT nur wenn nicht quit
		state = PAYOUT;
		c.handAufdecken();
		drawScreen(state, s, c);
		
		//Dealer spielt sich hoch -> Soft 17 halten regel wird angewendet
		while (c.getPunkte(c.hand) < 17) { c.drawCard(); drawScreen(state, s, c); }
		
		determineResult(s, c);

		//Nochmal?
		cout << "\nNochmal spielen [y/n]?\n";
		bool redo;
		char c = ' ';
		do {
			redo = false;
			if (!(cin >> c) || !(c == 'y' || c == 'n')) {
				redo = true;
				cin.clear();
				cin.ignore(10000, '\n');
			}
			if (c == 'y') { run = true; }
			if (c == 'n') { run = false; }
		} while (redo);
	}
}