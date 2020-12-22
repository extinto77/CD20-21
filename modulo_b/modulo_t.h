#ifndef MODULO_T_AKA_B
#define MODULO_T_AKA_B

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAMANHO 256

typedef struct info_symbl{
    int symbl;
    int freq;
    int binary_code;
}InfSymbl;

typedef struct lligada { //Struct da Lista ligada de blocos que prefazem um ficheiro
    int nbloco; //número do bloco
    int tamanho_bloco; //tamano do bloco
    InfSymbl arr[TAMANHO]; //frequência de cada símbolo
    struct lligada *prox;
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

void converte (LInt *info_blocos);

char *remove1digit (int val);

void soBin(LInt *info_blocos);

int countDigits(int val);

void makeAtribution (char *buffer, LInt *info_blocos, char *file_type, int *num_blocos);

void makeCo();

void printTamBlocos(LInt info_blocos, int num_blocos);

void printData1();

void printData2();

void printInfo(LInt info_blocos ,int num_blocos /* float tempExec */);

int modulo_t(char *fileName);



#endif