#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "modulo_t.h"


int main(int argc, char *argv[]){
    char *filename = argv[1];
    char *arg1 = argv[2];
    char modulo = argv[3];
    char *arg2 = argv[4];
    char forceRLE = argv[5];
    
    if(strcmp(arg1, "-m") == 2){
        switch (modulo){
        case 'f':
            
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

}