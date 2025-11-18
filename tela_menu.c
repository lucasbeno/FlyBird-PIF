#include "raylib.h"
#include "tela_menu.h"
#include <math.h>

TelaAtual tela_menu() {

    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    static Texture2D birdTexture = {0};
    if (birdTexture.id == 0) {
        birdTexture = LoadTexture("assets/bird.png");
    }

    static float frame = 0;
    frame += 0.1f;

    float birdY = (sh / 2.0f) + sinf(frame) * (sh * 0.02f);
    float birdSize = sh * 0.06f; 

    if (IsKeyPressed(KEY_ENTER)) {
        return TELA_JOGO;
    }

    Color skyBlue = (Color){138, 235, 244, 255};
    Color grassGreen = (Color){117, 201, 109, 255};

    BeginDrawing();
    ClearBackground(skyBlue);

    DrawRectangle(0, sh * 0.9f, sw, sh * 0.1f, grassGreen);

    int fontSize = sh / 6;
    const char *titulo = "FLY BIRD";
    int titleW = MeasureText(titulo, fontSize);

    DrawText(titulo, 
        (sw - titleW)/2, 
        sh * 0.10f, 
        fontSize, 
        YELLOW
    );

    float birdX = sw * 0.50f;
    const char *msg = "Pressione ENTER para comecar";
    int msgSize = sh / 20;

    DrawText(
        msg,
        (sw - MeasureText(msg, msgSize)) / 2,
        sh * 0.80f,
        msgSize,
        DARKGREEN
    );

    EndDrawing();

    return TELA_MENU;
}
