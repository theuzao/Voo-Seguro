#include "cadastrarVoo.h"
#include <stdlib.h>
#include <ctype.h>

Voo listaVoos[MAX_VOOS];
Assento listaAssentos[MAX_VOOS][MAX_ASSENTOS];
int qtdVoos = 0;

void limparBufferVoo() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validarData(const char *data) {
    if (strlen(data) != 10) return 0;
    if (data[2] != '/' || data[5] != '/') return 0;

    int dia, mes, ano;
    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);

    if (ano < 2024) return 0;  // Não aceita datas passadas
    if (mes < 1 || mes > 12) return 0;
    
    int diasPorMes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (ano % 4 == 0) diasPorMes[2] = 29;  // Ano bissexto
    
    if (dia < 1 || dia > diasPorMes[mes]) return 0;

    return 1;
}

int validarHora(const char *hora) {
    if (strlen(hora) != 5) return 0;
    if (hora[2] != ':') return 0;

    int h, m;
    sscanf(hora, "%d:%d", &h, &m);

    if (h < 0 || h > 23) return 0;
    if (m < 0 || m > 59) return 0;

    return 1;
}

int validarTarifa(float tarifa) {
    return tarifa > 0.0;
}

void cadastrarVoo() {
    if (qtdVoos >= MAX_VOOS) {
        printf("Erro: Limite máximo de voos atingido.\n");
        return;
    }

    Voo novoVoo;

    printf("\n--- Cadastro de Voo ---\n");
    
    // Validação do código do voo
    while (1) {
        printf("Digite o código do voo: ");
        if (scanf("%d", &novoVoo.codigo) != 1 || novoVoo.codigo <= 0) {
            printf("Erro: Código inválido!\n");
            limparBufferVoo();
            continue;
        }
        
        int codigoExiste = 0;
        for (int i = 0; i < qtdVoos; i++) {
            if (listaVoos[i].codigo == novoVoo.codigo) {
                codigoExiste = 1;
                break;
            }
        }
        
        if (codigoExiste) {
            printf("Erro: Código de voo já existe!\n");
            continue;
        }
        break;
    }
    limparBufferVoo();

    // Validação da data
    while (1) {
        printf("Digite a data (DD/MM/AAAA): ");
        if (fgets(novoVoo.data, sizeof(novoVoo.data), stdin)) {
            novoVoo.data[strcspn(novoVoo.data, "\n")] = 0;
            if (validarData(novoVoo.data)) break;
        }
        printf("Erro: Data inválida! Use o formato DD/MM/AAAA e data futura.\n");
    }

    // Validação da hora
    while (1) {
        printf("Digite a hora (HH:MM): ");
        if (fgets(novoVoo.hora, sizeof(novoVoo.hora), stdin)) {
            novoVoo.hora[strcspn(novoVoo.hora, "\n")] = 0;
            if (validarHora(novoVoo.hora)) break;
        }
        printf("Erro: Hora inválida! Use o formato HH:MM (24h).\n");
    }

    printf("Digite a origem: ");
    fgets(novoVoo.origem, sizeof(novoVoo.origem), stdin);
    novoVoo.origem[strcspn(novoVoo.origem, "\n")] = 0;

    printf("Digite o destino: ");
    fgets(novoVoo.destino, sizeof(novoVoo.destino), stdin);
    novoVoo.destino[strcspn(novoVoo.destino, "\n")] = 0;

    // Validação da tarifa
    while (1) {
        printf("Digite a tarifa: R$ ");
        if (scanf("%f", &novoVoo.tarifa) == 1 && validarTarifa(novoVoo.tarifa)) {
            break;
        }
        printf("Erro: Tarifa inválida! Digite um valor maior que zero.\n");
        limparBufferVoo();
    }
    limparBufferVoo();

    // Validação da tripulação
    printf("\nCadastro da Tripulação do Voo\n");
    while (1) {
        printf("Digite o código do piloto: ");
        scanf("%d", &novoVoo.codigoPiloto);
        printf("Digite o código do copiloto: ");
        scanf("%d", &novoVoo.codigoCopiloto);
        
        if (verificarTripulacaoMinima(novoVoo.codigoPiloto, novoVoo.codigoCopiloto)) {
            break;
        }
        printf("Erro: Tripulação inválida! Verifique os códigos do piloto e copiloto.\n");
    }

    printf("Digite o código do comissário: ");
    scanf("%d", &novoVoo.codigoComissario);
    limparBufferVoo();

    // Configura o status inicial como ativo
    novoVoo.status = 1;

    // Salva o voo e configura os assentos
    listaVoos[qtdVoos] = novoVoo;
    configurarAssentos(qtdVoos);
    qtdVoos++;

    printf("\nVoo cadastrado com sucesso!\n");
    printf("============================\n");
}

void configurarAssentos(int indiceVoo) {
    for (int i = 0; i < MAX_ASSENTOS; i++) {
        listaAssentos[indiceVoo][i].numero = i + 1;
        listaAssentos[indiceVoo][i].codigoVoo = listaVoos[indiceVoo].codigo;
        listaAssentos[indiceVoo][i].status = 0;  // Livre
    }
}

void listarVoos() {
    if (qtdVoos == 0) {
        printf("\nNenhum voo cadastrado.\n");
        return;
    }

    printf("\n=== Lista de Voos ===\n");
    for (int i = 0; i < qtdVoos; i++) {
        printf("\nVoo %d:\n", i+1);
        printf("Código: %d\n", listaVoos[i].codigo);
        printf("Data: %s\n", listaVoos[i].data);
        printf("Hora: %s\n", listaVoos[i].hora);
        printf("Origem: %s\n", listaVoos[i].origem);
        printf("Destino: %s\n", listaVoos[i].destino);
        printf("Tarifa: R$ %.2f\n", listaVoos[i].tarifa);
        printf("Status: %s\n", listaVoos[i].status ? "Ativo" : "Inativo");
        printf("----------------------------\n");
    }
}

int verificarStatusVoo(int codigoVoo) {
    for (int i = 0; i < qtdVoos; i++) {
        if (listaVoos[i].codigo == codigoVoo) {
            return listaVoos[i].status;
        }
    }
    return 0;  // Voo não encontrado
}