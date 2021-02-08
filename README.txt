A) FUNCIONAMENTO DEL TRABAJO

El propósito de este trabajo es poder crear una simulador que trasladará pokemones que se encuentran en un arrecife (listados en un archivo de texto) hacia un acuario (que finalmente serán listados en otro archivo).
Los traslados serán realizados por pasadas, la cantidad a trasladar estará determinada dentro del trabajo y la caracteristica que deberán cumplir para serlo, también. Una vez terminada cada pasada, se mostrara por pantalla la cantidad de pokemones a retirar y la lista de los pokemones que siguen habitando el arrecife.
Finalmente, se mostrará la cantidad de pokemones que aún están en el arrecife y la cantidad de pokemones en el acuario. 


**Aclaraciones importantes**

~> Los archivos sobre los cuales trabajará, arrecife.txt y acuario.txt, serán recibios por linea de comando.

~> La cantidad a trasladar fue determinada por mi, no es un numero al azar.

~> Función trasladar_pokemon():
	--Si en el arrecife se encuentra una cantidad de pokemones menor a la pedida, no seran trasladados y devolvera ERROR. En caso de ser mayor o igual a ésta, se interará realizar el traslado.
	--Para buscar este número, recorré el vector de pokemones en el arrecife y guarda en una variable de tipo entero los contados.
	En caso de haber una cantidad mayor o igual a la pedida, recorrerá el vector por segunda vez para poder agregarlos al acuario y retirarlos del arrecife.
	--Si al momento de retirar el correspondiente pokemon del arrecife, falla la redimensión de la memoria, devolverá ERROR. De ser así, se verá duplicado (aparecerá tanto en el archivo arrecife.txt como en el de acuario.txt).
	--Si no ocurre ninguna de las anteriores, el traslado se pudo realizar correctamente y la función devolverá EXITO.

~> Función pokemon_retirado_arrecife (arrecife_t** arrecife,  int posicion):
	--Si la posición recibida por parámetro NO coincide con la última del vector de arrecife->pokemon, procederá a intercambiar de posiciòn al pokemon que se encuentra en ésta con el que se encuentra en la última.
	--Se intentará reducir en una unidad de pokemon_t la memoria reservada para arrecife->pokemon, eliminando asì al pokemon.
	--Si la reduccion falla, devolvera false, lo que luego provocará que la funcion trasladar_pokemon devuelva ERROR.
	--En cualquier otro caso, la funcion devolvera true, lo que significa que la eliminacion resultó exitosa.
 
 ~> Se incluira en el zip un archivo de pokemones de ejemplo.

B) COMPILACION
Para compilar el trabajo se utiliza el siguiente comando: "gcc *c -Wall -Wconversion -Werror -std=c99 -g -o evento_pesca"

*c: el compilador tomará todos los archivos .c de la carpeta en la que se encuentra y los compilará.
-Wall: habilitará todos los avisos.
-Wconversion: avisará si hubo algun tipo de conversion que puede alterar un valor/resultado.
-std=c99: especifica el estandar del lenguaje (en este caso c99)
-Werror: esta opcion convertirá a los avisos anteriores en errores.
-g:
-o: para asignarle el nombre al fichero de salida.
evento_pesca: el nombre del archivo ejecutable.

C) EJECUCION
Para ejecutar este programa se utiliza la siguiente linea de comando: " ./evento_pesca "nombre archivo arrecife" "nombre archivo acuario" "

./: refiere al directorio actual
./evento_pesca: carga y ejecuta el fichero ejecutable "evento_pesca"
"nombre archivo arrecife": arrecife.txt
"nombre archivo acuario": acuario.txt
(en este caso el programa recibe los nombres de los archivos por linea de comando)

D) CONCEPTOS

~>Punteros: un puntero es un tipo de variable que almacena una direccion de memoria.

~>Aritmetica de punteros: como para cualquier otro tipo de variable, existen distintas operaciones que se pueden realizar con estos.

	--Operador de direccion (&): devuelve la direccion de memoria de una variable.
	  Ejemplo:

	  int x = 8;
	  int *ptr_x;
	  ptr_x = &x;  <-- se le asginó a ptr_x la direccion de memoria de x

	  printf("%p\n", ptr_x); <-- imprime por pantalla la direccion de memoria en la cual se encuentra x

	--Operador de indireccion (*): devuelve el valor que tiene la direccion a la que apunta.
	  Ejemplo:

	  int x = 8;
	  int *ptr_x;
	  ptr_x = &x;

	  printf("&i\n", *ptr_x); <-- imprime por pantalla el valor de la variable x, o sea 8

	--La relacion entre punteros y vectores en C. Se sabe que el nombre de un vector es en sí mismo un puntero a la primera posicion del éste. Por esa razon surgen las siguiente equivalencia:

	  int vector[4] = {2,5,7,9} <-- designa 5 posiciones consecutivas de memoria para almacenar enteros
	  int ptr*; 	 <-- inicializa un puntero a un entero

	  ptr = &vector[0] ==> ptr = vector

	  Para acceder a las diferentes posiciones del vector usando el puntero:
	  ptr       -> apunta a la primer posicion del vector
	  (ptr + 1) -> apunta a la segunda posicion del vector
	  (ptr + 2) -> apunta a la tercera posicion del vector
	  (ptr + 3) -> apunta a la cuarta y ultima posicion del vector

	  *Tambien podemos movernos con los operadores de incremento (++) y decremento (--)*

	--Ejemplo de Otras operaciones:

	  int x = 8;
	  int y = 0;
	  int k = 0;
	  int *ptr_x;
	  ptr_x = &x;
	  y = *ptr_x + 2;
	  k = *ptr_x--;

	  printf("&i\n", y); <-- imprime por pantalla el valor de la variable y, o sea el valor de x (8) + 2 = 10
	  printf("&i\n", k); <-- imprime por pantalla el valor de la variable k, o sea el valor de x decrementado en una unidad = 7

	  int x = 8;
	  int *ptr_x;
	  ptr_x = &x;
	  *ptr_x = 8;        <- al valor que tiene el puntero se le asigna 0, o sea a x se le asigno 0

	  printf("&i\n", y); <-- imprime por pantalla el valor de la variable X, o sea 0


~>Punteros a funciones: en C, también podemos crear punteros a funciones, lo que nos da la posibilidad de poder recibirlas como parámetro o ser devueltas en otras función y de hacerlas un elemento de un vector. Este puntero guarda la direccion de memoria en la cual reside la función. Se declara de la siguiente forma:
	
	tipo de dato que devuelve la funcion (* nombre con el que identificaremos a la funcion) (parametros de la funcion)

	*importante* 
	 estos punteros apuntan a codigo.
	 no debemos reservar ni liberar memoria para este tipo.
	 lo siguiente es equivalente:

	 void (*ptr_funcion)(int) = funcion ==> void (*ptr_funcion)(int) = &funcion
	 ptr_funcion(10)                    ==> *ptr_funcion(10)


~>Malloc: reserva un bloque de memoria dinamica (en el heap) y devuelve un puntero de tipo void a la misma, el cual apunta al primer byte reservado. Se declara se la siguiente forma:
	
	void * malloc(size_t size) <-- size representa el numero de bytes a reservar, por ejemplo en la siguiente declaracion:

	int * puntero = malloc(sizeof(int)) <-- se reservaron 4 bytes en el heap

	En caso de no poder realizar la asignacion devolverá NULL.

~>Realloc: redimensiona el bloque de memoria dinámica reservado anteriormente para otro puntero. Se declara de la siguiente forma:

	void* realloc (void* puntero, size_t size);

	--Si el numero de bytes a reservar es mayor al anterior, se aumenta el espacio en memoria al que apunta el puntero.
	--Si es menor al anterior, se disminuye.
	--Si es cero y el puntero no es NULL, realloc actua como un free.
	--Si el numero no es cero y el puntero es NULL, realloc actua como malloc.
	--En caso que no pueda realizarlo, realloc devolvera NULL y el puntero enviado como parametro quedara intacto.
	--IMPORTANTE: es recomendable usar un puntero auixilar al momento de usar realloc, para asegurarnos de no perder memoria en el caso de que realloc tenga algun error.


E) ENUNCIADO:
La líder de gimnasio Misty organizó un evento de pesca que se llevará a cabo en su acuario, ubicado en Ciudad Celeste. Para ello necesitará muchos y muy variados pokémon de tipo agua. El lugar indicado en Kanto para obtener a todos estos pokémon es el arrecife que rodea a las Islas Espuma.
Para realizarlo, te pide que la ayudes a trasladar los pokémon seleccionados desde el arrecife a su acuario, donde será realizado el evento.
A Misty le preocupa perjudicar la población de las especies más vulnerables, es por ello que te pide realizar una simulación del arrecife, pudiendo ver como quedará su estado dependiendo de qué especies se elijan para el evento.