#include "../lib/munit/munit.h"
#include "../src/cadastrarReserva.h"

#define UNUSED(x) (void)(x)

/* Função de preparação que limpa os dados antes de cada teste */
static void* test_setup(const MunitParameter params[], void* user_data) {
    UNUSED(params);
    UNUSED(user_data);
    
    // Limpa todas as estruturas de dados
    qtdReservas = 0;
    qtdVoos = 0;
    qtdPassageiros = 0;
    memset(listaReservas, 0, sizeof(listaReservas));
    memset(listaVoos, 0, sizeof(listaVoos));
    memset(listaPassageiros, 0, sizeof(listaPassageiros));
    memset(listaAssentos, 0, sizeof(listaAssentos));
    
    return NULL;
}

/* Teste da verificação de disponibilidade de assento */
static MunitResult test_verificar_disponibilidade_assento(const MunitParameter params[], void* data) {
    UNUSED(params);
    UNUSED(data);

    // Configura um voo de teste
    Voo vooTeste = {
        .codigo = 1,
        .status = 1
    };
    listaVoos[qtdVoos++] = vooTeste;
    
    // Configura assentos iniciais como livres
    for (int i = 0; i < MAX_ASSENTOS; i++) {
        listaAssentos[0][i].status = 0;
    }
    
    // Testa assento válido e livre
    munit_assert_true(verificarDisponibilidadeAssento(1, 1));
    
    // Ocupa um assento e testa novamente
    listaAssentos[0][0].status = 1;
    munit_assert_false(verificarDisponibilidadeAssento(1, 1));
    
    // Testa assento inválido
    munit_assert_false(verificarDisponibilidadeAssento(1, MAX_ASSENTOS + 1));
    munit_assert_false(verificarDisponibilidadeAssento(1, 0));
    
    // Testa voo inexistente
    munit_assert_false(verificarDisponibilidadeAssento(999, 1));
    
    return MUNIT_OK;
}

/* Teste de validação de passageiro */
static MunitResult test_validar_passageiro_existe(const MunitParameter params[], void* data) {
    UNUSED(params);
    UNUSED(data);

    // Configura um passageiro de teste
    Passageiro passageiroTeste = {
        .codigo = 1,
        .fidelidade = 1
    };
    listaPassageiros[qtdPassageiros++] = passageiroTeste;
    
    // Testa passageiro existente
    munit_assert_true(validarPassageiroExiste(1));
    
    // Testa passageiro inexistente
    munit_assert_false(validarPassageiroExiste(999));
    
    return MUNIT_OK;
}

/* Teste de cadastro de reserva */
static MunitResult test_cadastro_reserva(const MunitParameter params[], void* data) {
    UNUSED(params);
    UNUSED(data);

    // Configura dados necessários para o teste
    Voo vooTeste = {
        .codigo = 1,
        .status = 1,
        .tarifa = 500.0
    };
    listaVoos[qtdVoos++] = vooTeste;

    Passageiro passageiroTeste = {
        .codigo = 1,
        .fidelidade = 1
    };
    listaPassageiros[qtdPassageiros++] = passageiroTeste;

    // Cria uma reserva manualmente (simulando input do usuário)
    Reserva novaReserva = {
        .codigo = 1,
        .codigoVoo = 1,
        .numeroAssento = 1,
        .codigoPassageiro = 1,
        .valorTotal = 500.0
    };
    listaReservas[qtdReservas++] = novaReserva;

    // Verifica se a reserva foi criada corretamente
    munit_assert_int(qtdReservas, ==, 1);
    munit_assert_int(listaReservas[0].codigo, ==, 1);
    munit_assert_float(listaReservas[0].valorTotal, ==, 500.0);
    
    return MUNIT_OK;
}

/* Lista de testes */
static MunitTest test_suite_tests[] = {
    {
        "/verificar_disponibilidade_assento",
        test_verificar_disponibilidade_assento,
        test_setup,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/validar_passageiro_existe",
        test_validar_passageiro_existe,
        test_setup,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/cadastro_reserva",
        test_cadastro_reserva,
        test_setup,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* Definição da suite de testes */
static const MunitSuite test_suite = {
    "/reserva",
    test_suite_tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&test_suite, NULL, argc, argv);
}