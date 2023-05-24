#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include "conectorC/include/mysql.h"

int main()
{
    int conexao();
    
    conexao();

    return 0;
}



int conexao(){

    MYSQL *conn = mysql_init(NULL);

    if(conn == NULL){
        printf("Erro ao tentar estabelecer a conexão!");
        exit(1);
    } 

    if(mysql_real_connect(conn, "localhost", "root", "", "dados_escolares", 0, NULL, 0) == NULL){

        printf("Erro ao estabelecer a conexão com o banco de dados");
        exit(1);

    }

    printf("tudo okay");

}
