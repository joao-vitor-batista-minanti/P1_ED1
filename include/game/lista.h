#ifndef FILA_H
#define LISTA_H

#include <stdlib.h>

typedef struct No No;
typedef struct Lista Lista;

Lista* criarLista();
int inserirInicio(Lista* lista, void* dado);
int inserirFim(Lista* lista, void* dado);
void* removerPosicao(Lista* lista, int posicao);
void* obterDadoPosicao(Lista* lista, int posicao);
void imprimirLista(Lista* lista, void (*imprime)(const void*));
void liberarLista(Lista* lista);
int tamanhoLista(Lista* lista);

#endif