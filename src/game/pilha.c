#include <stdio.h>
#include <stdlib.h>
#include "../../include/game/pilha.h"

Pilha* criarPilha() {
    return criarLista();
}

void pushPilha(Pilha* pilha, int x, int y) {
    Posicao* p = (Posicao*)malloc(sizeof(Posicao));
    if(p != NULL) {
        p->x = x;
        p->y = y;
        inserirInicio(pilha, p);
    }
}

Posicao* popPilha(Pilha* pilha) {
    return (Posicao*)removerPosicao(pilha, 1);
}

int isPilhaEmpty(Pilha* pilha) {
    // pilha->tamanho == 0? return 1 : return 0;
}

void liberarPilha(Pilha* pilha) {
    liberarLista(pilha);
}