#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/game/inimigo.h"


int cond_inimigo_vida_alta(Jogador* j, Inimigo* i) {
    return (i->vida >= (i->vida_max / 2));
}

int cond_jogador_vida_media(Jogador* j, Inimigo* i) {
    return (j->vida >= 30);
}


Inimigo* criarInimigo(const char* nome, int vida, int ataque) {
    Inimigo* inimigo = (Inimigo*)malloc(sizeof(Inimigo));
    if (!inimigo) return NULL;

    strcpy(inimigo->nome, nome);
    inimigo->vida = vida;
    inimigo->vida_max = vida;
    inimigo->ataque = ataque;
    inimigo->limite_cura = 4;

    NoArvore* acao_atacar = criarNoAcao(ACAO_ATACAR);
    NoArvore* acao_defender = criarNoAcao(ACAO_DEFENDER);
    NoArvore* acao_curar = criarNoAcao(ACAO_USAR_CURA);

    NoArvore* decisao_vida_jogador = criarNoDecisao(cond_jogador_vida_media, acao_atacar, acao_defender);
    inimigo->ia_arvore = criarNoDecisao(cond_inimigo_vida_alta, decisao_vida_jogador, acao_curar);

    return inimigo;
}

void liberarInimigo(Inimigo* inimigo) {
    if (inimigo) {
        liberarArvore(inimigo->ia_arvore);
        free(inimigo);
    }
}