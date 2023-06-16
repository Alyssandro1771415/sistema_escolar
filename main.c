#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "conectorC/include/mysql.h"

void showdata();
void manha();
void tarde();
void noite();
void integral();
void cadastrar();
void procurar();
void listClasses(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, char shift[8]);
void registeringClasses(MYSQL *mysql, char shift[8]);
void listStudents(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, char shift[8], int classID);
void registeringStudents(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row,char shift[8]);

int opcao_tu;
char shift[8];
MYSQL *mysql;
MYSQL_RES *result;
MYSQL_ROW row;

int main()
{

    mysql = mysql_init(NULL);
    mysql_real_connect(mysql, "localhost", "root", "", "dados_escolares", 0, NULL, 0);

    system("color 9f");
    int opcao_tp;
    do
    {
        system("cls");
        printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t==========MENU INICIAL==========\n\t\t\t\t\t\t--------------------------------\n");
        showdata();
        printf("\n\t\t\t\t\t\t-------------------------------- \n");
        printf("\t\t\t\t\t\t1- Turnos \n\t\t\t\t\t\t2- Sair\n");
        printf("\t\t\t\t\t\t================================ \n");
        printf("\t\t\t\t\t\tescolha uma opcao: ");
        scanf("%d", &opcao_tp);
        switch (opcao_tp)
        {
        case 1:
            do
            {
                system("cls");
                printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t==========TURNOS==========\n\t\t\t\t\t\t--------------------------\n");
                showdata();
                printf("\n\t\t\t\t\t\t--------------------------\n");
                printf("\t\t\t\t\t\t 1- Manha \n\t\t\t\t\t\t 2- Tarde \n\t\t\t\t\t\t 3- Noite \n\t\t\t\t\t\t 4- Integral \n\t\t\t\t\t\t 5- Voltar\n");
                printf("\t\t\t\t\t\t==========================\n");
                printf("\t\t\t\t\t\tescolha uma opcao: ");
                scanf("%d", &opcao_tu);

                switch (opcao_tu)
                {
                case 1:
                    strcpy(shift, "manha");
                    manha();
                    break;
                case 2:
                    strcpy(shift, "tarde");
                    tarde();
                    break;
                case 3:
                    strcpy(shift, "noite");
                    noite();
                    break;
                case 4:
                    strcpy(shift, "integral");
                    integral();
                    break;
                case 5:
                    break;
                }
                break;
            } while (opcao_tu != 5);
        case 2:
            exit(0);
            break;
        }
    } while (opcao_tp != 2);

    return 0;
}

void showdata()
{
    int diaatual, mesatual, anoatual;
    struct tm *local;
    time_t temp;
    temp = time(NULL);
    local = localtime(&temp);
    diaatual = local->tm_mday;
    mesatual = local->tm_mon + 1;
    anoatual = local->tm_year + 1900;
    printf("\t\t\t\t\t\tDATA:  %d/%d/%d", diaatual, mesatual, anoatual);
}

void manha()
{
    int opcao_m;
    do
    {
        system("cls");
        printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t==========MANHA==========\n\t\t\t\t\t\t-------------------------\n");
        showdata();
        printf("\n\t\t\t\t\t\t-------------------------\n");
        printf("\t\t\t\t\t\t 1- Series\n\t\t\t\t\t\t 2- Cadastrar\n\t\t\t\t\t\t 3- Procurar Aluno\n\t\t\t\t\t\t 4- Voltar\n");
        printf("\t\t\t\t\t\t========================\n");
        printf("\t\t\t\t\t\tescolha uma opcao: ");
        scanf("%d", &opcao_m);
        switch (opcao_m)
        {
        case 1:
            system("cls");
            listClasses(mysql, result, row, "manha");
            system("pause");
            break;
        case 2:
            system("cls");
            cadastrar();
            break;
        case 3:
            system("cls");
            procurar();
            break;
        case 4:
            main();
            break;
        }
    } while (opcao_m != 6);
}

void tarde()
{
    int opcao_t;
    do
    {
        system("cls");
        printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t==========TARDE==========\n\t\t\t\t\t\t-------------------------\n");
        showdata();
        printf("\n\t\t\t\t\t\t-------------------------\n");
        printf("\t\t\t\t\t\t 1- Series\n\t\t\t\t\t\t 2- Cadastrar\n\t\t\t\t\t\t 3- Procurar Aluno\n\t\t\t\t\t\t 4- Voltar\n");
        printf("\t\t\t\t\t\t========================\n");
        printf("\t\t\t\t\t\tescolha uma opcao: ");
        scanf("%d", &opcao_t);
        switch (opcao_t)
        {
        case 1:
            system("cls");
            listClasses(mysql, result, row, "tarde");
            system("pause");
            break;
        case 2:
            system("cls");
            cadastrar();
            break;
        case 3:
            system("cls");
            procurar();
            break;
        case 4:
            main();
            break;
        }
    } while (opcao_t != 6);
}

void noite()
{
    int opcao_n;
    do
    {
        system("cls");
        printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t==========NOITE==========\n\t\t\t\t\t\t-------------------------\n");
        showdata();
        printf("\n\t\t\t\t\t\t-------------------------\n");
        printf("\t\t\t\t\t\t 1- Series\n\t\t\t\t\t\t 2- Cadastrar\n\t\t\t\t\t\t 3- Procurar Aluno\n\t\t\t\t\t\t 4- Voltar\n");
        printf("\t\t\t\t\t\t========================\n");
        printf("\t\t\t\t\t\tescolha uma opcao: ");
        scanf("%d", &opcao_n);
        switch (opcao_n)
        {
        case 1:
            system("cls");
            listClasses(mysql, result, row, "noite");
            system("pause");
            break;
        case 2:
            system("cls");
            cadastrar();
            break;
        case 3:
            system("cls");
            procurar();
            break;
        case 4:
            main();
            break;
        }
    } while (opcao_n != 6);
}

void integral()
{
    int opcao_i;
    do
    {
        system("cls");
        printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t==========INTEGRAL==========\n\t\t\t\t\t\t-------------------------\n");
        showdata();
        printf("\n\t\t\t\t\t\t-------------------------\n");
        printf("\t\t\t\t\t\t 1- Series\n\t\t\t\t\t\t 2- Cadastrar\n\t\t\t\t\t\t 3- Procurar Aluno\n\t\t\t\t\t\t 4- Voltar\n");
        printf("\t\t\t\t\t\t========================\n");
        printf("\t\t\t\t\t\tescolha uma opcao: ");
        scanf("%d", &opcao_i);
        switch (opcao_i)
        {
        case 1:
            system("cls");
            listClasses(mysql, result, row, "integral");
            system("pause");
            break;
        case 2:
            system("cls");
            cadastrar();
            break;
        case 3:
            system("cls");
            procurar();
            break;
        case 4:
            main();
            break;
        }
    } while (opcao_i != 4);
}

void cadastrar()
{
    int opcao_r;
    do
    {
        system("cls");
        printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t========CADASTRAR========\n\t\t\t\t\t\t-------------------------\n");
        showdata();
        printf("\n\t\t\t\t\t\t-------------------------\n");
        printf("\t\t\t\t\t\t 1- Estudante \n\t\t\t\t\t\t 2- Classe \n\t\t\t\t\t\t 3- Voltar\n");
        printf("\t\t\t\t\t\t=========================\n");
        printf("\t\t\t\t\t\tescolha uma opcao: ");
        scanf("%d", &opcao_r);
        switch (opcao_r)
        {
        case 1:
            system("cls");
            registeringStudents(mysql, result, row, shift);
            system("pause");
            break;
        case 2:
            system("cls");
            registeringClasses(mysql, shift);
            system("pause");
            break;
        case 3:
            return;
            break;
        }
    } while (opcao_r != 3);
}

void procurar()
{
    int opcao_p;
    do
    {
        system("cls");
        printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t==========PROCURAR==========\n\t\t\t\t\t\t---------------------------\n");
        showdata();
        printf("\n\t\t\t\t\t\t-------------------------\n");
        printf("\t\t\t\t\t\t 1- Estudante \n\t\t\t\t\t\t 2- Classe \n\t\t\t\t\t\t 3- Voltar\n");
        printf("\t\t\t\t\t\t=========================\n");
        printf("\t\t\t\t\t\tescolha uma opcao: ");
        scanf("%d", &opcao_p);
        switch (opcao_p)
        {
        case 1:
            system("cls");

            system("pause");
            break;
        case 2:
            system("cls");

            system("pause");
            break;
        case 3:
            return;
            break;
        }
    } while (opcao_p != 3);
}

void listClasses(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, char shift[8])
{
    char query[200];

    sprintf(query, "SELECT nome_turma FROM turmas WHERE turno = '%s'", shift);

    mysql_query(mysql, query);
    result = mysql_store_result(mysql);
    int num_fields = mysql_num_fields(result);

    printf("| Classes |\n");
    printf("-----------\n");

    while ((row = mysql_fetch_row(result)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            printf("| %s |", row[i] ? row[i] : "NULL");
        }        

        printf("\n");
    }
    mysql_free_result(result);
}

void registeringClasses(MYSQL *mysql, char shift[8])
{
    char className[30];
    int schoolYear;
    char query[200];

    printf("nsira o nome da turma: \n");
    scanf(" %[^\n]", className);

    printf("Ano Letivo: ");
    scanf("%i", &schoolYear);
    getchar();

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

void registeringStudents(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, char shift[8])
{
    char studentName[100];
    char class[20];
    int classID;
    char query[200];

    printf("Insira o nome completo do aluno: \n");
    scanf(" %[^\n]", studentName);
    
    printf("Insira a série do aluno: \n");
    scanf(" %[^\n]", class);

    sprintf(query, "SELECT turma_id FROM turmas WHERE nome_turma = '%s' AND turno = '%s'", class, shift);

    mysql_query(mysql, query);
    result = mysql_store_result(mysql);

    if (result != NULL)
    {
        if ((row = mysql_fetch_row(result)) != NULL)
        {
            sscanf(row[0], "%d", &classID);
        }
        mysql_free_result(result);
    }

    sprintf(query, "INSERT INTO aluno (nome_aluno, turma_id) VALUES ('%s', '%i')", studentName, classID);

    if (mysql_query(mysql, query) != 0)
    {
        fprintf(stderr, "Erro ao executar o registro: %s\n", mysql_error(mysql));
        exit(1);
    }

    printf("Inserção realizada com sucesso!\n");
}
