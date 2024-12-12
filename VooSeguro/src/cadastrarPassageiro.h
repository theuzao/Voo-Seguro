#ifndef CADASTRAR_PASSAGEIRO_H
#define CADASTRAR_PASSAGEIRO_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Definições e limites
#define MAX_PASSAGEIROS 100

// Estrutura para passageiros
typedef struct {
    int codigo;
    char nome[50];
    char endereco[100];
    char telefone[15];
    int fidelidade;
} Passageiro;

// Declaração de variáveis globais (extern indica que serão definidas em outro arquivo)
extern Passageiro listaPassageiros[MAX_PASSAGEIROS];
extern int qtdPassageiros;

// Declaração das funções (protótipos)
int validarNumeros(const char *entrada);
int validarEndereco(const char *endereco);
void cadastrarPassageiro();
void listarPassageiros();

#endif