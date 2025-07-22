#ifndef ARVORE_H
#define ARVORE_H

#include "jogador.h"

typedef struct Inimigo Inimigo;

typedef enum {
    NO_DECISAO,
    NO_ACAO
} TipoNo;

typedef enum {
    ACAO_ATACAR,
    ACAO_DEFENDER,
    ACAO_USAR_CURA
} AcaoInimigo;

typedef struct NoArvore {
    TipoNo tipo;

    int (*condicao)(Jogador*, Inimigo*);

    AcaoInimigo acao;
    struct NoArvore *sim;
    struct NoArvore *nao; 

} NoArvore;

NoArvore* criarNoAcao(AcaoInimigo acao);
NoArvore* criarNoDecisao(int (*condicao)(Jogador*, Inimigo*), NoArvore* no_sim, NoArvore* no_nao);
void liberarArvore(NoArvore* raiz);
AcaoInimigo decidirAcao(NoArvore* raiz, Jogador* jogador, Inimigo* inimigo);

#endif