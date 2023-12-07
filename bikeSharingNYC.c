#include "stationADT.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CANTCOL 4
#define BLOQUE 100

int getLine(char ** s, FILE * file) {
    size_t w = 0;
    char c;

    while ((c = fgetc(file)) != EOF && c != '\n') {
        if (w%BLOQUE == 0) {
            (*s) = realloc((*s), (w + BLOQUE + 1));
            if (*s == NULL) {
                return -1;
            }
        }
        (*s)[w++] = c;
    }

    (*s)[w] = '\0';
    return 1;
}

void readStatFile(FILE * fileBike, stationADT station) {
char * s = NULL;
    char * token;
    if (getLine(&s, fileBike) == -1) {
        fprintf(stderr, "Error al leer archivo\n");
        exit(1);
    }
    while (!feof(fileBike)) {
        if ((getLine(&s, fileBike)) != -1 && (token = strtok(s, ";")) != NULL) {
            unsigned id;
            char *aux;
            for (int i = 0; token != NULL && i < CANTCOL; token = strtok(NULL, ";"), i++) {
                switch (i) {
                case 0:
                    aux=token;
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    sscanf(token, "%u", &id);
                    break;
                default:
                    fprintf(stderr, "Error en switch de lectura de stations\n");
                    exit(1);
                    break;
                }
            }
            addStaADT(station, aux, id);
        }
    }
    free(s);
}

void readBikeFile(FILE * fileBike, stationADT stations) {
    char * s = NULL;
    char * token;
    if (getLine(&s, fileBike) == -1) {
        fprintf(stderr, "Error al leer archivo\n");
        exit(1);
    }
    int a =0;
    while (!feof(fileBike)) {

        if ((getLine(&s, fileBike)) != -1 && (token = strtok(s, ";")) != NULL) {
            unsigned idStart, idEnd, isMember;
            struct tm dateStart, dateEnd;
            for (int i = 0; token != NULL; token = strtok(NULL, ";"), i++) {
                switch (i) {
                case 0:
                    sscanf(token, "%d-%d-%d %d:%d:%d", &(dateStart.tm_year), &(dateStart.tm_mon), &(dateStart.tm_mday), &(dateStart.tm_hour), &(dateStart.tm_min), &(dateStart.tm_sec));
                    break;
                case 1:
                    sscanf(token, "%u", &idStart);
                    break;
                case 2:
                    sscanf(token, "%d-%d-%d %d:%d:%d", &(dateEnd.tm_year), &(dateEnd.tm_mon), &(dateEnd.tm_mday), &(dateEnd.tm_hour), &(dateEnd.tm_min), &(dateEnd.tm_sec));
                    break;
                case 3:
                    sscanf(token, "%u", &idEnd);
                    break;
                case 4:
                    break;
                case 5:
                    if(*token =='c'){
                        isMember=0; 
                    }
                    else
                        isMember=1;
                    break;
                default:
                    fprintf(stderr, "Error en switch de lectura de stations\n");
                    exit(1);
                    break;
                }
            }
            addTripStaADT(stations, dateStart, idStart, dateEnd, idEnd, isMember);
            printf ("%d\n",a++);
        }
    }
    free(s);
}

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Cantidad de parámetros erronea\n");
        exit(1);
    }
    if (strcmp(argv[1], "bikesNYC.csv") != 0 || strcmp(argv[2], "stationsNYC.csv") != 0) {
        fprintf(stderr, "Archivos pasados incorrectos\n");
        exit(1);
    }
    time_t t = time(NULL);
    FILE * fileBike = fopen(argv[1], "r");
    FILE * fileStat = fopen(argv[2], "r");

    stationADT stations = newStaADT();
    
    readStatFile(fileStat, stations);
    readBikeFile(fileBike, stations);
    char *que2="query2.csv";

    FILE *pQuery2=fopen(que2, "w");
    if(pQuery2==NULL){
        printf("Problema creando %s. Aborto.\n", que2);
        exit(1);
    }
    char * q2camp1="bikeStation";
    char * q2camp2="bikeEndStation";
    char * q2camp3="oldestDateTime";
    fprintf(pQuery2, "%s;%s;%s\n",q2camp1,q2camp2,q2camp3);
    start2StaADT(stations);
    while(hasNext2StaADT(stations)){
        query2 q2=next2StaADT(stations);
        fprintf(pQuery2, "%s;%s;%d/%d/%d %d:%d \n", q2.bikeStation, q2.bikeEndStation, q2.oldestDateTime.tm_year,q2.oldestDateTime.tm_mon,q2.oldestDateTime.tm_mday,q2.oldestDateTime.tm_hour,q2.oldestDateTime.tm_min );
    }
    freePostReadStaADT(stations);
    freeEndStaADT(stations);
        printf("Tiempo: %ld segundos\n", time(NULL)-t);

    
    return 0;
}