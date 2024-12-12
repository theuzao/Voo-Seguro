#ifndef CADASTRAR_TRIPULACAO_H
#define CADASTRAR_TRIPULACAO_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TRIPULACAO 50

typedef struct {
    int codigo;
    char nome[50];
    char telefone[15];
    char cargo[20];
} Tripulacao;

// Variáveis globais
extern Tripulacao listaTripulacao[MAX_TRIPULACAO];
extern int qtdTripulacao;

// Funções
int validarTelefone(const char *telefone);
int validarCargo(const char *cargo);
void cadastrarTripulacao();
void listarTripulacao();

#endif