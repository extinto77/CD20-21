#include "modulo_t.h"


void swap(InfSymbl *xp, InfSymbl *yp){ 
    InfSymbl temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void freqDecres(InfSymbl arr[]){
    for (int i = 0; i < 255; i++)
        for (int j = 0; j < 255-i; j++)
            if (arr[j].freq < arr[j+1].freq) swap(&arr[j], &arr[j+1]);
}

void symblCres(InfSymbl arr[]){
    for (int i = 0; i < 255; i++)
        for (int j = 0; j < 255-i; j++)
            if (arr[j].symbl < arr[j+1].symbl) swap(&arr[j], &arr[j+1]);
}

/*
int somaFreq (InfSymbl arr[], int n) {
    int count = 0;
    for (int i=0; i<n && arr[i].freq!=0 ; i++) { 
        count += arr[i].freq;
    }
    return count;
}*/

int split (InfSymbl arr[], int inicio, int fim){
    int p1 = arr[inicio].freq, p2 = arr[fim].freq;

    while(inicio < (fim-1) ) {
        if (p2<p1) p2 += arr[fim--].freq;
        else p1 += arr[inicio++].freq;
    }
    return inicio;
}

void add0 (InfSymbl arr[], int i){
    arr[i].binary_code *= 10;
}

void add1 (InfSymbl arr[], int i){
    arr[i].binary_code = (arr[i].binary_code)*10 + 1;
} 

void atribuiBin (InfSymbl arr[], int inicio, int fim){ //rever ???
    if(inicio == fim || inicio == fim+1){
        add0(arr,inicio);
        add1(arr, fim);
    }else{
        int aux = inicio;
        int separa = split (arr, inicio, fim);

        atribuiBin(arr, aux, separa);
        atribuiBin(arr, (++separa),fim);

        for(int i=0; i<=separa;i++) add0(arr, i);
        for(int i=separa; i<fim;i++) add1(arr, i);
    }
}

int correct_file (char s1[], char s2[]){
    int i, j=0, ans=0;

    for(i=0; s1[i]; i++);

    for(i--,j; s2[j], s1[i]==s2[j]; i--,j++);

    if(!s2[j]) ans = 1; //s2[j]=='\0'

    return ans;
}

void converte (LInt *info_blocos) {
    while (info_blocos) {
        freqDecres((*info_blocos)->arr);
        int fim;
        for(int i = 0; (*info_blocos)->arr[i].freq != 0 && i<256; i++) fim = i;
        atribuiBin((*info_blocos)->arr, 0, fim);
        symblCres((*info_blocos)->arr); // se calhar não compensa

        info_blocos = &((*info_blocos)->prox);
    }
}

char *remove1digit (int val) {
    int i, aux=val;
    for (i=0; aux>=1; i++) aux = aux / 10;
    
    char *pt = malloc(sizeof(char)*++i);
    sprintf(pt, "%d", val);

    for(int j=0; pt[j] != '\0';j++) pt[j]=pt[j+1];

    char *reduct = malloc(sizeof(char)*--i);
    strcpy(reduct, pt);
    free (pt);
    return reduct;
}

void soBin(LInt *info_blocos) {
    
}

int countDigits(int val) {
    int i;
    for (i=0; val>=1 ;i++) val /= 10;
    return i;
}

void makeAtribution (char *buffer, LInt *info_blocos, char file_type, int num_blocos){
    int ant_freq;

    sscanf(buffer, "@%c@%d@", &file_type, &num_blocos);
    buffer = buffer + 4 + countDigits(num_blocos);

    for (int nb = 1; nb <= num_blocos; nb++){
        *info_blocos = malloc(sizeof(struct lligada));
        (*info_blocos)->nbloco = nb;
        sscanf(buffer, "%d@", &((*info_blocos)->tamanho_bloco));
        buffer = buffer + 1 + countDigits((*info_blocos)->tamanho_bloco);
            
        for (int i=0; i<=TAMANHO; i++) {
            if(sscanf(buffer, "%d", &((*info_blocos)->arr[i].freq)) == 1){
                ant_freq = (*info_blocos)->arr[i].freq;
                (*info_blocos)->arr[i].symbl = i;
                (*info_blocos)->arr[i].binary_code = 1; //inicializat todos a 1
                buffer = buffer + 1 + countDigits(ant_freq);
            }else{
                (*info_blocos)->arr[i].freq = ant_freq;
                (*info_blocos)->arr[i].symbl = i;
                (*info_blocos)->arr[i].binary_code = 1; //inicializat todos a 1
                buffer = buffer + 1;
            }
        }
        info_blocos = &((*info_blocos)->prox);
    }
    //free (buffer);
}

void makeCod(){
    //fazer
}


void printTamBlocos(LInt *info_blocos) {
    do{
        printf("%d", (*info_blocos)->tamanho_bloco);
        printf("/");
    }while((*info_blocos));
}

void printData1() { //mudar para printData
    struct tm *cache;     
    time_t now;
    time(&now);   
    cache = localtime(&now);
 
    printf("Data:%02d-%02d-%d ; Hora:%02d%02d%02d\n", cache->tm_mday, cache->tm_mon+1, cache->tm_year+1900, 
                                                        cache->tm_hour, cache->tm_min, cache->tm_sec);
}

void printData2() { //mudar para printData
    time_t now;
    time(&now);
    printf("Data : %s\n", ctime(&now));
}

void printInfo(LInt info_blocos ,int num_blocos /* float tempExec */) {
    printf("Autores: Pedro Miguel Marques Ferreira -> a93303 ; José Luís Alves Fernades -> a93200\nMIEI -> Comunicação Dados ; ");
    printData1(); //1 ou 2
    printf("Módulo: t (cálculo dos códigos dos símbolos)\nNúmero de Blocos: %d\nTamanho dos blocos analisados no ficheiro de símbolos: ", num_blocos);
    printTamBlocos(&info_blocos);
    //printf("bytes\nTempo de execução do módulo (milissegundos): %f\n", tempExec);
    printf("Ficheiro gerado: ???\n");
}

//John Doe, a12234, MIEI/CD, 1-jan-2021
//Módulo: t (cálculo dos códigos dos símbolos)
//Número de blocos: 2
//Tamanho dos blocos analisados no ficheiro de símbolos: 57444/1620 bytes
//Tempo de execução do módulo (milissegundos): 296
//Ficheiro gerado: exemplo.txt.rle.cod                 ainda falta !!! 





int modulo_t(char *fileName){ //trabalhar com o buffer passsar o primeiro para lá
    clock_t tic = clock();

    if(correct_file(fileName, "qerf.")){
        FILE *fp = fopen(fileName, "r");

        if(fp == NULL){
            printf("Não foi possível ler o ficheiro!");
            return 0;
        }

        fseek(fp, 0, SEEK_END);
        unsigned int tambuffer = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        char buffer[tambuffer+1]; //ver se posso fazer se for rle assim ou se tem de ser por blocos
        int count = fread(&buffer, tambuffer+1, 1, fp);

        LInt info_blocos;

        char file_type;
        int num_blocos;

        makeAtribution(buffer, &info_blocos, file_type, num_blocos);
        converte (&info_blocos);
        soBin(&info_blocos);
        makeCod(&info_blocos);

       clock_t toc = clock();

        float tempExec = ((double)(toc-tic) / CLOCKS_PER_SEC );

        printInfo(info_blocos, num_blocos /* tempExec */);
        fclose(fp);
    }
    else{
        printf("Tipo de ficheiro incorreto!");
    } 
}



int main(){
    modulo_t("aaa.txt.freq");
    return 1;
}