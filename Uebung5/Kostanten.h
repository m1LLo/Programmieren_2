/*
 * Kostanten.h
 *
 *  Created on: 20.05.2013
 *      Author: Steven Weber
 */

#ifndef KOSTANTEN_H_
#define KOSTANTEN_H_

/** Fehlerfaelle */
enum Fehler {ArtikelnummerNichtVierstellig, ArtikelVorhanden,
	ArtikelNichtVorhanden, BezeichnungLeer, BestandNegativ,
	PreisNegativ, PreisaenderungUngueltig, LagerLeer, LagergroesseNegativ, MengeNegativ};

static const int ArtikelAnlegen = 1;
static const int ArtikeLoeschen = 2;
static const int ZugangBuchen = 3;
static const int AbgangBuchen = 4;
static const int PreisAendernArtikel = 5;
static const int PreisAendernLager = 6;
static const int LagerAnsehen = 7;
static const int LagerLeeren = 8;
static const int Ende = 0;

/** Definiert die maximale Preismanipulation */
const double MAX_PREISERHOEHUNG_PROZENT = 300.0;
const double MAX_PREISSENKUNG_PROZENT = -70;

/** Fehlermeldungen */
static const char* meldung_ArtikelNrNichtVorhanden = "Artikel ist nicht vorhanden";
static const char* meldung_ArtikelNrNichtVierstellig = "Artikelnummer muss vierstellig, positiv sein!";
static const char* meldung_ArtikelVorhanden = "Diese Artikelnummer ist bereits vergeben!";
static const char* meldung_BestandNegativ = "Bestand muss positiv sein!";
static const char* meldung_BezeichnungLeer = "Bezeichnung darf nicht leer sein!";
static const char* meldung_EingabeNegativ = "Bitte eine positive Zahl eingeben!";
static const char* meldung_EingabeKeineZahl = "Das war keine Zahl!";
static const char* meldung_PreisNegativ = "Preis muss positiv sein!";
static const char* meldung_LagerLeer = "Das Lager ist leer!";
static const char* meldung_LagergroesseNegativ = "Das Lager muss eine positive Kapazitaet ausweisen";
static const char* meldung_MegeNegativ = "Es duerfen keine negativen Mengen gebucht werden!";
static const char* meldung_BestandKleinerMenge = "So viele Artikel sind nicht mehr vorhanden!";
static const char* meldung_PreisaenderungUngueltig = "Bitte Preis innerhalb einer Grenze von -70% - 300% aendern!";


#endif /* KOSTANTEN_H_ */
