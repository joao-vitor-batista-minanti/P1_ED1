#include <stdio.h>
#include <stdlib.h>
#include "../../include/game/arvore.h"

NoArvore* criarNoAcao(AcaoInimigo acao) {
    NoArvore* no = (NoArvore*)malloc(sizeof(NoArvore));
    no->tipo = NO_ACAO;
    no->acao = acao; 
    no->condicao = NULL;
    no->sim = NULL;
    no->nao = NULL;
    return no;
}

NoArvore* criarNoDecisao(int (*condicao)(Jogador*, Inimigo*), NoArvore* no_sim, NoArvore* no_nao) {
    NoArvore* no = (NoArvore*)malloc(sizeof(NoArvore));
    no->tipo = NO_DECISAO;
    no->condicao = condicao; 
    no->sim = no_sim;
    no->nao = no_nao;
    return no;
}

void liberarArvore(NoArvore* raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->sim);
    liberarArvore(raiz->nao);
    free(raiz);
}

AcaoInimigo decidirAcao(NoArvore* raiz, Jogador* jogador, Inimigo* inimigo) {
    NoArvore* no_atual = raiz;

    while (no_atual->tipo == NO_DECISAO) {
        if (no_atual->condicao(jogador, inimigo)) {
            no_atual = no_atual->sim;
        } else {
            no_atual = no_atual->nao;
        }
    }
    return no_atual->acao;
}