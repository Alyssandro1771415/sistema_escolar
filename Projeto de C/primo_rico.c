#include <stdio.h>
#include "utilitario.h"
#include "despesa.h"
#define MAX_DESPESAS 100


int main()
{
    Despesa despesas[MAX_DESPESAS];
    int contadorDespesas = 0;
    char opcao;

    Usuario usuario;
    printf("Informe o seu salario: R$");
    scanf("%f", &usuario.limiteSalario);
    printf("===================================");

    printf("\nQuantos %% cada categoria ira ter?\n");

    for (int i = 0; i < NUM_CATEGORIAS; i++)
    {
        printf("%s: ", obterNomeCategoria(i));
        scanf("%f", &usuario.orcamentoCategorias[i]);
    }
    printf("\n===================================\n");

    do
    {
        printf("\n======== Controle de Gastos =======\n");
        printf("[1] Registrar Despesa\n");
        printf("[2] Visualizar Historico\n");
        printf("[3] Excluir Despesa\n");
        printf("[4] Calcular Total Gasto\n");
        printf("[5] Calcular Porcentagem de Gastos\n");
        printf("[6] Alterar Orcamento\n");
        printf("[0] Sair\n");
        printf("===================================\n");
        printf("Escolha uma opcao: ");
        scanf(" %c", &opcao);
        printf("===================================\n");

        switch (opcao)
        {
            case '1':
                contadorDespesas = registrarDespesa(despesas, &contadorDespesas, &usuario);
                break;
            case '2':
                visualizarHistorico(despesas, contadorDespesas);
                break;
            case '3':
                excluirDespesa(despesas, &contadorDespesas);
                break;
            case '4':
                printf("Total Gasto: R$%.2f\n", calcularTotalGasto(despesas, contadorDespesas));
                break;
            case '5':
                calcularPorcentagemGastos(despesas, contadorDespesas, &usuario);
                break;
            case '6':
                alterarOrcamento(&usuario);
                break;
            case '0':
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != '0');
    return 0;
}


