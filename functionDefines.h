//
// Created by stips on 29.11.18..
//

#include "structDefines.h"

#ifndef COMPILERBRACKETSTESTER_STOGDEFINES_H
#define COMPILERBRACKETSTESTER_STOGDEFINES_H


int ucitavanjeIzDatoteke(char[], Pok);
int checker(char znak);
void testStog(Pok root);
Pok alokacija();
int ispisStoga(Pok);

Pok copy(Pok , Pok);
int stogPush(Pok, Pok );
Pok stogPop(Pok);
position copyPosition(position, position);
char firstOnStog(Pok);
void ispisStogaGresaka(Pok);

void copyAll(Pok, Pok);

#endif //COMPILERBRACKETSTESTER_STOGDEFINES_H
