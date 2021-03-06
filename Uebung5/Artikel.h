/**
 * @file		Artikel.h
 * @date		04.05.2013
 * @author		Steven Weber, Markus Leitz
 *
 * @param bezeichnung	nicht leer
 * @param artikelNr		4-stellig, positiv, einzigartig
 * @param bestand		nicht kleiner 0
 * @param preis			nicht kleiner 0
 *
 * Erstellt Artikelobjekte
 *
 */

#ifndef ARTIKEL_H_
#define ARTIKEL_H_

#include "Kostanten.h"

#include <string>
using namespace std;

class Artikel
{
public:
	/** Konstruktor mit 2 Parametern
	 *
	 * @param artikelNr  einzigartig, vierstellig, positiv
	 * @param bezeichnung darf nicht leer sein
	 */
	Artikel(int artikelNr, string bezeichnung);

	/** Kontruktor mit 3 Parametern
	 *
	 * @param artikelNr  einzigartig, vierstellig, positiv
	 * @param bezeichnung darf nicht leer sein
	 * @param bestand	darf nicht kleiner 0 werden
	 */
	Artikel(int artikelNr, string bezeichnung, int bestand);

	/** Konstruktor mit 4 Parametern
	 *
	 * @param artikelNr  einzigartig, vierstellig, positiv
	 * @param bezeichnung darf nicht leer sein
	 * @param bestand	darf nicht kleiner 0 werden
	 * @param preis 	darf nicht kleiner 0 werden
	 */
	Artikel(int artikelNr, string bezeichnung, int bestand, double preis);

	~Artikel();	//Destruktor

	// SET-Methoden
	void setArtikelNr(int artikelNrNeu)
	{
		if (artikelNrNeu < 1000 || artikelNrNeu >= 10000)
		{
			throw MSG_ARTIKELNR_NICHT_VIERSTELLIG;
		}
		artikelNr = artikelNrNeu;
	}

	void setBezeichnung(string bezeichnungNeu)
	{
		if (bezeichnungNeu.empty())
		{
			throw MSG_BEZEICHNUNG_LEER;
		}
		bezeichnung = bezeichnungNeu;
	}

	void setArtikelPreis(double artikelPreisNeu)
	{
		if (artikelPreisNeu < 0)
		{
			throw MSG_PREIS_NEGATIV;
		}
		this->preis = artikelPreisNeu;
	}

	// GET-Methoden
	int getArtikelNr() const
	{
		return artikelNr;
	}

	double getArtikelPreis() const
	{
		return preis;
	}

	int getBestand() const
	{
		return bestand;
	}

	const string& getBezeichnung() const
	{
		return bezeichnung;
	}

	/** Addiert menge zu bestand
	 *
	 * @param menge darf nicht kleiner 0 sein
	 */
	void bucheZugang(int menge);

	/** Subtrahiert menge von bestand
	 *
	 * @param menge darf nicht kleiner 0 sein
	 */
	void bucheAbgang(int menge);

	/**
	 * Aendert artikelPreis um einen bestimmten Prozentsatz.
	 * Parameter muss zwischen MAX_PREISERHOEHUNG_PROZENT &
	 * MAX_PREISSENKUNG_PROZENT liegen
	 *
	 * @param prozent prozentsatz der Erhoehung
	 */
	void aenderePreis(double prozent);

	/** schreibt einen Artikel mit allen Attributen in einen String
	 *
	 * @return String des Artikels
	 */
	string toString() const;

	static const char* MSG_ARTIKELNR_NICHT_VORHANDEN;
	static const char* MSG_ARTIKELNR_NICHT_VIERSTELLIG;
	static const char* MSG_ARTIKEL_VORHANDEN;
	static const char* MSG_BESTAND_NEGATIV;
	static const char* MSG_BEZEICHNUNG_LEER;
	static const char* MSG_EINGABE_NEGATIV;
	static const char* MSG_EINGABE_KEINE_ZAHL;
	static const char* MSG_PREIS_NEGATIV;
	static const char* MSG_LAGER_LEER;
	static const char* MSG_LAGER_GROESSE_NEGATIV;
	static const char* MSG_MEGE_NEGATIV;
	static const char* MSG_BESTAND_KLEINER_MENGE;
	static const char* MSG_PREIS_AENDERUNG_UNGUELTIG;

private:
	int artikelNr;
	string bezeichnung;
	int bestand;
	double preis;
};

#endif /* ARTIKEL_H_ */
