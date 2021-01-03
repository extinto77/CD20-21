#include "modulo_t.h"

/*      CD 20/21 
    MODULO B
        Os autores deste modulo foram José Luis Alves Fernandes a93200 e Pedro Miguel Marques Ferreira a93303.
        ->Este ficheiro contem todas as funções utilizadas para a execução do modulo B, a criação dos códigos Shannon Fano, para tal utlizamos as funções 
        como a modulo_t, a makeAtribution, a converte e a writeBuffer.
        ->A modulo_t é a função principal, recebe como input o nome do ficheiro e começa por saber o tamanho do mesmo, de seguida cria um buffer desse tamanho, onde será
        guardada toda a informação do ficheiro, de seguida vai para a makeAtribution, que utliza esse buffer e organiza a informação em blocos, utilizando a struct lligada
        e a Info_Symbl e que retorna o tamanho dos digitos do tamanho de cada bloco em que o ficheiro foi dividido, para posterior utilização.
        ->A Converte ordena as frequências de forma decrescente e de seguida cria os códigos  Shannon Fano, aproveita também para calcular a soma do número de bits de 
        cada código binário. No fim volta a organizar tudo como estava de inicio.
        ->A writeBuffer cria o buffer final, que será utilizado para escrever no ficheiro de output, segundo as regras do tipo de ficheiro cod.
*/

// Avalia se o ficheiro input é válido
int correct_file (char s1[], char s2[]){
    int i, j=0, ans=0;

    for(i=0; s1[i]; i++);

    for(i--, j; s2[j], s1[i]==s2[j]; i--,j++);

    if(!s2[j]) ans = 1;

    return ans;
}

// Atuliza a extensão do ficheiro para .cod
char *codFile(char fileName[]){
    int i=0;
    char *cod = {"cod"};
    for(i; fileName[i]; i++);
    
    int j;

    for(i=i-4, j=0; fileName[i]; i++, j++){
        fileName[i] = cod[j];
    }

    return fileName;
}

// Troca a ordem de dois elementos no array
void swap(InfSymbl *xp, InfSymbl *yp){ 
    InfSymbl temp = *xp;
    *xp = *yp;
    *yp = temp;
}

//Ordena as frequências por ordem decrescente
void freqDecres(InfSymbl arr[]){
    for (int i = 0; i < 255; i++)
        for (int j = 0; j < 255-i; j++)
            if (arr[j].freq < arr[j+1].freq) swap(&arr[j], &arr[j+1]);
}

//Ordena os símbolos por ordem crescente
void symblCres(InfSymbl arr[]){
    for (int i = 0; i < 255; i++)
        for (int j = 0; j < 255-i; j++)
            if (arr[j].symbl > arr[j+1].symbl) swap(&arr[j], &arr[j+1]);
}

//Adiciona um 0 ao códifo Shannon Fano
void add0 (InfSymbl arr[], int i){
    arr[i].Shannon_Fano *= 10;
}

//Adiciona um 1 ao códifo binário
void add1 (InfSymbl arr[], int i){
    arr[i].Shannon_Fano = (arr[i].Shannon_Fano)*10 + 1;
}

// Remove o primeiro digito 1 do código Shannon Fano
char *remove1digit (int val){
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

//Conta os dígitos de determinao valor
int countDigits(int val){
    if (val==0) return 1;
    int i;
    for (i=0; val>=1 ;i++) val /= 10;
    return i;
}

//Determina o índice da melhor divisão tal que a soma das probabilidades dos dois subconjuntos seja o mais próxima da metade do conjunto 
int split (InfSymbl arr[], int inicio, int fim){
    int auxi = inicio, auxf = fim;
    int p1 = arr[auxi].freq, p2 = arr[auxf].freq;

    if (inicio == fim) return (auxi=-1);

    while(auxi <= (auxf-1)){
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

//Calcula a soma do número de digitos dos códigos Shannon Fano
int countBuffer(LInt *info_blocos){
    int acc = 0;
    
    for (int i=0; (*info_blocos)->arr[i].freq != 0 && i<256; i++) {
        acc += (countDigits((*info_blocos)->arr[i].Shannon_Fano))-1;
    }
    return acc;
}

// Cria os códigos Shannon Fano de cada símbolo
void atribuiBin (InfSymbl arr[], int inicio, int fim){
    if(inicio == fim || inicio > fim) return;

    if((inicio + 1) == fim){
        add0(arr, inicio);
        add1(arr, fim);
    }else{
        int separa = split (arr, inicio, fim);

        if(separa<0) return;

        for(int i=inicio; i<=separa;i++) add0(arr, i);
        for(int i=separa+1; i<=fim;i++) add1(arr, i);

        atribuiBin(arr, inicio, separa);
        atribuiBin(arr, separa+1,fim);
    }
}

// Organiza a informação para criação dos códigos Shannon Fano
void converte (LInt *info_blocos, int *tamanhoBin){
    while (*info_blocos) {
        freqDecres((*info_blocos)->arr);
        int fim;
        for(int i = 0; (*info_blocos)->arr[i].freq != 0 && i<256; i++) fim = i;
        atribuiBin((*info_blocos)->arr, 0, fim);
        
        (*tamanhoBin) += countBuffer(info_blocos);
        
        symblCres((*info_blocos)->arr);

        info_blocos = &((*info_blocos)->prox);
    }
}

// Organiza a informação do buffer listas ligadas e Info_Symbl
int makeAtribution (char *buffer, LInt *info_blocos, char *file_type, int *num_blocos){
    int digitsTams = 0, ant_freq = 0;

    sscanf(buffer, "@%c@%d", file_type, num_blocos);
    buffer += 4 + countDigits(*num_blocos); // 4 e n 3 para passar já o @ seguinte

    for (int nb = 1; nb <= *num_blocos; nb++){
        *info_blocos = malloc(sizeof(struct lligada));

        (*info_blocos)->nbloco = nb;
        sscanf(buffer, "%d@", &((*info_blocos)->tamanho_bloco));
        int aux = countDigits((*info_blocos)->tamanho_bloco);
        digitsTams += aux;
        buffer += 1 + aux;
            
        for (int i=0; i<256; i++) {
            if(sscanf(buffer, "%d", &((*info_blocos)->arr[i].freq)) == 1){
                ant_freq = (*info_blocos)->arr[i].freq;
                (*info_blocos)->arr[i].symbl = i;
                (*info_blocos)->arr[i].Shannon_Fano = 1; //inicializat todos a 1
                buffer += 1 + countDigits(ant_freq);
            }else{
                (*info_blocos)->arr[i].freq = ant_freq;
                (*info_blocos)->arr[i].symbl = i;
                (*info_blocos)->arr[i].Shannon_Fano = 1; //inicializat todos a 1
                buffer++;
            }
        }
        info_blocos = &((*info_blocos)->prox);
    }
    (*info_blocos) = NULL;
    

    return digitsTams;
}

// Cria o buffer final para o ficheiro output
void writeBuffer(LInt *info_blocos, char *bufferFinal, int num_blocos, char *file_type){
    int indice = 0;
    sprintf (bufferFinal, "@%c@%d",file_type[0], num_blocos );
    indice += 3 + countDigits(num_blocos);
    while (*info_blocos) {
        sprintf(bufferFinal+indice, "@%d@", (*info_blocos)->tamanho_bloco);
        indice += 2 + countDigits( (*info_blocos)->tamanho_bloco );
        for(int i = 0; i < 255 ; i++){
            if ((*info_blocos)->arr[i].freq == 0) {
                sprintf(bufferFinal+indice,";");
                indice++;
            }else{
                sprintf(bufferFinal+indice,"%s;", remove1digit((*info_blocos)->arr[i].Shannon_Fano));
                indice += strlen(remove1digit((*info_blocos)->arr[i].Shannon_Fano)) + 1;
            }
        }
        if((*info_blocos)->arr[255].freq != 0){
            sprintf(bufferFinal+indice,"%s", remove1digit((*info_blocos)->arr[255].Shannon_Fano));
            indice += strlen(remove1digit((*info_blocos)->arr[255].Shannon_Fano)); // tirar o + 1 ???
        }
        info_blocos = &((*info_blocos)->prox);   
    }
    sprintf(bufferFinal+indice, "@0");
}

// Faz print dos tamanhos dos blocos
void printTamBlocos(LInt *info_blocos){
    while(*info_blocos) {
        printf("%d", (*info_blocos)->tamanho_bloco);
        if ((*info_blocos)->prox) printf("/");
        info_blocos = &((*info_blocos)->prox); 
    }
}

// Faz print da Hora e Data
void printData(){ 
    struct tm *cache;     
    time_t now;
    time(&now);   
    cache = localtime(&now);
 
    printf("Data:%02d-%02d-%d ; Hora: %02d:%02d:%02d\n", cache->tm_mday, cache->tm_mon+1, cache->tm_year+1900, 
                                                        cache->tm_hour, cache->tm_min, cache->tm_sec);
}

// Faz print da informação essencial do modulo 
void printInfo(LInt info_blocos ,int num_blocos, float tempExec, char *fileOutput){
    printf("Autores: Pedro Miguel Marques Ferreira -> a93303 ; José Luís Alves Fernades -> a93200\nMIEI -> Comunicação Dados ; ");
    printData(); 
    printf("Módulo: t (cálculo dos códigos dos símbolos)\nNúmero de Blocos: %d\nTamanho dos blocos analisados no ficheiro de símbolos: ", num_blocos);
    printTamBlocos(&info_blocos);
    printf(" bytes\nTempo de execução do módulo (milissegundos): %f\nFicheiro gerado: %s\n\n", tempExec, fileOutput);
}

// Função principal do modulo
int modulo_t(char *fileName){
    clock_t tic = clock();

    if(correct_file(fileName, "qerf.")){
        FILE *fp = fopen(fileName, "r");

        if(fp == NULL){
            printf("--> Não foi possível ler o ficheiro! <--");
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

        int tamFinal = 3 + countDigits(num_blocos) + 257*num_blocos + digitsTams + tamanhoBin + 2;
        char bufferFinal[tamFinal + 1];
        writeBuffer(&info_blocos, bufferFinal, num_blocos, file_type);
        
        char *fileOutput = codFile(fileName);

        fclose(fopen(fileOutput,"w"));
        FILE *fpf = fopen (fileOutput, "w");
        
        fwrite(bufferFinal , 1, tamFinal, fpf);
        fclose(fpf);

        clock_t toc = clock();

        float tempExec = ((double)(toc-tic) / CLOCKS_PER_SEC)*1000;

        printInfo(info_blocos, num_blocos, tempExec, fileOutput);
    }
    else printf("--> Tipo de ficheiro incorreto! <--");
}