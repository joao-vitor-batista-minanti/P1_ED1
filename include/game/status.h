#ifndef STATUS_H
#define STATUS_H

typedef enum {
    EFEITO_REPELENTE
} EfeitoTipo;

typedef struct {
    EfeitoTipo tipo;
    int duracao;
} Status;

Status* criarStatus(EfeitoTipo tipo, int duracao);
void imprimirStatus(void* dado);

#endif