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
            if (arr[j].symbl > arr[j+1].symbl) swap(&arr[j], &arr[j+1]);
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
    int auxi = inicio, auxf = fim;
    int p1 = arr[auxi].freq, p2 = arr[auxf].freq;

    if (inicio == fim) return (auxi=-1);

    while(auxi <= (auxf-1)) {
        if (p2<p1){
            p2 += arr[auxf].freq; 
            auxf--;
        }else{
            p1 += arr[auxi].freq;
            auxi++;
        } 
    }
    return auxi;
}

void add0 (InfSymbl arr[], int i){
    arr[i].binary_code *= 10;
}

void add1 (InfSymbl arr[], int i){
    arr[i].binary_code = (arr[i].binary_code)*10 + 1;
} 

void atribuiBin (InfSymbl arr[], int inicio, int fim){

    int separa = split (arr, inicio, fim);

    if(separa<0) return;

    if(fim == inicio+1){
        add0(arr, inicio);
        add1(arr, fim);
    }else{
        for(int i=inicio; i<=separa;i++) add0(arr, i);
        for(int i=separa+1; i<=fim;i++) add1(arr, i);

        atribuiBin(arr, inicio, separa);
        atribuiBin(arr, separa+1,fim);
    }
}

int correct_file (char s1[], char s2[]){
    int i, j=0, ans=0;

    for(i=0; s1[i]; i++);

    for(i--,j; s2[j], s1[i]==s2[j]; i--,j++);

    if(!s2[j]) ans = 1;

    return ans;
}

void converte (LInt *info_blocos, int *tamanho) {
    int acc=0;
    while (*info_blocos) { // while ((*info_blocos)->prox) {   antigo
        freqDecres((*info_blocos)->arr);
        int fim;
        for(int i = 0; (*info_blocos)->arr[i].freq != 0 && i<256; i++) fim = i;
        atribuiBin((*info_blocos)->arr, 0, fim);
        
        (*tamanho) += countBuffer(info_blocos);
        
        symblCres((*info_blocos)->arr);

        info_blocos = &((*info_blocos)->prox);
    }
}

int countBuffer(LInt *info_blocos){
    int acc = 0;
    
    for (int i=0; (*info_blocos)->arr[i].freq != 0 && i<256; i++) {
        acc += (countDigits((*info_blocos)->arr[i].binary_code))-1;
    }
    return acc;
}

char *remove1digit (int val) {
    int i, aux=val;
    for (i=0; aux>=1; i++) aux = aux / 10;
    
    char *pt = malloc(sizeof(char)*(i+1));
    sprintf(pt, "%d", val);

    for(int j=0; pt[j] != '\0';j++) pt[j]=pt[j+1];

    char *reduct = malloc(sizeof(char)*i);
    strcpy(reduct, pt);
    free (pt);
    return reduct;
}

int countDigits(int val) {
    int i;
    for (i=0; val>=1 ;i++) val /= 10;
    return i;
}

int makeAtribution (char *buffer, LInt *info_blocos, char *file_type, int *num_blocos){
    int digitsTams = 0, ant_freq;

    sscanf(buffer, "@%c@%d@", file_type, num_blocos);
    buffer = buffer + 4 + countDigits(*num_blocos);

    for (int nb = 1; nb <= *num_blocos; nb++){
        *info_blocos = malloc(sizeof(struct lligada));

        (*info_blocos)->nbloco = nb;
        sscanf(buffer, "%d@", &((*info_blocos)->tamanho_bloco));
        int aux = countDigits((*info_blocos)->tamanho_bloco);
        digitsTams += aux;
        buffer = buffer + 1 + aux;
            
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
                buffer = buffer + 1; //buffer += 1
            }
        }
        info_blocos = &((*info_blocos)->prox);
        buffer = buffer + 1;
    }
    (*info_blocos) = NULL;
    

    return digitsTams;
}

void writeBuffer(LInt *info_blocos, char *bufferFinal, int num_blocos, char *file_type){
    int indice = 0;
    sprintf (bufferFinal, "@%c@%d",file_type[0], num_blocos );
    indice += 3 + countDigits(num_blocos);
    while (*info_blocos) {
        sprintf(bufferFinal+indice, "@%d@", (*info_blocos)->tamanho_bloco);
        indice += 2 + countDigits( (*info_blocos)->tamanho_bloco );
        for(int i=0; i<256 ; i++) {
            if ((*info_blocos)->arr->freq == 0) {
                sprintf(bufferFinal+indice,";");
                indice++;
            }
            else{
                char *str1 = malloc(sizeof(char)*9);
                str1 = remove1digit((*info_blocos)->arr->binary_code);
                sprintf(bufferFinal+indice,"%s;", str1);
                indice += strlen(str1);
                free(str1);
            }
        }
    info_blocos = &((*info_blocos)->prox);   
    }
    sprintf(bufferFinal+indice, "@0");
}

void printTamBlocos(LInt *info_blocos) {
    while(*info_blocos) {
        printf("%d", (*info_blocos)->tamanho_bloco);
        printf("/");
        info_blocos = &((*info_blocos)->prox); 
    }
}

void printData() { //mudar para printData
    struct tm *cache;     
    time_t now;
    time(&now);   
    cache = localtime(&now);
 
    printf("Data:%02d-%02d-%d ; Hora:%02d%02d%02d\n", cache->tm_mday, cache->tm_mon+1, cache->tm_year+1900, 
                                                        cache->tm_hour, cache->tm_min, cache->tm_sec);
}

void printInfo(LInt info_blocos ,int num_blocos, float tempExec, char *fixe) {
    printf("Autores: Pedro Miguel Marques Ferreira -> a93303 ; José Luís Alves Fernades -> a93200\nMIEI -> Comunicação Dados ; ");
    printData(); //1 ou 2
    printf("Módulo: t (cálculo dos códigos dos símbolos)\nNúmero de Blocos: %d\nTamanho dos blocos analisados no ficheiro de símbolos: ", num_blocos);
    printTamBlocos(&info_blocos);
    printf("bytes\nTempo de execução do módulo (milissegundos): %f\n", tempExec);
    printf("Ficheiro gerado: %s\n", fixe);
}

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
        char buffer[tambuffer+1];
        fread(&buffer, tambuffer+1, 1, fp); 
        fclose(fp);

        LInt info_blocos;
        char *file_type = malloc(sizeof(char)*2);
        int num_blocos = 0;
        
        int digitsTams = makeAtribution(buffer, &info_blocos, file_type, &num_blocos);

        int tamanhoBin = 0;
        converte (&info_blocos, &tamanhoBin);

        int tamFinal = 4 + countDigits(num_blocos) + digitsTams + 256*num_blocos + tamanhoBin;
        char bufferFinal[tamFinal+1]; // + \0
        writeBuffer(&info_blocos, bufferFinal, num_blocos, file_type);

        char *fixe = malloc(sizeof(char)*(strlen(fileName)+5));
        strcpy(fixe,fileName);
        strcat(fixe, ".cod");

        fclose(fopen(fixe,"w"));
        FILE *fpf = fopen (fixe, "w");
        
        //fprintf(fpf, "%s", buffer);
        fwrite(bufferFinal ,1 ,tamFinal+1 , fpf);
        fclose(fpf);

        clock_t toc = clock();

        float tempExec = ((double)(toc-tic) / CLOCKS_PER_SEC );

        printInfo(info_blocos, num_blocos, tempExec, fixe);
    }
    else printf("Tipo de ficheiro incorreto!");
}


int main(){
    modulo_t("aaa.txt.freq");
    return 1;
}

