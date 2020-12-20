#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define int TAMANHO 256

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



int modulo_t(char *fileName){
    if(correct_file(fileName, "qerf.")){
        FILE *fp = fopen(fileName, "r+");

        if(fp == NULL){
            printf("Não foi possível ler o ficheiro!");
            return 0;
        }

        char file_type;
        int num_blocos;
        int ant_freq;

        fscanf(fp, "@%c@%d@", &file_type, &num_blocos);

        LInt info_blocos; //criar função

        LInt *inicio_info_blocos = info_blocos;

        //while(fp) ver se é necessário, not sure

        for(int nb = 1; nb <= num_blocos; nb++){
            info_blocos->prox = criar_lista();
            
            info_blocos->nbloco = nb;
            fscanf(fp, "%d@", &info_blocos->tamanho_bloco);
            
            for(int i=0; i<=256; i++){ //caso particular do ;; em que valor da freq é igual ao anterior
                if(fscanf(fp, "%d", &info_blocos->arr[i].freq) == 1){
                    ant_freq = &info_blocos->arr[i].freq;
                    info_blocos->arr[i].binary_code = 1; //inicializat todos a 1
                    fseek(fp, 1, SEEK_CUR);
                } else{
                    info_blocos->arr[i].freq = ant_freq;
                    info_blocos->arr[i].binary_code = 1; //inicializat todos a 1
                }
            }
            info_blocos = info_blocos->prox;
        }
        fclose(fp);
        LInt fichFinal = inicio_info_blocos;
        converte (fichFinal); //posso destruir o apontador para o inicio ??
        soBin(fichFinal);
    }else{
        printf("Tipo de ficheiro incorreto!");
    } 
}


void swap(int *xp, int *yp){ 
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
  
void freqDecres(InfSymbl arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++){
        for (j = 0; j < n-i-1; j++){
            if (arr[j].freq < arr[j+1].freq){
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

void symblCres(InfSymbl arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++){
        for (j = 0; j < n-i-1; j++){
            if (arr[j].symbl < arr[j+1].symbl) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

/*
int somaFreq (InfSymbl arr[], int n) {
    int count = 0;
    for (int i=0; i<n && arr[i].freq!=0 ; i++) { 
        count += arr[i].freq;
    }
    return count;
}*/

int split (InfSymbl arr[], int inicio, int fim /*, int count*/ ) {
    int p1=0, p2=0;

    p1 = arr[inicio].freq;
    p2 = arr[fim].freq;

    while(inicio < (fim-1) ) {
        if (p2<p1) p2 += arr[fim--].freq;
        else p1 += arr[inicio++].freq;
    }
    return inicio;
}

void add0 (InfSymbl arr[], int i) {
    arr[i].binary_code *= 10;
}

void add1 (InfSymbl arr[], int i) {
    arr[i].binary_code = (arr[i].binary_code)*10 + 1;
} 

void atribuiBin (InfSymbl arr[], int inicio, int fim) {

    int aux = inicio;
    int separa = split (arr, inicio, fim);
    for(int i=0; i<=separa;i++) add0(arr, i);
    for(int i=separa; i<n;i++) add1(arr, i);

    atribuiBin(arr, aux, inicio);
    atribuiBin(arr, (++separa),fim);
}

int correct_file (char s1[], char s2[]){
    int i, j=0, ans=0;

    for(i=0;s1[i];i++);

    for(i--,j; s2[j],s1[i]==s2[j]; i--,j++);

    if(!s2[j]) ans = 1; //s2[j]=='\0'

    return ans;
}

void converte (LInt *fichFinal) {
    while (fichFinal) {
        freqDecres(fichFinal->arr, TAMANHO);
        atribuiBin(fichFinal->arr, 0, --TAMANHO);
        symblCres(arr, TAMANHO);

        fichFinal = fichFinal->prox;
    }
}

char *remove1digit (int val) {
    int i, aux=val;
    for (i=0; aux>=1; i++) {
        aux = aux / 10;
    }
    char *pt=malloc(sizeof(char)*++i);
    sprintf(pt, "%d", val);

    for(int j=0; pt[j] != '\0';j++) pt[j]=pt[j+1];

    char *reduct = malloc(sizeof(char)*--i);
    strcpy(reduct, pt);
    free (pt);
    return reduct;
}

/*int main() {
char *miyagilindo = remove1digit(101001);
  return 0;
}*/

void soBin(LInt *fichFinal) {
    // lligada nova struct?? 
}

