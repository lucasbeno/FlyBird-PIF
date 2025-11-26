#include "raylib.h"
#include "tela_menu.h"
#include <math.h>


#define LINHAS_CEU 5 
#define COLUNAS_CEU 10 

int nuvens_menu[LINHAS_CEU][COLUNAS_CEU];

void InicializarNuvensMenu() {
    for (int i = 0; i < LINHAS_CEU; i++) {
        for (int j = 0; j < COLUNAS_CEU; j++) {
            if (GetRandomValue(0, 10) >= 8) {
                nuvens_menu[i][j] = 1;
            } else {
                nuvens_menu[i][j] = 0;
            }
        }
    }
}

void DesenharNuvensMenu(int largura_tela, int altura_tela) {
    int largura_celula = largura_tela / COLUNAS_CEU;
    int altura_celula = (altura_tela * 0.5f) / LINHAS_CEU; 

    for (int i = 0; i < LINHAS_CEU; i++) {
        for (int j = 0; j < COLUNAS_CEU; j++) {

            if (nuvens_menu[i][j] == 1) {
                int x = j * largura_celula + (largura_celula / 2);
                int y = i * altura_celula + (altura_celula / 2);
                Color corNuvem = (Color){255, 255, 255, 200}; 
                
                DrawCircle(x, y, 30, corNuvem);           
                DrawCircle(x - 25, y + 10, 20, corNuvem); 
                DrawCircle(x + 25, y + 10, 20, corNuvem); 
            }
        }
    }
}

TelaAtual tela_menu() {

    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    static bool cenarioIniciado = false;
    if (!cenarioIniciado) {
        InicializarNuvensMenu();
        cenarioIniciado = true;
    }

    static Texture2D birdTexture = {0};
    if (birdTexture.id == 0) {
        birdTexture = LoadTexture("assets/bird.png");
    }

    static float frame = 0;
    frame += 0.1f;

    float birdY = (sh / 2.0f) + sinf(frame) * (sh * 0.02f);
    float birdSize = sh * 0.06f;
    float birdX = sw * 0.50f;

    if (IsKeyPressed(KEY_ENTER)) {
        return TELA_JOGO;
    }

    Color skyBlue = (Color){138, 235, 244, 255};
    Color grassGreen = (Color){117, 201, 109, 255};

    BeginDrawing();
    ClearBackground(skyBlue); 

    DesenharNuvensMenu(sw, sh);

    DrawRectangle(0, sh * 0.9f, sw, sh * 0.1f, grassGreen);

    int fontSize = sh / 6;
    char *titulo = "FLY BIRD";
    int titleW = MeasureText(titulo, fontSize);

    DrawText(titulo, (sw - titleW) / 2 + 4, sh * 0.10f + 4, fontSize, BLACK);
    DrawText(titulo, (sw - titleW) / 2, sh * 0.10f, fontSize, YELLOW);

    DrawTexturePro(
        birdTexture,
        (Rectangle){0, 0, birdTexture.width, birdTexture.height},
        (Rectangle){
            birdX - birdSize,
            birdY - birdSize,
            birdSize * 2,
            birdSize * 2
        },
        (Vector2){0,0},
        0.0f,
        WHITE
    );

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