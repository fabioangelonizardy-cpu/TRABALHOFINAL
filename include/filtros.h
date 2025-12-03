#ifndef FILTROS_H
#define FILTROS_H

#include "types.h"

// Filtros
void listar_aeronaves_por_fabricante(const string fabricante, dados_aeronaves_t *lista);
void listar_aeronaves_por_modelo(const string modelo, dados_aeronaves_t *lista);
void listar_aeronaves_por_tipo(tipo_t tipo, dados_aeronaves_t *lista);
void listar_aeronaves_por_ano_fabricacao(int ano, dados_aeronaves_t *lista);
void listar_aeronaves_por_situacao(situacao_t situacao, dados_aeronaves_t *lista);
void alterar_situacao_aeronave(const string matricula, situacao_t nova_situacao, dados_aeronaves_t *lista);
void manutencoes_aeronave(const string matricula, dados_aeronaves_t *lista);

#endif