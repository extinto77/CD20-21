#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modulo_b/modulo_t.h"
#include "modulo_a/modulo_a.h"
/* 
#include "modulo_a/modulo_.h"
#include "modulo_c/modulo_.h"
#include "modulo_d/modulo_.h"
 */

/* 
shafa filename -m t -b x -c r
  0       1     2 3  4 5  6 7
*/

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


