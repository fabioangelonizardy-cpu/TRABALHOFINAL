CC = gcc
SRC_DIR = src
INCLUDE = include
OBJ = obj
BIN = bin

CFLAGS = -Wall -Wextra -g -MMD -MP
CPPFLAGS = -I$(INCLUDE)
LDFLAGS =

# lista de fontes: main.c + todos os .c em src
SRCS = main.c $(wildcard $(SRC_DIR)/*.c)

# objetos em obj/ com nomes sem diretório
OBJS = $(patsubst %.c,$(OBJ)/%.o,$(notdir $(SRCS)))
DEPS = $(OBJS:.o=.d)

TARGET = $(BIN)/projetofinal

.PHONY: all clean dirs

all: dirs $(TARGET)

dirs:
	mkdir -p $(OBJ) $(BIN)

# link final
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# regra: compila main.c -> obj/main.o
$(OBJ)/main.o: main.c | $(OBJ)
    $(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# regra: compila src/%.c -> obj/%.o
$(OBJ)/%.o: $(SRC_DIR)/%.c | $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# inclui dependências geradas (-MMD). O - include evita erro se .d não existir ainda.
-include $(DEPS)

clean:
	rm -rf $(OBJ) $(BIN)