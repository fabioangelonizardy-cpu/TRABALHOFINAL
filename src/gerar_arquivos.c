#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../include/types.h"
#include "../include/gerar_arquivos.h"
#include "../include/aeronaves_lista.h"
#include "../include/consulta_rotas.h"

// ----------------------------------- EXPORTAR PARA ARQUIVO BINÁRIO -----------------------------------

void salvar_dados_aeronaves_binario(dados_aeronaves_t *inicio)
{
    FILE *file = NULL;
    
    file = fopen("aeronaves.bin", "wb");

    if (!file) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    while(inicio) {
        fwrite(inicio, sizeof(dados_aeronaves_t), 1, file);
        inicio = inicio->prox;
    }

    fclose(file);
    printf("Dados das aeronaves salvos com sucesso em 'aeronaves.bin'.\n");
}


void salvar_dados_rotas_binario(dados_cia_t *inicio)
{
    FILE *file = NULL;
    
    file = fopen("rotas.bin", "wb");
    if (!file) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    while(inicio) {
        fwrite(inicio, sizeof(dados_cia_t), 1, file);
        inicio = inicio->prox;
    }

    fclose(file);
    printf("Dados das rotas salvos com sucesso em 'rotas.bin'.\n");
}

// ----------------------------------- IMPORTAR DE ARQUIVO BINÁRIO -----------------------------------

void carregar_dados_aeronaves(struct base_aeronaves *aeronaves)
{
    FILE *file = NULL;
    struct base_aeronaves *novo = NULL;

    file = fopen("aeronaves.bin", "rb");

    if(!file) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    while(!feof(file)) {
        novo = (struct base_aeronaves *)malloc(sizeof(struct base_aeronaves));
        fread(novo, sizeof(struct base_aeronaves), 1, file);
        dados_aeronaves_t *novo;
        novo = malloc(sizeof(dados_aeronaves_t));
        novo->prox = NULL;

        if(!feof(file)) {
            inserir_aeronave_base_dados(aeronaves, novo, 2);
        } else {
            free(novo);
        }
    }
}

void carregar_dados_rotas(struct base_rotas *rotas)
{
    FILE *file = NULL;
    dados_cia_t *novo = NULL;

    file = fopen("rotas.bin", "rb");

    if (!file) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    while (!feof(file)) {
        novo = (dados_cia_t *) malloc(sizeof(dados_cia_t));
        fread(novo, sizeof(dados_cia_t), 1, file);
        
        novo->prox = NULL;

        if (!feof(file)) {
            inserir_rota_base_dados(rotas, novo, 2);
        } else {
            free(novo);
        }
    }

    fclose(file);
}

// ----------------------------------- EXPORTAR PARA ARQUIVO TXT -----------------------------------

void exportar_aeronaves_arquivo_txt(dados_aeronaves_t *aeronaves, char *nome_arq)
{
    FILE *file = NULL;

    file = fopen(nome_arq, "w");

    if(!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while(aeronaves) {
        relatorio_aeronaves_cadastradas(aeronaves);
        fprintf(file, "\n");
        aeronaves = aeronaves->prox;
    }

    fclose(file);
    printf("Dados das aeronaves exportados com sucesso para '%s'.\n", nome_arq);

}


void exportar_rotas_arquivo_txt(dados_cia_t *rotas, char *nome_arq)
{
    FILE *file = NULL;

    file = fopen(nome_arq, "w");

    if(!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while(rotas) {
        relatorio_rotas_cadastradas(rotas);
        fprintf(file, "\n");
        rotas = rotas->prox;
    }

    fclose(file);
    printf("Dados das rotas exportados com sucesso para '%s'.\n", nome_arq);
}

// ----------------------------------- EXPORTAR PARA ARQUIVO CSV -----------------------------------

void exportar_aeronaves_arquivo_csv(dados_aeronaves_t *aeronaves, char *nome_arq)
{
    FILE *file = NULL;

    file = fopen(nome_arq, "w");

    if(!file) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    fprintf(file, "Identificação,Modelo,Fabricante,Matrícula,Ano de fabricação,Tipo,Número de passageiros,Situação,Número de manutenções,Manutenções\n");
    while(aeronaves) {
        fprintf(file, "%s,%s,%s,%s,%d,%d,%d,%d,%d,\"",
                aeronaves->identificacao,
                aeronaves->modelo,
                aeronaves->fabricante,
                aeronaves->matricula,
                aeronaves->ano_fabricacao,
                aeronaves->tipo,
                aeronaves->n_passageiros,
                aeronaves->situacao,
                aeronaves->n_manutencoes);
        aeronaves = aeronaves->prox;
}
    fclose(file);
}   

void exportar_rotas_arquivo_csv(dados_cia_t *rotas, char *nome_arq)
{
    FILE *file = NULL;

    file = fopen(nome_arq, "w");

    if(!file) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    fprintf(file, "Código da rota,Data e hora de partida,Origem,Destino,Estimativa de voo,Combustível,Quantidade de passageiros,Quantidade de carga,Quantidade de tripulação,Membros da tripulação,Aeronave alocada\n");
    while(rotas) {
        fprintf(file, "%s,%02d/%02d/%04d %02d:00,%s,%s,%02d:%02d,%d,%d,%d,%d,\"%s\",%s\n",
                rotas->codigo_rota,
                rotas->data_hora_partida.dia,
                rotas->data_hora_partida.mes,
                rotas->data_hora_partida.ano,
                rotas->data_hora_partida.hora,
                rotas->origem,
                rotas->destino,
                rotas->estimativa_voo.horas_estimada,
                rotas->estimativa_voo.minutos_estimados,
                rotas->combustivel,
                rotas->qtd_passageiros,
                rotas->qtd_carga,
                rotas->qtd_tripulacao,
                rotas->membros_tripulacao,
                rotas->aeronave_alocada);
        rotas = rotas->prox;
    }

    fclose(file);
}

// ----------------------------------- EXPORTAR PARA ARQUIVOS HTML -----------------------------------

void exportar_aeronaves_arquivo_html(dados_aeronaves_t *aeronaves, char *nome_arq)
{
    FILE *file = fopen(nome_arq, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    fprintf(file, "<HTML> <HEAD> <TITLE> RELATORIO DE AERONAVES </TITLE> </HEAD> <BODY>\n");
    fprintf(file, "<TABLE> border = '1' > <TR> <TH> Identificação </TH> <TH> Modelo </TH> <TH> Fabricante </TH> <TH> Matrícula </TH> <TH> Ano de fabricação </TH> <TH> Tipo </TH> <TH> Número de passageiros </TH> <TH> Situação </TH> <TH> Número de manutenções </TH> <TH> Manutenções </TH> </TR>\n");
    while (aeronaves) {
        fprintf(file, "<TR> <TD> %s </TD> <TD> %s </TD> <TD> %s </TD> <TD> %s </TD> <TD> %d </TD> <TD> %d </TD> <TD> %d </TD> <TD> %d </TD> <TD> %d </TD> <TD> ",
                aeronaves->identificacao,
                aeronaves->modelo,
                aeronaves->fabricante,
                aeronaves->matricula,
                aeronaves->ano_fabricacao,
                aeronaves->tipo,
                aeronaves->n_passageiros,
                aeronaves->situacao,
                aeronaves->n_manutencoes);
        aeronaves = aeronaves->prox;
    }
    fprintf(file, "</TABLE> </BODY> </HTML>\n");
    fclose(file);
}

void exportar_rotas_arquivo_html(dados_cia_t *rotas, char *nome_arq)
{
    FILE *file = NULL;

    file = fopen(nome_arq, "w");
    if(!file) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    fprintf(file, "<HTML> <HEAD> <TITLE> RELATORIO DE ROTAS </TITLE> </HEAD> <BODY>\n");
    fprintf(file, "<TABLE border = '1' > <TR> <TH> Código da rota </TH> <TH> Data e hora de partida </TH> <TH> Origem </TH> <TH> Destino </TH> <TH> Estimativa de voo </TH> <TH> Combustível </TH> <TH> Quantidade de passageiros </TH> <TH> Quantidade de carga </TH> <TH> Quantidade de tripulação </TH> <TH> Membros da tripulação </TH> <TH> Aeronave alocada </TH> </TR>\n");
    while(rotas) {
        fprintf(file, "<TR> <TD> %s </TD> <TD> %02d/%02d/%04d %02d:00 </TD> <TD> %s </TD> <TD> %s </TD> <TD> %02d:%02d </TD> <TD> %d </TD> <TD> %d </TD> <TD> %d </TD> <TD> %d </TD> <TD> %s </TD> <TD> %s </TD> </TR>\n",
                rotas->codigo_rota,
                rotas->data_hora_partida.dia,
                rotas->data_hora_partida.mes,
                rotas->data_hora_partida.ano,
                rotas->data_hora_partida.hora,
                rotas->origem,
                rotas->destino,
                rotas->estimativa_voo.horas_estimada,
                rotas->estimativa_voo.minutos_estimados,
                rotas->combustivel,
                rotas->qtd_passageiros,
                rotas->qtd_carga,
                rotas->qtd_tripulacao,
                rotas->membros_tripulacao,
                rotas->aeronave_alocada);
        rotas = rotas->prox;
    }
    fprintf(file, "</TABLE> </BODY> </HTML>\n");
    fclose(file);
} 

