#include "menus.h"

//Apresentação do menu inicial
void showInitMenu (List** ISP_graph,int* top_f, int max_node_value,int* list_top,int count_f,int true_size) {
    int option = 0,source_node=1,destination_node=1;
    int amount_invalid=0;
    int** all_path_types;
    int* PD_path;
    // auxiliares para o pathLength
    int result = 0;
    int* length;
    int opt, opt1;
    int type=0, * r;

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
                    PD_path=(int*)calloc(4,sizeof(int));    //vetor para calculo da distribuicao de probabilidades de cada caminho
                    if(PD_path==NULL){
                        exit(EXIT_FAILURE);
                    }
                    source_node=1;  //reset das variaveis
                    destination_node=1;  //reset das variaveis
                    if(cycle_graph(ISP_graph, max_node_value, top_f, list_top, count_f, true_size)==true){  //corre para ver se e comercially connected
                        printf("\n\n1.  From a source to a destination.\n2.  From all to all.\n");
                        scanf("%d",&option);    //guarda a opcao do utilizador
                        if(option==1){
                            printf("\n Please choose a Source and Destination (in this order) node to find the path:\n");
                            printf("Source:");
                            scanf("%d",&source_node);
                            printf("Destination:");
                            scanf("%d",&destination_node);
                            if(ISP_graph[destination_node-1]!=NULL && ISP_graph[source_node-1]!=NULL){  //caso nenhum dos nos seja invalido
                                result=path_type(ISP_graph,max_node_value,destination_node,PD_path,source_node);    //calculo do tipo de caminho
                                printf("Answer: The path type will be ");   //formatacao da resposta
                                switch (result) {
                                    case 1:
                                      printf("Customer");
                                      break;
                                    case 2:
                                        printf("Peer");
                                        break;
                                    case 3:
                                        printf("Provider");
                                        break;
                                    default:
                                        printf("Invalid");
                                }
                            }else{
                                printf("Answer: The node you picked wasn´t available.\n");  //indicar que o no e invalido
                            }
                        }else{
                            printf("Running all to all:\n");
                            for(int i=0;i<max_node_value;i++){  //fazer dijkstra de um no para todos
                                if(ISP_graph[i]!=NULL){ //caso o no faca parte da rede
                                    result=path_type(ISP_graph,max_node_value,i+1,PD_path,source_node); //calculo do tipo de caminho e da PD
                                }
                            }
                            PD_path[3]=(true_size*(true_size-1))-(PD_path[1]+PD_path[2]);   //calculo do tipo de caminhos provider
                            printf("\n Answer: The path type will be ");    //formatacao resposta
                            for(int i=0;i<4;i++){
                                printf("%d|",PD_path[i]);
                            }
                            printf("\n");
                        }

                    }else{
                        printf("\nAnswer: The input internet isn´t comercially connected, therefore we won´t compute the solution\n");
                    }
                    free(PD_path);  //libertacao memoria alocada
                    break;
                case 6: // Length do caminho produzido pelo BGP
                    printf("\n\n(1) From a source to a destination\n(Any other number) All to all (can take a while!!)\n");
                    scanf("%d", &opt);
                    switch (opt) {
                        case 1:
                            printf("Source:");
                            scanf("%d",&source_node);
                            printf("Destination:");
                            scanf("%d",&destination_node);
                            result = single_length(ISP_graph, max_node_value, destination_node, source_node);
                            printf("\nAnswer: %d\n", result);
                            break;
                        default:
                            length = lengths(ISP_graph, max_node_value);
                            printf("Lenghts:\n");
                            for (int i = 0; i < max_node_value; ++i) {
                                printf("Size (%d): %d\n", i, length[i]);
                                if(i == 40){
                                    printf("*PRESS (1) TO EXIT TO MENU*\n *PRESS ANY OTHER NUMBER TO SEE THE REST OF THE LENGTHS*\n");
                                    scanf("%d", &opt1);
                                    if(opt1 == 1)
                                        break;
                                }
                            }
                            free(length);
                            scanf("%d", &opt1);
                            break;
                    }
                    break;
                case 7:
                    type=0;
                    printf("1:From all to all\n2:Source-Destination\n");
                    length=(int*)malloc(sizeof(int)*max_node_value);
                    scanf("%d",&type);
                    if(type==2){
                        printf("Source:\n");
                        scanf("%d",&source_node);
                        printf("Destination:\n");
                        scanf("%d",&destination_node);
                        r=BigBoyDijkstra(ISP_graph, length,r,destination_node,source_node,max_node_value);
                        printf("Type: %d, Cost: %d\n", r[0],r[1]);
                        free(r);
                    }
                    else if(type==1){
                        for(int i=0;i<max_node_value;i++){
                            if(ISP_graph[i] != NULL)
                                BigBoyDijkstra(ISP_graph, length,r,i+1,source_node,max_node_value);
                        }
                        printFile("lengths.txt", length, max_node_value);
                    }
                    free(length);
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
