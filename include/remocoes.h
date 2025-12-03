#ifndef REMOCOES_H
#define REMOCOES_H

#include "types.h"

// Remoções
void remover_aeronave_por_matricula(const string matricula, dados_aeronaves_t **lista);
void remover_rota_por_codigo(const string codigo_rota, dados_cia_t **lista);

#endif