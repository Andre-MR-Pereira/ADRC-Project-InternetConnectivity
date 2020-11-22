#include "printFile.h"

void printFile(char* name, int* vect, int size)
{
    FILE* fp = NULL;

    fp = fopen(name, "w");

    for (int i = 0; i < size; ++i)
        fprintf(fp, "%d\n", vect[i]);

    fclose(fp);
}
