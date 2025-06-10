#include <stdio.h>
#include <stdlib.h>

#include "../../include/game/item.h"

Item* criarItem(const char* nome, const char* desc, TipoItem tipo, int valor) {
    Item* novo = (Item*)malloc(sizeof(Item));
    if(novo) {
        strcpy(novo->nome, nome);
        strcpy(novo->descricao, desc);
        novo->tipo = tipo;
        novo->valor = valor;
    }
    return novo;
}

void imprimirItem(const void* item) {
    if (!item) return;
    const Item* convertido = (const Item*)item;
    printf("Nome: %s | Descricao: %s\n", convertido->nome, convertido->descricao);
}