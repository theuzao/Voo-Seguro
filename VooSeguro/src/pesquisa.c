#include "pesquisa.h"
#include <string.h>
#include <ctype.h>

// Constantes para níveis de fidelidade
#define NIVEL_OURO 100
#define NIVEL_PRATA 50

// Função auxiliar para comparar strings ignorando maiúsculas/minúsculas
int comparaStringsCase(const char *s1, const char *s2) {
    if (!s1 || !s2) return 0;
    
    while (*s1 && *s2) {
        if (tolower(*s1) != tolower(*s2)) {
            return 0;
        }
        s1++;
        s2++;
    }
    return *s1 == *s2;
}

void pesquisarPassageiroPorCodigo(int codigo) {
    for (int i = 0; i < qtdPassageiros; i++) {
        if (listaPassageiros[i].codigo == codigo) {
            printf("\n=== Passageiro Encontrado ===\n");
            printf("Código: %d\n", listaPassageiros[i].codigo);
            printf("Nome: %s\n", listaPassageiros[i].nome);
            printf("Endereço: %s\n", listaPassageiros[i].endereco);
            printf("Telefone: %s\n", listaPassageiros[i].telefone);
            printf("Fidelidade: %s\n", listaPassageiros[i].fidelidade ? "Sim" : "Não");
            return;
        }
    }
    printf("Passageiro não encontrado!\n");
}

void pesquisarPassageiroPorNome(const char *nome) {
    int encontrou = 0;
    for (int i = 0; i < qtdPassageiros; i++) {
        if (comparaStringsCase(listaPassageiros[i].nome, nome)) {
            printf("\n=== Passageiro Encontrado ===\n");
            printf("Código: %d\n", listaPassageiros[i].codigo);
            printf("Nome: %s\n", listaPassageiros[i].nome);
            printf("Endereço: %s\n", listaPassageiros[i].endereco);
            printf("Telefone: %s\n", listaPassageiros[i].telefone);
            printf("Fidelidade: %s\n", listaPassageiros[i].fidelidade ? "Sim" : "Não");
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhum passageiro encontrado com este nome!\n");
    }
}

void pesquisarTripulacaoPorCodigo(int codigo) {
    for (int i = 0; i < qtdTripulacao; i++) {
        if (listaTripulacao[i].codigo == codigo) {
            printf("\n=== Tripulante Encontrado ===\n");
            printf("Código: %d\n", listaTripulacao[i].codigo);
            printf("Nome: %s\n", listaTripulacao[i].nome);
            printf("Cargo: %s\n", listaTripulacao[i].cargo);
            printf("Telefone: %s\n", listaTripulacao[i].telefone);
            return;
        }
    }
    printf("Tripulante não encontrado!\n");
}

void pesquisarTripulacaoPorNome(const char *nome) {
    int encontrou = 0;
    for (int i = 0; i < qtdTripulacao; i++) {
        if (comparaStringsCase(listaTripulacao[i].nome, nome)) {
            printf("\n=== Tripulante Encontrado ===\n");
            printf("Código: %d\n", listaTripulacao[i].codigo);
            printf("Nome: %s\n", listaTripulacao[i].nome);
            printf("Cargo: %s\n", listaTripulacao[i].cargo);
            printf("Telefone: %s\n", listaTripulacao[i].telefone);
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhum tripulante encontrado com este nome!\n");
    }
}

void listarVoosPassageiro(int codigoPassageiro) {
    int encontrou = 0;
    printf("\n=== Voos do Passageiro ===\n");
    
    for (int i = 0; i < qtdReservas; i++) {
        if (listaReservas[i].codigoPassageiro == codigoPassageiro) {
            for (int j = 0; j < qtdVoos; j++) {
                if (listaVoos[j].codigo == listaReservas[i].codigoVoo) {
                    printf("\nVoo: %d\n", listaVoos[j].codigo);
                    printf("Data: %s\n", listaVoos[j].data);
                    printf("Hora: %s\n", listaVoos[j].hora);
                    printf("Origem: %s\n", listaVoos[j].origem);
                    printf("Destino: %s\n", listaVoos[j].destino);
                    printf("Assento: %d\n", listaReservas[i].numeroAssento);
                    printf("Status: %s\n", listaVoos[j].status ? "Ativo" : "Inativo");
                    printf("--------------------\n");
                    encontrou = 1;
                }
            }
        }
    }
    if (!encontrou) {
        printf("Nenhum voo encontrado para este passageiro!\n");
    }
}

void atualizarPontosFidelidade(int codigoPassageiro) {
    if (codigoPassageiro <= 0) return;

    for (int i = 0; i < qtdPassageiros; i++) {
        if (listaPassageiros[i].codigo == codigoPassageiro) {
            if (listaPassageiros[i].fidelidade) {
                int pontos = PONTOS_POR_VOO;
                printf("\n=== Pontos Adicionados ===\n");
                printf("Pontos: %d\n", pontos);
                printf("Mantenha seu cadastro ativo para acumular mais pontos!\n");
            } else {
                printf("Passageiro não participa do programa de fidelidade.\n");
            }
            return;
        }
    }
    printf("Passageiro não encontrado!\n");
}

void consultarPontosFidelidade(int codigoPassageiro) {
    if (codigoPassageiro <= 0) {
        printf("Código de passageiro inválido!\n");
        return;
    }

    int totalPontos = 0;
    int totalVoos = 0;
    
    for (int i = 0; i < qtdReservas; i++) {
        if (listaReservas[i].codigoPassageiro == codigoPassageiro) {
            totalVoos++;
            totalPontos += PONTOS_POR_VOO;
        }
    }

    for (int i = 0; i < qtdPassageiros; i++) {
        if (listaPassageiros[i].codigo == codigoPassageiro) {
            if (listaPassageiros[i].fidelidade) {
                printf("\n=== Programa de Fidelidade ===\n");
                printf("Passageiro: %s\n", listaPassageiros[i].nome);
                printf("Total de voos: %d\n", totalVoos);
                printf("Pontos acumulados: %d\n", totalPontos);
                printf("Nível: %s\n", 
                    totalPontos >= NIVEL_OURO ? "Ouro" :
                    totalPontos >= NIVEL_PRATA ? "Prata" : "Bronze");
                printf("Próximo nível em: %d pontos\n", 
                    totalPontos >= NIVEL_OURO ? 0 :
                    totalPontos >= NIVEL_PRATA ? NIVEL_OURO - totalPontos :
                    NIVEL_PRATA - totalPontos);
            } else {
                printf("Este passageiro não participa do programa de fidelidade.\n");
                printf("Cadastre-se para começar a acumular pontos!\n");
            }
            return;
        }
    }
    printf("Passageiro não encontrado!\n");
}