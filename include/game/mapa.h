#ifndef MAPA_H
#define MAPA_H

#include "jogador.h"

#define MAPA_LARGURA 20
#define MAPA_ALTURA 10

#define PAREDE '#'
#define CAMINHO ' '
#define ITEM 'B'
#define ARMADILHA 'T'
#define INIMIGO 'E'
#define SAIDA 'S'
#define JOGADOR_CHAR '@'

typedef struct Jogador Jogador;
typedef struct {
    char data[MAPA_ALTURA][MAPA_LARGURA];
} Mapa;

Mapa* criarMapa();
void inicializarMapa(Mapa* mapa);
void popularMapa(Mapa* mapa, Jogador* jogador, int num_item, int num_armadilhas, int num_inimigos);
void desenharMapa(Mapa* mapa, Jogador* jogador);
void liberarMapa(Mapa* mapa);

#endif