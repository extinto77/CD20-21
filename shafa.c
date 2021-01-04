#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modulo_t.h"
#include "modulo_a.h"


int main(int argc, char *argv[]){
    char *filename = argv[1];
    char *arg1 = argv[2];
    char modulo = *argv[3];
    

    char forceRLE = '0';
    char tamanhoBloco = 'D';


    int i;
    for(i = 2; i < argc; ++i){
        if(argv[i][1] == 'c'){
            forceRLE = '1'; ++i; 
        }
        else if(argv[i][1] == 'b'){
            ++i;
            switch(argv[i][0]){
                case 'K':
                    tamanhoBloco = 'K';
                    break;
                case 'm':
                    tamanhoBloco = 'm';
                    break;
                case 'M':
                    tamanhoBloco = 'M';
                    break;
                default:
                    tamanhoBloco = 'D';
            }
       
        }
    }

    if(strcmp(arg1, "-m") == 0){
        switch (modulo){
        case 'f':
            
            moduloA(filename, forceRLE, tamanhoBloco);
      
            break;
            
            
        case 't':
            modulo_t(filename);
            break;
        case 'c':
            break;
        case 'd':
            break;
        default:
            printf("Input errado!");
            break;
        }
    }
    return 0;
}


