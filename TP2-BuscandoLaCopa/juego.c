#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "copa.h"

#define ESCREGUTO 'E'
#define ACROMANTULA 'A'
#define BOGGART 'B'
#define POCION 'P'
#define IMPEDIMENTA 'I'
#define RIDDIKULUS 'R'
#define ESFINGE 'F'
#define MAX_NOMBRE 25

const int TURNO_JUGADOR = 0;
const int TURNO_RIVAL = 1;

const char NOMBRE_RIVAL[MAX_NOMBRE] = "HARRY POTTER";

/*
Condiciones de uso:
	mensaje_de_bienvenida:
		Pre condiciones:
		Post condiciones:
			Informara al usuario que significan cada unos de los caracteres que aparecen en el laberinto.
	obtener_nombre_jugador:
		Pre condiciones:
			El nombre ingresado no debe superar las 25 letras.
		Post condiciones:

	mensaje_final:
		Pre condiciones:
			El nombre del jugador no debe superar las 25 letras.
		Post condiciones:
			Mostrara al usuario un mensaje final antes de terminar el juego informandole si gano el o el rival o perdio por falta de vida.
	mostrar_inventario:
		Pre condiciones:

		Post condiciones:
			Mostrara los hechizos y objetos que posea el jugador en su inventario
	mostrar_vida:
		Pre condiciones:
			
		Post condiciones:
			Mostrara la vida que posee el jugador en ese momento, junto a una barra de vida.
	mostrar_juego:
		Pre condiciones:

		Post condiciones:
			Mostrara al usuario el HUD y el laberinto en ese momento.
	obtener_movimiento_valido:
		Pre condiciones:
			
		Post condiciones:
			Lee la tecla que ingresa el usuario por teclado y la devuelve en caso de que sea valida, en otro caso la pedira nuevamente.

*/
void mensaje_de_bienvenida(){
	system("clear");
	printf(" Bienvenido al laberinto del Torneo de los tres magos\n");
	printf(" Tu objetivo y el de tu rival sera conseguir la copa, esta estara oculta en alguna parte del laberinto.\n");
	printf(" Repartidos por el laberinto habra ayudas, estas seran: \n");
	printf("	Pociones < %c >: Recuperaran vida.\n", POCION);
	printf("	Riddikulus < %c >: Es un encantamiento que se utiliza para defenderse contra un Boggart.\n", RIDDIKULUS);
	printf("	Impedimenta < %c >: Es un embrujo que impide el movimiento hacia adelante. Servira para defenderse contra un Escreguto.\n", IMPEDIMENTA);
	printf("	Esfinge < %c >: La esfinge es una criatura magica natal de Egipto. Te dira donde se encuentra la copa.\n", ESFINGE);
	printf("\n Repartidos por el laberinto tambien habra obstaculos, estos seran:\n");
	printf("\n 	Boggart < %c >:Es un no-ser amortal de forma cambiante. Quita 15 de vida.",BOGGART);
	printf("\n 	Escreguto < %c >: Parecidos a escorpiones gigantes usan sus explosiones para acercarse al enemigo. Quita 20 de vida.", ESCREGUTO);
	printf("\n 	Acromantula < %c >:Es una monstruosa y gigante arania. Quita 10 de vida.", ACROMANTULA);
}
void obtener_nombre_jugador(char nombre_jugador[MAX_NOMBRE]){
	printf("\n\n Por favor ingresa tu nombre: ");
	scanf("%[^\n]", nombre_jugador);
}
void mensaje_final(juego_t juego, char nombre_jugador[MAX_NOMBRE]){
	int resultado = estado_juego(juego);

	if(resultado == GANO_JUGADOR){
		printf("\n\n\n¡TENEMOS UN NUEVO CAMPEON, FELICITACIONES %s, HAS ENCONTRADO LA COPA!\n\n", nombre_jugador);
	}
	else if(resultado == PERDIO_JUGADOR && juego.jugador.vida > 0){
		printf("\n\n\n¡TENEMOS UN NUEVO CAMPEON, %s ENCONTRO LA COPA!\n\n", NOMBRE_RIVAL);
	}else{
		printf("\n\n\n -Ha vuelto, ha vuelto, ¡Voldemort ha vuelto! %s me pidio que trajera su cuerpo! ¡¡No podia abandonarlo, no ahi!!\n", nombre_jugador);
		printf(" -Tranquilo Harry... ya paso, esta aqui ¿¿Nos oyes??\n");
		printf(" -¡¡QUE PERMANEZCAN EN SUS ASIENTOS!! ... El chico esta muerto... \n\n	Fin del juego. Has muerto\n\n");
	}
}
void mostrar_inventario(jugador_t jugador){
	printf("\n INVENTARIO: [");
	for(int i = 0; i < jugador.tope_ayudas; i++){
		printf("%c ", jugador.ayudas[i].codigo);
	}
	printf("]\n");
}
void mostrar_vida(jugador_t jugador){
	printf("\n VIDA: ");
	printf("[");
	printf("\033[1;31m");
	for(int i = 0; i < jugador.vida; i += 10){

		printf("♥");
	}
	printf("\033[0m"); 
	printf("] %i\n", jugador.vida);
}
void mostrar_juego(jugador_t jugador, char laberinto[TAMANIO][TAMANIO]){
	mostrar_laberinto(laberinto);
	mostrar_vida(jugador);
	mostrar_inventario(jugador);	
}	
char obtener_movimiento_valido(juego_t* juego, char laberinto[TAMANIO][TAMANIO]){
	char tecla;
	printf("\nIngrese su proximo movimiento: ");
	scanf(" %c", &tecla);
	while(!es_movimiento_valido(juego, tecla)){
		mostrar_juego((*juego).jugador, laberinto);
		printf("\n Por favor, ingrese nuevamente la direccion: ");
		scanf(" %c", &tecla);
	}
	return(tecla);
}

/*
                                         _ __
        ___                             | '  \
   ___  \ /  ___         ,'\_           | .-. \        /|
   \ /  | |,'__ \  ,'\_  |   \          | | | |      ,' |_   /|
 _ | |  | |\/  \ \ |   \ | |\_|    _    | |_| |   _ '-. .-',' |_   _
// | |  | |____| | | |\_|| |__    //    |     | ,'_`. | | '-. .-',' `. ,'\_
\\_| |_,' .-, _  | | |   | |\ \  //    .| |\_/ | / \ || |   | | / |\  \|   \
 `-. .-'| |/ / | | | |   | | \ \//     |  |    | | | || |   | | | |_\ || |\_|
   | |  | || \_| | | |   /_\  \ /      | |`    | | | || |   | | | .---'| |
   | |  | |\___,_\ /_\ _      //       | |     | \_/ || |   | | | |  /\| |
   /_\  | |           //_____//       .||`      `._,' | |   | | \ `-' /| |
        /_\           `------'        \ |              `.\  | |  `._,' /_\
                                       \|                    `.\
											
			Y el caliz de fuego
*/

int main(){

	juego_t juego;
	char laberinto[TAMANIO][TAMANIO];
	char direccion_de_movimiento;
	int turno = TURNO_JUGADOR;
	char nombre_jugador[MAX_NOMBRE];
	mensaje_de_bienvenida();
	obtener_nombre_jugador(nombre_jugador);
	inicializar_laberinto(&juego);
	actualizar_laberinto(juego, laberinto);
	mostrar_juego(juego.jugador, laberinto);
	while(estado_juego(juego) == 0){
		if(turno == TURNO_JUGADOR){
			direccion_de_movimiento = obtener_movimiento_valido(&juego, laberinto);	
			mover_jugador(&juego.jugador,direccion_de_movimiento);
			turno = TURNO_RIVAL;
			actualizar_juego(&juego);
		}else if(turno == TURNO_RIVAL){
			mover_rival(&juego);
			turno = TURNO_JUGADOR;
		}
		actualizar_laberinto(juego, laberinto);
		mostrar_juego(juego.jugador, laberinto);
	}
	mensaje_final(juego, nombre_jugador);
	
	return 0;
}


