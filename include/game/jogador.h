#ifndef JOGADOR_H
#define JOGADOR_H

#include "lista.h"
typedef struct Jogador{
    int pos_x;
    int pos_y;
    int vida;
    Lista* inventario;
} Jogador;

Jogador* criarJogador(int x, int y, int vida);
void liberarJogador(Jogador* jogador);

#endif
