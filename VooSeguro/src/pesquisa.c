#include "pesquisa.h"
#include <string.h>
#include <ctype.h>

// Funções auxiliares e de pesquisa já existentes...

void atualizarPontosFidelidade(int codigoPassageiro) {
    for (int i = 0; i < qtdPassageiros; i++) {
        if (listaPassageiros[i].codigo == codigoPassageiro) {
            listaPassageiros[i].pontosFidelidade += PONTOS_POR_VOO;  // Incrementa os pontos
            printf("Pontos atualizados! Pontos atuais: %d\n", listaPassageiros[i].pontosFidelidade);
            return;
        }
    }
    printf("Passageiro não encontrado para atualizar os pontos.\n");
}

void consultarPontosFidelidade(int codigoPassageiro) {
    for (int i = 0; i < qtdPassageiros; i++) {
        if (listaPassageiros[i].codigo == codigoPassageiro) {
            printf("Pontos de fidelidade do passageiro %s: %d\n", listaPassageiros[i].nome, listaPassageiros[i].pontosFidelidade);
            return;
        }
    }
    printf("Passageiro não encontrado.\n");
}

void limparBufferPesquisa() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

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
    printf("\n=== Resultado da Pesquisa ===\n");
    
    for (int i = 0; i < qtdPassageiros; i++) {
        if (strstr(listaPassageiros[i].nome, nome) != NULL) {
            printf("\nPassageiro %d:\n", i+1);
            printf("Código: %d\n", listaPassageiros[i].codigo);
            printf("Nome: %s\n", listaPassageiros[i].nome);
            printf("Endereço: %s\n", listaPassageiros[i].endereco);
            printf("Telefone: %s\n", listaPassageiros[i].telefone);
            printf("Fidelidade: %s\n", listaPassageiros[i].fidelidade ? "Sim" : "Não");
            printf("----------------------------\n");
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
    printf("\n=== Resultado da Pesquisa ===\n");
    
    for (int i = 0; i < qtdTripulacao; i++) {
        if (strstr(listaTripulacao[i].nome, nome) != NULL) {
            printf("\nTripulante %d:\n", i+1);
            printf("Código: %d\n", listaTripulacao[i].codigo);
            printf("Nome: %s\n", listaTripulacao[i].nome);
            printf("Cargo: %s\n", listaTripulacao[i].cargo);
            printf("Telefone: %s\n", listaTripulacao[i].telefone);
            printf("----------------------------\n");
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
                    printf("\nReserva: %d\n", listaReservas[i].codigo);
                    printf("Voo: %d\n", listaVoos[j].codigo);
                    printf("Data: %s\n", listaVoos[j].data);
                    printf("Hora: %s\n", listaVoos[j].hora);
                    printf("Origem: %s\n", listaVoos[j].origem);
                    printf("Destino: %s\n", listaVoos[j].destino);
                    printf("Assento: %d\n", listaReservas[i].numeroAssento);
                    printf("----------------------------\n");
                    encontrou = 1;
                }
            }
        }
    }
    
    if (!encontrou) {
        printf("Nenhum voo encontrado para este passageiro!\n");
    }
}
