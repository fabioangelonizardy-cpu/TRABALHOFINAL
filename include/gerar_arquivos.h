#ifndef GERAR_ARQUIVOS_H
#define GERAR_ARQUIVOS_H

#include "./types.h"

//Gerar arquivos de texto
void exportar_aeronaves_arquivo_texto(const string nome_arquivo, dados_aeronaves_t *lista);
void exportar_rotas_arquivo_texto(const string nome_arquivo, dados_cia_t *lista);
void exportar_aeronaves_arquivo_texto_binario(const string nome_arquivo, dados_aeronaves_t *lista);
void exportar_rotas_arquivo_texto_binario(const string nome_arquivo, dados_cia_t *lista);

#endif