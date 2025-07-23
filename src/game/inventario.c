#include <stdio.h>
#include <stdlib.h>
#include "../../include/game/inventario.h"

void adicionarAoInventario(Jogador* jogador, Item* item) {
    if(!jogador || !item) {
        printf("ERRO AO ADICIONAR ITEM\n");
        return;
    }

    if(item->tipo == ITEM_MOEDA) {
        jogador->moedas += item->valor;
        printf("Você Coletou %d Moedas! Total: %d\n", item->valor, jogador->moedas);
        free(item);
    } else {
        int sucesso = inserirFim(jogador->inventario, (void*)item);
        if(!sucesso) {
            printf("ERRO: Nao Foi Possivel Adicionar o Item ao Inventario.\n");
            free(item);
            return;
        }
        printf("'%s' Foi Adicionado ao Inventario.\n", item->nome);
    }
}

void exibirInventario(Jogador* jogador) {
    printf("\n--- INVENTARIO ---\n");
    if(!jogador->inventario || !jogador) return;
    imprimirLista(jogador->inventario, imprimirItem);
    printf("------------------\n");
}

void usarItemDoInventario(Jogador* jogador, int posicao) {
    if(!jogador || !jogador->inventario) {
        printf("\nJogador Invalido\n");
        return;
    }

    if(posicao < 1 || posicao > tamanhoLista(jogador->inventario)) {
        printf("\nPosicao Invalida no Inventario.\n");
        return;
    } 

    Item* item = (Item*)obterDadoPosicao(jogador->inventario, posicao);
    if(item == NULL) {
        printf("\nPosicao Invalida do Inventario.");
        return;
    }

    printf("\nVoce usou: %s\n", item->nome);
    
    switch(item->tipo) {
        case ITEM_POCAO_CURA:
            if(jogador->vida <= 80) {
                jogador->vida += item->valor;
                printf("Sua Vida Aumentou em %d Pontos.\n", item->valor);
            } else {
                jogador->vida = 100;
                printf("Sua Vida Esta Cheia!\n");
            }
            removerPosicao(jogador->inventario, posicao);
            free(item);  
            break;
        
        case ITEM_REPELENTE:
            aplicarRepelente(jogador, item->valor);
            printf("Voce Esta Protegido de Encontros de Inimigos por %d Passos", item->valor);
            removerPosicao(jogador->inventario, posicao);
            free(item); 
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
            default: printf("\nOPCAO INVALIDA\n.");
        }
        printf("\nAperte Enter Para Continuar...");
        getInput();
    }    
}

void limparBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
