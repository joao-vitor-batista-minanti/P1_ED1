#include <stdio.h>
#include <stdlib.h>
#include "../../include/game/batalha.h"
#include "../../include/game/arvore.h"
#include "../../include/game/inventario.h"

void exibirTelaCombate(Jogador* jogador, Inimigo* inimigo) {
    printf("\n\n--- BATALHA ---\n");
    printf("Jogador - Vida: %d\n", jogador->vida);
    printf("%s - Vida: %d\n", inimigo->nome, inimigo->vida);
    printf("----------------\n");
}

void turnoDoJogador(Jogador* jogador, Inimigo* inimigo, int* jogador_defende, int* inimigo_defende, int* fugiu) {
    char acao;
    printf("Seu turno! Escolha sua acao:\n");
    printf(" [A] Atacar\n");
    printf(" [D] Defender\n");
    printf(" [I] Usar Item\n");
    printf(" [F] Tentar Fugir\n");
    printf("> ");
    scanf(" %c", &acao);

    switch(acao) {
        case 'a': case 'A':{
            int dano = jogador->ataque;
            if(*inimigo_defende) {
                printf("O %s Tentou Defender seu Ataque!\n", inimigo->nome);
                if((rand() % 100) < 45) {
                    printf("Defesa do Inimigo Funcionou! Ataque Falhou.\n");
                    dano = 0;
                } else {
                    printf("Defesa do Inimigo Falhou! Ataque Bem Sucedido.\n"); 
                }
                *inimigo_defende = 0;
            }
            inimigo->vida -= dano;
            printf("Voce Ataca o %s, Causando %d de Dano!\n", inimigo->nome, dano);
            break;
        }

        case 'd': case 'D':
            printf("Voce Assume Uma Postura Defensiva.\n");
            *jogador_defende = 1;
            break;

        case 'i': case 'I':
            exibirInventario(jogador);
            if (isListaEmpty(jogador->inventario)) {
                 printf("Voce Nao Tem Itens Para Usar.\n");
            } else {
                printf("Digite a Posicao do Item que Deseja Usar: ");
                int pos;
                scanf("%d", &pos);
                usarItemDoInventario(jogador, pos);
            }
            break;

        case 'f': case 'F': {
            double chance = ((double)jogador->vida / jogador->vida_max * (double)inimigo->vida / inimigo->vida_max * (1 - (double)inimigo->vida / inimigo->vida_max)) * 100;
            if ((rand() % 100) < chance) {
                printf("Voce Conseguiu Fugir!\n");
                *fugiu = 1; 
            } else {
                printf("A Fuga Falhou!\n");
            }
            break;
        }

        default:
            printf("Acao Invalida! Voce Perdeu o Turno.\n");
            break;
    }
}

void turnoDoInimigo(Jogador* jogador, Inimigo* inimigo, int* jogador_defende, int* inimigo_defende) {
    printf("Turno do %s!\n", inimigo->nome);

    AcaoInimigo acao = decidirAcao(inimigo->ia_arvore, jogador, inimigo);

    switch(acao) {
        case ACAO_ATACAR: {
            int dano = inimigo->ataque;
            if(*jogador_defende) {
                printf("Voce Tentou Defender o Ataque do %s!\n", inimigo->nome);
                if((rand() % 100) < 45) {
                    printf("Defesa Bem Sucedida! Dano Negado.\n");
                    dano = 0;
                } else {
                    printf("Defesa Falhou! Dano Recebido.\n");
                }
                *jogador_defende = 0;
            }
            jogador->vida -= dano;
            printf("O %s Ataca, Causando %d de Dano!\n", inimigo->nome, dano);
            break;
        }

        case ACAO_DEFENDER: {
            printf("O %s Assume Uma Postura Defensiva!\n", inimigo->nome);
            *inimigo_defende = 1;
            break;
        }

        case ACAO_USAR_CURA: {
            if(inimigo->limite_cura >= 0) {
                int cura = 10;
                inimigo->vida += cura;
                printf("O %s Usa uma Habilidade De Cura e Recupera Vida!\n", inimigo->nome);
                inimigo->limite_cura--;
                break;
            } else {
                jogador->vida -= inimigo->ataque;
                printf("O %s Tentou Se Curar, Mas Falhou e Conseguiu Atingir um Golpe, Causando %d de Dano!\n", inimigo->nome, inimigo->ataque);
            }
        }
    }
}


EstadoBatalha iniciarBatalha(Jogador* jogador, Inimigo* inimigo) {
    int jogador_defende = 0;
    int inimigo_defende = 0;
    int fugiu = 0;

    while (jogador->vida > 0 && inimigo->vida > 0) {
        exibirTelaCombate(jogador, inimigo);
        turnoDoJogador(jogador, inimigo, &jogador_defende, &inimigo_defende, &fugiu);

        if (fugiu) {
            return BATALHA_EM_ANDAMENTO;
        }

        if (inimigo->vida <= 0) {
            break;
        }

        exibirTelaCombate(jogador, inimigo);
        turnoDoInimigo(jogador, inimigo, &jogador_defende, &inimigo_defende);
    }

    if (inimigo->vida <= 0) {
        printf("\nVoce Derrotou o %s!\n", inimigo->nome);
        return BATALHA_VITORIA_JOGADOR;
    } else {
        printf("\nVoce foi derrotado!\n");
        return BATALHA_VITORIA_INIMIGO;
    }
}