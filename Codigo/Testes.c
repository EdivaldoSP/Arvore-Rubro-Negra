#include "Arvore.h"
#include "Exibe.h"
#include "Insere.h"
#include "Rotacoes.h"
#include "Remove.h"
#include "Visualizer.h"

int menu();

int main(){

    int escolha = 0;
    capsule temp;
    Tree *raiz;

    raiz = CreateTree();
    
    // Loop do Menu Principal
    while(escolha != 99){ 
        escolha = menu();
        switch(escolha){
            
            case 1:
                // Modo de Inserção
                {
                    int continuar = 1;
                    char ver_arvore;
                    
                    printf("\n\n--- Modo de Insercao (Digite 0 para sair do modo) ---\n");
                    
                    while(continuar) {
                        printf("\nInforme o valor para inserir: ");
                        scanf("%d", &temp.key);
                        
                        // Encerra inserção
                        if (temp.key == 0) {
                            continuar = 0;
                            printf("\n\t>>> Insercoes finalizadas com sucesso! <<<\n");
                            
                            char ver_web;
                            printf("\n\tDeseja visualizar a arvore via web? (s/n): ");
                            scanf(" %c", &ver_web);
                            if (ver_web == 's' || ver_web == 'S') {
                                ShowWebTree(raiz);
                            }
                            
                            break;
                        }

                        Insere(&raiz, raiz, temp);
                        printf("\n\t[SUCESSO] Elemento %d inserido na arvore.\n", temp.key);
                    }
                }
            break;
            
            case 2:
                // Remoção
                printf("\n\tInforme o elemento que deseja Remover: ");
                scanf("%d",&temp.key);
                RemoveTree(&raiz,temp);
                printf("\n\t(Elemento removido. Rebalanceamento aplicado se necessario)\n");
                
                char ver_web_rem;
                printf("\n\tDeseja visualizar a arvore via web? (s/n): ");
                scanf(" %c", &ver_web_rem);
                if (ver_web_rem == 's' || ver_web_rem == 'S') {
                    ShowWebTree(raiz);
                }
            break;

            case 3:
                // Exibição Terminal (Números)
                printf("\n\n\n\n");
                draw_arvore_hor(raiz,true);
            break;

            case 4:
                // Exibição Terminal (Cores)
                printf("\n\n\n\n");
                draw_arvore_hor(raiz,false);
            break;
            
            case 5:
               // Visualização Web
               ShowWebTree(raiz);
            break;

            case 0:
                printf("\n\tEncerrando programa. Ate mais!!\n\n\n ");
                escolha = 99;
            break;

            default:
                printf("\n\nOpcao invalida.");

        }
    }    
    return 0;
}

int menu(){
    int x;
    printf("\n\n\n------------------------------------------------------------------");
    printf("\n\n\t\t  MENU ARVORE RUBRO-NEGRA");
    printf("\n\n\t Operacoes:");
    printf("\n\t   [1] -> Inserir Elementos (Modo Interativo)");
    printf("\n\t   [2] -> Remover Elemento");
    printf("\n\n\t Visualizacao:");
    printf("\n\t   [3] -> Grafica (Numeros)");
    printf("\n\t   [4] -> Grafica (Cores)");
    printf("\n\t   [5] -> Visualizacao Web (Navegador)");
    printf("\n\n\t   [0] -> Sair");
    printf("\n--------------------------------------------------------------------");
    
    printf("\n\n\tEscolha uma opcao: ");
    scanf("%d",&x);
    return x;
}
