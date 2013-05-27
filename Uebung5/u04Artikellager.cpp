/**
// Name        : u02KlassenMehrfach.cpp
// Author      : Steven Weber
// Version     :
// Description : Einfache Artikelverwaltung m.H. eines Lagers
*/

#include "Lagerdialog.h"



int main(void) {
	Lagerdialog *dialog;
	dialog = new Lagerdialog;
	dialog->hauptmenue();
	delete dialog;
	dialog = 0;
	return 0;
}


