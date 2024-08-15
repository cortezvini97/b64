# Defina o compilador e os flags de compilação
CC = gcc
CFLAGS = -fPIC -Iinclude
LDFLAGS = -shared

# Diretórios de destino
BUILD_DIR = build
DIST_DIR = dist
TEST_DIR = tests
INCLUDE_DIR = /usr/include/b64
LIB_DIR = /usr/lib/b64
LD_CONFIG_PATH = /etc/ld.so.conf.d/b64.conf

# Nome do arquivo de saída
TARGET = $(DIST_DIR)/libB64.so
TEST_EXEC = $(TEST_DIR)/main

# Lista de arquivos fonte para a biblioteca
LIB_SRCS = src/b64.c
LIB_OBJS = $(patsubst src/%.c, $(BUILD_DIR)/%.o, $(LIB_SRCS))

# Lista de arquivos fonte para o executável de teste
TEST_SRCS = src/main.c src/b64.c
TEST_OBJS = $(patsubst src/%.c, $(BUILD_DIR)/%.o, $(TEST_SRCS))

# Regra padrão
all: $(TARGET)

# Criação dos diretórios de destino, se necessário
$(BUILD_DIR) $(DIST_DIR) $(TEST_DIR):
	mkdir -p $@

# Regra para criar a biblioteca compartilhada
$(TARGET): $(LIB_OBJS) | $(DIST_DIR)
	$(CC) $(LDFLAGS) -o $@ $(LIB_OBJS)

# Regra para compilar arquivos .c em .o e colocar em build/
$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para compilar e gerar o executável de teste
$(TEST_EXEC): $(BUILD_DIR)/main.o $(BUILD_DIR)/b64.o | $(TEST_DIR)
	$(CC) -o $@ $(BUILD_DIR)/main.o $(BUILD_DIR)/b64.o

# Regra para compilar main.c em main.o
$(BUILD_DIR)/main.o: src/main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/main.c -o $@

# Regra para compilar b64.c em b64.o
$(BUILD_DIR)/b64.o: src/b64.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/b64.c -o $@

# Regra para limpar os arquivos gerados
clean:
	rm -f $(LIB_OBJS) $(TARGET)
	rm -f $(TEST_OBJS) $(TEST_EXEC)
	rmdir $(BUILD_DIR) 2>/dev/null || true
	rmdir $(TEST_DIR) 2>/dev/null || true
	rm -rf $(DIST_DIR)

# Regra para compilar e executar o executável de teste
test: $(TEST_EXEC)
	$(TEST_EXEC)

install: $(TARGET)
	make unistall
	mkdir -p $(INCLUDE_DIR)
	mkdir -p $(LIB_DIR)
	cp include/b64.h $(INCLUDE_DIR)/
	cp $(TARGET) $(LIB_DIR)/
	echo "$(LIB_DIR)" > $(LD_CONFIG_PATH)
	ldconfig

unistall:
	rm -f $(INCLUDE_DIR)/b64.h
	rm -f $(LIB_DIR)/libB64.so
	rm -f $(LD_CONFIG_PATH)
	ldconfig

.PHONY: all clean test install uninstall