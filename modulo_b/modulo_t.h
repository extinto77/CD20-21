#ifndef MODULO_T_AKA_B
#define MODULO_T_AKA_B

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct info_symbl{
    int symbl; //símbolo (ASCII)
    int freq; //frequência do símbolo
    int binary_code; //código binário do símbolo
}InfSymbl;

typedef struct lligada { //Struct da Lista ligada de blocos que prefazem um ficheiro
    int nbloco; //número do bloco
    int tamanho_bloco; //tamano do bloco
    InfSymbl arr[256]; //Array de struct com as 3 informações
    struct lligada *prox; // próximo bloco
}*LInt;

//ver que funções ficam e que funções por aqui

void swap(InfSymbl *xp, InfSymbl *yp);

void freqDecres(InfSymbl arr[]);

void symblCres(InfSymbl arr[]);

int split (InfSymbl arr[], int inicio, int fim);

void add0 (InfSymbl arr[], int i);

void add1 (InfSymbl arr[], int i);

void atribuiBin (InfSymbl arr[], int inicio, int fim);

int correct_file (char s1[], char s2[]);

void converte (LInt *info_blocos, int *medidas);

int countBuffer(LInt *info_blocos);

char *remove1digit (int val);

int countDigits(int val);

int makeAtribution (char *buffer, LInt *info_blocos, char *file_type, int *num_blocos);

void writeBuffer(LInt *info_blocos, char *bufferFinal, int num_blocos, char *file_type);

void printTamBlocos(LInt *info_blocos);

void printData();

void printInfo(LInt info_blocos ,int num_blocos, float tempExec, char *fixe);

int modulo_t(char *fileName);


#endif