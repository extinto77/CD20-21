#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//ordenar funções todas


int modulo_t(char *fileName){ //trabalhar com o buffer passsar o primeiro para lá
    if(correct_file(fileName, "qerf.")){
        FILE *fp = fopen(fileName, "r+");

        if(fp == NULL){
            printf("Não foi possível ler o ficheiro!");
            return 0;
        }

        char file_type;
        int num_blocos;
        int ant_freq;

        fscanf(fp, "@%c@%d@", &file_type, &num_blocos); //fseek(fp, 5, SEEK_CUR);

        LInt info_blocos; //criar função

        LInt *inicio_info_blocos = info_blocos; //LInt *inicio_info_blocos = &info_blocos; ??

        //while(fp) ver se é necessário, not sure

        for (int nb = 1; nb <= num_blocos; nb++) {
            info_blocos->prox = criar_lista();
            
            info_blocos->nbloco = nb;
            fscanf(fp, "%d@", &info_blocos->tamanho_bloco); //fseek(fp, 2, SEEK_CUR);
            
            for (int i=0; i<=TAMANHO; i++) { //caso particular do ;; em que valor da freq é igual ao anterior
                if(fscanf(fp, "%d", &info_blocos->arr[i].freq) == 1){ // buffersize 256*8+255+1
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

        info_blocos = *inicio_info_blocos;
        converte (info_blocos); //posso destruir o apontador para o inicio ??
        info_blocos = *inicio_info_blocos;
        soBin(info_blocos);
    }else{
        printf("Tipo de ficheiro incorreto!");
    } 
}

void swap(int *xp, int *yp){ 
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
  
void freqDecres(InfSymbl arr[], int n) { //tentar tirar o n
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

void converte (LInt *info_blocos) {
    while (info_blocos) {
        freqDecres(info_blocos->arr, TAMANHO);
        atribuiBin(info_blocos->arr, 0, --TAMANHO);
        symblCres(arr, TAMANHO);// se calhar não compensa

        info_blocos = info_blocos->prox;
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

void soBin(LInt *info_blocos) {
    // lligada nova struct?? 
}

// fazer as cenas

// dar free do buffer











/*
#define BUFFER_SIZE 2304 // buffersize 256*8+255(';')+1('\0')

FILE *fp = fopen(fileName, "r+");

char *readFile (FILE *fp){
    char file_type;
    int num_blocos;
    fscanf(fp, "@%c@%d@", &file_type, &num_blocos);

    fazerStruct fixe; // valor = apontador do buffer
    while(*fp /*&& fgetc(fp) != '0') { // ver fim da leitura
        fixe->tamBloco
        fixe->valor = readBlock(fp); // ou com '&' e '.'
        fixe->prox;
    }

    write3info(fixe, file_type, num_blocos);
}

char *readBlock(FILE *fp) {
    char c;
    char *buffer = malloc(sizeof(char) *BUFFER_SIZE);
    int i;
    for(i = 0; (c = fgetc(fp)) != '@';i++)
        buffer[i] = c;
    buffer[i] = '\0';
    return buffer;
}

write3info(fazerStruct fixe, char file_type, int num_blocos) {
    int ant_freq;
    LInt info_blocos; //criar função

    LInt *inicio_info_blocos = info_blocos;

    //while(fp) ver se é necessário, not sure

    for (int nb = 1; nb <= num_blocos; nb++) {
        info_blocos->prox = criar_lista();
            
        info_blocos->nbloco = nb;
        fscanf(fp, "%d@", &info_blocos->tamanho_bloco);
        
        for (int i=0; i<=256; i++) { //caso particular do ;; em que valor da freq é igual ao anterior
            if(fscanf(fp, "%d", &info_blocos->arr[i].freq) == 1){ // buffersize 256*8+255+1
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
}*/



//------------------------------------


/*
int main () {
   FILE *fp;
   int tamfixe;

   fp = fopen("file.txt", "r");
   if( fp == NULL )  {
      perror ("Error opening file");
      return(-1);
   }
   fseek(fp, 0, SEEK_END);

   tamfixe = ftell(fp);
   fclose(fp);

   

   printf("Total size of file.txt = %d bytes\n", tamfixe);
  
   return(0);
}



*/






int modulo_t(char *fileName){ //trabalhar com o buffer passsar o primeiro para lá
    if(correct_file(fileName, "qerf.")){
        int tambuffer;
        FILE *fp = fopen(fileName, "r+");

        if(fp == NULL){
            printf("Não foi possível ler o ficheiro!");
            return 0;
        }

        fseek(fp, 0, SEEK_END);
        tambuffer = ftell(fp);
        char *buffer = malloc(sizeof(char) * (++tambuffer) ); //ver se posso fazer se for rle assim ou se tem de ser por blocos
        
        for(i = 0; i<tambuffer-2 ;i++)
            buffer[i] = fgetc(fp);
        buffer[i] = '\0';

        fclose(fp);

        LInt info_blocos;
        LInt *inicio_info_blocos = info_blocos; //LInt *inicio_info_blocos = &info_blocos; ??
        char file_type;
        int num_blocos;

        makeAtribution(buffer, info_blocos, &file_type, &num_blocos);
        LInt info_blocos = inicio_info_blocos; // sou burro e não é preciso criar novo
        converte (info_blocos); //posso destruir o apontador para o inicio ??
        soBin(info_blocos);
        makeCod()

        printInfo();
    }
    else{
        printf("Tipo de ficheiro incorreto!");
    } 
}

int countDigits(int val) {
    int i;
    for (i=0; val>=1 ;i++) (float)val /= 10;
    return i;
}

void makeAtribution (char *buffer, LInt info_blocos, char *file_type, int *num_blocos) {
    int ant_freq;

    sscanf(buffer, "@%c@%d@", file_type, num_blocos);
    buffer = buffer + 4 + countDigits(*num_blocos);

    for (int nb = 1; nb <= *num_blocos; nb++) {
        info_blocos->prox = criar_lista();
            
        info_blocos->nbloco = nb;
        sscanf(buffer, "%d@", &info_blocos->tamanho_bloco);
        buffer = buffer + 1 + countDigits(info_blocos->tamanho_bloco);
            
        for (int i=0; i<=TAMANHO; i++) { //caso particular do ;; em que valor da freq é igual ao anterior
            if(sscanf(fp, "%d", &info_blocos->arr[i].freq) == 1){ // buffersize 256*8+255+1
                ant_freq = &info_blocos->arr[i].freq;
                info_blocos->arr[i].binary_code = 1; //inicializat todos a 1
                buffer = buffer + 1;
            } else {
                info_blocos->arr[i].freq = ant_freq;
                info_blocos->arr[i].binary_code = 1; //inicializat todos a 1
            }
        }
        info_blocos = info_blocos->prox;
    }
    free (buffer);
}

printInfo(int num_blocos, float temExec) {
    printf("Autores: Pedro Miguel Marques Ferreira -> a93303 ; José Luís Alves Fernades -> a93200\n
            MIEI -> Comunicação Dados ; ");
    printData(); //1 ou 2
    printf("Módulo: t (cálculo dos códigos dos símbolos)\n
            Número de Blocos: %d\n
            Tamanho dos blocos analisados no ficheiro de símbolos: ", num_blocos);
    printTamBlocos();
    printf("bytes\n
            Tempo de execução do módulo (milissegundos): %f\n", tempExec);
    printf("Ficheiro gerado: ???\n");
}

printTamBlocos(LInt info_blocos, int num_blocos) {
    int pt = listaTamanhos(LInt info_blocos, int num_blocos);
    while (*(pt[i]))
}

void printData1() {
    struct tm *cache;     
    time_t now;
    time(&now);   
    cache = localtime(&now);
 
    printf("Data:%02d-%02d-%d ; Hora:%02d%02d%02d\n", cache->tm_mday, cache->tm_mon+1, cache->tm_year+1900, 
                                                        cache->tm_hour, cache->tm_min, cache->tm_sec);
}

printData2() {
    time_t now;
    time(&now);
    printf("Data : %s\n", ctime(&now));
}

//John Doe, a12234, MIEI/CD, 1-jan-2021
//Módulo: t (cálculo dos códigos dos símbolos)
//Número de blocos: 2
Tamanho dos blocos analisados no ficheiro de símbolos: 57444/1620 bytes
//Tempo de execução do módulo (milissegundos): 296
Ficheiro gerado: exemplo.txt.rle.cod 




int main() // inserir na duncao modulo depois de decidida
{
    clock_t tic = clock();

    // inserir função 

    clock_t toc = clock();

    float tempExec = (double)(toc-tic) / CLOCKS_PER_SEC );

    printInfo( ?? );

    return 0;
}

int *listaTamanhos(LInt info_blocos, int num_blocos) { // para depois escrever nas infos
    int *pt = arr_tam[num_blocos];
    for (int i=0; info_blocos; i++) {
        arr_tam[i] = info_blocos->tamanho_bloco;
    }
    return pt;
}