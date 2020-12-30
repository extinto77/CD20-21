#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h> 




/*
if((file=fopen("C:\\Users\\ste\\Desktop\\file.txt", "r"))==NULL) 
{
    printf("Cannot open file.\n");
    puts(strerror(errno));

    getchar();
    exit(1);
}*/

char** codigos;

char* rawCodigos;

char* dados;

int tam;

int bytearr[8]; 


//Tranforma o bytearray no byte(char) coorespondente; 
char bytearr_to_byte(){
	int res = 0;
	for(int i = 0; i < 8; i++){
		res += bytearr[i] * (pow(2,(double) i));
	}
	return (char) res;
}



int povoaCods(String filename){
	codigos = (char **)malloc(256 * sizeof(char *));
    int tam = 0;

	for(int i = 0; i < 256; i++){
		/* codigo */
        

		codigos[i] = (char *)malloc(tam * sizeof(char));
	}
}



void print_char_file(char c){
    
    char *file = "teste.txt";


    FILE *fp;
    if((fp=fopen("file.txt", "w+"))==NULL) {
        printf("Impossivel abrir ficheiro.\n");
        puts(strerror(errno));

        exit(1);
    }

    fputs("abcdef",fp);
    fclose(fp);
}







int main(){


    bytearr[0] = 0;  //1
    bytearr[1] = 1;  //2
    bytearr[2] = 1;  //4
    bytearr[3] = 1;  //8
    bytearr[4] = 1;  //16
    bytearr[5] = 0;  //32
    bytearr[6] = 0;  //64
    bytearr[7] = 0;  //128

    char c = bytearr_to_byte();
    print_char_file(c);


    printf("%c\n", c);

	return 0;
}