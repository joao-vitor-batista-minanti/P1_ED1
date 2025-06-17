#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../include/game/mapa.h"

Mapa* criarMapa() {
    Mapa* novo = (Mapa*)malloc(sizeof(Mapa));
    if(novo != NULL) {
        return novo;
    }
}

void inicializarMapa(Mapa* mapa) {
    for(int y = 0 ; y < MAPA_ALTURA ; y++) {
        for(int x = 0 ; x < MAPA_LARGURA ; x++) {
            if(y == 0 || y == MAPA_ALTURA - 1 || x == 0 || x == MAPA_LARGURA - 1) {
                mapa->data[y][x] = PAREDE;
            } else {
                mapa->data[y][x] = CAMINHO;
            }
        }
    }
    // Posicao fixa (por enquanto)
    mapa->data[MAPA_ALTURA - 2][MAPA_LARGURA - 2] = SAIDA;
}

void popularMapa(Mapa* mapa, int num_item, int num_armadilhas) {
    srand(time(NULL));
    for(int i = 0 ; i < num_item ; i++) {
        int x, y;
        do {
            y = rand() % MAPA_ALTURA;
            x = rand() % MAPA_LARGURA;
        } while(mapa->data[y][x] != CAMINHO);
        mapa->data[y][x] = ITEM;
    }

    for(int i = 0 ; i < num_armadilhas ; i++) {
        int x, y;
        do {
            y = rand() % MAPA_ALTURA;
            x = rand() % MAPA_LARGURA;
        } while(mapa->data[y][x] != CAMINHO);
        mapa->data[y][x] = ARMADILHA;
    }
}

void desenharMapa(Mapa* mapa, Jogador* jogador) {
    system("cls" || "clear");
    printf("\n============ DUNGEON ============\n");
    for(int y = 0 ; y < MAPA_ALTURA ; y++) {
        for(int x = 0 ; x < MAPA_LARGURA ; x++) {
            if(x == jogador->pos_x && y == jogador->pos_y) {
                printf("%c", JOGADOR_CHAR);
            } else if (mapa->data[y][x] == ARMADILHA) {
                printf("%c", CAMINHO);
            }
            else {
                printf("%c", mapa->data[y][x]);
            }
        }
        printf("\n");
    }
    printf("===================================\n");
    printf("Vida: %d\n", jogador->vida);
}

void liberarMapa(Mapa* mapa) {
    free(mapa);
}