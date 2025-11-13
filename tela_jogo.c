#include "raylib.h"
#include "tela_jogo.h"

TelaAtual tela_jogo() {
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    static float birdX = -1; // valor inicial
    float birdY = sh * 0.35f;
    float birdSize = sh * 0.03f;

    // inicializa só uma vez
    if (birdX == -1) {
        birdX = sw * 0.10f;    // pássaro bem à esquerda
    }

    if (IsKeyPressed(KEY_SPACE)) {
        return TELA_SAIR;   // depois vira GAMEPLAY
    }

    BeginDrawing();
    ClearBackground((Color){138, 235, 244, 255});

    DrawRectangle(0, sh * 0.9f, sw, sh * 0.1f, (Color){117, 201, 109, 255});

    DrawCircle(birdX, birdY, birdSize, YELLOW);

    const char *msg = "Aperte ESPACO para comecar";
    int msgSize = sh / 20;
    DrawText(msg, (sw - MeasureText(msg, msgSize))/2, sh * 0.75f, msgSize, DARKGREEN);

    EndDrawing();

    return TELA_JOGO;
}
