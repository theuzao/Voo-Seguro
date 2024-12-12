#include "cadastrarReserva.h"
#include <stdlib.h>

// Definição das variáveis globais
Reserva listaReservas[MAX_RESERVAS];
int qtdReservas = 0;

// Funções de validação
int verificarDisponibilidadeAssento(int codigoVoo, int numeroAssento) {
    if (numeroAssento <= 0 || numeroAssento > MAX_ASSENTOS) {
        return 0;  // Assento inválido
    }
    
    for (int i = 0; i < qtdVoos; i++) {
        if (listaVoos[i].codigo == codigoVoo) {
            return !listaAssentos[i][numeroAssento-1].status;  // Retorna 1 se livre, 0 se ocupado
        }
    }
    return 0;  // Voo não encontrado
}

int validarPassageiroExiste(int codigoPassageiro) {
    for (int i = 0; i < qtdPassageiros; i++) {
        if (listaPassageiros[i].codigo == codigoPassageiro) {
            return 1;
        }
    }
    return 0;
}

int validarVooAtivo(int codigoVoo) {
    for (int i = 0; i < qtdVoos; i++) {
        if (listaVoos[i].codigo == codigoVoo) {
            return listaVoos[i].status;
        }
    }
    return 0;
}

// Função principal de cadastro
void cadastrarReserva() {
    if (qtdReservas >= MAX_RESERVAS) {
        printf("Erro: Limite máximo de reservas atingido.\n");
        return;
    }

    Reserva novaReserva;
    
    printf("\n--- Cadastro de Reserva ---\n");
    printf("Digite o código da reserva: ");
    scanf("%d", &novaReserva.codigo);

    // Validação de código duplicado
    for (int i = 0; i < qtdReservas; i++) {
        if (listaReservas[i].codigo == novaReserva.codigo) {
            printf("Erro: Código de reserva já existe!\n");
            return;
        }
    }

    printf("Digite o código do passageiro: ");
    scanf("%d", &novaReserva.codigoPassageiro);
    if (!validarPassageiroExiste(novaReserva.codigoPassageiro)) {
        printf("Erro: Passageiro não encontrado!\n");
        return;
    }

    printf("Digite o código do voo: ");
    scanf("%d", &novaReserva.codigoVoo);
    if (!validarVooAtivo(novaReserva.codigoVoo)) {
        printf("Erro: Voo não encontrado ou inativo!\n");
        return;
    }

    printf("Digite o número do assento (1-%d): ", MAX_ASSENTOS);
    scanf("%d", &novaReserva.numeroAssento);
    if (!verificarDisponibilidadeAssento(novaReserva.codigoVoo, novaReserva.numeroAssento)) {
        printf("Erro: Assento não disponível ou inválido!\n");
        return;
    }

    // Calcula valor total e marca assento como ocupado
    for (int i = 0; i < qtdVoos; i++) {
        if (listaVoos[i].codigo == novaReserva.codigoVoo) {
            novaReserva.valorTotal = listaVoos[i].tarifa;
            listaAssentos[i][novaReserva.numeroAssento-1].status = 1;
            break;
        }
    }

    listaReservas[qtdReservas++] = novaReserva;
    atualizarPontosFidelidade(novaReserva.codigoPassageiro);
    
    printf("Reserva cadastrada com sucesso!\n");
    printf("Valor total: R$ %.2f\n", novaReserva.valorTotal);
}

void baixarReserva() {
    int codigoReserva;
    printf("\nDigite o código da reserva para baixa: ");
    scanf("%d", &codigoReserva);

    for (int i = 0; i < qtdReservas; i++) {
        if (listaReservas[i].codigo == codigoReserva) {
            // Libera o assento
            for (int j = 0; j < qtdVoos; j++) {
                if (listaVoos[j].codigo == listaReservas[i].codigoVoo) {
                    listaAssentos[j][listaReservas[i].numeroAssento-1].status = 0;
                    break;
                }
            }
            
            printf("Reserva baixada com sucesso!\n");
            printf("Valor da reserva: R$ %.2f\n", listaReservas[i].valorTotal);
            
            // Remove a reserva (move a última para esta posição)
            listaReservas[i] = listaReservas[--qtdReservas];
            return;
        }
    }
    printf("Erro: Reserva não encontrada!\n");
}

void listarReservasPassageiro(int codigoPassageiro) {
    int encontrou = 0;
    printf("\n--- Reservas do Passageiro ---\n");
    
    for (int i = 0; i < qtdReservas; i++) {
        if (listaReservas[i].codigoPassageiro == codigoPassageiro) {
            printf("Código da Reserva: %d\n", listaReservas[i].codigo);
            printf("Código do Voo: %d\n", listaReservas[i].codigoVoo);
            printf("Assento: %d\n", listaReservas[i].numeroAssento);
            printf("Valor: R$ %.2f\n", listaReservas[i].valorTotal);
            printf("--------------------\n");
            encontrou = 1;
        }
    }
    
    if (!encontrou) {
        printf("Nenhuma reserva encontrada para este passageiro.\n");
    }
}

void atualizarPontosFidelidade(int codigoPassageiro) {
    for (int i = 0; i < qtdPassageiros; i++) {
        if (listaPassageiros[i].codigo == codigoPassageiro && 
            listaPassageiros[i].fidelidade) {
            printf("Pontos de fidelidade adicionados: %d\n", PONTOS_POR_VOO);
            return;
        }
    }
}

void consultarPontosFidelidade(int codigoPassageiro) {
    for (int i = 0; i < qtdPassageiros; i++) {
        if (listaPassageiros[i].codigo == codigoPassageiro) {
            if (listaPassageiros[i].fidelidade) {
                int totalPontos = 0;
                // Conta número de voos do passageiro
                for (int j = 0; j < qtdReservas; j++) {
                    if (listaReservas[j].codigoPassageiro == codigoPassageiro) {
                        totalPontos += PONTOS_POR_VOO;
                    }
                }
                printf("Total de pontos: %d\n", totalPontos);
            } else {
                printf("Passageiro não participa do programa de fidelidade.\n");
            }
            return;
        }
    }
    printf("Passageiro não encontrado.\n");
}