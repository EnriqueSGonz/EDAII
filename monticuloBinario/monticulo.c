#include "monticulo.h"
#include <stdio.h>
void iniciaMonticulo(Monticulo *m){
    m->tamanno=0;
}
int vacioMonticulo(Monticulo m){
    if(m.tamanno==0) return 1;
    else return 0;
}
int insertar(tipoElemento x, Monticulo *m){
    if(m->tamanno >= MAXIMO -1) return -1;
    else{
        m->tamanno++;
        m->elemento[m->tamanno]=x;
        filtradoAscendente(m,m->tamanno);
        return 0;
    }
}

int decrementarClave(int pos, tipoClave cantidad, Monticulo *m){
    if((cantidad<0) || (pos<1) || (pos>m->tamanno)) return -1;
    else{
    m->elemento[pos].clave=m->elemento[pos].clave-cantidad;
    filtradoAscendente(m,pos);
    return 0;
    }
}

void filtradoAscendente(Monticulo *m, int i){
    tipoElemento temp;
    while( i!=1 && m->elemento[i].clave < m->elemento[i/2].clave ){
        temp=m->elemento[i];
        m->elemento[i]=m->elemento[i/2];
        m->elemento[i/2]=temp;
        i=i/2;
    }
}

void filtradoDescendente(Monticulo *m, int i){
    //hueco=i=pos;

    int hueco = i;
    int finFiltrado = 0;

    while ((2 * hueco <= m->tamanno) && !finFiltrado) {
        int hijo = 2 * hueco;

        if (hijo != m->tamanno) {
            if (m->elemento[hijo + 1].clave < m->elemento[hijo].clave) {
                hijo = hijo + 1;
            }
        }

        if (m->elemento[hijo].clave < m->elemento[hueco].clave) {
            m->elemento[hueco] = m->elemento[hijo];
            hueco = hijo;
        } else {
            finFiltrado = 1;
        }
    }
}

int eliminarMinimo(Monticulo *m, tipoElemento *minimo){
    if(m->tamanno == 0) return -1;
    else{
        *minimo=m->elemento[1];
        m->elemento[1]=m->elemento[m->tamanno];
        m->tamanno--;
        filtradoDescendente(m,1);
        return 0;
    }
}
void heapsort1(int *vector, int n){
    Monticulo m;
    tipoElemento elemento;
    int i;

    iniciaMonticulo(&m);
    m.tamanno = 0;

    for (i = 0; i < n; i++) {
        elemento.clave = vector[i];
        elemento.informacion = 0;
        insertar(elemento, &m);
    }

    for (i = n - 1; i >= 0; i--) {
        eliminarMinimo(&m, &elemento);
        vector[i] = elemento.clave;
    }
}

void heapsort(Monticulo *m){
    tipoElemento elemento;
    int i;

    for (i = m->tamanno; i >= 1; i--) {
        elemento = m->elemento[i];
        m->elemento[i] = m->elemento[1];
        m->elemento[1] = elemento;
        m->tamanno--;
        filtradoDescendente(m, 1);
    }
}

void verMonticulo(Monticulo *m){
    int i;
    for (i=1;i<=m->tamanno;i++)
    printf("%d ",m->elemento[i].clave);
    printf("\n");
}
