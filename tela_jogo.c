#include "raylib.h"
#include "tela_jogo.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define GRAVITY 800.0f
#define JUMP_FORCE -300.0f
#define GROUND_HEIGHT 0.10f 

void DrawScore(int score, Texture2D numeros[], int sw) {
    char text[10];
    sprintf(text, "%d", score);

    int totalWidth = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        int digit = text[i] - '0';
        totalWidth += numeros[digit].width;
    }

    int x = (sw - totalWidth) / 2;
    int y = 40;

    for (int i = 0; text[i] != '\0'; i++) {
        int digit = text[i] - '0';
        DrawTexture(numeros[digit], x, y, WHITE);
        x += numeros[digit].width;
    }
}

Pipe* criarCano(int sw, int sh) {
    Pipe *novo = malloc(sizeof(Pipe));
    if (!novo) return NULL;

    float gap = sh * 0.25f;
    float minHeight = sh * 0.10f;

    novo->topHeight = minHeight + GetRandomValue(0, (int)(sh * 0.50f));
    novo->bottomHeight = sh - (novo->topHeight + gap);

    novo->x = sw + 100;
    novo->counted = false;
    novo->next = NULL;

    return novo;
}

void atualizarCanos(Pipe **lista, float delta, float *speed) {
    Pipe *atual = *lista;
    Pipe *anterior = NULL;

    while (atual != NULL) {
        atual->x -= (*speed) * delta;

        if (atual->x < -100) {
            Pipe *remover = atual;
            if (anterior == NULL) *lista = atual->next;
            else anterior->next = atual->next;
            atual = atual->next;
            free(remover);
            continue;
        }

        anterior = atual;
        atual = atual->next;
    }
}

void desenharCanos(Pipe *lista, int sh, Texture2D canoTexture) {
    Pipe *atual = lista;

    while (atual != NULL) {
        float pipeWidth = 80;

        DrawTexturePro(
            canoTexture,
            (Rectangle){0, 0, canoTexture.width, -canoTexture.height},
            (Rectangle){atual->x, 0, pipeWidth, atual->topHeight},
            (Vector2){0,0}, 0.0f, WHITE
        );

        DrawTexturePro(
            canoTexture,
            (Rectangle){0,0,canoTexture.width,canoTexture.height},
            (Rectangle){atual->x, sh - atual->bottomHeight, pipeWidth, atual->bottomHeight},
            (Vector2){0,0}, 0.0f, WHITE
        );

        atual = atual->next;
    }
}

TelaAtual tela_jogo() {

    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    Texture2D birdTexture = LoadTexture("assets/bird.png");
    Texture2D canoTexture = LoadTexture("assets/cano.png");

    Texture2D numeros[10];
    for (int i = 0; i < 10; i++) {
        char caminho[50];
        sprintf(caminho, "assets/%d.png", i);
        numeros[i] = LoadTexture(caminho);
    }

    Pipe *canos = NULL;
    float tempoParaNovoCano = 0;
    float velocidadeCanos = 300.0f;   

    Bird bird;
    bird.x = sw * 0.12f;
    bird.y = sh * 0.35f;
    bird.size = sh * 0.03f;
    bird.velocity = 0;

    int score = 0;
    bool jogoComecou = false;
    bool gameOver = false;

    while (!WindowShouldClose()) {
        float delta = GetFrameTime();

        if (gameOver) {

            if (IsKeyPressed(KEY_ENTER)) return TELA_MENU;
            if (IsKeyPressed(KEY_ESCAPE)) return TELA_MENU;

            BeginDrawing();
            ClearBackground((Color){138, 235, 244, 255});

            DrawRectangle(0, sh * (1.0f - GROUND_HEIGHT), sw, sh * GROUND_HEIGHT,
                          (Color){117,201,109,255});

            desenharCanos(canos, sh, canoTexture);

            DrawTexturePro(
                birdTexture,
                (Rectangle){0,0,birdTexture.width,birdTexture.height},
                (Rectangle){bird.x-bird.size,bird.y-bird.size,bird.size*2,bird.size*2},
                (Vector2){0,0},
                90.0f,
                WHITE
            );

            DrawScore(score, numeros, sw);

            int fs = sh / 12;
            DrawText("GAME OVER", (sw - MeasureText("GAME OVER", fs))/2, sh*0.35f, fs, RED);

            int fs2 = sh / 25;
            DrawText("Press ENTER to return",
                     (sw - MeasureText("Press ENTER to return", fs2)) / 2,
                     sh * 0.55f, fs2, BLACK);

            EndDrawing();
            continue;
        }

        tempoParaNovoCano -= delta;
        if (tempoParaNovoCano <= 0) {
            Pipe *novo = criarCano(sw, sh);
            if (novo) { novo->next = canos; canos = novo; }
            tempoParaNovoCano = 2.0f;
        }

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

            atualizarCanos(&canos, delta, &velocidadeCanos);
        }

        Rectangle birdRec = { bird.x - bird.size, bird.y - bird.size, bird.size*2, bird.size*2 };

        if (bird.y + bird.size > sh * (1.0f - GROUND_HEIGHT)) {
            gameOver = true;
        }

        for (Pipe *p = canos; p != NULL; p = p->next) {

            Rectangle topPipe = { p->x, 0, 80, p->topHeight };
            Rectangle bottomPipe = { p->x, sh - p->bottomHeight, 80, p->bottomHeight };

            if (CheckCollisionRecs(birdRec, topPipe) || CheckCollisionRecs(birdRec, bottomPipe)) {
                gameOver = true;
            }

            if (!p->counted && p->x + 80 < bird.x) {
                p->counted = true;
                score++;

                velocidadeCanos += 100.0f;

                printf("Score = %d | Velocidade = %.2f\n", score, velocidadeCanos);
            }
        }

        BeginDrawing();
        ClearBackground((Color){138, 235, 244, 255});

        DrawRectangle(0, sh * (1.0f - GROUND_HEIGHT), sw, sh * GROUND_HEIGHT,
                      (Color){117,201,109,255});

        desenharCanos(canos, sh, canoTexture);

        DrawTexturePro(
            birdTexture,
            (Rectangle){0,0,birdTexture.width,birdTexture.height},
            (Rectangle){bird.x-bird.size,bird.y-bird.size,bird.size*2,bird.size*2},
            (Vector2){0,0},
            0.0f,
            WHITE
        );

        DrawScore(score, numeros, sw);

        if (!jogoComecou) {
            const char *msg = "Press SPACE to start";
            int s = sh / 20;
            DrawText(msg, (sw - MeasureText(msg, s))/2, sh * 0.75f, s, DARKGREEN);
        }

        EndDrawing();
    }

    return TELA_MENU;
}
