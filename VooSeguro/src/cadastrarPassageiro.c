#include "cadastrarPassageiro.h"
#include <stdlib.h>

// Definição das variáveis globais
Passageiro listaPassageiros[MAX_PASSAGEIROS];
int qtdPassageiros = 0;

// Funções de validação
int validarNome(const char *nome) {
   if (strlen(nome) < 3 || strlen(nome) > 50) return 0;
   
   for (int i = 0; nome[i]; i++) {
       if (!isalpha(nome[i]) && !isspace(nome[i])) {
           return 0;
       }
   }
   return 1;
}

int validarNumeros(const char *input) {
    if (input == NULL || *input == '\0') {
        return 0; // Retorna falso se a string for nula ou vazia
    }
    for (int i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i])) {
            return 0; // Retorna falso se encontrar um caractere não numérico
        }
    }
    return 1; // Retorna verdadeiro se todos os caracteres forem números
}

int validarEndereco(const char *endereco) {
   if (strlen(endereco) < 5 || strlen(endereco) > 100) return 0;
   
   int temNumero = 0;
   int temLetra = 0;
   
   for (int i = 0; endereco[i]; i++) {
       if (isalpha(endereco[i])) temLetra = 1;
       if (isdigit(endereco[i])) temNumero = 1;
   }
   
   return temNumero && temLetra;
}

int validarTelefone(const char *telefone) {
   if (strlen(telefone) != 11) return 0;
   
   for (int i = 0; telefone[i]; i++) {
       if (!isdigit(telefone[i])) {
           return 0;
       }
   }
   return 1;
}

void limparBuffer() {
   int c;
   while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarPassageiro() {
   if (qtdPassageiros >= MAX_PASSAGEIROS) {
       printf("Erro: Limite máximo de passageiros atingido.\n");
       return;
   }

   Passageiro novoPassageiro;
   novoPassageiro.pontosFidelidade = 0;  // Inicializa pontos

   // Validação do código
   printf("\n--- Cadastro de Passageiro ---\n");
   while (1) {
       printf("Digite o código (somente números maiores que 0): ");
       if (scanf("%d", &novoPassageiro.codigo) != 1 || novoPassageiro.codigo <= 0) {
           printf("Erro: Código inválido!\n");
           limparBuffer();
           continue;
       }
       
       int codigoExiste = 0;
       for (int i = 0; i < qtdPassageiros; i++) {
           if (listaPassageiros[i].codigo == novoPassageiro.codigo) {
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
   limparBuffer();

   // Validação do nome
   while (1) {
       printf("Digite o nome: ");
       if (fgets(novoPassageiro.nome, sizeof(novoPassageiro.nome), stdin)) {
           novoPassageiro.nome[strcspn(novoPassageiro.nome, "\n")] = 0;
           if (validarNome(novoPassageiro.nome)) break;
       }
       printf("Erro: Nome inválido! Use apenas letras e espaços (3-50 caracteres).\n");
   }

   // Validação do endereço
   while (1) {
       printf("Digite o endereço: ");
       if (fgets(novoPassageiro.endereco, sizeof(novoPassageiro.endereco), stdin)) {
           novoPassageiro.endereco[strcspn(novoPassageiro.endereco, "\n")] = 0;
           if (validarEndereco(novoPassageiro.endereco)) break;
       }
       printf("Erro: Endereço inválido! Inclua número e nome da rua (5-100 caracteres).\n");
   }

   // Validação do telefone
   while (1) {
       printf("Digite o telefone (11 dígitos, apenas números): ");
       if (fgets(novoPassageiro.telefone, sizeof(novoPassageiro.telefone), stdin)) {
           novoPassageiro.telefone[strcspn(novoPassageiro.telefone, "\n")] = 0;
           if (validarTelefone(novoPassageiro.telefone)) break;
       }
       printf("Erro: Telefone inválido! Use exatamente 11 números.\n");
   }

   // Validação da fidelidade
   while (1) {
       printf("Participa do programa de fidelidade? (1 = Sim, 0 = Não): ");
       char input[10];
       if (fgets(input, sizeof(input), stdin)) {
           input[strcspn(input, "\n")] = 0;
           if (strlen(input) == 1 && (input[0] == '0' || input[0] == '1')) {
               novoPassageiro.fidelidade = input[0] - '0';
               break;
           }
       }
       printf("Erro: Digite apenas 0 ou 1!\n");
   }

   listaPassageiros[qtdPassageiros++] = novoPassageiro;
   printf("\nPassageiro cadastrado com sucesso!\n");
   printf("============================\n");
}

void listarPassageiros() {
   if (qtdPassageiros == 0) {
       printf("\nNenhum passageiro cadastrado.\n");
       return;
   }

   printf("\n=== Lista de Passageiros ===\n");
   for (int i = 0; i < qtdPassageiros; i++) {
       printf("\nPassageiro %d:\n", i+1);
       printf("Código: %d\n", listaPassageiros[i].codigo);
       printf("Nome: %s\n", listaPassageiros[i].nome);
       printf("Endereço: %s\n", listaPassageiros[i].endereco);
       printf("Telefone: %s\n", listaPassageiros[i].telefone);
       printf("Fidelidade: %s\n", listaPassageiros[i].fidelidade ? "Sim" : "Não");
       if (listaPassageiros[i].fidelidade) {
           printf("Pontos: %d\n", listaPassageiros[i].pontosFidelidade);
       }
       printf("----------------------------\n");
   }
}