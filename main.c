#include <stdio.h>
#include <stdlib.h>
#include "conectorC/include/mysql.h"

void listClasses(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row);
void registeringClasses(MYSQL *mysql);
void listStudents(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, char shift[8], int classID);

int main()
{
    MYSQL *mysql;
    MYSQL_RES *result;
    MYSQL_ROW row;
    mysql = mysql_init(NULL);
    mysql_real_connect(mysql, "localhost", "root", "", "dados_escolares", 0, NULL, 0);

    listClasses(mysql, result, row);

    registeringClasses(mysql);

    listStudents(mysql, result, row, "noite", 1);

    return 0;
}

void listClasses(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row)
{

    mysql_query(mysql, "select nome_turma from turmas");
    result = mysql_store_result(mysql);
    int num_fields = mysql_num_fields(result);

    while ((row = mysql_fetch_row(result)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }
    mysql_free_result(result);
}

void registeringClasses(MYSQL *mysql)
{
    char className[30];
    int schoolYear;
    char query[200];

    printf("Turma: ");
    fgets(className, sizeof(className), stdin);
    className[strcspn(className, "\n")] = '\0';

    printf("Ano Letivo: ");
    scanf("%i", &schoolYear);
    getchar();

    sprintf(query, "INSERT INTO turmas (nome_turma, ano_letivo) VALUES ('%s', '%i')", className, schoolYear);

    if (mysql_query(mysql, query) != 0)
    {
        fprintf(stderr, "Erro ao executar a consulta: %s\n", mysql_error(mysql));
        exit(1);
    }

    printf("Inserção realizada com sucesso!\n");
}

void listStudents(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, char shift[8], int classID)
{

    char query[200];

    sprintf(query, "SELECT * FROM ALUNO WHERE turno = '%s' and turma_id = %i;", shift, classID);

    mysql_query(mysql, query);
    result = mysql_store_result(mysql);
    int num_fields = mysql_num_fields(result);

    while ((row = mysql_fetch_row(result)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            printf("| %s ", row[i] ? row[i] : "NULL");
        }        
        printf("|");
    }
    mysql_free_result(result);
}
