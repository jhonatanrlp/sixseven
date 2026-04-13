# Makefile para Base SixSeven Interpretador
#
# Base SixSeven: Linguagem real com aritmética em base 67
# Todos os números são interpretados em base 67.

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS = -lm

SRC_DIR = src
BIN_DIR = .

SOURCES = $(SRC_DIR)/main.c \
          $(SRC_DIR)/base67.c \
          $(SRC_DIR)/lexer.c \
          $(SRC_DIR)/parser.c \
          $(SRC_DIR)/ast.c \
          $(SRC_DIR)/runtime.c \
          $(SRC_DIR)/memory.c \
          $(SRC_DIR)/value.c \
          $(SRC_DIR)/builtins.c

HEADERS = $(SRC_DIR)/base67.h \
          $(SRC_DIR)/lexer.h \
          $(SRC_DIR)/parser.h \
          $(SRC_DIR)/ast.h \
          $(SRC_DIR)/runtime.h \
          $(SRC_DIR)/memory.h \
          $(SRC_DIR)/value.h \
          $(SRC_DIR)/builtins.h

OBJECTS = $(SOURCES:.c=.o)
TARGET = $(BIN_DIR)/sixseven

.PHONY: all clean test help

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Linkando $(TARGET)..."
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "✓ Compilação concluída com sucesso!"
	@echo ""
	@echo "Executar exemplos:"
	@echo "  ./sixseven examples/hello_world.s67"
	@echo "  ./sixseven examples/aritmetica.s67"
	@echo "  ./sixseven examples/loops.s67"

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@echo "Compilando $<..."
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "Limpando objetos e executável..."
	rm -f $(OBJECTS) $(TARGET)
	@echo "✓ Limpeza concluída"

rebuild: clean all

test: $(TARGET)
	@echo ""
	@echo "====== TESTE 1: Hello World ======"
	./sixseven examples/hello_world.s67
	@echo ""
	@echo "====== TESTE 2: Aritmética ======"
	./sixseven examples/aritmetica.s67
	@echo ""
	@echo "====== TESTE 3: Loops ======"
	./sixseven examples/loops.s67

help:
	@echo "Base SixSeven - Makefile"
	@echo "Alvos disponíveis:"
	@echo "  make         - compila o interpretador"
	@echo "  make test    - compila e executa testes"
	@echo "  make clean   - remove arquivos compilados"
	@echo "  make rebuild - limpa e recompila"
	@echo "  make help    - mostra esta mensagem"

.SILENT: help
