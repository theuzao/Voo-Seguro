#ifndef CADASTRAR_VOO_H
#define CADASTRAR_VOO_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "cadastrarTripulacao.h"

#define MAX_VOOS 100
#define MAX_ASSENTOS 50

typedef struct {
    int codigo;
    char data[11];
    char hora[6];
    char origem[50];
    char destino[50];
    int codigoAviao;
    int codigoPiloto;
    int codigoCopiloto;
    int codigoComissario;
    int status;
    float tarifa;
} Voo;

typedef struct {
    int numero;
    int codigoVoo;
    int status;
} Assento;

extern Voo listaVoos[MAX_VOOS];
extern Assento listaAssentos[MAX_VOOS][MAX_ASSENTOS];
extern int qtdVoos;

// Funções
int validarData(const char *data);
int validarHora(const char *hora);
int validarTripulacaoMinima(int codigoPiloto, int codigoCopiloto);
void cadastrarVoo();
void listarVoos();
void configurarAssentos(int codigoVoo);

#endif