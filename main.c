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
void obterNomeEstudante(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, int studentID, char *studentName);
void gerarBoletim(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, int studentID);
void obterTurmaID(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, int studentID, int *classID);
void obterNomeTurno(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, int classID, char className[20], char shift[8]);
void obterNotas(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, int studentID, float grades[8]);
void obterMedias(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, int studentID, float averages[2]);
void searchStudent(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row);

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
        printf("\t\t\t\t\t\t1- Turnos \n\t\t\t\t\t\t2- Sair\n\t\t\t\t\t\t3- Procurar Aluno e Gerar Boletim\n");
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
        case 3:
            searchStudent(mysql, result, row);
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
        printf("\t\t\t\t\t\t 1- Series\n\t\t\t\t\t\t 2- Cadastrar\n\t\t\t\t\t\t 3- Voltar\n");
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
        printf("\t\t\t\t\t\t 1- Series\n\t\t\t\t\t\t 2- Cadastrar\n\t\t\t\t\t\t 3- Voltar\n");
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
        printf("\t\t\t\t\t\t 1- Series\n\t\t\t\t\t\t 2- Cadastrar\n\t\t\t\t\t\t 3- Voltar\n");
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
        printf("\t\t\t\t\t\t 1- Series\n\t\t\t\t\t\t 2- Cadastrar\n\t\t\t\t\t\t 3- Voltar\n");
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
    char className[20];
    int classID;
    char query[200];

    printf("Insira o nome completo do aluno: \n");
    scanf(" %[^\n]", studentName);
    
    printf("Insira a série do aluno: \n");
    scanf(" %[^\n]", className);

    sprintf(query, "SELECT turma_id FROM turmas WHERE nome_turma = '%s' AND turno = '%s'", className, shift);

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
    }
    else
    {
        printf("Inserção realizada com sucesso!\n");
    }
}
    
void obterTurmaID(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, int studentID, int *classID) {
    
    char query[200];
    sprintf(query, "SELECT turma_id FROM aluno WHERE aluno_id = '%i'", studentID);
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

    sscanf(row[0], "%i", classID);
    mysql_free_result(result);
}

void obterNomeTurno(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, int classID, char className[20], char shift[8]) {
    char query[200];
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

    strcpy(className, row[0]);
    strcpy(shift, row[1]);
    mysql_free_result(result);
}

void obterNotas(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, int studentID, float grades[8]) {
    char query[200];
    sprintf(query, "SELECT nota1, nota2, nota3, nota4 FROM notas WHERE aluno_id = '%i' AND semestre = '1'", studentID);
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

        for (int i = 0; i < 8; i++) {
            grades[i] = 0.0f;
        }

        return;
    }

    for (int i = 0; i < 4; i++) {
        sscanf(row[i], "%f", &grades[i]);
    }

    mysql_free_result(result);

    sprintf(query, "SELECT nota1, nota2, nota3, nota4 FROM notas WHERE aluno_id = '%i' AND semestre = '2'", studentID);
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

        for (int i = 4; i < 8; i++) {
            grades[i] = 0.0f;
        }

        return;
    }

    for (int i = 0; i < 4; i++) {
        sscanf(row[i], "%f", &grades[i + 4]);
    }

    mysql_free_result(result);
}

void obterMedias(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, int studentID, float averages[2]) {
    char query[200];
    sprintf(query, "SELECT media FROM media WHERE aluno_id = '%i' AND semestre = '1'", studentID);
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
        return;
    }

    sscanf(row[0], "%f", &averages[0]);

    mysql_free_result(result);

    sprintf(query, "SELECT media FROM media WHERE aluno_id = '%i' AND semestre = '2'", studentID);
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
        return;
    }

    sscanf(row[0], "%f", &averages[1]);

    mysql_free_result(result);
}

void obterNomeEstudante(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, int studentID, char *studentName) {
    char query[200];
    sprintf(query, "SELECT nome_aluno FROM aluno WHERE aluno_id = '%i'", studentID);

    if (mysql_query(mysql, query) != 0) {
        fprintf(stderr, "Erro ao executar a consulta: %s\n", mysql_error(mysql));
        return;
    }

    if (mysql_field_count(mysql) == 0) {
        fprintf(stderr, "Nenhum resultado encontrado.\n");
        return;
    }

    result = mysql_store_result(mysql);
    if (result == NULL) {
        fprintf(stderr, "Erro ao obter o resultado: %s\n", mysql_error(mysql));
        return;
    }

    row = mysql_fetch_row(result);

    if (row == NULL) {
        fprintf(stderr, "Aluno não encontrado.\n");
        return;
    }

    strcpy(studentName, row[0]);
}

void searchStudent(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row){
    
    system("cls");

    char studentName[100];
    int studentID;
    char query[200];
    int myOpt;

    printf("Buscar por Estudantes: ");
    scanf(" %[^\n]", studentName);

    sprintf(query, "SELECT aluno_id, nome_aluno FROM ALUNO WHERE nome_aluno LIKE '%%%s%%'", studentName);

    mysql_query(mysql, query);
    result = mysql_store_result(mysql);
    int num_fields = mysql_num_fields(result);

    printf("---------------------------\n\n\n");

    while((row = mysql_fetch_row(result))){

        for(int i = 0; i < num_fields; i++){

            printf("%s ", row[i]);

        }
        printf("\n");
    }
    mysql_free_result(result);
    
    printf("---------------------------\n\n\n");

    printf("1- Imprimir Boletim\n2- Voltar\n");
    scanf("%i", &myOpt);

    switch (myOpt)
    {
    case 1:
        printf("Insira o id do aluno ao qual deseja gerar o boletim: ");
        scanf("%i", &studentID);

        gerarBoletim(mysql, result, row, studentID);

        break;
    
    case 2:
        break;
    }
    
    main();
}

void gerarBoletim(MYSQL *mysql, MYSQL_RES *result, MYSQL_ROW row, int studentID) {
    
    float grades[8];
    float averages[2];
    char className[20];
    char shift[8];
    int classID;
    char studentName[100];

    obterNomeEstudante(mysql, result, row, studentID, studentName); 
    obterTurmaID(mysql, result, row, studentID, &classID);
    obterNomeTurno(mysql, result, row, classID, className, shift);
    obterNotas(mysql, result, row, studentID, grades);
    obterMedias(mysql, result, row, studentID, averages);

    FILE *arquivo = fopen("boletim.txt", "w");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para escrita.\n");
        mysql_close(mysql);
        return;
    }

    fprintf(arquivo, "      Boletim Escolar\n");
    fprintf(arquivo, "----------------------------\n");

    fprintf(arquivo, "Nome: %s\n", studentName);
    fprintf(arquivo, "----------------------------\n");

    fprintf(arquivo, "Turma: %s\n", className);
    fprintf(arquivo, "----------------------------\n");

    fprintf(arquivo, "Turno: %s\n", shift);
    fprintf(arquivo, "----------------------------\n\n");
    fprintf(arquivo, "============================\n");
    fprintf(arquivo, "1° Semestre:\n");
    fprintf(arquivo, "============================\n");

    fprintf(arquivo, "%.2f                           |\n", grades[0]);
    fprintf(arquivo, "%.2f                           |\n", grades[1]);
    fprintf(arquivo, "%.2f                           |\n", grades[2]);
    fprintf(arquivo, "%.2f                           |\n", grades[3]);
    fprintf(arquivo, "------------MEDIA--------------|\n");
    fprintf(arquivo, "%.2f                           |\n\n", averages[0]);

    fprintf(arquivo, "============================\n");
    fprintf(arquivo, "2° Semestre:\n");
    fprintf(arquivo, "============================\n");
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
