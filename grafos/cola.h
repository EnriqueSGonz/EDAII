#include "arbol.h"
#ifndef __COLA_H
#define __COLA_H

#ifndef __TIPO_ELEMENTO
#define __TIPO_ELEMENTO
typedef Arbol tipoElemento;
#endif

#ifndef __TIPO_CELDA
#define __TIPO_CELDA
typedef struct tipoCelda {
	tipoElemento elemento;
	struct tipoCelda * sig;
	} tipoCelda;
#endif


typedef struct {
        tipoCelda *frente, *fondo;
} Cola;

int colaCreaVacia(Cola *c);

// En vacía no sería necesario el paso por referencia,
// se hace por mantener la misma interfaz con la implementación
// de matrices
int colaVacia(Cola *c);

int colaInserta(Cola *c, tipoElemento elemento);

tipoElemento colaSuprime(Cola *c);

#endif
/*#ifndef __LINKED_LIST_QUEUE_H__
#define __LINKED_LIST_QUEUE_H__

//Queue element
typedef int queueElement;

//Queue structure with linked list implementation
typedef struct queueNode {
	queueElement element;
	struct queueNode * next;
} QueueNode;


typedef struct {
        QueueNode *front, *rear;
} LLQueue;


//Stack methods
int createEmptyQueue(LLQueue *queue);
int isEmpty(LLQueue *queue);

int queueAdd(queueElement newElement, LLQueue *queue);
int queueRemove(LLQueue *queue, queueElement *element);

void printQueue(LLQueue *queue);

#endif*/