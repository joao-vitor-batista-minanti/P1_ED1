#include <stdio.h>
#include <stdlib.h>
#include "../../include/game/jogador.h"


Jogador* criarJogador(int x, int y, int vida) {
    Jogador* novo = (Jogador*)malloc(sizeof(Jogador));
    if(novo != NULL) {
        novo->pos_x = x;
        novo->pos_y = y;
        novo->vida = vida;
        novo->vida_max = 100; 
        novo->moedas = 0;
        novo->ataque = 10;
        novo->inventario = criarLista();
        novo->duracao_repelente = 0;
    }
    return novo;
}

void liberarJogador(Jogador* jogador) {
    if(jogador != NULL) {
        liberarLista(jogador->inventario);
        free(jogador);
    }
}

void aplicarRepelente(Jogador* jogador, int duracao) {
    if(!jogador) return;
    jogador->duracao_repelente = duracao;
}

void atualizarEfeito(Jogador* jogador) {
    if(!jogador || jogador->duracao_repelente <= 0) return;
    jogador->duracao_repelente--;
    if(jogador->duracao_repelente <= 0) {
        printf("O efeito do repelente acabou.\n");
    }
}

int jogadorTemEfeito(Jogador* jogador) {
    if(!jogador) return 0;
    return jogador->duracao_repelente > 0;
}