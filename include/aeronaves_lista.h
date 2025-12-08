#ifndef AERONAVES_LISTA_H
#define AERONAVES_LISTA_H

#include "types.h"

// Aeronaves (LISTA)
dados_aeronaves_t *cadastrar_nova_aeronave();
void inicializar_base_aeronaves(struct base_aeronaves *aeronaves);
void inserir_aeronave(dados_aeronaves_t **lista, dados_aeronaves_t *nova);

dados_aeronaves_t *busca_aeronave_por_matricula(const char *matricula, dados_aeronaves_t *lista);
void relatorio_aeronaves_cadastradas(dados_aeronaves_t *lista);

void quantidade_manutencoes_aeronave(const string matricula, dados_aeronaves_t *lista);
void alterar_situacao_aeronave(const string matricula, situacao_t nova_situacao, dados_aeronaves_t *lista);

#endif