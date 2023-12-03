#include "bikesADT.h"
#include <time.h>

#define T_DAYS 7
enum DIAS {MON = 0, TUE, WED, THU, FRI, SAT, SUN};

struct trip {
    time_t nTime; // valor de hora de inicio
    struct tm sTime; // datos de hora de inicio
    char * sName; // nombre de estacion de inicio
    char * eName; // nombre de estacion de fin
};

struct station {
    // query1:
    unsigned memberTrips; // viajes de usuarios miembros
    unsigned casualTrips; // viajes de usuarios casuales
    // query2:
    struct trip oldest; // viaje mas antiguo
};


struct node {
    struct station head; // estacion almacenada en nodo
    struct node * alphaTail; // siguiente en forma alfabetica
    struct node * countTail; // siguiente en cantidad de viajes
};

typedef struct node * tList;

struct bikesCDT {
    //query3:
    int week[T_DAYS];
    tList alphaFirst;
    tList countFirst;
};

bikesADT newBikesADT(void);

int main(int argc, char const *argv[]) {

    sizeof(struct node);

    return 0;
}

/*
    IDEAS:
        -hacer lista donde guardar los id de las estaciones, y ahi verificar si una estacion existe o no
        -al agregar viaje, tener que verif el id, y sacar datos (?
*/
