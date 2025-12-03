#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../include/types.h"
#include "../include/funcao_base.h"
#include "../include/gerar_arquivos.h"
#include "../include/aeronaves_lista.h"
#include "../include/consulta_rotas.h"

// ----------------------------------- EXPORTAR PARA ARQUIVO DE TEXTO -----------------------------------
void salvar_dados_aeronaves_binario(struct dados_aeronaves *inicio)
{
    FILE *file = fopen("aeronaves.bin", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    struct dados_aeronaves *atual = inicio;
    while (atual != NULL) {
        fwrite(atual, sizeof(struct dados_aeronaves), 1, file);
        atual = atual->prox;
    }
    fclose(file);

}

void salvar_dados_rotas_binario(struct dados_cia *inicio)
{
    FILE *file = fopen("rotas.bin", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    struct dados_cia *atual = inicio;
    while (atual != NULL) {
        fwrite(atual, sizeof(struct dados_cia), 1, file);
        atual = atual->prox;
    }
    fclose(file);

}
void carregar_dados_aeronaves(struct dados_aeronaves *aeronaves)
{
    FILE *fp = NULL;
    struct dados_aeronaves *novo = NULL;

    fp = fopen("aeronaves.bin", "rb");
    if (!fp) {
        printf("Erro ao tentar abrir arquivo aeronaves.bin\n");
        return;
    }
    while (!feof(fp)) {
        novo = (struct dados_aeronaves*)malloc(sizeof(struct dados_aeronaves));

        fread(novo, sizeof(struct dados_aeronaves), 1, fp);
        novo->prox = NULL;
        if (!feof(fp)) {
            inserir_aeronave(&aeronaves, novo);
        }
        else {
            free(novo);
        }
    }
    fclose(fp);

}
void carregar_dados_rotas(struct dados_cia *rotas)
{
    FILE *fp = NULL;
    struct dados_cia *novo = NULL;

    fp = fopen("rotas.bin", "rb");
    if (!fp) {
        printf("Erro ao tentar abrir arquivo rotas.bin\n");
        return;
    }
    while (!feof(fp)) {
        novo = (struct dados_cia*)malloc(sizeof(struct dados_cia));

        fread(novo, sizeof(struct dados_cia), 1, fp);
        novo->prox = NULL;
        if (!feof(fp)) {
            inserir_rota(&rotas, novo);
        }
        else {
            free(novo);
        }
    }
    fclose(fp);


}
void exportar_aeronaves_arquivo_txt(struct base_aeronaves *aeronaves, char *nome_arq)
{
        FILE *fp = NULL;

    fp = fopen(nome_arq, "w");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita.\n", nome_arq);
        return;
    }
    struct dados_aeronaves *atual = aeronaves->inicio;
    while (atual != NULL) {
        fprintf(fp, "Identificação: %s\n", atual->identificacao);
        fprintf(fp, "Modelo: %s\n", atual->modelo);
        fprintf(fp, "Fabricante: %s\n", atual->fabricante);
        fprintf(fp, "Matrícula: %s\n", atual->matricula);
        fprintf(fp, "Ano de Fabricação: %d\n", atual->ano_fabricacao);
        fprintf(fp, "Tipo: %d\n", atual->tipo);
        fprintf(fp, "Número de Passageiros: %d\n", atual->n_passageiros);
        fprintf(fp, "Situação: %d\n", atual->situacao);
        fprintf(fp, "--------------------------\n");
        atual = atual->prox;
    }

    fclose(fp);
}

void exportar_rotas_arquivo_txt(struct base_rotas *rotas, char *nome_arq)
{
    FILE *fp = NULL;

    fp = fopen(nome_arq, "w");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita.\n", nome_arq);
        return;
    }
    struct dados_cia *atual = rotas->inicio;
    while (atual != NULL) {
        fprintf(fp, "Código da Rota: %s\n", atual->codigo_rota);
        fprintf(fp, "Data e Hora de Partida: %02d/%02d/%04d %02dh\n", atual->data_hora_partida.dia, atual->data_hora_partida.mes, atual->data_hora_partida.ano, atual->data_hora_partida.hora);
        fprintf(fp, "Origem: %s\n", atual->origem);
        fprintf(fp, "Destino: %s\n", atual->destino);
        fprintf(fp, "Combustível: %d\n", atual->combustivel);
        fprintf(fp, "Quantidade de Passageiros: %d\n", atual->qtd_passageiros);
        fprintf(fp, "Quantidade de Carga: %d\n", atual->qtd_carga);
        fprintf(fp, "Quantidade de Tripulação: %d\n", atual->qtd_tripulacao);
        fprintf(fp, "Membros da Tripulação: %s\n", atual->membros_tripulacao);
        fprintf(fp, "Aeronave Alocada: %s\n", atual->aeronave_alocada);
        fprintf(fp, "--------------------------\n");
        atual = atual->prox;
    }

    fclose(fp);


}
void exportar_aeronaves_arquivo_csv(struct base_aeronaves *aeronaves, char *nome_arq)
{
    FILE *fp = NULL;

        fp = fopen(nome_arq, "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita.\n", nome_arq);
        return;
    }
    struct dados_aeronaves *atual = aeronaves->inicio;
    // Cabeçalho CSV
    fprintf(fp, "Identificação,Modelo,Fabricante,Matrícula,Ano de Fabricação,Tipo,Número de Passageiros,Situação\n");
    while (atual != NULL) {
        fprintf(fp, "\"%s\",\"%s\",\"%s\",\"%s\",%d,%d,%d,%d\n",
                atual->identificacao,
                atual->modelo,
                atual->fabricante,
                atual->matricula,
                atual->ano_fabricacao,
                atual->tipo,
                atual->n_passageiros,
                atual->situacao);

        atual = atual->prox;

        }
}
void exportar_rotas_arquivo_csv(struct base_rotas *rotas, char *nome_arq)
{
    FILE *fp = NULL;

        fp = fopen(nome_arq, "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita.\n", nome_arq);
        return;
    }
    struct dados_cia *atual = rotas->inicio;
    // Cabeçalho CSV
    fprintf(fp, "Código da Rota,Data e Hora de Partida,Origem,Destino,Combustível,Quantidade de Passageiros,Quantidade de Carga,Quantidade de Tripulação,Membros da Tripulação,Aeronave Alocada\n");
    while (atual != NULL) {
        fprintf(fp, "\"%s\",\"%02d/%02d/%04d %02dh\",\"%s\",\"%s\",%d,%d,%d,%d,\"%s\",\"%s\"\n",
                atual->codigo_rota,
                atual->data_hora_partida.dia,
                atual->data_hora_partida.mes,
                atual->data_hora_partida.ano,
                atual->data_hora_partida.hora,
                atual->origem,
                atual->destino,
                atual->combustivel,
                atual->qtd_passageiros,
                atual->qtd_carga,
                atual->qtd_tripulacao,
                atual->membros_tripulacao,
                atual->aeronave_alocada);

        atual = atual->prox;

        }

}
void exportar_aeronaves_arquivo_html(struct base_aeronaves *aeronaves, char *nome_arq)
{
        FILE *fp = NULL;

    fp = fopen(nome_arq, "w");

    if (!fp) {
        printf("Erro ao tentar abrir arquivo %s\n", nome_arq);
        return;
    }
    fprintf(fp, "<HTML> <HEAD> <TITLE> RELATORIO DE AERONAVES </TITLE> </HEAD> <BODY> \n");
    fprintf(fp, "<TABLE border = '1'> <TR> <TH> IDENTIFICAÇÃO </TH> <TH> MODELO </TH> <TH> FABRICANTE </TH> <TH> MATRÍCULA </TH> <TH> ANO DE FABRICAÇÃO </TH> <TH> TIPO </TH> <TH> NÚMERO DE PASSAGEIROS </TH> <TH> SITUAÇÃO </TH> </TR>\n");
    struct dados_aeronaves *atual = aeronaves->inicio;
    while (atual) {
        fprintf(fp, "<TR> <TD> %s </TD> <TD> %s </TD> <TD>%s</TD> <TD>%s</TD> <TD>%d</TD> <TD>%d</TD> <TD>%d</TD> <TD>%d</TD> </TR>\n",
                atual->identificacao,
                atual->modelo,
                atual->fabricante,
                atual->matricula,
                atual->ano_fabricacao,
                atual->tipo,
                atual->n_passageiros,
                atual->situacao);
        atual = atual->prox; 
    }

}
void exportar_rotas_arquivo_html(struct base_rotas *rotas, char *nome_arq)
{
    FILE *fp = NULL;

    fp = fopen(nome_arq, "w");

    if (!fp) {
        printf("Erro ao tentar abrir arquivo %s\n", nome_arq);
        return;
    }
    fprintf(fp, "<HTML> <HEAD> <TITLE> RELATORIO DE ROTAS </TITLE> </HEAD> <BODY> \n");
    fprintf(fp, "<TABLE border = '1'> <TR> <TH> CÓDIGO DA ROTA </TH> <TH> DATA E HORA DE PARTIDA </TH> <TH> ORIGEM </TH> <TH> DESTINO </TH> <TH> COMBUSTÍVEL </TH> <TH> QUANTIDADE DE PASSAGEIROS </TH> <TH> QUANTIDADE DE CARGA </TH> <TH> QUANTIDADE DE TRIPULAÇÃO </TH> <TH> MEMBROS DA TRIPULAÇÃO </TH> <TH> AERONAVE ALOCADA </TH> </TR>\n");
    struct dados_cia *atual = rotas->inicio;
    while (atual) {
        fprintf(fp, "<TR> <TD> %s </TD> <TD> %02d/%02d/%04d %02dh </TD> <TD>%s</TD> <TD>%s</TD> <TD>%d</TD> <TD>%d</TD> <TD>%d</TD> <TD>%d</TD> <TD>%s</TD> <TD>%s</TD> </TR>\n",
                atual->codigo_rota,
                atual->data_hora_partida.dia,
                atual->data_hora_partida.mes,
                atual->data_hora_partida.ano,
                atual->data_hora_partida.hora,
                atual->origem,
                atual->destino,
                atual->combustivel,
                atual->qtd_passageiros,
                atual->qtd_carga,
                atual->qtd_tripulacao,
                atual->membros_tripulacao,
                atual->aeronave_alocada);
        atual = atual->prox; 
    }

}

