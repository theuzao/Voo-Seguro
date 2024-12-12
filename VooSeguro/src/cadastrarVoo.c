#include "cadastrarVoo.h"
#include <stdlib.h>

Voo listaVoos[MAX_VOOS];
Assento listaAssentos[MAX_VOOS][MAX_ASSENTOS];
int qtdVoos = 0;

int validarData(const char *data) {
    if (strlen(data) != 10) return 0;
    if (data[2] != '/' || data[5] != '/') return 0;

    struct tm tm = {0};
    char dia[3], mes[3], ano[5];
    strncpy(dia, data, 2); dia[2] = '\0';
    strncpy(mes, data + 3, 2); mes[2] = '\0';
    strncpy(ano, data + 6, 4); ano[4] = '\0';

    tm.tm_mday = atoi(dia);
    tm.tm_mon = atoi(mes) - 1;
    tm.tm_year = atoi(ano) - 1900;

    if (tm.tm_mday < 1 || tm.tm_mday > 31) return 0;
    if (tm.tm_mon < 0 || tm.tm_mon > 11) return 0;
    if (tm.tm_year < 124) return 0;  // Não aceita datas anteriores a 2024

    return 1;
}

int validarHora(const char *hora) {
    if (strlen(hora) != 5) return 0;
    if (hora[2] != ':') return 0;

    int h = atoi(hora);
    int m = atoi(hora + 3);

    if (h < 0 || h > 23) return 0;
    if (m < 0 || m > 59) return 0;

    return 1;
}

int validarTripulacaoMinima(int codigoPiloto, int codigoCopiloto) {
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

void configurarAssentos(int codigoVoo) {
    for (int i = 0; i < MAX_ASSENTOS; i++) {
        listaAssentos[codigoVoo][i].numero = i + 1;
        listaAssentos[codigoVoo][i].codigoVoo = codigoVoo;
        listaAssentos[codigoVoo][i].status = 0;  // livre
    }
}

void cadastrarVoo() {
    if (qtdVoos >= MAX_VOOS) {
        printf("Erro: Limite máximo de voos atingido.\n");
        return;
    }

    Voo novoVoo;
    char dataTemp[11], horaTemp[6];

    printf("\n--- Cadastro de Voo ---\n");
    printf("Digite o código do voo: ");
    scanf("%d", &novoVoo.codigo);

    for (int i = 0; i < qtdVoos; i++) {
        if (listaVoos[i].codigo == novoVoo.codigo) {
            printf("Erro: Código de voo já cadastrado!\n");
            return;
        }
    }

    do {
        printf("Digite a data (DD/MM/AAAA): ");
        scanf(" %10s", dataTemp);
        if (!validarData(dataTemp)) {
            printf("Erro: Data inválida!\n");
        }
    } while (!validarData(dataTemp));
    strcpy(novoVoo.data, dataTemp);

    do {
        printf("Digite a hora (HH:MM): ");
        scanf(" %5s", horaTemp);
        if (!validarHora(horaTemp)) {
            printf("Erro: Hora inválida!\n");
        }
    } while (!validarHora(horaTemp));
    strcpy(novoVoo.hora, horaTemp);

    printf("Digite a origem: ");
    scanf(" %[^\n]s", novoVoo.origem);
    
    printf("Digite o destino: ");
    scanf(" %[^\n]s", novoVoo.destino);
    
    printf("Digite o código do avião: ");
    scanf("%d", &novoVoo.codigoAviao);
    
    printf("Digite o código do piloto: ");
    scanf("%d", &novoVoo.codigoPiloto);
    
    printf("Digite o código do copiloto: ");
    scanf("%d", &novoVoo.codigoCopiloto);

    if (!validarTripulacaoMinima(novoVoo.codigoPiloto, novoVoo.codigoCopiloto)) {
        printf("Erro: Tripulação mínima não atendida (piloto e copiloto necessários)!\n");
        return;
    }

    printf("Digite o código do comissário: ");
    scanf("%d", &novoVoo.codigoComissario);
    
    printf("Digite a tarifa: ");
    scanf("%f", &novoVoo.tarifa);

    novoVoo.status = 1;  // Ativo por padrão
    listaVoos[qtdVoos] = novoVoo;
    configurarAssentos(qtdVoos);
    qtdVoos++;

    printf("Voo cadastrado com sucesso!\n");
}

void listarVoos() {
    if (qtdVoos == 0) {
        printf("Nenhum voo cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Voos ---\n");
    for (int i = 0; i < qtdVoos; i++) {
        Voo v = listaVoos[i];
        printf("Código: %d\n", v.codigo);
        printf("Data: %s\n", v.data);
        printf("Hora: %s\n", v.hora);
        printf("Origem: %s\n", v.origem);
        printf("Destino: %s\n", v.destino);
        printf("Status: %s\n", v.status ? "Ativo" : "Inativo");
        printf("Tarifa: R$ %.2f\n", v.tarifa);
        printf("--------------------\n");
    }
}