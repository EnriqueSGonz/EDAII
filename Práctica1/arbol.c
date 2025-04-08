#include <stdlib.h>
#include <stdio.h>
#include "arbol.h"
#include "cola.h"

//
// Reserva de memoria para un nuevo nodo de árbol binario
//
Arbol creaNodo(tipoInfo info)
{
  tipoNodo *nuevo;

  //   nuevo =(tipoNodo *)calloc(1, sizeof(tipoNodo));
  if ((nuevo = (tipoNodo *)malloc(sizeof(tipoNodo))) == NULL)
    return NULL;
  else
  {
    nuevo->info = info;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
  }
}

//
// Recorrido en amplitud o por niveles: necesita una cola de punteros a nodos de árbol binario!!!
//

void amplitud(Arbol raiz)
{
  Cola c;
  tipoNodo *nodo;
  colaCreaVacia(&c);
  nodo = raiz;
  if (raiz != NULL)
    colaInserta(&c, nodo);
  while (!colaVacia(&c))
  {
    nodo = (Arbol)colaSuprime(&c);
    printf(" %c ", nodo->info);
    if (nodo->izq != NULL)
      colaInserta(&c, nodo->izq);
    if (nodo->der != NULL)
      colaInserta(&c, nodo->der);
  }
}
//
// Recorridos en profundidad "recursivos"
//
void preOrden(Arbol raiz)
{
  if (raiz != NULL)
  {
    printf("%c ", raiz->info);
    preOrden(raiz->izq);
    preOrden(raiz->der);
  }
}
void enOrden(Arbol raiz)
{
  if (raiz != NULL)
  {
    enOrden(raiz->izq);
    printf("%c ", raiz->info);
    enOrden(raiz->der);
  }
}
void postOrden(Arbol raiz)
{
  if (raiz != NULL)
  {
    postOrden(raiz->izq);
    postOrden(raiz->der);
    printf("%c ", raiz->info);
  }
}

int altura(Arbol raiz)
{
  if (raiz == NULL)
    return -1;
  int izq = altura(raiz->izq);
  int der = altura(raiz->der);
  return 1 + (izq > der ? izq : der);
}

// 📌 Devuelve el número total de nodos en el árbol
int numNodos(Arbol raiz)
{
  if (raiz == NULL)
    return 0;
  return 1 + numNodos(raiz->izq) + numNodos(raiz->der);
}

// 📌 Elimina todos los nodos del árbol
Arbol anula(Arbol raiz)
{
  if (raiz != NULL)
  {
    anula(raiz->izq);
    anula(raiz->der);
    free(raiz);
  }
  return NULL;
}

// 📌 Sustituye todas las apariciones de `x` por `y` en el árbol
int sustituye(Arbol raiz, char x, char y)
{
  if (raiz == NULL)
    return 0;
  int cambios = 0;
  if (raiz->info == x)
  {
    raiz->info = y;
    cambios++;
  }
  cambios += sustituye(raiz->izq, x, y);
  cambios += sustituye(raiz->der, x, y);
  return cambios;
}

// 📌 Devuelve el número de nodos hoja
int numNodosHoja(Arbol raiz)
{
  if (raiz == NULL)
    return 0;
  if (raiz->izq == NULL && raiz->der == NULL)
    return 1;
  return numNodosHoja(raiz->izq) + numNodosHoja(raiz->der);
}

// 📌 Devuelve el número de nodos internos (con al menos un hijo)
int numNodosInternos(Arbol raiz)
{
  if (raiz == NULL || (raiz->izq == NULL && raiz->der == NULL))
    return 0;
  return 1 + numNodosInternos(raiz->izq) + numNodosInternos(raiz->der);
}

// 📌 Devuelve el número de nodos con un solo hijo
int numHijoUnico(Arbol raiz)
{
  if (raiz == NULL)
    return 0;
  int unico = ((raiz->izq == NULL) != (raiz->der == NULL)) ? 1 : 0;
  return unico + numHijoUnico(raiz->izq) + numHijoUnico(raiz->der);
}

// 📌 Devuelve el nodo con el valor máximo en el árbol
Arbol buscarMax(Arbol raiz)
{
  if (raiz == NULL)
    return NULL;
  while (raiz->der != NULL)
  {
    raiz = raiz->der;
  }
  return raiz;
}

// 📌 Devuelve el nodo con el valor mínimo en el árbol
Arbol buscarMin(Arbol raiz)
{
  if (raiz == NULL)
    return NULL;
  while (raiz->izq != NULL)
  {
    raiz = raiz->izq;
  }
  return raiz;
}

// 📌 Determina si dos árboles son similares (misma estructura)
int similares(Arbol r1, Arbol r2)
{
  if (r1 == NULL && r2 == NULL)
    return 1;
  if (r1 == NULL || r2 == NULL)
    return 0;
  return similares(r1->izq, r2->izq) && similares(r1->der, r2->der);
}

// 📌 Determina si dos árboles son equivalentes (misma estructura y contenido)
int equivalentes(Arbol r1, Arbol r2)
{
  if (r1 == NULL && r2 == NULL)
    return 1;
  if (r1 == NULL || r2 == NULL)
    return 0;
  return (r1->info == r2->info) &&
         equivalentes(r1->izq, r2->izq) &&
         equivalentes(r1->der, r2->der);
}

// 📌 Devuelve el árbol espejo de otro árbol (invertido)
Arbol especular(Arbol raiz)
{
  if (raiz == NULL)
    return NULL;
  Arbol nuevo = creaNodo(raiz->info);
  nuevo->izq = especular(raiz->der);
  nuevo->der = especular(raiz->izq);
  return nuevo;
}
