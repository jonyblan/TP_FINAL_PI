/*
* stationADT.c
* Contenido:
*     Funciones y estructuras que dan soporte a stationADT.
* Autores:
*     Buela Mateo
*     Lanari Augusto
*     Blankleder Jonathan
* Version:
*     1.0.0
* Fecha de creación:
*     02/12/2023
*/

#include "stationADT.h"
#include "bstADT.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <stdio.h>
#define NULL_QU1 {NULL, 0, 0, 0}
#define NULL_QU2 {NULL, NULL, {0,0,0,0,0,0,0,0,0}}
#define WEEKDAY(d,m,y) ((((d) += (m) < 3 ? (y)-- : (y) - 2, 23*(m)/9 + (d) + 4 + (y)/4- (y)/100 + (y)/400)+6)%7)

struct trip {
    time_t nTime; // time_t de hora de inicio
    struct tm sTime; // datos de hora de inicio
    char * endName; // nombre de estacion de fin
};

struct trips {
    // query1:
    unsigned memberTrips; // viajes de usuarios miembros
    unsigned casualTrips; // viajes de usuarios casuales
    // query2:
    char * name; // nombre de estacion de inicio
    struct trip oldest; // viaje mas antiguo
};

struct node {
    struct trips head; // estacion almacenada en nodo
    struct node * alphaTail; // siguiente en forma alfabetica
};

struct countTrips {
    char * name;
    unsigned memberTrips;
    unsigned totalTrips;
};

typedef struct node * tList;

struct stationCDT {
    bstADT bst; // BST para buscar y verificar las id de forma eficiente
    struct countTrips * arr; // array ordenado para query1
    unsigned dim;        //
    tList list; // primer nodo de la lista
    // query3:
    unsigned weekStarts[T_DAYS]; //cambiarlo a struct para guardar entradas y salidas
    unsigned weekEnds[T_DAYS];   //
    // iteradores para q1 y q2;
    unsigned itQ1;
    tList itQ2;
};

stationADT newStaADT(void) {
    stationADT new = calloc(1, sizeof(struct stationCDT));
    if (new == NULL) {
        return NULL;
    }
    for (int i = MON; i < T_DAYS; i++) {
        new->weekStarts[i] = 0;
        new->weekEnds[i] = 0;
    }
    new->bst = newBstADT();
    return new;
}

tList addListRec(tList l, char * name, unsigned len, tList * added) {
    int c;
    if (l == NULL || (c = strcasecmp(l->head.name, name)) > 0) {
        tList newNode = calloc(1, sizeof(*newNode));
        if (newNode == NULL) {
            return NULL;
        }
        newNode->head.name = malloc(len+1);
        if (newNode->head.name == NULL) {
            return NULL;
        }
        strcpy(newNode->head.name, name);
        newNode->alphaTail = l;
        *added = newNode;
        return newNode;
    }
    l->alphaTail = addListRec(l->alphaTail, name, len, added);
    return l;
}

int addStaADT(stationADT sta, char * name, unsigned id) {
    tList added = NULL;
    sta->list = addListRec(sta->list, name, strlen(name), &added);
    if (added == NULL) {
        return ERROR;
    }
    insertBstADT(sta->bst, id, added);
    sta->dim++;
    return OK;
}

void addTripStaADT(stationADT sta, struct tm tStart, unsigned idStart, struct tm tEnd, unsigned idEnd, int isMember) {
	
	tList node = belongsBstADT(sta->bst, idStart);
    if (node == NULL) {
        return;
    }
    time_t t;
    tList endNode = NULL;
    if ((endNode = belongsBstADT(sta->bst, idEnd)) == NULL) {
        return;
    }
    tStart.tm_isdst = -1;
    isMember ? node->head.memberTrips++ : node->head.casualTrips++;

    if ((node->head.oldest.nTime > (t = mktime(&tStart)) || node->head.oldest.nTime == 0) && idStart != idEnd) {
        node->head.oldest.nTime = t;
        node->head.oldest.sTime = tStart;
        node->head.oldest.endName = realloc(node->head.oldest.endName, strlen(endNode->head.name)+1);
        strcpy(node->head.oldest.endName, endNode->head.name);
    }
    int weekdayStart = WEEKDAY(tStart.tm_mday,tStart.tm_mon,tStart.tm_year);
    sta->weekStarts[weekdayStart]++;
    int weekdayEnd = WEEKDAY(tEnd.tm_mday,tEnd.tm_mon,tEnd.tm_year);
    sta->weekEnds[weekdayEnd]++;
}

void freePostReadStaADT(stationADT sta) {
    freeBstADT(sta->bst);
}

static struct countTrips * listToArr(tList l, unsigned dim) {
    struct countTrips * ret = malloc(dim * sizeof(*ret));
    if (ret == NULL) {
        return NULL;
    }
    for (int i = 0; i < dim; i++) {
        ret[i].memberTrips = l->head.memberTrips;
        ret[i].totalTrips = l->head.memberTrips + l->head.casualTrips;
        ret[i].name = l->head.name;
        l = l->alphaTail;
    }
    return ret;
}

static int partitionStationsByViajes(struct countTrips array[] , unsigned low , unsigned high) {
    int pivot = array[high].totalTrips;
	char * pivot2 = array[high].name;
    int i = (low - 1);
    for(int j = low ; j<high ; j++){
        if(array[j].totalTrips > pivot){
            i++;
            struct countTrips temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
		if(array[j].totalTrips == pivot){
			if(strcasecmp(array[j].name, pivot2) < 0){
				i++;
				struct countTrips temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
    }
    struct countTrips temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return (i + 1);

}

static void QuickSortStationsByViajes(struct countTrips *array , int low , int high){
    if (low < high){
        int Pi = partitionStationsByViajes(array , low , high);
        QuickSortStationsByViajes(array , low , Pi -1);
        QuickSortStationsByViajes(array , Pi + 1 , high);
    }
}

int start1StaADT(stationADT sta) {
    sta->arr = listToArr(sta->list, sta->dim);
    if (sta->arr == NULL) {
        return ERROR;
    }
    QuickSortStationsByViajes(sta->arr, 0, sta->dim - 1);
    sta->itQ1 = 0;
    return OK;
}

int hasNext1StaADT(stationADT sta) {
    return sta->itQ1 < sta->dim;
}

struct q1 next1StaADT(stationADT sta) {
    if (!hasNext1StaADT(sta)) {
        query1 ret = NULL_QU1;
        return ret;
    }

    query1 ret;
    ret.bikeStation = sta->arr[sta->itQ1].name;
    ret.memberTrips = sta->arr[sta->itQ1].memberTrips;
    ret.casualTrips = sta->arr[sta->itQ1].totalTrips - sta->arr[sta->itQ1].memberTrips;
    ret.totalTrips = sta->arr[sta->itQ1].totalTrips;

    sta->itQ1++;
    return ret;
}

void start2StaADT(stationADT sta) {
    sta->itQ2 = sta->list;
}

int hasNext2StaADT(stationADT sta) {
    return sta->itQ2 != NULL;
}

query2 next2StaADT(stationADT sta) {
    if (!hasNext2StaADT(sta)) {
        query2 ret = NULL_QU2;
        return ret;
    }
    query2 ret;
    ret.bikeStation = sta->itQ2->head.name;
    ret.bikeEndStation = sta->itQ2->head.oldest.endName;
    ret.oldestDateTime = sta->itQ2->head.oldest.sTime;
    sta->itQ2 = sta->itQ2->alphaTail;
    return ret;
}

query3 query3StaADT(stationADT sta) {
    query3 ret;
    for (int i = 0; i < T_DAYS; i++) {
        ret.arr[i].startedTrips = sta->weekStarts[i];
        ret.arr[i].endedTrips = sta->weekEnds[i];
    }
    return ret;
}

int cantViajes(stationADT sta){
	return (sta->itQ2->head.casualTrips+sta->itQ2->head.memberTrips);
}

static void freeListRec(tList l) {
    if (l == NULL) {
        return;
    }
    free(l->head.oldest.endName);
    free(l->head.name);
    freeListRec(l->alphaTail);
    free(l);
}

void freeEndStaADT(stationADT sta) {
    freeListRec(sta->list);
    free(sta->arr);
    free(sta);
}
