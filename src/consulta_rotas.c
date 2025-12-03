#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "../include/types.h"
#include "../include/funcao_base.h"

// ----------------------------------- CADASTRO DE ROTAS -----------------------------------

dados_aeronaves_t *base_aeronaves = NULL;
dados_cia_t *base_rotas = NULL;

void inicializar_base_rotas(struct base_rotas *rotas)
{
    rotas->inicio = NULL;
    rotas->fim = NULL;
    rotas->contador = 0;
}

void inserir_rota(dados_cia_t **lista, dados_cia_t *nova)
{
    if (*lista == NULL) {
        *lista = nova;
    } else {
        dados_cia_t *atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = nova;
    }
}

dados_cia_t *cadastrar_nova_rota()
{
    dados_cia_t *rota = (dados_cia_t *)malloc(sizeof(dados_cia_t));
    if (rota == NULL) {
        printf("Erro ao alocar memória para nova rota.\n");
        return NULL;
    }

    printf("Código da rota: ");
    fgets(rota->codigo_rota, STR_SIZE, stdin);
    nova_linha(rota->codigo_rota);

    printf("Data e hora de partida (dd/mm/aaaa/hh): ");
    scanf("%d/%d/%d/%d", &rota->data_hora_partida.dia, &rota->data_hora_partida.mes,
        &rota->data_hora_partida.ano, &rota->data_hora_partida.hora);
    clear_input();

    printf("Origem: ");
    fgets(rota->origem, STR_SIZE, stdin);
    nova_linha(rota->origem);

    printf("Destino: ");
    fgets(rota->destino, STR_SIZE, stdin);
    nova_linha(rota->destino);

    printf("Estimativa de voo (horas minutos): ");
    scanf("%d %d", &rota->estimativa_voo.horas_estimada, &rota->estimativa_voo.minutos_estimados);
    clear_input();

    printf("Combustível (litros): ");
    scanf("%d", &rota->combustivel);
    clear_input();

    printf("Quantidade de passageiros: ");
    scanf("%d", &rota->qtd_passageiros);
    clear_input();

    printf("Quantidade de carga (kg): ");
    scanf("%d", &rota->qtd_carga);
    clear_input();

    printf("Quantidade de tripulação: ");
    scanf("%d", &rota->qtd_tripulacao);
    clear_input();

    // Agora escreve os membros da tripulação por quantidade
    // garantir string vazia antes de concatenar
    rota->membros_tripulacao[0] = '\0';
    for (int i = 0; i < rota->qtd_tripulacao; i++) {
        char membro[STR_SIZE];
        printf("Membro da tripulação %d: ", i + 1);
        fgets(membro, STR_SIZE, stdin);
        nova_linha(membro);
        strcat(rota->membros_tripulacao, membro);
        if (i < rota->qtd_tripulacao - 1) {
            strcat(rota->membros_tripulacao, ", ");
        }
    }

    //Agora não irei permitir que a aeronave alocada seja inválida!!!!

    printf("Aeronave alocada (matrícula): ");
    fgets(rota->aeronave_alocada, STR_SIZE, stdin);
    nova_linha(rota->aeronave_alocada);
    if (strlen(rota->aeronave_alocada) == 0) {
        printf("Aeronave alocada não pode ser vazia. Rota não cadastrada.\n");
        free(rota);
        return NULL;
    }
    rota->prox = NULL;

    return rota;
}

void relatorio_rotas_cadastradas(dados_cia_t *lista)
{
    while (lista != NULL) {
        printf("Código da rota: %s\n", lista->codigo_rota);
        printf("Data e hora de partida: %02d/%02d/%04d %02d:00\n", lista->data_hora_partida.dia,
               lista->data_hora_partida.mes, lista->data_hora_partida.ano, lista->data_hora_partida.hora);
        printf("Origem: %s\n", lista->origem);
        printf("Destino: %s\n", lista->destino);
        printf("Estimativa de voo: %d horas e %d minutos\n", lista->estimativa_voo.horas_estimada,
               lista->estimativa_voo.minutos_estimados);
        printf("Combustível: %d litros\n", lista->combustivel);
        printf("Quantidade de passageiros: %d\n", lista->qtd_passageiros);
        printf("Quantidade de carga: %d kg\n", lista->qtd_carga);
        printf("Quantidade de tripulação: %d\n", lista->qtd_tripulacao);
        printf("Membros da tripulação: %s\n", lista->membros_tripulacao);
        printf("Aeronave alocada (matrícula): %s\n", lista->aeronave_alocada);
        printf("\n");
        lista = lista->prox;
    }
}

    int consultar_rota_por_data(data_hora_t data, dados_cia_t *base) {
    dados_cia_t *atual = base;
    int encontrado = 0;
    while (atual != NULL) {
        if (atual->data_hora_partida.dia == data.dia &&
            atual->data_hora_partida.mes == data.mes &&
            atual->data_hora_partida.ano == data.ano) {
            printf("Código da rota: %s\n", atual->codigo_rota);
            printf("Data e hora de partida: %02d/%02d/%04d %02d:00\n", atual->data_hora_partida.dia,
                   atual->data_hora_partida.mes, atual->data_hora_partida.ano, atual->data_hora_partida.hora);
            printf("Origem: %s\n", atual->origem);
            printf("Destino: %s\n", atual->destino);
            printf("Estimativa de voo: %d horas e %d minutos\n", atual->estimativa_voo.horas_estimada,
                   atual->estimativa_voo.minutos_estimados);
            printf("Combustível: %d litros\n", atual->combustivel);
            printf("Quantidade de passageiros: %d\n", atual->qtd_passageiros);
            printf("Quantidade de carga: %d kg\n", atual->qtd_carga);
            printf("Quantidade de tripulação: %d\n", atual->qtd_tripulacao);
            printf("Membros da tripulação: %s\n", atual->membros_tripulacao);
            printf("Aeronave alocada (matrícula): %s\n", atual->aeronave_alocada);
            printf("\n");
            encontrado++;
        }
        atual = atual->prox;
    }
    return encontrado;
}

void listar_rotas_por_origem(const string origem, dados_cia_t *lista)
{
    while (lista != NULL) {
        if (strcmp(lista->origem, origem) == 0) {
            printf("Código da rota: %s\n", lista->codigo_rota);
            printf("Data e hora de partida: %02d/%02d/%04d %02d:00\n", lista->data_hora_partida.dia,
                   lista->data_hora_partida.mes, lista->data_hora_partida.ano, lista->data_hora_partida.hora);
            printf("Origem: %s\n", lista->origem);
            printf("Destino: %s\n", lista->destino);
            printf("Estimativa de voo: %d horas e %d minutos\n", lista->estimativa_voo.horas_estimada,
                   lista->estimativa_voo.minutos_estimados);
            printf("Combustível: %d litros\n", lista->combustivel);
            printf("Quantidade de passageiros: %d\n", lista->qtd_passageiros);
            printf("Quantidade de carga: %d kg\n", lista->qtd_carga);
            printf("Quantidade de tripulação: %d\n", lista->qtd_tripulacao);
            printf("Membros da tripulação: %s\n", lista->membros_tripulacao);
            printf("Aeronave alocada (matrícula): %s\n", lista->aeronave_alocada);
            printf("\n");
        }
        lista = lista->prox;

    }
}

void listar_rotas_por_destino(const string destino, dados_cia_t *lista)
{
    while (lista != NULL) {
        if (strcmp(lista->destino, destino) == 0) {
            printf("Código da rota: %s\n", lista->codigo_rota);
            printf("Data e hora de partida: %02d/%02d/%04d %02d:00\n", lista->data_hora_partida.dia,
                   lista->data_hora_partida.mes, lista->data_hora_partida.ano, lista->data_hora_partida.hora);
            printf("Origem: %s\n", lista->origem);
            printf("Destino: %s\n", lista->destino);
            printf("Estimativa de voo: %d horas e %d minutos\n", lista->estimativa_voo.horas_estimada,
                   lista->estimativa_voo.minutos_estimados);
            printf("Combustível: %d litros\n", lista->combustivel);
            printf("Quantidade de passageiros: %d\n", lista->qtd_passageiros);
            printf("Quantidade de carga: %d kg\n", lista->qtd_carga);
            printf("Quantidade de tripulação: %d\n", lista->qtd_tripulacao);
            printf("Membros da tripulação: %s\n", lista->membros_tripulacao);
            printf("Aeronave alocada (matrícula): %s\n", lista->aeronave_alocada);
            printf("\n");
        }
        lista = lista->prox;
    }
}
void percentual_voos_realizados_destino(const string destino, dados_cia_t *lista, dados_aeronaves_t *aeronaves)
{
    int total_rotas = 0;
    int rotas_para_destino = 0;

    for (dados_cia_t *r = lista; r != NULL; r = r->prox) {
        total_rotas++;
        if (strcmp(r->destino, destino) == 0) {
            rotas_para_destino++;
        }
    }

    if (total_rotas == 0) {
        printf("Nenhuma rota cadastrada.\n");
        return;
    }

    double percentual = ((double)rotas_para_destino / total_rotas) * 100.0;
    printf("Percentual de voos realizados para o destino '%s': %.2f%%\n", destino, percentual);
}

int consumo_combustivel_intervalo_datas(data_hora_t data_inicio, data_hora_t data_fim, dados_cia_t *lista)
{
    int total_combustivel = 0;
    while (lista != NULL) {
        if (date_in_range(lista->data_hora_partida, data_inicio, data_fim)) {
            total_combustivel += lista->combustivel;
        }
        lista = lista->prox;
    }
    return total_combustivel;
}

