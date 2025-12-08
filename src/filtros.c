#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../include/types.h"
#include "../include/funcao_base.h"
#include "../include/aeronaves_lista.h"

// ----------------------------------- FILTROS AERONAVES -----------------------------------

dados_aeronaves_t *base_aeronaves = NULL;
dados_cia_t *base_rotas = NULL;

void listar_aeronaves_por_fabricante(const string fabricante, dados_aeronaves_t *lista)
{
    while (lista != NULL) {
        if (strcmp(lista->fabricante, fabricante) == 0) {
            printf("Identificação da aeronave: %s\n", lista->identificacao);
            printf("Modelo da aeronave: %s\n", lista->modelo);
            printf("Matrícula da aeronave: %s\n", lista->matricula);
            printf("Ano de fabricação: %d\n", lista->ano_fabricacao);
            printf("Tipo de aeronave: %d\n", lista->tipo);
            printf("Situação da aeronave: %d\n", lista->situacao);
            printf("Número de passageiros: %d\n", lista->n_passageiros);
            printf("\n");
        }
        lista = lista->prox;
    }
}
void listar_aeronaves_por_modelo(const string modelo, dados_aeronaves_t *lista){
    while (lista != NULL) {
        if (strcmp(lista->modelo, modelo) == 0) {
            printf("Identificação da aeronave: %s\n", lista->identificacao);
            printf("Fabricante da aeronave: %s\n", lista->fabricante);
            printf("Matrícula da aeronave: %s\n", lista->matricula);
            printf("Ano de fabricação: %d\n", lista->ano_fabricacao);
            printf("Tipo de aeronave: %d\n", lista->tipo);
            printf("Situação da aeronave: %d\n", lista->situacao);
            printf("Número de passageiros: %d\n", lista->n_passageiros);
            printf("\n");
        }
        lista = lista->prox;
    }
}
void listar_aeronaves_por_tipo(tipo_t tipo, dados_aeronaves_t *lista){
    while (lista != NULL) {
        if (lista->tipo == tipo) {
            printf("Identificação da aeronave: %s\n", lista->identificacao);
            printf("Modelo da aeronave: %s\n", lista->modelo);
            printf("Fabricante da aeronave: %s\n", lista->fabricante);
            printf("Matrícula da aeronave: %s\n", lista->matricula);
            printf("Ano de fabricação: %d\n", lista->ano_fabricacao);
            printf("Situação da aeronave: %d\n", lista->situacao);
            printf("Número de passageiros: %d\n", lista->n_passageiros);
            printf("\n");
        }
        lista = lista->prox;
    }
}
void listar_aeronaves_por_ano_fabricacao(int ano, dados_aeronaves_t *lista)
{
    while (lista != NULL) {
        if (lista->ano_fabricacao == ano) {
            printf("Identificação da aeronave: %s\n", lista->identificacao);
            printf("Modelo da aeronave: %s\n", lista->modelo);
            printf("Fabricante da aeronave: %s\n", lista->fabricante);
            printf("Matrícula da aeronave: %s\n", lista->matricula);
            printf("Tipo de aeronave: %d\n", lista->tipo);
            printf("Situação da aeronave: %d\n", lista->situacao);
            printf("Número de passageiros: %d\n", lista->n_passageiros);
            printf("\n");
        }
        lista = lista->prox;
    }
}
void listar_aeronaves_por_situacao(situacao_t situacao, dados_aeronaves_t *lista)
{
    while (lista != NULL) {
        if (lista->situacao == situacao) {
            printf("Identificação da aeronave: %s\n", lista->identificacao);
            printf("Modelo da aeronave: %s\n", lista->modelo);
            printf("Fabricante da aeronave: %s\n", lista->fabricante);
            printf("Matrícula da aeronave: %s\n", lista->matricula);
            printf("Ano de fabricação: %d\n", lista->ano_fabricacao);
            printf("Tipo de aeronave: %d\n", lista->tipo);
            printf("Número de passageiros: %d\n", lista->n_passageiros);
            printf("\n");
        }
        lista = lista->prox;
    }
}
void alterar_situacao_aeronave(const string matricula, situacao_t nova_situacao, dados_aeronaves_t *lista)
{
    dados_aeronaves_t *aeronave = busca_aeronave_por_matricula(matricula, lista);
    if (aeronave != NULL) {
        aeronave->situacao = nova_situacao;
        printf("Situação da aeronave com matrícula '%s' alterada com sucesso.\n", matricula);
    } else {
        printf("Aeronave com matrícula '%s' não encontrada.\n", matricula);
    }
}

void manutencoes_aeronave(const string matricula, dados_aeronaves_t *lista)
{
    dados_aeronaves_t *aeronave = busca_aeronave_por_matricula(matricula, lista);
    if (aeronave != NULL) {
        printf("Manutenções da aeronave com matrícula '%s':\n", matricula);
        if (aeronave->n_manutencoes == 0) {
            printf("Nenhuma manutenção registrada.\n");
        } else {
            for (int i = 0; i < aeronave->n_manutencoes && i < MAX_MANUTENCOES; i++) {
                printf("- %i\n", aeronave->manutencoes[i]);
            }
        }
    } else {
        printf("Aeronave com matrícula '%s' não encontrada.\n", matricula);
    }
}

void percentual_voos_realizados(const string matricula, dados_aeronaves_t *lista)
{
    dados_aeronaves_t *aeronave = busca_aeronave_por_matricula(matricula, lista);
    if (aeronave == NULL) {
        printf("Aeronave com matrícula '%s' não encontrada.\n", matricula);
        return;
    }

    int total_rotas = 0;
    int rotas_da_aeronave = 0;

    for (dados_cia_t *r = base_rotas; r != NULL; r = r->prox) {
        total_rotas++;
        if (strcmp(r->aeronave_alocada, matricula) == 0) {
            rotas_da_aeronave++;
        }
    }

    if (total_rotas == 0) {
        printf("Nenhuma rota cadastrada.\n");
        return;
    }

    float percentual = (rotas_da_aeronave * 100.0f) / (float)total_rotas;
    printf("Aeronave com matrícula '%s' participou de %d de %d rotas (%.2f%%).\n",
           matricula, rotas_da_aeronave, total_rotas, percentual);
}
