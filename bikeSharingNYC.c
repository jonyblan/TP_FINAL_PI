/*
* bikeSharingNYC.c
* Contenido: 
*     Lectura y procesado de archivos de alquileres y estaciones de
*     la ciudad de Nueva York, Estados Unidos. Donde se ejecutan los
*     pedidos o "querys" solicitados en el TPE.
* Autores:
*     Buela Mateo
*     Lanari Augusto
*     Blankleder Jonathan
* Version:
*     1.0.0
* Fecha de creación:
*     03/12/2023
*/

#include "stationADT.h"
#include "htmlTable.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOQUE 50
#define CANT_CARACTERS_Q2 17
enum columnas {CANTCOL_STATIONS = 4, COLQ1 = 4, COLQ2 = 3, COLQ3 = 3};

/*
*  Lee linea de archivo.
*    @param s es puntero char * de salida donde se almacena la lina leida
*    @param FILE archivo a leer
*    @returns OK si se leyo correctamente, ERROR si falla
*/
int getLine(char ** s, FILE * file);

/*
*  Lee y almacena datos de archivo de estaciones
*    @param station, station ADT donde guarda los datos
*    @param fileStat archivo de estaciones  a leer
*    @returns OK si se leyo correctamente, ERROR si falla
*/
int readStatFile(FILE * fileStat, stationADT station);

/*
*  Lee y almacena datos de archivo de alquileres
*    @param stations, station ADT donde guarda los datos
*    @param fileBike archivo de estaciones  a leer
*    @returns OK si se leyo correctamente, ERROR si falla
*/
int readBikeFile(FILE * fileBike, stationADT stations);

/*
*  Cuenta la cantidad de digitos de un numero entero unsigned.
*    @param unsigned int a contar digitos
*    @returns la cantidad de digitos
*/
int countDigit(unsigned n);

/*
*  Imprime fila de datos de la query1 tanto en el archivo csv, como html
*    @param q1 struct q1 donde obtener los datos a imprimir
*    @param file arcivo .csv a escribir
*    @returns html archivo .html a escribir
*/
void printQuery1(query1 q1, FILE * file, htmlTable html);

/*
*   Obtiene los datos para la query1 de station ADT para crear y escribir los archivos de salida
*    @param stationADT a obtener datos
*    @returns OK si se leyo y escribio correctamente, ERROR si falla
*/
int doQuery1(stationADT sta);


/*
*  Imprime fila de datos de la query2 tanto en el archivo csv, como html
*    @param q2 struct q1 donde obtener los datos a imprimir
*    @param file arcivo .csv a escribir
*    @returns html archivo .html a escribir
*/
void printQuery2(query2 q2, FILE * file, htmlTable html);

/*
*   Obtiene los datos para la query2 de station ADT para crear y escribir los archivos de salida
*    @param stationADT a obtener datos
*    @returns OK si se leyo y escribio correctamente, ERROR si falla
*/
int doQuery2(stationADT sta);

/*
*  Imprime fila de datos de la query3 tanto en el archivo csv, como html
*    @param q3 struct q1 donde obtener los datos a imprimir
*    @param file arcivo .csv a escribir
*    @returns html archivo .html a escribir
*/
void printQuery3(query3 q3, FILE * file, htmlTable html, int i, char * dia);

/*
*   Obtiene los datos para la query3 de station ADT para crear y escribir los archivos de salida
*    @param stationADT a obtener datos 
*    @returns OK si se leyo y escribio correctamente, ERROR si falla
*/
int doQuery3(stationADT sta);

int getLine(char ** s, FILE * file) {
    size_t w = 0;
    char c;
    while ((c = fgetc(file)) != EOF && c != '\n') {
        if (w%BLOQUE == 0) {
            *s = realloc(*s, (w + BLOQUE + 1));
            if (*s == NULL) {
                return ERROR;
            }
        }
        (*s)[w++] = c;
    }
    (*s)[w] = '\0';
    return OK;
}

int readStatFile(FILE * fileBike, stationADT station) {
char * s = NULL;
    char * token;
    if (getLine(&s, fileBike) == ERROR) {
        return ERROR;
    }
    while (!feof(fileBike)) {
        if ((getLine(&s, fileBike)) != ERROR && (token = strtok(s, ";")) != NULL) {
            unsigned id;
            char * aux;
            for (int i = 0; token != NULL && i < CANTCOL_STATIONS; token = strtok(NULL, ";"), i++) {
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
                    break;
                    return ERROR;
                }
            }
            addStaADT(station, aux, id);
        }
    }
    free(s);
    return OK;
}

int readBikeFile(FILE * fileBike, stationADT stations) {
    char * s = NULL;
    char * token;
    if (getLine(&s, fileBike) == ERROR) {
        return ERROR;
    }
    while (!feof(fileBike)) {
        if ((getLine(&s, fileBike)) != ERROR && (token = strtok(s, ";")) != NULL) {
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
                    isMember = *token == 'm';
                    break;
                default:
                    return ERROR;
                    break;
                }
            }
            addTripStaADT(stations, dateStart, idStart, dateEnd, idEnd, isMember);
        }
    }
    free(s);
    return OK;
}

int countDigit(unsigned n)  {
    if (n == 0)
        return 1;
    int count = 0;
    while (n != 0) {
        n /= 10;
        count++;
    }
    return count;
}


void printQuery1(struct q1 q1, FILE * file, htmlTable html) {
    fprintf(file, "%s;%u;%u;%u\n", q1.bikeStation, q1.memberTrips, q1.casualTrips, q1.totalTrips);

    char memberTrips[countDigit(q1.memberTrips)+1];
    char casualTrips[countDigit(q1.casualTrips)+1];
    char totalTrips[countDigit(q1.totalTrips)+1];
    sprintf(memberTrips, "%u", q1.memberTrips);
    sprintf(casualTrips, "%u", q1.casualTrips);
    sprintf(totalTrips, "%u", q1.totalTrips);

    addHTMLRow(html, q1.bikeStation, memberTrips, casualTrips, totalTrips);
}

int doQuery1(stationADT sta) {
    FILE * fQuery1 = fopen("query1.csv", "wr");
    if(fQuery1 == NULL){
        return ERROR;
    }
    htmlTable hQuery1 = newTable("query1.html", 4, "bikeStation", "memberTrips", "casualTrips", "allTrips");
    query1 q1;
    fprintf(fQuery1, "bikeStation;memberTrips;casualTrips;allTrips\n");
    while (hasNext1StaADT(sta)) {
        q1 = next1StaADT(sta);
        printQuery1(q1, fQuery1, hQuery1);
    }
    closeHTMLTable(hQuery1);
    fclose(fQuery1);
    
    return OK;
}
void printQuery2(query2 q2, FILE * file, htmlTable html) {
    fprintf(file, "%s;%s;%02d/%02d/%4d %02d:%02d;\n", q2.bikeStation, q2.bikeEndStation, q2.oldestDateTime.tm_mday, q2.oldestDateTime.tm_mon, q2.oldestDateTime.tm_year, q2.oldestDateTime.tm_hour, q2.oldestDateTime.tm_min);
    
    char fecha[CANT_CARACTERS_Q2];
    sprintf(fecha, "%02u/%02u/%4u %02u:%02u", q2.oldestDateTime.tm_mday, q2.oldestDateTime.tm_mon, q2.oldestDateTime.tm_year, q2.oldestDateTime.tm_hour, q2.oldestDateTime.tm_min);

    addHTMLRow(html, q2.bikeStation, q2.bikeEndStation, fecha);
}

int doQuery2(stationADT sta) {
    FILE * fQuery2 = fopen("query2.csv", "wr");
    if(fQuery2 == NULL){
        return ERROR;
    }
    htmlTable hQuery2 = newTable("query2.html", 3, "bikeStation", "bikeEndStation", "oldestDateTime");
    if (hQuery2 == NULL){
        return ERROR;
    }
    query2 q2;
    fprintf(fQuery2, "bikeStation;bikeEndStation;oldestDateTime\n");
    start2StaADT(sta);
    while (hasNext2StaADT(sta)) {
        q2 = next2StaADT(sta);
		if(q2.bikeEndStation != NULL) {
		    printQuery2(q2, fQuery2, hQuery2);
		}
    }
    
    closeHTMLTable(hQuery2);
    fclose(fQuery2);
    
    return OK;
}
void printQuery3(query3 q3, FILE * file, htmlTable html, int i, char * dia) {
    fprintf(file, "%s;%u;%u\n", dia, q3.arr[i].startedTrips, q3.arr[i].endedTrips);
    
    char started[countDigit(q3.arr[i].startedTrips)+1];
    char ended[countDigit(q3.arr[i].endedTrips)+1];
    sprintf(started, "%u", q3.arr[i].startedTrips);
    sprintf(ended, "%u", q3.arr[i].endedTrips);

    addHTMLRow(html, dia, started, ended);
}

int doQuery3(stationADT sta) {
    FILE * fQuery3 = fopen("query3.csv", "wr");
    if (fQuery3 == NULL) {
        return ERROR;
    }
    query3 q3 = query3StaADT(sta);
    htmlTable hQuery3 = newTable("query3.html", 3, "weekDay", "startedTrips", "endedTrips");
    if (hQuery3 == NULL){
        return ERROR;
    }
    fprintf(fQuery3, "weekDay;startedTrips;endedTrips\n");
    char * diasSemana[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for (int i = MON; i < T_DAYS; i++) {
        printQuery3(q3, fQuery3, hQuery3, i, diasSemana[i]);
    }
    closeHTMLTable(hQuery3);
    fclose(fQuery3);
    return OK;
}

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Error: cantidad de parámetros erronea\n");
        exit(1);
    }
    
    FILE * fileBike = fopen(argv[1], "r");
    FILE * fileStat = fopen(argv[2], "r");

    if (fileBike == NULL || fileStat == NULL) {
        fprintf(stderr, "Error al abrir archivos\n");
        exit(1);
    }

    stationADT stations = newStaADT();
    if (stations == NULL) {
        fprintf(stderr, "Error al crear TAD\n");
        exit(1);
    }
    
    if (readStatFile(fileStat, stations) == ERROR) {
        fprintf(stderr, "Error al leer archivo de estaciones\n");
        exit(1);
    }
    
    if (readBikeFile(fileBike, stations) == ERROR) {
        fprintf(stderr, "Error al leer archivo de viajes\n");
        exit(1);
    }

    freePostReadStaADT(stations);

    if (start1StaADT(stations) == ERROR) {
        fprintf(stderr, "Error al iniciar proceso de query1\n");
        exit(1);
    }

    if (doQuery1(stations) == ERROR) {
        fprintf(stderr, "Error al procesar query1\n");
        exit(1);
    }

    if (doQuery2(stations) == ERROR) {
        fprintf(stderr, "Error al procesar query2\n");
        exit(1);
    }

    if (doQuery3(stations) == ERROR) {
        fprintf(stderr, "Error al procesar query3\n");
        exit(1);
    }

    freeEndStaADT(stations);
    
    return 0;
}
