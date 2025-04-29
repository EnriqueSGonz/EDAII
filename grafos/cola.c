#include <stdio.h>
#include <stdlib.h>
//#include <errno.h>
#include "cola.h"



int colaCreaVacia(Cola *c)
{
    if(c == NULL) return -1;
	
	c->frente = c->fondo = NULL;
	return 0;
}

int colaVacia(Cola *c)
{
    if((c->frente==NULL)&&(c->fondo==NULL)) return -1;
    else return 0;
}

int colaInserta(Cola *c,tipoElemento elemento)
{
    tipoCelda *nuevoNodo = (tipoCelda *)malloc(sizeof(tipoCelda));  // Crear un nuevo nodo
    if (nuevoNodo == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo nodo.\n");
        return -1;
    }
    nuevoNodo->elemento = elemento;  // Asignar el valor al nuevo nodo   
    nuevoNodo->sig=NULL; // El nuevo nodo apunta a NULL, ya que es el último
    if (colaVacia(c)) {
        c->frente = c->fondo=nuevoNodo;  // Si la cola está vacía, el frente apunta al nuevo nodo
    } else {
        c->fondo->sig = nuevoNodo;
        c->fondo = nuevoNodo;  // El nodo actual en el fondo apunta al nuevo nodo
    }
    return 0;
}

tipoElemento colaSuprime(Cola *c)
{   tipoElemento elemento;
tipoCelda *aBorrar;
    if (!colaVacia(c)) {
        aBorrar=c->frente;
        elemento= aBorrar->elemento;
        c->frente=c->frente->sig;
        if(c->frente==NULL) c->fondo=NULL;
        free(aBorrar);
    }
    return elemento;
}
