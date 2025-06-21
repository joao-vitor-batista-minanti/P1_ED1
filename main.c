#include <stdio.h>
#include <stdlib.h>

#include "include/game/inventario.h"
#include "include/game/item.h"
#include "include/game/jogador.h"
#include "include/game/mapa.h"
#include "include/game/pilha.h"
#include "include/game/lista.h"


int main() {
    Jogador* jogador = criarJogador(1, 1, 100);
    Mapa* mapa = criarMapa();
    Pilha* historico_movimentos = criarPilha();

    inicializarMapa(mapa);
    popularMapa(mapa, 5, 5);

    int jogo_ativo = 1;
    char input;

    while(jogo_ativo) {
        desenharMapa(mapa, jogador);

        printf("Use W, A, S, D para mover\n");
        printf("MENU: [I] Inventario | [Z] Desfazer | [Q] Sair\n>");
        scanf(" %c", &input);
        limparBuffer();
        int next_x = jogador->pos_x;
        int next_y = jogador->pos_y;

        Posicao pos_atual = {jogador->pos_x, jogador->pos_y};
        switch(input) {
            case 'w': case 'W': next_y--; break;
            case 's': case 'S': next_y++; break;
            case 'a': case 'A': next_x--; break;
            case 'd': case 'D': next_x++; break;
            case 'i': case 'I':
                exibirMenuInventario(jogador);
                continue;
            case 'z': case 'Z':
                if(!isPilhaEmpty(historico_movimentos)) {
                    Posicao* pos_anterior = popPilha(historico_movimentos);
                    jogador->pos_x = pos_anterior->x;
                    jogador->pos_y = pos_anterior->y;
                    free(pos_anterior);
                } else {
                    printf("Nao ha Movimentos Para Desfazer\n");
                }
                continue;
            case 'q': case 'Q':
                jogo_ativo = 0;
                continue;       
            default:
                printf("Comando Invalido\n");
                continue; 
        }

        if(mapa->data[next_x][next_y] != PAREDE) {
        pushPilha(historico_movimentos, pos_atual.x, pos_atual.y);
        jogador->pos_x = next_x;
        jogador->pos_y = next_y;

        char title_atual = mapa->data[jogador->pos_y][jogador->pos_x];

        switch(title_atual) {
            case ITEM:
                printf("Voce Encontrou uma Pocao de Cura.\n");
                adicionarAoInventario(jogador->inventario, criarItem("Pocao de Cura", "Restaura 20 de Vida.", ITEM_POCAO_CURA, 20));
                mapa->data[jogador->pos_y][jogador->pos_y] = CAMINHO;
                break;
            case ARMADILHA:
                printf("Vocec Caiu em Uma Armadilha. -10 de Vida.\n");
                jogador->vida -= 10;
                break;
            case SAIDA:
                printf("Parabens, Voce encontrou a Saida.");
                jogo_ativo = 0;
                continue; 
        }
        if(jogador->vida <= 0) {
            printf("Game Over. Vida Zerada\n");
            jogo_ativo = 0;
        }
        } else {
            printf("Voce Bateu na Parede\n");
        }
        if(jogo_ativo) {
            printf("Pressione Enter para Continuar.\n");
            getchar();
        }
    }
    printf("\n=== FIM DE JOGO ===\n");
    liberarJogador(jogador);
    liberarMapa(mapa);
    liberarPilha(historico_movimentos);
    return 0;
}