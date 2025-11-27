#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "./include/types.h"
#include "./include/funcao_base.h"

// ----------------------------------- CADASTRO DE ROTAS -----------------------------------

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
    // Repetir enquanto a aeronave NÃO existir
    while (busca_aeronave_por_matricula(rota->aeronave_alocada, base_aeronaves) == NULL) {
        printf("Aeronave com matrícula '%s' não encontrada.\n", rota->aeronave_alocada);
        printf("Digite novamente uma matrícula válida: ");
        fgets(rota->aeronave_alocada, STR_SIZE, stdin);
        nova_linha(rota->aeronave_alocada);
    }
    rota->prox = NULL;

    return rota;
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

void mostrar_membros_tripulacao_rota(const string codigo_rota, dados_cia_t *lista)
{
    if (lista == NULL) {
        printf("Nenhuma rota cadastrada.\n");
        return;
    }

    for (dados_cia_t *r = lista; r != NULL; r = r->prox) {
        if (strcmp(r->codigo_rota, codigo_rota) == 0) {
            printf("Rota %s - Membros da tripulação: %s\n", r->codigo_rota, r->membros_tripulacao);
            // também mostramos os dados da aeronave alocada, se existir
            dados_aeronaves_t *certificando = busca_aeronave_por_matricula(r->aeronave_alocada, base_aeronaves);
            if (certificando != NULL) {
                mostrar_membros_tripulacao(certificando);
            } else {
                printf("Aeronave alocada '%s' não encontrada na base.\n", r->aeronave_alocada);
            }
            return;
        }
    }

    printf("Rota com código '%s' não encontrada.\n", codigo_rota);
}


