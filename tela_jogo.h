#ifndef TELA_JOGO_H
#define TELA_JOGO_H

#include "tela_menu.h"   // usa o enum TELA_MENU, TELA_JOGO, TELA_SAIR

// Struct do pássaro (Bird)
typedef struct {
    float x;
    float y;
    float size;
    float velocity;
} Bird;

// Função da tela de jogo
TelaAtual tela_jogo();

#endif

