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
    char cargo[20];  // piloto, copiloto, comissário
} Tripulacao;

extern Tripulacao listaTripulacao[MAX_TRIPULACAO];
extern int qtdTripulacao;

// Funções de validação
int validarCargoTripulacao(const char *cargo);
int validarNomeTripulacao(const char *nome);
int validarTelefoneTripulacao(const char *telefone);

// Funções principais
void cadastrarTripulacao();
void listarTripulacao();
int verificarTripulacaoMinima(int codigoPiloto, int codigoCopiloto);

#endif