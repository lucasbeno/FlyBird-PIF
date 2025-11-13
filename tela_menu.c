#include "raylib.h"
#include "tela_menu.h"
#include <math.h>

TelaAtual tela_menu() {

    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    static float frame = 0;
    frame += 0.1f;

    float birdY = (sh / 2.0f) + sinf(frame) * (sh * 0.015f);

    if (IsKeyPressed(KEY_ENTER)) {
        return TELA_JOGO;
    }

    // ---- DESENHO DA TELA ----
    Color skyBlue = (Color){138, 235, 244, 255};
    Color grassGreen = (Color){117, 201, 109, 255};

    BeginDrawing();
    ClearBackground(skyBlue);

    DrawRectangle(0, sh * 0.9f, sw, sh * 0.1f, grassGreen);

    int fontSize = sh / 6;
    const char *titulo = "FLY BIRD";
    int titleW = MeasureText(titulo, fontSize);
    DrawText(titulo, (sw - titleW)/2, sh * 0.1f, fontSize, YELLOW);

    float birdSize = sh * 0.03f;
    float birdX = sw / 2.0f;
    DrawCircle(birdX, birdY, birdSize, YELLOW);

    const char *msg = "Pressione ENTER para comecar";
    int msgSize = sh / 20;
    DrawText(msg, (sw - MeasureText(msg, msgSize))/2, sh * 0.8f, msgSize, DARKGREEN);

    EndDrawing();

    return TELA_MENU;
}
