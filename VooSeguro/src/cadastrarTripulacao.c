#include <stdio.h>
#include <string.h>

#define MAX_TRIPULANTES 50

// Armazenar os dados da tripulação
typedef struct
{
    int codigo;        // Código único do tripulante
    char nome[50];     // Nome do tripulante
    char telefone[15]; // Telefone do tripulante
    char cargo[20];    // Cargo: piloto, copiloto ou comissário
} Tripulante;

Tripulante listaTripulantes[MAX_TRIPULANTES];
int qtdTripulantes = 0;

// Função para cadastrar um tripulante
void cadastrarTripulante()
{
    if (qtdTripulantes >= MAX_TRIPULANTES)
    {
        printf("Capacidade máxima de tripulantes atingida!\n");
        return;
    }

    Tripulante novoTripulante;

    printf("\n--- Cadastro de Tripulante ---\n");
    printf("Digite o código do tripulante (número inteiro): ");
    scanf("%d", &novoTripulante.codigo);

    // Validação de código único
    for (int i = 0; i < qtdTripulantes; i++)
    {
        if (listaTripulantes[i].codigo == novoTripulante.codigo)
        {
            printf("Erro: Código já cadastrado!\n");
            return;
        }
    }

    printf("Digite o nome do tripulante: ");
    scanf(" %[^\n]s", novoTripulante.nome);

    printf("Digite o telefone do tripulante: ");
    scanf(" %[^\n]s", novoTripulante.telefone);

    printf("Digite o cargo do tripulante (piloto, copiloto ou comissário): ");
    scanf(" %[^\n]s", novoTripulante.cargo);

    // Armazenar o tripulante na lista
    listaTripulantes[qtdTripulantes] = novoTripulante;
    qtdTripulantes++;

    printf("Tripulante cadastrado com sucesso!\n");
}

// Função para listar tripulantes
void listarTripulantes()
{
    if (qtdTripulantes == 0)
    {
        printf("Nenhum tripulante cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Tripulantes ---\n");
    for (int i = 0; i < qtdTripulantes; i++)
    {
        Tripulante t = listaTripulantes[i];
        printf("Codigo: %d, Nome: %s, Telefone: %s, Cargo: %s\n",
               t.codigo, t.nome, t.telefone, t.cargo);
    }
}
