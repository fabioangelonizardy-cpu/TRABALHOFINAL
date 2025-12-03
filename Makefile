CC = gcc
SRC = ./src
OBJS = ./obj
TARGET = aeroporto
LIMPAR = rm

all: objetos
	$(CC) $(OBJS)/aeronaves_lista.o $(OBJS)/consulta_rotas.o $(OBJS)/filtros.o $(OBJS)/funcao_base.o $(OBJS)/gerar_arquivos.o $(OBJS)/main.o $(OBJS)/remocoes.o -o $(TARGET)
	

objetos:
	$(CC) -c $(SRC)/aeronaves_lista.c -o $(OBJS)/aeronaves_lista.o
	$(CC) -c $(SRC)/consulta_rotas.c -o $(OBJS)/consulta_rotas.o
	$(CC) -c $(SRC)/filtros.c -o $(OBJS)/filtros.o
	$(CC) -c $(SRC)/funcao_base.c -o $(OBJS)/funcao_base.o
	$(CC) -c $(SRC)/gerar_arquivos.c -o $(OBJS)/gerar_arquivos.o
	$(CC) -c $(SRC)/remocoes.c -o $(OBJS)/remocoes.o
	$(CC) -c main.c -o $(OBJS)/main.o


clear:
	$(LIMPAR) $(OBJS)/*.o
	$(LIMPAR) $(TARGET)