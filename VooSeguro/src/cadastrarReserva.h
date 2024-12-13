#ifndef CADASTRAR_RESERVA_H
#define CADASTRAR_RESERVA_H

#include <stdio.h>
#include <string.h>
#include "cadastrarPassageiro.h"
#include "cadastrarVoo.h"

#define MAX_RESERVAS 1000
#define PONTOS_POR_VOO 10

typedef struct {
   int codigo;
   int codigoVoo;
   int numeroAssento;
   int codigoPassageiro;
   float valorTotal;
} Reserva;

extern Reserva listaReservas[MAX_RESERVAS];
extern int qtdReservas;

// Funções de validação
int verificarDisponibilidadeAssento(int codigoVoo, int numeroAssento);
int validarPassageiroExiste(int codigoPassageiro);
int validarVooAtivo(int codigoVoo);

// Funções principais
void cadastrarReserva();
void baixarReserva();
void listarReservasPassageiro(int codigoPassageiro);
void atualizarPontosFidelidade(int codigoPassageiro);

#endif