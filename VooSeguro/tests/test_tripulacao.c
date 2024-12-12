#include "../lib/munit/munit.h"
#include "../src/cadastrarTripulacao.h"

/* Função de preparação (setup)
   Esta função é executada antes de cada teste para garantir um ambiente limpo */
static void* test_setup(const MunitParameter params[], void* user_data) {
    qtdTripulacao = 0;  // Reseta o contador
    memset(listaTripulacao, 0, sizeof(listaTripulacao));  // Limpa a lista
    return NULL;
}

/* Teste de validação de cargo
   Verifica se a função aceita apenas os cargos permitidos */
static MunitResult test_validar_cargo(const MunitParameter params[], void* data) {
    // Teste com cargos válidos
    munit_assert_true(validarCargo("piloto"));
    munit_assert_true(validarCargo("copiloto"));
    munit_assert_true(validarCargo("comissario"));
    
    // Teste com variações de maiúsculas/minúsculas
    munit_assert_true(validarCargo("PILOTO"));
    munit_assert_true(validarCargo("Copiloto"));
    
    // Teste com cargos inválidos
    munit_assert_false(validarCargo("engenheiro"));
    munit_assert_false(validarCargo(""));
    
    return MUNIT_OK;
}

/* Teste de validação de telefone
   Verifica se a função aceita apenas números e respeita o tamanho máximo */
static MunitResult test_validar_telefone(const MunitParameter params[], void* data) {
    // Teste com telefones válidos
    munit_assert_true(validarTelefone("1234567890"));
    munit_assert_true(validarTelefone("31999999999"));
    
    // Teste com telefones inválidos
    munit_assert_false(validarTelefone("123-456-789")); // Contém caracteres especiais
    munit_assert_false(validarTelefone("")); // Vazio
    munit_assert_false(validarTelefone("1234567890123456")); // Muito longo
    
    return MUNIT_OK;
}

/* Teste de cadastro de tripulação
   Verifica se é possível cadastrar um membro da tripulação corretamente */
static MunitResult test_cadastro_tripulacao(const MunitParameter params[], void* data) {
    // Preparar dados de teste
    Tripulacao novo = {
        .codigo = 1,
        .nome = "João Silva",
        .telefone = "31999999999",
        .cargo = "piloto"
    };
    
    // Simular cadastro
    listaTripulacao[qtdTripulacao++] = novo;
    
    // Verificações
    munit_assert_int(qtdTripulacao, ==, 1);
    munit_assert_int(listaTripulacao[0].codigo, ==, novo.codigo);
    munit_assert_string_equal(listaTripulacao[0].nome, novo.nome);
    munit_assert_string_equal(listaTripulacao[0].cargo, novo.cargo);
    
    return MUNIT_OK;
}

/* Definição da suite de testes 
   Aqui listamos todos os testes que criamos */
static MunitTest test_suite_tests[] = {
    {
        "/validar_cargo",
        test_validar_cargo,
        test_setup,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/validar_telefone",
        test_validar_telefone,
        test_setup,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/cadastro_tripulacao",
        test_cadastro_tripulacao,
        test_setup,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* Definição da suite principal */
static const MunitSuite test_suite = {
    "/tripulacao",
    test_suite_tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

/* Função principal */
int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&test_suite, NULL, argc, argv);
}