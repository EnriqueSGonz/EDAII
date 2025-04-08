# Ejercicio 1
cMatrices:prueba.c rMatrices/conjuntos.o  
	gcc -g prueba.c -DMATRICES rMatrices/conjuntos.o -o cMatrices
rMatrices/conjuntos.o: rMatrices/conjuntos.c rMatrices/conjuntos.h
	gcc -c -g rMatrices/conjuntos.c -o rMatrices/conjuntos.o
# Ejercicio 2
cListas:prueba.c rListas/conjuntos.o 
	gcc -g prueba.c -DLISTAS rListas/conjuntos.o -o cListas
rListas/conjuntos.o: rListas/conjuntos.c rListas/conjuntos.h
	gcc -c -g rListas/conjuntos.c -o rListas/conjuntos.o
# Ejercicio 3 
cArboles:prueba.c rArboles/conjuntos.o 
	gcc -g prueba.c -DARBOLES rArboles/conjuntos.o -o cArboles
rArboles/conjuntos.o: rArboles/conjuntos.c rArboles/conjuntos.h
	gcc -c -g rArboles/conjuntos.c -o rArboles/conjuntos.o
# Ejercicio 4, 5 y 6
#  ....
cTamaño:prueba.c rTamaño/conjuntos.o 
	gcc -g prueba.c -DARBOLES rTamaño/conjuntos.o -o cTamaño
rTamaño/conjuntos.o: rTamaño/conjuntos.c rTamaño/conjuntos.h
	gcc -c -g rTamaño/conjuntos.c -o rTamaño/conjuntos.o
cAltura:prueba.c rAltura/conjuntos.o 
	gcc -g prueba.c -DARBOLES rAltura/conjuntos.o -o cAltura
rAltura/conjuntos.o: rAltura/conjuntos.c rAltura/conjuntos.h
	gcc -c -g rAltura/conjuntos.c -o rAltura/conjuntos.o
cCompresion:prueba.c rCompresion/conjuntos.o 
	gcc -g prueba.c -DCOMPRESION rCompresion/conjuntos.o -o cCompresion
rCompresion/conjuntos.o: rCompresion/conjuntos.c rCompresion/conjuntos.h
	gcc -c -g rCompresion/conjuntos.c -o rCompresion/conjuntos.o
limpiar:
	rm c*
