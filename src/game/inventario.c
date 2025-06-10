#include <stdio.h>
#include <stdlib.h>

#include "../../include/game/inventario.h"

void adicionarAoInventario(Lista* inven, Item* item) {
    if(!inven|| !item) return;
    inserirFim(inven, (void*)item);
    printf("'%s' foi adicionado ao inventario.\n", item->nome);
}

void exibirInventario(Lista* inven) {
    printf("--- INVENTARIO ---\n");
    if(!inven) return;
    imprimirLista(inven, imprimirItem);
    printf("------------------\n");
}

void usarItemDoInventario(Lista* inven, int posicao) {

}

void descartarItemDoInventario(Lista* inven, int posicao);