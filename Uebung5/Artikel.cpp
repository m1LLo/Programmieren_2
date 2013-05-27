/**
 * Methoden der Klasse Artikel.
 *
 * @file		Artikel.cpp
 * @date		04.05.2013
 * @author		Steven Weber
 */

#include "Artikel.h"
#include <sstream>

Artikel::Artikel(int artikelNr, string bezeichnung)
{
	if (artikelNr < 1000 || artikelNr >= 10000)
	{
		throw MSG_ARTIKELNR_NICHT_VIERSTELLIG;
	}

	if (bezeichnung.empty())
	{
		throw MSG_BEZEICHNUNG_LEER;
	}

	this->artikelNr = artikelNr;
	this->bezeichnung = bezeichnung;
	this->bestand = 0;
	this->preis = 0.0;
}

Artikel::Artikel(int artikelNr, string bezeichnung, int bestand)
{
	if (artikelNr < 1000 || artikelNr >= 10000)
	{
		throw MSG_ARTIKELNR_NICHT_VIERSTELLIG;
	}
	if (bezeichnung.empty())
	{
		throw MSG_BEZEICHNUNG_LEER;
	}

	if (bestand < 0)
	{
		throw MSG_BESTAND_NEGATIV;
	}

	this->artikelNr = artikelNr;
	this->bezeichnung = bezeichnung;
	this->bestand = bestand;
	this->preis = 0.0;
}

Artikel::Artikel(int artikelNr, string bezeichnung, int bestand,
		double preis)
{
	if (artikelNr < 1000 || artikelNr >= 10000)
	{
		throw MSG_ARTIKELNR_NICHT_VIERSTELLIG;
	}

	if (bezeichnung.empty())
	{
		throw MSG_BEZEICHNUNG_LEER;
	}

	if (bestand < 0)
	{
		throw MSG_BESTAND_NEGATIV;
	}

	if (preis < 0)
	{
		throw MSG_PREIS_NEGATIV;
	}

	this->artikelNr = artikelNr;
	this->bezeichnung = bezeichnung;
	this->bestand = bestand;
	this->preis = preis;
}

void Artikel::bucheZugang(int menge)
{
	if (menge < 0)
	{
		throw MSG_MEGE_NEGATIV;
	}
	this->bestand += menge;
}

void Artikel::bucheAbgang(int menge)
{
	if (menge < 0)
	{
		throw MSG_MEGE_NEGATIV;
	}

	if ((this->bestand) - (menge) < 0)
	{
		throw MSG_BESTAND_KLEINER_MENGE;
	}

	this->bestand -= menge;
}

void Artikel::aenderePreis(double prozent)
{
	int hundert = 100;
	if (prozent > MAX_PREISERHOEHUNG_PROZENT)
	{
		throw MSG_PREIS_AENDERUNG_UNGUELTIG;
	}

	if (prozent < MAX_PREISSENKUNG_PROZENT)
	{
		throw MSG_PREIS_AENDERUNG_UNGUELTIG;
	}


	this->preis = (preis) * (1 + (prozent)/100);
}

string Artikel::toString() const {
	ostringstream o;
	o << "ArtikelNr: " << artikelNr << "\t"
			<< "Bezeichnung: "<< bezeichnung << "\t"
			<< "Bestand: "<< bestand << "\t"
			<< "Preis: " << preis;
	return o.str();
}
