#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "lista.h"
#include "item.h"

void adicionarAoInventario(Lista* inven, Item* item);
void exibirInventario(Lista* inven);
void usarItemDoInventario(Lista* inven, int posicao);
void descartarItemDoInventario(Lista* inven, int posicao);

#endif