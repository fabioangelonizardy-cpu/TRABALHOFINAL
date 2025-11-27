#ifndef FUNCAO_BASE_H
#define FUNCAO_BASE_H

// Funções base
#include "./types.h"

int menu();
void clear_input(void);
void nova_linha(string str);
bool date_in_range(data_hora_t d, data_hora_t start, data_hora_t end);
void formatar_maiusculo(char* str);

#endif