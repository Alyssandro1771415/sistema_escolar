#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include "conectorC/include/mysql.h"

MYSQL *mysql;
MYSQL_RES *result;
MYSQL_ROW row;

void gerarBoletim(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, char studentName[100]);

int main()
{

    mysql = mysql_init(NULL);
    mysql_real_connect(mysql, "localhost", "root", "", "dados_escolares", 0, NULL, 0);

    const char *nomeTabela = "nome_da_tabela";
    const char *nomeEstudante = "nome_do_estudante";

    gerarBoletim(mysql, result, row, "Alyssandro Dyogo Ramos", 1);

    return 0;
}

void gerarBoletim(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, char studentName[100])
{
    char query[200];
    int classID;
    int studentID;
    char className[20];
    char shift[8];
    float grades[4];
    float averages[2];

    sprintf(query, "SELECT turma_id FROM aluno WHERE nome_aluno = '%s'", studentName);
    if (mysql_query(mysql, query))
    {
        fprintf(stderr, "Erro ao executar a consulta: %s\n", mysql_error(mysql));
        return;
    }

    result = mysql_store_result(mysql);
    if (result == NULL)
    {
        fprintf(stderr, "Erro ao obter resultados: %s\n", mysql_error(mysql));
        return;
    }

    row = mysql_fetch_row(result);
    if (row == NULL)
    {
        fprintf(stderr, "Turma não encontrada.\n");
        mysql_free_result(result);
        mysql_close(mysql);
        return;
    }

    if (result != NULL)
    {
        sscanf(row[0], "%d", &classID);
        mysql_free_result(result);
    }

    sprintf(query, "SELECT nome_turma, turno FROM turmas WHERE turma_id = '%i'", classID);

    if (mysql_query(mysql, query))
    {
        fprintf(stderr, "Erro ao executar a consulta: %s\n", mysql_error(mysql));
        return;
    }

    result = mysql_store_result(mysql);
    if (result == NULL)
    {
        fprintf(stderr, "Erro ao obter resultados: %s\n", mysql_error(mysql));
        return;
    }

    row = mysql_fetch_row(result);
    if (row == NULL)
    {
        fprintf(stderr, "Dados não obtidos.\n");
        mysql_free_result(result);
        mysql_close(mysql);
        return;
    }

    if (result != NULL)
    {
        strcpy(className, row[0]);
        strcpy(shift, row[1]);
        mysql_free_result(result);
    }

    sprintf(query, "SELECT aluno_id FROM aluno WHERE nome_aluno = '%s'", studentName);

    if (mysql_query(mysql, query))
    {
        fprintf(stderr, "Erro ao executar a consulta: %s\n", mysql_error(mysql));
        return;
    }

    result = mysql_store_result(mysql);
    if (result == NULL)
    {
        fprintf(stderr, "Erro ao obter resultados: %s\n", mysql_error(mysql));
        return;
    }

    row = mysql_fetch_row(result);
    if (row == NULL)
    {
        fprintf(stderr, "Dados não obtidos.\n");
        mysql_free_result(result);
        mysql_close(mysql);
        return;
    }

    if (result != NULL)
    {
        sscanf(row[0], "%d", &studentID);
        mysql_free_result(result);
    }

    sprintf(query, "SELECT nota1, nota2, nota3, nota4 FROM notas where aluno_id = '%i' and semestre = '1'", studentID);

    if (mysql_query(mysql, query))
    {
        fprintf(stderr, "Erro ao executar a consulta: %s\n", mysql_error(mysql));
        return;
    }

    result = mysql_store_result(mysql);
    if (result == NULL)
    {
        fprintf(stderr, "Erro ao obter resultados: %s\n", mysql_error(mysql));
        return;
    }

    row = mysql_fetch_row(result);
    if (row == NULL)
    {
        fprintf(stderr, "Dados não obtidos.\n");
        mysql_free_result(result);
        mysql_close(mysql);
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        sscanf(row[i], "%f", &grades[i]);
    }

    sprintf(query, "SELECT nota1, nota2, nota3, nota4 FROM notas where aluno_id = '%i' and semestre = '2'", studentID);

    if (mysql_query(mysql, query))
    {
        fprintf(stderr, "Erro ao executar a consulta: %s\n", mysql_error(mysql));
        return;
    }

    result = mysql_store_result(mysql);
    if (result == NULL)
    {
        fprintf(stderr, "Erro ao obter resultados: %s\n", mysql_error(mysql));
        return;
    }

    row = mysql_fetch_row(result);
    if (row == NULL)
    {
        fprintf(stderr, "Dados não obtidos.\n");
        mysql_free_result(result);
        mysql_close(mysql);
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        sscanf(row[i], "%f", &grades[i + 4]);
    }

    sprintf(query, "SELECT media FROM media WHERE aluno_id = '%i' AND semestre = '1'", studentID);

    if (mysql_query(mysql, query))
    {
        fprintf(stderr, "Erro ao executar a consulta: %s\n", mysql_error(mysql));
        return;
    }

    result = mysql_store_result(mysql);
    if (result == NULL)
    {
        fprintf(stderr, "Erro ao obter resultados: %s\n", mysql_error(mysql));
        return;
    }

    row = mysql_fetch_row(result);
    if (row == NULL)
    {
        fprintf(stderr, "Dados não obtidos.\n");
        mysql_free_result(result);
        mysql_close(mysql);
        return;
    }

    for (int i = 0; i < 1; i++)
    {
        sscanf(row[i], "%f", &averages[i]);
    }

    sprintf(query, "SELECT media FROM media WHERE aluno_id = '%i' AND semestre = '2'", studentID);

    if (mysql_query(mysql, query))
    {
        fprintf(stderr, "Erro ao executar a consulta: %s\n", mysql_error(mysql));
        return;
    }

    result = mysql_store_result(mysql);
    if (result == NULL)
    {
        fprintf(stderr, "Erro ao obter resultados: %s\n", mysql_error(mysql));
        return;
    }

    row = mysql_fetch_row(result);
    if (row == NULL)
    {
        fprintf(stderr, "Dados não obtidos.\n");
        mysql_free_result(result);
        mysql_close(mysql);
        return;
    }

    sscanf(row[0], "%f", &averages[1]);

    mysql_free_result(result);

    mysql_free_result(result);

    FILE *arquivo = fopen("boletim.txt", "w");
    if (arquivo == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo para escrita.\n");
        mysql_close(mysql);
        return;
    }

    fprintf(arquivo, "      Boletim Escolar\n");
    fprintf(arquivo, "----------------------------\n\n");

    fprintf(arquivo, "Nome: %s\n", studentName);
    fprintf(arquivo, "----------------------------\n");

    fprintf(arquivo, "Turma: %s\n", className);
    fprintf(arquivo, "----------------------------\n");

    fprintf(arquivo, "Turno: %s\n", shift);
    fprintf(arquivo, "----------------------------\n\n");
    fprintf(arquivo, "============================\n");
    fprintf(arquivo, "Semestre:\n");
    fprintf(arquivo, "============================\n");
    fprintf(arquivo, "1° Semestre\n");
    fprintf(arquivo, "------------NOTAS--------------|\n");

    fprintf(arquivo, "%.2f                           |\n", grades[0]);
    fprintf(arquivo, "%.2f                           |\n", grades[1]);
    fprintf(arquivo, "%.2f                           |\n", grades[2]);
    fprintf(arquivo, "%.2f                           |\n", grades[3]);
    fprintf(arquivo, "------------MEDIA--------------|\n");
    fprintf(arquivo, "%.2f                           |\n\n", averages[0]);

    fprintf(arquivo, "2° Semestre\n");
    fprintf(arquivo, "------------NOTAS--------------|\n");
    fprintf(arquivo, "%.2f                           |\n", grades[4]);
    fprintf(arquivo, "%.2f                           |\n", grades[5]);
    fprintf(arquivo, "%.2f                           |\n", grades[6]);
    fprintf(arquivo, "%.2f                           |\n", grades[7]);
    fprintf(arquivo, "------------MEDIA--------------|\n");
    fprintf(arquivo, "%.2f                           |\n\n", averages[1]);

    fclose(arquivo);
    mysql_close(mysql);
}
