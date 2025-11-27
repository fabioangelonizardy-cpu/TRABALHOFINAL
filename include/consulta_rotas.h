#ifndef CONSULTA_ROTAS_H
#define CONSULTA_ROTAS_H

#include "./types.h"

dados_cia_t *cadastrar_nova_rota();
void inserir_rota(dados_cia_t **lista, dados_cia_t *nova);
void mostrar_membros_tripulacao(dados_aeronaves_t *aeronave);

#endif