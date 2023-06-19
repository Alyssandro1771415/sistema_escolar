#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include "conectorC/include/mysql.h"

struct aluno{ // POSTERIORMENTE, MODIFICAR PARA QUE OS DADOS DOS ALUNOS SEJAM IMPUTADOS
    char aluno_nome[51];
    char turno[20];
    char turma[20];
    char matricula[20];
    struct aluno*prox;
    struct aluno*ant;
} lista;

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

    while(1){
        switch(menu()){
            case 1: inserir(); // =)
                break;
            case 2: deletar(&inicio, &fim); // 
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

void inserir(void){
    struct aluno *info;

    while(1){
        info =(struct aluno *)malloc(sizeof(lista));
        if(!info){
        printf("\nsem memoria");
        return;
        }

        inputs("Insira o NOME do aluno: ", info->aluno_nome, 51);
            if(!info->aluno_nome[0]) break;
        inputs("Insira o TURNO do aluno: ", info->turno, 20);
        inputs("Insira a TURMA do aluno: ", info->turma, 20);
        inputs("Insira o numero da MATRICULA do aluno: ", info->matricula, 20);

        armazenar(info, &inicio, &fim);
    }   // LAÇO DE ENTRADA
}

void deletar(struct aluno ** inicio, struct aluno ** fim){
    struct aluno * info, *encontrar();
    char s[51];

    printf("Insira o nome: ", s, 30);
    info = encontrar(s);
        if (*inicio == info) {
            *inicio = info->prox;
            if(*inicio) (*inicio)-> prox = NULL;
            else *fim = NULL;
        } else {
            info ->
}
}

void armazenar( struct aluno * i, struct aluno ** inicio, struct aluno ** fim){
    struct aluno *anterior, *pont;

    if(*fim == NULL){
        i -> prox = NULL;
        i -> aux = NULL;
        *fim = i;
        *inicio = i;
        return;
    }
    pont = *inicio; // TOPO DA LISTA

    anterior = NULL;
    while(pont){
        if(strcmp(pont->aluno_nome, i->aluno_nome) < 0) {
            anterior = pont;
            pont = pont->prox;
        }else{
            if(pont->aux){
                pont->aux->prox = i;
                i->prox = pont;
                i->aux = pont->aux;
                pont->aux = i;
                return;
            }
            i->prox = pont; // NOVO PRIMEIRO ELEMENTO
            i->aux = NULL;
            pont->aux = i;
            *inicio = i;
            return;
        }
    }
    anterior->prox = i; // insere no fim
    i->prox = NULL;
    i->aux = anterior;
    *fim = i;
}

struct aluno *encontrar(char *aluno_nome){
    struct aluno *info;
    info = inicio;
    while(info){
        if(!strcmp(aluno_nome, info->aluno_nome)) return info;
        info = info->prox; 
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
//     lista->fim = NULL;'
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

// void pesq_aluno(void){
//     char nome[40];
//     struct *info, *encontrar();
// }