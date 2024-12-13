CC = gcc
CFLAGS = -Wall -Wextra -I./src -I./lib/munit

SRC_DIR = src
TEST_DIR = tests
LIB_DIR = lib/munit

# Arquivos fonte base
BASE_SOURCES = $(SRC_DIR)/cadastrarTripulacao.c \
               $(SRC_DIR)/cadastrarPassageiro.c \
               $(SRC_DIR)/cadastrarVoo.c \
               $(SRC_DIR)/cadastrarReserva.c \
               $(SRC_DIR)/pesquisa.c

# Executáveis
MAIN = vooseguro
TEST_PASSAGEIRO = test_passageiro
TEST_TRIPULACAO = test_tripulacao
TEST_VOO = test_voo
TEST_RESERVA = test_reserva

all: $(MAIN) $(TEST_PASSAGEIRO) $(TEST_TRIPULACAO) $(TEST_VOO) $(TEST_RESERVA)

$(MAIN): $(SRC_DIR)/main.c $(BASE_SOURCES)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_PASSAGEIRO): $(TEST_DIR)/test_passageiro.c $(SRC_DIR)/cadastrarPassageiro.c $(LIB_DIR)/munit.c
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_TRIPULACAO): $(TEST_DIR)/test_tripulacao.c $(SRC_DIR)/cadastrarTripulacao.c $(LIB_DIR)/munit.c
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_VOO): $(TEST_DIR)/test_voo.c $(BASE_SOURCES) $(LIB_DIR)/munit.c
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_RESERVA): $(TEST_DIR)/test_reserva.c $(BASE_SOURCES) $(LIB_DIR)/munit.c
	$(CC) $(CFLAGS) $^ -o $@

test: $(TEST_PASSAGEIRO) $(TEST_TRIPULACAO) $(TEST_VOO) $(TEST_RESERVA)
	./$(TEST_PASSAGEIRO)
	./$(TEST_TRIPULACAO)
	./$(TEST_VOO)
	./$(TEST_RESERVA)
	@echo "Todos os testes foram executados com sucesso!"

clean:
	rm -f $(MAIN) $(TEST_PASSAGEIRO) $(TEST_TRIPULACAO) $(TEST_VOO) $(TEST_RESERVA)

run: $(MAIN)
	./$(MAIN)

.PHONY: all test clean run
