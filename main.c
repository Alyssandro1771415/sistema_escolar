#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conectorC/include/mysql.h"

struct aluno
{
    char aluno_nome[100];
    int class_ID;
    struct aluno *proximo;
};

struct aluno *inicio_aluno = NULL;
struct aluno *fim_aluno = NULL;

struct turma
{
    char className[30];
    int schoolYear;
    char shift[8];
    struct turma *proximo;
};

struct turma *inicio_turma = NULL;
struct turma *fim_turma = NULL;

void novo_aluno(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, const char shift[8]);
void insercao_encadeada_alunos(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row);
void limpar_lista_alunos();
void novas_turmas(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, const char shift[8]);
void limpar_lista_turmas();
void insercao_encadeada_turmas(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row);

MYSQL *mysql;
MYSQL_RES *result;
MYSQL_ROW row;

int main()
{
    mysql = mysql_init(NULL);
    mysql_real_connect(mysql, "localhost", "root", "", "dados_escolares", 0, NULL, 0);

    // novo_aluno(mysql, result, row, "noite");
    // insercao_encadeada(mysql, result, row);
    // limpar_lista_alunos();

    novas_turmas(mysql, result, row, "noite");
    insercao_encadeada_turmas(mysql, result, row);

    limpar_lista_turmas();

    return 0;
}

void novo_aluno(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, const char shift[8])
{
    char studentName[100];
    char className[20];
    int classID;
    char query[200];
    char continuar;

    do
    {
        printf("Insira o nome do estudante: ");
        scanf(" %[^\n]", studentName);

        printf("Insira a série do aluno: ");
        scanf(" %[^\n]", className);

        sprintf(query, "SELECT turma_id FROM turmas WHERE nome_turma = '%s' AND turno = '%s'", className, shift);

        if (mysql_query(mysql, query) == 0)
        {
            result = mysql_store_result(mysql);

            if (result != NULL)
            {
                if ((row = mysql_fetch_row(result)) != NULL)
                {
                    sscanf(row[0], "%d", &classID);
                }
                mysql_free_result(result);
            }
        }
        else
        {
            printf("Erro ao executar a consulta.\n");
            return;
        }

        struct aluno *novo_aluno = (struct aluno *)malloc(sizeof(struct aluno));
        if (novo_aluno == NULL)
        {
            printf("Erro ao alocar memória para o novo aluno.\n");
            return;
        }

        strcpy(novo_aluno->aluno_nome, studentName);
        novo_aluno->class_ID = classID;

        novo_aluno->proximo = NULL;

        if (inicio_aluno == NULL)
        {
            inicio_aluno = novo_aluno;
            fim_aluno = novo_aluno;
        }
        else
        {
            fim_aluno->proximo = novo_aluno;
            fim_aluno = novo_aluno;
        }

        printf("Deseja adicionar outro aluno? (S/N): ");
        scanf(" %c", &continuar);
    } while (continuar == 'S' || continuar == 's');
}

void insercao_encadeada_alunos(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row)
{
    char query[200];

    struct aluno *atual = inicio_aluno;
    while (atual != NULL)
    {
        sprintf(query, "INSERT INTO aluno (nome_aluno, turma_id) VALUES ('%s', '%i')", atual->aluno_nome, atual->class_ID);

        if (mysql_query(mysql, query) != 0)
        {
            fprintf(stderr, "Erro ao executar o registro: %s\n", mysql_error(mysql));
        }
        else
        {
            printf("Inserção realizada com sucesso!\n");
            printf("Nome: %s\n", atual->aluno_nome);
            printf("ID da turma: %i\n", atual->class_ID);
            printf("\n");
        }

        atual = atual->proximo;
    }
}

void limpar_lista_alunos()
{
    struct aluno *atual = inicio_aluno;
    while (atual != NULL)
    {
        struct aluno *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    inicio_aluno = NULL;
    fim_aluno = NULL;
}

void novas_turmas(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, const char shift[8])
{
    char continuar;
    char className[30];
    int schoolYear;

    do
    {
        printf("Insira o nome da turma: ");
        scanf(" %[^\n]", className);

        printf("Ano Letivo: ");
        scanf("%i", &schoolYear);

        struct turma *novas_turmas = (struct turma *)malloc(sizeof(struct turma));
        if (novas_turmas == NULL)
        {
            printf("Erro ao alocar memória para a nova turma.\n");
            return;
        }

        strcpy(novas_turmas->className, className);
        strcpy(novas_turmas->shift, shift);
        novas_turmas->schoolYear = schoolYear;

        novas_turmas->proximo = NULL;

        if (inicio_turma == NULL)
        {
            inicio_turma = novas_turmas;
            fim_turma = novas_turmas;
        }
        else
        {
            fim_turma->proximo = novas_turmas;
            fim_turma = novas_turmas;
        }

        printf("Deseja adicionar outra turma? (S/N): ");
        scanf(" %c", &continuar);

    } while (continuar == 'S' || continuar == 's');
}

void limpar_lista_turmas()
{
    struct turma *atual = inicio_turma;
    while (atual != NULL)
    {
        struct turma *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    inicio_turma = NULL;
    fim_turma = NULL;
}

void insercao_encadeada_turmas(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row)
{

    char query[200];

    struct turma *atual = inicio_turma;
    while (atual != NULL)
    {
        
        sprintf(query, "INSERT INTO turmas (nome_turma, ano_letivo, turno) VALUES ('%s', '%i', '%s')", atual->className, atual->schoolYear, atual->shift);

        if (mysql_query(mysql, query) != 0)
        {
            fprintf(stderr, "Erro ao executar o registro: %s\n", mysql_error(mysql));
        }
        else
        {
            printf("Inserção realizada com sucesso!\n");
            printf("Nome: %s\n", atual->className);
            printf("ID da turma: %i\n", atual->schoolYear);
            printf("Turno: %s\n", atual->shift);
            printf("\n");
        }

        atual = atual->proximo;
    }
}
