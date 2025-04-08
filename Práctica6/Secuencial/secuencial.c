#include "secuencial.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

int leeSecuencial(char *fichero){
	FILE *f;
	tipoAlumno reg;
	int numReg=0;
	f=fopen("alumnos.dat","rb");
	fread(&reg,sizeof(tipoAlumno),1,f);
	while(!feof(f)){
		printf("%d\t %s %s %s %s %s\n\n",numReg,reg.dni,reg.nombre,reg.ape1,reg.ape2,reg.provincia);
		fread(&reg,sizeof(tipoAlumno),1,f);
		numReg++;
	}
	fclose(f);
	return numReg;
}
int buscaReg(FILE *fSecuencial, tipoAlumno *reg,char *dni){
	
	int numReg=0;
	
	while(fread(reg,sizeof(tipoAlumno),1,fSecuencial)){
		if(!strcmp(dni,reg->dni)) return numReg;
		numReg++;	
	}
	return -1;
}
int insertaReg(char *fSecuencial, tipoAlumno *reg){
	
	//fseek ftell
	FILE *file = fopen(fSecuencial, "wb");
	fseek(file, 0, SEEK_END);
	int numReg=ftell(file);
	fwrite(reg, sizeof(tipoAlumno), 1, file);
	fclose(file);
	return numReg++;
	
}
int modificarRegistro(char *fSecuencial, char *dni, char *provincia){}
