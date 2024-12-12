#ifndef PESQUISA_H
#define PESQUISA_H

#include "cadastrarPassageiro.h"
#include "cadastrarTripulacao.h"
#include "cadastrarVoo.h"
#include "cadastrarReserva.h"

// Funções de pesquisa para passageiros
void pesquisarPassageiroPorCodigo(int codigo);
void pesquisarPassageiroPorNome(const char *nome);
void listarVoosPassageiro(int codigoPassageiro);

// Funções de pesquisa para tripulação
void pesquisarTripulacaoPorCodigo(int codigo);
void pesquisarTripulacaoPorNome(const char *nome);

// Funções para programa de fidelidade
void consultarPontosFidelidade(int codigoPassageiro);
void atualizarPontosFidelidade(int codigoPassageiro);

#endif