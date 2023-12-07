#include <stdio-h>
#include <string.h>

char *query1="query1.csv";

FILE *pQuery1=fopen(query1, "w");
if(pQuery1==NULL){
    printf("Problema creando %s. Aborto.\n", query1);
    exit(1);
}
char * q1camp1="bikeStation";
char * q1camp2="memberTrips";
char * q1camp3="casualTrips";
char * q1camp4="allTrips"

fprintf(query1,"%s;%s;%s;%s", campo1, campo2, campo3, campo4);
for(int i=0; i<stationADT->stations, i++){
    fprintf(query1, "%s;%d;%d;%d \n",stationADT->query1[i].name,stationADT->query1[i].memeberTrips, stationADT->query1[i].casualTrips,stationADT->query1[i].memeberTrips+ stationADT->query1[i].casualTrips);
}

char *query2="query2.csv";

FILE *pQuery2=fopen(query2, "w");
if(pQuery2==NULL){
    printf("Problema creando %s. Aborto.\n", Query2);
    exit(1);
}
char * q2camp1="bikeStation";
char * q2camp2="bikeEndStation";
char * q2camp3="oldestDateTime";

fprintf(pQuery2, "%s,%s,%s\n",q2camp1,q2camp2,q2camp3);
while(hasNext){
    fprintf(pQuery2, )
}


char *query3="query3.csv";

FILE *pQuery3=fopen(query3, "w");
if(pQuery3==NULL){
    printf("Problema creando %s. Aborto.\n", query3);
    exit(1);
}