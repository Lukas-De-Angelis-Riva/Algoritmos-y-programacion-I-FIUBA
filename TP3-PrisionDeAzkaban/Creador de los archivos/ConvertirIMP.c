#include <stdio.h>
#define MAX_NOMBRE 200
#define MAX_FECHA 7

typedef struct preso {
	char nombre[MAX_NOMBRE];
	unsigned int edad;
	char conducta;
	unsigned int pabellon;
	unsigned int celda;
	char fecha[MAX_FECHA];
	int maldicion_realizada;
}preso_t;


int main(){
	
	FILE* presos = fopen("IMPERIO.csv","r");
	if(presos == NULL){
		printf("paso algo 1\n");
		return -1;
	}
	FILE* presos_bin = fopen("imperius.dat", "w");
	if(presos_bin == NULL){
		printf("paso algo 2\n");
		fclose(presos);
		return -2;
	}

	preso_t actual;
	int leidos = fscanf(presos,"%[^;];%i; %c; %i;%i;%[^;];%i\n",
	 actual.nombre, &(actual.edad), &(actual.conducta), &(actual.pabellon), &(actual.celda), actual.fecha, &(actual.maldicion_realizada));
	while(leidos == 7){
		fwrite(&actual,sizeof(actual),1,presos_bin);
		leidos = fscanf(presos,"%[^;];%i; %c; %i;%i;%[^;];%i\n",
		 actual.nombre, &(actual.edad), &(actual.conducta), &(actual.pabellon), &(actual.celda), actual.fecha, &(actual.maldicion_realizada));
	
	}

	fclose(presos_bin);
	fclose(presos);
	return 0;
}
