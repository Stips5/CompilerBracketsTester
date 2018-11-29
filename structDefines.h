//
// Created by stips on 29.11.18..
//

#ifndef COMPILERBRACKETSTESTER_STRUCTDEFINES_H
#define COMPILERBRACKETSTESTER_STRUCTDEFINES_H

typedef struct ELEMENT *Pok;

typedef struct Pozicija
{
    int columnn;
    int line;
}position;

typedef struct ELEMENT *Pok;
typedef struct ELEMENT
{
    char znak;
    position pos;
    int id;     //ako je ne zatvorena otvorena zagrada id = 1 , ako je ima zagrada viska id = 2
    Pok next;
}element;

#endif //COMPILERBRACKETSTESTER_STRUCTDEFINES_H
