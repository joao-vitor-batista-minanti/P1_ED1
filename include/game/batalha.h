#ifndef BATALHA_H
#define BATALHA_H

#include "jogador.h"
#include "inimigo.h"

typedef enum {
    BATALHA_EM_ANDAMENTO,
    BATALHA_VITORIA_JOGADOR,
    BATALHA_VITORIA_INIMIGO
} EstadoBatalha;

void exibirTelaCombate(Jogador* jogador, Inimigo* inimigo);
void turnoDoJogador(Jogador* jogador, Inimigo* inimigo, int* jogador_defende, int* inimigo_defende);
void turnoDoInimigo(Jogador* jogador, Inimigo* inimigo, int* jogador_defende, int* inimigo_defende);
EstadoBatalha iniciarBatalha(Jogador* jogador, Inimigo* inimigo);

#endif