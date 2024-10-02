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

// Função para carregar usuários do arquivo binário
int carregarUsuarios(Usuario usuarios[]) {
  FILE *file = fopen("usuarios.bin", "rb");
  if (file == NULL) {
    return 0;
  }
  int i = 0;
  while (i < MAX_USUARIOS &&
         fread(&usuarios[i], sizeof(Usuario), 1, file) == 1) {
    i++;
  }
  fclose(file);
  return i;
}

// Função para salvar os usuários no arquivo binário
void salvarUsuarios(Usuario usuarios[], int qtd) {
  FILE *file = fopen("usuarios.bin", "wb");
  if (file == NULL) {
    printf("Erro ao salvar dados.\n");
    return;
  }
  fwrite(usuarios, sizeof(Usuario), qtd, file);
  fclose(file);
}

// Função para encontrar o índice do usuário pelo CPF
int encontrarUsuario(Usuario usuarios[], int qtd, char *cpf) {
  for (int i = 0; i < qtd; i++) {
    if (strcmp(usuarios[i].cpf, cpf) == 0) {
      return i;
    }
  }
  return -1;
}

// Registra uma transação
void registrarTransacao(Usuario *usuario, TipoOperacao tipo, double valor,
                        double taxa, Criptomoeda moeda) {
  if (usuario->qtdTransacoes >= MAX_TRANSACOES) {
    printf("Limite de transações alcançado.\n");
    return;
  }
  Transacao t;
  obterDataAtual(t.data);
  t.tipo = tipo;
  t.valor = valor;
  t.taxa = taxa;
  t.moeda = moeda;
  usuario->transacoes[usuario->qtdTransacoes++] = t;
}

// Função de login
int efetuarLogin(Usuario usuarios[], int qtd) {
  char cpf[CPF_SIZE];
  char senha[SENHA_SIZE];
  printf("Login\n");
  printf("CPF: ");
  scanf("%s", cpf);
  printf("Senha: ");
  scanf("%s", senha);

  int idx = encontrarUsuario(usuarios, qtd, cpf);
  if (idx == -1) {
    printf("Não encontrado.\n");
    return -1;
  }
  if (strcmp(usuarios[idx].senha, senha) != 0) {
    printf("Senha incorreta.\n");
    return -1;
  }
  printf("Login feito com sucesso!\n");
  return idx;
}

// Função para consultar saldo
void consultarSaldo(Usuario *usuario) {
  printf("\nSaldo da Carteira\n");
  printf("R$: %.2lf\n", usuario->saldoBRL);
  printf("Bitcoin: %.6lf\n", usuario->saldoBitcoin);
  printf("Ethereum: %.6lf\n", usuario->saldoEthereum);
  printf("Ripple: %.6lf\n", usuario->saldoRipple);
}

// Função para consultar extrato
void consultarExtrato(Usuario *usuario) {
  printf("\nExtrato\n");
  printf("CPF: %s\n", usuario->cpf);
  for (int i = 0; i < usuario->qtdTransacoes; i++) {
    Transacao t = usuario->transacoes[i];
    printf("Data: %s | ", t.data);
    printf("Tipo: %s | ", t.tipo == COMPRA ? "Compra" : "Venda");
    printf("Moeda: ");
    switch (t.moeda) {
    case BITCOIN:
      printf("Bitcoin");
      break;
    case ETHEREUM:
      printf("Ethereum");
      break;
    case RIPPLE:
      printf("Ripple");
      break;
    default:
      printf("Nenhuma");
    }
    printf(" | Valor: %.2lf | Taxa: %.2lf\n", t.valor, t.taxa);
  }

  // Salvar em arquivo texto
  FILE *file = fopen("extrato.txt", "w");
  if (file == NULL) {
    printf("Erro ao salvar extrato.\n");
    return;
  }
  fprintf(file, "Extrato\n");
  fprintf(file, "CPF: %s\n", usuario->cpf);
  for (int i = 0; i < usuario->qtdTransacoes; i++) {
    Transacao t = usuario->transacoes[i];
    fprintf(file, "Data: %s | Tipo: %s | Moeda: ", t.data,
            t.tipo == COMPRA ? "Compra" : "Venda");
    switch (t.moeda) {
    case BITCOIN:
      fprintf(file, "Bitcoin");
      break;
    case ETHEREUM:
      fprintf(file, "Ethereum");
      break;
    case RIPPLE:
      fprintf(file, "Ripple");
      break;
    default:
      fprintf(file, "Nenhuma");
    }
    fprintf(file, " | Valor: %.2lf | Taxa: %.2lf\n", t.valor, t.taxa);
  }
  fclose(file);
}

// Função para depositar em reais
void depositarBRL(Usuario *usuario) {
  double valor;
  printf("\nDepositar Reais\n");
  printf("Valor a depositar: ");
  scanf("%lf", &valor);
  if (valor <= 0) {
    printf("Valor inválido.\n");
    return;
  }
  usuario->saldoBRL += valor;
  registrarTransacao(usuario, COMPRA, valor, 0.0,
                     NONE);
  printf("Depósito realizado com sucesso!\n");
}
// Função para sacar em reais
void sacarBRL(Usuario *usuario) {
  double valor;
  char senha[SENHA_SIZE];
  printf("\nSacar Reais\n");
  printf("Valor a sacar: ");
  scanf("%lf", &valor);
  if (valor <= 0) {
    printf("Valor inválido.\n");
    return;
  }
  if (usuario->saldoBRL < valor) {
    printf("Saldo insuficiente.\n");
    return;
  }
  printf("Confirme sua senha: ");
  scanf("%s", senha);
  if (strcmp(usuario->senha, senha) != 0) {
    printf("Senha incorreta.\n");
    return;
  }
  usuario->saldoBRL -= valor;
  registrarTransacao(usuario, VENDA, valor, 0.0, NONE);
  printf("Realizado com sucesso!\n");
}


// Função para obter a taxa de compra
double taxaCompra(int moeda) {
  switch (moeda) {
  case BITCOIN:
    return 0.02;
  case ETHEREUM:
    return 0.01;
  case RIPPLE:
    return 0.01;
  default:
    return 0.0;
  }
}
// Função para obter a taxa de venda
double taxaVenda(int moeda) {
  switch (moeda) {
  case BITCOIN:
    return 0.03;
  case ETHEREUM:
    return 0.02;
  case RIPPLE:
    return 0.01;
  default:
    return 0.0;
  }
}
// Função para comprar criptomoeda
void comprarCriptomoeda(Usuario *usuario, Cotacoes *cotacoes) {
  int escolha;
  double valor;
  char senha[SENHA_SIZE];
  printf("\nComprar Criptomoeda\n");
  printf("Selecione a moeda:\n1. Bitcoin\n2. Ethereum\n3. Ripple\nEscolha: ");
  scanf("%d", &escolha);
  Criptomoeda moeda;
  double taxa;
  double precoAtual;

  switch (escolha) {
  case 1:
    moeda = BITCOIN;
    precoAtual = cotacoes->bitcoin;
    taxa = taxaCompra(moeda);
    break;
  case 2:
    moeda = ETHEREUM;
    precoAtual = cotacoes->ethereum;
    taxa = taxaCompra(moeda);
    break;
  case 3:
    moeda = RIPPLE;
    precoAtual = cotacoes->ripple;
    taxa = taxaCompra(moeda);
    break;
  default:
    printf("Opção inválida.\n");
    return;
  }

  printf("Valor em BRL para compra: ");
  scanf("%lf", &valor);
  if (valor <= 0) {
    printf("Valor inválido.\n");
    return;
  }
  printf("Confirme sua senha: ");
  scanf("%s", senha);
  if (strcmp(usuario->senha, senha) != 0) {
    printf("Senha incorreta.\n");
    return;
  }

  double valorComTaxa = valor * (1 + taxa);
  if (usuario->saldoBRL < valorComTaxa) {
    printf("Saldo insuficiente.\n");
    return;
  }

  double quantidade = valor / precoAtual;
  usuario->saldoBRL -= valorComTaxa;

  switch (moeda) {
  case BITCOIN:
    usuario->saldoBitcoin += quantidade;
    break;
  case ETHEREUM:
    usuario->saldoEthereum += quantidade;
    break;
  case RIPPLE:
    usuario->saldoRipple += quantidade;
    break;
  default:
    break;
  }

  registrarTransacao(usuario, COMPRA, valor, valor * taxa, moeda);
  printf("Compra realizada!\n");
  printf("Quantidade comprada: %.6lf %s\n", quantidade,
         moeda == BITCOIN ? "Bitcoin"
                          : (moeda == ETHEREUM ? "Ethereum" : "Ripple"));
  printf("Taxa cobrada: %.2lf BRL\n", valor * taxa);
}

// Função para vender criptomoeda
void venderCriptomoeda(Usuario *usuario, Cotacoes *cotacoes) {
  int escolha;
  double quantidade;
  char senha[SENHA_SIZE];
  printf("\nVender Criptomoeda\n");
  printf("Selecione a moeda:\n1. Bitcoin\n2. Ethereum\n3. Ripple\nEscolha: ");
  scanf("%d", &escolha);
  Criptomoeda moeda;
  double taxa;
  double precoAtual;

  switch (escolha) {
  case 1:
    moeda = BITCOIN;
    precoAtual = cotacoes->bitcoin;
    taxa = taxaVenda(moeda);
    break;
  case 2:
    moeda = ETHEREUM;
    precoAtual = cotacoes->ethereum;
    taxa = taxaVenda(moeda);
    break;
  case 3:
    moeda = RIPPLE;
    precoAtual = cotacoes->ripple;
    taxa = taxaVenda(moeda);
    break;
  default:
    printf("Opção inválida.\n");
    return;
  }

  printf("Quantidade a vender: ");
  scanf("%lf", &quantidade);
  if (quantidade <= 0) {
    printf("Quantidade inválida.\n");
    return;
  }
  // Verifica saldo da criptomoeda
  switch (moeda) {
  case BITCOIN:
    if (usuario->saldoBitcoin < quantidade) {
      printf("Saldo insuficiente de Bitcoin.\n");
      return;
    }
    break;
  case ETHEREUM:
    if (usuario->saldoEthereum < quantidade) {
      printf("Saldo insuficiente de Ethereum.\n");
      return;
    }
    break;
  case RIPPLE:
    if (usuario->saldoRipple < quantidade) {
      printf("Saldo insuficiente de Ripple.\n");
      return;
    }
    break;
  default:
    break;
  }

  printf("Confirme sua senha: ");
  scanf("%s", senha);
  if (strcmp(usuario->senha, senha) != 0) {
    printf("Senha incorreta.\n");
    return;
  }

  double valor = quantidade * precoAtual;
  double valorComTaxa = valor * (1 - taxa);
  