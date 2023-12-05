#ifndef __STATIONADT_H__
#define __STATIONADT_H__

#include <time.h>

typedef struct stationCDT * stationADT;

typedef struct q1 {
    const char * bikeStation;
    unsigned memberTrips;
    unsigned casualTrips;
    unsigned totalTrips;
} query1;

typedef struct q2 {
    const char * bikeStation;
    const char * bikeEndStation;
    struct tm oldestDateTime;
} query2;

typedef struct q3 {
    const unsigned * startedTrips;
    const unsigned * endedTrips;
} query3;

// nuevo ADT para manejar las estaciones
stationADT newStaADT(void);

// agrega una nueva estacion a las estructuras
void addStaADT(stationADT sta, char * name, unsigned id);

void addTripStaADT(stationADT sta, struct tm tStart, unsigned idStart, struct tm tEnd, unsigned idEnd, char isMember);

void start1StaADT(stationADT sta);

int hasNext1StaADT(stationADT sta);

query1 next1StaADT(stationADT sta);

void start2StaADT(stationADT sta);

int hasNext2StaADT(stationADT sta);

query2 next2StaADT(stationADT sta);

query3 query3StaADT(stationADT sta);

#endif
