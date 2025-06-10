#ifndef ITEM_H
#define ITEM_H

typedef enum {
    ITEM_POCAO_CURA,
    ITEM_REPELENTE,
    ITEM_MOEDA
} TipoItem;

typedef struct {
    char nome[50];
    char descricao[300];
    TipoItem tipo;
    int valor;
} Item;

Item* criarItem(const char* nome, const char* desc, TipoItem tipo, int valor);
void imprimirItem(const void* item);


#endif