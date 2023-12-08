#include "stationADT.h"
#include "htmlTable.h"
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
                return ERROR;
            }
        }
        (*s)[w++] = c;
    }
    (*s)[w] = '\0';
    return OK;
}

int readStatFile(FILE * fileStat, stationADT station) {
    char * s = NULL;
    char * token;
    if (getLine(&s, fileStat) == ERROR) {
        return ERROR;
    }
    while (!feof(fileStat)) {
        if ((getLine(&s, fileStat)) != -1 && (token = strtok(s, ";")) != NULL) {
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
                    return ERROR;
                    break;
                }
            }
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
        n = n / 10; 
        ++count; 
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
    query1 * q1;
    fprintf(fQuery1, "bikeStation;memberTrips;casualTrips;allTrips\n");
    while (hasNext1StaADT(sta)) {
        q1 = next1StaADT(sta);
        printQuery1(*q1, fQuery1, hQuery1);
    }
    closeHTMLTable(hQuery1);
    fclose(fQuery1);
    free(q1);
    return OK;
}

void printQuery2(query2 q2, FILE * file, htmlTable html) {
    fprintf(file, "%s;%s;%d/%d/%d %d:%d\n", q2.bikeStation, q2.bikeEndStation, q2.oldestDateTime.tm_mday, q2.oldestDateTime.tm_mon, q2.oldestDateTime.tm_year, q2.oldestDateTime.tm_hour, q2.oldestDateTime.tm_min);
    
    char day[countDigit(q2.oldestDateTime.tm_mday)+1];
    char mon[countDigit(q2.oldestDateTime.tm_mon)+1];
    char year[countDigit(q2.oldestDateTime.tm_year)+1];
    char hour[countDigit(q2.oldestDateTime.tm_hour)+1];
    char min[countDigit(q2.oldestDateTime.tm_min)+1];
    sprintf(day, "%u", q2.oldestDateTime.tm_mday);
    sprintf(mon, "%u", q2.oldestDateTime.tm_mon);
    sprintf(year, "%u", q2.oldestDateTime.tm_year);
    sprintf(hour, "%u", q2.oldestDateTime.tm_hour);
    sprintf(min, "%u", q2.oldestDateTime.tm_min);

    addHTMLRow(html, q2.bikeStation, q2.bikeEndStation, day, mon,year,hour,min);
    
}

int doQuery2(stationADT sta) {
    FILE * fQuery2 = fopen("query2.csv", "wr");
    if(fQuery2 == NULL){
        return ERROR;
    }
    htmlTable hQuery2 = newTable("query2.html", 3, "bikeStation", "bikeEndStation", "oldestDateTime");
    if (hQuery2==NULL){
        return ERROR;
    }
    query2 * q2;
    fprintf(fQuery2, "bikeStation;bikeEndStation;oldestDateTime\n");
    start2StaADT(sta);
    while (hasNext2StaADT(sta)) {
        q2 = next2StaADT(sta);
        printQuery2(*q2, fQuery2, hQuery2);
    }
    closeHTMLTable(hQuery2);
    fclose(fQuery2);
    free(q2);
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
    if (hQuery3==NULL){
        return ERROR;
    }
    fprintf(fQuery3, "weekDay;startedTrips;endedTrips\n");
    char * diasSemana[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for (int i = 0; i < T_DAYS; i++) {
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
    time_t t = time(NULL);
    FILE * fileBike = fopen(argv[1], "r");
    FILE * fileStat = fopen(argv[2], "r");

    if (fileBike == NULL || fileStat == NULL) {
        fprintf(stderr, "Error al abrir archivos\n");
        exit(1);
    }

    stationADT stations = newStaADT();
    if (stations == NULL) {
        fprintf(stderr, "Error al crear TAD\n");
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

    printf("Tiempo: %ld segundos\n", time(NULL)-t);
    return 0;
}

