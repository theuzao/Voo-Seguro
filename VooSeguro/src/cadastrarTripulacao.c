#include "cadastrarTripulacao.h"

// Definição das variáveis globais
Tripulacao listaTripulacao[MAX_TRIPULACAO];
int qtdTripulacao = 0;

// Função para validar o telefone (apenas números e tamanho correto)
int validarTelefone(const char *telefone) {
    int len = strlen(telefone);
    if (len == 0 || len > 15) return 0;
    
    for (int i = 0; i < len; i++) {
        if (!isdigit(telefone[i])) return 0;
    }
    return 1;
}

// Função para validar o cargo
int validarCargo(const char *cargo) {
    char cargoMin[20];
    strcpy(cargoMin, cargo);
    for (int i = 0; cargoMin[i]; i++) {
        cargoMin[i] = tolower(cargoMin[i]);
    }
    
    return (strcmp(cargoMin, "piloto") == 0 ||
            strcmp(cargoMin, "copiloto") == 0 ||
            strcmp(cargoMin, "comissario") == 0);
}

void cadastrarTripulacao() {
    if (qtdTripulacao >= MAX_TRIPULACAO) {
        printf("Erro: Limite máximo da tripulação atingido.\n");
        return;
    }

    Tripulacao novoTripulante;

    printf("\n--- Cadastro de Tripulação ---\n");
    printf("Digite o código do tripulante: ");
    scanf("%d", &novoTripulante.codigo);

    // Validação de código duplicado
    for (int i = 0; i < qtdTripulacao; i++) {
        if (listaTripulacao[i].codigo == novoTripulante.codigo) {
            printf("Erro: Código já cadastrado!\n");
            return;
        }
    }

    printf("Digite o nome: ");
    scanf(" %[^\n]s", novoTripulante.nome);

    // Loop para validação do telefone
    do {
        printf("Digite o telefone (apenas números, máximo 15 dígitos): ");
        scanf(" %[^\n]s", novoTripulante.telefone);
        if (!validarTelefone(novoTripulante.telefone)) {
            printf("Erro: Telefone inválido!\n");
        }
    } while (!validarTelefone(novoTripulante.telefone));

    // Loop para validação do cargo
    do {
        printf("Digite o cargo (piloto, copiloto, comissario): ");
        scanf(" %[^\n]s", novoTripulante.cargo);
        if (!validarCargo(novoTripulante.cargo)) {
            printf("Erro: Cargo inválido! Use piloto, copiloto ou comissario.\n");
        }
    } while (!validarCargo(novoTripulante.cargo));

    listaTripulacao[qtdTripulacao++] = novoTripulante;
    printf("Tripulante cadastrado com sucesso!\n");
}

void listarTripulacao() {
    if (qtdTripulacao == 0) {
        printf("Nenhum tripulante cadastrado.\n");
        return;
    }

    printf("\n--- Lista da Tripulação ---\n");
    for (int i = 0; i < qtdTripulacao; i++) {
        Tripulacao t = listaTripulacao[i];
        printf("Código: %d, Nome: %s, Telefone: %s, Cargo: %s\n",
               t.codigo, t.nome, t.telefone, t.cargo);
    }
}
