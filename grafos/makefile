# Sesión Grafos

ejercicio1: ejercicio1.c grafos.h grafos.o cola.o
	gcc -g ejercicio1.c grafos.o cola.o -o ejercicio1
ejercicio2: ejercicio2.c grafos.h grafos.o cola.o 
	gcc -g ejercicio2.c grafos.o cola.o -o ejercicio2


# Para la ultima parte de ejercicio2.c necesitamos monticulo.o ...cambia la linea de ordenes...
#ejercicio2: ejercicio2.c grafos.h grafos.o cola.o monticulo.o 
#	gcc -g ejercicio2.c grafos.o cola.o monticulo.o -o ejercicio2
ejercicio3a: ejercicio3a.c grafos.h grafos.o cola.o pila.o
	gcc -g ejercicio3a.c grafos.o cola.o pila.o -o ejercicio3a



grafos.o: grafos.c grafos.h
	gcc -g -c grafos.c
cola.o: cola.c cola.h
	gcc -g -c cola.c
pila.o: pila.c pila.h
	gcc -g -c pila.c
<<<<<<< HEAD
conjuntos.o: conjuntos.c conjuntos.h
	gcc -g -c conjuntos.c
=======
>>>>>>> cf88253d820a87210789558a303e935e59271a2b
# hay que modificar tipoElemento de monticulo 	
# CUIDADO hay que cambiar tipoElemento de monticulo a tipoElementoM ....
monticulo.o:monticulo.c monticulo.h
	gcc -g -c monticulo.c
limpiar:
	rm *.o	


