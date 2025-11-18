#include "raylib.h"
#include "tela_game_over.h"

TelaAtual tela_game_over() {

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("GAME OVER", 200, 150, 50, RED);
        DrawText("Pressione ENTER para reiniciar", 120, 250, 24, WHITE);

        EndDrawing();

        // ENTER → volta pro jogo
        if (IsKeyPressed(KEY_ENTER)) {
            return TELA_JOGO;
        }

        // ESC → volta pro menu
        if (IsKeyPressed(KEY_ESCAPE)) {
            return TELA_MENU;
        }
    }

    return TELA_MENU; // fallback
}
