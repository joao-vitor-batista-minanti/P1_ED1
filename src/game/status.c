#include <stdio.h>
#include <stdlib.h>
#include "../../include/game/status.h"

Status* criarStatus(EfeitoTipo tipo, int duracao) {
    Status* novo_status = (Status*)malloc(sizeof(Status));
    if (novo_status != NULL) {
        novo_status->tipo = tipo;
        novo_status->duracao = duracao;
    }
    return novo_status;
}

void imprimirStatus(void* dado) {
    if (dado == NULL) return;
    Status* s = (Status*)dado;
    switch(s->tipo) {
        case EFEITO_REPELENTE:
            printf(" - Efeito: Repelente (Duracao: %d passos)\n", s->duracao);
            break;
        default:
            printf(" - Efeito: Desconhecido (Duracao: %d)\n", s->duracao);
            break;
    }
}