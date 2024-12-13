#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cadastrarPassageiro.h"
#include "cadastrarTripulacao.h"
#include "cadastrarVoo.h"
#include "cadastrarReserva.h"
#include "pesquisa.h"

void limparBufferMain() {
   int c;
   while ((c = getchar()) != '\n' && c != EOF);
}

void menuPesquisa() {
   int opcao;
   printf("\n--- Menu de Pesquisa ---\n");
   printf("1. Pesquisar Passageiro por Código\n");
   printf("2. Pesquisar Passageiro por Nome\n");
   printf("3. Pesquisar Tripulação por Código\n");
   printf("4. Pesquisar Tripulação por Nome\n");
   printf("5. Listar Voos de um Passageiro\n");
   printf("6. Voltar\n");
   printf("Escolha uma opção: ");

   if (scanf("%d", &opcao) != 1) {
       printf("Opção inválida!\n");
       limparBufferMain();
       return;
   }
   limparBufferMain();

   int codigo;
   char nome[50];

   switch(opcao) {
       case 1:
           printf("Digite o código do passageiro: ");
           scanf("%d", &codigo);
           pesquisarPassageiroPorCodigo(codigo);
           break;
           
       case 2:
           printf("Digite o nome do passageiro: ");
           fgets(nome, sizeof(nome), stdin);
           nome[strcspn(nome, "\n")] = 0;
           pesquisarPassageiroPorNome(nome);
           break;
           
       case 3:
           printf("Digite o código do tripulante: ");
           scanf("%d", &codigo);
           pesquisarTripulacaoPorCodigo(codigo);
           break;
           
       case 4:
           printf("Digite o nome do tripulante: ");
           fgets(nome, sizeof(nome), stdin);
           nome[strcspn(nome, "\n")] = 0;
           pesquisarTripulacaoPorNome(nome);
           break;
           
       case 5:
           printf("Digite o código do passageiro: ");
           scanf("%d", &codigo);
           listarVoosPassageiro(codigo);
           break;
           
       case 6:
           return;
           
       default:
           printf("Opção inválida!\n");
   }
}

int main() {
   int opcao;
   char entrada[10];

   while (1) {
       printf("\n=== Sistema de Gerenciamento de Voos ===\n");
       printf("1. Cadastrar Passageiro\n");
       printf("2. Listar Passageiros\n");
       printf("3. Cadastrar Tripulação\n");
       printf("4. Listar Tripulação\n");
       printf("5. Cadastrar Voo\n");
       printf("6. Listar Voos\n");
       printf("7. Fazer Reserva\n");
       printf("8. Cancelar Reserva\n");
       printf("9. Menu de Pesquisa\n");
       printf("10. Consultar Fidelidade\n");
       printf("11. Sair\n");
       printf("Escolha uma opção: ");

       if (fgets(entrada, sizeof(entrada), stdin)) {
           entrada[strcspn(entrada, "\n")] = 0;
           
           if (sscanf(entrada, "%d", &opcao) != 1) {
               printf("Erro: Digite apenas números!\n");
               continue;
           }

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
                   cadastrarVoo();
                   break;
                   
               case 6:
                   listarVoos();
                   break;
                   
               case 7:
                   cadastrarReserva();
                   break;
                   
               case 8:
                   baixarReserva();
                   break;
                   
               case 9:
                   menuPesquisa();
                   break;
                   
               case 10: {
                   int codigo;
                   printf("Digite o código do passageiro: ");
                   scanf("%d", &codigo);
                   limparBufferMain();
                   consultarPontosFidelidade(codigo);
                   break;
               }
               
               case 11:
                   printf("\nEncerrando o sistema...\n");
                   return 0;
                   
               default:
                   printf("Opção inválida! Escolha um número entre 1 e 11.\n");
           }
       }
   }

   return 0;
}