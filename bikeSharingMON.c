#include "stationADT.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CANTCOL 2
#define BLOQUE 30

int getLine(char ** s, FILE * file) {
    size_t w = 0;
    char c;

    while ((c = fgetc(file)) != EOF && c != '\n') {
        if (w%BLOQUE == 0) {
            *s = realloc(*s, (w + BLOQUE + 1));
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
            for (int i = 0; token != NULL && i < CANTCOL; token = strtok(NULL, ";"), i++) {
                switch (i) {
                case 0:
                    sscanf(token, "%d", &id);
                    break;
                case 1:
                    addStaADT(station, token, id);
                    break;
                default:
                    fprintf(stderr, "Error en switch de lectura de stations\n");
                    exit(1);
                    break;
                }
            }
        }
    }
}

void readBikeFile(FILE * fileBike, stationADT stations) {
    char * s = NULL;
    char * token;
    if (getLine(&s, fileBike) == -1) {
        fprintf(stderr, "Error al leer archivo\n");
        exit(1);
    }
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
                    sscanf(token, "%d", &idStart);
                    break;
                case 2:
                    sscanf(token, "%d-%d-%d %d:%d:%d", &(dateEnd.tm_year), &(dateEnd.tm_mon), &(dateEnd.tm_mday), &(dateEnd.tm_hour), &(dateEnd.tm_min), &(dateEnd.tm_sec));
                    break;
                case 3:
                    sscanf(token, "%d", &idEnd);
                    break;
                case 4:
                    sscanf(token, "%d", &isMember);
                    break;
                default:
                    fprintf(stderr, "Error en switch de lectura de stations\n");
                    exit(1);
                    break;
                }
            }
            addTripStaADT(stations, dateStart, idStart, dateEnd, idEnd, isMember);
        }
    }
}

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Cantidad de parámetros erronea\n");
        exit(1);
    }
    if (strcmp(argv[1], "bikesMON.csv") != 0 || strcmp(argv[2], "stationsMON.csv") != 0) {
        fprintf(stderr, "Archivos pasados incorrectos\n");
        exit(1);
    }
    time_t t = time(NULL);
    FILE * fileBike = fopen(argv[1], "r");
    FILE * fileStat = fopen(argv[2], "r");

    stationADT stations = newStaADT();
    
    readStatFile(fileStat, stations);
    
    readBikeFile(fileBike, stations);

    freePostReadStaADT(stations);

    query3 q3 = query3StaADT(stations);

    printf("Query3:\n");
    for (int i = 0; i < T_DAYS; i++) {
        printf("%d: %d\t; %d\t\n", i, q3.arr[i].startedTrips, q3.arr[i].endedTrips);
    }

    printf("Tiempo: %ld segundos\n", time(NULL)-t);
    return 0;
}

