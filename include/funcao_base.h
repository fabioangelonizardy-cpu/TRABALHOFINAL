#ifndef FUNCAO_BASE_H
#define FUNCAO_BASE_H

// Funções base
#include "types.h"
#include <stdbool.h>

int menu();
int sub_menu_aeronaves();
int sub_menu_rotas();
int sub_menu_filtros();
int sub_menu_consulta_rotas();
int sub_menu_arquivos();
int sub_menu_relatorios_arquivos();
void clear_input();
void nova_linha(string str);
bool date_in_range(data_hora_t d, data_hora_t start, data_hora_t end);
void formatar_maiusculo(char* str);


#endif