#include "raylib.h"
#include "tela_menu.h"
#include "tela_jogo.h"

int main() {
    InitWindow(0, 0, "Fly Bird");
    ToggleFullscreen();
    SetTargetFPS(60);

    TelaAtual estado = TELA_MENU;

    while (!WindowShouldClose()) {

        switch (estado) {
            case TELA_MENU:
                estado = tela_menu();
                break;

            case TELA_JOGO:
                estado = tela_jogo();
                break;

            case TELA_SAIR:
                CloseWindow();
                return 0;
        }
    }

    CloseWindow();
    return 0;
}
