#ifndef STRUCTS_H
#define STRUCTS_H

#include <time.h>

#define MAX_USUARIOS 10
#define MAX_TRANSACOES 100
#define CPF_SIZE 12
#define SENHA_SIZE 20
#define DATA_SIZE 20

typedef enum {
    COMPRA,
    VENDA
} TipoOperacao;

typedef enum {
    BITCOIN,
    ETHEREUM,
    RIPPLE,
    NONE
} Criptomoeda;

typedef struct {
    char data[DATA_SIZE];
    TipoOperacao tipo;
    double valor;
    double taxa;
    Criptomoeda moeda;
} Transacao;

typedef struct {
    char cpf[CPF_SIZE];
    char senha[SENHA_SIZE];
    double saldoBRL;
    double saldoBitcoin;
    double saldoEthereum;
    double saldoRipple;
    Transacao transacoes[MAX_TRANSACOES];
    int qtdTransacoes;
} Usuario;

typedef struct {
    double bitcoin;
    double ethereum;
    double ripple;
} Cotacoes;

#endif
