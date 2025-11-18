#include "raylib.h"
#include "tela_game_over.h"

TelaAtual tela_game_over() {

    BeginDrawing();
    ClearBackground(BLACK);

    DrawText("GAME OVER", 200, 150, 50, RED);
    DrawText("Pressione ENTER para reiniciar", 120, 250, 24, WHITE);

    EndDrawing();

    if (IsKeyPressed(KEY_ENTER)) {
        return TELA_JOGO;  // volta para o jogo
    }

    return TELA_GAME_OVER;
}

