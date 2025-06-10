#ifndef FILA_H
#define LISTA_H

#include <stdlib.h>

typedef struct Node Node;
typedef struct Lista Lista;

Lista* criarLista(size_t);
int inserirInicio(Lista*, void*);
void inserirFim(Lista*, void*);
void removerNo(Lista*, void*);
void imprimirLista(Lista*, void (*imprime)(const void*));
void liberarLista(Lista*);

#endif