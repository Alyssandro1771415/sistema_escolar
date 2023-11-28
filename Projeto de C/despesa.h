#ifndef DESPESA_H
#define DESPESA_H


#define DESCRICAO_MAX_LEN 50
#define NUM_CATEGORIAS 7

typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

typedef enum
{
    ALIMENTACAO,
    TRANSPORTE,
    MORADIA,
    EDUCACAO,
    SAUDE,
    LAZER,
    OUTROS
} Categoria;

typedef struct
{
    char descricao[DESCRICAO_MAX_LEN];
    float valor;
    Data data;
    Categoria categoria;
} Despesa;

typedef struct
{
    float limiteSalario;
    float orcamentoCategorias[NUM_CATEGORIAS];
} Usuario;

int registrarDespesa(Despesa *despesas, int *contadorDespesas, Usuario *usuario);
void visualizarHistorico(Despesa *despesas, int contadorDespesas);
void excluirDespesa(Despesa *despesas, int *contadorDespesas);
float calcularTotalGasto(Despesa *despesas, int contadorDespesas);
const char *obterNomeCategoria(Categoria categoria);
void calcularOrcamentoDisponivel(Usuario *usuario, float *orcamentoDisponivel);
void calcularPorcentagemGastos(Despesa *despesas, int contadorDespesas, Usuario *usuario);
void alterarOrcamento(Usuario *usuario);


#endif