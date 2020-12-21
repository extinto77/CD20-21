#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "modulo_a.h"
#include "fsize.h"


//Função que devolve o tamanho do bloco para análise
int tamanho_bloco (char t){
    int tamanho;

    if (t=='K') tamanho= 655360;
    else if (t=='m') tamanho=8388608;
    else tamanho = 67108864;
}

//Função que devolve o número de bytes do ficheiro
long tamanho_ficheiro(const char* ficheiro)
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
int compressao (char* ficheiro){


    unsigned long long total;
    long long n_blocks;
    unsigned long size_of_last_block, block_size;
    FILE *fp;

    // Using function fsize() when file is already opened
    
    block_size = 2048;
    n_blocks = fsize(fp, NULL, &block_size, &size_of_last_block);
    total = (n_blocks-1) * block_size + size_of_last_block;
  
   int c;
   int n = 0;
   int i;
  
   fp = fopen("file.txt","r");
   if(fp == NULL) {
      printf("Error in opening file");
      return(-1); }
   while (c = fgetc(fp) != '\0'){
    char anterior =c;
    i++;
    


   }
      
      

   fclose(fp);
   return(0);
}

