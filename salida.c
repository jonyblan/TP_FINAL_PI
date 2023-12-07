
char *que1="query1.csv";

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
while(hasNext1StaADT(sta)){
    query1 q1=next1StaADT(sta);
    fprintf(pQuery1, "%s;%d;%d;%d \n", q1->bikeStation, q1->memberTrips, q1->casualTrips, q1->totalTrips);
}

char *que2="query2.csv";

FILE *pQuery2=fopen(query2, "w");
if(pQuery2==NULL){
    printf("Problema creando %s. Aborto.\n", Query2);
    exit(1);
}
char * q2camp1="bikeStation";
char * q2camp2="bikeEndStation";
char * q2camp3="oldestDateTime";


fprintf(pQuery2, "%s;%s;%s\n",q2camp1,q2camp2,q2camp3);
while(hasNext2StaADT(sta)){
    query2 q2=next2StaADT(sta);
    fprintf(pQuery2, "%s;%s;%d/%d/%d %d:%d \n", q2->bikeStation, q2->bikeEndStation, q2->oldestDateTime.year,q2->oldestDateTime.mon,q2->oldestDateTime.mday,q2->oldestDateTime.hour,q2->oldestDateTime.min );
}


char *que3="query3.csv";

FILE *pQuery3=fopen(query3, "w");
if(pQuery3==NULL){
    printf("Problema creando %s. Aborto.\n", query3);
    exit(1);
}
char * q3camp1="weekDay";
char * q3camp2="startedTrips";
char * q3camp3="endedTrips";

char* * diasSemana[7]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};

fprintf(pQuery3, "%s;%s;%s", q3camp1, q3camp2,q3camp3);
for(int i=0; i<T_DAYS; i++){
    query3 q3=query3StaADT(sta);
    fprintf(pQuery3,"%s;%d;%d \n",diasSemana[i],query3->q3_arr[i].startedTrips,query3->q3_arr[i].endedTrips);
}