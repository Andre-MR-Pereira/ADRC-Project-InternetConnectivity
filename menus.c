#include "menus.h"

//Apresentação do menu inicial
void showInitMenu (List** ISP_graph,int* top_f, int max_node_value,int* list_top,int count_f,int true_size) {
    int option = 0;

    while(true){
        printf("\n=================[Menu]=================\n---Please select one of the following---\n\n\n1.  Determine if input internet is connected.\n2.  Determine if input internet is linkbiconnected.\n3.  Determine if input internet is commercially acyclic.\n4.  Determine if input internet is comercially connected.\n5.  Extra\n\n\n\n\n\n6.Exit\n\n");
        scanf("%d", &option); //lê qual opção o utilizador escolheu

        if (option == 1 || option == 2 || option == 3 || option == 4 || option == 5 || option == 6) { //condição posta para ter a certeza que o utilizador só escolheu uma das opções apresentadas
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
                case 5:
                    /*todo*/;
                    break;
                case 6: //se o utilizador introduzir o número 6 sai do programa
                    system("clear");
                    return;
                default:
                    system("clear");
                    return;
            }
        }
    }

}
