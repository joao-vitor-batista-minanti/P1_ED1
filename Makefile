# --- Compilador e Flags ---
# Define o compilador a ser usado (gcc)
CC = gcc
# Flags de compilação:
# -Wall e -Wextra: Ativam todos os avisos importantes do compilador.
# -std=c11: Usa o padrão C11 da linguagem.
# -g: Inclui informações de depuração no executável (essencial para usar um debugger).
# -Iinclude: Diz ao compilador para procurar arquivos de cabeçalho (.h) na pasta 'include'.
CFLAGS = -Wall -Wextra -std=c11 -g -Iinclude

# --- Diretórios ---
# Nome do executável final que será criado.
EXECUTAVEL = jogo.exe
# Diretório onde o executável será colocado.
BIN_DIR = bin
# Diretório onde os arquivos objeto (.o) serão colocados.
BUILD_DIR = build
# Diretório onde os arquivos fonte (.c) estão.
SRC_DIR = src

# --- Descoberta Automática de Arquivos ---
# Encontra todos os arquivos .c dentro da pasta SRC_DIR e subpastas.
SOURCES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
# Gera os nomes dos arquivos objeto correspondentes, que irão para a pasta BUILD_DIR.
# Ex: src/game/lista.c se torna build/game/lista.o
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# --- Regras Principais ---

# A regra 'all' é a padrão. Executada quando você digita apenas 'make'.
all: $(BIN_DIR)/$(EXECUTAVEL)

# Regra para linkar todos os arquivos objeto (.o) e criar o executável final.
# O '$^' é uma variável automática que representa TODAS as dependências (todos os .o).
$(BIN_DIR)/$(EXECUTAVEL): $(OBJECTS)
	@echo "Ligando os arquivos para criar o executável..."
	@mkdir -p $(BIN_DIR)
	$(CC) $^ -o $@

# Regra genérica para compilar um arquivo .c em um .o.
# Esta regra mágica é executada para cada arquivo .c.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compilando $< -> $@"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra 'clean' para limpar a bagunça (arquivos compilados).
clean:
	@echo "Limpando arquivos gerados..."
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Declara que 'all' e 'clean' não são nomes de arquivos.
.PHONY: all clean
