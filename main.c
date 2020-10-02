#include <stdio.h>
#include <stdlib.h>

#include "lib/Graph_module/ISPs.h"

int main(int argc,char const *argv[]) {
    FILE *fp_preview,*fp;

    /*fp_preview = fopen(argv[1], "r"); //abrir o ficheiro a ser analisado
    if (fp_preview == NULL || argc != 2) {
        return EXIT_FAILURE;
    }*/

    fp_preview=fopen("../lib/Assets/pdf_example.txt","r");
    if (fp_preview == NULL) {
        return EXIT_FAILURE;
    }

    fp=fopen("../lib/Assets/pdf_example.txt","r");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }

    /*fp = fopen(argv[1], "r"); //abrir o ficheiro a ser analisado
    if (fp == NULL || argc != 2) {
        return EXIT_FAILURE;
    }*/

    read_ISP(fp_preview,fp);

    fclose(fp_preview); //fecha o ficheiro apos ser analisado
    fclose(fp); //fecha o ficheiro apos ser analisado

    return 0;
}
