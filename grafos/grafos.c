/*
 * grafos.c
 *
 *  Created on: 21/04/2014
 *      Author: MJ Polo
 */
#include <stdio.h>
#include <stdlib.h>
#include "cola.h"
#include "pila.h"
#include "grafos.h"
/**********************************************
/ Inicia correctamente directorio de vertices *
***********************************************/
void iniciar(tipoGrafo *g)
{
  /*for(int i=0;i<g->orden;i++){
    g->directorio[i].alcanzado=NULL;
  }*/
  int i;
	pArco lsta;

	for(i=1; i<=g->orden; i++){

	g->directorio[i].alcanzado=0;
	g->directorio[i].gradoEntrada=0;
	g->directorio[i].ordenTop=0;
	g->directorio[i].distancia=INF;
	g->directorio[i].peso=INF;
	g->directorio[i].anterior=0;

	}
	
	for(i=1; i<=g->orden; i++){

	lsta=g->directorio[i].lista;
	
	while(lsta!=NULL){

	g->directorio[lsta->v].gradoEntrada++;
	lsta=lsta->sig;
	}
	}	
}
void profundidadMejorado(int v_inicio,tipoGrafo *g)
{
  for(int i=1;i<=g->orden;i++){
    //g->directorio->alcanzado=;
  }
}
void amplitudMejorado(int v_inicio,tipoGrafo *g)
{
}
/* Ejercicio 2*/

int ordenTop1(tipoGrafo *g)
{
    int i;
    pArco p;
    int v, w;

    for (i = 1; i <= g->orden; i++) {
        v = buscarVerticeGradoCeroNoOrdenTop(g);

        if (v == -1) {
            printf("Error: grafo con ciclo\n");
            return;
        }

        g->directorio[v].ordenTop = i;
        p = g->directorio[v].lista;

        while (p != NULL) {
            w = p->v;
            g->directorio[w].gradoEntrada--;
            p = p->sig;
        }
    }

}
int ordenTop2(tipoGrafo *g)
{
  int v, w;
    Cola c;
    creaVacia(&c);

    for (v = 1; v <= g->orden; v++) {
        if (g->directorio[v].gradoEntrada == 0) {
            inserta(v, &c);
        }
    }

    int orden = 1;
    while (!vacia(&c)) {
        v = suprime(&c);
        g->directorio[v].ordenTop = orden;
        orden++;
        pArco p = g->directorio[v].lista;
        while (p != NULL) {
            w = p->v;
            g->directorio[w].gradoEntrada--;

            if (g->directorio[w].gradoEntrada == 0) {
                inserta(w, &c);
            }
            p = p->sig;
        }
    }
}
/******************************************************************************/
/* Recorrido en PROFUNDIDAD de un grafo. ¡CUIDADO! Depende del vertice inicial y del tipo de grafo */
/*********************************************************************************/
void profundidad(int v_inicio,tipoGrafo * grafo)
{ int w;
  pArco  p;
  printf("%d ",v_inicio);
  grafo->directorio[v_inicio].alcanzado=1;
  p = grafo->directorio[v_inicio].lista;
  while (p!=NULL)
  { w=p->v;
    if (!grafo->directorio[w].alcanzado)
        profundidad(w,grafo);
    p = p->sig;
  }
}
/************************************************************************************************/
/* Recorrido en AMPLITUD de un grafo. ¡CUIDADO! Depende del vertice inicial y del tipo de grafo */
/************************************************************************************************/
void amplitud(int v_inicio,tipoGrafo *grafo)
{ int w;
  pArco  p;
  Cola c;

  colaCreaVacia(&c);
  colaInserta(&c,v_inicio);
  while (!colaVacia(&c))  {
	w =colaSuprime(&c);
        if (!grafo->directorio[w].alcanzado) {
		printf("%d ",w);
	        grafo->directorio[w].alcanzado=1;
        	p =grafo->directorio[w].lista;
 		while (p!=NULL){
			w = p->v;
			colaInserta(&c,w);
			p = p->sig;
		}
	}
  }
}
/**********************************************************************************************/
/* Función auxiliar para ver el contenido de la estructura que representa un grafo en memoria */
/**********************************************************************************************/
void verGrafo(tipoGrafo *g)
{  int i;
   pArco p;

   printf("\nGrafo  (Orden %d)\n\n",g->orden);
   printf("       alc gEnt oTop dist peso ant \n");
   printf("     +----+----+----+----+----+----+\n");

   for(i=1;i<=g->orden;i++)
   {  printf("  %2d | %2d | %2d | %2d |", i, g->directorio[i].alcanzado,
                       g->directorio[i].gradoEntrada, g->directorio[i].ordenTop);
       if (g->directorio[i].distancia == INF) printf("  * |");
       else   printf(" %2d |", g->directorio[i].distancia);
       if (g->directorio[i].peso == INF) printf("  * |");
       else   printf(" %2d |", g->directorio[i].peso);
       printf(" %2d |",g->directorio[i].anterior);
       p = g->directorio[i].lista;
       while (p != NULL)
       {   printf(" ->%2d", p->v);	// Grafos no ponderados
           //printf(" ->%2d, %2d", p->v, p->peso); // Grafos ponderados
           p = p->sig;
       }
       printf("\n");
   }
   printf("     +----+----+----+----+----+----+\n\n");
}


int buscarVerticeGradoCeroNoOrdenTop(tipoGrafo *g) {
    for (int i = 1; i <= g->orden; i++) {
        if (g->directorio[i].gradoEntrada == 0 && g->directorio[i].ordenTop == 0) {
            return i; // Vértice encontrado
        }
    }
    return -1; // No hay vértice con grado 0 y sin orden topológico
}

void caminos2(int vInicio, tipoGrafo *g){
  int v,w;
  pArco  p;
  Cola c;

  iniciar(g);

  colaCreaVacia(&c);
  g->directorio[vInicio].distancia=0;
  colaInserta(&c,vInicio);

  while (!colaVacia(&c))  {
    v=colaSuprime(&c);
    p= g->directorio[v].lista;
    while(p!=NULL){
      w=p->v;
      if(g->directorio[w].distancia == INF){
        g->directorio[w].distancia=g->directorio[v].distancia+1;
        g->directorio[w].anterior=v;
        colaInserta(&c,w);
      }
      p=p->sig;
    }
  }
}

int costeyTrayectoria(int vIni, int vFin, tipoGrafo *g){
  Pila vP;
  int anterior=vFin;

  pilaCreaVacia(&vP);
  while(anterior!=vIni){
    pilaInserta(&vP,anterior);
    anterior=g->directorio[anterior].anterior;
  }
  while(!pilaVacia(&vP)){
    printf("v%d ",pilaSuprime(&vP));
  }
  
  return g->directorio[vFin].distancia;  
}