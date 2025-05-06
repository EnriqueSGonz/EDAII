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
#include "monticulo.h"
/**********************************************
/ Inicia correctamente directorio de vertices *
***********************************************/
#ifdef KRUSKAL
void crearMonticuloAristas(Monticulo *m, tipoGrafo *g)
{
  int i, numAristas = 0;
  pArco p;
  p = g->directorio[1].lista;
  while (p != NULL)
  {
    m->tamanno++;
    m->elemento[m->tamanno].clave = p->peso;
    m->elemento[m->tamanno].informacion.u = 1;
    m->elemento[m->tamanno].informacion.v = p->v;
    p = p->sig;
  }
  crearMonticulo(m);
}
void aceptarArista(tipoElementoM x, tipoGrafo *g)
{
  pArco arista;
  //(u,v)
  arista = (arco *)calloc(1, sizeof(arco));
  arista->v = x.informacion.v;
  arista->peso = x.clave;
  arista->sig = g->directorio[x.informacion.u].lista;
  g->directorio[x.informacion.u].lista = arista;
  //(v,u)
  arista = (arco *)calloc(1, sizeof(arco));
  arista->v = x.informacion.u;
  arista->peso = x.clave;
  arista->sig = g->directorio[x.informacion.v].lista;
  g->directorio[x.informacion.v].lista = arista;
}
tipoGrafo *kruskal(tipoGrafo *grafo)
{
  int i, n, numAristasAceptadas = 0;
  particion C;
  Monticulo m;
  tipoInfo arista;
  tipoGrafo *arbolExp;
  tipoConjunto u, v;
  tipoElementoM x;
  arbolExp = (tipoGrafo *)calloc(1, sizeof(tipoGrafo));
  arbolExp->orden = 7;
  iniciaMonticulo(&m);
  crea(C);
  crearMonticuloAristas(&m, g);

  while (numAristasAceptadas < g->orden - 1)
  {

    eliminarMinimo(&m, &x);
    u = buscar(x.informacion.u, C);
    v = buscar(x.informacion.v, C);
    if (u != v)
    {
      unirConjuntos(u, v, C);
      numAristasAceptadas++;
      aceptarArista(x, arbolExp);
    }
  }
  return arbolExp;
}
#else
void djikstra2(int vInicio, tipoGrafo *g)
{
  Monticulo m;
  tipoElementoM x;
  pArco p;
  int v, w;

  iniciar(g);
  g->directorio[1].distancia = 0;
  creaVacio(&m);

  x.clave = 0;
  x.informacion = 1;
  insertar(x, &m);

  while (!vacioMonticulo(m))
  {
    eliminarMinimo(&m, &x);
    v = x.informacion;

    if (!g->directorio[v].alcanzado)
    {
      g->directorio[v].alcanzado = 1;
      p = g->directorio[v].lista;

      while (p != NULL)
      {
        w = p->v;
        if (!g->directorio[w].alcanzado)
        {
          if (g->directorio[v].distancia + p->peso < g->directorio[w].distancia)
          {
            g->directorio[w].distancia = g->directorio[v].distancia + p->peso;
            g->directorio[w].anterior = v;
            x.clave = g->directorio[w].distancia;
            x.informacion = w;
            insertar(x, &m);
          }
        }
        p = p->sig;
      }
    }
  }
}
tipoGrafo *prim2(tipoGrafo *grafo)
{
  pArco p, ant, arista;
  int i, v, w;
  Monticulo m;
  tipoElementoM x;
  iniciar(grafo);
  iniciarMonticulo(&m);
  grafo->directorio[7].peso = 0;
  x.informacion = 7;
  x.clave = 0;
  insertar(x, &m);
  while (!vacioMonticulo(m))
  {
    eliminarMinimo(&m, &x);
    v = x.informacion;
    grafo->directorio[v].alcanzado = 1;
    p = grafo->directorio[v].lista;
    while (p != NULL)
    {
      w = p->v;
      if (!grafo->directorio[w].alcanzado)
      {
        if (grafo->directorio[w].peso > p->peso)
        {
          grafo->directorio[w].peso = p->peso;
          grafo->directorio[w].anterior = v;
          insertar(x, &m);
        }
      }
      p = p->sig;
    }
  }
  tipoGrafo *arbolExp;
  arbolExp = (tipoGrafo *)calloc(1, sizeof(tipoGrafo));
  arbolExp->orden = grafo->orden;

  for (i = 1; i <= grafo->orden; i++)
  {
    w = grafo->directorio[i].anterior;
    if (w != 0)
    {
      arista = (arco *)calloc(1, sizeof(arco));
      arista->v = i;
      arista->peso = grafo->directorio[i].peso;
      arista->sig = arbolExp->directorio[w].lista;
      arbolExp->directorio[w].lista = arista;

      arista = (arco *)calloc(1, sizeof(arco));
      arista->v = w;
      arista->peso = grafo->directorio[i].peso;
      arista->sig = arbolExp->directorio[i].lista;
      arbolExp->directorio[i].lista = arista;
    }
  }
  return arbolExp;
}
#endif
void iniciar(tipoGrafo *g)
{
  /*for(int i=0;i<g->orden;i++){
    g->directorio[i].alcanzado=NULL;
  }*/
  int i;
  pArco lsta;

  for (i = 1; i <= g->orden; i++)
  {

    g->directorio[i].alcanzado = 0;
    g->directorio[i].gradoEntrada = 0;
    g->directorio[i].ordenTop = 0;
    g->directorio[i].distancia = INF;
    g->directorio[i].peso = INF;
    g->directorio[i].anterior = 0;
  }

  for (i = 1; i <= g->orden; i++)
  {

    lsta = g->directorio[i].lista;

    while (lsta != NULL)
    {

      g->directorio[lsta->v].gradoEntrada++;
      lsta = lsta->sig;
    }
  }
}
void profundidadMejorado(int v_inicio, tipoGrafo *g)
{
  for (int i = 1; i <= g->orden; i++)
  {
    // g->directorio->alcanzado=;
  }
}
void amplitudMejorado(int v_inicio, tipoGrafo *g)
{
}
/* Ejercicio 2*/

int ordenTop1(tipoGrafo *g)
{
  int i;
  pArco p;
  int v, w;

  for (i = 1; i <= g->orden; i++)
  {
    v = buscarVerticeGradoCeroNoOrdenTop(g);

    if (v == -1)
    {
      printf("Error: grafo con ciclo\n");
      return;
    }

    g->directorio[v].ordenTop = i;
    p = g->directorio[v].lista;

    while (p != NULL)
    {
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
  for (v = 1; v <= g->orden; v++)
  {
    if (g->directorio[v].gradoEntrada == 0)
    {
      inserta(v, &c);
    }
  }
  int orden = 1;
  while (!vacia(&c))
  {
    v = suprime(&c);
    g->directorio[v].ordenTop = orden;
    orden++;
    pArco p = g->directorio[v].lista;
    while (p != NULL)
    {
      w = p->v;
      g->directorio[w].gradoEntrada--;
      if (g->directorio[w].gradoEntrada == 0)
      {
        inserta(w, &c);
      }
      p = p->sig;
    }
  }
}
/******************************************************************************/
/* Recorrido en PROFUNDIDAD de un grafo. ¡CUIDADO! Depende del vertice inicial y del tipo de grafo */
/*********************************************************************************/
void profundidad(int v_inicio, tipoGrafo *grafo)
{
  int w;
  pArco p;
  printf("%d ", v_inicio);
  grafo->directorio[v_inicio].alcanzado = 1;
  p = grafo->directorio[v_inicio].lista;
  while (p != NULL)
  {
    w = p->v;
    if (!grafo->directorio[w].alcanzado)
      profundidad(w, grafo);
    p = p->sig;
  }
}
/************************************************************************************************/
/* Recorrido en AMPLITUD de un grafo. ¡CUIDADO! Depende del vertice inicial y del tipo de grafo */
/************************************************************************************************/
void amplitud(int v_inicio, tipoGrafo *grafo)
{
  int w;
  pArco p;
  Cola c;

  colaCreaVacia(&c);
  colaInserta(&c, v_inicio);
  while (!colaVacia(&c))
  {
    w = colaSuprime(&c);
    if (!grafo->directorio[w].alcanzado)
    {
      printf("%d ", w);
      grafo->directorio[w].alcanzado = 1;
      p = grafo->directorio[w].lista;
      while (p != NULL)
      {
        w = p->v;
        colaInserta(&c, w);
        p = p->sig;
      }
    }
  }
}
/**********************************************************************************************/
/* Función auxiliar para ver el contenido de la estructura que representa un grafo en memoria */
/**********************************************************************************************/
void verGrafo(tipoGrafo *g)
{
  int i;
  pArco p;

  printf("\nGrafo  (Orden %d)\n\n", g->orden);
  printf("       alc gEnt oTop dist peso ant \n");
  printf("     +----+----+----+----+----+----+\n");

  for (i = 1; i <= g->orden; i++)
  {
    printf("  %2d | %2d | %2d | %2d |", i, g->directorio[i].alcanzado,
           g->directorio[i].gradoEntrada, g->directorio[i].ordenTop);
    if (g->directorio[i].distancia == INF)
      printf("  * |");
    else
      printf(" %2d |", g->directorio[i].distancia);
    if (g->directorio[i].peso == INF)
      printf("  * |");
    else
      printf(" %2d |", g->directorio[i].peso);
    printf(" %2d |", g->directorio[i].anterior);
    p = g->directorio[i].lista;
    while (p != NULL)
    {
      printf(" ->%2d", p->v); // Grafos no ponderados
      // printf(" ->%2d, %2d", p->v, p->peso); // Grafos ponderados
      p = p->sig;
    }
    printf("\n");
  }
  printf("     +----+----+----+----+----+----+\n\n");
}

int buscarVerticeGradoCeroNoOrdenTop(tipoGrafo *g)
{
  for (int i = 1; i <= g->orden; i++)
  {
    if (g->directorio[i].gradoEntrada == 0 && g->directorio[i].ordenTop == 0)
    {
      return i; // Vértice encontrado
    }
  }
  return -1; // No hay vértice con grado 0 y sin orden topológico
}

void caminos1(int vInicio, tipoGrafo *g)
{
  pArco p;
  int v, w;
  int distancia = 0;
  iniciar(g);
  g->directorio[vInicio].distancia = 0;
  for (distancia = 0; distancia < g->orden; distancia++)
  {
    for (v = 1; v <= g->orden; v++)
    {
      if ((!g->directorio[v].alcanzado) && g->directorio[v].distancia == distancia)
      {
        g->directorio[v].alcanzado = 1;
        p = g->directorio[v].lista;
        while (p != NULL)
        {
          w = p->v;
          if (g->directorio[w].distancia == INF)
          {
            g->directorio[w].distancia = g->directorio[v].distancia + 1;
            g->directorio[w].anterior = v;
          }
          p = p->sig;
        }
      }
    }
  }
}

void caminos2(int vInicio, tipoGrafo *g)
{
  int v, w;
  pArco p;

    return -1; // No hay vértice con grado 0 y sin orden topológico
}

void caminos2(int vInicio, tipoGrafo *g){
  int v,w;
  pArco  p;

  Cola c;

  iniciar(g);

  colaCreaVacia(&c);

  g->directorio[vInicio].distancia = 0;
  colaInserta(&c, vInicio);

  while (!colaVacia(&c))
  {
    v = colaSuprime(&c);
    p = g->directorio[v].lista;
    while (p != NULL)
    {
      w = p->v;
      if (g->directorio[w].distancia == INF)
      {
        g->directorio[w].distancia = g->directorio[v].distancia + 1;
        g->directorio[w].anterior = v;
        colaInserta(&c, w);
      }
      p = p->sig;
    }
  }
}
void dijkstra1(int vInicio, tipoGrafo *g)
{
  int v, w, minDist, current;
  pArco p;

  iniciar(g);
  g->directorio[vInicio].distancia = 0;

  for (int i = 1; i <= g->orden; i++)
  {
    minDist = INF;
    current = -1;

    // Find the vertex with the smallest distance that hasn't been reached
    for (v = 1; v <= g->orden; v++)
    {
      if (!g->directorio[v].alcanzado && g->directorio[v].distancia < minDist)
      {
        minDist = g->directorio[v].distancia;
        current = v;
      }
    }

    if (current == -1)
    {
      break; // All reachable vertices have been processed
    }

    g->directorio[current].alcanzado = 1;

    // Update distances for adjacent vertices
    p = g->directorio[current].lista;
    while (p != NULL)
    {
      w = p->v;
      if (!g->directorio[w].alcanzado && g->directorio[current].distancia + p->peso < g->directorio[w].distancia)
      {
        g->directorio[w].distancia = g->directorio[current].distancia + p->peso;
        g->directorio[w].anterior = current;
      }
      p = p->sig;
    }
  }
}
/*void dijkstra2(int vInicio, tipoGrafo *g) {
  int v, w;
  pArco p;
  Cola c;

  iniciar(g);
  g->directorio[vInicio].distancia = 0;

  colaCreaVacia(&c);
  colaInserta(&c, vInicio);

  while (!colaVacia(&c)) {
    v = colaSuprime(&c);
    if (!g->directorio[v].alcanzado) {
      g->directorio[v].alcanzado = 1;
      p = g->directorio[v].lista;

      while (p != NULL) {
        w = p->v;
        if (g->directorio[v].distancia + p->peso < g->directorio[w].distancia) {
          g->directorio[w].distancia = g->directorio[v].distancia + p->peso;
          g->directorio[w].anterior = v;
          colaInserta(&c, w);
        }
        p = p->sig;
      }
    }
  }
}*/

int costeyTrayectoria(int vIni, int vFin, tipoGrafo *g)
{
  Pila vP;
  int anterior = vFin;

  pilaCreaVacia(&vP);
  while (anterior != vIni)
  {
    pilaInserta(&vP, anterior);
    anterior = g->directorio[anterior].anterior;
  }
  while (!pilaVacia(&vP))
  {
    printf("v%d ", pilaSuprime(&vP));
  }

  return g->directorio[vFin].distancia;
}

void todosCaminosMin(int vIni, tipoGrafo *g)
{
  int i;
  pArco p;
  Pila vP;
  int anterior = vIni;

  pilaCreaVacia(&vP);
  while (anterior != 0)
  {
    pilaInserta(&vP, anterior);
    anterior = g->directorio[anterior].anterior;
  }
  while (!pilaVacia(&vP))
  {
    printf("v%d ", pilaSuprime(&vP));
  }

  for (i = 1; i <= g->orden; i++)
  {
    p = g->directorio[i].lista;
    while (p != NULL)
    {
      printf(" -> %d", p->v);
      p = p->sig;
    }
  }
}
/*tipoGrafo *prim1(tipoGrafo *grafo) {
  g->directorio[1].distancia=0;
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
}*/

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
