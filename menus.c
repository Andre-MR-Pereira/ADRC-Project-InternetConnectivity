#include "menus.h"

//Apresentação do menu inicial
void showInitMenu (List** ISP_graph,int* top_f, int max_node_value,int* list_top,int count_f,int true_size) {
    int option = 0,source_node=0,destination_node=0;
    char path_mode;
    char** all_path_types;

    while(true){
        printf("\n=================[Menu]=================\n---Please select one of the following---\n\n\n1.  Determine if input internet is connected.\n2.  Determine if input internet is linkbiconnected.\n3.  Determine if input internet is commercially acyclic.\n4.  Determine if input internet is comercially connected.\n\n=================[BGP]=================\n5.  Type of path elected.\n6.  Length of path elected.\n7.  Ya silvestre faz o que quiseres aqui.\n\n\n\n\n\n8.Exit\n\n");
        //lê qual opção o utilizador escolheu
        scanf("%d",&option);

        if (option == 1 || option == 2 || option == 3 || option == 4 || option == 5 || option == 6|| option == 7|| option == 8) { //condição posta para ter a certeza que o utilizador só escolheu uma das opções apresentadas
            switch (option) {
                case 1: //se o utilizador introduzir o número 1, o programa vê se o grafo é conexo
                    if(g_connected(ISP_graph, max_node_value, true_size)==true){    //corre para ver se o grafo e connected
                        printf("\nAnswer: The input internet is connected.\n");
                    }else{
                        printf("\nAnswer: The input internet isn´t connected.\n");
                    }
                    break;
                case 2: //se o utilizador introduzir o número 2, o programa vê se o grafo têm, pelo menos, uma ponte
                    if(g_connected(ISP_graph, max_node_value, true_size)==true){
                        link_biconnected(ISP_graph, max_node_value);    //corre para ver se e link biconnected
                    }else{
                        printf("\nAnswer: The input internet isn´t connected, therefore it is not link_biconnected.\n");
                    }
                    break;
                case 3: //se o utilizador introduzir o número 3, o programa vê se o grafo é comercialmente acíclico
                    c_cycle(ISP_graph, max_node_value); //corre para ver se e comercially cyclic
                    break;
                case 4: //se o utilizador introduzir o número 4, o programa vê se o grafo é comercialmente conexo
                    if(cycle_graph(ISP_graph, max_node_value, top_f, list_top, count_f, true_size)==true){  //corre para ver se e comercially connected
                        printf("\nAnswer: The input internet is comercially connected.\n");
                    }else{
                        printf("\nAnswer: The input internet isn´t comercially connected.\n");
                    }
                    break;
                case 5: //se o utilizador introduzir o numero 5, indica-se o tipo de caminho escolhido pelo BGP
                    all_path_types=(char**)malloc(max_node_value*sizeof(char*));
                    for(int i=0;i<max_node_value;i++){
                        all_path_types[i]=(char*)malloc(max_node_value*sizeof(char));
                    }
                    printf("\n Please choose a Source and Destination (in this order) node to find the path:\n");
                    printf("Source:");
                    scanf("%d",&source_node);
                    printf("Destination:");
                    scanf("%d",&destination_node);
                    path_mode=path_type(ISP_graph,max_node_value,source_node,destination_node);
                    printf("\n Answer: The path type will be ");
                    switch(path_mode){
                        case 'C':
                            printf("CUSTOMER\n");
                            break;
                        case 'R':
                            printf("PEER\n");
                            break;
                        case 'P':
                            printf("PROVIDER\n");
                            break;
                        default:
                            printf("INVALID\n");
                            break;
                    }
                    for(int i=0;i<max_node_value;i++){
                        for(int j=0;j<max_node_value;j++){
                            path_mode=path_type(ISP_graph,max_node_value,i+1,j+1);
                            all_path_types[i][j]=path_mode;
                        }
                    }
                    printf("From all to all:\n\n");
                    for(int i=0;i<max_node_value;i++){
                        for(int j=0;j<max_node_value;j++){
                            printf("%c|",all_path_types[i][j]);
                        }
                        printf("\n");
                    }
                    for(int i=0;i<max_node_value;i++){
                        free(all_path_types[i]);
                    }
                    free(all_path_types);
                    break;
                case 6:
                    /*todo*/;
                    break;
                case 7:
                    /*todo*/;
                    break;
                case 8: //se o utilizador introduzir o número 8 sai do programa
                    system("clear");
                    return;
                default:
                    system("clear");
                    return;
            }
        }
    }

}
