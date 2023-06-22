#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include "conectorC/include/mysql.h"

struct aluno{
    char aluno_nome[51];
    char turno[20];
    char turma[20];
    char matricula[20];
    struct aluno * proximo;
};

struct aluno * inicio;
struct aluno * fim;

void novo_aluno(const char * nome, const char * turno, const char * turma, const char * matricula);
void listar_alunos();
void limpar_lista();

int main(){
    // EXEMPLOS: (CRIAR UMA FUNÇÃO EXPECÍFICA PARA INSERIR OS DADOS DO MYSQL)
    novo_aluno("Zé Lucas", "Manhã", "A", "123456");
    novo_aluno("Alyssandersson", "Noite", "B", "666999");
    novo_aluno("Zé Tom", "Tarde", "C", "000000");

    listar_alunos();

    limpar_lista();

    return 0;
}

void novo_aluno(const char * nome, const char * turno, const char * turma, const char * matricula){
    struct aluno * novo_aluno = (struct aluno *) malloc(sizeof(struct aluno));
    if(novo_aluno == NULL){
        printf("Erro ao alocar memória para o novo aluno.\n");
        return;
    }

    strcpy(novo_aluno->aluno_nome, nome);
    strcpy(novo_aluno->turno, turno);
    strcpy(novo_aluno->turma, turma);
    strcpy(novo_aluno->matricula, matricula);
    novo_aluno->proximo = NULL;

    if(inicio == NULL){
        inicio = novo_aluno;
    }else{
        struct aluno * atual = inicio;
        while(atual->proximo != NULL){
            atual = atual->proximo;
        }
        atual->proximo = novo_aluno;
    }
}

void listar_alunos(){
    struct aluno * atual = inicio;
    while (atual != NULL){
        printf("Nome: %s\n", atual->aluno_nome);
        printf("Turno: %s\n", atual->turno);
        printf("Turma: %s\n", atual->turma);
        printf("Matrícula: %s\n", atual->matricula);
        printf("\n");
        atual = atual->proximo;
    }
}

void limpar_lista(){
    struct aluno * atual = inicio;
    while (atual != NULL){
        struct aluno * proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    inicio = NULL;
}