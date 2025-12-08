#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "../include/types.h"
#include "../include/funcao_base.h"
#include "../include/aeronaves_lista.h"

// ----------------------------------- CADASTRO DE ROTAS -----------------------------------

void inicializar_base_rotas(struct base_rotas *rotas)
{
    rotas->inicio = NULL;
    rotas->fim = NULL;
    rotas->contador = 0;
}

void inserir_rota_base_dados(struct base_rotas *rotas, dados_cia_t *rota, int modo)
{
    rota->prox = NULL;

    if (rotas->inicio == NULL) {
        rotas->fim = rota;
        rotas->inicio = rota;
        return;
    }

    if(modo == 1) { //Inicio
        rota->prox = rotas->inicio;
        rotas->inicio = rota;

    } else if(modo == 2) { //Fim
        rotas->fim->prox = rota;
        rotas->fim = rota;
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
    formatar_maiusculo(rota->codigo_rota);

    printf("Data e hora de partida (dd/mm/aaaa/hh): ");
    scanf("%d/%d/%d/%d", &rota->data_hora_partida.dia, &rota->data_hora_partida.mes,
        &rota->data_hora_partida.ano, &rota->data_hora_partida.hora);
    clear_input();

    printf("Origem: ");
    fgets(rota->origem, STR_SIZE, stdin);
    nova_linha(rota->origem);
    formatar_maiusculo(rota->origem);

    printf("Destino: ");
    fgets(rota->destino, STR_SIZE, stdin);
    nova_linha(rota->destino);
    formatar_maiusculo(rota->destino);

    printf("Estimativa de voo (hh:mm): ");
    scanf("%d:%d", &rota->estimativa_voo.horas_estimada, &rota->estimativa_voo.minutos_estimados);
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
    if(busca_aeronave_por_matricula(rota->aeronave_alocada, base_aeronaves) == NULL) {
        printf("Aeronave com matrícula '%s' não encontrada. Rota não cadastrada.\n", rota->aeronave_alocada);
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

    double percentual = ((double)rotas_para_destino / total_rotas) * 100.0; //doublezinho pra transformar em float
    printf("Percentual de voos realizados para o destino '%s': %.2f%%\n", destino, percentual);
}

int consumo_combustivel_intervalo_datas(data_hora_t data_inicio, data_hora_t data_fim, dados_cia_t *lista)
{
    int consumo_total = 0;
    while (lista != NULL) {
        bool dentro_intervalo = false;

        if (lista->data_hora_partida.ano > data_inicio.ano &&
            lista->data_hora_partida.ano < data_fim.ano) {
            dentro_intervalo = true;
        } else if (lista->data_hora_partida.ano == data_inicio.ano) {
            if (lista->data_hora_partida.mes > data_inicio.mes ||
                (lista->data_hora_partida.mes == data_inicio.mes &&
                 lista->data_hora_partida.dia >= data_inicio.dia)) {
                dentro_intervalo = true;
            }
        } else if (lista->data_hora_partida.ano == data_fim.ano) {
            if (lista->data_hora_partida.mes < data_fim.mes ||
                (lista->data_hora_partida.mes == data_fim.mes &&
                 lista->data_hora_partida.dia <= data_fim.dia)) {
                dentro_intervalo = true;
            }
        }

        if (dentro_intervalo) {
            consumo_total += lista->combustivel;
        }

        lista = lista->prox;
    }
    printf("Consumo total de combustível entre %02d/%02d/%04d e %02d/%02d/%04d: %d litros\n",
           data_inicio.dia, data_inicio.mes, data_inicio.ano,
           data_fim.dia, data_fim.mes, data_fim.ano,
           consumo_total);
    return consumo_total;
}

void listar_rota_maior_numero_passageiros(dados_cia_t *lista)
{
    dados_cia_t *maior_rota = lista;
    if(lista == NULL) {
        printf("Nenhuma rota cadastrada.\n");
        return;
    }
    while (lista != NULL) {
        if (lista->qtd_passageiros > maior_rota->qtd_passageiros) {
            maior_rota = lista;
        }
        lista = lista->prox;
    }
    printf("Rota com maior número de passageiros:\n");
    printf("Código da rota: %s\n", maior_rota->codigo_rota);
    printf("Data e hora de partida: %02d/%02d/%04d %02d:00\n", maior_rota->data_hora_partida.dia,
           maior_rota->data_hora_partida.mes, maior_rota->data_hora_partida.ano, maior_rota->data_hora_partida.hora);
    printf("Origem: %s\n", maior_rota->origem);
    printf("Destino: %s\n", maior_rota->destino);
    printf("Estimativa de voo: %d horas e %d minutos\n", maior_rota->estimativa_voo.horas_estimada,
           maior_rota->estimativa_voo.minutos_estimados);
    printf("Combustível: %d litros\n", maior_rota->combustivel);
    printf("Quantidade de passageiros: %d\n", maior_rota->qtd_passageiros);
    printf("Quantidade de carga: %d kg\n", maior_rota->qtd_carga);
    printf("Quantidade de tripulação: %d\n", maior_rota->qtd_tripulacao);
    printf("Membros da tripulação: %s\n", maior_rota->membros_tripulacao);
    printf("Aeronave alocada (matrícula): %s\n", maior_rota->aeronave_alocada);


}
void listar_rota_menor_numero_passageiros(dados_cia_t *lista)
{
    dados_cia_t *menor_rota = lista;
    if(lista == NULL) {
        printf("Nenhuma rota cadastrada.\n");
        return;
    }
    while (lista != NULL) {
        if (lista->qtd_passageiros < menor_rota->qtd_passageiros) {
            menor_rota = lista;
        }
        lista = lista->prox;
    }
    printf("Rota com menor número de passageiros:\n");
    printf("Código da rota: %s\n", menor_rota->codigo_rota);
    printf("Data e hora de partida: %02d/%02d/%04d %02d:00\n", menor_rota->data_hora_partida.dia,
           menor_rota->data_hora_partida.mes, menor_rota->data_hora_partida.ano, menor_rota->data_hora_partida.hora);
    printf("Origem: %s\n", menor_rota->origem);
    printf("Destino: %s\n", menor_rota->destino);
    printf("Estimativa de voo: %d horas e %d minutos\n", menor_rota->estimativa_voo.horas_estimada,
           menor_rota->estimativa_voo.minutos_estimados);
    printf("Combustível: %d litros\n", menor_rota->combustivel);
    printf("Quantidade de passageiros: %d\n", menor_rota->qtd_passageiros);
    printf("Quantidade de carga: %d kg\n", menor_rota->qtd_carga);
    printf("Quantidade de tripulação: %d\n", menor_rota->qtd_tripulacao);
    printf("Membros da tripulação: %s\n", menor_rota->membros_tripulacao);
    printf("Aeronave alocada (matrícula): %s\n", menor_rota->aeronave_alocada);

}

