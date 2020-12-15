#include <stdio.h>
#include <stdlib.h>


typedef struct lligada { //Struct da Lista ligada de blocos que prefazem um ficheiro
    int nbloco; //número do bloco
    int tamanho_bloco; //tamano do bloco
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
                }else{
                    info_blocos->freq[i] == ant_freq;
                }
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



int i==0;
    while (i<=(separar_prob(v[]))) {
        v[i]->adiciona_zero//fazer
    }
    while (v[i] && i>(separar_prob(v[]))) {
        v[i]->adiciona_um//fazer
    }


int separar_prob(v[]) {//retorna o n indice que a probabilidade se aproxima mais de 50%
int cima, baixo, first=0/*indice do primeiro elemento do array*/, last=/*indice do ultimo elemento do array*/; 
cima==v[first];
baixo==v[last];
    for(){
        if (baixo<cima) baixo+= v[last--];
        else cima+= v[first++];
    }
    return first;
}
