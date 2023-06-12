#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include "conectorC/include/mysql.h"

void exportarDadosEstudante();

int main(){
    
    const char *nomeTabela = "nome_da_tabela";
    const char *nomeEstudante = "nome_do_estudante";

    void exportarDadosEstudante();

    return 0;
}

void exportarDadosEstudante( const char* nomeTabela, const char* nomeEstudante) {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "usuario", "senha", "nomeBanco", 0, NULL, 0)) {
        fprintf(stderr, "Erro ao conectar ao banco de dados: %s\n", mysql_error(conn));
        return;
    }

    char consulta[200];
    sprintf(consulta, "SELECT * FROM %s WHERE nome = '%s'", nomeTabela, nomeEstudante);
    if (mysql_query(conn, consulta)) {
        fprintf(stderr, "Erro ao executar a consulta: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *resultado = mysql_store_result(conn);
    if (resultado == NULL) {
        fprintf(stderr, "Erro ao obter resultados: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_ROW registro = mysql_fetch_row(resultado);
    if (registro == NULL) {
        fprintf(stderr, "Estudante não encontrado.\n");
        mysql_free_result(resultado);
        mysql_close(conn);
        return;
    }

    char nomeArquivo[100];
    sprintf(nomeArquivo, "%s.txt", nomeEstudante);
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s para escrita.\n", nomeArquivo);
        mysql_free_result(resultado);
        mysql_close(conn);
        return;
    }

    for (unsigned int i = 0; i < mysql_num_fields(resultado); i++) {
        fprintf(arquivo, "%s\t", registro[i]);
    }

    fclose(arquivo);
    mysql_free_result(resultado);
    mysql_close(conn);
}