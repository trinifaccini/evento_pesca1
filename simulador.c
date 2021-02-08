#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evento_pesca.h"

#define MAX_ARCHIVO 100
#define MAX_SELECCION 6

const char AFIRMATIVO = 'S';

#define FIN				"\033[0m"
#define ROJO 			"\033[1m\033[31m"
#define VERDE 			"\033[1m\033[32m"
#define AMARILLO		"\033[1m\033[33m"
#define MAGENTA 		"\033[1m\033[35m"
#define AZUL_F          "\x1b[44m"
#define RESET_COLOR     "\x1b[0m"

bool desnutrido (pokemon_t* pokemon);

bool sobrepeso (pokemon_t* pokemon);

bool colores_piola (pokemon_t* pokemon);

bool schumacher (pokemon_t* pokemon);

bool mejores_especies(pokemon_t* pokemon);

bool tortuga(pokemon_t * pokemon);

void mostrar_poke_tabla(pokemon_t* pokemon);

void mostrar_poke_tarjeta(pokemon_t* pokemon);

void mostrar_poke_papiro(pokemon_t* pokemon);

void mostrar_poke_compu(pokemon_t* pokemon);

void mostrar_poke_escalera(pokemon_t* pokemon);

//POST: devolvera true si el caracter recibido como parámetro es una S
bool es_respuesta_valida(char respuesta){

	return (respuesta == AFIRMATIVO);
}


int main (int argc, char *argv[]){

	char respuesta; 

	arrecife_t* arrecife_oficial = crear_arrecife(argv[1]);
	acuario_t* acuario_oficial = crear_acuario();

	int seleccion[MAX_SELECCION] = {7,6,9,8,2,5};

	bool (*seleccionar_pokemon[])(pokemon_t*) = {schumacher, mejores_especies, colores_piola, desnutrido, sobrepeso, tortuga};
	
	void (*mostrar_pokemon[])(pokemon_t*) = {mostrar_poke_tabla, mostrar_poke_papiro, mostrar_poke_tarjeta, mostrar_poke_compu, mostrar_poke_escalera, mostrar_poke_tabla};

	printf("----------CANTIDAD INICIAL: %i----------\n\n", arrecife_oficial->cantidad_pokemon);
	
	for (int i = 0; i < MAX_SELECCION; i++){
		trasladar_pokemon(arrecife_oficial, acuario_oficial, seleccionar_pokemon[i], seleccion[i]);
		printf("Pasada numero: %i. Pokemones a quitar: %i.\n", i+1, seleccion[i]);
		printf("-------POKEMONES EN EL ARRECIFE--------\n");
		censar_arrecife(arrecife_oficial, mostrar_pokemon[i]);
		printf("----------CANTIDAD ACTUAL: %i----------\n\n\n", arrecife_oficial->cantidad_pokemon);
		printf("Ingrese S para continuar\n");
		scanf(" %c", &respuesta);
		while (!es_respuesta_valida(respuesta)){
			printf("Por favor, ingrese S para continuar\n ");
			scanf(" %c", &respuesta);
		}
		
	}

	guardar_datos_acuario(acuario_oficial, argv[2]);

	printf("------CANTIDAD FINAL ARRECIFE: %i------\n", arrecife_oficial->cantidad_pokemon);
	printf("------CANTIDAD FINAL ACUARIO: %i-------\n", acuario_oficial->cantidad_pokemon);

	liberar_arrecife(arrecife_oficial);
	liberar_acuario(acuario_oficial);

	return 0;
}
	
/*
 * Pre: recibe un puntero a un pokemon con todos sus campos validos
 * Post: devuelve true si el pokemon recibido pesa menos de 50 kg
 */
bool desnutrido (pokemon_t* pokemon){
	return(pokemon->peso <= 50);
}

/*
 * Pre: recibe un puntero a un pokemon con todos sus campos validos
 * Post: devuelve true si el pokemon recibido pesa mas de 300 kg
 */
bool sobrepeso (pokemon_t* pokemon){
	return(pokemon->peso > 300);
}

/*
 * Pre: recibe un puntero a un pokemon con todos sus campos validos
 * Post: devuelve true si el pokemon recibido pesa es de color rojo, verde o morado
 */
bool colores_piola (pokemon_t* pokemon){
	return(strcmp(pokemon->color, "rojo") == 0 || strcmp(pokemon->color, "verde") == 0 || strcmp(pokemon->color, "morado") == 0 );
}

/*
 * Pre: recibe un puntero a un pokemon con todos sus campos validos
 * Post: devuelve true si el pokemon puede correr a una velocidad mayor a 60 km/h
 */
bool schumacher (pokemon_t* pokemon){
	return(pokemon->velocidad > 60);
}

/*
 * Pre: recibe un puntero a un pokemon con todos sus campos validos
 * Post: devuelve true si su especie comienza con la letra T o F
 */
bool mejores_especies(pokemon_t* pokemon){
	return (pokemon->especie[0] == 'T' || pokemon->especie[0] == 'F');
}

/*
 * Pre: recibe un puntero a un pokemon con todos sus campos validos
 * Post: devuelve true si el pokemon no puede correr a una velocidad mayor a 40 km/h
 */
bool tortuga(pokemon_t* pokemon){
	return(pokemon->velocidad < 40);
}

/*
 * Pre: recibe un puntero a un pokemon con todos sus campos validos
 * Post: muestra por pantalla los datos del pokemon en forma de tabla
 */
void mostrar_poke_tabla(pokemon_t* pokemon){

	printf(ROJO "|%12s|%5i|%5i|%12s|\n" FIN,pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color);
}

/*
 * Pre: recibe un puntero a un pokemon con todos sus campos validos
 * Post: muestra por pantalla los datos del pokemon en forma de tarjeta
 */
void mostrar_poke_tarjeta(pokemon_t* pokemon){

	printf(VERDE "║ Especie: %11s ║\n" FIN, pokemon->especie);
	printf(VERDE "║ Velocidad: %9i ║\n" FIN, pokemon->velocidad);
	printf(VERDE "║ Peso: %14i ║\n" FIN, pokemon->peso);
	printf(VERDE "║ Color: %13s ║\n" FIN, pokemon->color);
	printf("\n");
}
	
/*
 * Pre: recibe un puntero a un pokemon con todos sus campos validos
 * Post: muestra por pantalla los datos del pokemon en forma de papiro
 */	
void mostrar_poke_papiro(pokemon_t* pokemon){

	printf(AMARILLO"    _____________________________________________________ \n" FIN);
	printf(AMARILLO"  / \\                                                   \\\n" FIN);
	printf(AMARILLO" |   |     ESPECIE        COLOR    VELOCIDAD         PESO|\n" FIN);
	printf(AMARILLO "     |%12s %12i %12i %12s|\n" FIN,pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color);
	printf(AMARILLO"     |    _______________________________________________|___\n" FIN);
	printf(AMARILLO"     |   /                                                  /.\n" FIN);
	printf(AMARILLO"      \\_/__________________________________________________/.\n" FIN);
	printf("\n" );
	printf("\n");

}

/*
 * Pre: recibe un puntero a un pokemon con todos sus campos validos
 * Post: muestra por pantalla los datos del pokemon dentro de la pantalla de una computadora
 */
void mostrar_poke_compu(pokemon_t* pokemon){

	printf(AZUL_F" ._________________________________________________________."  RESET_COLOR "\n" );
	printf(AZUL_F"| .___________________________________________________. |==|" RESET_COLOR "\n" );
	printf(AZUL_F"| |                                                   | |  |" RESET_COLOR "\n" );
	printf(AZUL_F"| |     ESPECIE        COLOR    VELOCIDAD         PESO| |  |" RESET_COLOR "\n" );
	printf(AZUL_F"| |%12s %12i %12i %12s| |  |" RESET_COLOR "\n" ,pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color);
	printf(AZUL_F"| |                                                   | | ,|" RESET_COLOR "\n" );
	printf(AZUL_F"| !___________________________________________________! |(c|" RESET_COLOR "\n" );
	printf(AZUL_F"!_______________________________________________________!__!" RESET_COLOR "\n" );
	printf(AZUL_F"|           ___ --=                     ___ --=         | ,|" RESET_COLOR "\n" );
	printf(AZUL_F"|  ---------[_]----------    -----------[_]-----------  |(c|" RESET_COLOR "\n" );
	printf(AZUL_F"!_______________________________________________________!__!" RESET_COLOR "\n" );
	printf("\n" );
	printf("\n" );

}

/*
 * Pre: recibe un puntero a un pokemon con todos sus campos validos
 * Post: muestra por pantalla los datos del pokemon en forma de escalera
 */
void mostrar_poke_escalera(pokemon_t* pokemon){


	printf(" __| |___________________________________________________| |__\n");
	printf("(__   ___________________________________________________   __)\n");
	printf("   | |                                                   | |\n");
	printf("   | |     ESPECIE        COLOR    VELOCIDAD         PESO| |  \n"FIN);
	printf("   | |%12s %12i %12i %12s| |  |\n" FIN,pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color);
	printf(" __| |___________________________________________________| |__\n");
	printf("(__   ___________________________________________________   __)\n");
	printf("   | |                                                   | |\n");
}
