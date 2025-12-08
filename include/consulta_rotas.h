#ifndef CONSULTA_ROTAS_H
#define CONSULTA_ROTAS_H

#include "types.h"

dados_cia_t *cadastrar_nova_rota();
void inicializar_base_rotas(struct base_rotas *rotas);
void inserir_rota(dados_cia_t **lista, dados_cia_t *nova);
void inicializar_base_rotas(struct base_rotas *rotas);
void relatorio_rotas_cadastradas(dados_cia_t *lista);

void listar_rotas_por_origem(const string origem, dados_cia_t *lista);
void listar_rotas_por_destino(const string destino, dados_cia_t *lista);

int consultar_rota_por_data(data_hora_t data, dados_cia_t *base);
int consumo_combustivel_intervalo_datas(data_hora_t data_inicio, data_hora_t data_fim, dados_cia_t *lista);
void percentual_voos_realizados_destino(const string destino, dados_cia_t *lista, dados_aeronaves_t *aeronaves);

void listar_rota_maior_numero_passageiros(dados_cia_t *lista);
void listar_rota_menor_numero_passageiros(dados_cia_t *lista);

void inserir_rota_base_dados(struct base_rotas *rotas, dados_cia_t *rota, int modo);

#endif