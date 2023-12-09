/*
* stationADT.h
* Contenido:
*     Prototipos de funciones para el usuario de stationADT.
*     stationADT:
*         stationADT es una libreria para almacenar y procesar
*         datos de alquileres y estaciones de bicicletas.
* Autores:
*     Buela Mateo
*     Lanari Augusto
*     Blankleder Jonathan
* Version:
*     1.0.0
* Fecha de creación:
*     02/12/2023
*/

#ifndef __STATIONADT_H__
#define __STATIONADT_H__

#include <time.h>

#define T_DAYS 7
enum status {OK = 0, ERROR = -1};

enum dias {MON = 0, TUE, WED, THU, FRI, SAT, SUN};

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

/*
* Nuevo ADT para manejar las estaciones
* @returns puntero al nuevo ADT
*/
stationADT newStaADT(void);

/*
* Agrega una nueva estacion a las estructuras
* @returns OK si se logró agregar la información; ERROR si falla
* @param sta ADT donde agregar la información
* @param name nombre de la estación
* @param id id de la estación
*/
int addStaADT(stationADT sta, char * name, unsigned id);

/*
* Agrega un alquiler ya con toda la informacion necesaria a las estructuras
* @param sta ADT donde agregar la información
* @param tStart datos del tiempo de inicio del alquiler
* @param idStart id de estación de incio del alquiler
* @param tEnd datos del tiempo de fin del alquier
* @param idEnd id de estación de fin del alquiler
# @param isMember 1 si es miembro; 0 si no
*/
void addTripStaADT(stationADT sta, struct tm tStart, unsigned idStart, struct tm tEnd, unsigned idEnd, int isMember);

/*
* Una vez leida y almacenada toda la informacion, libera los recursos utilizados para leer
* @param sta ADT a liberar información
*/
void freePostReadStaADT(stationADT sta);

/*
* Prepara las estructuras para poder realizar la query1 e inicia el iterador para la query1
* @returns OK si se preparó todo correctamente; ERROR si falla
*/
int start1StaADT(stationADT sta);

/*
* Verifica que haya proximo para la query1
* @returns 1 si hay siguiente; 0 si no
*/
int hasNext1StaADT(stationADT sta);

/*
* Devuelve el siguiente y aumenta el iterador de la query1
* @returns datos para query1 donde está el iterador
*/
query1 next1StaADT(stationADT sta);

/*
* Inicia el iterador para la query2
*/
void start2StaADT(stationADT sta);

/*
* Verifica que haya proximo para la query1
* @returns 1 si hay siguiente; 0 si no
*/
int hasNext2StaADT(stationADT sta);

/*
* Devuelve el siguiente y aumenta el iterador de la query1
* @returns datos para query2 donde está el iterador
*/
query2 next2StaADT(stationADT sta);

/*
* Devuelve la informacion necesaria para la query3
* @returns datos para query3
*/
query3 query3StaADT(stationADT sta);

/*
* Libera todos los recursos utilizados por el ADT
*/
void freeEndStaADT(stationADT sta);

#endif
