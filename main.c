#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include "conectorC/include/mysql.h"

struct aluno{
    int aluno_id;
    int turma_id;
    char turno[10];
    char aluno_nome[100];
};

struct no{
    struct aluno info;
    struct no*prox;
    struct no*ant;
};

struct lista{
    struct no*inicio;
    struct no*fim;
};

void inic_lista(struct lista*lista);

int lista_vazia(struct lista*lista);

void inserir_aluno(struct lista*lista, struct aluno aluno);

void limpar_lista(struct lista*lista);

int main(){
    struct lista lista_dos_alunos;
    inic_lista(&lista_dos_alunos);

    return 0;
}

void inic_aluno(struct lista*lista){
    lista->inicio = NULL;
    lista->fim = NULL;
}

int lista_vazia(struct lista*lista){
    return lista->inicio == NULL;
}

void inserir_aluno(struct lista*lista, struct aluno aluno){
    struct no*novo_no = (struct no*)malloc(sizeof(struct no));
    novo_no->info = aluno;
    novo_no->prox = NULL;

    if(lista_vazia(lista)){
        novo_no->ant = NULL;
        lista->inicio = novo_no;
        lista->fim = novo_no;
    }else{
        novo_no->ant = lista->fim;
        lista->fim->prox = novo_no;
        lista->fim = novo_no;
    }
}

void limpar_lista(struct lista*lista){
    struct no*atual = lista->inicio;
    while (atual != NULL){
        struct no*temp = atual;
        atual = atual->prox;
        free(temp);
    }

    lista->inicio = NULL;
    lista->fim = NULL;
}