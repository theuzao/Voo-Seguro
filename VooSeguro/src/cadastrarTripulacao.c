#include "cadastrarTripulacao.h"
#include <stdlib.h>

Tripulacao listaTripulacao[MAX_TRIPULACAO];
int qtdTripulacao = 0;

void limparBufferTripulacao() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validarCargoTripulacao(const char *cargo) {
    char cargoMin[20];
    strncpy(cargoMin, cargo, sizeof(cargoMin) - 1);
    cargoMin[sizeof(cargoMin) - 1] = '\0';

    // Converte para minúsculas
    for (int i = 0; cargoMin[i]; i++) {
        cargoMin[i] = tolower(cargoMin[i]);
    }

    return (strcmp(cargoMin, "piloto") == 0 ||
            strcmp(cargoMin, "copiloto") == 0 ||
            strcmp(cargoMin, "comissario") == 0);
}

int validarNomeTripulacao(const char *nome) {
    if (strlen(nome) < 3 || strlen(nome) > 50) return 0;
    
    for (int i = 0; nome[i]; i++) {
        if (!isalpha(nome[i]) && !isspace(nome[i])) {
            return 0;
        }
    }
    return 1;
}

int validarTelefoneTripulacao(const char *telefone) {
    if (strlen(telefone) != 11) return 0;
    
    for (int i = 0; telefone[i]; i++) {
        if (!isdigit(telefone[i])) {
            return 0;
        }
    }
    return 1;
}

void cadastrarTripulacao() {
    if (qtdTripulacao >= MAX_TRIPULACAO) {
        printf("Erro: Limite máximo de tripulantes atingido.\n");
        return;
    }

    Tripulacao novoTripulante;

    printf("\n--- Cadastro de Tripulação ---\n");
    
    // Validação do código
    while (1) {
        printf("Digite o código (somente números maiores que 0): ");
        if (scanf("%d", &novoTripulante.codigo) != 1 || novoTripulante.codigo <= 0) {
            printf("Erro: Código inválido!\n");
            limparBufferTripulacao();
            continue;
        }
        
        int codigoExiste = 0;
        for (int i = 0; i < qtdTripulacao; i++) {
            if (listaTripulacao[i].codigo == novoTripulante.codigo) {
                codigoExiste = 1;
                break;
            }
        }
        
        if (codigoExiste) {
            printf("Erro: Código já cadastrado!\n");
            continue;
        }
        break;
    }
    limparBufferTripulacao();

    // Validação do nome
    while (1) {
        printf("Digite o nome: ");
        if (fgets(novoTripulante.nome, sizeof(novoTripulante.nome), stdin)) {
            novoTripulante.nome[strcspn(novoTripulante.nome, "\n")] = 0;
            if (validarNomeTripulacao(novoTripulante.nome)) break;
        }
        printf("Erro: Nome inválido! Use apenas letras e espaços (3-50 caracteres).\n");
    }

    // Validação do telefone
    while (1) {
        printf("Digite o telefone (11 dígitos, apenas números): ");
        if (fgets(novoTripulante.telefone, sizeof(novoTripulante.telefone), stdin)) {
            novoTripulante.telefone[strcspn(novoTripulante.telefone, "\n")] = 0;
            if (validarTelefoneTripulacao(novoTripulante.telefone)) break;
        }
        printf("Erro: Telefone inválido! Use exatamente 11 números.\n");
    }

    // Validação do cargo
    while (1) {
        printf("Digite o cargo (piloto, copiloto ou comissario): ");
        if (fgets(novoTripulante.cargo, sizeof(novoTripulante.cargo), stdin)) {
            novoTripulante.cargo[strcspn(novoTripulante.cargo, "\n")] = 0;
            if (validarCargoTripulacao(novoTripulante.cargo)) break;
        }
        printf("Erro: Cargo inválido! Use apenas: piloto, copiloto ou comissario.\n");
    }

    listaTripulacao[qtdTripulacao++] = novoTripulante;
    printf("\nTripulante cadastrado com sucesso!\n");
    printf("============================\n");
}

void listarTripulacao() {
    if (qtdTripulacao == 0) {
        printf("\nNenhum tripulante cadastrado.\n");
        return;
    }

    printf("\n=== Lista de Tripulantes ===\n");
    for (int i = 0; i < qtdTripulacao; i++) {
        printf("\nTripulante %d:\n", i+1);
        printf("Código: %d\n", listaTripulacao[i].codigo);
        printf("Nome: %s\n", listaTripulacao[i].nome);
        printf("Cargo: %s\n", listaTripulacao[i].cargo);
        printf("Telefone: %s\n", listaTripulacao[i].telefone);
        printf("----------------------------\n");
    }
}

int verificarTripulacaoMinima(int codigoPiloto, int codigoCopiloto) {
    int pilotoEncontrado = 0, copilotoEncontrado = 0;

    for (int i = 0; i < qtdTripulacao; i++) {
        if (listaTripulacao[i].codigo == codigoPiloto && 
            strcmp(listaTripulacao[i].cargo, "piloto") == 0) {
            pilotoEncontrado = 1;
        }
        if (listaTripulacao[i].codigo == codigoCopiloto && 
            strcmp(listaTripulacao[i].cargo, "copiloto") == 0) {
            copilotoEncontrado = 1;
        }
    }

    return pilotoEncontrado && copilotoEncontrado;
}