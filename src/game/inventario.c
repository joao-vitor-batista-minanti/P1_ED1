#include <stdio.h>
#include <stdlib.h>
#include "../../include/game/inventario.h"

void adicionarAoInventario(Jogador* jogador, Item* item) {
    if(!jogador || !item) return;

    if(item->tipo == ITEM_MOEDA) {
        jogador->moedas += item->valor;
        printf("Você Coletou %d Moedas! Total: %d\n", item->valor, jogador->moedas);
        free(item);
    } else {
        inserirFim(jogador->inventario, (void*)item);
        printf("'%s' foi adicionado ao inventario.\n", item->nome);
    }
}

void exibirInventario(Jogador* jogador) {
    printf("\n--- INVENTARIO ---\n");
    if(!jogador->inventario || !jogador) return;
    imprimirLista(jogador->inventario, imprimirItem);
    printf("------------------\n");
}

void usarItemDoInventario(Jogador* jogador, int posicao) {
    if(!jogador) {
        printf("\nJogador Invalido\n");
        return;
    }

    Item* item = (Item*)obterDadoPosicao(jogador->inventario, posicao);
    if(item == NULL) {
        printf("\nPosicao dada invalida no inventario.");
        return;
    }

    printf("\nVoce usou: %s", item->nome);
    
    switch(item->tipo) {
        case ITEM_POCAO_CURA:
            jogador->vida += item->valor;
            printf("\nSua Vida Aumentou em %d Pontos.\n", item->valor);
            free(removerPosicao(jogador->inventario, posicao));
            break;
        
        case ITEM_REPELENTE:
            adicionarEfeito(jogador, EFEITO_REPELENTE, item->valor);
            printf("Voce Esta Protegido de Encontros de Inimigos por %d Passos", item->valor);
            free(removerPosicao(jogador->inventario, posicao));
            break;
        case ITEM_MOEDA:
            printf("\nMoedas Sao Coletadas Automaticamente!\n");
            break;

        default: 
            printf("\nERRO: ITEM NAO RECONHECIDO\n");
            break;
    }
}

void descartarItemDoInventario(Jogador* jogador, int posicao) {
    void* dado_removido = removerPosicao(jogador->inventario, posicao);
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
        exibirInventario(jogador);
        printf("\nOpcoes:\n1. Usar Item\n2. Descartar Item\n3. Voltar\n> ");
        scanf("%d", &escolha);
        limparBuffer();
        if(escolha == 3) break;

        printf("Digite a posicao do item: ");
        scanf("%d", &posicao);
        switch(escolha) {
            case 1: usarItemDoInventario(jogador, posicao); break;
            case 2: descartarItemDoInventario(jogador, posicao); break;
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
