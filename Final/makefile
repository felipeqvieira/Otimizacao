# Definições de variáveis
CC = gcc
CFLAGS = -Wall -Ilib
SRC_DIR = src
OBJ_DIR = obj
EXEC = comissao

# Lista de arquivos de origem e objetos
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Regra principal
all: $(EXEC)

# Regra para compilar o executável
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para compilar arquivos .c em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Regra de limpeza
clean:
	rm -rf $(OBJ_DIR) $(EXEC)

# Regra para recompilar tudo
rebuild: clean all

# Regra para incluir dependências automaticamente
-include $(OBJS:.o=.d)

# Regras para criar arquivos .d (dependências)
$(OBJ_DIR)/%.d: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -MM $< > $@
	@mv -f $@ $@.tmp
	@sed 's|.*:|$(OBJ_DIR)/$*.o:|' < $@.tmp > $@
	@rm -f $@.tmp

.PHONY: all clean rebuild
