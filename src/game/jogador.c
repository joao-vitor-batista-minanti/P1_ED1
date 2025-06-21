#include <stdio.h>
#include <stdlib.h>
#include "../../include/game/jogador.h"

Jogador* criarJogador(int x, int y, int vida) {
    Jogador* novo = (Jogador*)malloc(sizeof(Jogador));
    if(novo != NULL) {
        novo->pos_x = x;
        novo->pos_y = y;
        novo->vida = vida;
        novo->inventario = criarLista();
    }
    return novo;
}

void liberarJogador(Jogador* jogador) {
    if(jogador != NULL) {
        liberarLista(jogador->inventario);
        free(jogador);
    }
}