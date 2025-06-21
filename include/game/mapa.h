#ifndef MAPA_H
#define MAPA_H

#include "jogador.h"
#include "inventario.h" 
#include "jogador.h"

#define MAPA_LARGURA 20
#define MAPA_ALTURA 10

#define PAREDE '#'
#define CAMINHO ' '
#define ITEM 'I'
#define ARMADILHA 'T'
#define SAIDA 'S'
#define JOGADOR_CHAR '@'

typedef struct {
    char data[MAPA_ALTURA][MAPA_LARGURA];
} Mapa;

Mapa* criarMapa();
void inicializarMapa(Mapa* mapa);
void popularMapa(Mapa* mapa, int num_item, int num_armadilhas);
void desenharMapa(Mapa* mapa, Jogador* jogador);
void liberarMapa(Mapa* mapa);

#endif