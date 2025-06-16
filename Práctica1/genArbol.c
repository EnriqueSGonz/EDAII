#include <stdlib.h>
#include <stdio.h>
#include "genArbol.h"
#include "pila.h"

Arbol genArbol(char *exPostfija)
{
  Pila p = NULL;
  Arbol a = NULL;
  int i = 0;
  char simbolo;
  tipoInfo info;
  simbolo = exPostfija[i];
  while (simbolo != '\0')
  {
    switch (esOperador(simbolo))
    {
    case 0:
      a = creaNodo(simbolo);
      pilaInserta(&p, a);
      break;
    case 1:
      a = creaNodo(simbolo);
      a->der = (Arbol)pilaSuprime(&p);
      a->izq = (Arbol)pilaSuprime(&p);
      pilaInserta(&p, a);
      break;
    default:
      printf("\n\n¡¡Expresión incorrecta !!\n\n");
      anula(a);
      while (!pilaVacia(&p))
        pilaSuprime(&p);
      return NULL;
    }
    i++;
    simbolo = exPostfija[i];
  }
  return pilaSuprime(&p);
}
int esOperador(char simbolo)
{
  if ((simbolo == '+') || (simbolo == '-') || (simbolo == '*') || (simbolo == '/'))
    return 1;
  else if ((simbolo >= 'A' && simbolo <= 'Z') ||
          (simbolo >= 'a' && simbolo <= 'z') ||
          (simbolo >= '0' && simbolo <= '9'))
    return 0;
  else
    return -1;
}

int evaluar(Arbol a)
{
  if (a == NULL)
  {
    return 0; // Caso base: árbol vacío
  }

  // Evaluar subárbol izquierdo y derecho
  int izquierda = evaluar(a->izq);
  int derecha = evaluar(a->der);

  // Si el nodo es una hoja (número), convertirlo y retornarlo
  if (!esOperador(a->info))
  {
    return a->info - '0'; // Convierte el carácter numérico a entero
  }

  // Realizar la operación correspondiente
  switch (a->info)
  {
  case '+':
    return izquierda + derecha;
  case '-':
    return izquierda - derecha;
  case '*':
    return izquierda * derecha;
  default:
    printf("Error: Operador desconocido %c\n", a->info);
    return 0;
  }
}

/*Arbol construccionArbolBin(char *exPrefija, char *exInfija)
{
  Pila p = NULL;
  Arbol a = NULL;
  int i = 0;
  int j = 0;
  char simbolo;
  tipoInfo info;
  simbolo = exPrefija[i];
  while (simbolo != '\0')
  {
    while (exPrefija[i] != exInfija[j])
    {
      j++;
    }
    if (i <= j)
    {
    }
  }
}*/
Arbol construccionArbolBinRec(char *preorden, char *inorden, int inicio, int fin, int *indicePre) {
  if (inicio > fin) {
    return NULL;
  }

  // Crear el nodo raíz con el elemento actual de preorden
  char raizInfo = preorden[*indicePre];
  (*indicePre)++;
  Arbol raiz = creaNodo(raizInfo);

  // Si el subarreglo tiene un solo elemento, es una hoja
  if (inicio == fin) {
    return raiz;
  }

  // Buscar la posición de la raíz en el inorden
  int i;
  for (i = inicio; i <= fin; i++) {
    if (inorden[i] == raizInfo) {
      break;
    }
  }

  // Construir subárbol izquierdo y derecho recursivamente
  raiz->izq = construccionArbolBinRec(preorden, inorden, inicio, i - 1, indicePre);
  raiz->der = construccionArbolBinRec(preorden, inorden, i + 1, fin, indicePre);

  return raiz;
}
Arbol construccionArbolBin(char *exPrefija, char *exInfija) {
  int n = 0;
  while (exInfija[n] != '\0') n++; // Calcular longitud
  int indicePre = 0;
  return construccionArbolBinRec(exPrefija, exInfija, 0, n - 1, &indicePre);
}