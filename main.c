#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include "conectorC/include/mysql.h"

MYSQL *mysql;
MYSQL_RES *result;
MYSQL_ROW row;

void exportarDadosEstudante(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, char studentName[100]);

int main(){

    mysql = mysql_init(NULL);
    mysql_real_connect(mysql, "localhost", "root", "", "dados_escolares", 0, NULL, 0);

    
    const char *nomeTabela = "nome_da_tabela";
    const char *nomeEstudante = "nome_do_estudante";

    exportarDadosEstudante(mysql, result, row, "Alyssandro 3.1415");

    return 0;
}

void exportarDadosEstudante(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, char studentName[100]) {
    char query[200];
    int classID;
    int studentID;
    char className[20];
    char shift[8];
    float grades[4];
    float media[4];

    sprintf(query, "SELECT turma_id FROM aluno WHERE nome_aluno = '%s'", studentName);
    if (mysql_query(mysql, query)) {
        fprintf(stderr, "Erro ao executar a consulta: %s\n", mysql_error(mysql));
        return;
    }

    result = mysql_store_result(mysql); 
    if (result == NULL) {
        fprintf(stderr, "Erro ao obter resultados: %s\n", mysql_error(mysql));
        return;
    }

    row = mysql_fetch_row(result);  
    if (row == NULL) {
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

    if (mysql_query(mysql, query)) {
        fprintf(stderr, "Erro ao executar a consulta: %s\n", mysql_error(mysql));
        return;
    }

    result = mysql_store_result(mysql);  
    if (result == NULL) {
        fprintf(stderr, "Erro ao obter resultados: %s\n", mysql_error(mysql));
        return;
    }

    row = mysql_fetch_row(result);  
    if (row == NULL) {
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

        if (mysql_query(mysql, query)) {
        fprintf(stderr, "Erro ao executar a consulta: %s\n", mysql_error(mysql));
        return;
    }

    result = mysql_store_result(mysql);  
    if (result == NULL) {
        fprintf(stderr, "Erro ao obter resultados: %s\n", mysql_error(mysql));
        return;
    }

    row = mysql_fetch_row(result);  
    if (row == NULL) {
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

    
    sprintf(query, "SELECT nota1, nota2, nota3, nota4 FROM notas where aluno_id = '%i'", studentID);

    //--------------------------------------------------------------------

    char nomeArquivo[100];
    sprintf(nomeArquivo, "%s.txt", studentName);
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s para escrita.\n", nomeArquivo);
        mysql_free_result(result);
        mysql_close(mysql);
        return;
    }

    for (unsigned int i = 0; i < mysql_num_fields(result); i++) {
        fprintf(arquivo, "%s\t", row[i]);
    }

    fclose(arquivo);
    mysql_free_result(result);
}