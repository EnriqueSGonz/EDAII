#include "dispersion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Crea un fichero hash inicialmente vacio seg�n los criterios especificados en la pr�ctica
// Primera tarea a realizar para  crear un fichero organizado mediante DISPERSI�N
void creaHvacio(char *fichHash)
{ FILE *fHash;
  tipoCubo cubo;
  int j;
  int numCubos =CUBOS+CUBOSDESBORDE;

  memset(&cubo,0,sizeof(cubo));

  fHash = fopen(fichHash,"wb");
  for (j=0;j<numCubos;j++) fwrite(&cubo,sizeof(cubo),1,fHash);
  fclose(fHash);
}
// Lee el contenido del fichero hash organizado mediante el m�todo de DISPERSI�N seg�n los criterios
// especificados en la pr�ctica. Se leen todos los cubos completos tengan registros asignados o no. La
// salida que produce esta funci�n permite visualizar el m�todo de DISPERSI�N

int leeHash(char *fichHash)
{ FILE *f;
  tipoCubo cubo;
  int j,i=0;
  size_t numLee;

   f = fopen(fichHash,"rb");
   rewind(f);
   fread(&cubo,sizeof(cubo),1,f);
   while (!feof(f)){
	for (j=0;j<C;j++) {
        if (j==0)    	printf("Cubo %2d (%2d reg. ASIGNADOS)",i,cubo.numRegAsignados);
        else  	printf("\t\t\t");
	if (j < cubo.numRegAsignados) 
		    printf("\t%s %s %s %s %s\n",
	    		cubo.reg[j].dni,
			cubo.reg[j].nombre,
			cubo.reg[j].ape1,
		  	cubo.reg[j].ape2,
  	                cubo.reg[j].provincia);
	else printf ("\n");
        }
       i++;
       fread(&cubo,sizeof(cubo),1,f);
   }
   fclose(f);
   return i;
}
int creaHash(char *fichEntrada,char *fichHash){
	FILE *f,*fHash;
	tipoAlumno reg;
	int numRegDesb=0,nCubo,i;
	tipoCubo cubo;
	creaHvacio(fichHash);
	
	f=fopen(fichEntrada,"rb");
	fHash=fopen(fichHash,"r+b");
	fread(&reg,sizeof(tipoAlumno),1,f);
	while(!feof(f)){
		nCubo=atoi(reg.dni)%CUBOS;
		fseek(fHash,nCubo*sizeof(tipoCubo),SEEK_SET);
		fread(&cubo,sizeof(tipoCubo),1,fHash);
		i=cubo.numRegAsignados;
		if(i<C){
			cubo.reg[i]=reg;
			cubo.numRegAsignados++;
			fseek(fHash,nCubo*sizeof(tipoCubo),SEEK_SET);
			fwrite(&cubo,sizeof(tipoCubo),1,fHash);
		}else{	
			desborde(fHash,reg);
			numRegDesb++;
		}
		fread(&reg,sizeof(tipoAlumno),1,f);
		
	}
	fclose(f);
	fclose(fHash);
	return numRegDesb;
}

int buscaReg(FILE *fHash, tipoAlumno *reg,char *dni){
	tipoCubo cubo;
	int i,nCubo;

	nCubo=atoi(dni)%CUBOS;
	fseek(fHash,nCubo*sizeof(tipoCubo),SEEK_SET);
	fread(&cubo,sizeof(tipoCubo),1,fHash);
	for(i=0;i<cubo.numRegAsignados;i++){
		if(strcmp(cubo.reg[i].dni,dni)==0){
			*reg=cubo.reg[i];
			return 1;
		}
	}
	return 0;
}











