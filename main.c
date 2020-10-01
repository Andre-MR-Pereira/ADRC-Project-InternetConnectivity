#include <stdio.h>
#include <stdlib.h>



int main(int argc,char const *argv[]) {
    FILE *fp;

    fp = fopen(argv[1], "r"); //abrir o ficheiro a ser analisado
    if (fp == NULL || argc != 2) {
        return EXIT_FAILURE;
    }

    fclose(fp); //fecha o ficheiro apos ser analisado

    return 0;
}
