# Compiler and flags
CC = gcc
CFLAGS = -Wall

# Targets
pruebaSecuencial: pruebaSecuencial.c secuencial.o
	$(CC) -o pruebaSecuencial pruebaSecuencial.c secuencial.o

secuencial.o: secuencial.c secuencial.h
	$(CC) $(CFLAGS) -c secuencial.c


