#include "./include/types.h"
#include "./include/funcao_base.h"
#include "./include/aeronaves_lista.h"
#include "./include/remocoes.h"
#include "./include/filtros.h"
#include "./include/consulta_rotas.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


//----------------------------------- VARIÁVEIS GLOBAIS -----------------------------------
dados_aeronaves_t *base_aeronaves = NULL;
dados_cia_t *base_rotas = NULL;


//----------------------------------- FUNÇÃO MAIN -----------------------------------

int main()
{
    int opc, ano, situacao, tipo;
    char confirma;
    string matricula, fabricante, modelo, destino, origem, nome_arquivo;
    data_hora_t data, data_inicio, data_fim;
    dados_aeronaves_t *aux = NULL;
    dados_cia_t *rota_aux = NULL;


    do{
        opc = menu();
        switch (opc){

            // ----------------------------------- CADASTRO DE AERONAVES -----------------------------------

            case 1:
                {
                    dados_aeronaves_t *nova_aeronave = cadastrar_nova_aeronave();
                    if (nova_aeronave != NULL) {
                        inserir_aeronave(&base_aeronaves, nova_aeronave);
                        printf("Aeronave com matrícula '%s' cadastrada com sucesso.\n", nova_aeronave->matricula); //NOTAS: Papercut - Linkin Park é pratimonio da humanidade
                    }
                }
                break;
            case 2:
                relatorio_aeronaves_cadastradas(base_aeronaves);
                break;

            case 3:

                printf("Digite a matrícula da aeronave a ser removida: ");
                fgets(matricula, STR_SIZE, stdin);
                nova_linha(matricula);
                printf("Certeza que deseja remover a aeronave com matrícula '%s'? (s/n): ", matricula);
                scanf(" %c", &confirma);
                clear_input();
                if (confirma == 's' || confirma == 'S') {
                aux = busca_aeronave_por_matricula(matricula, base_aeronaves);
                if (aux == NULL) {
                    printf("Aeronave com matrícula '%s' não encontrada.\n", matricula);
                } else {
                    remover_aeronave_por_matricula(matricula, &base_aeronaves);
                    printf("Aeronave com matrícula '%s' removida com sucesso.\n", matricula);
                }
                } else {
                    printf("Remoção cancelada.\n");
                }  //    Esse aqui até mandei pra minha mãe de orgulho (Apenas comentários necessários no projeto)
                break;

            case 4:
                printf("Digite a matrícula da aeronave para alterar a situação: ");
                fgets(matricula, STR_SIZE, stdin);
                nova_linha(matricula);
                printf("Digite a nova situação (1 - Operação, 2 - Manutenção): ");
                scanf("%d", &situacao);
                clear_input();
                alterar_situacao_aeronave(matricula, (situacao_t)situacao, base_aeronaves);
                break;

            case 5:
                
                    printf("Digite a matrícula da aeronave para ver as manutenções: ");
                    fgets(matricula, STR_SIZE, stdin);
                    nova_linha(matricula);
                    manutencoes_aeronave(matricula, base_aeronaves);
                
                break;

            case 6:
                printf("Digite a matrícula da aeronave para ver o percentual de voos realizados: ");
                fgets(matricula, STR_SIZE, stdin);
                nova_linha(matricula);
                percentual_voos_realizados(matricula, base_aeronaves);

                break;

            case 7:
                printf("Digite a data de início (dd/mm/aaaa): ");
                scanf("%d/%d/%d", &data_inicio.dia, &data_inicio.mes, &data_inicio.ano);
                clear_input();
                printf("Digite a data de fim (dd/mm/aaaa): ");
                scanf("%d/%d/%d", &data_fim.dia, &data_fim.mes, &data_fim.ano);
                clear_input();
                int total_combustivel = consumo_combustivel_intervalo_datas(data_inicio, data_fim, base_rotas);
                printf("Consumo total de combustível entre %02d/%02d/%04d e %02d/%02d/%04d: %d litros\n",
                       data_inicio.dia, data_inicio.mes, data_inicio.ano,
                       data_fim.dia, data_fim.mes, data_fim.ano,
                       total_combustivel);
                break;


            // ----------------------------------- CADASTRO DE ROTAS -----------------------------------
            case 8:
                {
                    dados_cia_t *nova_rota = cadastrar_nova_rota();
                    if (nova_rota != NULL) {
                        inserir_rota(&base_rotas, nova_rota);
                        printf("Rota com código '%s' cadastrada com sucesso.\n", nova_rota->codigo_rota);
                    }
                }
                break;

            case 9:
                printf("Digite o código da rota a ser removida: ");
                fgets(nome_arquivo, STR_SIZE, stdin);
                nova_linha(nome_arquivo);
                printf("Certeza que deseja remover a rota com código '%s'? (s/n): ", nome_arquivo);
                scanf(" %c", &confirma);
                clear_input();
                if (confirma == 's' || confirma == 'S') {
                    rota_aux = base_rotas;
                    bool encontrada = false;
                    while (rota_aux != NULL) {
                        if (strcmp(rota_aux->codigo_rota, nome_arquivo) == 0) {
                            encontrada = true;
                            break;
                        }
                        rota_aux = rota_aux->prox;
                    }
                    if (!encontrada) {
                        printf("Rota com código '%s' não encontrada.\n", nome_arquivo);
                    } else {
                        remover_rota_por_codigo(nome_arquivo, &base_rotas);
                        printf("Rota com código '%s' removida com sucesso.\n", nome_arquivo);
                    }
                } else {
                    printf("Remoção cancelada.\n");
                }
                break;

            case 10:
                printf("Digite a data para consultar rotas (dd/mm/aaaa): ");
                scanf("%d/%d/%d", &data.dia, &data.mes, &data.ano);
                clear_input();
                if (consultar_rota_por_data(data, base_rotas) == 0){
                    printf("Nenhuma rota encontrada para a data %02d/%02d/%04d\n", data.dia, data.mes, data.ano);
                }
                break;

            case 11:
                {
                    printf("Digite o código da rota para ver os membros da tripulação: ");
                    fgets(nome_arquivo, STR_SIZE, stdin);
                    nova_linha(nome_arquivo);
                    mostrar_membros_tripulacao_rota(nome_arquivo, base_rotas);
                }
                break;
                
            // ----------------------------------- FILTROS AERONAVES -----------------------------------

            case 12:
                printf("Digite o fabricante para listar as aeronaves: ");
                fgets(fabricante, STR_SIZE, stdin);
                nova_linha(fabricante);
                formatar_maiusculo(fabricante);
                listar_aeronaves_por_fabricante(fabricante, base_aeronaves);
                break;

            case 13:
                printf("Digite o tipo de aeronave (1 - Carga, 2 - Passageiro): ");
                scanf("%d", &tipo);
                clear_input();
                listar_aeronaves_por_tipo((tipo_t)tipo, base_aeronaves);
                break;

            case 14:
                printf("Digite o modelo para listar as aeronaves: ");
                fgets(modelo, STR_SIZE, stdin);
                nova_linha(modelo);
                formatar_maiusculo(modelo);
                listar_aeronaves_por_modelo(modelo, base_aeronaves);
                break;    

            case 15:
                printf("Digite o ano de fabricação para listar as aeronaves: ");
                scanf("%d", &ano);
                clear_input();
                listar_aeronaves_por_ano_fabricacao(ano, base_aeronaves);
                break;

            case 16:
                printf("Digite a situação da aeronave (1 - Operação, 2 - Manutenção): ");
                scanf("%d", &situacao);
                clear_input();
                listar_aeronaves_por_situacao((situacao_t)situacao, base_aeronaves);
                break;

            //----------------------------------- CONSULTA DE ROTAS -----------------------------------

            case 17:

                printf("Digite o destino para listar as rotas: ");
                fgets(destino, STR_SIZE, stdin);
                nova_linha(destino);
                formatar_maiusculo(destino);
                listar_rotas_por_destino(destino, base_rotas);
                break;

            case 18:
                printf("Digite a origem para listar as rotas: ");
                fgets(origem, STR_SIZE, stdin);
                nova_linha(origem);
                formatar_maiusculo(origem);
                listar_rotas_por_origem(origem, base_rotas);
                break;

            case 19:
                printf("Digite o destino para calcular o percentual de voos: ");
                fgets(destino, STR_SIZE, stdin);
                nova_linha(destino);
                formatar_maiusculo(destino);
                printf("Digite a data de início (dd/mm/aaaa): ");
                scanf("%d/%d/%d", &data_inicio.dia, &data_inicio.mes, &data_inicio.ano);
                clear_input();
                printf("Digite a data de fim (dd/mm/aaaa): ");
                scanf("%d/%d/%d", &data_fim.dia, &data_fim.mes, &data_fim.ano);
                clear_input();
                float percentual = calcular_percentual_voos_destino(destino, data_inicio, data_fim, base_rotas);
                printf("Percentual de voos para %s entre %02d/%02d/%04d e %02d/%02d/%04d: %.2f%%\n",
                       destino,
                       data_inicio.dia, data_inicio.mes, data_inicio.ano,
                       data_fim.dia, data_fim.mes, data_fim.ano,
                       percentual); //Andersson me da 10 🙏🙏🙏
                break;

            case 20:
                listar_rotas_maior_numero_passageiros(base_rotas);
                break;

            case 21:
                listar_rotas_menor_numero_passageiros(base_rotas);
                break;

            // ----------------------------------- GERAR ARQUIVOS DE TEXTO -----------------------------------

            case 22:
                {
                    printf("Digite o nome do arquivo para exportar as aeronaves: ");
                    fgets(nome_arquivo, STR_SIZE, stdin);
                    nova_linha(nome_arquivo);
                    exportar_aeronaves_arquivo_texto(nome_arquivo, base_aeronaves);
                }
                break;
            case 23:
                {
                    printf("Digite o nome do arquivo para exportar as rotas: ");
                    fgets(nome_arquivo, STR_SIZE, stdin);
                    nova_linha(nome_arquivo);
                    exportar_rotas_arquivo_texto(nome_arquivo, base_rotas);
                }
                break;
            case 24:
                {
                    printf("Digite o nome do arquivo binário para exportar as aeronaves: ");
                    fgets(nome_arquivo, STR_SIZE, stdin);
                    nova_linha(nome_arquivo);
                    exportar_aeronaves_arquivo_texto_binario(nome_arquivo, base_aeronaves);
                }
                break;

            case 25:
                {
                    printf("Digite o nome do arquivo binário para exportar as rotas: ");
                    fgets(nome_arquivo, STR_SIZE, stdin);
                    nova_linha(nome_arquivo);
                    exportar_rotas_arquivo_texto_binario(nome_arquivo, base_rotas);
                }
                break;
            
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida! Digite um número das opções abaixo.\n");
        }
    }while(opc != 0);

    return 0;
}