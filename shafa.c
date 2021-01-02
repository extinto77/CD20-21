#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modulo_b/modulo_t.h"
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
    
    if(strcmp(arg1, "-m") == 0){
        switch (modulo){
        case 'f':
            char tam = 'D';

            if (argc>6) {
                tam = argv[5];
                if ( strcmp(argv[6],"-c") && strcmp(argv[7],"r") ) moduloA(filename, 1, tam);
                else moduloA(filename, 0, tam);
            }
            if (argc>4){
                if ( strcmp(argv[4],"-b") ){
                    tam = argv[5];
                    moduloA(filename, 0, tam);
                }
                if ( strcmp(argv[4],"-c") && strcmp(argv[5],"r") ) moduloA(filename, 1, tam);
            }
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


