#ifndef CADASTRAR_PASSAGEIRO_H
#define CADASTRAR_PASSAGEIRO_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PASSAGEIROS 100

typedef struct {
    int codigo;
    char nome[50];
    char endereco[100];
    char telefone[15];
    int fidelidade;
    int pontosFidelidade; 
} Passageiro;

extern Passageiro listaPassageiros[MAX_PASSAGEIROS];
extern int qtdPassageiros;

// Funções de validação
int validarNome(const char *nome);
int validarEndereco(const char *endereco);
int validarTelefone(const char *telefone);

// Funções principais
void cadastrarPassageiro();
void listarPassageiros();

#endif