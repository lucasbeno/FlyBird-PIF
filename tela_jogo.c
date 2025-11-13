#include "raylib.h"
#include "tela_jogo.h"

#define GRAVITY 800.0f      // força da gravidade
#define JUMP_FORCE -300.0f  // força do pulo

TelaAtual tela_jogo() {
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    // pássaro inicial
    Bird bird;
    bird.x = sw * 0.12f;
    bird.y = sh * 0.35f;
    bird.size = sh * 0.03f;
    bird.velocity = 0;

    bool jogoComecou = false;

    float delta = GetFrameTime();

    while (!WindowShouldClose()) {

        delta = GetFrameTime();

        // ===============================
        // COMEÇA O JOGO AO APERTAR ESPAÇO
        // ===============================
        if (!jogoComecou) {
            if (IsKeyPressed(KEY_SPACE)) {
                jogoComecou = true;
                bird.velocity = JUMP_FORCE; // pulo inicial
            }
        } 
        else {
            // ======================
            // FÍSICA DO PÁSSARO
            // ======================
            bird.velocity += GRAVITY * delta; // gravidade puxa para baixo
            bird.y += bird.velocity * delta;  // aplica movimento

            // ======================
            // PULO
            // ======================
            if (IsKeyPressed(KEY_SPACE)) {
                bird.velocity = JUMP_FORCE;
            }

            // impedir que caia no chão
            if (bird.y + bird.size > sh * 0.90f) {
                bird.y = sh * 0.90f - bird.size;
                bird.velocity = 0;
            }
        }

        // ===============================
        // DESENHO
        // ===============================
        BeginDrawing();
        ClearBackground((Color){138, 235, 244, 255});

        // chão
        DrawRectangle(0, sh * 0.90f, sw, sh * 0.10f, (Color){117, 201, 109, 255});

        // pássaro
        DrawCircle(bird.x, bird.y, bird.size, YELLOW);

        // mensagem
        if (!jogoComecou) {
            const char *msg = "Pressione ESPACO para comecar";
            int msgSize = sh / 20;
            DrawText(msg, (sw - MeasureText(msg, msgSize))/2, sh * 0.75f, msgSize, DARKGREEN);
        }

        EndDrawing();
    }

    return TELA_SAIR;
}
