/*
 * Lagerdialog.h
 *
 *  Created on: 20.05.2013
 *      Author: Steven Weber
 *
 * Testklasse fuer Lager und Artikel
 */

#ifndef LAGERDIALOG_H_
#define LAGERDIALOG_H_

#include "Artikel.h"
#include "Lager.h"

#include <iostream>
#include <string>

using namespace std;

class Lagerdialog {
public:
	Lagerdialog();

	/**
	 * Gibt das Menue fuer den Benutzer aus
	 */
	void hauptmenue();
	int leseInteger();

private:

	Lager * lager;
};


#endif /* LAGERDIALOG_H_ */
