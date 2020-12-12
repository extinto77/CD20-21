#include <stdio.h>

typedef struct lligada {
    int nBloco;
    int tamanho_Bloco;
    int *freq[255];
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
        int num_Blocos;

        fscanf(fp, "@%c@%d@", &file_type, &num_Blocos);

        LInt info_Blocos = criar_lista(); //criar função 
        LInt *inicio_info_Blocos = info_Blocos;


        //while(fp) ver se é necessário, not sure

        for(int nb = 1; nb<=num_Blocos; nb++){
            info_Blocos->nBloco = nb;
            fscanf(fp, "%d@", &info_Blocos->tamanho_Bloco);
            
            for(int i=0; i<=255; i++){ //caso particular do ;; em que valor da freq é igual ao anterior
                fscanf(fp, "%d", &info_Blocos->freq[i]);
                fseek(fp, 1, SEEK_CUR);
            }
            info_Blocos->prox = criar_lista(); 
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