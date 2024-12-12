#include "cadastrarPassageiro.h"

// Definição das variáveis globais que foram declaradas como extern no header
Passageiro listaPassageiros[MAX_PASSAGEIROS];
int qtdPassageiros = 0;

// Função que verifica se uma string contém apenas números
// Retorna 1 se for válido (apenas números) e 0 caso contrário
int validarNumeros(const char *entrada) {
    for (int i = 0; entrada[i] != '\0'; i++) {
        if (!isdigit(entrada[i])) {
            return 0; // Encontrou um caractere que não é número
        }
    }
    return 1; // Todos os caracteres são números
}

// Função que verifica se um endereço é válido
// Um endereço é considerado válido se não estiver vazio
int validarEndereco(const char *endereco) {
    return strlen(endereco) > 0;
}

// Função principal para cadastrar um novo passageiro
// Realiza todas as validações necessárias durante o cadastro
void cadastrarPassageiro() {
    // Verifica se ainda há espaço para novos passageiros
    if (qtdPassageiros >= MAX_PASSAGEIROS) {
        printf("Erro: Limite máximo de passageiros atingido.\n");
        return;
    }

    Passageiro novoPassageiro;

    printf("\n--- Cadastro de Passageiro ---\n");
    printf("Digite o código do passageiro: ");
    scanf("%d", &novoPassageiro.codigo);

    // Verifica se o código já está em uso
    for (int i = 0; i < qtdPassageiros; i++) {
        if (listaPassageiros[i].codigo == novoPassageiro.codigo) {
            printf("Erro: Código já cadastrado!\n");
            return;
        }
    }

    // Captura e armazena o nome do passageiro
    printf("Digite o nome: ");
    scanf(" %[^\n]s", novoPassageiro.nome);

    // Loop para garantir que um endereço válido seja fornecido
    while (1) {
        printf("Digite o endereço: ");
        scanf(" %[^\n]s", novoPassageiro.endereco);
        
        if (validarEndereco(novoPassageiro.endereco)) {
            break; // Endereço válido, sai do loop
        } else {
            printf("Erro: O endereço não pode estar vazio.\n");
        }
    }

    // Loop para garantir que um telefone válido seja fornecido
    while (1) {
        printf("Digite o telefone (somente números, máx. 15 caracteres): ");
        scanf(" %[^\n]s", novoPassageiro.telefone);
        
        if (validarNumeros(novoPassageiro.telefone) && strlen(novoPassageiro.telefone) <= 15) {
            break; // Telefone válido, sai do loop
        } else {
            printf("Erro: Telefone inválido! Insira apenas números (máx. 15 caracteres).\n");
        }
    }

    // Captura a informação sobre participação no programa de fidelidade
    printf("Participa do programa de fidelidade? (1 = Sim, 0 = Não): ");
    scanf("%d", &novoPassageiro.fidelidade);

    // Adiciona o novo passageiro à lista e incrementa o contador
    listaPassageiros[qtdPassageiros++] = novoPassageiro;
    printf("Passageiro cadastrado com sucesso!\n");
}

// Função para exibir todos os passageiros cadastrados
void listarPassageiros() {
    if (qtdPassageiros == 0) {
        printf("Nenhum passageiro cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Passageiros ---\n");
    for (int i = 0; i < qtdPassageiros; i++) {
        Passageiro passageiroAtual = listaPassageiros[i];
        printf("Código: %d, Nome: %s, Endereço: %s, Telefone: %s, Fidelidade: %s\n",
               passageiroAtual.codigo, 
               passageiroAtual.nome, 
               passageiroAtual.endereco,
               passageiroAtual.telefone, 
               passageiroAtual.fidelidade ? "Sim" : "Não");
    }
}