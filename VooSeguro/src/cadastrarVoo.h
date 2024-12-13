#ifndef CADASTRAR_VOO_H
#define CADASTRAR_VOO_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "cadastrarTripulacao.h"

#define MAX_VOOS 100
#define MAX_ASSENTOS 50

typedef struct {
   int codigo;
   char data[11];     // DD/MM/AAAA
   char hora[6];      // HH:MM
   char origem[50];
   char destino[50];
   int codigoAviao;
   int codigoPiloto;
   int codigoCopiloto;
   int codigoComissario;
   int status;        // 1 = ativo, 0 = inativo
   float tarifa;
} Voo;

typedef struct {
   int numero;
   int codigoVoo;
   int status;        // 1 = ocupado, 0 = livre
} Assento;

extern Voo listaVoos[MAX_VOOS];
extern Assento listaAssentos[MAX_VOOS][MAX_ASSENTOS];
extern int qtdVoos;

// Funções de validação
int validarData(const char *data);
int validarHora(const char *hora);
int validarTarifa(float tarifa);
int validarTripulacaoCompleta(int codigoPiloto, int codigoCopiloto);

// Funções principais
void cadastrarVoo();
void listarVoos();
void configurarAssentos(int indiceVoo);
int verificarStatusVoo(int codigoVoo);

#endif