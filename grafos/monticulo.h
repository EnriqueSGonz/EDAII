#define MAX 100

typedef int tipoClave ;
#ifdef KRUSKAL
typedef struct
{ int u;
  int v;
} tipoInfo;
#else
typedef int tipoInfo ;
#endif
typedef struct
{ tipoClave clave;
   tipoInfo  informacion;
} tipoElementoM;

typedef struct
{ tipoElementoM elemento[MAX];
    int tamanno;
} Monticulo;


/* Ejercicio 1 */

void iniciaMonticulo(Monticulo *m);
int vacioMonticulo(Monticulo m);
int insertar(tipoElementoM x, Monticulo *m);
int eliminarMinimo(Monticulo *m, tipoElementoM *minimo);
int decrementarClave(int pos, tipoClave cantidad, Monticulo *m);
void incrementarClave(int pos, tipoClave cantidad, Monticulo *m);
int esMonticulo(Monticulo m);

/* Funciones auxiliares que conviene implementar: las dos estrategias de filtrado en las 
   que se basan todos los algoritmos que manejan montículos */

  void filtradoDescendente(Monticulo *m, int i);
  void filtradoAscendente(Monticulo *m, int i);

/* Operación crearMonticulo la utilizaremos en ejercicio 2 y en tema de grafos */ 

  void crearMonticulo(Monticulo *m);

void heapsort1(int *vector, int n);

void verMonticulo(Monticulo *m);
