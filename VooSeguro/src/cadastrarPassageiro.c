#include <stdio.h>
#include <string.h>

// Definições e limites
#define MAX_PASSAGEIROS 100

// Estrutura de dados para passageiros
typedef struct
{
    int codigo;         // Código único do passageiro
    char nome[50];      // Nome do passageiro
    char endereco[100]; // Endereço do passageiro
    char telefone[15];  // Telefone do passageiro
    int fidelidade;     // Fidelidade: 0 = Não, 1 = Sim
} Passageiro;

// Variáveis globais para gerenciamento de passageiros
Passageiro listaPassageiros[MAX_PASSAGEIROS]; // Vetor para armazenar passageiros
int qtdPassageiros = 0;                       // Contador de passageiros cadastrados

// Função para cadastrar passageiro
void cadastrarPassageiro()
{
    if (qtdPassageiros >= MAX_PASSAGEIROS)
    {
        printf("Capacidade máxima de passageiros atingida!\n");
        return;
    }

    Passageiro novoPassageiro;

    // Captura dos dados
    printf("\n--- Cadastro de Passageiro ---\n");
    printf("Digite o código do passageiro (número inteiro): ");
    scanf("%d", &novoPassageiro.codigo);

    // Validação do código
    for (int i = 0; i < qtdPassageiros; i++)
    {
        if (listaPassageiros[i].codigo == novoPassageiro.codigo)
        {
            printf("Erro: Código já cadastrado!\n");
            return;
        }
    }

    // Captura de dados restantes
    printf("Digite o nome do passageiro: ");
    scanf(" %[^\n]s", novoPassageiro.nome);

    printf("Digite o endereço do passageiro: ");
    scanf(" %[^\n]s", novoPassageiro.endereco);

    printf("Digite o telefone do passageiro: ");
    scanf(" %[^\n]s", novoPassageiro.telefone);

    printf("O passageiro participa do programa de fidelidade? (1 = Sim, 0 = Não): ");
    scanf("%d", &novoPassageiro.fidelidade);

    // Armazenamento no vetor
    listaPassageiros[qtdPassageiros] = novoPassageiro;
    qtdPassageiros++;

    printf("Passageiro cadastrado com sucesso!\n");
}

// Função para listar passageiros
void listarPassageiros()
{
    if (qtdPassageiros == 0)
    {
        printf("Nenhum passageiro cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Passageiros ---\n");
    for (int i = 0; i < qtdPassageiros; i++)
    {
        Passageiro p = listaPassageiros[i];
        printf("Codigo: %d, Nome: %s, Endereco: %s, Telefone: %s, Fidelidade: %s\n",
               p.codigo, p.nome, p.endereco, p.telefone,
               p.fidelidade ? "Sim" : "Não");
    }
}
