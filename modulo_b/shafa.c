#include "modulo_t.h"
#include <string.h>

int main(int argc, char *argv[]){
    if (argc==4 && strcmp(argv[2],"-m") && !strcmp(argv[3],"t")){
        modulo_t(argv[1]);
    }
    else printf("\n-> Input incorreto <-\n\n");

    return 0;
}