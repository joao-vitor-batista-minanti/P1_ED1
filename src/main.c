#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/game/inventario.h"
#include "../include/game/item.h"
#include "../include/game/jogador.h"
#include "../include/game/mapa.h"
#include "../include/game/pilha.h"
#include "../include/game/lista.h"
#include "../include/utils/input_handler.h"
#include "../include/game/batalha.h"

int main() {
    srand(time(NULL));
    Jogador* jogador = criarJogador(1, 1, 100);
    if(jogador == NULL) {
        printf("Erro ao criar jogador.\n");
        return 1;
    }

    Mapa* mapa = criarMapa();
    if(mapa == NULL) {
        printf("Erro ao criar mapa.\n");
        liberarJogador(jogador);
        return 1;
    }

    Pilha* historico_movimentos = criarPilha();
    if(historico_movimentos == NULL) {
        printf("Erro ao criar pilha de movimentos.\n");
        liberarJogador(jogador);
        liberarMapa(mapa);
        return 1;
    }

    inicializarMapa(mapa);
    popularMapa(mapa, jogador, 5, 5, 5);

    int jogo_ativo = 1;
    char input;

    while(jogo_ativo) {
        desenharMapa(mapa, jogador);
        atualizarEfeito(jogador);

        printf("Use W, A, S, D para mover\n");
        printf("MENU: [I] Inventario | [Z] Desfazer | [Q] Sair\n>");
        input = getInput();
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
                    if(pos_anterior != NULL) {
                        jogador->pos_x = pos_anterior->x;
                        jogador->pos_y = pos_anterior->y;
                        free(pos_anterior);
                    } else {
                        printf("ERRO: NAO EXISTE MOVIMENTOS ANTERIORES.\n");
                    }
                } else {
                    printf("Nao ha Movimentos Para Desfazer\n");
                }
                continue;

            case 'q': case 'Q':
                jogo_ativo = 0;
                continue;
        }

        if(mapa->data[next_y][next_x] != PAREDE) {
            pushPilha(historico_movimentos, pos_atual.x, pos_atual.y);
            jogador->pos_x = next_x;
            jogador->pos_y = next_y; 

            switch(mapa->data[jogador->pos_y][jogador->pos_x]) {
                case ITEM: {
                    int tipo_aleatorio = rand() % 3;
                    Item* item_encontrado;

                    switch(tipo_aleatorio) {
                        case 0:
                            item_encontrado = criarItem("Pocao de Cura", "Restaura 20 de Vida.", ITEM_POCAO_CURA, 20);
                            break;
                        case 1:
                            item_encontrado = criarItem("Repelente", "Evita inimigos por 5 passos", ITEM_REPELENTE, 5);
                            break;
                        case 2:
                            item_encontrado = criarItem("Moedas", "Dinheiro do jogo", ITEM_MOEDA, 10);
                            break;
                    }
                    adicionarAoInventario(jogador, item_encontrado);
                    mapa->data[jogador->pos_y][jogador->pos_x] = CAMINHO;
                    break;
                }

                case INIMIGO:
                    if(jogadorTemEfeito(jogador)) {
                        printf("Inimigo Afastado Pelo Repelente.\n");
                        mapa->data[jogador->pos_y][jogador->pos_x] = CAMINHO;
                        break;
                    }

                    printf("Voce Encontrou um Inimigo!\n");

                    Inimigo* inimigo = criarInimigo("Goblin", 40, 5); 
                    EstadoBatalha resultado = iniciarBatalha(jogador, inimigo);
                    if(resultado == BATALHA_VITORIA_JOGADOR) {
                        mapa->data[jogador->pos_y][jogador->pos_x] = CAMINHO;
                        jogador->moedas += 10;
                    } else if(resultado == BATALHA_VITORIA_INIMIGO) {
                        jogo_ativo = 0;
                    } else if (resultado == BATALHA_EM_ANDAMENTO) {
                        printf("Voce Fugiu da Batalha.\n");
                        mapa->data[jogador->pos_y][jogador->pos_x] = CAMINHO;
                    }
                    liberarInimigo(inimigo);
                    break;

                case ARMADILHA:
                    printf("Voce Caiu em Uma Armadilha. -10 de Vida.\n");
                    jogador->vida -= 10;
                    break;

                case SAIDA:
                    printf("\n\nParabens, Voce Chegou a Saida.\n");
                    printf("Moedas Coletadas: %d\n", jogador->moedas);
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
            // getchar();
        }
    }
    printf("=== FIM DE JOGO ===\n\n");
    liberarJogador(jogador);
    liberarMapa(mapa);
    liberarPilha(historico_movimentos);
    system("pause");
    return 0;
}