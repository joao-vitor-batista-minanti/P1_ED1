#ifndef LISTA_H
#define LISTA_H

typedef struct No {
    void* dado;
    struct No* prox;
}No;

typedef struct Lista {
    int tamanho;
    No* comeco;
    No* fim;
} Lista;

Lista* criarLista();
int inserirInicio(Lista* lista, void* dado);
int inserirFim(Lista* lista, void* dado);
void* removerPosicao(Lista* lista, int posicao);
void* obterDadoPosicao(Lista* lista, int posicao);
void imprimirLista(Lista* lista, void (*imprime)(const void*));
void liberarLista(Lista* lista);
int tamanhoLista(Lista* lista);
int isListaEmpty(Lista* lista);

#endif