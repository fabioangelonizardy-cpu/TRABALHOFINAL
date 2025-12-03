#ifndef GERAR_ARQUIVOS_H
#define GERAR_ARQUIVOS_H

#include "types.h"

//Gerar arquivos de texo
void salvar_dados_aeronaves_binario(struct dados_aeronaves *inicio);
void salvar_dados_rotas_binario(struct dados_cia *inicio);
void carregar_dados_aeronaves(struct dados_aeronaves *aeronaves);
void carregar_dados_rotas(struct dados_cia *rotas);
void exportar_aeronaves_arquivo_txt(struct base_aeronaves *aeronaves, char *nome_arq);
void exportar_rotas_arquivo_txt(struct base_rotas *rotas, char *nome_arq);
void exportar_aeronaves_arquivo_csv(struct base_aeronaves *aeronaves, char *nome_arq);
void exportar_rotas_arquivo_csv(struct base_rotas *rotas, char *nome_arq);
void exportar_aeronaves_arquivo_html(struct base_aeronaves *aeronaves, char *nome_arq);
void exportar_rotas_arquivo_html(struct base_rotas *rotas, char *nome_arq);


#endif