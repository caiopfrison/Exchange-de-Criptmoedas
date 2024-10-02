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

    int opcao;
    do {
        printf("\nMenu Principal\n");
        printf("1. Consultar Saldo\n");
        printf("2. Consultar Extrato\n");
        printf("3. Depositar R$\n");
        printf("4. Sacar R$\n");
        printf("5. Comprar Criptomoeda\n");
        printf("6. Vender Criptomoeda\n");
        printf("7. Atualizar Cotações\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                consultarSaldo(&usuarios[userIndex]);
                break;
            case 2:
                consultarExtrato(&usuarios[userIndex]);
                break;
            case 3:
                depositarBRL(&usuarios[userIndex]);
                salvarUsuarios(usuarios, qtdUsuarios);
                break;
            case 4:
                sacarBRL(&usuarios[userIndex]);
                salvarUsuarios(usuarios, qtdUsuarios);
                break;
            case 5:
                comprarCriptomoeda(&usuarios[userIndex], &cotacoes);
                salvarUsuarios(usuarios, qtdUsuarios);
                break;
            case 6:
                venderCriptomoeda(&usuarios[userIndex], &cotacoes);
                salvarUsuarios(usuarios, qtdUsuarios);
                break;
            case 7:
                atualizarCotacoes(&cotacoes);
                break;
            case 8: 
                cadastrarUsuario(usuarios, &qtdUsuarios);
                break;
            case 0:
                printf("Sessão finalizada.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while(opcao != 0);

    // Salva os dados antes de finalizar o programa
    salvarUsuarios(usuarios, qtdUsuarios);
    return 0;
}