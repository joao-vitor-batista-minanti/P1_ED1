#include <stdio.h>
#include <stdlib.h>
#include "../../include/game/inventario.h"

void adicionarAoInventario(Lista* inven, Item* item) {
    if(!inven || !item) return;
    inserirFim(inven, (void*)item);
    printf("'%s' foi adicionado ao inventario.\n", item->nome);
}

void exibirInventario(Lista* inven) {
    printf("\n--- INVENTARIO ---\n");
    if(!inven) return;
    imprimirLista(inven, imprimirItem);
    printf("------------------\n");
}

void usarItemDoInventario(Lista* inven, int posicao /*, Jogador jogador*/) {
    Item* item = (Item*)obterDadoPosicao(inven, posicao);
    if(item == NULL) {
        printf("\nPosicao dada invalida no inventario.");
        return;
    }

    printf("\nVoce usou: %s", item->nome);
    if(item->tipo == ITEM_POCAO_CURA || item->tipo == ITEM_REPELENTE) {
        void* dado_removido = removerPosicao(inven, posicao);
        free(dado_removido);
    }
}

void descartarItemDoInventario(Lista* inven, int posicao) {
    void* dado_removido = removerPosicao(inven, posicao);
    if(dado_removido != NULL) {
        Item* item = (Item*)dado_removido;
        printf("\nItem Descartado: %s", item->nome);
        free(dado_removido);
        return;
    } else {
        printf("\nPosicao Invalida do Inventario.");
    }
}

void exibirMenuInventario(Jogador* jogador) {
    int escolha = 0;
    int posicao = 0;

    while(escolha != 3) {
        exibirInventario(jogador->inventario);
        printf("\nOpcoes:\n1. Usar Item\n2. Descartar Item\n3. Voltar\n> ");
        scanf("%d", &escolha);
        limparBuffer();
        if(escolha == 3) break;

        printf("Digite a posicao do item: ");
        scanf("%d", &posicao);
        switch(escolha) {
            case 1: usarItemDoInventario(jogador->inventario, posicao); break;
            case 2: descartarItemDoInventario(jogador->inventario, posicao); break;
            case 3: printf("Ue, como assim\n"); break;
            default: printf("\nOPCAO INVALIDA\n.");
        }
        printf("\nAperte enter para continuar...");
        getInput();
        desenharMapa(criarMapa(), jogador);
    }    
}

void limparBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
