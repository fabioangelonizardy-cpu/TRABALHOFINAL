#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "./include/types.h"
#include "./include/funcao_base.h"

// ----------------------------------- EXPORTAR PARA ARQUIVO DE TEXTO -----------------------------------
void exportar_aeronaves_arquivo_texto(const string nome_arquivo, dados_aeronaves_t *lista)
{
    FILE *fp_arquivo = NULL;

    fp_arquivo = fopen(nome_arquivo, "w");
    if (fp_arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    while (lista) {
        fprintf(fp_arquivo, "Identificação da aeronave: %s\n", lista->identificacao);
        fprintf(fp_arquivo, "Modelo da aeronave: %s\n", lista->modelo);
        fprintf(fp_arquivo, "Fabricante da aeronave: %s\n", lista->fabricante);
        fprintf(fp_arquivo, "Matrícula da aeronave: %s\n", lista->matricula);
        fprintf(fp_arquivo, "Ano de fabricação: %d\n", lista->ano_fabricacao);
        fprintf(fp_arquivo, "Tipo de aeronave: %d\n", lista->tipo);
        fprintf(fp_arquivo, "Situação da aeronave: %d\n", lista->situacao);
        fprintf(fp_arquivo, "Número de passageiros: %d\n", lista->n_passageiros);
        fprintf(fp_arquivo, "Número de pilotos: %d\n", lista->tripulacao.n_pilotos);
        fprintf(fp_arquivo, "Número de co-pilotos: %d\n", lista->tripulacao.n_co_pilotos);
        fprintf(fp_arquivo, "Número de comissários: %d\n", lista->tripulacao.n_comissarios);
        fprintf(fp_arquivo, "\n");
        lista = lista->prox;

        //Podia fazer o modelinho dado em aula, mas pra ficar igual ao rotas (Que não tem função), deixei assim mesmo
    }

    fclose(fp_arquivo);


}
void exportar_rotas_arquivo_texto(const string nome_arquivo, dados_cia_t *lista)
{
    FILE *fp_arquivo = NULL;

    fp_arquivo = fopen(nome_arquivo, "w");
    if (fp_arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    while (lista) {
        fprintf(fp_arquivo, "Código da rota: %s\n", lista->codigo_rota);
        fprintf(fp_arquivo, "Data e hora de partida: %02d/%02d/%04d %02d:00\n",
                lista->data_hora_partida.dia, lista->data_hora_partida.mes,
                lista->data_hora_partida.ano, lista->data_hora_partida.hora);
        fprintf(fp_arquivo, "Origem: %s\n", lista->origem);
        fprintf(fp_arquivo, "Destino: %s\n", lista->destino);
        fprintf(fp_arquivo, "Estimativa de voo: %d horas e %d minutos\n",
                lista->estimativa_voo.horas_estimada, lista->estimativa_voo.minutos_estimados);
        fprintf(fp_arquivo, "Combustível: %d litros\n", lista->combustivel);
        fprintf(fp_arquivo, "Quantidade de passageiros: %d\n", lista->qtd_passageiros);
        fprintf(fp_arquivo, "Quantidade de carga: %d kg\n", lista->qtd_carga);
        fprintf(fp_arquivo, "Membros da tripulação: %s\n", lista->membros_tripulacao);
        fprintf(fp_arquivo, "Aeronave alocada: %s\n", lista->aeronave_alocada);
        fprintf(fp_arquivo, "\n");
        lista = lista->prox;
    }

    fclose(fp_arquivo);

}

void exportar_aeronaves_arquivo_texto_binario(const string nome_arquivo, dados_aeronaves_t *lista)
{
    FILE *fp_arquivo = NULL;

    fp_arquivo = fopen(nome_arquivo, "wb");
    if (fp_arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    while (lista) {
        fwrite(lista, sizeof(dados_aeronaves_t), 1, fp_arquivo);
        lista = lista->prox;
    }

    fclose(fp_arquivo);
}
void exportar_rotas_arquivo_texto_binario(const string nome_arquivo, dados_cia_t *lista)
{
    FILE *fp_arquivo = NULL;

    fp_arquivo = fopen(nome_arquivo, "wb");
    if (fp_arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    while (lista) {
        fwrite(lista, sizeof(dados_cia_t), 1, fp_arquivo);
        lista = lista->prox;
    }

    fclose(fp_arquivo);
}
