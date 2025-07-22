#ifndef INIMIGO_H
#define INIMIGO_H

#include "arvore.h"
#include "item.h"
#include "lista.h"

typedef struct Inimigo {
    char nome[50];
    int vida;
    int vida_max;
    int ataque;
    int limite_cura;
    NoArvore* ia_arvore;
} Inimigo;

Inimigo* criarInimigo(const char* nome, int vida, int ataque);
void liberarInimigo(Inimigo* inimigo);

#endif