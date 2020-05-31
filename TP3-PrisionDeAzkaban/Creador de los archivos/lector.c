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

int main(int argc, char* argv[]){
	FILE* presos = fopen(argv[1], "r");
	if(presos == NULL){
        printf("ocurrio un error al intentar leer el archivo!");        
        return -1;
    }

	preso_t preso;
	int leidos = fread(&preso,sizeof(preso_t),1, presos);
	while(leidos > 0 && !feof(presos)){
		printf("Nombre: %s\n Edad: %i\n Conducta: %c\n Pabellon, Celda: %i,%i\n fecha: %s\n maldicion_realizada: %i\n\n\n",preso.nombre, preso.edad, preso.conducta, preso.pabellon, preso.celda, preso.fecha, preso.maldicion_realizada );
		int leidos = fread(&preso,sizeof(preso_t),1, presos);
	}
    fclose(presos);
}
