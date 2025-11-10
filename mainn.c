#include <stdio.h>
#include <stdlib.h>
#include "tela_menu.h"

int main() {
    int opcao;

    while (1) {
        exibir_menu();
        opcao = selecionar_opcao();

        switch (opcao) {
            case 1:
                system("clear");
                printf("Iniciando novo jogo...\n");
                getchar(); getchar(); 
                break;
            case 2:
                system("clear");
                printf("=== Opções ===\n");
                printf("1. Dificuldade\n");
                printf("2. Controles\n");
                printf("3. Voltar\n");
                getchar(); getchar(); 
                break;
            case 0:
                printf("\nSaindo do jogo...\n");
                return 0;
            default:
                printf("Opção inválida!\n");
                getchar(); getchar();
                break;
        }
    }
}
