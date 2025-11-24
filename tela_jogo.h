#ifndef TELA_JOGO_H
#define TELA_JOGO_H

#include "tela_menu.h"

typedef struct Pipe {
    float x;
    float topHeight;
    float bottomHeight;
    bool counted;
    struct Pipe *next;
} Pipe;

typedef struct {
    float x, y;
    float velocity;
    float size;
} Bird;

TelaAtual tela_jogo();

#endif
