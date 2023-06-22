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
    struct aluno*proximo;
} lista;

struct aluno * inicio;
struct aluno * fim;
struct aluno * encontrar(char*);

void inserir(void), buscar(void), salvar(void);
void carregar(void), listar(void);
void deletar(struct aluno **, struct aluno **);
void armazenar(struct aluno * aux, struct aluno ** inicio, struct aluno ** fim);
void inputs(char *, char *, int), display();
int menu(void);

int main(void){
    inicio = fim = NULL;

    while(1){
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
            default:
                printf("Insira uma opcao valida\n");      
                return 0;      
        }
    }
    return 0;
}

int menu(void){
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
        fgets(opcao, sizeof(opcao), stdin);
        num = atoi(opcao);
    }while(num<1 || num>7);

    return num;
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

void inputs(char * prompt, char * s, int contador){
    char pont[255];

    do{
        printf(prompt);
        fgets(pont, sizeof(pont), stdin);
        pont[strcspn(pont, "\n")] = '\0';
        *pont = atoi(pont);

        if(strlen(pont) > contador) 
            printf("\nNome muito longo\n");

    }while(strlen(pont) > contador);
    strcpy(s, pont);
}

void armazenar( struct aluno * aux, struct aluno ** inicio, struct aluno ** fim){
    struct aluno *ant, *pont;

    if(*fim == NULL){
        aux -> proximo = NULL;
        aux -> ant = NULL;
        *fim = aux;
        *inicio = aux;
        return;
    }
    pont = *inicio; // TOPO DA LISTA

    ant = NULL;
    while(pont){
        if(strcmp(pont->aluno_nome, aux->aluno_nome) < 0) {
            ant = pont;
            pont = pont->proximo;
        }else{
            if(pont->ant){
                pont->ant->proximo = aux;
            aux->                = pont;
                aux->ant = pont->ant;
                pont->ant = aux;
                return;
            }
            aux->proximo = pont; // NOVO PRIMEIRO ELEMENTO
            aux->ant = NULL;
            pont->ant = aux;
            *inicio = aux;
            return;
        }
    }
    ant->proximo = aux; // insere no fim
    aux->proximo = NULL;
    aux->ant = ant;
    *fim = aux;
}

// void deletar(struct aluno ** inicio, struct aluno ** fim){
//     struct aluno * info, *encontrar();
//     char s[51];
//     printf("Insira o nome:\n");
//     info = encontrar(s);
//     if(info){
//         if (*inicio == info) {
//             *inicio = info->proximo;
//             if(*inicio) (*inicio) -> ant = NULL;
//             else *fim = NULL;
//         }else{
//             info -> ant -> proximo = info -> proximo;
//             if(info!=*fim)
//                 info -> proximo -> ant = info -> ant;
//             else
//                 *fim = info -> ant;
//         }
//         free(info); // DEVOLVE MEMÓRIA PARA O SISTEMA
//     }
// }

struct aluno* encontrar(char* aluno_nome) {
    struct aluno* info = inicio;

    while (info != NULL) {
        if (strcmp(aluno_nome, info->aluno_nome) == 0) {
            return info;
        }
        info = info->proximo;
    }

    return NULL;  // RETORNA NULL CASO NÃO SEJA ENCONTRADO
}

void listar(void){
    struct aluno * info;

    info = inicio; 
    while(info){
        display(info);
        info = info -> proximo; // OBTENDO O proximo ENDEREÇO     
    }
    printf("\n\n");
}

void display(struct aluno* info) {
    printf("Nome: %s\n", info->aluno_nome);
    printf("Turno: %s\n", info->turno);
    printf("Turma: %s\n", info->turma);
    printf("Matricula: %s\n", info->matricula);
    printf("\n");
}

void buscar(void){
    char aluno_nome[51];
    struct aluno *info, *encontrar();

    printf("Nome do aluno: ");
    gets(aluno_nome);
    info = encontrar(aluno_nome);
    if(!info)
        printf("Nenhum resultado\n");
    else
        display(info);
}