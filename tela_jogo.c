#include "raylib.h"
#include "tela_jogo.h"
#include <stdlib.h>  // para malloc e free
#include <stddef.h>  // para NULL

#define GRAVITY 800.0f
#define JUMP_FORCE -300.0f

Pipe* criarCano(int sw, int sh) {
    Pipe *novo = malloc(sizeof(Pipe));

    float gap = sh * 0.25f;
    float minHeight = sh * 0.10f;

    novo->topHeight = minHeight + GetRandomValue(0, sh * 0.50f);
    novo->bottomHeight = sh - (novo->topHeight + gap);

    novo->x = sw + 100;
    novo->next = NULL;

    return novo;
}

void atualizarCanos(Pipe **lista, float delta, float speed) {
    Pipe *atual = *lista;
    Pipe *anterior = NULL;

    while (atual != NULL) {
        atual->x -= speed * delta;

        if (atual->x < -100) {
            Pipe *remover = atual;

            if (anterior == NULL) {
                *lista = atual->next;
                atual = atual->next;
            } else {
                anterior->next = atual->next;
                atual = atual->next;
            }

            free(remover);
            continue;
        }

        anterior = atual;
        atual = atual->next;
    }
}

void desenharCanos(Pipe *lista, int sh) {
    Pipe *atual = lista;

    while (atual != NULL) {
        DrawRectangle(atual->x, 0, 80, atual->topHeight, GREEN);
        DrawRectangle(atual->x, sh - atual->bottomHeight, 80, atual->bottomHeight, GREEN);

        atual = atual->next;
    }
}

TelaAtual tela_jogo() {
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    Pipe *canos = NULL;
    float tempoParaNovoCano = 0;
    float velocidadeCanos = 300.0f;

    Bird bird;
    bird.x = sw * 0.12f;
    bird.y = sh * 0.35f;
    bird.size = sh * 0.03f;
    bird.velocity = 0;

    bool jogoComecou = false;

    while (!WindowShouldClose()) {

        float delta = GetFrameTime();

        // --- GERAR NOVO CANO ---
        tempoParaNovoCano -= delta;

        if (tempoParaNovoCano <= 0) {
            Pipe *novo = criarCano(sw, sh);
            novo->next = canos;
            canos = novo;
            tempoParaNovoCano = 2.0f;
        }

        // --- ATUALIZAR CANOS ---
        if (jogoComecou) {
            atualizarCanos(&canos, delta, velocidadeCanos);
        }

        // --- FÍSICA DO PÁSSARO ---
        if (!jogoComecou) {
            if (IsKeyPressed(KEY_SPACE)) {
                jogoComecou = true;
                bird.velocity = JUMP_FORCE;
            }
        } else {
            bird.velocity += GRAVITY * delta;
            bird.y += bird.velocity * delta;

            if (IsKeyPressed(KEY_SPACE)) {
                bird.velocity = JUMP_FORCE;
            }

            if (bird.y + bird.size > sh * 0.90f) {
                bird.y = sh * 0.90f - bird.size;
                bird.velocity = 0;
            }
        }

        // --- DESENHO ---
        BeginDrawing();
        ClearBackground((Color){138, 235, 244, 255});

        // chão
        DrawRectangle(0, sh * 0.90f, sw, sh * 0.10f, (Color){117, 201, 109, 255});

        // CANOS — AGORA NO LUGAR CERTO!
        desenharCanos(canos, sh);

        // pássaro
        DrawCircle(bird.x, bird.y, bird.size, YELLOW);

        if (!jogoComecou) {
            const char *msg = "Pressione ESPACO para comecar";
            int msgSize = sh / 20;
            DrawText(msg, (sw - MeasureText(msg, msgSize)) / 2, sh * 0.75f, msgSize, DARKGREEN);
        }

        EndDrawing();
    }

    return TELA_SAIR;
}
