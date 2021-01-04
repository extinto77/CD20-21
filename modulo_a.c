
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


#define FSIZE_DEFAULT_BLOCK_SIZE 524288         // Default block size = 512 KBytes
#define FSIZE_MIN_BLOCK_SIZE 512                // Min block size = 512 Bytes
#define FSIZE_MAX_BLOCK_SIZE 67108864           // Max block size = 64 MBytes
#define FSIZE_MAX_NUMBER_OF_BLOCKS 4294967296   // Max number of blocks that can be returned = 2^32 blocks
#define FSIZE_MAX_SIZE_FSEEK 2147483648         // Max size permitted in fseek/ftell functions = 2 GBytes
#define FSIZE_ERROR_BLOCK_SIZE -1               // Error: Block size is larger than max value
#define FSIZE_ERROR_NUMBER_OF_BLOCKS -2         // Error: Number of Blocks exceeds max value permitted
#define FSIZE_ERROR_IN_FILE -3                  // Error: Opening or reading file
#define FSIZE_ERROR_IN_FTELL -1L                // Error: When using ftell()

long long fsize(FILE *fp_in, unsigned char *filename, unsigned long *the_block_size, long *size_of_last_block)
{
    unsigned long long total;
    long long n_blocks;
    unsigned long n_read, block_size;
    unsigned char *temp_buffer;
    int fseek_error;
    FILE *fp;

    block_size = *the_block_size;
    if (block_size > FSIZE_MAX_BLOCK_SIZE) return (FSIZE_ERROR_BLOCK_SIZE);
    if (block_size == 0UL) block_size = FSIZE_DEFAULT_BLOCK_SIZE;
    if (block_size < FSIZE_MIN_BLOCK_SIZE) block_size = FSIZE_MIN_BLOCK_SIZE;
    *the_block_size = block_size;

    if (filename == NULL || *filename == 0) fp = fp_in;
    else
    { fp = fopen(filename, "rb");
      if (fp == NULL) return (FSIZE_ERROR_IN_FILE);
    }

    fseek_error = fseek(fp, 0L, SEEK_SET);
    if (fseek_error) return (FSIZE_ERROR_IN_FILE);

    fseek_error = fseek(fp, 0L, SEEK_END);
    if (!fseek_error)
    { total = ftell(fp);
      if (total == FSIZE_ERROR_IN_FTELL) return (FSIZE_ERROR_IN_FILE);
      n_blocks = total/block_size;
      if (n_blocks*block_size == total) *size_of_last_block = block_size;
      else
      { *size_of_last_block = total - n_blocks*block_size;
        n_blocks++;
      }
      fseek_error = fseek(fp, 0L, SEEK_SET);
      if (fseek_error) return (FSIZE_ERROR_IN_FILE);
      else return(n_blocks);
    }

    n_blocks = FSIZE_MAX_SIZE_FSEEK/block_size-1; // In reality fseek() can't handle FSIZE_MAX_SIZE_FSEEK of 2GBytes, so let's use a smaller size
    fseek_error = fseek(fp, n_blocks * block_size, SEEK_SET);
    if (fseek_error) return (FSIZE_ERROR_IN_FILE);

    temp_buffer = malloc(sizeof(unsigned char)*block_size);
    do
    { n_blocks++;
      n_read = fread(temp_buffer, sizeof(unsigned char), block_size, fp);
    } while (n_read == block_size && n_blocks <= FSIZE_MAX_NUMBER_OF_BLOCKS);

    free(temp_buffer);
    if (n_blocks > FSIZE_MAX_NUMBER_OF_BLOCKS) return(FSIZE_ERROR_NUMBER_OF_BLOCKS);

    if (n_read == 0L)
    { *size_of_last_block = block_size;
      n_blocks--;
    }
    else *size_of_last_block = n_read;

    if (filename == NULL || *filename == 0)
    { fseek_error = fseek(fp, 0L, SEEK_SET);
      if (fseek_error) return (FSIZE_ERROR_IN_FILE);
    }
    else fclose(fp);

    return(n_blocks);
}

//Função que devolve o tamanho do bloco para análise
int funcaotamanho_bloco (char t){
    int tamanho;

    if (t=='K') tamanho= 655360;
    else if (t=='m') tamanho=8388608;
    else if (t=='M') tamanho=67108864;
    else tamanho = 65536;

    return tamanho;
}

//Função que devolve o número de bytes do ficheiro
long funcaotamanho_ficheiro(const char* ficheiro)
{
    long tamanho;
    FILE *f;
 
    f = fopen(ficheiro, "rb");
    if (f == NULL) return -1;
    fseek(f, 0, SEEK_END);
    tamanho = ftell(f);
    fclose(f);
 
    return tamanho;
}

//Função que comprime o ficheiro
int compressao (char* ficheiro, char* lista, unsigned long tamanhobloco, int bloco){



   //abrir em wb, fechar , e abrir em ab
FILE *fp;
// fclose(fopen(nomeFicheiro, "wb")); //limpar ficheiro e escrever em modo ab
 fp = fopen(ficheiro, "ab");


fseek(fp, (tamanhobloco*bloco),SEEK_SET);

int i = 0;
char atual = lista[i];
char anterior;
int c = 0;
int carateres = 0;


for ( i; lista[i]; i++) {
   anterior = atual;
   atual = lista[i+1];
   if (i==0) fputc(anterior,fp);
   if (atual == anterior) c++;
   else {
       if (c >= 4 ){
        fputc('\0',fp);
        fputc (anterior,fp);
        fputc(c,fp);
        
        c = 1;
        carateres +=3;

           }
        else {
            while (c != 0) {
               fputc(anterior, fp);
               c--;
               carateres++;
       }
        c = 1;
   }
   }
}


fclose(fp);

int taxa;


taxa= 100*(i-carateres)/i;



return taxa;

}



char* novaLista (char* ficheiro, unsigned long tamanho_bloco, int bloco, unsigned long long tamanhoficheiro){
 int i = 0;
 char* lista = (char*)malloc(tamanho_bloco+1);
 FILE* fp = fopen(ficheiro, "rb");
 
 fseek(fp,( tamanho_bloco * bloco), SEEK_SET);
 fread (lista, tamanho_bloco,1,fp);
 lista[tamanho_bloco] = '\0';

 return lista;
}
char* ultimaLista (char* ficheiro, unsigned long size_of_last_block,int bloco,unsigned long block_size){
  int i = 0;
 char* lista = (char*)malloc(size_of_last_block+1);
 FILE* fp = fopen(ficheiro, "rb");
 
 fseek(fp,( block_size * bloco), SEEK_SET);
 fread (lista, size_of_last_block,1,fp);
 lista[size_of_last_block] = '\0';



 return lista;
}

int** novaMatriz(char* ficheiro, long long numeroblocos){
 int** matriz = malloc(sizeof(int)* numeroblocos);
 int i;
 for (i = 0; i < numeroblocos; i++) matriz[i] = malloc(sizeof (int)*256);
int j;
 for (j=0; j < numeroblocos; j++){
   for (i = 0; i<256; i++){
     matriz[j][i] = 0;
   }
 }
 return matriz;
}

void frequencia (char * ficheiro, char compressao, unsigned long long tamanho_ficheiro, unsigned long size_of_last_block,long long numeroblocos, unsigned long tamanhobloco, int bloco,int **m){

/**  
int f = 0;
for (f;lista[f];f++){
  m[bloco][lista[f]]++;
} **/

char nomeFicheiro[200];
strcpy (nomeFicheiro,ficheiro);
char* extensaoFreq = ".freq";
strcat(nomeFicheiro, extensaoFreq);
  

FILE *fp;
 // fclose(fopen("teste2", "wb")); limpar ficheiro e escrever em modo ab
 fp = fopen(nomeFicheiro, "ab");

fprintf(fp,"@%c",compressao);
fprintf(fp,"@%lld",numeroblocos);

if (numeroblocos == 1 ){
  fprintf (fp, "@%lu@", tamanhobloco);
  int i =0;
  for (i; i< 256;i++){
    fprintf(fp,";");
    if (m[0][i] == m[0][i-1]) fprintf(fp,";");
    else fprintf(fp,"%d;", m[0][i-1]);
  }
}else{
  int j,k=0;
  for (j;j<numeroblocos-1;j++){
    fprintf(fp,"@%lu@",tamanhobloco);
    for (k; k< 256;k++){
    fprintf(fp,";");
    if (m[j][k] == m[j][k-1]) fprintf(fp,";");
    else fprintf(fp,"%d;", m[j][k]);
  }
  }
  fprintf (fp, "@%lu@", size_of_last_block);
  int p = 0;
  for (p; p< 256;p++){
    fprintf(fp,";");
   // if (m[j][p] == m[j][p-1]) fprintf(fp,";");
   //else fprintf(fp,"%d;", m[j][p]);
}
}
fprintf(fp, "@0");
fclose(fp);

}

int printinfo(long long n_blocks,unsigned long block_size, double time_spent,unsigned long size_of_last_block,int taxafinal){

    printf ("\n Daniel a93292 e Isabela a90723 MIEI/CD, 03-JAN-2021 ");
    printf ("\n Módulo: f (cálculo das frequências dos símbolos");
    printf("\n Número de blocos: %llu ", n_blocks);
    printf("\n Tamanho dos blocos analisados no ficheiro original: %lu", block_size);
    printf("\n Tamanho do último bloco analisado no ficheiro original: %lu",size_of_last_block);
    printf("\n Compressão RLE: aaa.rle | Taxa compressão: %d",taxafinal);
    printf("\n Tempo de execução do módulo (milissegundos): %f ", time_spent);
    printf("\n Ficheiros gerados: aaa.txt.rle aaa.txt.freq");
    return 0;
  }




  int moduloA (char* ficheiro, char forceRLE, char tamanhobloco){

  
     clock_t begin = clock();
     
     unsigned long long total;
    long long n_blocks;
    unsigned long size_of_last_block, block_size;
    FILE *fp;

    // Using function fsize() when file is already opened
    fp = fopen("aaa.txt", "rb");
    block_size = funcaotamanho_bloco(tamanhobloco);
    n_blocks = fsize(fp, NULL, &block_size, &size_of_last_block);
    total = (n_blocks-1) * block_size + size_of_last_block;
   

    
    fclose(fp);

       int bloco = 0;
       int c =0; 
       
       char* lista = novaLista(ficheiro, block_size, bloco, total);
       int** matriz = novaMatriz(ficheiro,n_blocks); 
       char* nomeFicheiro= malloc (sizeof(char)*100);


      strcpy (nomeFicheiro,ficheiro);
      char* extensaoRLE = ".rle";
      strcat(nomeFicheiro, extensaoRLE);


       int percentagem = compressao (nomeFicheiro,lista, block_size, bloco);
      bloco++;  

    if (forceRLE == '1'){
    while(bloco < n_blocks-1){   
      char* listaFRLE = novaLista(ficheiro, block_size, bloco, total);
      compressao (nomeFicheiro,listaFRLE, block_size, bloco);
      char letra = 'R';
      frequencia (nomeFicheiro,letra, total, size_of_last_block, n_blocks, block_size,bloco, matriz);
      bloco++;
    
    free(listaFRLE);
    }



    char* ultimobloco = ultimaLista (ficheiro, size_of_last_block,bloco,block_size);
    int taxafinal= compressao (nomeFicheiro,ultimobloco, size_of_last_block, bloco);
    

    }
    else {
      

      if (percentagem >= 5) {
       while (bloco < n_blocks-1){

          char* lista2 = novaLista(ficheiro, block_size, bloco, total);
          compressao(ficheiro,lista2, block_size,bloco);
          char letra = 'R';

          frequencia (ficheiro,letra, total, size_of_last_block, n_blocks, block_size,bloco, matriz);
          bloco ++;
          free(lista2);
          
      }
         char* ultimobloco = ultimaLista (ficheiro, size_of_last_block,bloco,block_size);
         int taxafinal= compressao (nomeFicheiro,ultimobloco, size_of_last_block, bloco);
    }else{
      char letra = 'N';

      frequencia (ficheiro,letra, total, size_of_last_block, n_blocks, block_size,bloco, matriz);
    }
    }


   fclose(fp);
   
   clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  

  printinfo(n_blocks,block_size,time_spent,size_of_last_block,percentagem);

  return 0;

}