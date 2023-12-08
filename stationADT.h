#ifndef __STATIONADT_H__
#define __STATIONADT_H__

#include <time.h>

#define T_DAYS 7
#define ERROR -1
#define OK 0

enum DIAS {MON = 0, TUE, WED, THU, FRI, SAT, SUN};

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

struct q3_arr {
    unsigned startedTrips;
    unsigned endedTrips;
};

typedef struct q3 {
    struct q3_arr arr[T_DAYS];
} query3;

// nuevo ADT para manejar las estaciones
stationADT newStaADT(void);

// agrega una nueva estacion a las estructuras
int addStaADT(stationADT sta, char * name, unsigned id);

// agrega un viaje ya con toda la informacion necesaria a las estructuras
void addTripStaADT(stationADT sta, struct tm tStart, unsigned idStart, struct tm tEnd, unsigned idEnd, int isMember);

// una vez leida y almacenada toda la informacion, libera los recursos utilizados para leer
void freePostReadStaADT(stationADT sta);

// prepara las estructuras para poder realizar la query1 e inicia el iterador para la query1
int start1StaADT(stationADT sta);

// verifica que haya proximo para la query1
int hasNext1StaADT(stationADT sta);

// devuelve el siguiente y aumenta el iterador de la query1
query1 next1StaADT(stationADT sta);

// inicia el iterador para la query2
void start2StaADT(stationADT sta);

// verifica que haya proximo para la query1
int hasNext2StaADT(stationADT sta);

// devuelve el siguiente y aumenta el iterador de la query1
query2 next2StaADT(stationADT sta);

// devuelve la informacion necesaria para la query3
query3 query3StaADT(stationADT sta);

// libera todos los recursos utilizados por el ADT
void freeEndStaADT(stationADT sta);

void a(stationADT sta);

#endif
