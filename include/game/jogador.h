#ifndef JOGADOR_H
#define JOGADOR_H

#include "lista.h"
#include "inventario.h"
typedef struct Jogador{
    int pos_x;
    int pos_y;
    int vida;
    int vida_max;
    int moedas;
    int ataque;
    Lista* inventario;
    int duracao_repelente;
} Jogador;

Jogador* criarJogador(int x, int y, int vida);
void liberarJogador(Jogador* jogador);
void aplicarRepelente(Jogador* jogador, int duracao);
void atualizarEfeito(Jogador* jogador);
int jogadorTemEfeito(Jogador* jogador);

#endif
