#include "raylib.h"
#include "tela_menu.h"

void tela_menu() {
    InitWindow(800, 450, "Fly Bird - Menu");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ENTER)) {
            break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("FLY BIRD", 260, 150, 60, BLUE);
        DrawText("Aperte ENTER para comecar", 220, 250, 25, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
}
