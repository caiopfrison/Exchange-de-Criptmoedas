#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>


// Função que cadastra um novo usuário
int cadastrarUsuario(Usuario usuarios[], int *qtdUsuarios) {
    if (*qtdUsuarios >= MAX_USUARIOS) {
        printf("Limite máximo de usuários atingido.\n");
        return -1;
    }

    Usuario novoUsuario;
    char cpf[CPF_SIZE];
    char senha[SENHA_SIZE];

    printf("=== Cadastro de Novo Usuário ===\n");

    
// Entrada do CPF
    while (1) {
        printf("CPF (apenas números, 11 dígitos): ");
        scanf("%s", cpf);

        // Verificar se o CPF já existe
        if (encontrarUsuario(usuarios, *qtdUsuarios, cpf) != -1) {
            printf("CPF já cadastrado. Tente novamente.\n");
        } else if (strlen(cpf) != 11) {
            printf("CPF inválido. Deve conter exatamente 11 dígitos.\n");
        } else {
            break;
        }
    }
    strcpy(novoUsuario.cpf, cpf);

    // Entrada da Senha
    printf("Senha: ");
    scanf("%s", senha);
    strcpy(novoUsuario.senha, senha);

    // Inicializar saldos e transações
    novoUsuario.saldoBRL = 0.0;
    novoUsuario.saldoBitcoin = 0.0;
    novoUsuario.saldoEthereum = 0.0;
    novoUsuario.saldoRipple = 0.0;
    novoUsuario.qtdTransacoes = 0;

    // Adicionar o novo usuário ao array
    usuarios[*qtdUsuarios] = novoUsuario;
    (*qtdUsuarios)++;

    // Salvar os usuários atualizados no arquivo
    salvarUsuarios(usuarios, *qtdUsuarios);

    printf("Usuário cadastrado com sucesso!\n");
    printf("CPF: %s\n", novoUsuario.cpf);
    return 0;
}

// Inicializa as cotações com os valores padrão
void inicializarCotacoes(Cotacoes *cotacoes) {
  cotacoes->bitcoin = 50000.0; // Bitcoin inicial
  cotacoes->ethereum = 4000.0; // Ethereum inicial
  cotacoes->ripple = 1.0;      // Ripple inicial
}

// Função para obter data
void obterDataAtual(char *buffer) {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(buffer, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1,
          tm.tm_year + 1900);
}