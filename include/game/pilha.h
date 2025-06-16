#ifndef PILHA_H
#define PILHA_H

#include "lista.h"

typedef Lista Pilha;

typedef struct posicao {
    int x;
    int y;
} Posicao;

Pilha* criarPilha();
void pushPilha(Pilha* pilha, int x, int y);
Posicao* popPilha(Pilha* pilha);
int isPilhaEmpty(Pilha* pilha);
void liberarPilha(Pilha* pilha); 

#endif