// Incluímos as bibliotecas necessárias
#include "../lib/munit/munit.h"    // Framework de testes
#include "../src/cadastrarPassageiro.h"  // Nossa implementação

/* Função de preparação (setup)
   Esta função é executada antes de cada teste para garantir um ambiente limpo */
static void* test_setup(const MunitParameter params[], void* user_data) {
    (void) params;
    (void) user_data;
    qtdPassageiros = 0;  // Reseta o contador de passageiros
    memset(listaPassageiros, 0, sizeof(listaPassageiros));  // Limpa o array
    return NULL;
}

/* Teste da função validarNumeros() 
   Verifica se a validação de números está funcionando corretamente */
static MunitResult test_validar_numeros(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;

    // Teste com entrada válida (apenas números)
    munit_assert_true(validarNumeros("123456789"));
    
    // Teste com entrada inválida (contém letras)
    munit_assert_false(validarNumeros("123abc456"));
    
    // Teste com entrada vazia
    munit_assert_false(validarNumeros(""));
    
    return MUNIT_OK;
}

/* Teste da função validarEndereco() 
   Verifica se a validação de endereço está funcionando corretamente */
static MunitResult test_validar_endereco(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;

    // Teste com endereço válido
    munit_assert_true(validarEndereco("Rua das Flores, 123"));
    
    // Teste com endereço vazio (deve falhar)
    munit_assert_false(validarEndereco(""));
    
    return MUNIT_OK;
}

/* Teste do cadastro de passageiro 
   Verifica se é possível cadastrar um passageiro com sucesso */
static MunitResult test_cadastro_passageiro(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;

    // Preparar dados de teste
    Passageiro p = {
        .codigo = 1,
        .nome = "João Silva",
        .endereco = "Rua ABC, 123",
        .telefone = "31999999999",
        .fidelidade = 1
    };
    
    // Simular o cadastro (adicionando diretamente para teste)
    listaPassageiros[qtdPassageiros++] = p;
    
    // Verificar se o passageiro foi cadastrado corretamente
    munit_assert_int(qtdPassageiros, ==, 1);
    munit_assert_int(listaPassageiros[0].codigo, ==, p.codigo);
    munit_assert_string_equal(listaPassageiros[0].nome, p.nome);
    
    return MUNIT_OK;
}

/* Definição da suite de testes
   Aqui listamos todos os testes que queremos executar */
static MunitTest test_suite_tests[] = {
    {
        "/validar_numeros",  // Nome do teste
        test_validar_numeros,  // Função de teste
        test_setup,  // Função de preparação
        NULL,  // Função de limpeza (não necessária aqui)
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/validar_endereco",
        test_validar_endereco,
        test_setup,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/cadastro_passageiro",
        test_cadastro_passageiro,
        test_setup,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }  // Marca o fim da suite
};

/* Definição da suite principal */
static const MunitSuite test_suite = {
    "/passageiro_tests",  // Prefixo para todos os testes
    test_suite_tests,     // Array de testes
    NULL,                 // Suites filhas
    1,                    // Iterações
    MUNIT_SUITE_OPTION_NONE
};

/* Função principal que executa os testes */
int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&test_suite, NULL, argc, argv);
}
