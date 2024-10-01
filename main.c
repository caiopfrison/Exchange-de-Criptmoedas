#include <stdio.h>
#include <string.h>
#include "funcoes.h"
#include <string.h>


int main() {
    Usuario usuarios[MAX_USUARIOS];
    Cotacoes cotacoes;
    inicializarCotacoes(&cotacoes);

    int qtdUsuarios = carregarUsuarios(usuarios);

    // Caso não haja usuário, solicitar cadastro de um novo usário
    if(qtdUsuarios == 0) {
        printf("Nenhum usuário encontrado. Por favor, cadastre um novo usuário.\n");
        if (cadastrarUsuario(usuarios, &qtdUsuarios) != 0) {
            printf("Falha no cadastro. Encerrando o programa.\n");
            return 0;
        }
    }

    int userIndex = -1;
    while(userIndex == -1) {
        userIndex = efetuarLogin(usuarios, qtdUsuarios);
        if(userIndex == -1) {
            printf("Deseja cadastrar um novo usuário? (1 - Sim, 0 - Não): ");;
            int escolha;
            scanf("%d", &escolha);
            if(escolha == 1) {
                if (cadastrarUsuario(usuarios, &qtdUsuarios) != 0);
                if(escolha == 0) {
                    printf("Sessão finalizada.\n");
                     return 0;
                }
                
               
            }
        }
    }