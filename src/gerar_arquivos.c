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

// ----------------------------------- EXPORTAR PARA ARQUIVO BINÁRIO -----------------------------------
void salvar_dados_aeronaves_binario(struct dados_aeronaves *inicio)
{
    FILE *file = fopen("aeronaves.bin", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    dados_aeronaves_t *atual = inicio;
    while (atual != NULL) {
        fwrite(atual, sizeof(dados_aeronaves_t), 1, file);
        atual = atual->prox;
    }

    fclose(file);
    printf("Dados das aeronaves salvos com sucesso em 'aeronaves.bin'.\n");
}

void salvar_dados_rotas_binario(struct dados_cia *inicio)
{
    FILE *file = fopen("rotas.bin", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    dados_cia_t *atual = inicio;
    while (atual != NULL) {
        fwrite(atual, sizeof(dados_cia_t), 1, file);
        atual = atual->prox;
    }

    fclose(file);
    printf("Dados das rotas salvos com sucesso em 'rotas.bin'.\n");
}

// ----------------------------------- IMPORTAR DE ARQUIVO BINÁRIO -----------------------------------
void carregar_dados_aeronaves(struct dados_aeronaves *aeronaves)
{
    FILE *file = fopen("aeronaves.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }
    dados_aeronaves_t temp;
    while (fread(&temp, sizeof(dados_aeronaves_t), 1, file)) {
        dados_aeronaves_t *nova = (dados_aeronaves_t *)malloc(sizeof(dados_aeronaves_t));
        if (nova == NULL) {
            printf("Erro ao alocar memória para aeronave.\n");
            fclose(file);
            return;
        }
        *nova = temp;
        nova->prox = NULL;
        inserir_aeronave(&aeronaves, nova);
    }
    fclose(file);
    printf("Dados das aeronaves carregados com sucesso de 'aeronaves.bin'.\n");
}

void carregar_dados_rotas(struct dados_cia *rotas)
{
    FILE *file = fopen("rotas.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }
    dados_cia_t temp;
    while (fread(&temp, sizeof(dados_cia_t), 1, file)) {
        dados_cia_t *nova = (dados_cia_t *)malloc(sizeof(dados_cia_t));
        if (nova == NULL) {
            printf("Erro ao alocar memória para rota.\n");
            fclose(file);
            return;
        }
        *nova = temp;
        nova->prox = NULL;
        inserir_rota(&rotas, nova);
    }
    fclose(file);
    printf("Dados das rotas carregados com sucesso de 'rotas.bin'.\n");
}

// ----------------------------------- EXPORTAR PARA ARQUIVO TXT -----------------------------------
void exportar_aeronaves_arquivo_txt(struct base_aeronaves *aeronaves, char *nome_arq)
{
    FILE *file = fopen(nome_arq, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    dados_aeronaves_t *atual = aeronaves->inicio;
    while (atual != NULL) {
        fprintf(file, "Identificação: %s\n", atual->identificacao);
        fprintf(file, "Modelo: %s\n", atual->modelo);
        fprintf(file, "Fabricante: %s\n", atual->fabricante);
        fprintf(file, "Matrícula: %s\n", atual->matricula);
        fprintf(file, "Ano de fabricação: %d\n", atual->ano_fabricacao);
        fprintf(file, "Tipo: %d\n", atual->tipo);
        fprintf(file, "Número de passageiros: %d\n", atual->n_passageiros);
        fprintf(file, "Situação: %d\n", atual->situacao);
        fprintf(file, "Número de manutenções: %d\n", atual->n_manutencoes);
        fprintf(file, "Manutenções: ");
        for (int i = 0; i < atual->n_manutencoes; i++) {
            fprintf(file, "%d ", atual->manutencoes[i]);
        }
        fprintf(file, "\n\n");
        atual = atual->prox;
    }
    fclose(file);
    printf("Dados das aeronaves exportados com sucesso para '%s'.\n", nome_arq);
}

void exportar_rotas_arquivo_txt(struct base_rotas *rotas, char *nome_arq)
{
    FILE *file = fopen(nome_arq, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    dados_cia_t *atual = rotas->inicio;
    while (atual != NULL) {
        fprintf(file, "Código da rota: %s\n", atual->codigo_rota);
        fprintf(file, "Data e hora de partida: %02d/%02d/%04d %02d:00\n", atual->data_hora_partida.dia,
                atual->data_hora_partida.mes, atual->data_hora_partida.ano, atual->data_hora_partida.hora);
        fprintf(file, "Origem: %s\n", atual->origem);
        fprintf(file, "Destino: %s\n", atual->destino);
        fprintf(file, "Estimativa de voo: %02d:%02d\n", atual->estimativa_voo.horas_estimada,
                atual->estimativa_voo.minutos_estimados);
        fprintf(file, "Combustível: %d litros\n", atual->combustivel);
        fprintf(file, "Quantidade de passageiros: %d\n", atual->qtd_passageiros);
        fprintf(file, "Quantidade de carga: %d kg\n", atual->qtd_carga);
        fprintf(file, "Quantidade de tripulação: %d\n", atual->qtd_tripulacao);
        fprintf(file, "Membros da tripulação: %s\n", atual->membros_tripulacao);
        fprintf(file, "Aeronave alocada: %s\n\n", atual->aeronave_alocada);
        atual = atual->prox;
    }
    fclose(file);
    printf("Dados das rotas exportados com sucesso para '%s'.\n", nome_arq);
}

// ----------------------------------- EXPORTAR PARA ARQUIVO CSV -----------------------------------

void exportar_aeronaves_arquivo_csv(struct base_aeronaves *aeronaves, char *nome_arq)
{
    FILE *file = fopen(nome_arq, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fprintf(file, "Identificação,Modelo,Fabricante,Matrícula,Ano de fabricação,Tipo,Número de passageiros,Situação,Número de manutenções,Manutenções\n");
    dados_aeronaves_t *atual = aeronaves->inicio;
    while (atual != NULL) {
        fprintf(file, "%s,%s,%s,%s,%d,%d,%d,%d,%d,\"",
                atual->identificacao,
                atual->modelo,
                atual->fabricante,
                atual->matricula,
                atual->ano_fabricacao,
                atual->tipo,
                atual->n_passageiros,
                atual->situacao,
                atual->n_manutencoes);
        for (int i = 0; i < atual->n_manutencoes; i++) {
            fprintf(file, "%d", atual->manutencoes[i]);
            if (i < atual->n_manutencoes - 1) {
                fprintf(file, " ");
            }
        }
        fprintf(file, "\"\n");
        atual = atual->prox;
    }
    fclose(file);
    printf("Dados das aeronaves exportados com sucesso para '%s'.\n", nome_arq);
}

void exportar_rotas_arquivo_csv(struct base_rotas *rotas, char *nome_arq)
{
    FILE *file = fopen(nome_arq, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fprintf(file, "Código da rota,Data e hora de partida,Origem,Destino,Estimativa de voo,Combustível,Quantidade de passageiros,Quantidade de carga,Quantidade de tripulação,Membros da tripulação,Aeronave alocada\n");
    dados_cia_t *atual = rotas->inicio;
    while (atual != NULL) {
        fprintf(file, "%s,%02d/%02d/%04d %02d:00,%s,%s,%02d:%02d,%d,%d,%d,%d,\"%s\",%s\n",
                atual->codigo_rota,
                atual->data_hora_partida.dia,
                atual->data_hora_partida.mes,
                atual->data_hora_partida.ano,
                atual->data_hora_partida.hora,
                atual->origem,
                atual->destino,
                atual->estimativa_voo.horas_estimada,
                atual->estimativa_voo.minutos_estimados,
                atual->combustivel,
                atual->qtd_passageiros,
                atual->qtd_carga,
                atual->qtd_tripulacao,
                atual->membros_tripulacao,
                atual->aeronave_alocada);
        atual = atual->prox;
    }
    fclose(file);
    printf("Dados das rotas exportados com sucesso para '%s'.\n", nome_arq);
}

// ----------------------------------- EXPORTAR PARA ARQUIVOS HTML -----------------------------------

void exportar_aeronaves_arquivo_html(struct base_aeronaves *aeronaves, char *nome_arq)
{
    FILE *file = fopen(nome_arq, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fprintf(file, "<html><head><title>Relatório de Aeronaves</title></head><body>");
    fprintf(file, "<h1>Relatório de Aeronaves</h1>");
    dados_aeronaves_t *atual = aeronaves->inicio;
    while (atual != NULL) {
        fprintf(file, "<h2>%s</h2>", atual->identificacao);
        fprintf(file, "<p><strong>Modelo:</strong> %s<br>", atual->modelo);
        fprintf(file, "<strong>Fabricante:</strong> %s<br>", atual->fabricante);
        fprintf(file, "<strong>Matrícula:</strong> %s<br>", atual->matricula);
        fprintf(file, "<strong>Ano de fabricação:</strong> %d<br>", atual->ano_fabricacao);
        fprintf(file, "<strong>Tipo:</strong> %d<br>", atual->tipo);
        fprintf(file, "<strong>Número de passageiros:</strong> %d<br>", atual->n_passageiros);
        fprintf(file, "<strong>Situação:</strong> %d<br>", atual->situacao);
        fprintf(file, "<strong>Número de manutenções:</strong> %d<br>", atual->n_manutencoes);
        fprintf(file, "<strong>Manutenções:</strong> ");
        for (int i = 0; i < atual->n_manutencoes; i++) {
            fprintf(file, "%d ", atual->manutencoes[i]);
        }
        fprintf(file, "</p>");
        atual = atual->prox;
    }
    fprintf(file, "</body></html>");
    fclose(file);
    printf("Dados das aeronaves exportados com sucesso para '%s'.\n", nome_arq);
}

void exportar_rotas_arquivo_html(struct base_rotas *rotas, char *nome_arq)
{
    FILE *file = fopen(nome_arq, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fprintf(file, "<html><head><title>Relatório de Rotas</title></head><body>");
    fprintf(file, "<h1>Relatório de Rotas</h1>");
    dados_cia_t *atual = rotas->inicio;
    while (atual != NULL) {
        fprintf(file, "<h2>%s</h2>", atual->codigo_rota);
        fprintf(file, "<p><strong>Data e hora de partida:</strong> %02d/%02d/%04d %02d:00<br>",
                atual->data_hora_partida.dia,
                atual->data_hora_partida.mes,
                atual->data_hora_partida.ano,
                atual->data_hora_partida.hora);
        fprintf(file, "<strong>Origem:</strong> %s<br>", atual->origem);
        fprintf(file, "<strong>Destino:</strong> %s<br>", atual->destino);
        fprintf(file, "<strong>Estimativa de voo:</strong> %02d:%02d<br>",
                atual->estimativa_voo.horas_estimada,
                atual->estimativa_voo.minutos_estimados);
        fprintf(file, "<strong>Combustível:</strong> %d litros<br>", atual->combustivel);
        fprintf(file, "<strong>Quantidade de passageiros:</strong> %d<br>", atual->qtd_passageiros);
        fprintf(file, "<strong>Quantidade de carga:</strong> %d kg<br>", atual->qtd_carga);
        fprintf(file, "<strong>Quantidade de tripulação:</strong> %d<br>", atual->qtd_tripulacao);
        fprintf(file, "<strong>Membros da tripulação:</strong> %s<br>", atual->membros_tripulacao);
        fprintf(file, "<strong>Aeronave alocada:</strong> %s</p>", atual->aeronave_alocada);
        atual = atual->prox;
    }
    fprintf(file, "</body></html>");
    fclose(file);
    printf("Dados das rotas exportados com sucesso para '%s'.\n", nome_arq);
} 

