#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "modulo_a.h"
#include "fsize.h"


//Função que devolve o tamanho do bloco para análise
int funcaotamanho_bloco (char t){
    int tamanho;

    if (t=='K') tamanho= 655360;
    else if (t=='m') tamanho=8388608;
    else tamanho = 67108864;
}

//Função que devolve o número de bytes do ficheiro
long funcaotamanho_ficheiro(const char* ficheiro)
{
    long tamanho;
    FILE *f;
 
    f = fopen(ficheiro, "rb");
    if (f == NULL) return -1;
    fseek(f, 0, SEEK_END);
    tamanho = ftell(f);
    fclose(f);
 
    return tamanho;
}

//Função que comprime o ficheiro
int compressao (char* ficheiro, char* lista, unsigned long tamanhobloco, int bloco){

char nomeFicheiro[200];
strcpy (nomeFicheiro,ficheiro);
char extensaoRLE = ".rle";
strcat(nomeFicheiro, extensaoRLE);

   
FILE *fp = fopen("aaa.txt", "ab");
if (fp == NULL) printf ("Erro abrir ficheiro");

fseek(fp, (tamanhobloco*bloco),SEEK_SET);
int i = 0;
char atual = lista[i];
char anterior;
int c = 0;
int carateres = 0;


for ( i; lista[i]; i++ {
   anterior = atual;
   atual = lista [i];
   
   if (atual == anterior) c++;
   else {
       if (c >= 4 ){


           fputc ('\0', fp);
           fprintf (fp, "%c", anterior);
           fputc (c, fp);
           carateres += 3;
           c = 1;

           }
       } else {
            while (c != 0) {
               fputc(anterior, fp);
               c--;
               carateres++;
       }
        c = 1;
   }
}


fclose(fp);

int taxa;

for (int j = 0;lista [j];j++);

taxa= (((abs(j-carateres))/j)*100);
return taxa;
}



char* novaLista (char* ficheiro, unsigned long tamanho_bloco, int bloco, unsigned long long tamanhoficheiro){
    int i = 0;
 char* lista = malloc(sizeof(char)*tamanho_bloco);
 FILE* fp = fopen(ficheiro, "rb");
 if (fp == NULL) printf ("Erro abrir ficheiro");
 fseek(fp,( tamanho_bloco * bloco), SEEK_SET);
 fread (lista, tamanho_bloco,1,fp);
 lista[tamanho_bloco] = '\0';

 return lista;
}








   int moduloA (char* ficheiro, unsigned long tamanhobloco, unsigned long long tamanho_ficheiro, long long numeroblocos){
      
       int bloco = 0;
       char* lista = novaLista(ficheiro, tamanhobloco, bloco, tamanho_ficheiro);
       
    int percentagem = compressao (ficheiro,lista, tamanhobloco, bloco);
    

      
    
   fclose(fp);
   return 0;
}



