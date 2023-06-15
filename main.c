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

int opcao_tu;

int main()
{
    
    system("color 9f");
	int opcao_tp;
	do{
		system("cls");
		printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t==========MENU INICIAL==========\n\t\t\t\t\t\t--------------------------------\n");
		showdata();
		printf("\n\t\t\t\t\t\t-------------------------------- \n");
		printf("\t\t\t\t\t\t1- Turnos \n\t\t\t\t\t\t2- Sair\n");
		printf("\t\t\t\t\t\t================================ \n");
		printf("\t\t\t\t\t\tescolha uma opcao: ");
		scanf("%d", &opcao_tp);
		switch(opcao_tp){
			case 1:
				do{
					system("cls");
					printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t==========TURNOS==========\n\t\t\t\t\t\t--------------------------\n");
					showdata();
					printf("\n\t\t\t\t\t\t--------------------------\n");
					printf("\t\t\t\t\t\t 1- Manha \n\t\t\t\t\t\t 2- Tarde \n\t\t\t\t\t\t 3- Noite \n\t\t\t\t\t\t 4- Integral \n\t\t\t\t\t\t 5- Voltar\n");
					printf("\t\t\t\t\t\t==========================\n");
					printf("\t\t\t\t\t\tescolha uma opcao: ");
					scanf("%d", &opcao_tu);
					switch(opcao_tu){
						case 1:
							manha();
							break;
						case 2:
							tarde();
							break;
						case 3:
							noite();
							break;
						case 4:
							integral();
							break;
						case 5:
							break;
						}
						break;
				}while(opcao_tu != 5);
			case 2:
				exit(0);
				break;
		}
	}while(opcao_tp != 2);

    return 0;
}


void showdata()
{
    int diaatual, mesatual, anoatual;
    struct tm *local;
    time_t temp;
    temp= time(NULL);
    local= localtime(&temp);
    diaatual= local -> tm_mday;
    mesatual= local -> tm_mon+1;
    anoatual= local -> tm_year+1900;
    printf("\t\t\t\t\t\tDATA:  %d/%d/%d", diaatual, mesatual, anoatual);
}

void manha(){
	int opcao_m;
	do{
		system("cls");
		printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t==========MANHA==========\n\t\t\t\t\t\t-------------------------\n");
		showdata();
		printf("\n\t\t\t\t\t\t-------------------------\n");
		printf("\t\t\t\t\t\t 1- Series\n\t\t\t\t\t\t 2- Cadastrar\n\t\t\t\t\t\t 3- Procurar Aluno\n\t\t\t\t\t\t 4- Voltar\n");		printf("\t\t\t\t\t\t========================\n");
		printf("\t\t\t\t\t\tescolha uma opcao: ");
		scanf("%d", &opcao_m);
		switch(opcao_m){
			case 1:
				system("cls");
				
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
	}while(opcao_m != 6);
}

void tarde(){
	int opcao_t;
	do{
		system("cls");
		printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t==========TARDE==========\n\t\t\t\t\t\t-------------------------\n");
		showdata();
		printf("\n\t\t\t\t\t\t-------------------------\n");
		printf("\t\t\t\t\t\t 1- Series\n\t\t\t\t\t\t 2- Cadastrar\n\t\t\t\t\t\t 3- Procurar Aluno\n\t\t\t\t\t\t 4- Voltar\n");		printf("\t\t\t\t\t\t========================\n");
		printf("\t\t\t\t\t\tescolha uma opcao: ");
		scanf("%d", &opcao_t);
		switch(opcao_t){						
			case 1:
				system("cls");
				
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
	}while(opcao_t != 6);
}

void noite(){
	int opcao_n;
	do{
		system("cls");
		printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t==========NOITE==========\n\t\t\t\t\t\t-------------------------\n");
		showdata();
		printf("\n\t\t\t\t\t\t-------------------------\n");
		printf("\t\t\t\t\t\t 1- Series\n\t\t\t\t\t\t 2- Cadastrar\n\t\t\t\t\t\t 3- Procurar Aluno\n\t\t\t\t\t\t 4- Voltar\n");		printf("\t\t\t\t\t\t========================\n");
		printf("\t\t\t\t\t\tescolha uma opcao: ");
		scanf("%d", &opcao_n);
		switch(opcao_n){
			case 1:
				system("cls");
				
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
	}while(opcao_n != 6);
}

void integral(){
	int opcao_i;
	do{
		system("cls");
		printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t==========INTEGRAL==========\n\t\t\t\t\t\t-------------------------\n");
		showdata();
		printf("\n\t\t\t\t\t\t-------------------------\n");
		printf("\t\t\t\t\t\t 1- Series\n\t\t\t\t\t\t 2- Cadastrar\n\t\t\t\t\t\t 3- Procurar Aluno\n\t\t\t\t\t\t 4- Voltar\n");
		printf("\t\t\t\t\t\t========================\n");
		printf("\t\t\t\t\t\tescolha uma opcao: ");
		scanf("%d", &opcao_i);
		switch(opcao_i){
			case 1:
				system("cls");
				
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
	}while(opcao_i != 4);
}

void cadastrar(){
	int opcao_r;
	do{
		system("cls");
		printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t========CADASTRAR========\n\t\t\t\t\t\t-------------------------\n");
		showdata();
		printf("\n\t\t\t\t\t\t-------------------------\n");
		printf("\t\t\t\t\t\t 1- Estudane \n\t\t\t\t\t\t 2- Classe \n\t\t\t\t\t\t 3- Voltar\n");
		printf("\t\t\t\t\t\t=========================\n");
		printf("\t\t\t\t\t\tescolha uma opcao: ");
		scanf("%d", &opcao_r);
		switch(opcao_r)
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
	}while(opcao_r != 3);
}

void procurar(){
	int opcao_p;
	do{
		system("cls");
		printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t==========PROCURAR==========\n\t\t\t\t\t\t---------------------------\n");
		showdata();
		printf("\n\t\t\t\t\t\t-------------------------\n");
		printf("\t\t\t\t\t\t 1- Estudante \n\t\t\t\t\t\t 2- Classe \n\t\t\t\t\t\t 3- Voltar\n");
		printf("\t\t\t\t\t\t=========================\n");
		printf("\t\t\t\t\t\tescolha uma opcao: ");
		scanf("%d", &opcao_p);
		switch(opcao_p)
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
	}while(opcao_p != 3);
}