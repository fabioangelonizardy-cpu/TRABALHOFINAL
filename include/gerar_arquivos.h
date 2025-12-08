#ifndef GERAR_ARQUIVOS_H
#define GERAR_ARQUIVOS_H

#include "types.h"

// Funções para salvar e carregar dados em arquivos binários
void salvar_dados_aeronaves_binario(dados_aeronaves_t *inicio);
void salvar_dados_rotas_binario(dados_cia_t *inicio);
void carregar_dados_aeronaves(struct base_aeronaves *aeronaves);
void carregar_dados_rotas(struct base_rotas *rotas);

// Funções para exportar dados em arquivos de TXT
void exportar_aeronaves_arquivo_txt(dados_aeronaves_t *aeronaves, char *nome_arq);
void exportar_rotas_arquivo_txt(dados_cia_t *rotas, char *nome_arq);

// Funções para exportar dados em arquivos de CSV
void exportar_aeronaves_arquivo_csv(dados_aeronaves_t *aeronaves, char *nome_arq);
void exportar_rotas_arquivo_csv(dados_cia_t *rotas, char *nome_arq);

// Funções para exportar dados em arquivos de HTML
void exportar_aeronaves_arquivo_html(dados_aeronaves_t *aeronaves, char *nome_arq);
void exportar_rotas_arquivo_html(dados_cia_t *rotas, char *nome_arq);

#endif