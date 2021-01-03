#include "modulo_t.h"
#include <string.h>

int main(int argc, char *argv[]){
    if(argc == 4){
        char *filename = argv[1];
        char *arg1 = argv[2];
        char modulo = *argv[3];

        if(strcmp(arg1, "-m")==0 && modulo == 't') modulo_t(filename);
    }else printf("\n-> Input incorreto <-\n\n");

    return 0;
}