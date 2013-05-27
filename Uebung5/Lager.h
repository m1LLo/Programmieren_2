/*
 * 	Lager.h
 *
 *  @file Lager.h
 *  @author Steven Weber, Markus Leitz
 *
 *  @param anzahlArtikel	Reale Anzahl an Artikeln
 *  @param lagergroesse 	Maximale Anzahl an Artikeln
 *  @param Artikel ** artikelTab	Array von Artikelobjekten
 *
 * 	Verwaltet mehrere Objekte der Klasse
 * 	Artikel als vereinfachtes Lager
 */

#ifndef LAGER_H_
#define LAGER_H_
#include "Artikel.h"
#include <iostream>

#include "Kostanten.h"


using namespace std;

class Lager {
public:
	/**
	 * Lager anlegen
	 *
	 * @param lagergroesse	Max. Artikelanzahl im Lager
	 */
	Lager(int lagergroesse);
	/** Kopierkonstruktor
	 *
	 * @param Referzenz auf das aktuelle Objekt
	 */
	Lager(const Lager &);

	/**
	 * Explizit zu definierender Zuweisungsoperator
	 *
	 * @param Referenz auf das zugewiesene Objekt
	 * @return Referenz auf das aktuelle Objekt
	 */
	Lager& operator=(const Lager&);

	/** erstellt einen neuen Artikel */
	void legeArtikelAn ();

	/** gibt einen Artikel aus */
	void schreibeArtikel();

	/** loescht einen Artikel */
	void loescheArtikel ();

	/** bucht einen Zugang zum Bestand */
	void bucheMengenZugang ();

	/** bucht einen Abgang vom Bestand */
	void bucheMengenAbgang ();

	/** leert das komplette Lager */
	void loescheAlleArtikel();

	/** aendert den Preis eines Artikels */
	void aendereArtikelpreis();

	/** aendert alle Artikelpreise */
	void aendereAlleArtikelpreise();

	/** sucht einen Artikel im Lager
	 *
	 * @param artikelNr Artikelnummer des Artikels
	 * @return Position des Artikels im Lager
	 */
	int findeArtikel (int artikelNr);

	/** schreibt alle Artikel in einen String
	 *
	 * @return String der gesamtes Lager enthaelt
	 */
	string toString() const;
	/**
	 * Destruktor der Klasse Lager
	 */
	~Lager();

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
	int anzahlArtikel;
	int lagergroesse;
	Artikel ** artikelTab;
};

/* namespace std */
#endif /* LAGER_H_ */

