#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "item.h"
#include "jogador.h"
#include "mapa.h"

#include "../utils/input_handler.h"

typedef struct Jogador Jogador;
void limparBuffer();
void adicionarAoInventario(Jogador* jogador, Item* item);
void exibirInventario(Jogador* jogador);
void usarItemDoInventario(Jogador* jogador, int posicao);
void descartarItemDoInventario(Jogador* jogador, int posicao);
void exibirMenuInventario(Jogador* jogador);

#endif