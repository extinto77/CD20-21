#ifndef MODULO_A
#define MODULO_A

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


#endif