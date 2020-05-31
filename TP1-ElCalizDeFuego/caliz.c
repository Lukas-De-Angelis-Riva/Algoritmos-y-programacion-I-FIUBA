#include <stdio.h>
#include <stdbool.h>

//Declaraciones de las constantes del programa:

const int MINIMO_DE_EDAD = 17;
const int MINIMO_INTELIGENCIA = 0;
const int MAXIMO_INTELIGENCIA = 10;
const int MINIMO_FUERZA = 0;
const int MAXIMO_FUERZA = 10;
const char CAPACIDAD_MAGICA_BUENA = 'B';
const char CAPACIDAD_MAGICA_REGULAR = 'R';
const char CAPACIDAD_MAGICA_MALA = 'M';
const char PARAR_DE_INGRESAR = 'N';


//Las pre y post condiciones de cada funcion estan escritas justo encima de ellas, si no hay nada es porque considere que no eran necesarias
//para dicha funcion.


void presentacion_del_programa(){
	printf("\n \n Bienvenidx al sistema de seleccion de campeon del colegio. \n");
	printf("A continuacion debera ingresar los datos del aspirante a ser campeon, estos seran:");
	printf("\n Edad (Minimo de edad para aspirar al titulo: %i años)", MINIMO_DE_EDAD);
	printf("\n Inteligencia (Atributo que mide la inteligencia del %i al %i (ambos incluidos)) ", MINIMO_INTELIGENCIA, MAXIMO_INTELIGENCIA);
	printf("\n Fuerza (Atributo que mide la fuerza del %i al %i (ambos incluidos)) ", MINIMO_FUERZA, MAXIMO_FUERZA);	
	printf("\n Capacidad Magica (Atributo que mide tu capacidad magica, valuada en 3 rangos: ");
	printf("\n    '%c'  Domina magnificamente los conjuros y hechizos.\n    '%c': Tiene un manejo decente de la magia, pero nada del otro mundo.\n    '%c': Tiene problemas en el manejo fluido y preciso de los hechizos.", CAPACIDAD_MAGICA_BUENA, CAPACIDAD_MAGICA_REGULAR, CAPACIDAD_MAGICA_MALA);
}

/*
	PRE-CONDICIONES:
	-No ingresar caracteres fuera del codigo ASCII en particular la ñ/Ñ 
	-No ingresar cadenas de caracteres, solo un caracter.
	POST-CONDICIONES:
	-Se devolvera verdadero si su respuesta NO es "N".
	-Se devolvera falso si su respuesta es "N".
*/
bool obtener_si_seguir_ingresando(int contador_de_aspirantes){
	char respuesta;   

	if(contador_de_aspirantes == 1){
		//si es el primer aspirante que ingresas, te pregunta particularmente si queres ingresar al primer aspirante.
		printf("\n \n¿Desea ingresar al primer aspirante? '%c' para NO. Cualquier letra para SI: ", PARAR_DE_INGRESAR);
	}
	else{
		//si ya ingresaste 1 o mas usuarios, lo mismo pero el mensaje cambia ligeramente.
		printf("\n \n ¿Desea ingresar otro aspirante? '%c' para NO. Cualquier letra para SI : ", PARAR_DE_INGRESAR);
	}

	scanf(" %c", &respuesta);
	return(respuesta!= PARAR_DE_INGRESAR);
}

/*	
	PRE-CONDICIONES:
	-Las variables que recibe deben ser las letras 'M' y/o 'R' y/o 'B'.
	-Dichas letras deben estar en mayuscula. 
	-Dichas letras no pueden ser iguales (Antes contemplado dicha posibilidad).
	POST-CONDICIONES:
	-Se devolvera verdadero si la capacidad magica del ingresado es superior que la del campeon actual.
	-Se devolvera falso si la capacidad magica del ingresado es inferior que la del campeon actual.
*/
bool comparar_letras(char cap_mag_i,char cap_mag_c){ 
	//En esta funcion establezco un orden de magnitud en las capacidades magicas, independiente del orden de magnitud alfabetico.
	int valor_i;     //Numero para la capacidad magica del ingresado.
	int valor_c;     //Numero para la capacidad magica del campeon.

	if(cap_mag_i == CAPACIDAD_MAGICA_MALA)
		valor_i = 0;      
	else if(cap_mag_i == CAPACIDAD_MAGICA_REGULAR)
		valor_i = 1;
	else
		valor_i = 2;

	if(cap_mag_c == CAPACIDAD_MAGICA_MALA)
		valor_c = 0;
	else if(cap_mag_c == CAPACIDAD_MAGICA_REGULAR)
		valor_c = 1;
	else
		valor_c = 2;


	if (valor_i > valor_c) 
		return true;
	else 
		return false;
}

/*	
	PRE-CONDICIONES:
	-La inteligencia ingresada debe ser un numero entero.
	-La fuerza ingresada debe ser un numero entero.
	-La capacidad magica debe ser uno de los 3 caracteres designados en las constantes del programa
	POST-CONDICIONES: (Cuando me refiero a mayor y menor lo hago estrictamente)
	-Si la inteligencia del aspirante ingresado es mayor que la del campeon actual la funcion devolvera true, de lo contrario false.
	-Si la inteligencia del aspirante ingresado es igual que la del campeon actual:
		*Si la fuerza del aspirante ingresado es mayor que la del campeon actual la funcion devolvera true, de lo contrario false.
		*Si la fuerza del aspirante ingresado es igual que la del campeon actual:
			**Si la capacidad magica del ingresado es mejor que la del campeon actual se devolvera true, de lo contrario false.
			**Si la capacidad magica del ingresado es igual a la del campeon actual se devolvera false.
*/
bool aspirante_es_mejor_que_campeon(int inteligencia_i, int fuerza_i, char cap_mag_i, int inteligencia_c,int fuerza_c,char cap_mag_c){

	if((inteligencia_i == inteligencia_c) && (fuerza_i == fuerza_c) && (cap_mag_i == cap_mag_c)){ 
		return false;
	}

	if(inteligencia_i > inteligencia_c){
		return true;
	}

	if(inteligencia_i == inteligencia_c){
		if (fuerza_i > fuerza_c)
			return true;

		else if(fuerza_i == fuerza_c)
			return comparar_letras(cap_mag_i, cap_mag_c);

		else 
			return false;
	}
	else
		return false;
}

/*	
	PRE-CONDICIONES:
	-Ingresar un numero entero.
	-No ingresar caracteres ni cadenas de estos.
	-La edad no debe superar los 2.147.483.647 años :P
	POST-CONDICIONES:
	-Si tu edad es menor a 0 se considera un dato invalido y se te pedira que la ingreses nuevamente.
*/
void obtener_edad_valida(int *edad){

	printf("    Edad: ");
	scanf(" %i", edad);

	while((*edad) < 0){
		printf("Por favor, ingrese la edad nuevamente: ");
		scanf(" %i", edad);
	}
}

/*
	PRE-CONDICIONES:
	-La inteligencia debe ser un numero entero.
	-No ingresar caracteres ni cadenas de estos.
	POST-CONDICIONES:
	-Si tu inteligencia no pertenece al rango [MINIMO_INTELIGENCIA, MAXIMO_INTELIGENCIA] se considera un dato invalido y se te pedira ingresar nuevamente. 
*/
void obtener_inteligencia_valida(int *inteligencia){

	printf("\n    Inteligencia (valor entre %i y %i inclusive): ", MINIMO_INTELIGENCIA, MAXIMO_INTELIGENCIA); 
	scanf(" %i", inteligencia);

	while((*inteligencia) < MINIMO_INTELIGENCIA || (*inteligencia) > MAXIMO_INTELIGENCIA){
		printf("\n    Recuerde que el valor de la inteligecia esta medido entre %i y %i. Por favor, intente nuevamente: ",MINIMO_INTELIGENCIA, MAXIMO_INTELIGENCIA);
		scanf(" %i", inteligencia);
	}
}

/*
	PRE-CONDICIONES:
	-La fuerza debe ser un numero entero.
	-No ingresar caracteres ni cadenas de estos.
	POST-CONDICIONES:
	-Si tu fuerza no pertenece al rango [MINIMO_FUERZA, MAXIMO_FUERZA] se considera un dato invalido y se te pedira ingresar nuevamente. 
*/
void obtener_fuerza_valida(int *fuerza){

	printf("\n    Fuerza(valor entre %i y %i inclusive): ", MINIMO_FUERZA, MAXIMO_FUERZA);
	scanf(" %i", fuerza);

	while((*fuerza) < MINIMO_FUERZA || (*fuerza) >MAXIMO_FUERZA){ //ingresar fuerza.
		printf("\n    Recuerde que el valor de la fuerza esta medido entre %i y %i. Por favor, intente nuevamente: ",MINIMO_FUERZA, MAXIMO_FUERZA);
		scanf(" %i", fuerza);
	}
}

/*
	PRE-CONDICIONES:
	-No ingresar caracteres fuera del codigo ASCII en particular la ñ/Ñ 
	-No ingresar cadenas de caracteres, solo un caracter.
	POST-CONDICIONES:
	-Si tu capacidad magica no coincide con ninguna de las constantes de capacidad magica arriba definidas se considera un dato invalido y se te pedira ingresar nuevamente.
*/
void obtener_capacidad_magica_valida(char *cap_mag){

	printf("\n    Capacidad Magica ('%c' buena; '%c' regular; '%c' mala): ", CAPACIDAD_MAGICA_BUENA, CAPACIDAD_MAGICA_REGULAR, CAPACIDAD_MAGICA_MALA);
	scanf(" %c", cap_mag);

	while((*cap_mag) != CAPACIDAD_MAGICA_BUENA && (*cap_mag) != CAPACIDAD_MAGICA_REGULAR && (*cap_mag)!= CAPACIDAD_MAGICA_MALA){
		printf("\n    Recuerde que la Capacidad Magica es evaluada en ('%c' buena; '%c' regular; '%c' mala). Por favor, intente nuevamente: ", CAPACIDAD_MAGICA_BUENA, CAPACIDAD_MAGICA_REGULAR, CAPACIDAD_MAGICA_MALA);
		scanf(" %c", cap_mag);
	}
}

void ingresar_aspirantes(int *inteligencia_i, int *fuerza_i, char *cap_mag_i,int contador_de_aspirantes,int *edad_i){
	printf("\n \n Por favor, ingrese los datos del aspirante Nº %i: \n", contador_de_aspirantes);
	obtener_edad_valida(edad_i);
	if(*edad_i < 17){
		printf(" Usted no podra participar, el campeon debe tener al menos %i años", MINIMO_DE_EDAD);
		return;
	}
	obtener_inteligencia_valida(inteligencia_i);
	obtener_fuerza_valida(fuerza_i);
	obtener_capacidad_magica_valida(cap_mag_i);
}

/*
	PRE-CONDICIONES:
	-Los atributos del aspirante ingresado deben ser superiores a las del campeon actual.
	POST-CONDICIONES:
	-Se asignara al campeon actual, los atributos del aspirante que pasara a ser nuestro campeon de ahora en adelante.
*/
void actualizar_datos_del_campeon(int inteligencia_i, int fuerza_i, char cap_mag_i, int *inteligencia_c, int *fuerza_c, char *cap_mag_c, int *campeon_actual, int contador_de_aspirantes){
	(*inteligencia_c) = inteligencia_i;
	(*fuerza_c) = fuerza_i;
	(*cap_mag_c) = cap_mag_i;        
	(*campeon_actual) = contador_de_aspirantes;
}

void mostrar_campeon(int campeon_actual){

	if(campeon_actual == 0){ //Si campeon_actual es el numero 0, entonces significa que no hay campeon.
		printf("\n \nNo hay campeón :( \n"); 
	}
	else { //En el caso que campeon_actual no sea 0, significa que el usuario ingreso un aspirante valido, por lo tanto, hay campeon.
		printf("\nEl campeón es el número %i :)", campeon_actual);
	}
}



/*
	PRE-CONDICIONES:
	-Las inteligencias evaluadas entre [MINIMO_INTELIGENCIA,MAXIMO_INTELIGENCIA]
	-La fuerzas evaluadas entre [MINIMO_FUERZA,MAXIMO_FUERZA]
	-Capacidad magica evaluada en solo 3 valores posibles arriba designados.
	-Edades deben ser mayores a 0 y menores a 2.147.483.647
	-No ingresar caracteres fuera del codigo ASCII [[MUY IMPORTANTE]]
	-Cuando pida ingresar un numero entero no ingresar un caracter ni cadenas de estos (Salvo por los numericos)

	POST-CONDICIONES:
	-Una vez ingresados todos los aspirantes que usted desee, recibira un mensaje con el numero de aspirante que fue seleccionado campeon mediante las siguientes reglas:
		*Si no cumple con el mínimo de edad se lo descarta como opción.
		*El campeón será el que tenga más inteligencia.
		*Si tienen igual de inteligencia, el campeón será el que tenga más fuerza.
		*Si tanto inteligencia como fuerza son iguales, se pasa a comparar por la capacidad mágica. Teniendo ​ M ​ < ​ R ​ < ​ B ​ .
		*Si coinciden en todos los valores anteriores, quedará como campeón el que ya estaba actualmente.
	-Si ningun aspirante cumple con el minimo de edad o se decide no ingresar ningun aspirante:
		*recibira el mensaje: "No hay campeón :(".
*/
int main(){

	int campeon_actual = 0;
	int contador_de_aspirantes = 1;
	
	int edad_i; //Edad del aspirante ingresado.
				//Considere inneseario tener una edad de campeon actual ya que no la utilizo en ningun momento para nada.
	int inteligencia_c = -1; //Inteligencia del campeon actual.
	int inteligencia_i = -2; //Inteligencia del aspirante ingresado.
	int fuerza_c = -1;		 //Fuerza del campeon actual.
	int fuerza_i = -2;		 //Fuerza del aspirante ingresado.
	char cap_mag_c = 'M';	 //Capacidad magica del campeon actual.
	char cap_mag_i = 'M';	 //Capacidad magica del aspirante ingresado.

	presentacion_del_programa();

	while(obtener_si_seguir_ingresando(contador_de_aspirantes)){

		ingresar_aspirantes(&inteligencia_i,&fuerza_i,&cap_mag_i,contador_de_aspirantes,&edad_i);

		if(aspirante_es_mejor_que_campeon(inteligencia_i, fuerza_i, cap_mag_i, inteligencia_c, fuerza_c, cap_mag_c)){
			actualizar_datos_del_campeon(inteligencia_i, fuerza_i, cap_mag_i, &inteligencia_c, &fuerza_c, &cap_mag_c, &campeon_actual, contador_de_aspirantes);
		}

		contador_de_aspirantes++;
	}

	mostrar_campeon(campeon_actual);

	return 0;
}