#include "raylib.h"
#include "tela_menu.h"
#include <math.h>

void tela_menu() {
    // Abre em tela cheia automaticamente
    InitWindow(0, 0, "Fly Bird - Menu");
    ToggleFullscreen();
    SetTargetFPS(60);

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    Color skyBlue = (Color){138, 235, 244, 255};
    Color grassGreen = (Color){117, 201, 109, 255};

    float birdY = screenHeight / 2.0f;
    float frame = 0;

    while (!WindowShouldClose()) {
        frame += 0.1f;
        birdY = (screenHeight / 2.0f) + sinf(frame) * (screenHeight * 0.015f);

        if (IsKeyPressed(KEY_ENTER)) break;

        BeginDrawing();
        ClearBackground(skyBlue);

        // Fundo inferior (grama)
        DrawRectangle(0, screenHeight * 0.9f, screenWidth, screenHeight * 0.1f, grassGreen);

        // Nuvens (proporcionais e maiores)
        DrawCircle(screenWidth * 0.18f, screenHeight * 0.20f, screenWidth * 0.06f, RAYWHITE);
        DrawCircle(screenWidth * 0.22f, screenHeight * 0.18f, screenWidth * 0.07f, RAYWHITE);
        DrawCircle(screenWidth * 0.26f, screenHeight * 0.20f, screenWidth * 0.06f, RAYWHITE);

        DrawCircle(screenWidth * 0.72f, screenHeight * 0.15f, screenWidth * 0.06f, RAYWHITE);
        DrawCircle(screenWidth * 0.76f, screenHeight * 0.13f, screenWidth * 0.07f, RAYWHITE);
        DrawCircle(screenWidth * 0.80f, screenHeight * 0.15f, screenWidth * 0.06f, RAYWHITE);

        // Título centralizado
        int fontSize = screenHeight / 6;
        const char *titulo = "FLY BIRD";
        int titleWidth = MeasureText(titulo, fontSize);
        DrawText(titulo, (screenWidth - titleWidth) / 2 + 5, screenHeight * 0.1f + 5, fontSize, ORANGE);
        DrawText(titulo, (screenWidth - titleWidth) / 2, screenHeight * 0.1f, fontSize, YELLOW);

        // Pássaro
        float birdX = screenWidth / 2.0f;
        float birdSize = screenHeight * 0.03f;
        DrawCircle(birdX, birdY, birdSize, YELLOW);
        DrawTriangle((Vector2){birdX + birdSize, birdY},
                     (Vector2){birdX + birdSize * 1.4f, birdY - birdSize / 3},
                     (Vector2){birdX + birdSize * 1.4f, birdY + birdSize / 3},
                     ORANGE);
        DrawCircle(birdX - birdSize * 0.5f, birdY - birdSize * 0.3f, birdSize * 0.2f, BLACK);

        // Texto inferior (ENTER)
        const char *msg = "Pressione ENTER para comecar";
        int msgFont = screenHeight / 20;
        int msgWidth = MeasureText(msg, msgFont);
        DrawText(msg, (screenWidth - msgWidth) / 2, screenHeight * 0.8f, msgFont, DARKGREEN);

        EndDrawing();
    }

    CloseWindow();
}
