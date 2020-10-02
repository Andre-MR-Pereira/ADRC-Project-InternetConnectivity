#include "ISPs.h"

void read_ISP(FILE *fp_preview,FILE *fp){
    int max_node_value=1,tail,head,mode;

    while(fscanf(fp_preview,"%d %d %d",&tail,&head,&mode)!=EOF){
        printf("Entrou\n");
        if(tail>max_node_value){
            max_node_value=tail;
        }
    }
    printf("Máximo:%d\n",max_node_value);
    return;
}