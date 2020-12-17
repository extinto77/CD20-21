#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "modulo_t.c"


int main(int argc, char *argv[]){
    char line[1024];

    scanf ("%s", &line);//ler do terminal ou dá como input??
    
    if (correct_file())
    {
        /* code */
    }
}


/*
strcmp returns 0 if str1 = str2
strcmp returns 1 if str1 > str2
strcmp returns -1 if str1 < str2
*/

//Para calcular o tempo de execução :


#include <time.h> //clock(), CLOCKS_PER_SEC e clock_t

int RandomInteger(int low, int high)
{
    int k;
    srand( (unsigned)time(NULL) );
    k = (rand() % high) + low;
    return k;
}



int main(){
 clock_t t; //variável para armazenar tempo

 t = clock(); //armazena tempo

//inserir a função

 t = clock() - t; // tempo final - tempo inicial
 printf("Tempo de execucao: %lf", ((double)t)/((CLOCKS_PER_SEC/1000))); //tempo apresentado em milisegundos
}