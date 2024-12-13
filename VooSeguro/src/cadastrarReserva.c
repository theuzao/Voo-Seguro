#include "cadastrarReserva.h"
#include <stdlib.h>

Reserva listaReservas[MAX_RESERVAS];
int qtdReservas = 0;

void limparBufferReserva() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int verificarDisponibilidadeAssento(int codigoVoo, int numeroAssento) {
    if (numeroAssento <= 0 || numeroAssento > MAX_ASSENTOS) return 0;
    
    for (int i = 0; i < qtdVoos; i++) {
        if (listaVoos[i].codigo == codigoVoo) {
            return !listaAssentos[i][numeroAssento-1].status;
        }
    }
    return 0;
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

void cadastrarReserva() {
    if (qtdReservas >= MAX_RESERVAS) {
        printf("Erro: Limite máximo de reservas atingido.\n");
        return;
    }

    Reserva novaReserva;

    printf("\n--- Cadastro de Reserva ---\n");
    
    // Validação do código da reserva
    while (1) {
        printf("Digite o código da reserva: ");
        if (scanf("%d", &novaReserva.codigo) != 1 || novaReserva.codigo <= 0) {
            printf("Erro: Código inválido!\n");
            limparBufferReserva();
            continue;
        }
        
        int codigoExiste = 0;
        for (int i = 0; i < qtdReservas; i++) {
            if (listaReservas[i].codigo == novaReserva.codigo) {
                codigoExiste = 1;
                break;
            }
        }
        
        if (codigoExiste) {
            printf("Erro: Código de reserva já existe!\n");
            continue;
        }
        break;
    }
    limparBufferReserva();

    // Validação do passageiro
    while (1) {
        printf("Digite o código do passageiro: ");
        scanf("%d", &novaReserva.codigoPassageiro);
        if (validarPassageiroExiste(novaReserva.codigoPassageiro)) break;
        printf("Erro: Passageiro não encontrado!\n");
    }

    // Validação do voo
    while (1) {
        printf("Digite o código do voo: ");
        scanf("%d", &novaReserva.codigoVoo);
        if (validarVooAtivo(novaReserva.codigoVoo)) break;
        printf("Erro: Voo não encontrado ou inativo!\n");
    }

    // Validação do assento
    while (1) {
        printf("Digite o número do assento (1-%d): ", MAX_ASSENTOS);
        scanf("%d", &novaReserva.numeroAssento);
        if (verificarDisponibilidadeAssento(novaReserva.codigoVoo, novaReserva.numeroAssento)) break;
        printf("Erro: Assento indisponível ou inválido!\n");
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
    
    printf("\nReserva cadastrada com sucesso!\n");
    printf("Valor total: R$ %.2f\n", novaReserva.valorTotal);
    printf("============================\n");
}

void baixarReserva() {
    int codigoReserva;
    printf("\n--- Baixa de Reserva ---\n");
    printf("Digite o código da reserva: ");
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
            
            printf("\nReserva cancelada com sucesso!\n");
            printf("Valor a ser reembolsado: R$ %.2f\n", listaReservas[i].valorTotal);
            
            // Remove a reserva (move a última para esta posição)
            listaReservas[i] = listaReservas[--qtdReservas];
            return;
        }
    }
    printf("Reserva não encontrada!\n");
}

void listarReservasPassageiro(int codigoPassageiro) {
    int encontrou = 0;
    printf("\n=== Reservas do Passageiro ===\n");
    
    for (int i = 0; i < qtdReservas; i++) {
        if (listaReservas[i].codigoPassageiro == codigoPassageiro) {
            printf("\nReserva %d:\n", i+1);
            printf("Código: %d\n", listaReservas[i].codigo);
            printf("Voo: %d\n", listaReservas[i].codigoVoo);
            printf("Assento: %d\n", listaReservas[i].numeroAssento);
            printf("Valor: R$ %.2f\n", listaReservas[i].valorTotal);
            printf("----------------------------\n");
            encontrou = 1;
        }
    }
    
    if (!encontrou) {
        printf("Nenhuma reserva encontrada para este passageiro.\n");
    }
}