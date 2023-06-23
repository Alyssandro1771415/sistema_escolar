#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include "conectorC/include/mysql.h"

struct aluno
{
    char aluno_nome[51];
    int class_ID;
    struct aluno *proximo;
};

struct aluno *inicio;
struct aluno *fim;

void novo_aluno(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, char shift[8]);
void listar_alunos(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row);
void limpar_lista();

MYSQL *mysql;
MYSQL_RES *result;
MYSQL_ROW row;

int main()
{

    mysql = mysql_init(NULL);
    mysql_real_connect(mysql, "localhost", "root", "", "dados_escolares", 0, NULL, 0);

    novo_aluno(mysql, result, row, "noite");
    listar_alunos(mysql, result, row);
    limpar_lista();

    return 0;
}

void novo_aluno(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, char shift[8])
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

        if (inicio == NULL)
        {
            inicio = novo_aluno;
            fim = novo_aluno;
        }
        else
        {
            fim->proximo = novo_aluno;
            fim = novo_aluno;
        }

        printf("Deseja adicionar outro aluno? (S/N): ");
        scanf(" %c", &continuar);
    } while (continuar == 'S' || continuar == 's');
}

void listar_alunos(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row)
{

    char query[200];

    struct aluno *atual = inicio;
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
            printf("ID da turma: %i", atual->class_ID);
            printf("\n");
        }

        atual = atual->proximo;
    }
}

void limpar_lista()
{
    struct aluno *atual = inicio;
    while (atual != NULL)
    {
        struct aluno *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    inicio = NULL;
}
