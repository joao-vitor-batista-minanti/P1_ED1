#include <stdio.h>
#include <stdlib.h>
#include "../../include/game/lista.h"

Lista* criarLista() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    if(lista != NULL) {
        lista->tamanho = 0;
        lista->comeco = NULL;
        lista->fim = NULL;
        return lista;
    }
    return lista;
}

int inserirInicio(Lista* lista, void* dado) {
    if(lista == NULL) return 0;

    No* novo = (No*)malloc(sizeof(No));
    if(novo == NULL) return 0;

    novo->dado = dado;
    novo->prox = lista->comeco;
    lista->comeco = novo;

    if(lista->fim == NULL) {
        lista->fim = novo;
    }

    lista->tamanho++;
    return 1;
}

int inserirFim(Lista* lista, void* dado) {
    if(lista == NULL) return 0;
    No* novo = (No*)malloc(sizeof(No));
    if(novo == NULL) return 0;
    novo->dado = dado;
    novo->prox = NULL;

    if(lista->comeco == NULL) {
        lista->comeco = novo;
        lista->fim = novo;
    } else {
         lista->fim->prox = novo;
         lista->fim = novo;
    }
    lista->tamanho++;
    return 1;
}

void* removerPosicao(Lista* lista, int posicao) {
    if(lista->comeco == NULL || posicao < 1 || posicao > lista->tamanho) return NULL;

    No* remover = NULL;
    No* anterior = NULL;
    void* dado_removido = NULL;

    anterior = lista->comeco;    
    if(posicao == 1) {
        remover = lista->comeco;
        lista->comeco = lista->comeco->prox;
        if(lista->comeco == NULL) {
            lista->fim = NULL;
        }
    } else {
        for(int i = 1 ; i < posicao - 1 ; i++) {
            anterior = anterior->prox;
        }
        remover = anterior->prox;
        anterior->prox = remover->prox;
        if(remover == lista->fim) {
            lista->fim = anterior;
        }
    }
    dado_removido = remover->dado;
    free(remover);
    lista->tamanho--;
    return dado_removido;
}

void* obterDadoPosicao(Lista* lista, int posicao) {
    if(lista == NULL || posicao < 1 || posicao > lista->tamanho) return NULL;

    No* atual = lista->comeco;
    for(int i = 1 ; i < posicao ; i++) { atual = atual->prox; }
    return atual->dado;
}

void imprimirLista(Lista* lista, void (*imprime)(const void*)) {
    if(lista == NULL || lista->comeco == NULL) {
        printf("\nInventario Vazio.\n");
        return;
    }

    No* atual = lista->comeco;
    int posicao = 1;
    while(atual != NULL) {
        printf("\n%d ", posicao);
        imprime(atual->dado);
        atual = atual->prox;
        posicao++;
    }
}

void liberarLista(Lista* lista) {
    if(lista == NULL) return;
    
    No* atual = lista->comeco;
    while(atual != NULL) {
        No* aux = atual;
        atual = atual->prox;
        free(aux->dado);
        free(aux);
    }
    free(lista);
}

int tamanhoLista(Lista* lista) {
    return lista->tamanho;
}

int isListaEmpty(Lista* lista) {
    if (!lista) return 1;
    return lista->tamanho == 0;
}