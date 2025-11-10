#include <stdio.h>
#include <stdlib.h>
#include "tela_menu.h"

void exibir_menu() {
    system("clear"); 
    printf("=====================================\n");
    printf("           FLY BIRD GAME 🐦          \n");
    printf("=====================================\n\n");
    printf(" [1] Começar novo jogo\n");
    printf(" [2] Opções\n");
    printf(" [0] Sair\n");
    printf("\nSelecione uma opção: ");
}

int selecionar_opcao() {
    int opcao;
    scanf("%d", &opcao);
    return opcao;
}
