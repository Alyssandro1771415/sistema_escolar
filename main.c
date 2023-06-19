#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include "conectorC/include/mysql.h"

struct aluno{ // POSTERIORMENTE, MODIFICAR PARA QUE OS DADOS DOS ALUNOS SEJAM IMPUTADOS
    int aluno_id;
    int turma_id;
    char turno[10];
    char aluno_nome[100];
    struct aluno*prox;
    struct aluno*ant;
};

struct aluno * inicio;
struct aluno * fim;
struct aluno * encontrar(char*);

void inserir(void), buscar(void), salvar(void);
void carregar(void), listar(void);
void deletar(struct aluno **, struct aluno **);
void armazrnar(struct aluno * i, struct aluno ** inicio, struct aluno ** ultimo);
void inputs(char *, char *, int), display();
int menu(void);

void main(void){
    inicio = fim = NULL;

    for(;;){
        switch(menu()){
            case 1: inserir();
                break;
            case 2: deletar(&inicio, &fim);
                break;
            case 3: buscar();
                break;
            case 4: listar();
                break;
            case 5: salvar();
                break;    
            case 6: carregar();
                break;
            case 7: exit(0);
                break;                
        }
    }
}

// struct no{
//     struct aluno info;
//     struct no*prox;
//     struct no*ant; 
// };

// struct lista{
//     struct no*inicio;
//     struct no*fim;
// };

// void inic_lista(struct lista*lista);

// int lista_vazia(struct lista*lista);

// void inserir_aluno(struct lista*lista, struct aluno aluno);

// void limpar_lista(struct lista*lista);

void pesq_aluno();

menu(void);

int main(){
    // struct lista lista_dos_alunos;
    // inic_lista(&lista_dos_alunos);
    menu();

    return 0;
}

// NOVO MENU
menu(void){
    char opcao[3];
    int num;

    printf("1. Inserir aluno\n");
    printf("2. Deletar alunon\n");
    printf("3. Buscar por aluno\n");
    printf("4. Listar arquivo\n");
    printf("5. Gravar o arquivo\n");
    printf("6. Carregar o arquivo\n");
    printf("7. Sair\n");
    do{
        printf("\nEscolha: ");
        gets(opcao);
        num = atoi(opcao);
    }while(num<0 || num>7);

    return num;
}

// void inic_lista(struct lista*lista){
//     lista->inicio = NULL;
//     lista->fim = NULL;
// }

// int lista_vazia(struct lista*lista){
//     return lista->inicio == NULL;
// }

// void inserir_aluno(struct lista*lista, struct aluno aluno){
//     struct no*novo_no = (struct no*)malloc(sizeof(struct no));
//     novo_no->info = aluno;
//     novo_no->prox = NULL;

//     if(lista_vazia(lista)){
//         novo_no->ant = NULL;
//         lista->inicio = novo_no;
//         lista->fim = novo_no;
//     }else{
//         novo_no->ant = lista->fim;
//         lista->fim->prox = novo_no;
//         lista->fim = novo_no;
//     }
// }

// void limpar_lista(struct lista*lista){
//     struct no*atual = lista->inicio;
//     while (atual != NULL){
//         struct no*temp = atual;
//         atual = atual->prox;
//         free(temp);
//     }

//     lista->inicio = NULL;
//     lista->fim = NULL;
// }

void pesq_aluno(void){
    char nome[40];
    struct *info, *encontrar();
}