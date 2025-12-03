#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../include/types.h"
#include "../include/funcao_base.h"

// ----------------------------------- REMOÇÕES -----------------------------------

void remover_aeronave_por_matricula(const string matricula, dados_aeronaves_t **lista)
{
    dados_aeronaves_t *atual = *lista;
    dados_aeronaves_t *anterior = NULL;

    while (atual != NULL && strcmp(atual->matricula, matricula) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Aeronave com matrícula '%s' não encontrada.\n", matricula);
        return;
    }

    if (anterior == NULL) {
        *lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);

    // printf("Aeronave com matrícula '%s' removida com sucesso.\n", matricula); Botar na main
}

void remover_rota_por_codigo(const string codigo_rota, dados_cia_t **lista)
{
    dados_cia_t *atual = *lista;
    dados_cia_t *anterior = NULL;

    while (atual != NULL && strcmp(atual->codigo_rota, codigo_rota) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Rota com código '%s' não encontrada.\n", codigo_rota);
        return;
    }

    if (anterior == NULL) {
        *lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    // printf("Rota com código '%s' removida com sucesso.\n", codigo_rota); Botar na main
}