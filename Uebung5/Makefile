CFLAGS =  -O -Wall -g
CC=g++
LD=g++
LDFLAGS= 
OBJ= Artikel.o Lager.o Lagerdialog.o u04Artikellager.o
DELOBJ= *.o
all: u04Artikellager

#Definition abhaengigkeiten
u04Artikellager: $(OBJ)
Artikel.o: Artikel.cpp Artikel.h  Kostanten.h
Lager.o: Lager.cpp Lager.h  Kostanten.h
Lagerdialog.o: Lagerdialog.cpp Lagerdialog.h  	

#loescht alte Objekte bevor neue erstellt werden
clean:
	@echo "Folgende Daten werden gel�scht"
	@echo $(DELOBJ)
	rm  $(DELOBJ)
	
	#Erzeuge aus ccp eine .o Datei
	%.o: %.cpp
		$(CC) $(CFLAGS) -c $<
		
	#Erzeuge aus o.Datei eine .exe
	%: %.o
		$(LD) $(LDFLAGS) -o $@ $^
	
	#Erzeuge aus .ccp datei eine .exe
	%: %.cpp
		$(CC) $(CFLAGS) -o $@ $^