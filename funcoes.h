#ifndef FUNCOES_H
#define FUNCOES_H

#include "structs.h"

//Função que cadastra um novo usuário
int cadastrarUsuario(Usuario usuarios[], int *qtdUsuarios);

// Função que gerencia os usuários
int carregarUsuarios(Usuario usuarios[]);
void salvarUsuarios(Usuario usuarios[], int qtd);
int encontrarUsuario(Usuario usuarios[], int qtd, char *cpf);
void registrarTransacao(Usuario *usuario, TipoOperacao tipo, double valor,
                        double taxa, Criptomoeda moeda);
// Função auxiliar
void obterDataAtual(char *buffer);

// Função de autenticação
int efetuarLogin(Usuario usuarios[], int qtd);

// Função das operações financeiras
void consultarSaldo(Usuario *usuario);
void consultarExtrato(Usuario *usuario);
void depositarBRL(Usuario *usuario);
void sacarBRL(Usuario *usuario);
void comprarCriptomoeda(Usuario *usuario, Cotacoes *cotacoes);
void venderCriptomoeda(Usuario *usuario, Cotacoes *cotacoes);
void atualizarCotacoes(Cotacoes *cotacoes);

#endif
