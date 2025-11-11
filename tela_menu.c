#include "raylib.h"
#include "tela_menu.h"
#include <math.h>

void tela_menu() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Fly Bird - Menu");
    SetTargetFPS(60);

    // Cores inspiradas no Flappy Bird
    Color skyBlue = (Color){138, 235, 244, 255};
    Color grassGreen = (Color){117, 201, 109, 255};
    Color pipeGreen = (Color){77, 194, 71, 255};

    float birdY = screenHeight / 2;
    float frame = 0;

    while (!WindowShouldClose()) {
        frame += 0.1f;
        birdY = (screenHeight / 2) + sinf(frame) * 10; // movimento suave

        if (IsKeyPressed(KEY_ENTER)) {
            break;
        }

        BeginDrawing();
        ClearBackground(skyBlue);

        // Fundo verde na parte de baixo (grama)
        DrawRectangle(0, screenHeight - 50, screenWidth, 50, grassGreen);

        // Céu (linhas das nuvens)
        DrawCircle(150, 100, 40, RAYWHITE);
        DrawCircle(190, 90, 50, RAYWHITE);
        DrawCircle(230, 100, 40, RAYWHITE);
        DrawCircle(650, 80, 45, RAYWHITE);
        DrawCircle(690, 70, 55, RAYWHITE);
        DrawCircle(730, 80, 45, RAYWHITE);

        // Título
        DrawText("FLY BIRD", 240, 100, 70, YELLOW);
        DrawText("FLY BIRD", 244, 104, 70, ORANGE); // sombra

        // Pássaro simples (círculo amarelo com bico)
        DrawCircle(400, birdY, 20, YELLOW);
        DrawTriangle((Vector2){420, birdY},
                     (Vector2){435, birdY - 5},
                     (Vector2){435, birdY + 5},
                     ORANGE);
        DrawCircle(392, birdY - 5, 5, BLACK); // olho

        // Texto de instrução
        DrawText("Pressione ENTER para comecar", 220, 330, 25, DARKGREEN);

        EndDrawing();
    }

    CloseWindow();
}
