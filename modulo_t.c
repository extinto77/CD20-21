#include <stdio.h>
#include <stdlib.h>
#include <time.h> //vem daqui : clock(), CLOCKS_PER_SEC e clock_t

 clock_t t; //variável para armazenar tempo

 double t = clock(); //armazena tempo

//inserir a função

 t = clock() - t; // tempo final - tempo inicial
 printf("Tempo de execucao do módulo (milissegundos): %lf", (t/(CLOCKS_PER_SEC/1000));


 
typedef struct lligada { //Struct da Lista ligada de blocos que prefazem um ficheiro
    int nbloco; //número do bloco
    int tamanho_bloco; //tamanho do bloco
    int *freq[255]; //frequência de cada símbolo
    struct lligada *prox;
} *LInt;



int modulo_t(char *fileName){
    if(correct_file(fileName, "qerf.")){
        FILE *fp = fopen(fileName, "r+"); //dont't forget to close file

        if(fp == NULL){
            printf("Não foi possível ler o ficheiro!");
            return 0;
        }

        char file_type;
        int num_blocos;
        int ant_freq;

        fscanf(fp, "@%c@%d@", &file_type, &num_blocos);

        LInt info_blocos = criar_lista(); //criar função    
        //acrescentar 0 (*10)
        //acrescentar 1 (*10+1)

        LInt *inicio_info_blocos = info_blocos;


        //while(fp) ver se é necessário, not sure

        for(int nb = 1; nb<=num_blocos; nb++){
            info_blocos->nbloco = nb;
            fscanf(fp, "%d@", &info_blocos->tamanho_bloco);
            
            for(int i=0; i<=255; i++){ //caso particular do ;; em que valor da freq é igual ao anterior
                if(fscanf(fp, "%d", &info_blocos->freq[i]) == 1){
                    ant_freq == info_blocos->freq[i];
                    fseek(fp, 1, SEEK_CUR);
                } else info_blocos->freq[i] == ant_freq;
            }
            info_blocos->prox = criar_lista();
        }

        fclose(fp);
    }else printf("Tipo de ficheiro incorreto!");

}



int correct_file (char s1[], char s2[]){
    int i, j=0, ans=0;

    for(i=0;s1[i];i++);

    for(i--,j; s2[j],s1[i]==s2[j]; i--,j++);

    if(!s2[j]) ans = 1; //s2[j]=='\0'

    return ans;
}

criar_lista()





//----------Diarreias Mentais Extinto----------

int i==0;
    while (i<=(separar_prob(v[]))) {
        int val = v[i->codigo]; // v[i->codigo] == (v[i->codigo])*10;
        val = val*10;
        v[i->codigo]==val;
    }
    while (v[i] && i>(separar_prob(v[]))) {
        int val = v[i->codigo];
        val =val*10;
        v[i->codigo]==val;
    }

int add_zero {

}


int separar_prob(v[n]) {//retorna o n indice que a probabilidade se aproxima mais de 50%, sabendo que as freq estao oeganizadas decrescente
int cima, baixo, first=0, last=n; 
cima==v[first];
baixo==v[last];
    while(v[i] && first<last){
        if (baixo<cima) baixo+= v[last--];
        else cima+= v[first++];
    }
    return first;
}



typedef struct Ligacao{ //optar com um array com estas 3 informações do que array ("int *freq[255];") ou matriz
    int simbolo;//ASCII
    int codigo;
    int freq;
    struct Ligacao* proximo;
}Ligacao;

Dado *inicio = NULL, *fim = NULL;

freqDecrescente (e) { //
    Ligacao *e1 = e1;

    while (e1){
        Ligacao *e2 = e1->proximo;
        while (e2){
            if (e1->freq < e2->freq) { //se menor a ordem desses dois
                
                //trocar apontadores de e1 e e2

                /*int temporario = e1->freq; 
                e1->freq = e2->freq;
                e2->freq = temporario;*/
            }
            //e2 = e2->proximo;
        }
        //e1 = e1->proximo;
    }
}

