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
	delete artikelTab;
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
	} catch (Fehler & f) {
		switch (f) {
		case ArtikelnummerNichtVierstellig:
			cout << meldung_ArtikelNrNichtVierstellig << endl;
			break;
		case ArtikelVorhanden:
			cout << meldung_ArtikelVorhanden << endl;
			break;
		case BezeichnungLeer:
			cout << meldung_BezeichnungLeer << endl;
			break;
		case BestandNegativ:
			cout << meldung_BestandNegativ << endl;
			break;
		case PreisNegativ:
			cout << meldung_PreisNegativ << endl;
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
			cout << meldung_ArtikelNrNichtVorhanden<< endl;
			break;
		case MengeNegativ:
			cout << meldung_MegeNegativ << endl;
			break;
		case LagerLeer:
			cout << meldung_LagerLeer << endl;
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
				cout << meldung_ArtikelNrNichtVorhanden << endl;;
				break;
			case LagerLeer:
				cout << meldung_LagerLeer << endl;
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
			cout << meldung_ArtikelNrNichtVorhanden << endl;
			break;
		case PreisaenderungUngueltig:
			cout << meldung_PreisaenderungUngueltig << endl;
			break;
		case LagerLeer:
			cout << meldung_LagerLeer << endl;
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
				cout << meldung_LagerLeer << endl;
				break;
			case PreisaenderungUngueltig:
				cout << meldung_PreisaenderungUngueltig << endl;
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

	} catch (Fehler & f) {
		switch (f) {
		case LagerLeer:
			cout << meldung_LagerLeer << endl;
			break;
		case ArtikelNichtVorhanden:
			cout << meldung_ArtikelNrNichtVorhanden;
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
			cout << meldung_LagerLeer << endl;
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
		cout << meldung_LagerLeer << endl;

	}
	return o.str();
}
