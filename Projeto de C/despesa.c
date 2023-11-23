#include <stdio.h>
#include "despesa.h"
#include "utilitario.h"

#define MAX_DESPESAS 100
#define NUM_CATEGORIAS 7


int registrarDespesa(Despesa *despesas, int *contadorDespesas, Usuario *usuario)
{
    if (*contadorDespesas < MAX_DESPESAS)
    {
        printf("Descricao: ");
        lerString(despesas[*contadorDespesas].descricao, DESCRICAO_MAX_LEN);

        printf("Valor: R$");
        despesas[*contadorDespesas].valor = lerFloatPositivo();

        printf("Data (DD MM AAAA): ");
        scanf("%d %d %d", &despesas[*contadorDespesas].data.dia, &despesas[*contadorDespesas].data.mes, &despesas[*contadorDespesas].data.ano);
        printf("===================================\n");

        int categoria;
        printf("Categoria:\n");
        printf("[0] Alimentacao\n");
        printf("[1] Transporte\n");
        printf("[2] Moradia\n");
        printf("[3] Educacao\n");
        printf("[4] Saude\n");
        printf("[5] Lazer\n");
        printf("[6] Outros\n");
        printf("Escolha uma categoria (0-6): ");
        categoria = lerInteiroPositivo();
        despesas[*contadorDespesas].categoria = (Categoria)categoria;
        printf("===================================\n");
        printf("\nDespesa registrada com sucesso!\n");
        printf("\n===================================\n");

        (*contadorDespesas)++;

        return *contadorDespesas;
    }
    else
    {
        printf("Limite de despesas atingido. Nao e possivel adicionar mais despesas.\n");
        return *contadorDespesas;
    }
}

void visualizarHistorico(Despesa *despesas, int contadorDespesas)
{
    if (contadorDespesas > 0)
    {
        printf("\nHistorico de Despesas\n");
        for (int i = 0; i < contadorDespesas; i++)
        {
            printf("%d. %s - R$%.2f - Data: %02d/%02d/%04d - Categoria: %s\n",
                   i + 1,
                   despesas[i].descricao,
                   despesas[i].valor,
                   despesas[i].data.dia,
                   despesas[i].data.mes,
                   despesas[i].data.ano,
                   obterNomeCategoria(despesas[i].categoria));
        }
    }
    else
    {
        printf("Nenhuma despesa registrada ainda.\n");
    }
}

void excluirDespesa(Despesa *despesas, int *contadorDespesas)
{
    if (*contadorDespesas == 0)
    {
        printf("Nenhuma despesa registrada para excluir.\n");
        return;
    }

    int idExcluir;
    printf("Digite o ID da despesa a ser excluida: ");
    idExcluir = lerInteiroPositivo();  // Usando a função utilitária

    if (idExcluir >= 1 && idExcluir <= *contadorDespesas)
    {
        for (int i = idExcluir - 1; i < *contadorDespesas - 1; ++i)
        {
            despesas[i] = despesas[i + 1];
        }

        (*contadorDespesas)--;

        printf("Despesa excluida com sucesso!\n");
    }
    else
    {
        printf("ID invalido. Tente novamente.\n");
    }
}


float calcularTotalGasto(Despesa *despesas, int contadorDespesas)
{
    float total = 0;
    for (int i = 0; i < contadorDespesas; ++i)
    {
        total += despesas[i].valor;
    }
    return total;
}

const char *obterNomeCategoria(Categoria categoria)
{
    switch (categoria)
    {
        case ALIMENTACAO:
            return "ALIMENTACAO";
        case TRANSPORTE:
            return "TRANSPORTE";
        case MORADIA:
            return "MORADIA";
        case EDUCACAO:
            return "EDUCACAO";
        case SAUDE:
            return "SAUDE";
        case LAZER:
            return "LAZER";
        case OUTROS:
            return "OUTROS";
    }
}

void calcularOrcamentoDisponivel(Usuario *usuario, float *orcamentoDisponivel)
{
    float orcamentoTotal = 0;

    for (int i = 0; i < NUM_CATEGORIAS; i++)
    {
        orcamentoTotal += usuario->orcamentoCategorias[i];
    }

    *orcamentoDisponivel = (usuario->limiteSalario * (orcamentoTotal / 100));
}

void calcularPorcentagemGastos(Despesa *despesas, int contadorDespesas, Usuario *usuario)
{
    float totalGastos[NUM_CATEGORIAS] = {0};
    float totalOrcamento[NUM_CATEGORIAS] = {0};

    for (int i = 0; i < NUM_CATEGORIAS; i++)
    {
        totalOrcamento[i] = (usuario->limiteSalario * usuario->orcamentoCategorias[i]) / 100;
    }

    for (int i = 0; i < contadorDespesas; i++)
    {
        totalGastos[despesas[i].categoria] += despesas[i].valor;
    }

    printf("\nPorcentagem de gastos por categoria:\n");
    for (int i = 0; i < NUM_CATEGORIAS; i++)
    {
        float porcentagem = 0;
        if (totalOrcamento[i] != 0)
        {
            porcentagem = (totalGastos[i] / totalOrcamento[i]) * 100;
        }
        printf("%s: %.2f%%\n", obterNomeCategoria(i), porcentagem);
    }
}


void alterarOrcamento(Usuario *usuario)
{
    int categoria;
    float novaPorcentagem;

    printf("\nCategorias:\n");
    for (int i = 0; i < NUM_CATEGORIAS; i++)
    {
        printf("[%d] %s\n", i, obterNomeCategoria(i));
    }

    printf("\nEscolha a categoria para alterar o orçamento: ");
    categoria = lerInteiroPositivo();  // Usando a função utilitária

    if (categoria >= 0 && categoria < NUM_CATEGORIAS)
    {
        printf("Digite a nova porcentagem de orçamento para a categoria %s: ", obterNomeCategoria(categoria));
        novaPorcentagem = lerFloatPositivo();  // Usando a função utilitária

        if (novaPorcentagem >= 0 && novaPorcentagem <= 100)
        {
            usuario->orcamentoCategorias[categoria] = novaPorcentagem;
            printf("Orçamento alterado com sucesso!\n");
        }
        else
        {
            printf("Porcentagem invalida. A porcentagem deve estar entre 0 e 100.\n");
        }
    }
    else
    {
        printf("Categoria invalida. Tente novamente.\n");
    }
}

