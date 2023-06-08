#include <stdio.h>
#include <stdlib.h>
#include "conectorC/include/mysql.h"

void listClasses(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row);

int main() {
    MYSQL *mysql;
    MYSQL_RES *result;
    MYSQL_ROW row;
    mysql = mysql_init(NULL);
    mysql_real_connect(mysql, "localhost", "root", "", "dados_escolares", 0, NULL, 0);
    
    listClasses(mysql, result, row);
    return 0;
}


void listClasses(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row){

    mysql_query(mysql, "select nome_turma from turmas");
    result = mysql_store_result(mysql);

    int num_fields = mysql_num_fields(result);

    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < num_fields; i++) {
            printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }
    mysql_free_result(result);
    mysql_close(mysql);
}
>>>>>>> Stashed changes
