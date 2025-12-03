#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../include/types.h"
#include "../include/funcao_base.h"
#include "../include/aeronaves_lista.h"

// ----------------------------------- CADASTRO DE AERONAVES -----------------------------------

void inicializar_base_aeronaves(struct base_aeronaves *aeronaves)
{
    aeronaves->inicio = NULL;
    aeronaves->fim = NULL;
    aeronaves->contador = 0;

}

void inserir_aeronave(dados_aeronaves_t **lista, dados_aeronaves_t *nova)
{
    if (*lista == NULL) {
        *lista = nova;
    } else {
        dados_aeronaves_t *atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = nova;
    }
}

dados_aeronaves_t *cadastrar_nova_aeronave()
{
    dados_aeronaves_t *nova = (dados_aeronaves_t *)malloc(sizeof(dados_aeronaves_t));
    if (nova == NULL) {
        printf("Erro ao alocar memória para nova aeronave.\n");
        return NULL;
    }

    printf("Identificação da aeronave: ");
    fgets(nova->identificacao, STR_SIZE, stdin);
    nova_linha(nova->identificacao);
    formatar_maiusculo(nova->identificacao);

    printf("Modelo da aeronave: ");
    fgets(nova->modelo, STR_SIZE, stdin);
    nova_linha(nova->modelo);
    formatar_maiusculo(nova->modelo);

    printf("Fabricante da aeronave: ");
    fgets(nova->fabricante, STR_SIZE, stdin);
    nova_linha(nova->fabricante);
    formatar_maiusculo(nova->fabricante);

    printf("Matrícula da aeronave: ");
    fgets(nova->matricula, STR_SIZE, stdin);
    nova_linha(nova->matricula);

    printf("Ano de fabricação: ");
    scanf("%d", &nova->ano_fabricacao);
    clear_input();

    int tipo_input;
    printf("Tipo de aeronave (1 - Carga, 2 - Passageiro): ");
    scanf("%d", &tipo_input);
    clear_input();
    nova->tipo = (tipo_input == 1) ? CARGA : PASSAGEIRO;

    printf("Número de passageiros: ");
    scanf("%d", &nova->n_passageiros);
    clear_input();

    int situacao_input;
    printf("Situação da aeronave (1 - Operação, 2 - Manutenção): ");
    scanf("%d", &situacao_input);
    clear_input();
    nova->situacao = (situacao_input == 1) ? OPERACAO : MANUTENCAO;

    // Inicializar tripulação
    nova->tripulacao.n_pilotos = 0;
    nova->tripulacao.n_co_pilotos = 0;
    nova->tripulacao.n_comissarios = 0;

    // Inicializar registros de manutenção
    nova->n_manutencoes = 0;
    for (int i = 0; i < MAX_MANUTENCOES; i++) {
        nova->manutencoes[i] = '\0';
    }

    nova->prox = NULL;

    return nova;
}

void relatorio_aeronaves_cadastradas(dados_aeronaves_t *lista)
{
    while (lista != NULL) {
        printf("Identificação da aeronave: %s\n", lista->identificacao);
        printf("Modelo da aeronave: %s\n", lista->modelo);
        printf("Fabricante da aeronave: %s\n", lista->fabricante);
        printf("Matrícula da aeronave: %s\n", lista->matricula);
        printf("Ano de fabricação: %d\n", lista->ano_fabricacao);
        printf("Tipo de aeronave: %d\n", lista->tipo);
        printf("Situação da aeronave: %d\n", lista->situacao);
        printf("Número de passageiros: %d\n", lista->n_passageiros);
        printf("\n");
        lista = lista->prox;
    }
}


dados_aeronaves_t *busca_aeronave_por_matricula(const char *matricula, dados_aeronaves_t *lista)
{
    while (lista != NULL) {
        if (strcmp(lista->matricula, matricula) == 0) {
            return lista;
        }
        lista = lista->prox;
    }
    return NULL;
}