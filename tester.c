#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define BLOQUE 50
#define CANT_DIAS_SEMANA 7

// Max int: 2147483647
#define linesStations 2147483647
#define linesBikes 2147483647

#define tipoDatoBikes int
#define tipoDatoStations int
#define datoBikes idEnd
#define datoStation id

struct stacion {
    char * nombre;
    float lat;
    float lon;
    int id;
	int cantViajesIniciadosCasuales;
	int cantViajesIniciadosMiembros;
	time_t timeEarliestTrip;
	char * nameEarliestTrip;
	int idEarliestTrip;
};

struct bikes {
    time_t timeStart;
    time_t timeEnd;
    int idStart;
    int idEnd;
    char member;
};

void readTitle(FILE * file) {
    char c;
    while ((c = fgetc(file)) != '\n' && c != EOF) {
        ;
    }
}

void readLine(FILE * file,  char * s) {
    char c;
    while ((c = fgetc(file)) != '\n' && c != EOF) {
        *(s++) = c;
    }
    *s = 0;
}

// partition y quickSort son un combo
int partitionStationsByViajes(struct stacion array[] , int low , int high){
    tipoDatoStations pivot = (array[high].cantViajesIniciadosCasuales + array[high].cantViajesIniciadosMiembros);
	char * pivot2 = array[high].nombre;
    int i = (low - 1);
    for(int j = low ; j<high ; j++){
        if((array[j].cantViajesIniciadosCasuales + array[j].cantViajesIniciadosMiembros) < pivot){
            i++;
            struct stacion temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
		if((array[j].cantViajesIniciadosCasuales + array[j].cantViajesIniciadosMiembros) == pivot){
			if(strcasecmp(array[j].nombre, pivot2) < 0){
				i++;
				struct stacion temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
    }
    struct stacion temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return (i + 1);
}

void QuickSortStationsByViajes(struct stacion *array , int low , int high){
    if (low < high){
        int Pi = partitionStationsByViajes(array , low , high);
        QuickSortStationsByViajes(array , low , Pi -1);
        QuickSortStationsByViajes(array , Pi + 1 , high);
    }
}

// partition y quickSort son un combo
int partitionStationsByName(struct stacion array[] , int low , int high){
	char * pivot2 = array[high].nombre;
    int i = (low - 1);
    for(int j = low ; j<high ; j++){
		if(strcasecmp(array[j].nombre, pivot2) < 0){
			i++;
			struct stacion temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
    }
    struct stacion temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return (i + 1);
}

void QuickSortStationsByName(struct stacion *array , int low , int high){
    if (low < high){
        int Pi = partitionStationsByName(array , low , high);
        QuickSortStationsByName(array , low , Pi -1);
        QuickSortStationsByName(array , Pi + 1 , high);
    }
}

// partition y quickSort son un combo
int partitionBikes(struct bikes *array , int low , int high){
    tipoDatoBikes pivot = array[high].datoBikes;
    int i = (low - 1);
    for(int j = low ; j<high ; j++){
        if(array[j].datoBikes <= pivot){
            i++;
            struct bikes temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    struct bikes temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return (i + 1);
}

void QuickSortBikes(struct bikes *array , int low , int high){
    if (low < high){
        int Pi = partitionBikes(array , low , high) ;
        QuickSortBikes(array , low , Pi -1) ;
        QuickSortBikes(array , Pi + 1 , high) ;
    }
}

void query1(struct stacion * estaciones, int from, int to){
	printf("\n\n\n\n\n");
	printf("Name\t;Id\t;Viajes Casuales\t;Viajes Miembros\t;Viajes Totales\t;\n");
	for (int i = from; i < to; i++) {
        printf("%-40s;%-7d\t;%-7d\t;%-7d\t;%-7d\t;\n", estaciones[i].nombre, estaciones[i].id, estaciones[i].cantViajesIniciadosCasuales, estaciones[i].cantViajesIniciadosMiembros, estaciones[i].cantViajesIniciadosCasuales + estaciones[i].cantViajesIniciadosMiembros);
	}
	printf("\n\n\n\n\n");
}

void query2(struct stacion * estaciones, int from, int to, time_t iniTime){
	printf("\n\n\n\n\n");
	printf("bikeStation\t;bikeEndStation\t;oldestDateTime\t;\n");
	for(int i = from; i<to; i++){
		if(estaciones[i].timeEarliestTrip != iniTime){
			printf("%-40s;%-40s;%-7ld\t;%-7d\t;\n", estaciones[i].nombre, estaciones[i].nameEarliestTrip, estaciones[i].timeEarliestTrip, estaciones[i].id);
		}
	}
	printf("\n\n\n\n\n");
}

void showByWeekDay(char * day, int cantStarted, int cantEnded){
	printf("%s\t;%d\t;%d\t;\n", day, cantStarted, cantEnded);
}

void query3(int diasStart[], int diasEnd[]){
	printf("\n\n\n\n\n");
	printf("WeekDay\t;Trips started\t;Trips Ended\t;\n");
	char * diasSemana[CANT_DIAS_SEMANA] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
	for(int i = 0; i<CANT_DIAS_SEMANA; i++){
		showByWeekDay(diasSemana[i], diasStart[i], diasEnd[i]);
	}
	printf("\n\n\n\n\n");
}

void showTrips(struct bikes * viajes, int from, int to){
	printf("Trips\n\n");
	printf("Start time\t;End time\t;Id Start\t;Id End\t;Is Member\t;\n");
	for(int i = from; i<to; i++){
		printf("%ld\t;%ld\t;%d;\t%d;\t%d;\n", viajes[i].timeStart, viajes[i].timeEnd, viajes[i].idStart, viajes[i].idEnd, viajes[i].member);
	}
	printf("\n\n\n\n\n");
}

void showStations(struct stacion * estaciones, int from, int to){
	printf("Stations\n\n");
	printf("Name\t;Id\t;Viajes Casuales\t;Viajes Miembros\t;\n");
	for (int i = from; i < to; i++) {
        printf("%-40s;%-7d\t;%-7d\t;%-7d\t;\n", estaciones[i].nombre, estaciones[i].id, estaciones[i].cantViajesIniciadosCasuales, estaciones[i].cantViajesIniciadosMiembros);
	}
	printf("\n\n\n\n\n");
}

//int getWeekNum(time_t tiempo){
//	return = (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7;
//}

int main(int argc, char const *argv[]) {
	time_t iniTime = time(NULL)+1000;
	int diasStart[] = {0, 0, 0, 0, 0, 0, 0};
	int diasEnd[] = {0, 0, 0, 0, 0, 0, 0};
    struct bikes * viajes = NULL;
    struct stacion * estaciones = NULL;
    FILE * file1 = fopen(argv[1], "r");
    FILE * file2 = fopen(argv[2], "r");
    readTitle(file1);
    readTitle(file2);
    char s[200];
    char * token;
    int i;
    time_t t = time(NULL);
    int lineCounterStations = 0;
	int lineCounterBikes=0;

	// Lee las estaciones
    /*while (!feof(file1) && lineCounterStations<linesStations) {
        readLine(file1, s);
        token = strtok(s, ";");
        if (token != NULL) {
            if (lineCounterStations%BLOQUE == 0) {
                estaciones = realloc(estaciones, (lineCounterStations + BLOQUE + 1) * sizeof(*estaciones));
            }
            for (i = 0; token != NULL; token = strtok(NULL, ";"), i++) {
                switch (i) {
                case 0:
                    estaciones[lineCounterStations].nombre = malloc(strlen(token)+1);
                    strcpy(estaciones[lineCounterStations].nombre, token);
                    break;
                case 1:
                    sscanf(token, "%g", &(estaciones[lineCounterStations].lat));
                    break;
                case 2:
                    sscanf(token, "%g", &(estaciones[lineCounterStations].lon));
                    break;
                case 3:
                    sscanf(token, "%d", &(estaciones[lineCounterStations].id));
                    break;
                }
            }
            lineCounterStations++;
        }
    }*/
    
	while (!feof(file1) && lineCounterStations<linesStations) {
        readLine(file1, s);
        token = strtok(s, ";");
        if (token != NULL) {
            if (lineCounterStations%BLOQUE == 0) {
                estaciones = realloc(estaciones, (lineCounterStations + BLOQUE + 1) * sizeof(*estaciones));
            }
            for (i = 0; token != NULL; token = strtok(NULL, ";"), i++) {
                switch (i) {
                case 0:
                    sscanf(token, "%d", &(estaciones[lineCounterStations].id));
                    break;
                case 1:
                    estaciones[lineCounterStations].nombre = malloc(strlen(token)+1);
                    strcpy(estaciones[lineCounterStations].nombre, token);
                    break;
                case 2:
                    sscanf(token, "%g", &(estaciones[lineCounterStations].lat));
                    break;
                case 3:
                    sscanf(token, "%g", &(estaciones[lineCounterStations].lon));
                    break;
                }
            }
            lineCounterStations++;
        }
    }

	// Lee los viajes
	/*while (!feof(file2) && lineCounterBikes<linesBikes) {
		if(lineCounterBikes%100000 == 0){
			printf("%d\n", lineCounterBikes);
		}
        readLine(file2, s);
        token = strtok(s, ";");
        if (token != NULL) {
            if (lineCounterBikes%BLOQUE == 0) {
                viajes = realloc(viajes, (lineCounterBikes + BLOQUE + 1) * sizeof(*viajes));
            }
			//started_at;start_station_id;ended_at;end_station_id;rideable_type;member_casual
			//2022-10-29 14:58:11.000000;513711;2022-10-29 15:23:04.000000;482106;electric_bike;casual
			struct bikes aux;
            for (i = 0; token != NULL; token = strtok(NULL, ";"), i++) {
                switch (i) {
					case 0: // time start
						sscanf(token, "%ld", &(aux.timeStart));
						//diasStart[getWeekNun(token)]++; // Falta hacer getWeekNum y esta
                    break;
					case 1: // id station start
						sscanf(token, "%d", &(aux.idStart));
					break; 
					case 2: // time end
						sscanf(token, "%ld", &(aux.timeEnd));
						//diasEnd[getWeekNun(token)]++; // Falta hacer getWeekNum y esta
					break;
					case 3: // id station end
						sscanf(token, "%d", &(aux.idEnd));
					break;
					case 5: // membert type
						sscanf(token, "%c", &(aux.member));
					break;
					default:
						token = NULL;
					break;
                }
            }
			// Encuentra la cantidad de viajes iniciados casuales y por miembros de cada estacion
			for(int j = 0; j<=lineCounterStations; j++){
				if(estaciones[j].id == aux.idStart){
					//printf("%c\n", viajes[i].member);
					if(aux.member == 'm'){
						estaciones[j].cantViajesIniciadosMiembros++;
					}
					else if(aux.member == 'c'){
						estaciones[j].cantViajesIniciadosCasuales++;
					}
				}
			}
            lineCounterBikes++;
        }
    }*/

	while (!feof(file2) && lineCounterBikes<linesBikes) {
		if(lineCounterBikes%1000000 == 0){
			printf("%ld\n", time(NULL) - t);
			printf("%d\n", lineCounterBikes);
		}
        readLine(file2, s);
        token = strtok(s, ";");
        if (token != NULL) {
            if (lineCounterBikes%BLOQUE == 0) {
                viajes = realloc(viajes, (lineCounterBikes + BLOQUE + 1) * sizeof(*viajes));
            }
			//start_date;emplacement_pk_start;end_date;emplacement_pk_end;is_member
			//2021-05-06 16:44:13;658;2021-05-06 16:51:08;909;1
			struct bikes aux;
            for (i = 0; token != NULL; token = strtok(NULL, ";"), i++) {
                switch (i) {
					case 0: // time start
						sscanf(token, "%ld", &(aux.timeStart));
						//diasStart[getWeekNun(token)]++; // Falta hacer getWeekNum y esta
                    break;
					case 1: // id station start
						sscanf(token, "%d", &(aux.idStart));
					break; 
					case 2: // time end
						sscanf(token, "%ld", &(aux.timeEnd));
						//diasEnd[getWeekNun(token)]++; // Falta hacer getWeekNum y esta
					break;
					case 3: // id station end
						sscanf(token, "%d", &(aux.idEnd));
					break;
					case 4: // membert type
						sscanf(token, "%c", &(aux.member));
					break;
					default:
						token = NULL;
					break;
                }
            }
			// Encuentra la cantidad de viajes iniciados casuales y por miembros de cada estacion
			for(int j = 0; j<=lineCounterStations; j++){
				if(estaciones[j].id == aux.idStart){
					if(aux.member == '1'){
						estaciones[j].cantViajesIniciadosMiembros++;
					}
					else if(aux.member == '0'){
						estaciones[j].cantViajesIniciadosCasuales++;
					}
					if(estaciones[j].id != aux.idEnd){
						if(estaciones[j].timeEarliestTrip > aux.timeStart){
							// cambia
						}
					}
				}
			}
            lineCounterBikes++;
        }
    }



	/**/
	// inicializa todos los tiempos en un momento en el futuro (todos los viajes son anteriores a iniTime)
	/*for(int i = 0; i<lineCounterStations; i++){
		estaciones[i].timeEarliestTrip = iniTime;
	}
	
	// No funciona, deberia encontrar el nombre del viaje mas antiguo a cada estaciones[i]
	for(int i = 1; i<lineCounterStations; i++){ // busco estaciones[i].nameEarliestTrip
	int flag = 1;
		for(int j = 1; j<lineCounterBikes; j++){
			if(viajes[j].idStart == estaciones[i].id){
				for(int k = 1; k<lineCounterStations; k++){
					if(viajes[j].idEnd == estaciones[k].id){
						if((viajes[j].timeStart < estaciones[i].timeEarliestTrip) && (i!=k)){
							estaciones[i].timeEarliestTrip = viajes[j].timeStart;
							estaciones[i].nameEarliestTrip = estaciones[k].nombre;
						}
					}
				}
			}
		}
	}
	
	//for(int i = 0; i<linesStations; i++){
	//	int flag = 1;
	//	for(int j = 0; j<linesStations && flag; j++){
	//		if(estaciones[i].idEarliestTrip == estaciones[j].id){
	//			estaciones[i].nameEarliestTrip = estaciones[j].nombre;
	//			flag = 0;
	//		}
	//	}
	//}
	*/

	// What to do

	//QuickSortBikes(viajes, 1, lineCounterBikes);
	//showTrips(viajes, 1, lineCounterBikes);			// lineCounterBikes
	//showStations(estaciones, 1, lineCounterStations); 	// lineCounterStations

	// Query 1 ANDA
    printf("%ld\n", time(NULL) - t);
    QuickSortStationsByViajes(estaciones , 0 , lineCounterStations-1);
	query1(estaciones, 0, lineCounterStations-1);

	// Query 2 FALTA
	//QuickSortStationsByName(estaciones , 0 , lineCounterStations);
	//query2(estaciones, 0, lineCounterStations, iniTime);

	// Query 3 FALTA
	//query3(diasStart, diasEnd);
    
    printf("%ld\n", time(NULL) - t);

    // printf("%s\n", s);
    fclose(file1);
    return 0;
}
