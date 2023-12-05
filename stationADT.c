#include "stationADT.h"
#include "bstADT.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <stdio.h>

#define T_DAYS 7
enum DIAS {MON = 0, TUE, WED, THU, FRI, SAT, SUN};

struct trip {
    time_t nTime; // valor de hora de inicio
    struct tm sTime; // datos de hora de inicio
    char * eName; // nombre de estacion de fin
};

struct trips {
    // query1:
    unsigned memberTrips; // viajes de usuarios miembros
    unsigned casualTrips; // viajes de usuarios casuales
    // query2:
    char * sName; // nombre de estacion de inicio
    struct trip oldest; // viaje mas antiguo
};

struct node {
    struct trips head; // estacion almacenada en nodo
    struct node * alphaTail; // siguiente en forma alfabetica
    struct node * countTail; // siguiente en cantidad de viajes
};

typedef struct node * tList;

struct stationCDT {
    bstADT bst; // BST para buscar y verificar las id de forma eficiente
    // query3:
    int week[T_DAYS];
    tList alphaFirst;
    tList countFirst;
};

stationADT newStationADT(void) {
    stationADT new = malloc(sizeof(struct stationCDT));
    if (new == NULL) {
        printf("ERROR\n");
        exit(1);
    }
    for (int i = MON; i < T_DAYS; i++) {
        new->week[i] = 0;
    }
    new->alphaFirst = NULL;
    new->countFirst = NULL;
    new->bst = newBst();
    return new;
}

tList addListRec(tList l, char * name, unsigned len, tList * added) {
    int c;
    if (l == NULL || (c = strcasecmp(l->head.sName, name)) > 0) {
        tList newNode = calloc(1, sizeof(*newNode));
        if (newNode == NULL) {
            printf("ERROR\n");
            exit(1);
        }
        newNode->head.sName = malloc(len+1);
        if (newNode->head.sName == NULL) {
            printf("ERROR\n");
            exit(1);
        }
        strcpy(newNode->head.sName, name);
        newNode->alphaTail = l;
        *added = newNode;
        return newNode;
    }
    l->alphaTail = addListRec(l->alphaTail, name, len);
    return l;
}

void addStationADT(stationADT station, char * name) {
    tList added = NULL;
    station->alphaFirst = addListRec(station->alphaFirst, name, strlen(name));
    if (added == NULL) {
        printf("ERROR\n");
        exit(1);
    }
    
}

int main(int argc, char const *argv[]) {
    sizeof(struct stationCDT);
    return 0;
}


/*
    IDEAS:
        -arbol binario para id
        -el bstADT tenerlo adentro del stationADT
        -tenerlo a los dos en un ADT mas grande
*/