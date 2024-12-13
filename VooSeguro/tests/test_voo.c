#include "../lib/munit/munit.h"
#include "../src/cadastrarVoo.h"

static void* test_setup(const MunitParameter params[], void* user_data) {
    (void) params; // Ignora parâmetro não utilizado
    (void) user_data; // Ignora parâmetro não utilizado
    qtdVoos = 0;
    memset(listaVoos, 0, sizeof(listaVoos));
    memset(listaAssentos, 0, sizeof(listaAssentos));
    return NULL;
}

static MunitResult test_validar_data(const MunitParameter params[], void* data) {
    (void) params; // Ignora parâmetro não utilizado
    (void) data; // Ignora parâmetro não utilizado

    // Datas válidas
    munit_assert_true(validarData("01/01/2024"));
    munit_assert_true(validarData("31/12/2024"));
    
    // Datas inválidas
    munit_assert_false(validarData("32/12/2024")); // Dia inválido
    munit_assert_false(validarData("12/13/2024")); // Mês inválido
    munit_assert_false(validarData("01/01/2023")); // Ano anterior
    munit_assert_false(validarData("01-01-2024")); // Formato inválido
    
    return MUNIT_OK;
}

static MunitResult test_validar_hora(const MunitParameter params[], void* data) {
    (void) params; // Ignora parâmetro não utilizado
    (void) data; // Ignora parâmetro não utilizado

    // Horas válidas
    munit_assert_true(validarHora("00:00"));
    munit_assert_true(validarHora("23:59"));
    
    // Horas inválidas
    munit_assert_false(validarHora("24:00")); // Hora inválida
    munit_assert_false(validarHora("23:60")); // Minuto inválido
    munit_assert_false(validarHora("1:30"));  // Formato inválido
    
    return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
    {
        "/validar_data",
        test_validar_data,
        test_setup,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/validar_hora",
        test_validar_hora,
        test_setup,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
    "/voo",
    test_suite_tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&test_suite, NULL, argc, argv);
}
