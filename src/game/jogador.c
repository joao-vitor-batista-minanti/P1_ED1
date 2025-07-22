#include <stdio.h>
#include <stdlib.h>
#include "../../include/game/jogador.h"


Jogador* criarJogador(int x, int y, int vida) {
    Jogador* novo = (Jogador*)malloc(sizeof(Jogador));
    if(novo != NULL) {
        novo->pos_x = x;
        novo->pos_y = y;
        novo->vida = vida;
        novo->vida_max = 100; 
        novo->moedas = 0;
        novo->ataque = 10;
        novo->inventario = criarLista();
        novo->efeitos = criarLista();
    }
    return novo;
}

void liberarJogador(Jogador* jogador) {
    if(jogador != NULL) {
        liberarLista(jogador->inventario);
        liberarLista(jogador->efeitos);
        free(jogador);
    }
}

void adicionarEfeito(Jogador* jogador, EfeitoTipo tipo, int duracao) {
    if(!jogador) return;

    Status* novo_status = criarStatus(tipo, duracao);
    if(novo_status) inserirFim(jogador->efeitos, novo_status);
}

void atualizarEfeito(Jogador* jogador) {
    if(!jogador || !jogador->efeitos) return;

    No* atual = jogador->efeitos->comeco;
    int pos = 1;
    while(atual != NULL) {
        Status* s = (Status*)atual->dado;
        s->duracao--;

        No* proximo = atual->prox;

        if(s->duracao <= 0) {
            printf("O Efeito do Repelente Acabou!\n");
            void* dado_removido = removerPosicao(jogador->efeitos, pos);
            free(dado_removido); 
        } else {
            pos++;
        }
        atual = proximo;
    }
}

int jogadorTemEfeito(Jogador* jogador, EfeitoTipo tipo) {
    if(!jogador || !jogador->efeitos) return 0;

    No* atual = jogador->efeitos->comeco;
    while(atual != NULL) {
        Status* s = (Status*)atual->dado;
        if(s->tipo == tipo) {
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}