#include "./include/funcao_base.h"
#include "./include/aeronaves_lista.h"
#include "./include/remocoes.h"
#include "./include/filtros.h"
#include "./include/consulta_rotas.h"
#include "./include/gerar_arquivos.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

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

    struct base_aeronaves aeronaves;
    struct base_rotas rotas;

    inicializar_base_aeronaves(&aeronaves);
    inicializar_base_rotas(&rotas);

    int sub_opc;

    do{
        opc = menu();

        switch (opc){

            case 1: // Aeronaves
                sub_opc = sub_menu_aeronaves();

                    switch(sub_opc){ //Cadastrar aeronave
                        case 1:
                            {
                                dados_aeronaves_t *nova_aeronave = cadastrar_nova_aeronave();
                                if (nova_aeronave != NULL) {
                                    inserir_aeronave(&base_aeronaves, nova_aeronave);
                                    printf("Aeronave com matrícula '%s' cadastrada com sucesso.\n", nova_aeronave->matricula); //NOTAS: Papercut - Linkin Park é pratimonio da humanidade
                                }
                            }
                            break;

                        case 2: //Relatório de aeronaves cadastradas
                            relatorio_aeronaves_cadastradas(base_aeronaves);
                            break;

                        case 3: //Remover aeronave por matrícula
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
                            }  
                            break;

                        case 4: // Alterar situação de uma aeronave
                            printf("Digite a matrícula da aeronave para alterar a situação: ");
                            fgets(matricula, STR_SIZE, stdin);
                            nova_linha(matricula);
                            printf("Digite a nova situação (1 - Operação, 2 - Manutenção): ");
                            scanf("%d", &situacao);
                            clear_input();
                            alterar_situacao_aeronave(matricula, (situacao_t)situacao, base_aeronaves);
                            break;

                        case 5: // Manutenções de uma aeronave
                            printf("Digite a matrícula da aeronave para verificar a quantidade de manutenções: ");
                            fgets(matricula, STR_SIZE, stdin);
                            nova_linha(matricula);
                            quantidade_manutencoes_aeronave(matricula, base_aeronaves); //AOS 45 DO SEGUNDO TEMPO ELA FUNCIONOU AO9AOAOAOAOAOAO
                            break;

                        case 6: // Percentual de voos realizados por aeronave
                            printf("Digite a matrícula da aeronave para calcular o percentual de voos realizados: ");
                            fgets(matricula, STR_SIZE, stdin);
                            nova_linha(matricula);
                            percentual_voos_realizados(matricula, base_aeronaves);
                            break;

                        case 7: // Consumo de combustível total em um intervalo de datas
                            printf("Digite a matrícula da aeronave para calcular o consumo de combustível: ");
                            fgets(matricula, STR_SIZE, stdin);
                            nova_linha(matricula);
                            printf("Digite a data de início (dd/mm/aaaa): ");
                            scanf("%d/%d/%d", &data_inicio.dia, &data_inicio.mes, &data_inicio.ano);
                            clear_input();
                            printf("Digite a data de fim (dd/mm/aaaa): ");
                            scanf("%d/%d/%d", &data_fim.dia, &data_fim.mes, &data_fim.ano);
                            clear_input();
                            consumo_combustivel_intervalo_datas(data_inicio, data_fim, base_rotas);
                            break;

                        default:
                            printf("Opção inválida no submenu de aeronaves!\n");
                    }

                break;
            case 2: // Rotas
                 sub_opc = sub_menu_rotas();

                    switch(sub_opc){ //Cadastrar rota
                        case 1:
                            {
                                dados_cia_t *nova_rota = cadastrar_nova_rota();
                                if (nova_rota != NULL) {
                                    inserir_rota(&base_rotas, nova_rota);
                                    printf("Rota com código '%s' cadastrada com sucesso.\n", nova_rota->codigo_rota);
                                }
                            }
                            break;

                    case 2: // Relatório de rotas cadastradas
                        relatorio_rotas_cadastradas(base_rotas);
                        break;

                    case 3: // Remover rota por código
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

                    case 4: // Consultar rota por data
                        printf("Digite a data para consultar rotas (dd/mm/aaaa): ");
                        scanf("%d/%d/%d", &data.dia, &data.mes, &data.ano);
                        clear_input();
                        if (consultar_rota_por_data(data, base_rotas) == 0){
                            printf("Nenhuma rota encontrada para a data %02d/%02d/%04d\n", data.dia, data.mes, data.ano);
                        }
                        break;                
                        default:
                            printf("Opção inválida no submenu de rotas!\n");
                    }
                break;

            case 3: // Filtros
                 sub_opc = sub_menu_filtros();

                    switch(sub_opc){ 
                        case 1:
                            printf("Digite o fabricante para listar as aeronaves: ");
                            fgets(fabricante, STR_SIZE, stdin);
                            nova_linha(fabricante);
                            formatar_maiusculo(fabricante);
                            listar_aeronaves_por_fabricante(fabricante, base_aeronaves);
                            break;

                        case 2:
                            printf("Digite o tipo de aeronave (1 - Carga, 2 - Passageiro): ");
                            scanf("%d", &tipo);
                            clear_input();
                            listar_aeronaves_por_tipo((tipo_t)tipo, base_aeronaves);
                            break;

                        case 3:
                            printf("Digite o modelo para listar as aeronaves: ");
                            fgets(modelo, STR_SIZE, stdin);
                            nova_linha(modelo);
                            formatar_maiusculo(modelo);
                            listar_aeronaves_por_modelo(modelo, base_aeronaves);
                            break;    

                        case 4:
                            printf("Digite o ano de fabricação para listar as aeronaves: ");
                            scanf("%d", &ano);
                            clear_input();
                            listar_aeronaves_por_ano_fabricacao(ano, base_aeronaves);
                            break;

                        case 5:
                            printf("Digite a situação da aeronave (1 - Operação, 2 - Manutenção): ");
                            scanf("%d", &situacao);
                            clear_input();
                            listar_aeronaves_por_situacao((situacao_t)situacao, base_aeronaves);
                            break;

                        default:
                            printf("Opção inválida no submenu de filtros!\n");
                    }
                break;

            case 4:
                 sub_opc = sub_menu_consulta_rotas();

                    switch(sub_opc){ 
                        case 1: // Listar rotas por destino
                            printf("Digite o destino para listar as rotas: ");
                            fgets(destino, STR_SIZE, stdin);
                            nova_linha(destino);
                            formatar_maiusculo(destino);
                            listar_rotas_por_destino(destino, base_rotas);
                            break;

                        case 2: // Listar rotas por origem
                            printf("Digite a origem para listar as rotas: ");
                            fgets(origem, STR_SIZE, stdin);
                            nova_linha(origem);
                            formatar_maiusculo(origem);
                            listar_rotas_por_origem(origem, base_rotas);
                            break;

                        case 3: // Percentual de voos para um determinado destino em um intervalo de datas
                            
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
                                percentual_voos_realizados_destino(destino, base_rotas, base_aeronaves);
                            break;

                        case 4: // Listar rotas com menor número de passageiros
                            listar_rota_maior_numero_passageiros(base_rotas);
                            break;
                            

                        case 5: // Listar rotas com maior número de passageiros
                            listar_rota_menor_numero_passageiros(base_rotas); //Sim, eu inverti os nomes
                            break;

                        default:
                            printf("Opção inválida no submenu de consulta de rotas!\n");
                    }
                break;

                case 5:
                    sub_opc = sub_menu_arquivos();

                    switch(sub_opc){ 
                        case 1: // Exportar aeronaves para arquivo TXT
                            printf("Digite o nome do arquivo TXT para exportar as aeronaves: ");
                            fgets(nome_arquivo, STR_SIZE, stdin);
                            nova_linha(nome_arquivo);
                            exportar_aeronaves_arquivo_txt(base_aeronaves, nome_arquivo);
                            break;

                        case 2: // Exportar rotas para arquivo TXT
                            printf("Digite o nome do arquivo TXT para exportar as rotas: ");
                            fgets(nome_arquivo, STR_SIZE, stdin);
                            nova_linha(nome_arquivo);
                            exportar_rotas_arquivo_txt(base_rotas, nome_arquivo);
                            break;

                        case 3: // Exportar aeronaves para arquivo CSV
                            printf("Digite o nome do arquivo CSV para exportar as aeronaves: ");
                            fgets(nome_arquivo, STR_SIZE, stdin);
                            nova_linha(nome_arquivo);
                            exportar_aeronaves_arquivo_csv(base_aeronaves, nome_arquivo);
                            break;

                        case 4: // Exportar rotas para arquivo CSV
                            printf("Digite o nome do arquivo CSV para exportar as rotas: ");
                            fgets(nome_arquivo, STR_SIZE, stdin);
                            nova_linha(nome_arquivo);
                            exportar_rotas_arquivo_csv(base_rotas, nome_arquivo);
                            break;

                        case 5: // Exportar aeronaves para arquivo HTML
                            printf("Digite o nome do arquivo HTML para exportar as aeronaves: ");
                            fgets(nome_arquivo, STR_SIZE, stdin);
                            nova_linha(nome_arquivo);
                            exportar_aeronaves_arquivo_html(base_aeronaves, nome_arquivo);
                            break;

                        case 6: //Exportar rotas para arquivo HTML
                            printf("Digite o nome do arquivo HTML para exportar as rotas: ");
                            fgets(nome_arquivo, STR_SIZE, stdin);
                            nova_linha(nome_arquivo);
                            exportar_rotas_arquivo_html(base_aeronaves, nome_arquivo);
                            break;
                            
                        default:
                            printf("Opção inválida no submenu de arquivos!\n");
                    }
                            
            case 0:
                printf("Encerrando o programa...\n");
                salvar_dados_aeronaves_binario(aeronaves.inicio);
                salvar_dados_rotas_binario(rotas.inicio);
                break;
            default:
                printf("Opção inválida! Digite um número das opções abaixo.\n");
        }

    }while(opc != 0);

    return 0;
}