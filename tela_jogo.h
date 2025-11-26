#ifndef TELA_JOGO_H
#define TELA_JOGO_H

#include "tela_menu.h"

typedef struct Cano {
    float posicao_cano_x;                
    float altura_cano_superior;       
    float altura_cano_inferior;      
    bool contado;           
    struct Cano *next;   
} Cano;

typedef struct {
    float posicao_passaro_x, posicao_passaro_y;            
    float velocidade;       
    float tamanho;         
} Passaro;

TelaAtual tela_jogo();

#endif
