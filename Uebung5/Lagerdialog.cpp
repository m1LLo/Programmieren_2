/*
 * Lagerdialog.cpp
 *
 *  Created on: 20.05.2013
 *      Author: Steven Weber
 */

#include "Lagerdialog.h"

Lagerdialog::Lagerdialog() {
	int lagergroesse;

	do {
		try {
			cout << "Wie wie viele Artikel soll das Lager maximal aufnehmen koennen?"
					<< endl;
			lagergroesse = leseInteger();
			if (lagergroesse <= 0)
				throw MSG_LAGER_GROESSE_NEGATIV;
		lager = new Lager(lagergroesse);
		} catch (Fehler & f) {
			switch(f) {
			case LagergroesseNegativ:
				cout << MSG_LAGER_GROESSE_NEGATIV << endl;
				break;
			}
		}
	} while (lagergroesse <= 0);
}

int Lagerdialog::leseInteger() {
	int zahl;

	do {
		try {
			cin >> zahl;

			if (cin.fail()) {
				throw MSG_EINGABE_KEINE_ZAHL;
				cin.clear();
				cin.ignore(256, '\n');
			}
		} catch (const char *e) {
		}
	} while (cin.fail());

	return zahl;

}

void Lagerdialog::hauptmenue() {
	int lagergroesse, benutzerEingabe, artikelNr, menge;
	double prozentsatz;
	string ausgabe;

	do {
		cout << "Was moechten Sie tun?" 	<< endl;
		cout << "\t 1 - Artikel anlegen" 	<< endl;
		cout << "\t 2 - Artikel loeschen" 	<< endl;
		cout << "\t 3 - Zugang buchen" 		<< endl;
		cout << "\t 4 - Abgang buchen" 		<< endl;
		cout << "\t 5 - Preis aendern Artikel" << endl;
		cout << "\t 6 - Preis aendern Lager" << endl;
		cout << "\t 7 - Lager ansehen" 		<< endl;
		cout << "\t 8 - Lager leeren" 		<< endl;
		cout << "\t 0 - Programmende\n" 	<< endl;

		cin >> benutzerEingabe;
		switch (benutzerEingabe) {
		case ArtikelAnlegen:
			lager->legeArtikelAn();
			break;
		case ArtikeLoeschen:
			lager->loescheArtikel();
			break;
		case ZugangBuchen:
			lager->bucheMengenZugang();
			break;
		case AbgangBuchen:
			lager->bucheMengenAbgang();
			break;
		case PreisAendernArtikel:
			lager->aendereArtikelpreis();
			break;
		case PreisAendernLager:
			lager->aendereAlleArtikelpreise();
			break;
		case LagerAnsehen:
			cout << lager->toString();
			break;
		case LagerLeeren:
			lager->loescheAlleArtikel();
			cout << "Das Lager ist nun leer." << endl;
			break;
		case Ende:
			cout << "Programmende" << endl;

			break;
		default:
			cout << "Ungueltige Eingabe" << endl;
			break;
		}
	} while (benutzerEingabe != 0);
	lager->~Lager();
}

const char* Lagerdialog::MSG_LAGER_GROESSE_NEGATIV =
		"Das Lager muss eine positive Kapazitaet ausweisen";
const char* Lagerdialog::MSG_EINGABE_KEINE_ZAHL = "Das war keine Zahl!";
