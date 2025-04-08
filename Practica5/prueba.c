#include <stdio.h>
#include <stdlib.h>

#ifdef MATRICES
#include "rMatrices/conjuntos.h"
#endif
#ifdef LISTAS
#include "rListas/conjuntos.h"
#endif
#ifdef ARBOLES
#include "rArboles/conjuntos.h"
#endif
#ifdef COMPRESION
#include "rCompresion/conjuntos.h"
#endif

int main()
{ particion P;
  int i;


	crea(P);
	printf("Situación INICIAL: ");
	verParticion(P);

	// Se forman las siguientes clases de equivalencia haciendo al primer elemento del conjunto su representatne:
	// {7,0,13,15},{2,3,8,12},{11,1,4,6,14},{9,5,10}

	if (unir(13,15,P) && unir(7,0,P) && unir(7,13,P))
		printf( "Formada clase de equivalencia {7,0,13,15}\n");
	else 
   		printf(" No puede formase la clase de equivalencia {7,0,13,15}\n");

	if (unir(8,12,P) && unir(3,8,P) && unir(2,buscar(3,P),P)) 
		printf( "Formada clase de equivalencia {2,3,8,12}\n");
	else 
		printf(" No puede formase la clase de equivalencia {2,3,8,12}\n");

	if (unir(6,1,P) && unir(6,4,P) && unir(11,14,P) && unir(11,6,P))
		printf( "Formada clase de equivalencia {11,1,4,6,14}\n");
	else 
		printf(" No puede formase la clase de equivalencia {11,1,4,6,14}\n");

	if (unir(5,10,P) && unir(9,5,P)) 
		printf( "Formada clase de equivalencia {5,9,10}\n");
	else 
		printf(" No puede formase la clase de equivalencia {5,9,10}\n");

	printf("Situación FINAL:   ");

	verParticion(P);

	printf("\n\nEl elemento 5 pertenence a la clase de equivalencia con representante %d\n",buscar(5,P));

  	// ATENCIÓN Ejemplo con parámetros incorrectos para relacionar el elemento 6 con el 15

	if (unir(6,15,P))
		printf( "Relacionado elemento 6 con 15 ...\n");
	else 
		printf(" No puede formase la clase de equivalencia ...\n");

	printf("\nLa partición no ha cambiado...¡¡¡ERROR!!!\n   ");
	verParticion(P);

	// Para asegurar que los parámetros son correctos mejor usar siempre  unir(buscar(x,P),buscar(y,P),P)

	unir(buscarCC(6,P),buscar(15,P),P);
	printf("\n\nAhora la partición ha cambiado: ¿Se han relacionado 6 y 15? ¿Cómo han quedado las clases de equivalencia?\n");
	verParticion(P);

	#ifdef LISTAS
	verClaseEquivalencia(5,P);
	#endif

	// ¿Qué operación sería necesaria para relacionar el elemento 12 con el 15?


}
