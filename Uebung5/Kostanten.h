/*
 * Kostanten.h
 *
 *  Created on: 20.05.2013
 *      Author: Steven Weber
 */

#ifndef KOSTANTEN_H_
#define KOSTANTEN_H_

/** Fehlerfaelle */
enum Fehler
{
	ArtikelnummerNichtVierstellig,
	ArtikelVorhanden,
	ArtikelNichtVorhanden,
	BezeichnungLeer,
	BestandNegativ,
	PreisNegativ,
	PreisaenderungUngueltig,
	LagerLeer,
	LagergroesseNegativ,
	MengeNegativ
};

enum Menue {
	ArtikelAnlegen = 1,
	ArtikeLoeschen,
	ZugangBuchen,
	AbgangBuchen,
	PreisAendernArtikel,
	PreisAendernLager,
	LagerAnsehen,
	LagerLeeren,
	Ende = 0
};

/** Definiert die maximale Preismanipulation */
const double MAX_PREISERHOEHUNG_PROZENT = 300.0;
const double MAX_PREISSENKUNG_PROZENT = -70;



#endif /* KOSTANTEN_H_ */
