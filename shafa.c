#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "modulo_t.c"


int main(int argc, char *argv[]){
    char line[1024];

    scanf ("%s", &line);//ler do terminal ou dá como input??
    
    if (correct_file())
    {
        /* code */
    }
}


/*
strcmp returns 0 if str1 = str2
strcmp returns 1 if str1 > str2
strcmp returns -1 if str1 < str2
*/
