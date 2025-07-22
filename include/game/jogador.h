#ifndef JOGADOR_H
#define JOGADOR_H

#include "lista.h"
#include "inventario.h"
#include "status.h"
typedef struct Jogador{
    int pos_x;
    int pos_y;
    int vida;
    int vida_max;
    int moedas;
    int ataque;
    Lista* inventario;
    Lista* efeitos;
} Jogador;

Jogador* criarJogador(int x, int y, int vida);
void liberarJogador(Jogador* jogador);
void adicionarEfeito(Jogador* jogador, EfeitoTipo tipo, int duracao);
void atualizarEfeito(Jogador* jogador);
int jogadorTemEfeito(Jogador* jogador, EfeitoTipo tipo);

#endif
