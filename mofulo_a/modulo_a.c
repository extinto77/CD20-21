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

