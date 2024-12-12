#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Incluindo os headers necessários
#include "cadastrarPassageiro.h"
#include "cadastrarTripulacao.h"

/**
 * Função que valida se uma string contém apenas números
 * @param entrada: string a ser validada
 * @return: 1 se contém apenas números, 0 caso contrário
 */
int validarEntradaNumerica(char *entrada) {
    for (int i = 0; entrada[i] != '\0'; i++) {
        if (!isdigit(entrada[i])) {
            return 0;  // Retorna falso se encontrar um caractere não numérico
        }
    }
    return 1;  // Retorna verdadeiro se todos os caracteres forem números
}

int main() {
    char entrada[10];  // Buffer para capturar a entrada do usuário
    int opcao;         // Variável para armazenar a escolha convertida

    // Loop principal do programa
    while (1) {
        // Exibe o menu principal
        printf("\n--- Sistema de Cadastro ---\n");
        printf("1. Cadastrar Passageiro\n");
        printf("2. Listar Passageiros\n");
        printf("3. Cadastrar Tripulação\n");       
        printf("4. Listar Tripulação\n");          
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        
        // Captura a entrada como string para validação segura
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';  // Remove o caractere de nova linha

        // Valida se a entrada contém apenas números
        if (!validarEntradaNumerica(entrada)) {
            printf("Erro: Entrada inválida! Por favor, insira um número de 1 a 5.\n");
            continue;  // Volta ao início do loop
        }

        // Converte a entrada validada para número
        opcao = atoi(entrada);

        // Processa a opção escolhida
        switch (opcao) {
            case 1:
                cadastrarPassageiro();
                break;
            case 2:
                listarPassageiros();
                break;
            case 3:
                cadastrarTripulacao();  
                break;
            case 4:
                listarTripulacao();    
                break;
            case 5:
                printf("Encerrando o sistema...\n");
                return 0;
            default:
                printf("Opcao invalida! Por favor, insira um número entre 1 e 5.\n");
        }
    }
}
