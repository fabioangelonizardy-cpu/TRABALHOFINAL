#ifndef TYPES_H
#define TYPES_H

//Constantes
#define STR_SIZE 100
#define MAX_AVIAO 100
#define MAX_ROTAS 100
// máximo de registros de manutenção por aeronave
#define MAX_MANUTENCOES 20

//Tipos de dados
typedef char string[STR_SIZE];
typedef enum {CARGA = 1, PASSAGEIRO = 2} tipo_t;
typedef enum {OPERACAO = 1, MANUTENCAO = 2} situacao_t;

typedef struct data_hora
{
    int dia;
    int mes;
    int ano;
    int hora;
    struct data_hora *prox;

} data_hora_t;

typedef struct estimativa_voo
{
    int horas_estimada;
    int minutos_estimados;
    struct estimativa_voo *prox;

}  estimativa_voo_t;

typedef struct tripulacao
{
    int n_pilotos;
    int n_co_pilotos;
    int n_comissarios;
    struct tripulacao *prox;

} tripulacao_t;

typedef struct dados_aeronaves
{
    string identificacao;
    string modelo;
    string fabricante;
    string matricula;
    int ano_fabricacao;
    tipo_t tipo;
    int n_passageiros;
    int n_manutencoes;
    int manutencoes[MAX_MANUTENCOES];
    situacao_t situacao;
    tripulacao_t tripulacao;
    struct dados_aeronaves *prox;

} dados_aeronaves_t;

typedef struct dados_cia
{
    string codigo_rota;
    data_hora_t data_hora_partida;
    string origem;
    string destino;
    estimativa_voo_t estimativa_voo;
    int combustivel;
    int qtd_passageiros;
    int qtd_carga;
    int qtd_tripulacao;
    string membros_tripulacao;
    string aeronave_alocada;
    struct dados_cia *prox;

} dados_cia_t;

struct base_aeronaves {
    unsigned int contador;
    dados_aeronaves_t *inicio;
    dados_aeronaves_t *fim;
};

struct base_rotas {
    unsigned int contador;
    dados_cia_t *inicio;
    dados_cia_t *fim;
};

#endif