#include <stdio.h>
#include <unistd.h> // para sleep()
#include <stdlib.h>
#include "jogo.h"

void iniciar_jogo() {
    printf("=== INICIANDO O JOGO ===\n\n");
    printf("Use ESPAÇO para voar e evite os obstáculos!\n\n");

    // animação inicial simples
    for (int i = 0; i < 3; i++) {
        printf("🐦\n");
        sleep(1);
        system("clear");
        printf("  🐦\n");
        sleep(1);
        system("clear");
    }

    printf("Boa sorte!\n");
}
