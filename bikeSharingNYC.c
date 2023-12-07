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
            s = realloc(s, (w + BLOQUE + 1));
            if (s == NULL) {
                return -1;
            }
        }
        (s)[w++] = c;
    }

    (*s)[w] = '\0';
    return 1;
}

static void printTime(struct tm t) {
    printf("%d-%2d-%2d %2d:%2d:%2d", t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
}

void readStatFile(FILE * fileBike, stationADT station) {
char * s = NULL;
    char * token;
    size_t len;
    int a = 0;
    if (getLine(&s, &len, fileBike) == -1) {
        fprintf(stderr, "Error al leer archivo\n");
        exit(1);
    }
    free(s);
    s = NULL;
    while (!feof(fileBike)) {
        if ((getLine(&s, &len, fileBike)) != -1 && (token = strtok(s, ";")) != NULL) {
            unsigned id;
            char *aux;
            for (int i = 0; token != NULL && i < CANTCOL; token = strtok(NULL, ";"), i++) {
                switch (i) {
                case 0:
                    aux=token;
                    break;
                case 3:
                    sscanf(token, "%d", &id);
                    break;
                default:
                    fprintf(stderr, "Error en switch de lectura de stations\n");
                    exit(1);
                    break;
                }
            }
            addStaADT(station, aux, id);
        }
        free(s);
        s = NULL;
    }
}

void readBikeFile(FILE * fileBike, stationADT stations) {
    char * s = NULL;
    char * token;
    size_t len;
    int a = 0;
    if (getLine(&s, &len, fileBike) == -1) {
        fprintf(stderr, "Error al leer archivo\n");
        exit(1);
    }
    free(s);
    s = NULL;
    while (!feof(fileBike)) {
        if ((getLine(&s, &len, fileBike)) != -1 && (token = strtok(s, ";")) != NULL) {
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
        }
        free(s);
        s = NULL;
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

    printf("Tiempo: %ld segundos\n", time(NULL)-t);
    return 0;
}