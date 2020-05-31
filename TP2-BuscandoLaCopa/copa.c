#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "laberinto.h"
#include "copa.h"

#define JUGADOR 'J'
#define RIVAL 'G'
#define COPA 'C'
#define ESCREGUTO 'E'
#define ACROMANTULA 'A'
#define BOGGART 'B'
#define POCION 'P'
#define IMPEDIMENTA 'I'
#define RIDDIKULUS 'R'
#define ESFINGE 'F'



#define SEGUIR_JUGANDO 0
#define GANO_JUGADOR 1
#define PERDIO_JUGADOR -1



#define DERECHA 'd'
#define IZQUIERDA 'a'
#define ARRIBA 'w'
#define ABAJO 's'
#define TOTAL_DE_POCIONES 3

const int DISTANCIA_MANHATTAN = 10;

const int DANIO_POR_TURNO = 3;
const int DANIO_ESCREGUTO = 20;
const int DANIO_ACROMANTULA = 10;
const int DANIO_BOGGART = 15;

const int VIDA_A_RECUPERAR_POCION = 20;
const int MAX_VIDA = 50;
const int VIDA_MINIMA_PARA_MOSTRAR_COPA = 15;

#define MAX_INVENTARIO 5


/*
Condiciones de uso BLOQUE INICIALIZACION

	cargar_laberinto_orginial:
		Pre condiciones: 
			-El laberinto original debera estar inicializado previamente.
		Post condiciones:
			-Copiara el laberinto original al laberinto que se muestra por pantalla. 

	posicion_aleatoria:
		Pre condiciones: ---
		Post condiciones:
			Devuelve una coordenada aleatoria en el espacio dado por TAMANIOxTAMANIO
			Esta no comprobara que esta coordenada sea valida

	cumple_distancia_manhattan:
		Pre condiciones:
			-La copa debera estar inicializada previamente.
			-La posicion de la copa debera estar inicializada en el espacio TAMANIOxTAMANIO.
			-La posicion recibida debera estar inicializada en el espacio TAMANIOxTAMANIO.
		Post condiciones:
			-Devolvera true si la suma de los valores absolutos de la resta de las coordenadas no supera la DISTANCIA_MANHATTAN.
			-Devolvera false en cualquier otro caso. 

	obtener_coordenada_valida:
		Pre condiciones:
			-El laberinto auxiliar recibido debera haber sido inicializado correctamente junto a cada uno de los objetos ya inicializados.
		Post condiciones:
			-Devolvera una coordenada que sea valida para asignarle a la copa, ayudas y obstaculos.

	obtener_coordenada_valida_manhattan:
		Pre condiciones:
			-El laberinto auxiliar recibiddo debera haber sido inicializado correctamente junto a cada uno de los objetos ya inicializados.
		Post condiciones:
			-Devolvera una coordenada que sea valida para asignar al jugador y al rival, es decir, contara con la restriccion de la distancia manhattan. 
	inicializar_copa:
		Pre condiciones:
			-El laberinto auxiliar recibido debera contener ya inicializadas las paredes.
		Post condiciones:
			-inicializara todos los campos de la copa, incluyendo su posicion.
	inicializar_campos_de_obstaculo:
  		Pre condiciones:
			-El vector de obstaculos debera poseer espacio suficiente.
		Post condiciones:
			-Inicializara todos los campos de un obstaculo, menos su posicion.
	inicializar_obstaculos:
		Pre condiciones:
			-El laberinto auxiliar recibido debera contener ya inicializadas las paredes y la copa.
		Post condiciones:
			-El procedimiento inicializara los 3 obstaculos del juego.
	inicializar_campos_de_ayuda:
		Pre condiciones:
			-El vector de ayudas debera poseer espacio suficiente.
		Post condiciones:
			-Inicializara todos los campos de una ayuda, menos su posicion.
	incializar_ayudas:
		Pre condiciones:
			-El laberinto auxiliar recibido debera contener ya inicializadas las paredes, la copa y los obstaculos.
		Post condiciones:
			-El procedimiento inicializara las 6 ayudas del juego
	inicializar_rival:
		Pre condiciones:
			-El laberinto auxiliar recibido debera contener ya inicializadas las paredes, la copa, los obstaculos y las ayudas.
		Post condiciones:
			-El procedimiento inicializara todos los campos que posee el rival.
	inicializar_jugador:
		Pre condiciones:
			-El laberinto auxiliar recibido debera contener ya inicializadas las paredes, la copa, los obstaculos, las ayudas y el rival.
		Post condiciones:
			-El procedimiento inicializara todos los campos que posee el jugador.
	inicializar_laberinto:
		Pre condiciones:
			---
		Post condiciones:
			Inicializará todas las estructuras con los valores correspondientes, creará el laberinto, posicionará todos los elementos, etc.
*/
void cargar_laberinto_original(char laberinto[TAMANIO][TAMANIO], char laberinto_original[TAMANIO][TAMANIO]){
	for(int i = 0; i < TAMANIO; i++){
		for(int j = 0; j < TAMANIO; j++){
			laberinto[i][j] = laberinto_original[i][j];
		}
	}
}
coordenada_t posicion_aleatoria(){
	coordenada_t posicion_random;
	posicion_random.fil = rand()%(TAMANIO);
	posicion_random.col = rand()%(TAMANIO);
	return (posicion_random);
}
bool cumple_distancia_manhattan(coordenada_t posicion_copa, coordenada_t posicion_random){
	int distancia_en_filas = abs(posicion_copa.fil - posicion_random.fil);
	int distancia_en_columnas = abs(posicion_copa.col - posicion_random.col);
	return((distancia_en_filas + distancia_en_columnas) > DISTANCIA_MANHATTAN);
}
coordenada_t obtener_coordenada_valida(char laberinto_auxiliar[TAMANIO][TAMANIO]){
	coordenada_t coordenada_auxiliar;
	do{
		coordenada_auxiliar = posicion_aleatoria();
	}while(laberinto_auxiliar[coordenada_auxiliar.fil][coordenada_auxiliar.col] != VACIO);
	
	return (coordenada_auxiliar);
}
coordenada_t obtener_coordenada_valida_manhattan(char laberinto_auxiliar[TAMANIO][TAMANIO], juego_t* juego){
		coordenada_t coordenada_auxiliar;
		do{
			coordenada_auxiliar = posicion_aleatoria();
		}while((laberinto_auxiliar[coordenada_auxiliar.fil][coordenada_auxiliar.col] != VACIO) || !cumple_distancia_manhattan((*juego).copa.posicion, coordenada_auxiliar));	
		return (coordenada_auxiliar);
}


void inicializar_copa(juego_t* juego, char laberinto_auxiliar[TAMANIO][TAMANIO]){
	(*juego).copa.posicion = obtener_coordenada_valida(laberinto_auxiliar);
	laberinto_auxiliar[(*juego).copa.posicion.fil][(*juego).copa.posicion.col] = COPA;
	(*juego).copa.codigo = COPA;
}

void inicializar_campos_de_obstaculo(char obstaculo, juego_t* juego){
	switch(obstaculo){
		case ESCREGUTO:
			(*juego).obstaculos[(*juego).tope_obstaculos].codigo = ESCREGUTO;
			(*juego).obstaculos[(*juego).tope_obstaculos].danio = DANIO_ESCREGUTO;
		break;
		case ACROMANTULA:
			(*juego).obstaculos[(*juego).tope_obstaculos].codigo = ACROMANTULA;
			(*juego).obstaculos[(*juego).tope_obstaculos].danio = DANIO_ACROMANTULA;
		break;
		case BOGGART:
			(*juego).obstaculos[(*juego).tope_obstaculos].codigo = BOGGART;
			(*juego).obstaculos[(*juego).tope_obstaculos].danio = DANIO_BOGGART;
		break;
	}
	(*juego).tope_obstaculos++;
}
void incializar_obstaculos(juego_t* juego, char laberinto_auxiliar[TAMANIO][TAMANIO]){
	(*juego).tope_obstaculos = 0;

	(*juego).obstaculos[(*juego).tope_obstaculos].posicion = obtener_coordenada_valida(laberinto_auxiliar);
	laberinto_auxiliar[(*juego).obstaculos[(*juego).tope_obstaculos].posicion.fil][(*juego).obstaculos[(*juego).tope_obstaculos].posicion.col] = ESCREGUTO;		
	inicializar_campos_de_obstaculo(ESCREGUTO, juego);
	
	(*juego).obstaculos[(*juego).tope_obstaculos].posicion = obtener_coordenada_valida(laberinto_auxiliar);
	laberinto_auxiliar[(*juego).obstaculos[(*juego).tope_obstaculos].posicion.fil][(*juego).obstaculos[(*juego).tope_obstaculos].posicion.col] = ACROMANTULA;
	inicializar_campos_de_obstaculo(ACROMANTULA, juego);

	(*juego).obstaculos[(*juego).tope_obstaculos].posicion = obtener_coordenada_valida(laberinto_auxiliar);;
	laberinto_auxiliar[(*juego).obstaculos[(*juego).tope_obstaculos].posicion.fil][(*juego).obstaculos[(*juego).tope_obstaculos].posicion.col] = BOGGART;
	inicializar_campos_de_obstaculo(BOGGART, juego);
}

void inicializar_campos_de_ayuda(char ayuda, juego_t* juego){
	switch(ayuda){
		case ESFINGE:
			(*juego).ayudas[(*juego).tope_ayudas].codigo = ESFINGE;
			(*juego).ayudas[(*juego).tope_ayudas].vida_a_recuperar = 0;
			(*juego).tope_ayudas++;		
		break;
		case IMPEDIMENTA:
			(*juego).ayudas[(*juego).tope_ayudas].codigo = IMPEDIMENTA;
			(*juego).ayudas[(*juego).tope_ayudas].vida_a_recuperar = 0;
			(*juego).tope_ayudas++;
		break;
		case RIDDIKULUS:
			(*juego).ayudas[(*juego).tope_ayudas].codigo = RIDDIKULUS;
			(*juego).ayudas[(*juego).tope_ayudas].vida_a_recuperar = 0;
			(*juego).tope_ayudas++;
		break;
		case POCION:
			(*juego).ayudas[(*juego).tope_ayudas].codigo = POCION;
			(*juego).ayudas[(*juego).tope_ayudas].vida_a_recuperar = VIDA_A_RECUPERAR_POCION;
			(*juego).tope_ayudas++;
		break;
	}
}
void inicializar_ayudas(juego_t *juego, char laberinto_auxiliar[TAMANIO][TAMANIO]){
	(*juego).tope_ayudas = 0;

	(*juego).ayudas[(*juego).tope_ayudas].posicion = obtener_coordenada_valida(laberinto_auxiliar);
	laberinto_auxiliar[(*juego).ayudas[(*juego).tope_ayudas].posicion.fil][(*juego).ayudas[(*juego).tope_ayudas].posicion.col] = IMPEDIMENTA;
	inicializar_campos_de_ayuda(IMPEDIMENTA, juego);

	(*juego).ayudas[(*juego).tope_ayudas].posicion = obtener_coordenada_valida(laberinto_auxiliar);
	laberinto_auxiliar[(*juego).ayudas[(*juego).tope_ayudas].posicion.fil][(*juego).ayudas[(*juego).tope_ayudas].posicion.col] = RIDDIKULUS;
	inicializar_campos_de_ayuda(RIDDIKULUS, juego);

	for(int pocion = 0; pocion < TOTAL_DE_POCIONES; pocion++){
		(*juego).ayudas[(*juego).tope_ayudas].posicion = obtener_coordenada_valida(laberinto_auxiliar);
		laberinto_auxiliar[(*juego).ayudas[(*juego).tope_ayudas].posicion.fil][(*juego).ayudas[(*juego).tope_ayudas].posicion.col] = POCION;
		inicializar_campos_de_ayuda(POCION, juego);
	}

	(*juego).ayudas[(*juego).tope_ayudas].posicion = obtener_coordenada_valida(laberinto_auxiliar);
	laberinto_auxiliar[(*juego).ayudas[(*juego).tope_ayudas].posicion.fil][(*juego).ayudas[(*juego).tope_ayudas].posicion.col] = ESFINGE;
	inicializar_campos_de_ayuda(ESFINGE, juego);
}

void inicializar_rival(juego_t* juego, char laberinto_auxiliar[TAMANIO][TAMANIO]){
	(*juego).rival.cantidad_pasos = 0;
	(*juego).rival.posicion = obtener_coordenada_valida_manhattan(laberinto_auxiliar, juego);
	laberinto_auxiliar[(*juego).rival.posicion.fil][(*juego).rival.posicion.col] = RIVAL;
	(*juego).rival.codigo = RIVAL;
	(*juego).rival.direccion = DERECHA;
}
void inicializar_jugador(juego_t* juego, char laberinto_auxiliar[TAMANIO][TAMANIO]){
	(*juego).jugador.tope_ayudas = 0;
	(*juego).jugador.posicion = obtener_coordenada_valida_manhattan(laberinto_auxiliar, juego);
	laberinto_auxiliar[(*juego).jugador.posicion.fil][(*juego).jugador.posicion.col] = JUGADOR;
	(*juego).jugador.codigo = JUGADOR;
	(*juego).jugador.vida = MAX_VIDA;
}

void inicializar_laberinto(juego_t* juego){
	srand((unsigned int) time(NULL));
	char laberinto_auxiliar[TAMANIO][TAMANIO];
	inicializar_paredes_laberinto((*juego).laberinto_original);
	cargar_laberinto_original(laberinto_auxiliar,(*juego).laberinto_original);

	inicializar_copa(juego, laberinto_auxiliar);
	incializar_obstaculos(juego, laberinto_auxiliar);
	inicializar_ayudas(juego, laberinto_auxiliar);
	inicializar_rival(juego, laberinto_auxiliar);
	inicializar_jugador(juego, laberinto_auxiliar);
}

/* 
Condiciones de uso BLOQUE DE MOVIMIENTO:


	cambiar_direccion_rival:
		Pre condiciones:
			-La direccion recibida debera ser alguna de las validas, es decir: {DERECHA, ABAJO, IZQUIERDA, ARRIBA}, de otra manera no se asegura el buen funcionamiento de la misma.
		Post condiciones:
			-Esta funcion recibira una direccion y devolvera una nueva de acuerdo al patron establecido en el contrato(PDF).
				-En caso de recibir la direccion DERECHA: devolvera ABAJO.
				-En caso de recibir la direccion ABAJO: devolvera IZQUIERDA.
				-En caso de recibir la direccion IZQUIERDA: devolvera ARRIBA.
				-En cualquier otro caso: devolvera DERECHA.

	es_movimiento_valido_rival:
		Pre condiciones:
			-La direccion recibida debera ser alguna de las validas, es decir: {DERECHA, ABAJO, IZQUIERDA, ARRIBA}, de otra manera no se asegura el buen funcionamiento de la misma.
		Post condiciones:
			-Esta funcion devolvera VERDADERO en caso de que la direccion recibida sea valida, es decir, que no haya una pared en dicha casilla.
			-Esta funcion devolvera FALSO en caso de que la direccion recibida sea invalida, es decir, que haya una pared en dicha casilla.

	mover_rival:
		Pre condiciones:
			-Para el correcto uso de la funcion, para el primer llamado: el campo 'cantidad_pasos' en la estructura 'juego.rival' debera haber sido previamente inicializada en 0
		Post condiciones:
			-El procedimiento movera al rival una casilla.
			-En caso de haber superado el periodo de pasos, cambiara la direccion del siguiente paso.
	mover_jugador:
		Pre condiciones:
			-La direccion recibida debera ser valida, es decir, no debe haber una pared en la direccion a moverse.
		Post condiciones:
			-Movera al jugador una casilla en la direccion recibida.
	es_movimiento_valido:
		Pre condiciones:
			-
		Post condiciones:
			-Devolvera VERDADERO en caso de que la direccion recibida sea valida, es decir, que no haya una PARED en dicha casilla.
			-Devolvera FALSO en cualquier otro caso, es decir:
				-Si la direccion recibida es invalida, es decir, no es ninguna de las siguientes:{DERECHA, ABAJO, IZQUIERDA, ARRIBA}
				-Si la casilla a moverse segun la direccion recibida hay una PARED.
*/

bool seguis_en_el_laberinto(coordenada_t posicion, char direccion){
	switch(direccion){
		case DERECHA:
			return(posicion.col < 14);
		break;
		case ABAJO:
			return(posicion.fil < 14);
		break;
		case IZQUIERDA:
			return(posicion.col > 0);
		break;
		case ARRIBA:
			return(posicion.fil > 0);
		break;
		default:
			return(false);
		break;
	}
}
char cambiar_direccion_rival(char direccion){
	switch(direccion){
		case DERECHA:
			return(ABAJO);
		break;
		case ABAJO:
			return(IZQUIERDA);
		break;
		case IZQUIERDA:
			return(ARRIBA);
		break;
		default:
			return(DERECHA);
		break;
	}
}
bool es_movimiento_valido_rival(juego_t* juego, char direccion){
	switch(direccion){
		case DERECHA:
			return((*juego).laberinto_original[(*juego).rival.posicion.fil][((*juego).rival.posicion.col)+1] != PARED && seguis_en_el_laberinto((*juego).rival.posicion, direccion));		
		break;
		case ABAJO:
			return((*juego).laberinto_original[((*juego).rival.posicion.fil)+1][((*juego).rival.posicion.col)] != PARED && seguis_en_el_laberinto((*juego).rival.posicion, direccion));
		break;
		case IZQUIERDA:
			return((*juego).laberinto_original[(*juego).rival.posicion.fil][((*juego).rival.posicion.col)-1] != PARED && seguis_en_el_laberinto((*juego).rival.posicion, direccion));
		break;
		default:
			return((*juego).laberinto_original[((*juego).rival.posicion.fil)-1][((*juego).rival.posicion.col)] != PARED && seguis_en_el_laberinto((*juego).rival.posicion, direccion));
		break;
	}
}
void mover_rival(juego_t* juego){

	if((*juego).rival.cantidad_pasos >= 4){
		(*juego).rival.direccion = cambiar_direccion_rival((*juego).rival.direccion);
		(*juego).rival.cantidad_pasos = 0;
	}
	while(!es_movimiento_valido_rival(juego, (*juego).rival.direccion)){
		if((*juego).rival.cantidad_pasos >= 4){
			(*juego).rival.direccion = cambiar_direccion_rival((*juego).rival.direccion);
			(*juego).rival.cantidad_pasos = 0;
		}else{
			(*juego).rival.cantidad_pasos++;
		}
	}
	
	switch((*juego).rival.direccion){
		case DERECHA:
			(*juego).rival.posicion.col ++;
			(*juego).rival.cantidad_pasos++;
		break;
		case ABAJO:
			(*juego).rival.posicion.fil ++;		
			(*juego).rival.cantidad_pasos++;
		break;
		case IZQUIERDA:
			(*juego).rival.posicion.col --;
			(*juego).rival.cantidad_pasos++;
		break;
		default:
			(*juego).rival.posicion.fil --;
			(*juego).rival.cantidad_pasos++;
		break;
	}
}
void mover_jugador(jugador_t* jugador, char direccion){
	switch(direccion){
		case DERECHA:
			(*jugador).posicion.col ++;
		break;
		case ABAJO:
			(*jugador).posicion.fil ++;		
		break;
		case IZQUIERDA:
			(*jugador).posicion.col --;
		break;
		default:
			(*jugador).posicion.fil --;
		break;
	}
}
bool es_movimiento_valido(juego_t* juego, char direccion){
	switch(direccion){
		case DERECHA:
			return((*juego).laberinto_original[(*juego).jugador.posicion.fil][((*juego).jugador.posicion.col)+1] != PARED && seguis_en_el_laberinto((*juego).jugador.posicion, direccion));
		break;
		case ABAJO:
			return((*juego).laberinto_original[((*juego).jugador.posicion.fil)+1][((*juego).jugador.posicion.col)] != PARED && seguis_en_el_laberinto((*juego).jugador.posicion, direccion));
		break;
		case IZQUIERDA:
			return((*juego).laberinto_original[(*juego).jugador.posicion.fil][((*juego).jugador.posicion.col)-1] != PARED && seguis_en_el_laberinto((*juego).jugador.posicion, direccion));
		break;
		case ARRIBA:
			return((*juego).laberinto_original[((*juego).jugador.posicion.fil)-1][((*juego).jugador.posicion.col)] != PARED && seguis_en_el_laberinto((*juego).jugador.posicion, direccion));
		break;
	}
	return false;
}



/*
Condiciones de uso BLOQUE DE ACTUALIZACION:

	aplicar_ayuda:
		Pre condiciones:
			-La posicion de la ayuda en el vector debera ser valida.
		Post condiciones:
			-Aplicara una ayuda, es decir:
				-Le asignara la correspondiente vida al jugador, asegurando que esta nunca supere el MAX_VIDA.
				-En caso de no ser una pocion la guardara en el 'inventario' del jugador

	eliminar_ayuda:
		Pre condiciones:
			-La posicion de la ayuda en el vector debera ser valida.
		Post condiciones:
			-Eliminara una ayuda del vector de ayudas de juego.
	posee_hechizo:
		Pre condiciones:
			-El hechizo recibido debe ser uno valido, es decir, debera ser alguno de: {RIDDIKULUS, IMPEDIMENTA}
		Post condiciones:
			-Devolvera VERDADERO si el jugador posee el hechizo buscado.
			-Devolvera FALSO en cualquier otro caso.
	aplicar_obstaculo:
		Pre condiciones:
			-La posicion del obstaculo en el vector debera ser valida.
		Post condiciones:
			-Aplicara un obstaculo en caso de que el jugador no posea el hechizo indicado, es decir:
				-Le restara la correspondiente vida al jugador.
			-En caso de tener el hechizo correspondiente anulara el ataque del enemigo.
		
	eliminar_obstaculo:
		Pre condiciones:
			-La posicion del obstaculo en el vector de obstaculos debera ser valida.
		Post condiciones:
			-Eliminara un obstaculo del vector de obstaculos del juego.
	hay_ayuda:
		Pre condiciones:

		Post condiciones:
			-Devolvera VERDADERO si encuentra una ayuda en la posicion donde esta parado el jugador.
			-Devolvera FALSO en otro caso.
			-Devolvera por parametro por referencia la posicion de la ayuda en el vector ayudas.
	hay_obstaculo:
		Pre condiciones:
			
		Post condiciones:
			-Devolvera VERDADERO si encuentra un obstaculo en la posicion donde esta parado el jugador.
			-Devolvera FALSO en otro caso.
			-Devolvera por parametro por referencia la posicion del obstaculo en el vector obstaculos.		
	actualizar_juego:
		Pre condiciones:

		Post condiciones:
			Actualizará el juego. Restará vida si el jugador está sobre un obstáculo 
				o lo eliminará si cuenta con el hechizo, aprenderá hechizos y todo lo 
			 	que pueda suceder luego de un turno.
*/
void aplicar_ayuda(juego_t* juego, int i){

	if((*juego).jugador.vida + (*juego).ayudas[i].vida_a_recuperar > MAX_VIDA){
		(*juego).jugador.vida = MAX_VIDA;
	}else{
		(*juego).jugador.vida += (*juego).ayudas[i].vida_a_recuperar;
	}
	if((*juego).ayudas[i].codigo != POCION){
		(*juego).jugador.ayudas[(*juego).jugador.tope_ayudas] = (*juego).ayudas[i];
		(*juego).jugador.tope_ayudas ++;
	}
}
void eliminar_ayuda(juego_t* juego, int i){
	(*juego).ayudas[i] = (*juego).ayudas[(*juego).tope_ayudas-1];
	(*juego).tope_ayudas --;	
}
bool posee_hechizo(juego_t* juego, char buscado){
	bool lo_posee = false;
	int j = 0;
	while(j < (*juego).jugador.tope_ayudas && !lo_posee){
		if((*juego).jugador.ayudas[j].codigo == buscado){
			lo_posee = true;
		}
		j++;
	}
	return (lo_posee);
}
void aplicar_obstaculo(juego_t* juego, int i){
	char codigo_obstaculo = (*juego).obstaculos[i].codigo;
	
	if(codigo_obstaculo == BOGGART && !posee_hechizo(juego, RIDDIKULUS)){
		(*juego).jugador.vida -= (*juego).obstaculos[i].danio;
	}else if(codigo_obstaculo == ESCREGUTO && !posee_hechizo(juego, IMPEDIMENTA)){
		(*juego).jugador.vida -= (*juego).obstaculos[i].danio;
	}else if(codigo_obstaculo == ACROMANTULA){
		(*juego).jugador.vida -= (*juego).obstaculos[i].danio;
	}
}
void eliminar_obstaculo(juego_t*juego, int i){
	(*juego).obstaculos[i] = (*juego).obstaculos[(*juego).tope_obstaculos-1];
	(*juego).tope_obstaculos --;
}
bool hay_ayuda(juego_t* juego, int* posicion_de_la_ayuda_en_el_vector){
	int i = 0;
	bool encontrado = false;

	while(i < (*juego).tope_ayudas && !encontrado){
		if((*juego).jugador.posicion.fil == (*juego).ayudas[i].posicion.fil && (*juego).jugador.posicion.col == (*juego).ayudas[i].posicion.col){
			encontrado = true;
			(*posicion_de_la_ayuda_en_el_vector) = i;
		}else{
			i++;
		}
	}

	return (encontrado);
}
bool hay_obstaculo(juego_t* juego,int* posicion_del_obstaculo_en_el_vector){
	int i = 0;
	bool encontrado = false;

	while(i < (*juego).tope_obstaculos && !encontrado){
		if((*juego).jugador.posicion.fil == (*juego).obstaculos[i].posicion.fil && (*juego).jugador.posicion.col == (*juego).obstaculos[i].posicion.col){
			encontrado = true;
			(*posicion_del_obstaculo_en_el_vector) = i;
		}else{
			i++;
		}
	}

	return (encontrado);
}
void actualizar_juego(juego_t* juego){
	int posicion_de_la_ayuda_en_el_vector;
	int posicion_del_obstaculo_en_el_vector;

	(*juego).jugador.vida -= DANIO_POR_TURNO;

	if((*juego).jugador.vida > 0 && hay_ayuda(juego, &posicion_de_la_ayuda_en_el_vector)){
		aplicar_ayuda(juego, posicion_de_la_ayuda_en_el_vector);
		eliminar_ayuda(juego, posicion_de_la_ayuda_en_el_vector);
	}else if((*juego).jugador.vida > 0 && hay_obstaculo(juego, &posicion_del_obstaculo_en_el_vector)){
		aplicar_obstaculo(juego, posicion_del_obstaculo_en_el_vector);
		eliminar_obstaculo(juego, posicion_del_obstaculo_en_el_vector);
	}
	if((*juego).jugador.vida < 0){
		(*juego).jugador.vida = 0;
	}
}
int estado_juego(juego_t juego){
	if((juego.jugador.posicion.fil == juego.copa.posicion.fil && juego.jugador.posicion.col == juego.copa.posicion.col) && juego.jugador.vida > 0){
		return GANO_JUGADOR;
	}else if((juego.rival.posicion.fil == juego.copa.posicion.fil && juego.rival.posicion.col == juego.copa.posicion.col) || juego.jugador.vida <= 0){
		return PERDIO_JUGADOR;
	}
	return SEGUIR_JUGANDO;
}




/*
Condciones de uso BLOQUE ACTUALIZACION DEL LABERINTO:
	cargar_en_laberinto:
		Pre condiciones:
			-La posicion recibida debera estar en la dimension TAMANIOxTAMANIO
		Post condiciones:
			-Cargara un codigo en el laberinto que se le muestra al usuario.
	cargar_ayudas:
		Pre condiciones:
			
		Post condiciones:
			-Cargara todas las ayudas disponibles en el laberinto que se le muestra al usuario.
	cargar_obstaculos:
		Pre condiciones:
			
		Post condiciones:
			-Cargara todas los obstaculos disponibles en el laberinto que se le muestra al usuario.
	posee_esfinge:
		Pre condiciones:

		Post condiciones:
			-Devolvera VERDADERO si el jugador posee la esfinge.
			-Devolvera FALSO en cualquier otro caso.
	cargar_copa:
		Pre condiciones:
			-La posicion de la copa debera pertenecer a la dimension TAMANIOxTAMANIO
		Post condiciones:
			-Cargara la copa en el laberinto que se muestra al Usuario en caso de que:
				-La vida del jugador sea menor que la minima vida para mostrar la copa
				-Posea las esfinge en su inventario.
	actualizar_laberinto:
		Pre condiciones:
		
		Post condiciones:
			Actualizará el laberinto mostrado al usuario, con los elementos presentes en el juego.
*/

void cargar_en_laberinto(char laberinto[TAMANIO][TAMANIO], coordenada_t posicion, char codigo){
	laberinto[posicion.fil][posicion.col] = codigo;
}
void cargar_ayudas(char laberinto[TAMANIO][TAMANIO], juego_t juego){
	for(int a = 0; a < juego.tope_ayudas; a++){
		cargar_en_laberinto(laberinto, juego.ayudas[a].posicion, juego.ayudas[a].codigo);
	}	
}
void cargar_obstaculos(char laberinto[TAMANIO][TAMANIO], juego_t juego){
	for(int m = 0; m < juego.tope_obstaculos; m++){
		cargar_en_laberinto(laberinto, juego.obstaculos[m].posicion, juego.obstaculos[m].codigo);
	}
}
bool posee_esfinge(jugador_t jugador){

	bool encontrada = false;
	int k = 0;
	while(k < jugador.tope_ayudas && !encontrada){

		if(jugador.ayudas[k].codigo == ESFINGE){
			encontrada = true;
		}
		k++;
	}
	return encontrada;
}
void cargar_copa(char laberinto[TAMANIO][TAMANIO], juego_t juego){
	if(((juego.jugador.vida) <= VIDA_MINIMA_PARA_MOSTRAR_COPA) || (posee_esfinge(juego.jugador))){
		cargar_en_laberinto(laberinto, juego.copa.posicion, juego.copa.codigo);
	}
}
void actualizar_laberinto(juego_t juego, char laberinto[TAMANIO][TAMANIO]){	

	cargar_laberinto_original(laberinto, juego.laberinto_original);

	cargar_copa(laberinto, juego);

	cargar_obstaculos(laberinto, juego);
	
	cargar_ayudas(laberinto, juego);

	cargar_en_laberinto(laberinto, juego.rival.posicion, juego.rival.codigo);

	cargar_en_laberinto(laberinto, juego.jugador.posicion, juego.jugador.codigo);
}


/* 
Condiciones de uso BLOQUE VISUAL
	asignar_color:
		Pre condiciones:

		Post condiciones:
			-Colorea el laberinto que se muestra por pantalla, asignando un color a cada objeto.

	mostrar_laberinto:
		Pre condiciones:

		Post condiciones:
			-Muestra al usuario el laberinto.

*/

void asignar_color(char objeto){
	switch(objeto){
		case COPA:
		case ESFINGE:
			printf("\033[1;33m");
		break;
		case ESCREGUTO:
		case ACROMANTULA:
		case BOGGART:
			printf("\033[1;31m");
		break;
		case RIDDIKULUS:
		case IMPEDIMENTA:
			printf("\033[1;36m");
		break;
		case POCION:
			printf("\033[1;34m");
		break;
		case JUGADOR:
		case RIVAL:
			printf("\033[1;37m");
		break;
		default:
			printf("\033[1;32m");
		break;

	}
}

void mostrar_laberinto(char laberinto[TAMANIO][TAMANIO]){
	system("clear");
	printf("\033[1;32m");	
	for(int i = 0; i < TAMANIO; i++){
		for(int j = 0; j < TAMANIO; j++){
			asignar_color(laberinto[i][j]);
			printf("%c ", laberinto[i][j]);
			}
		printf("\n");
	}
	printf("\033[0m");
}
