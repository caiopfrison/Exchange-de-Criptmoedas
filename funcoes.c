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