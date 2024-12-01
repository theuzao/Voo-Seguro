#include <stdio.h>

// Protótipos para funções de passageiros
void cadastrarPassageiro();
void listarPassageiros();

// Protótipos para funções de tripulação
void cadastrarTripulante();
void listarTripulantes();

int main() {
    int opcao;

    while (1) {
        printf("\n--- Sistema de Cadastro ---\n");
        printf("1. Cadastrar Passageiro\n");
        printf("2. Listar Passageiros\n");
        printf("3. Cadastrar Tripulante\n");
        printf("4. Listar Tripulantes\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarPassageiro(); // Chama a função de cadastro de passageiros
                break;
            case 2:
                listarPassageiros(); // Chama a função de listagem de passageiros
                break;
            case 3:
                cadastrarTripulante(); // Chama a função de cadastro de tripulantes
                break;
            case 4:
                listarTripulantes(); // Chama a função de listagem de tripulantes
                break;
            case 5:
                printf("Encerrando o sistema.\n");
                return 0; // Encerra o programa
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }
}
