#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_NOMBRE 200
#define MAX_FECHA 7
#define MAX_NOMBRE_ARCHIVO 30
#define MAX_COMANDO 30

const int EXITO = 1;	
const int ERROR_ESCRITURA = -1;

const bool EXISTE = true;
const char COMANDO_PERDONABLES[] = "perdonables";
const char COMANDO_LIBERAR[] = "liberar";
const char COMANDO_ACTUALIZAR[] = "actualizar";
const char COMANDO_MOSTRAR_LIBERADOS[] = "mostrar_liberados";
const char EXTENSION_DATO[] = ".dat";
const char EXTENSION_ARCHIVO_DE_TEXTO[] = ".txt";
const char NOMBRE_DEL_ARCHIVO_CRUCIATUS[] = "crucio.dat";
const char NOMBRE_DEL_ARCHIVO_IMPERIUS[] = "imperius.dat";
const char PRIMERA_PARTE_NOMBRE_ARCHIVO_LIBERADOS[] = "liberados_";

const char LEER[] = "r";
const char ESCRIBIR[] = "w";


#define CONDUCTA_MALA 'M'
#define VALOR_CONDUCTA_MALA 0

#define CONDUCTA_REGULAR 'R'
#define VALOR_CONDUCTA_REGULAR 1

#define CONDUCTA_BUENA 'B'
#define VALOR_CONDUCTA_BUENA 2


const int NUMERO_DE_CAMPOS_DE_PRESOS = 7;






typedef struct preso {
	char nombre[MAX_NOMBRE];
	unsigned int edad;
	char conducta;
	unsigned int pabellon;
	unsigned int celda;
	char fecha[MAX_FECHA];
	int maldicion_realizada;
}preso_t;



void leer_preso(preso_t* preso,FILE* archivo){
	fread(preso, sizeof(preso_t),1, archivo);
}
bool escribir_preso(preso_t* preso, FILE* archivo){
	size_t escrito = fwrite(preso, sizeof(preso_t),1, archivo);
	return(escrito > 0);
}
void escribir_nombre_del_preso(preso_t preso, FILE* archivo){
	fprintf(archivo,"%s\n",preso.nombre);
	
}
int leer_nombre_preso(char nombre[], FILE* archivo_de_texto){
	return(fscanf(archivo_de_texto,"%[^\n]\n",nombre));
}


void ejecutar_comando_ayudas(){
	printf("\nComando %s:\n",COMANDO_PERDONABLES);
	printf("\t Ejemplo:\x1b[33m ./azkaban %s <nombre_del_archivo> \x1b[0m\n",COMANDO_PERDONABLES);
	printf("\t De los dos archivos ( %s , %s ) ambos binarios se creara un nuevo archivo (tambien binario) con el nombre ingresado;\n",NOMBRE_DEL_ARCHIVO_IMPERIUS, NOMBRE_DEL_ARCHIVO_CRUCIATUS);
	printf("\t este archivo contendra aquellos presos que no realizaron ambas maldiciones.\n\n");

	printf("Comando %s:\n", COMANDO_LIBERAR);
	printf("\t Ejemplo: \x1b[33m ./azkaban %s <archivo_perdonables> <aaaamm> <conducta> \x1b[0m \n",COMANDO_LIBERAR);
	printf("\t Dado el archivo de presos perdonables ingresado (binario) se creara un nuevo archivo (de texto)\n ");
	printf("\t con el nombre de aquellos presos que cumplen las condiciones de fecha y de conducta ingresados.\n");
	printf("\t La fecha tiene que seguir el estandar de 'aaaamm' donde el año se expresa en 4 digitos seguido de 2 digitos que representan el mes.\n");
	printf("\t La conducta se rige por el orden de '%c' mayor que '%c' mayor que '%c'.\n\n", CONDUCTA_BUENA, CONDUCTA_REGULAR, CONDUCTA_MALA);

	printf("Comando %s:\n",COMANDO_MOSTRAR_LIBERADOS);
	printf("\t Ejemplo: \x1b[33m ./azkaban %s <aaaamm> \x1b[0m \n", COMANDO_MOSTRAR_LIBERADOS);
	printf("\t Dado un archivo existente de liberados en la fecha ingresada, se procedera a mostrar a dichos presos.\n\n");	

	printf("Comando %s:\n",COMANDO_ACTUALIZAR);
	printf("\t Ejemplo: \x1b[33m ./azkaban %s <aaaamm> \x1b[0m \n", COMANDO_ACTUALIZAR);
	printf("\t actualizara los archvios de crucio e imperio (ambos binarios) e liminando a los presos que fueron liberados en la fecha ingresada\n\n\n");
}


void ejecutar_comando_mostrar_liberados(char nombre_del_archivo[], char fecha[]){
	FILE* presos_liberados = fopen(nombre_del_archivo, LEER);
	if(!presos_liberados){
		printf("Ocurrio un error al intentar abrir el archivo de presos a ser liberados.\n Solucione el error e intente nuevamente\n");
		return;
	}
	char preso_actual[MAX_NOMBRE];
	int leidos = leer_nombre_preso(preso_actual, presos_liberados);
	printf("Presos a ser liberados en la fecha %s: \n\n", fecha);
	while(leidos > 0){
		printf("\t%s\n",preso_actual);
		leidos = leer_nombre_preso(preso_actual, presos_liberados);
	}
	fclose(presos_liberados);
}


int actualizar_presos(FILE* presos_cruciatus,FILE* presos_imperius,FILE* presos_liberados,FILE* presos_cruciatus_aux,FILE* presos_imperius_aux){
	preso_t preso_crucio;
	preso_t preso_imperio;
	char preso_actual[MAX_NOMBRE];

	int leidos = leer_nombre_preso(preso_actual, presos_liberados);	
	leer_preso(&preso_crucio, presos_cruciatus);
	leer_preso(&preso_imperio, presos_imperius);
	bool pude_escribir = true;
	while(!feof(presos_cruciatus) && !feof(presos_imperius) && leidos > 0 && pude_escribir){
		if(strcmp(preso_imperio.nombre,preso_crucio.nombre) == 0){
			if(strcmp(preso_imperio.nombre,preso_actual) > 0){
				leidos = leer_nombre_preso(preso_actual, presos_liberados);
			}else{
				pude_escribir = escribir_preso(&preso_imperio, presos_imperius_aux);
				pude_escribir = escribir_preso(&preso_crucio, presos_cruciatus_aux);
				leer_preso(&preso_imperio, presos_imperius);
				leer_preso(&preso_crucio, presos_cruciatus);
			}
		}else if(strcmp(preso_imperio.nombre, preso_crucio.nombre) < 0){ 
			if(strcmp(preso_imperio.nombre, preso_actual) < 0){
				pude_escribir = escribir_preso(&preso_imperio, presos_imperius_aux);
				leer_preso(&preso_imperio, presos_imperius);
			}else if(strcmp(preso_imperio.nombre, preso_actual) == 0){
				leer_preso(&preso_imperio, presos_imperius);
				leidos = leer_nombre_preso(preso_actual, presos_liberados);
			}else{
				leidos = leer_nombre_preso(preso_actual, presos_liberados);
			}
		}else if(strcmp(preso_imperio.nombre, preso_crucio.nombre) > 0){
			if(strcmp(preso_crucio.nombre, preso_actual) < 0){
				pude_escribir = escribir_preso(&preso_crucio, presos_cruciatus_aux);
				leer_preso(&preso_crucio, presos_cruciatus);
			}else if(strcmp(preso_crucio.nombre, preso_actual) == 0){
				leer_preso(&preso_crucio, presos_cruciatus);
				leidos = leer_nombre_preso(preso_actual, presos_liberados);
			}else{
				leidos = leer_nombre_preso(preso_actual, presos_liberados);
			}
		}
	}
	while(!feof(presos_imperius) && leidos > 0 && pude_escribir){
		if(strcmp(preso_imperio.nombre, preso_actual) > 0){
			pude_escribir = escribir_preso(&preso_imperio, presos_imperius_aux);
			leer_preso(&preso_imperio, presos_imperius);
		}else if(strcmp(preso_imperio.nombre, preso_actual) == 0){
			leer_preso(&preso_imperio, presos_imperius);
			leidos = leer_nombre_preso(preso_actual, presos_liberados);
		}else{
			leidos = leer_nombre_preso(preso_actual, presos_liberados);
		}
	}
	while(!feof(presos_cruciatus) && leidos > 0 && pude_escribir){
		if(strcmp(preso_crucio.nombre, preso_actual) > 0){
			pude_escribir = escribir_preso(&preso_crucio, presos_cruciatus_aux);
			leer_preso(&preso_crucio, presos_cruciatus);
		}else if(strcmp(preso_crucio.nombre, preso_actual) == 0){
			leer_preso(&preso_crucio, presos_cruciatus);
			leidos = leer_nombre_preso(preso_actual, presos_liberados);
		}else{
			leidos = leer_nombre_preso(preso_actual, presos_liberados);
		}
	}
	while(!feof(presos_imperius) && pude_escribir){
		pude_escribir = escribir_preso(&preso_imperio, presos_imperius_aux);
		leer_preso(&preso_imperio, presos_imperius);		
	}
	while(!feof(presos_cruciatus) && pude_escribir){
		pude_escribir = escribir_preso(&preso_crucio, presos_cruciatus_aux);
		leer_preso(&preso_crucio, presos_cruciatus);
	}
	if(!pude_escribir){
		printf("\x1b[31m Ocurrio un problema al crear los archivos; Asegurese de tener memoria suficiente.\x1b[0m\n");
		return ERROR_ESCRITURA;
	}
	return EXITO;
}
void ejecutar_comando_actualizar(char nombre_del_archivo[], char fecha[]){
	FILE* presos_cruciatus = fopen(NOMBRE_DEL_ARCHIVO_CRUCIATUS, LEER);
    if(!presos_cruciatus){	
		printf("Ocurrio un error al intentar abrir el archivo de presos que realizaron la maldicion crucio. \n Solucione el problema e intente nuevamente.\n");
    	return;
    }
	FILE* presos_imperius = fopen(NOMBRE_DEL_ARCHIVO_IMPERIUS, LEER);
	if(!presos_imperius){
		printf("Ocurrio un error al intentar abrir el archivo de presos que realizaron la maldicion imperio. \n Solucione el problema e intente nuevamente.\n");
		fclose(presos_cruciatus);
		return;
	}
	FILE* presos_liberados = fopen(nombre_del_archivo, LEER);
	if(!presos_liberados){
		printf("Ocurrio un error al intentar abrir el archivo de presos a liberar en la fecha %s. \n Solucione el problema e intente nuevamente.\n", fecha);
		fclose(presos_cruciatus);
		fclose(presos_imperius);
		return;
	}
	FILE* presos_cruciatus_aux = fopen("presos_crucio_auxiliar",ESCRIBIR);
	if(!presos_cruciatus_aux){
		printf("Ocurrio un error al intentar crear archivos auxiliares. \n Solucione el problema e intente nuevamente.\n");
		fclose(presos_cruciatus);
		fclose(presos_imperius);
		fclose(presos_liberados);
		return;
	}
	FILE* presos_imperius_aux = fopen("presos_imperio_auxiliar",ESCRIBIR);
	if(!presos_imperius_aux){
		printf("Ocurrio un error al intentar crear archivos auxiliares. \n Solucione el problema e intente nuevamente.\n");
		fclose(presos_cruciatus);
		fclose(presos_imperius);
		fclose(presos_liberados);
		fclose(presos_cruciatus_aux);		
		return;
	}

	int resultado = actualizar_presos(presos_cruciatus, presos_imperius, presos_liberados, presos_cruciatus_aux, presos_imperius_aux);
	
	fclose(presos_imperius);
	fclose(presos_cruciatus);
	fclose(presos_liberados);
	fclose(presos_cruciatus_aux);
	fclose(presos_imperius_aux);

	if(resultado == EXITO){
		printf("¡El programa se ejecuto con exito!\n");
		remove(NOMBRE_DEL_ARCHIVO_CRUCIATUS);
		remove(NOMBRE_DEL_ARCHIVO_IMPERIUS);
		rename("presos_crucio_auxiliar", NOMBRE_DEL_ARCHIVO_CRUCIATUS);
		rename("presos_imperio_auxiliar", NOMBRE_DEL_ARCHIVO_IMPERIUS);
	}else{
		remove("presos_crucio_auxiliar");
		remove("presos_imperio_auxiliar");
	}
}


int valor_conducta(char conducta){
	switch(conducta){
		case CONDUCTA_MALA:
			return(VALOR_CONDUCTA_MALA);
		break;	
		case CONDUCTA_REGULAR:
			return(VALOR_CONDUCTA_REGULAR);
		break;
		default:
			return(VALOR_CONDUCTA_BUENA);
		break;
	}
}
int conductacmp(char conducta_1, char conducta_2){
	int valor_cond1 = valor_conducta(conducta_1);
	int valor_cond2 = valor_conducta(conducta_2);
	return(valor_cond1 - valor_cond2);
}
bool el_preso_es_liberable(preso_t preso, int fecha, char conducta){
	int fecha_preso = atoi(preso.fecha);
	return((fecha_preso <= fecha) && (conductacmp(preso.conducta, conducta) >= 0));
}
void escribir_presos_a_liberar(FILE* presos_perdonables, FILE* presos_a_liberar, int fecha, char conducta){
	preso_t preso;
	leer_preso(&preso,presos_perdonables);
	while(!feof(presos_perdonables)){
		if(el_preso_es_liberable(preso, fecha, conducta)){
			escribir_nombre_del_preso(preso, presos_a_liberar);
		}
		leer_preso(&preso, presos_perdonables);	
	}
}
void ejecutar_comando_liberar(char nombre_del_archivo_perdonables[],int fecha, char conducta, char nombre_del_archivo[]){
	FILE* presos_perdonables;
	FILE* presos_a_liberar;
	presos_perdonables = fopen(nombre_del_archivo_perdonables,LEER);
	if(!presos_perdonables){
		printf("Ocurrio un error al intentar abrir el archivo de presos perdonables. \n Solucione el problema e intente nuevamente.\n");
		return;
	}
	presos_a_liberar= fopen(nombre_del_archivo, ESCRIBIR);
	if(!presos_a_liberar){
		printf("Ocurrio un error al intentar crear el archivo de presos a liberar. \n Solucione el problema e intente nuevamente.\n");		
		fclose(presos_perdonables);
		return;
	}

	escribir_presos_a_liberar(presos_perdonables, presos_a_liberar, fecha, conducta);

	fclose(presos_perdonables);
	fclose(presos_a_liberar);		
	printf("El programa se ejecuto con exito\n");
}


void escribir_presos_perdonables(FILE* presos_perdonables, FILE* presos_imperius, FILE* presos_cruciatus){
	preso_t preso_crucio;
 	preso_t preso_imperio;
	leer_preso(&preso_crucio, presos_cruciatus);
	leer_preso(&preso_imperio, presos_imperius);

	while(!feof(presos_cruciatus) && !feof(presos_imperius)){
		if(strcmp(preso_crucio.nombre,preso_imperio.nombre) == 0){
			leer_preso(&preso_crucio, presos_cruciatus);
			leer_preso(&preso_imperio, presos_imperius);
		}else if(strcmp(preso_crucio.nombre, preso_imperio.nombre) < 0){
			escribir_preso(&preso_crucio,presos_perdonables);
			leer_preso(&preso_crucio, presos_cruciatus);
		}else if(strcmp(preso_crucio.nombre, preso_imperio.nombre) > 0){
			escribir_preso(&preso_imperio,presos_perdonables);
			leer_preso(&preso_imperio, presos_imperius);
		}
	}
	while(!feof(presos_cruciatus)){
		escribir_preso(&preso_crucio,presos_perdonables);
		leer_preso(&preso_crucio, presos_cruciatus);
	}
	while(!feof(presos_imperius)){
		escribir_preso(&preso_imperio,presos_perdonables);
		leer_preso(&preso_imperio, presos_imperius);
	}
}
void ejecutar_comando_perdonables(char nombre_del_archivo[]){
	FILE* presos_cruciatus;
	FILE* presos_imperius;
	FILE* presos_perdonables;

	presos_cruciatus = fopen(NOMBRE_DEL_ARCHIVO_CRUCIATUS, LEER);
	if(!presos_cruciatus){
		printf("Ocurrio un error al intentar abrir el archivo de presos que realizaron la maldicion crucio. \n Solucione el problema e intente nuevamente.\n");
		return;
	}
	presos_imperius = fopen(NOMBRE_DEL_ARCHIVO_IMPERIUS, LEER);
	if(!presos_imperius){
		printf("Ocurrio un error al intentar abrir el archivo de presos que realizaron la maldicion preso_imperio. \n Solucione el problema e intente nuevamente.\n");
		fclose(presos_cruciatus);
		return;
	}
	presos_perdonables = fopen(nombre_del_archivo, ESCRIBIR);
	if(!presos_perdonables){
		printf("Ocurrio un error al intentar crear el archivo. \n Solucione el problema e intente nuevamente.\n");
		fclose(presos_cruciatus);
		fclose(presos_imperius);
		return;
	}

	escribir_presos_perdonables(presos_perdonables, presos_imperius, presos_cruciatus);
	
	fclose(presos_cruciatus);
	fclose(presos_imperius);
	fclose(presos_perdonables);
	
	printf("El programa se ejecuto con exito\n");
}


void crear_nombre_del_archivo(char nombre_del_archivo[], const char primera_parte[], char segunda_parte[], const char extension[]){
	strcpy(nombre_del_archivo,primera_parte);
	strcat(nombre_del_archivo,segunda_parte);
	strcat(nombre_del_archivo,extension);	
}
bool existe_archivo_con_el_nombre(char nombre_del_archivo[]){
	FILE* archivo_de_prueba = fopen(nombre_del_archivo, "r");
	if(!archivo_de_prueba){
		return(!EXISTE);
	}else{
		fclose(archivo_de_prueba);
		return(EXISTE);
	}
}
int main(int argc, char* argv[]){
	int cant_comandos;
	char comando[MAX_COMANDO];
	cant_comandos = argc;

	if(cant_comandos > 1){
		strcpy(comando, argv[1]);
	}
	if(cant_comandos == 3 && strcmp(comando,COMANDO_PERDONABLES) == 0){
		char nombre_del_archivo[MAX_NOMBRE_ARCHIVO];
		strcpy(nombre_del_archivo, argv[2]);
		ejecutar_comando_perdonables(nombre_del_archivo);
	}else if(cant_comandos == 5 && strcmp(comando, COMANDO_LIBERAR) == 0){
		char nombre_del_archivo[MAX_NOMBRE_ARCHIVO];
		int fecha = atoi(argv[3]);
		char conducta = argv[4][0]; 

		crear_nombre_del_archivo(nombre_del_archivo,PRIMERA_PARTE_NOMBRE_ARCHIVO_LIBERADOS,argv[3],EXTENSION_ARCHIVO_DE_TEXTO);
		if(!existe_archivo_con_el_nombre(nombre_del_archivo)){
			ejecutar_comando_liberar(argv[2],fecha,conducta,nombre_del_archivo);
		}
		else{
			printf("\x1b[34m Ya existe un archivo con los liberados de la fecha %i, Ojo cuidado. \x1b[0m", fecha);
		}
	}else if(cant_comandos == 3 && strcmp(comando, COMANDO_ACTUALIZAR) == 0){
		char nombre_del_archivo[MAX_NOMBRE_ARCHIVO];
		crear_nombre_del_archivo(nombre_del_archivo,PRIMERA_PARTE_NOMBRE_ARCHIVO_LIBERADOS,argv[2],EXTENSION_ARCHIVO_DE_TEXTO);
		if(existe_archivo_con_el_nombre(nombre_del_archivo)){
			ejecutar_comando_actualizar(nombre_del_archivo, argv[2]);
		}else{
			printf("El archivo liberados de la fecha: %s no existe.\n", argv[2]);
		}

	}else if(cant_comandos == 3 && strcmp(comando, COMANDO_MOSTRAR_LIBERADOS) == 0){
		char nombre_del_archivo[MAX_NOMBRE_ARCHIVO];
		crear_nombre_del_archivo(nombre_del_archivo,PRIMERA_PARTE_NOMBRE_ARCHIVO_LIBERADOS,argv[2],EXTENSION_ARCHIVO_DE_TEXTO);
		if(existe_archivo_con_el_nombre(nombre_del_archivo)){
			ejecutar_comando_mostrar_liberados(nombre_del_archivo, argv[2]);
		}else{
			printf("No existe el archivo de liberados de la fecha %s. Ejecute previamente el comando %s y vuelva a intentarlo\n",argv[2], COMANDO_LIBERAR);
		}

	}else{
		ejecutar_comando_ayudas();
	}
	return 0;
} 
