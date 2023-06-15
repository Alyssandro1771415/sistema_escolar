#include <stdio.h>
#include <stdlib.h>
#include "conectorC/include/mysql.h"

void listClasses(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, char shift[8]);
void registeringClasses(MYSQL *mysql);
void listStudents(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, char shift[8], int classID);
void registeringStudents(MYSQL *mysql, char nomeAluno[100], int turmaID);

int main()
{
    MYSQL *mysql;
    MYSQL_RES *result;
    MYSQL_ROW row;
    mysql = mysql_init(NULL);
    mysql_real_connect(mysql, "localhost", "root", "", "dados_escolares", 0, NULL, 0);

    

    return 0;
}

void listClasses(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, char shift[8])
{

    char query[200];

    sprintf(query, "SELECT nome_turma FROM turmas WHERE turno = '%s'", shift);

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

void registeringClasses(MYSQL *mysql)
{
    char className[30];
    int schoolYear;
    char query[200];
    char shift[8];

    printf("Turma: ");
    fgets(className, sizeof(className), stdin);
    className[strcspn(className, "\n")] = '\0';

    printf("Ano Letivo: ");
    scanf("%i", &schoolYear);
    getchar();

    printf("Turno: ");
    fgets(shift, sizeof(shift), stdin);
    shift[strcspn(shift, "\n")] = '\0';

    sprintf(query, "INSERT INTO turmas (nome_turma, ano_letivo, turno) VALUES ('%s', '%i', '%s')", className, schoolYear, shift);

    if (mysql_query(mysql, query) != 0)
    {
        fprintf(stderr, "Erro ao executar o registro: %s\n", mysql_error(mysql));
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

void registeringStudents(MYSQL *mysql, char nomeAluno[100], int turmaID){

    char query[200];

    sprintf(query, "INSERT INTO aluno (nome_aluno, turma_id) VALUES ('%s', '%i')", nomeAluno, turmaID);

    if(mysql_query(mysql, query) != 0){

        fprintf(stderr, "Erro ao executar o registro: %s\n", mysql_error(mysql));
        exit(1);
    }

    printf("Inserção realizada com sucesso!\n");

}
