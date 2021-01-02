#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h> 
#include <stdbool.h>


#define BUF_SIZE 10240

#define BUF_SIZE_COD 256


int modo;

int n_blocks;

int* block_size;

char*** codigos;

char* curr_dados;


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
    int n_blocks;

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
char bytearr_to_byte(char* bytearr){
    int res = 0;
    for(int i = 0; i < 8; i++){
        res += ((int)(bytearr[i] - '0')) * (pow(2,(double) i));
    }
    return (char) res;
}


char* block_compressed(int b, bool dbug){
    int tambloco = block_size[b];

    int byteArrCurr = 0;
    char* byteArr = (char*)malloc(8 * sizeof(char));
    
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
    int* excess = (int*)malloc(bloc_maior * sizeof(int));
    printf("tambloco: %d",tambloco);
    for(int i = 0; i < tambloco; i++){
        char c = curr_dados[i];
        int sizeCodC = sizeCod[(int) c];
        char* codC = codigos[b][(int) c];
        int freeByteArr = 8 - byteArrCurr;

        printf("\ni: %d\nc:%c\nsizeCodC: %d\ncodC: %s\nbyteArrCurr: %d\nfreeByteArr: %d\nbyteArr: %sexcesstam"
            ,i,c,sizeCodC,codC,byteArrCurr,freeByteArr,byteArr);

        if(sizeCodC <= freeByteArr){
            for(int j = 0; j < sizeCodC; j++, byteArrCurr++){
                byteArr[byteArrCurr] = codC[j];
            }
        }else{
            for(int j = 0; j < freeByteArr; j++, byteArrCurr++){
                byteArr[byteArrCurr] = codC[j];
            }

            exc_tam = sizeCodC - freeByteArr;
            for(int j = 0; j < exc_tam; j++){
                excess[j] = codC[j + freeByteArr];
            }
        }
        while(exc_tam != 0){
            for(int j = 0; exc_tam >= 0 && byteArrCurr < 8; j++,exc_tam--,byteArrCurr++){
                byteArr[byteArrCurr] = excess[j];
            }
            if(exc_tam != 0 && byteArrCurr == 8){
                ret[ret_pos] = bytearr_to_byte(byteArr);
                ret_pos++;
                byteArrCurr = 0;
            }
        }
        if(byteArrCurr == 8){
            ret[ret_pos] = bytearr_to_byte(byteArr);
            ret_pos++;
            byteArrCurr = 0;
        }
    }
    free(byteArr);
    return ret;
}





/*
int povoaCods(char* filename){
	codigos = (char **)malloc(256 * sizeof(char *));
    int tam = 0;

	for(int i = 0; i < 256; i++){
		//Code
        

		codigos[i] = (char *)malloc(tam * sizeof(char));
	}
}*/





void print_char_file(char* s){
    
    char *file = "teste.txt";

    FILE *fp = fopenCntrl(file,"w+");

    fputs(s,fp);
    fclose(fp);
}







int main(){
   /* char bytearr[8];

    bytearr[0] = '0';  //1
    bytearr[1] = '1';  //2
    bytearr[2] = '0';  //4
    bytearr[3] = '0';  //8
    bytearr[4] = '0';  //16
    bytearr[5] = '0';  //32
    bytearr[6] = '1';  //64
    bytearr[7] = '0';  //128

    char c = bytearr_to_byte(bytearr);
    print_char_file(c);


    printf("%c\n", c);*/

    curr_dados = "abcbdbcbabdbcbdbcbabacdbacdaabcbddaaaabbcbcaaaaaaabcbcbdacabbaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbccccccccccddddddbcbdbabdbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbccccddddddddddbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbcccccccdbabaaababaacacdaddcababababababababbababababababababbababcdcdcdcdbababdccdbacddcbacdbacdbccdbabbabbdbbdbabbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbdbcbdcdbcdbcbdbbcbabcbdbcbabdbcbdbcbabacdbacdaabcbddaaaabbcbcaaaaaaabcbcbdacabbaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbccccccccccddddddbcbdbabdbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbccccddddddddddbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbcccccccdbabaaababaacacdaddcababababababababbababababababababbababcdcdcdcdbababdccdbacddcbacdbacdbccdbabbabbdbbdbabbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbdbcbdcdbcdbcbdbbcbcabcbdbcbabdbcbdbcbabacdbacdaabcbddaaaabbcbcaaaaaaabcbcbdacabbaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbccccccccccddddddbcbdbabdbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbccccddddddddddbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbcccccccdbbaaababaacacdddcababababababababbababababababababbababcdcdcdcdbababdccdbacddcbacdbacdbccdbabbabbdbbdbabbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbdbcbdcdbcdbcbdbbcbcabcbdbcbabdbcbdbcbabacdbacdaabcbddaaaabbcbcaaaaaaabcbcbdacabbaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbccccccccccddddddbcbdbabdbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbccccddddddddddbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbcccccccdbabaaababaacacdaddcababababababababbababababababababbababcdcdcdcdbababdccdbacddcbacdbacdbccdbabbabbdbbdbabbbbbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbdbcbdcdbcdbcbdbbcbabcbdbcbabdbcbdbcbabacdbacdaabcbddaaaabbcbcaaaaaaa";
    
    char* filecod = "teste.txt.cod";
    initCOD(filecod, true);
    char* ret = block_compressed(0, true);
    FILE *fp = fopenCntrl("output_teste.txt","r+");
    fputs(ret,fp);

	return 0;
}

