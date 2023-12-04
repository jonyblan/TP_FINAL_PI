#ifndef __STATIONADT_H__
#define __STATIONADT_H__

typedef struct stationCDT * stationADT;

// nuevo ADT para manejar las estaciones
stationADT newStationADT(void);

// agrega una nueva estacion a las estructuras
void addStationADT(stationADT station, char * name);

#endif
