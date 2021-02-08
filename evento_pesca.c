#include <stdio.h>
#include <stdlib.h>
#include "evento_pesca.h"

#define FORMATO_LECTURA "%100[^;];%i;%i;%50[^\n]\n"
#define FORMATO_ESCRITURA "%s;%i;%i;%s\n"
#define LECTURA_EXITOSA 4

static const int ERROR = -1;
static const int EXITO = 0;

/*
 * Pre: recibe un pokemon con todos sus campos validos correspondiente al recientemente leido, un puntero a un pokemon con todos sus campos validos
 * y un entero correspondiente a la cantidad de pokemones del arrecife que ya han sido leidos.
 * Post: devuelve un puntero a un arrecife válido o NULL en caso de error.
 */
pokemon_t* agregar_pokemon(pokemon_t pokemon, pokemon_t* poke_puntero, int cantidad){

	pokemon_t* poke_puntero_nuevo = realloc(poke_puntero, sizeof(pokemon_t)*((size_t)cantidad)); 

	if(poke_puntero_nuevo == NULL){
		return poke_puntero;
	}

	poke_puntero = poke_puntero_nuevo;
	poke_puntero[cantidad-1] = pokemon;

	return poke_puntero;
}


/*
 * Pre: recibe un archivo y un puntero a un pokemon con todos sus campos validos.
 * Post: devolvera la cantidad leida exitosamente.
 */
int leer_archivo(FILE* archivo, pokemon_t* poke_aux){

	return fscanf(archivo, FORMATO_LECTURA, poke_aux->especie, &(poke_aux->velocidad), &(poke_aux->peso), poke_aux->color); 
}


/*
 * Pre: recibe una estrucutra arrecife_t por referencia y un entero correspondiente a la posicio del pokemon a eliminar. 
 * Post: devolvera true si pudo quitar el pokemon exitosamente o false en caso contrario.
 */
bool pokemon_retirado_arrecife(arrecife_t** arrecife,  int posicion){

	if(posicion != (*arrecife)->cantidad_pokemon-1){

		(*arrecife)->pokemon[posicion] = (*arrecife)->pokemon[(*arrecife)->cantidad_pokemon-1];
	}

	pokemon_t* poke_puntero_nuevo = realloc((*arrecife)->pokemon, sizeof(pokemon_t)*(size_t)(*arrecife)->cantidad_pokemon-1);

	if((poke_puntero_nuevo == NULL && (*arrecife)->cantidad_pokemon == 1) || poke_puntero_nuevo != NULL){

		(*arrecife)->pokemon = poke_puntero_nuevo;
		((*arrecife)->cantidad_pokemon)--;
		return true;

	}else{
		return false;
	}
}


/*
 * Pre: recibe un puntero a una estrucutra  de tipo arrecife_t con todos sus campos validos, un entero correspondiente a la cantidad de pokemones 
 * pedida para trasladar y el puntero a una funcion valida
 * Post: devolvera la cantidad de pokemones que cumplen con la caracteristica pedida.
 */
int contador_pokemones(arrecife_t* arrecife, int pedidos, bool(*seleccionar_pokemon) (pokemon_t*)){

	int i = 0;
	int contados = 0;

	while (i < arrecife->cantidad_pokemon && contados < pedidos){

		if(seleccionar_pokemon(arrecife->pokemon+i)){
			contados++;
		}
		i++;
	}

	return contados;
}


arrecife_t* crear_arrecife(const char* ruta_archivo){

	FILE* arch_arrecife = fopen(ruta_archivo, "r");
	if(!arch_arrecife){
		printf("ERROR AL ABRIR EL ARCHIVO\n");
		return NULL;
	}

	pokemon_t poke_aux;
	arrecife_t* mi_arrecife = malloc(sizeof(arrecife_t)); 

	if(mi_arrecife == NULL){
		return NULL;
	}
	
	mi_arrecife->pokemon = NULL;
	mi_arrecife->cantidad_pokemon = 0;

	int leidos = leer_archivo(arch_arrecife, &poke_aux); 

	if (leidos == LECTURA_EXITOSA){

		while (leidos == LECTURA_EXITOSA){

			mi_arrecife->pokemon = agregar_pokemon(poke_aux, mi_arrecife->pokemon, mi_arrecife->cantidad_pokemon + 1);
			leidos = leer_archivo(arch_arrecife, &poke_aux);
			mi_arrecife->cantidad_pokemon++;
		}

	}else{ //si no pudo leer ni siquiera un pokemon, debo liberar solamente la creacion de arrecife y devolver NULL

		liberar_arrecife(mi_arrecife);
		mi_arrecife = NULL;
	}

	fclose(arch_arrecife);
	return mi_arrecife;
}


acuario_t* crear_acuario(){

	acuario_t* mi_acuario = malloc(sizeof(acuario_t)); 

	if(mi_acuario == NULL){
		return mi_acuario; //o return NULL?
	}

	mi_acuario->cantidad_pokemon = 0;
	mi_acuario->pokemon = NULL;

	return mi_acuario;
}


int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion){

	int i = 0;
	int valor_retorno = EXITO;
	bool retirado = true;

	int cant_pasada = contador_pokemones(arrecife, cant_seleccion, seleccionar_pokemon);
		
	if(cant_pasada < cant_seleccion){
		return ERROR;
	} 

	cant_pasada = 0;

	while(cant_pasada < cant_seleccion && i < arrecife->cantidad_pokemon && retirado){

		if(seleccionar_pokemon(arrecife->pokemon+i)){
			
			acuario->pokemon = agregar_pokemon((arrecife->pokemon)[i], acuario->pokemon, acuario->cantidad_pokemon + 1); //<-- agrego el pokemon al acuario
			retirado = pokemon_retirado_arrecife(&arrecife, i); 
			(acuario->cantidad_pokemon)++; 
			cant_pasada++;

		}else{
			i++;
        }
	}

	if(!retirado){
		valor_retorno = ERROR;
	}

	return valor_retorno;
}


void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)){

	for (int i = 0; i < arrecife->cantidad_pokemon; i++){
		mostrar_pokemon(arrecife->pokemon+i);
	}
	printf("\n");
}


int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo){

	FILE* arch_acuario = fopen(nombre_archivo, "w");
	if(!arch_acuario){
		printf("ERROR AL ABRIR EL ARCHIVO\n");
		return ERROR;

	}

	for(int i = 0; i < acuario->cantidad_pokemon; i++){
		fprintf(arch_acuario, FORMATO_ESCRITURA, acuario->pokemon[i].especie, acuario->pokemon[i].velocidad, acuario->pokemon[i].peso, acuario->pokemon[i].color);
	}

	fclose(arch_acuario);
	return EXITO;
	
}


void liberar_arrecife(arrecife_t* arrecife){

	if (arrecife->pokemon != NULL){

		free(arrecife->pokemon);
	}

	free(arrecife);
}


void liberar_acuario(acuario_t* acuario){

	if (acuario->pokemon != NULL){

		free(acuario->pokemon);
	}

	free(acuario);
}