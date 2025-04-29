#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "pila.h"



int pilaCreaVacia(Pila *p)
{   if(p==NULL){
    return -1;
}
    *p=NULL;
    return 0;
}

int pilaVacia(Pila *p)
{
   return (*p==NULL);
}

int pilaInserta(Pila *p,tipoElemento elemento)
{
    tipoCelda *nuevaCelda ;

    if(p==NULL){
        return -1;
    }else if(NULL==(nuevaCelda=(tipoCelda *)malloc(sizeof(tipoCelda)))){
        return -2;
    }else{
        nuevaCelda->elemento = elemento;  // Asignamos el elemento
    nuevaCelda->sig = *p;  // El nuevo nodo apunta al nodo anterior
    *p = nuevaCelda;  // La pila ahora apunta al nuevo nodo
    return 0; 
    }
}

tipoElemento pilaSuprime(Pila *p)
{   tipoElemento elemento;
    tipoCelda *aBorrar;

    if(p==NULL){
        return NULL;
    }else if(*p==NULL){
        return NULL;
    }
    else{
        elemento=(*p)->elemento;
        aBorrar=*p;
        (*p)=(*p)->sig;
        free(aBorrar);
    }
    return elemento;
}