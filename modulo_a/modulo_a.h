#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#ifndef MODULO_A
#define MODULO_A



#define FSIZE_DEFAULT_BLOCK_SIZE 524288         // Default block size = 512 KBytes
#define FSIZE_MIN_BLOCK_SIZE 512                // Min block size = 512 Bytes
#define FSIZE_MAX_BLOCK_SIZE 67108864           // Max block size = 64 MBytes
#define FSIZE_MAX_NUMBER_OF_BLOCKS 4294967296   // Max number of blocks that can be returned = 2^32 blocks
#define FSIZE_MAX_SIZE_FSEEK 2147483648         // Max size permitted in fseek/ftell functions = 2 GBytes
#define FSIZE_ERROR_BLOCK_SIZE -1               // Error: Block size is larger than max value
#define FSIZE_ERROR_NUMBER_OF_BLOCKS -2         // Error: Number of Blocks exceeds max value permitted
#define FSIZE_ERROR_IN_FILE -3                  // Error: Opening or reading file
#define FSIZE_ERROR_IN_FTELL -1L                // Error: When using ftell()

long long fsize(FILE *fp_in, unsigned char *filename, unsigned long *the_block_size, long *size_of_last_block);

int funcaotamanho_bloco (char t);

long funcaotamanho_ficheiro(const char* ficheiro);

int compressao (char* ficheiro, char* lista, unsigned long tamanhobloco, int bloco);

char* novaLista (char* ficheiro, unsigned long tamanho_bloco, int bloco, unsigned long long tamanhoficheiro);

char* ultimaLista (char* ficheiro, unsigned long size_of_last_block,int bloco,unsigned long block_size);

int** novaMatriz(char* ficheiro, long long numeroblocos);

void frequencia (char * ficheiro, char compressao, unsigned long long tamanho_ficheiro, unsigned long size_of_last_block,long long numeroblocos, unsigned long tamanhobloco, int bloco,int **m);

int printinfo(long long n_blocks,unsigned long block_size, double time_spent,unsigned long size_of_last_block,int taxafinal);

int moduloA (char* ficheiro, char forceRLE, char tamanhobloco);


#endif