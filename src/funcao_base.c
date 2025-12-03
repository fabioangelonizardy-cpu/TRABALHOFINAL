#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../include/types.h"
#include "../include/funcao_base.h"

//----------------------------------- FUNÇÕES BASE -----------------------------------
/*
int menu(){
    int opc;

    printf("\n=== MENU PRINCIPAL ===\n");

    printf("\n");

    printf("------------- Cadastro de aeronaves -----------------\n");
    printf("1 - Cadastrar nova aeronave\n");
    printf("2 - Relatório de aeronaves cadastradas\n");      
    printf("3 - Remover aeronave por matrícula\n");       
    printf("4 - Alterar situação de uma aeronave\n");    
    printf("5 - Manutenções de uma aeronave\n");     
    printf("6 - Percentual de voos realizados por aeronave\n");    
    printf("7 - Consumo de combustível total em um intervalo de datas\n");   

    printf("\n");

    printf("------------- Cadastro de rotas ---------------------\n");    
    printf("8 - Cadastrar nova rota\n");    
    printf("9 - Remover rota por código\n");
    printf("10 - Consultar rota por data\n");    
    printf("11 - Mostrar membros da tripulação de uma rota\n");

    printf("\n");

    printf("------------- Filtros de aeronaves -------------------\n");    
    printf("12 - Listar aeronaves por fabricante\n");
    printf("13 - Listar aeronaves por tipo de avião;\n");
    printf("14 - Listar aeronaves por modelo\n");
    printf("15 - Listar aeronaves por ano de fabricação\n");
    printf("16 - Listar aeronaves por situação\n");

    printf("\n");

    printf("------------- Consultas de rotas ---------------------\n");    
    printf("17 - Listar rotas por destino\n");
    printf("18 - Listar rotas por origem\n");    
    printf("19 - Percentual de voos para um determinado destino em um intervalo de datas\n");
    printf("20 - Listar rotas com maior número de passageiros\n");
    printf("21 - Listar rotas com menor número de passageiros\n");

    printf("\n");

    printf("------------- Gerar arquivos  ------------------------\n");
    printf("22 - Exportar aeronaves\n");
    printf("23 - Exportar rotas\n");
    printf("24 - Exportar aeronaves (Binário)\n");
    printf("25 - Exportar rotas (Binário)\n");

    printf("\n");

    printf("0 - Sair do programa\n");
    if (scanf("%d", &opc) != 1) {
        clear_input();
        return -1;
    }
    clear_input();
    return opc;
    
}
    */

int menu()
{
    int opc;
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1 - Submenu Aeronaves\n");
    printf("2 - Submenu Rotas\n");
    printf("3 - Submenu Filtros\n");
    printf("4 - Submenu Consulta de Rotas\n");
    printf("5 - Submenu Arquivos\n");
    printf("0 - Sair do programa\n");
    if (scanf("%d", &opc) != 1) {
        clear_input();
        return -1;
    }
    clear_input();
    return opc;
}

int sub_menu_aeronaves()
{
    int opc;
    printf("------------- Cadastro de aeronaves -----------------\n");
    printf("1 - Cadastrar nova aeronave\n");
    printf("2 - Relatório de aeronaves cadastradas\n");      
    printf("3 - Remover aeronave por matrícula\n");       
    printf("4 - Alterar situação de uma aeronave\n");    
    printf("5 - Manutenções de uma aeronave\n");     
    printf("6 - Percentual de voos realizados por aeronave\n");    
    printf("7 - Consumo de combustível total em um intervalo de datas\n"); 
    if (scanf("%d", &opc) != 1) {
        clear_input();
        return -1;
    }
    clear_input();
    return opc;
}

int sub_menu_rotas()
{
    int opc;
    printf("------------- Cadastro de rotas ---------------------\n");    
    printf("1 - Cadastrar nova rota\n");    
    printf("2 - Relatório de rotas cadastradas\n");
    printf("3 - Remover rota por código\n");
    printf("4 - Consultar rota por data\n");
    if (scanf("%d", &opc) != 1) {
        clear_input();
        return -1;
    }
    clear_input();
    return opc;

}
int sub_menu_filtros()
{
    int opc;
    printf("------------- Filtros de aeronaves -------------------\n");    
    printf("1 - Listar aeronaves por fabricante\n");
    printf("2 - Listar aeronaves por tipo de avião;\n");
    printf("3 - Listar aeronaves por modelo\n");
    printf("4 - Listar aeronaves por ano de fabricação\n");
    printf("5 - Listar aeronaves por situação\n");
    if (scanf("%d", &opc) != 1) {
        clear_input();
        return -1;
    }
    clear_input();
    return opc;

}
int sub_menu_consulta_rotas()
{
    int opc;
    printf("------------- Consultas de rotas ---------------------\n");    
    printf("1 - Listar rotas por destino\n");
    printf("2 - Listar rotas por origem\n");    
    printf("3 - Percentual de voos para um determinado destino em um intervalo de datas\n");
    printf("4 - Listar rotas com maior número de passageiros\n");
    printf("5 - Listar rotas com menor número de passageiros\n");
    if (scanf("%d", &opc) != 1) {
        clear_input();
        return -1;
    }
    clear_input();
    return opc;

}
int sub_menu_arquivos()
{
    int opc;
    printf("------------- Gerar arquivos  ------------------------\n");
    printf("1 - Exportar aeronaves (Binário)\n");
    printf("2 - Exportar rotas (Binário)\n");
    printf("3 - Importar aeronaves (.txt)\n");
    printf("4 - Importar rotas (.txt)\n");
    printf("5 - Exportar aeronaves (.csv)\n");
    printf("6 - Exportar rotas (.csv)\n");
    printf("7 - Exportar aeronaves (.html)\n");
    printf("8 - Exportar rotas (.html)\n");
    if (scanf("%d", &opc) != 1) {
        clear_input();
        return -1;
    }
    clear_input();
    return opc;

}

int sub_menu_relatorios_arquivos()
{
    int opc;
    printf("------------- Relatórios em arquivos  ------------------------\n");
    printf("1 - Relatório de aeronaves cadastradas (Sem formatação))\n");
    printf("2 - Relatório de rotas cadastradas (Sem formatação)\n");
    printf("3 - Relatório de aeronaves cadastradas (CSV)\n");
    printf("4 - Relatório de rotas cadastradas (CSV)\n");
    printf("5 - Relatório de aeronaves cadastradas (HTML)\n");
    printf("6 - Relatório de rotas cadastradas (HTML)\n");
    if (scanf("%d", &opc) != 1) {
        clear_input();
        return -1;
    }
    clear_input();
    return opc;

}

void clear_input(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}
void nova_linha(string str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

bool date_in_range(data_hora_t d, data_hora_t start, data_hora_t end)
{
    // Comparar anos
    if (d.ano < start.ano || d.ano > end.ano) {
        return false;
    }
    // Comparar meses
    if (d.ano == start.ano && d.mes < start.mes) {
        return false;
    }
    if (d.ano == end.ano && d.mes > end.mes) {
        return false;
    }
    // Comparar dias
    if (d.ano == start.ano && d.mes == start.mes && d.dia < start.dia) {
        return false;
    }
    if (d.ano == end.ano && d.mes == end.mes && d.dia > end.dia) {
        return false;
    }
    return true;
}

void formatar_maiusculo(char* str)
{
    for (int i = 0; str[i]; i++) {
        *(str+i) = toupper((unsigned char)*(str+i));
    }
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