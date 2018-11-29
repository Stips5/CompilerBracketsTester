#include <stdio.h>
#include <stdlib.h>
#include "bracketTypes.h"
#include "structDefines.h"
#include "functionDefines.h"

// ERROR_LOADING_FILE -1
// ERROR_ALOCATING_MEMORY -2
// STOG_IS_EMPTY -3

#define STOG_IS_EMPTY               '3'

//define  CHECKFUNCTION CODE

int main() {

    //char imeFilea[] = "primjerKoda";
    char imeFilea[] = "test.txt";
    int status;
    element root;
    root.pos.columnn = root.pos.line = root.id = 0;
    root.next = NULL;
    root.znak = ' ';
    Pok pRez = NULL;
    pRez = &root;

    // testStog(pStog);

    status = ucitavanjeIzDatoteke(imeFilea, pRez);         //ako je ucitano dobro vraca 0

    if (status) {
    printf("\t [FAILED]\n");
    }
    else
    {
        if(pRez->next == NULL)
        {
            printf("\nNo errors found\n");
            return 0;
        }
        else
        {
            printf("\nError(s) found!\n");
            ispisStogaGresaka(pRez);
            printf("\n\n");
            ispisStoga(pRez);
        }
    }
    return 0;
}

int ucitavanjeIzDatoteke(char fileName[], Pok rezultat)
{
    FILE *fp;
    char tmpChar = ' ';
    int status = 0;
    position lineCol;
    lineCol.columnn = lineCol.line = 1;
    Pok stog = alokacija();     //radi kao stog, na ovo se stavljaju i dizu znakovi
    Pok tmp = alokacija();
    tmp->znak = '?';
    int ostaJeZnak = 0;

    printf("Ucitavanje... ");
    fp = fopen(fileName,"r");
    if (fp != NULL) {
        printf("\t  [OK]\n");

        while (!feof(fp)) {
            //kad spremi skine element sa stoga i pribaci ga u rez,
            // trenutni element ne spremi, ovako priskoci ucitavanje novoga dok staroga ne spremi

            if (ostaJeZnak == 0)
            {
                tmpChar = (char) getc(fp);
                status = checker(tmpChar);      //status je znak
                lineCol.columnn++;
            }
            if(status > 3 && status < 7)        //ako je bilo koja otvarajuca zagrada stavi na stog poziciju i znak
            {
                tmp->znak = tmpChar;
                tmp->id = 1;
                tmp->pos = copyPosition(tmp->pos, lineCol);
                stogPush(stog,tmp);
            }
            else if(status == 7)        //ako je otvarajuca (
            {
                if( firstOnStog(stog) == '(')       //ako je prva na stogu istog tipa ali zatvarajuca skini je
                {
                    tmp = copy(tmp, stogPop(stog));     //skini prvoga
                    ostaJeZnak = 0;
                }
                else if(firstOnStog(stog) == STOG_IS_EMPTY)      //ako ima otvarajucu samo
                {
                    tmp->znak = ')';
                    tmp->pos = copyPosition(tmp->pos,lineCol);
                    tmp->id = 2;
                    stogPush(rezultat,tmp);
                }
                else                //ako fali zatvarajuca
                {
                    tmp->id = 1;
                    tmp = copy(tmp, stogPop(stog));  //inace skini i stavi u stog rez
                    stogPush(rezultat,tmp);
                    ostaJeZnak = 1;
                }
            }
            else if(status == 8)
            {
                if( firstOnStog(stog) == '[')
                {
                    tmp = copy(tmp,stogPop(stog));
                    ostaJeZnak = 0;
                }
                else if(firstOnStog(stog) == STOG_IS_EMPTY)      //ako je stog prazan izbaci error
                {
                    printf("Oppening bracket not found %c", tmp->znak);
                    tmp->id = 2;
                    stogPush(rezultat,tmp);
                }
                else
                {
                    tmp->id = 1;
                    tmp = copy(tmp, stogPop(stog));
                    stogPush(rezultat,tmp);
                    ostaJeZnak = 1;
                }
            }
            else if(status == 9)
            {
                if( firstOnStog(stog) == '{')
                {
                    tmp = copy(tmp, stogPop(stog));
                    ostaJeZnak = 0;
                }
                else if(firstOnStog(stog) == STOG_IS_EMPTY)      //ako je stog prazan izbaci error
                {
                    printf("Oppening bracket not found %c", tmp->znak);
                    tmp->id = 2;
                    stogPush(rezultat,tmp);
                }
                else
                {
                    tmp->id = 1;
                    tmp = copy(tmp, stogPop(stog));
                    stogPush(rezultat,tmp);
                    ostaJeZnak = 1;
                }
            }

            else if(status == TAB_FOUND)
            {
                lineCol.columnn+=4;
                ostaJeZnak = 0;
            }

            else if(status == NEW_LINE_FOUND)
            {
                lineCol.line++;
                lineCol.columnn = 1;
                ostaJeZnak = 0;
            }




//
//            if (tmpChar == '\n')
//                lineCol.line++;
        }

        //sve sta je ostalo pribaci na rez
        copyAll(rezultat,stog);
    }
    else
    {
        return -1;      //fail code
    }

    return 0;       //ok
}


Pok alokacija()
{
    Pok el = (Pok)malloc(sizeof(element));
    el->znak = ' ';
    el->pos.columnn = el->pos.line = 0;
    el->next = NULL;
    return el;
}

int checker(char znak)
{
//check function codes
// found_skip 3
// found_( 4
// found_[ 5
// found_{ 6
// found_) 7
// found_] 8
// found_} 9
// found_\n 10
// found_\t 11

    if(znak == '(')
        return OPENING1stCLASS;
    else if(znak == '[')
        return OPENING2rdCLASS;
    else if(znak == '{')
        return OPENING3rdCLASS;
    else if(znak == ')')
        return CLOSING1stCLASS;
    else if(znak == ']')
        return CLOSING2ndCLASS;
    else if(znak == '}')
        return CLOSING3rdCLASS;
    else if(znak == '\n')
        return NEW_LINE_FOUND;
    else if(znak == '\t')
        return TAB_FOUND;
    else
        return 3;
}

void testStog(Pok root)
{
    short unos = 0;
    char znakovi[5] = {'e','f','u','z','r',};
    int i = 0;
    Pok skinuto = NULL;

    do {
        printf("Odaberi: \n 1) pop \n 2) push\n");
        scanf("%hd", &unos);

        switch (unos) {
            case 0:
                return;
            case 1:{
                skinuto = stogPop(root);
                printf("\nskinut %c\n\n",skinuto->znak);
                i--;
                break;
            }
            case 2:
            {
                stogPush(root,znakovi[i]);
                i++;
                break;
            }
            default:
                break;
        }
        ispisStoga(root);

    }while(unos != 0);
}

int stogPush(Pok root, Pok znak)
{
    Pok iduci = alokacija();

    iduci->next = root->next;

    root->next = iduci;

    copy(iduci,znak);

    return 0;
}

Pok stogPop(Pok root)
{
    Pok iduci = root->next;
    Pok skinuti = alokacija();
    if(iduci == NULL)
        return NULL;
    else
    {
        copy(skinuti,iduci);
        root->next = iduci->next;
        free(iduci);
    }
    return skinuti;
}

int ispisStoga(Pok root)
{
    Pok current = root->next;

    if(current == NULL) {
        printf("\t +---------+\n");
        printf("stog prazan\n");
        return -3;
    }
    else {
        printf("\nIspis stanja stoga: \n");
        while (current != NULL)
        {
            printf("\t +---------+\n");
            printf("\t |    %c    |\t \t line %d column %d\n",current->znak,current->pos.line,current->pos.columnn);
            printf("\t +---------+\n");
            current = current->next;
        }
    }
    printf("\n");
    return 0;
}

Pok copy(Pok destination, Pok source)
{
    destination->znak = source->znak;
    destination->id = source->id;
    destination->pos = copyPosition(destination->pos, source->pos);

    return destination;
}

position copyPosition(position destination, position source)
{
    destination.columnn = source.columnn;
    destination.line = source.line;

    return destination;
}

char firstOnStog(Pok root) {

    if (root->next == NULL) {
        return '3';
    }
    else
    {
        return root->next->znak;
    }
}

void ispisStogaGresaka(Pok item)
{
    Pok current = item->next;

    if(current == NULL) {
        printf("stog gresaka prazan\n");
    }
    else {

        while (current != NULL) {
            if (current->id == 1)
            {
            printf("\n \toppening bracket %c is not closed\n\tline:%d, columnn:%d \n",
                   current->znak,
                   current->pos.line,
                   current->pos.columnn);
            }
            else if(current->id == 2)
            {
                printf("\n \tno opening brackets found for %c \n\tline:%d, columnn:%d \n",
                       current->znak,
                       current->pos.line,
                       current->pos.columnn);
            }
            current = current->next;
        }
    }
    printf("\n");
}

void copyAll(Pok destination, Pok source)
{
    Pok currentS = source->next;

    if(currentS == NULL)
    {
        return;
    }
    else
    {
        while(currentS != NULL)
        {
            stogPush(destination,currentS);
            currentS = currentS->next;
        }
    }
}