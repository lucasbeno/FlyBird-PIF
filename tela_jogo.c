#include "raylib.h"
#include "tela_jogo.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define GRAVIDADE 800.0f
#define FORCA_PULO -300.0f
#define ALTURA_CHÃO 0.10f 

void DesenharPontuacao(int pontuacao, Texture2D numeros[], int largura_tela) {
    char texto[10];
    sprintf(texto, "%d", pontuacao);

    int larguraTotal = 0;

    for (int i = 0; texto[i] != '\0'; i++) {
        int digito = texto[i] - '0';
        larguraTotal += numeros[digito].width;
    }

    int pos_x = (largura_tela - larguraTotal) / 2;
    int pos_y = 40;

    for (int i = 0; texto[i] != '\0'; i++) {
        int digito = texto[i] - '0';
        DrawTexture(numeros[digito], pos_x, pos_y, WHITE);
        pos_x += numeros[digito].width;
    }
}

Cano* criarCano(int largura_tela, int altura_tela) {
    Cano *novo = malloc(sizeof(Cano));
    if (!novo) return NULL;

    float espaco = altura_tela * 0.25f;
    float alturaMinima = altura_tela * 0.10f;

    novo->altura_cano_superior = alturaMinima + GetRandomValue(0, (int)(altura_tela * 0.50f));
    novo->altura_cano_inferior = altura_tela - (novo->altura_cano_superior + espaco);

    novo->posicao_cano_x = largura_tela + 100;
    novo->contado = false;
    novo->next = NULL;

    return novo;
}

void atualizarCanos(Cano **lista, float delta, float *velocidade) {
    Cano *atual = *lista;
    Cano *anterior = NULL;

    while (atual != NULL) {
        atual->posicao_cano_x -= (*velocidade) * delta;

        if (atual->posicao_cano_x < -100) {
            Cano *remover = atual;
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

void desenharCanos(Cano *lista, int altura_tela, Texture2D texturaCano) {
    Cano *atual = lista;

    while (atual != NULL) {
        float larguraCano = 80;

        DrawTexturePro(
            texturaCano,
            (Rectangle){0, 0, texturaCano.width, -texturaCano.height},
            (Rectangle){atual->posicao_cano_x, 0, larguraCano, atual->altura_cano_superior},
            (Vector2){0,0}, 0.0f, WHITE
        );

        DrawTexturePro(
            texturaCano,
            (Rectangle){0,0,texturaCano.width,texturaCano.height},
            (Rectangle){atual->posicao_cano_x, altura_tela - atual->altura_cano_inferior, larguraCano, atual->altura_cano_inferior},
            (Vector2){0,0}, 0.0f, WHITE
        );

        atual = atual->next;
    }
}

TelaAtual tela_jogo() {

    int largura_tela = GetScreenWidth();
    int altura_tela = GetScreenHeight();

    Texture2D texturaPassaro = LoadTexture("assets/bird.png");
    Texture2D texturaCano = LoadTexture("assets/cano.png");

    Texture2D numeros[10];
    for (int i = 0; i < 10; i++) {
        char caminho[50];
        sprintf(caminho, "assets/%d.png", i);
        numeros[i] = LoadTexture(caminho);
    }

    Cano *listaCanos = NULL;
    float tempoNovoCano = 0;
    float velocidadeCanos = 300.0f;   

    Passaro passaro;
    passaro.posicao_passaro_x = largura_tela * 0.12f;
    passaro.posicao_passaro_y = altura_tela * 0.35f;
    passaro.tamanho = altura_tela * 0.03f;
    passaro.velocidade = 0;

    int pontuacao = 0;
    bool jogoComecou = false;
    bool jogoTerminou = false;

    while (!WindowShouldClose()) {
        float delta = GetFrameTime();

        if (jogoTerminou) {

            if (IsKeyPressed(KEY_ENTER)) return TELA_MENU;
            if (IsKeyPressed(KEY_ESCAPE)) return TELA_MENU;

            BeginDrawing();
            ClearBackground((Color){138, 235, 244, 255});

            DrawRectangle(0, altura_tela * (1.0f - ALTURA_CHÃO), largura_tela, altura_tela * ALTURA_CHÃO,
                          (Color){117,201,109,255});

            desenharCanos(listaCanos, altura_tela, texturaCano);

            DrawTexturePro(
                texturaPassaro,
                (Rectangle){0,0,texturaPassaro.width,texturaPassaro.height},
                (Rectangle){passaro.posicao_passaro_x-passaro.tamanho, passaro.posicao_passaro_y-passaro.tamanho,
                            passaro.tamanho*2, passaro.tamanho*2},
                (Vector2){0,0},
                90.0f,
                WHITE
            );

            DesenharPontuacao(pontuacao, numeros, largura_tela);

            int fs = altura_tela / 12;
            DrawText("GAME OVER", (largura_tela - MeasureText("GAME OVER", fs))/2, altura_tela*0.35f, fs, RED);

            int fs2 = altura_tela / 25;
            DrawText("Press ENTER to return",
                     (largura_tela - MeasureText("Press ENTER to return", fs2)) / 2,
                     altura_tela * 0.55f, fs2, BLACK);

            EndDrawing();
            continue;
        }

        tempoNovoCano -= delta;
        if (tempoNovoCano <= 0) {
            Cano *novo = criarCano(largura_tela, altura_tela);
            if (novo) { novo->next = listaCanos; listaCanos = novo; }
            tempoNovoCano = 2.0f;
        }

        if (!jogoComecou) {
            if (IsKeyPressed(KEY_SPACE)) {
                jogoComecou = true;
                passaro.velocidade = FORCA_PULO;
            }
        } else {
            passaro.velocidade += GRAVIDADE * delta;
            passaro.posicao_passaro_y += passaro.velocidade * delta;

            if (IsKeyPressed(KEY_SPACE)) {
                passaro.velocidade = FORCA_PULO;
            }

            atualizarCanos(&listaCanos, delta, &velocidadeCanos);
        }

        Rectangle retanguloPassaro = { 
            passaro.posicao_passaro_x - passaro.tamanho,
            passaro.posicao_passaro_y - passaro.tamanho,
            passaro.tamanho*2,
            passaro.tamanho*2 
        };

        if (passaro.posicao_passaro_y + passaro.tamanho > altura_tela * (1.0f - ALTURA_CHÃO)) {
            jogoTerminou = true;
        }

        for (Cano *c = listaCanos; c != NULL; c = c->next) {

            Rectangle canoSuperior = { c->posicao_cano_x, 0, 80, c->altura_cano_superior };
            Rectangle canoInferior = { c->posicao_cano_x, altura_tela - c->altura_cano_inferior, 80, c->altura_cano_inferior };

            if (CheckCollisionRecs(retanguloPassaro, canoSuperior) ||
                CheckCollisionRecs(retanguloPassaro, canoInferior)) {
                jogoTerminou = true;
            }

            if (!c->contado && c->posicao_cano_x + 80 < passaro.posicao_passaro_x) {
                c->contado = true;
                pontuacao++;

                velocidadeCanos += 100.0f;

                printf("Pontuação = %d | Velocidade = %.2f\n", pontuacao, velocidadeCanos);
            }
        }

        BeginDrawing();
        ClearBackground((Color){138, 235, 244, 255});

        DrawRectangle(0, altura_tela * (1.0f - ALTURA_CHÃO), largura_tela, altura_tela * ALTURA_CHÃO,
                      (Color){117,201,109,255});

        desenharCanos(listaCanos, altura_tela, texturaCano);

        DrawTexturePro(
            texturaPassaro,
            (Rectangle){0,0,texturaPassaro.width,texturaPassaro.height},
            (Rectangle){passaro.posicao_passaro_x-passaro.tamanho, passaro.posicao_passaro_y-passaro.tamanho,
                        passaro.tamanho*2, passaro.tamanho*2},
            (Vector2){0,0},
            0.0f,
            WHITE
        );

        DesenharPontuacao(pontuacao, numeros, largura_tela);

        if (!jogoComecou) {
            const char *msg = "Press SPACE to start";
            int s = altura_tela / 20;
            DrawText(msg, (largura_tela - MeasureText(msg, s))/2, altura_tela * 0.75f, s, DARKGREEN);
        }

        EndDrawing();
    }

    return TELA_MENU;
}
