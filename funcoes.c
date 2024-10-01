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