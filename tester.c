#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define BLOQUE 50

struct stacion {
    char * nombre;
    float lat;
    float lon;
    int id;
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

int main(int argc, char const *argv[]) {
    // struct bikes * viajes;
    struct stacion * estaciones = NULL;
    FILE * file = fopen(argv[1], "r");
    readTitle(file);
    char s[200];
    char * token;
    int i;

    time_t t = time(NULL);
    size_t w = 0;
    while (!feof(file)) {
        readLine(file, s);
        token = strtok(s, ";");
        if (token != NULL) {
            if (w%BLOQUE == 0) {
                estaciones = realloc(estaciones, (w + BLOQUE + 1) * sizeof(*estaciones));
            }
            for (i = 0; token != NULL; token = strtok(NULL, ";"), i++) {
                switch (i) {
                case 0:
                    estaciones[w].nombre = malloc(strlen(token)+1);
                    strcpy(estaciones[w].nombre, token);
                    break;
                case 1:
                    sscanf(token, "%g", &(estaciones[w].lat));
                    break;
                case 2:
                    sscanf(token, "%g", &(estaciones[w].lon));
                    break;
                case 3:
                    sscanf(token, "%d", &(estaciones[w].id));
                    break;
                }
            }
            w++;
        }
    }

    for (int i = 0; i < w; i++) {
        printf("%-40s;%-7g\t;%-7g\t;%-7d\t;\n", estaciones[i].nombre, estaciones[i].lat, estaciones[i].lon, estaciones[i].id);
    }
    
    
    printf("%ld\n", time(NULL) - t);

    // printf("%s\n", s);
    fclose(file);
    return 0;
}
