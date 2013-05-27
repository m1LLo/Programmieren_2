/*
 * Lager.cpp
 *
 *  Created on: 19.05.2013
 *      Author: Steven Weber
 */

#include "Lager.h"
#include <sstream>

Lager::Lager(int lagergroesse) {
	anzahlArtikel = 0;
	artikelTab = new Artikel*[lagergroesse];
	this->lagergroesse = lagergroesse;
}

Lager::Lager(const Lager& lager) {
	this->lagergroesse = lager.lagergroesse;
	artikelTab = new Artikel*[lagergroesse];
	anzahlArtikel = lager.anzahlArtikel;
	// vorhandene Konten kopieren
	for (int i = 0; i < anzahlArtikel; i++) {
		Artikel* tmp = lager.artikelTab[i];
		artikelTab[i] = new Artikel(*tmp);
	}
}

Lager& Lager::operator =(const Lager& lager) {
		if (this == &lager)
			return *this;

		// bisherige Artikel-Objekte destruieren
		loescheAlleArtikel();
		// Attribute uebertragen und das Array anlegen
		this->lagergroesse = lager.lagergroesse;
		artikelTab = new Artikel*[lagergroesse];
		anzahlArtikel = lager.anzahlArtikel;

		// vorhandene Artikel kopieren
		for (int i = 0; i < anzahlArtikel; i++) {
			Artikel* tmp = lager.artikelTab[i];
			artikelTab[i] = new Artikel(*tmp);
		}
		return *this;
}

Lager::~Lager() {
	cout << "Destruktor"<< endl;
	loescheAlleArtikel();
	delete[] artikelTab;	//loescht das Array und nicht nur das erste Element
	artikelTab = 0;
}

void Lager::legeArtikelAn() {
	int nummer, bestand, tmp;
	double preis;
	string bezeichnung;

	try {
		cout << "Artikelnummer:" << endl;
		cin >> nummer;
		if ((nummer < 1000) || (nummer >= 10000))
			throw ArtikelnummerNichtVierstellig;
		for (int i = 0; i < anzahlArtikel; i++) {
			tmp = artikelTab[i]->getArtikelNr();
			if (nummer == tmp)
				throw ArtikelVorhanden;
		}

		cout << "Bezeichnung:" << endl;
		cin >> bezeichnung;
		if (bezeichnung == "")
			throw BezeichnungLeer;

		cout << "Bestand:" << endl;
		cin >> bestand;
		if (bestand < 0)
			throw BestandNegativ;

		cout << "Preis:" << endl;
		cin >> preis;
		if (preis < 0)
			throw PreisNegativ;

		artikelTab[anzahlArtikel] = new Artikel(nummer, bezeichnung, bestand, preis);
		anzahlArtikel++;
	} catch (Fehler &f) {
		switch (f) {
		case ArtikelnummerNichtVierstellig:
			cout << MSG_ARTIKELNR_NICHT_VIERSTELLIG << endl;
			break;
		case ArtikelVorhanden:
			cout << MSG_ARTIKEL_VORHANDEN << endl;
			break;
		case BezeichnungLeer:
			cout << MSG_BEZEICHNUNG_LEER << endl;
			break;
		case BestandNegativ:
			cout << MSG_BESTAND_NEGATIV << endl;
			break;
		case PreisNegativ:
			cout << MSG_PREIS_NEGATIV << endl;
			break;
		}
	}
}

/**
 * Wieso besser toString() ?
 */
//void Lager::schreibeArtikel() {
//	int zaehler = 0;
//	for (zaehler = 0; zaehler < anzahlArtikel; zaehler++) {
//		cout << "Artikel #" << zaehler << endl;
//		cout << "\t" << "Artikelnummer: " << artikelTab[zaehler]->getArtikelNr() << endl;
//		cout << "\t" << "Bezeichnung..: " << artikelTab[zaehler]->getBezeichnung() << endl;
//		cout << "\t" << "Bestand......: " << artikelTab[zaehler]->getBestand() << endl;
//		cout << "\t" << "Preis........: " << artikelTab[zaehler]->getArtikelPreis() << "\n" << endl;
// 	}
//}
/**
 * gibt die Position des Artikels im Lager zurueck
 */
int Lager::findeArtikel(int artikelNr) {
	for (int i = 0; i < anzahlArtikel; i++) {
		if (artikelTab[i]->getArtikelNr() == artikelNr)
			return i;
	}
	return -1;
}

void Lager::bucheMengenZugang() {
	int artikelNr, menge;
	try {
		if (anzahlArtikel == 0)
					throw LagerLeer;
		cout
				<< "Zu welchem Artikel moechten Sie etwas hinzubuchen? (Artikelnummer)"
				<< endl;
		cin >> artikelNr;
		int artikelPosition = findeArtikel(artikelNr);
		if (artikelPosition < 0)
			throw ArtikelNichtVorhanden;
		cout << "Menge:" << endl;
		cin >> menge;
		if (menge < 0)
			throw MengeNegativ;
		artikelTab[artikelPosition]->bucheZugang(menge);
	} catch (Fehler & f) {
		switch (f){
		case ArtikelNichtVorhanden:
			cout << MSG_ARTIKELNR_NICHT_VORHANDEN<< endl;
			break;
		case MengeNegativ:
			cout << MSG_MEGE_NEGATIV << endl;
			break;
		case LagerLeer:
			cout << MSG_LAGER_LEER << endl;
			break;
		}
	}
}

void Lager::bucheMengenAbgang() {
	int artikelNr, menge;
	try {
		if (anzahlArtikel == 0)
			throw LagerLeer;
		cout
				<< "Von welchem Artikel moechten Sie etwas abbuchen? (Artikelnummer)"
				<< endl;
		cin >> artikelNr;
		int artikelPosition = findeArtikel(artikelNr);
		if (artikelPosition < 0)
			throw ArtikelNichtVorhanden;
		cout << "Menge:" << endl;
		cin >> menge;
		artikelTab[artikelPosition]->bucheAbgang(menge);
	} catch (Fehler & f) {
			switch (f){
			case ArtikelNichtVorhanden:
				cout << MSG_ARTIKELNR_NICHT_VORHANDEN << endl;;
				break;
			case LagerLeer:
				cout << MSG_LAGER_LEER << endl;
				break;
			}
	}
}

void Lager::aendereArtikelpreis() {
	int artikelNr;
	try {
		if (anzahlArtikel == 0)
					throw LagerLeer;
		double prozentsatz;
		cout
				<< "Von welchem Artikel soll der Preis veraendert werden? (Artikelnummer)"
				<< endl;
		cin >> artikelNr;
		int artikelPosition = findeArtikel(artikelNr);
		if (artikelPosition < 0)
			throw ArtikelNichtVorhanden;
		cout << "Prozentsatz" << endl;
		cin >> prozentsatz;
		if ((prozentsatz <= MAX_PREISSENKUNG_PROZENT) || (prozentsatz >= MAX_PREISERHOEHUNG_PROZENT))
			throw PreisaenderungUngueltig;
		artikelTab[artikelPosition]->aenderePreis(prozentsatz);
	} catch (Fehler & f) {
		switch (f) {
		case ArtikelNichtVorhanden:
			cout << MSG_ARTIKELNR_NICHT_VORHANDEN << endl;
			break;
		case PreisaenderungUngueltig:
			cout << MSG_PREIS_AENDERUNG_UNGUELTIG << endl;
			break;
		case LagerLeer:
			cout << MSG_LAGER_LEER << endl;
			break;
		}
	}
}

void Lager::aendereAlleArtikelpreise() {
	double prozentsatz;
	try {
		if (anzahlArtikel == 0)
			throw LagerLeer;
		cout << "Prozentsatz" << endl;
		cin >> prozentsatz;
		if ((prozentsatz <= MAX_PREISSENKUNG_PROZENT) || (prozentsatz >= MAX_PREISERHOEHUNG_PROZENT))
			throw PreisaenderungUngueltig;
		for(int i = 0; i < anzahlArtikel; i++) {
			artikelTab[i]->aenderePreis(prozentsatz);
		}
	} catch (Fehler & f) {
		switch(f) {
			case LagerLeer:
				cout << MSG_LAGER_LEER << endl;
				break;
			case PreisaenderungUngueltig:
				cout << MSG_PREIS_AENDERUNG_UNGUELTIG << endl;
				break;
		}
	}
}


void Lager::loescheArtikel() {
	int artikelNr;

	try {
		if (anzahlArtikel == 0)
					throw LagerLeer;
		cout << "Artikelnummer:" << endl;
		cin >> artikelNr;
		int artikelPosition = findeArtikel(artikelNr);

		if (artikelPosition < 0) {
			throw ArtikelNichtVorhanden;
		}
		if (artikelPosition == (anzahlArtikel - 1)) {
			delete artikelTab[artikelPosition];
		}
		if (artikelPosition != (anzahlArtikel - 1)) {
			artikelTab[artikelPosition] = artikelTab[anzahlArtikel - 1];
		}
		cout << "### Der Artikel #" << artikelPosition
				<< " wurde geloescht. ###" << endl;
		anzahlArtikel--;

	} catch (enum Fehler &f) {
		switch (f) {
		case LagerLeer:
			cout << MSG_LAGER_LEER << endl;
			break;
		case ArtikelNichtVorhanden:
			cout << MSG_ARTIKELNR_NICHT_VORHANDEN;
			break;
		}
	}
}

void Lager::loescheAlleArtikel() {
	try {
		if (anzahlArtikel == 0)
			throw LagerLeer;
		for (int i = 0; i < anzahlArtikel; i++) {
			delete artikelTab[i];
		}
		anzahlArtikel = 0;

	} catch (Fehler & f) {
		switch (f) {
		case LagerLeer:
			cout << MSG_LAGER_LEER << endl;
			break;
		}
	}
}

string Lager::toString() const {
	ostringstream o;
	try {
		if (anzahlArtikel == 0)
			throw LagerLeer;

		for (int i = 0; i < anzahlArtikel; i++)
			o << artikelTab[i]->toString() << "\n";
	} catch (Fehler & f) {
		cout << MSG_LAGER_LEER << endl;

	}
	return o.str();
}

const char* Lager::MSG_ARTIKELNR_NICHT_VORHANDEN =
		"Artikel ist nicht vorhanden";
const char* Lager::MSG_ARTIKELNR_NICHT_VIERSTELLIG =
		"Artikelnummer muss vierstellig, positiv sein!";
const char* Lager::MSG_ARTIKEL_VORHANDEN =
		"Diese Artikelnummer ist bereits vergeben!";
const char* Lager::MSG_BESTAND_NEGATIV = "Bestand muss positiv sein!";
const char* Lager::MSG_BEZEICHNUNG_LEER =
		"Bezeichnung darf nicht leer sein!";
const char* Lager::MSG_EINGABE_NEGATIV =
		"Bitte eine positive Zahl eingeben!";
const char* Lager::MSG_EINGABE_KEINE_ZAHL = "Das war keine Zahl!";
const char* Lager::MSG_PREIS_NEGATIV = "Preis muss positiv sein!";
const char* Lager::MSG_LAGER_LEER = "Das Lager ist leer!";
const char* Lager::MSG_LAGER_GROESSE_NEGATIV =
		"Das Lager muss eine positive Kapazitaet ausweisen";
const char* Lager::MSG_MEGE_NEGATIV =
		"Es duerfen keine negativen Mengen gebucht werden!";
const char* Lager::MSG_BESTAND_KLEINER_MENGE =
		"So viele Artikel sind nicht mehr vorhanden!";
const char* Lager::MSG_PREIS_AENDERUNG_UNGUELTIG =
		"Bitte Preis innerhalb einer Grenze von -70% - 300% aendern!";
