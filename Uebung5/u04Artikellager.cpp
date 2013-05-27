//============================================================================
// Name        : u02KlassenMehrfach.cpp
// Author      : Steven Weber
// Version     :
// Description : Einfache Artikelverwaltung m.H. eines Lagers
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include "Lagerdialog.h"



int main(void) {
	Lagerdialog *dialog;
	dialog = new Lagerdialog;
	dialog->hauptmenue();
	return 0;
}


