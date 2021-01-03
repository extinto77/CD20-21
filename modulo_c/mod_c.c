#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h> 
#include <stdbool.h>


#define BUF_SIZE 1048576

#define BUF_SIZE_COD 256

FILE *fpoutput;

int modo;

int n_blocks;

int* block_size;

int block_size_comp;

char*** codigos;

char* curr_dados;



char* concat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


FILE* fopenCntrl(char* filename, char* mode){
    FILE *fp;
    if((fp=fopen(filename, mode))==NULL){
        printf("Impossivel abrir ficheiro %s.\n",filename);
        exit(1);
    }
    return fp;
}




int initCOD(char* filecod, bool dbug){
    FILE* fp = fopenCntrl(filecod,"r");
    char m;

    char cod_buf[BUF_SIZE];


    fscanf(fp,"@%c@%d@",&m,&n_blocks);
    
    if(dbug) printf("modo: %c\nnumBloc: %d\n",m,n_blocks);


    if(m == 'N') modo = 0;
    else if(m == 'R') modo = 1; 
    else{
        printf("Modo inválido!\n");
        return 1;
    } 

    fgets(cod_buf,BUF_SIZE,fp);
    
    fclose(fp);

    if(dbug) printf("cod_buf: %s\n",cod_buf);

    char* src;

    int nAts = ((n_blocks*2)+1);

    char** parsing = (char **)malloc(nAts * sizeof(char *));

    const char s[2] = "@";

    int it = 1;

    src = strtok(cod_buf,s);

    if(dbug) printf("src: %s\n",src);

    parsing[0] = src;

    while((src = strtok(NULL,"@"))!=NULL){
        parsing[it] = src;

        strcpy(parsing[it],src);
        it++;
    }
    if(dbug){for(int i = 0; i < nAts; i++){
        printf("parsing %d: %s\n",i,parsing[i]);
    }}

    block_size = (int*)malloc(n_blocks * sizeof(int));

    codigos = (char ***)malloc(n_blocks * sizeof(char **));

    for (int i = 0; i < n_blocks; ++i){
        codigos[i] = (char **)malloc(256 * sizeof(char *));
    }
    
    if(dbug) printf("MALLOC!\n");
    
    char *ptr = (char *)malloc(BUF_SIZE_COD * sizeof(char));
  
    for(int i = 0, j = 0; i < n_blocks*2; i++){
        if(i % 2 == 0){
            block_size[j] = (int) strtol(parsing[i], &ptr, 10);
            
            j++;
        }else{
            

            int pos = 0;
            for(int ii = 0; ii < 256; ii++){
                codigos[i/2][ii] = &parsing[i][pos];
                while(parsing[i][pos] != ';' && parsing[i][pos] != '\0') pos++;
                parsing[i][pos] = '\0';
                pos++;
            }

        }        
        
    }

    if(dbug){
        for(int i = 0; i < n_blocks; i++){
            for (int j = 0; j < 256; j++){
                if(strcmp(codigos[i][j],"")) printf("bloco: %d cod: %d cont: %s\n",i,j,codigos[i][j]);
                else printf("bloco: %d cod: %d cont: VAZIO\n",i,j);
            } 
            printf("\nENDBLOCK %d\n\n",i);
        }
        for(int i = 0; i < n_blocks; i++){
            printf("block_size %d: %d\n",i,block_size[i]);

        }
    }


    return 0;
}

//Tranforma um bytearray no byte(char) coorespondente; 
char bytearr_to_byte(char* bytearr, bool debug){
    int res = 0;
    int mult = 1;
    if(debug) printf("\n\n\n\nBYTEARR: %s\n\n",bytearr);
    for(int i = 0; i < 8; i++){
        res += mult * ((int)bytearr[7-i] - '0');
        mult *= 2;
    }
    if(debug)printf("res:%d\n\n\n\n\n",res );
    return (char) res;
}


char* block_compressed(int b, bool dbug, int* block_size_comp_arr){

    int tambloco = block_size[b];

    int byteArrCurr = 0;
    char* byteArr = (char*)malloc(9 * sizeof(char));
    
    byteArr[8] = '\0';
    int ret_pos = 0;    
    char* ret = (char*)malloc(tambloco * sizeof(char));

    int bloc_maior = 0;

    int sizeCod[256];

    for(int i = 0; i < 256; i++){
        int strl = strlen(codigos[b][i]);
        sizeCod[i] = strl;
        if(strl > bloc_maior) bloc_maior = strl;
        if(dbug)printf("sizeCod[%d]: %d bloc_maior: %d\n",i,sizeCod[i],bloc_maior); 
    }


    int exc_tam = 0;
    char* excess = (char*)malloc(bloc_maior * sizeof(char));
    if(dbug)printf("tambloco: %d",tambloco);
    for(int i = 0; i < tambloco; i++){
        unsigned char c = curr_dados[i];
        int sizeCodC = sizeCod[(int) c];
        char* codC = codigos[b][(int) c];
        int freeByteArr = 8 - byteArrCurr;

        if(dbug)printf("\n\ncurr_dados: %s\ncurrdados: %02hhx %02hhx %d\ni: %d\nc:%d\nsizeCodC: %d\ncodC: %s\nbyteArrCurr: %d\nfreeByteArr: %d\nbyteArr: %s\nexcesstam: %d\nexcess: %s\n\n"
            ,curr_dados,(unsigned char) curr_dados[i],(unsigned char) curr_dados[i+1],curr_dados[i+1],i,c,sizeCodC,codC,byteArrCurr,freeByteArr,byteArr,exc_tam,excess);

        if(sizeCodC <= freeByteArr){
            for(int j = 0; j < sizeCodC; j++, byteArrCurr++){
                byteArr[byteArrCurr] = codC[j];
            }
        }else{
            for(int j = 0; j < freeByteArr; j++){
                byteArr[byteArrCurr] = codC[j];
                byteArrCurr++;
                if(dbug)printf("(else) byteArr: %s\nbyteArrCurr: %d\n",byteArr,byteArrCurr);
            }

            exc_tam = sizeCodC - freeByteArr;
           if(dbug) printf("(else) exc_tam: %d\n", exc_tam);
            for(int j = 0; j < exc_tam; j++){
                excess[j] = codC[j + freeByteArr];
            }

                if(dbug)printf("(else) excess: %s\n",excess);
        }
        if(byteArrCurr == 8){
            ret[ret_pos] = bytearr_to_byte(byteArr, dbug);
            ret_pos++;
            byteArrCurr = 0;
            if(dbug)printf("byteArr: %s\nret: %c\nret_pos1: %d\n",byteArr,ret[ret_pos],ret_pos);
        }
        while(exc_tam > 0){
            if(dbug)printf("bytearr_pre: %s\nbyteArrCurr_pre: %d\nexec_tam_pre: %d\n\n",byteArr,byteArrCurr,exc_tam);
            for(int j = 0; exc_tam > 0 && byteArrCurr < 8; j++,exc_tam--,byteArrCurr++){
                byteArr[byteArrCurr] = excess[j];
            }
            

            if(dbug)printf("bytearr_pos: %s\nbyteArrCurr_pos: %d\nexec_tam_pos: %d\n\n",byteArr,byteArrCurr,exc_tam);
            if(exc_tam > 0 && byteArrCurr > 7){
                ret[ret_pos] = bytearr_to_byte(byteArr,dbug);
                ret_pos++;
                byteArrCurr = 0;
            }
        }
        if(byteArrCurr == 8){
            ret[ret_pos] = bytearr_to_byte(byteArr,dbug);
            ret_pos++;
            byteArrCurr = 0;

            if(dbug)printf("ret2: %s\nret_pos2: %d\n",ret,ret_pos);
        }
        if(i+1 == tambloco && byteArrCurr > 0){
            for(int j = byteArrCurr; j < 8; j++){
                byteArr[j] = '0';
            }
            ret[ret_pos] = bytearr_to_byte(byteArr,dbug);
            ret_pos++;
            byteArrCurr = 0;
        }
    }

    ret[ret_pos+1]='\0';
    block_size_comp = ret_pos++;
    int aux = block_size_comp;
    block_size_comp_arr[b] = aux;
    if(dbug)printf("block_size_comp[%d]: %d\n",b,block_size_comp);
    return ret;
}




void put_out_file(int tam, char* bloco_comp){
    fprintf(fpoutput, "@%d@",tam);
    for(int i = 0; i < tam; i++){
        fputc(bloco_comp[i],fpoutput);
    }
}


void printData(float t,char* f_in, char* f_out,int* block_size_comp_arr){
    int tamanho_tot_in = 0;
    int tamanho_tot_out = 0;
    
    
    printf("Módulo: c (codificação dum ficheiro de símbolos)\n");
    printf("Ficheiro input: %s\n", f_in);
    printf("Número de blocos: %d\n",n_blocks);

    for(int i = 0; i < n_blocks; i++){
        int tam_in = block_size[i];
        int tam_out = block_size_comp_arr[i];
        tamanho_tot_in += tam_in;
        tamanho_tot_out += tam_out;

        printf("Tamanho original do bloco %d: %d \n",i+1,tam_in);
        printf("Tamanho comprimido do bloco %d (Taxa de Compressão): %d (%f%%)\n",i+1,tam_out,(100-(((float)tam_out/tam_in)*100)));
    }

    



    printf("Tamanho original do ficheiro : %d\n",tamanho_tot_in);
    printf("Tamanho ficheiro comprimido (Taxa de Compressão) %d (%f%%)\n",tamanho_tot_out,(100-(((float)tamanho_tot_out/tamanho_tot_in)*100)));
    printf("Tempo de execução: %fs\n",t);
    printf("Ficheiro gerado: %s\n",f_out);
}



int modulo_c(char* fileinput){
    bool debug = false;

    clock_t tic = clock();

    FILE *fpdata = fopenCntrl(fileinput,"r");


    char* fileoutput = concat(fileinput,".shaf");
    fpoutput = fopenCntrl(fileoutput,"w+");
    

    char* filecod = concat(fileinput,".cod");

    initCOD(filecod, debug);
     
    fprintf(fpoutput, "@%d", n_blocks);


    int* block_size_comp_arr = (int*)malloc(n_blocks * sizeof(int));

    for(int i = 0; i < n_blocks; i++){
        curr_dados = (char *)malloc((block_size[i]+1)*sizeof(char));
        fread(curr_dados,1,block_size[i]+1,fpdata);
        char *bloco_comp = block_compressed(i,debug, block_size_comp_arr);
        put_out_file(block_size_comp,bloco_comp);
    }

    fclose(fpoutput);

    clock_t toc = clock();

    float tempExec = ((double)(toc-tic) / CLOCKS_PER_SEC);
    printData(tempExec,fileinput,fileoutput,block_size_comp_arr);


	return 0;
}

