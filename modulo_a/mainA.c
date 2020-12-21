#include <stdio.h>
#include <stdlib.h>
#include "fsize.h"
#include <time.h>

int main(){
clock_t begin = clock();

    unsigned long long total;
    long long n_blocks;
    unsigned long size_of_last_block, block_size;
    FILE *fp;

    // Using function fsize() when file is already opened
    fp = fopen("aaa.txt", "rb");
    block_size = 2048;
    n_blocks = fsize(fp, NULL, &block_size, &size_of_last_block);
    total = (n_blocks-1) * block_size + size_of_last_block;
    
    printf("\n File: aaa.txt (file already opened)");
    printf("\n %ld blocks of %lu bytes + 1 block of %lu bytes", n_blocks-1, block_size, size_of_last_block);
    printf("\n File size = %llu bytes\n", total);
    fclose(fp);

    // Using function fsize() when file is not opened
    block_size = FSIZE_DEFAULT_BLOCK_SIZE;
    n_blocks = fsize(NULL, "bbb.zip", &block_size, &size_of_last_block);
    total = (n_blocks-1) * block_size + size_of_last_block;
    printf("\n File: bbb.zip");
    printf("\n %ld blocks of %lu bytes + 1 block of %lu bytes", n_blocks-1, block_size, size_of_last_block);
    printf("\n File size = %llu bytes\n", total);
    
   clock_t end = clock();
   double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf ("\n Daniel e Isabela, a93292, MIEI/CD, 21-JAN-2021 ");
    printf ("\n Módulo: f (cálculo das frequências dos símbolos");
    printf("\n Número de blocos: %llu ", n_blocks);
    printf("\n Tamanho dos blocos analisados no ficheiro original: ", block_size);
    printf("\n Compressão RLE: ");
    printf("\n Tamanho dos blocos analisados no ficheiro RLE: ", block_size);
    printf("\n Tempo de execução do módulo (milissegundos): %d ", time_spent);
    printf("\n Ficheiros gerados: ");

    return(0);
}