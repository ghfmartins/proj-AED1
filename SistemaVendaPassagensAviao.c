/*

Universidade Federal de Goiás - UFG
Instituto de Informática - INF
Algoritmos e Estruturas de Dados 1 - AED

    PROJETO FINAL DA DISCIPLINA

Alunos: GUSTAVO HENRIQUE DE FREITAS MARTINS
	    JOSIMAR MORAIS DOS SANTOS

SVPA - SISTEMA DE VENDAS DE PASSAGENS DE AVIÃO

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAIL 0
//===========================================================
//Arquivo.h
//===========================================================
//DECLARACAO DE ESTRUTURAS:
typedef struct Passagem*  ApontadorPassagem;
typedef struct Registro* ApontadorRegistro;
typedef struct ListaDeVoo* ApontadorLista;

typedef struct assento{
	unsigned int fila;
	char cadeira;
}Assento;

typedef struct passagem{
    unsigned int cod;
    char nomePassageiro[50];
    char rg[10];
    char telefone[20];
    char email[50];
    Assento poltrona;
    float valor;
}Passagem;

typedef struct registro {
	Passagem  passagem;
	ApontadorPassagem proximo;
	ApontadorPassagem anterior;
}Registro;

typedef struct {
	ApontadorRegistro inicio;
	unsigned int qtdePassageiros;
}ListaDeVoo;

typedef struct{
	unsigned int numeroVoo;
    unsigned int qtdePoltronas;
    ApontadorLista passageiros;
    char data[11];
	char horario[6];
    char origem[20];
    char destino[20];
}Voo;

//DECLARACAO DE PROTOTIPOS:
int inicializaListaDeVoo (ApontadorLista l);
int insereNovoRegistroNoInicio (ApontadorLista l, Passagem p);
int iniciaVoo(Voo *v);
int vendePassagem(ApontadorLista l);
int escolheAssento(Assento *a);


//===========================================================
//Arquivo.c
//===========================================================
//DECLARACAO DE METODOS:

int inicializaListaDeVoo (ApontadorLista l){
	l->inicio = NULL;
	l->qtdePassageiros = 0;
	
	return SUCCESS;
}

int insereNovoRegistroNoInicio (ApontadorLista l, Passagem p){
	ApontadorRegistro reg;
	ApontadorRegistro primeiro;
	
	reg = (ApontadorRegistro) malloc (sizeof(Registro));
	primeiro = *l->inicio
	if(reg == NULL) return FAIL;
	else{
		reg->passagem = p;
	}
		
	if((l->qtdePassageiros == 0) {
		reg->anterior = NULL;
		reg->proximo = NULL;
		l->inicio = reg;
	}
	else{
		reg->proximo = l.inicio;
		reg->anterior = NULL;
		primeiro->anterior = *reg;
	}
	
	l->qtdePassageiros ++;
	
	return SUCCESS;
}

int iniciaVoo(Voo *v){
	//*v = (Voo) malloc (sizeof(Voo));
	
	//getchar();
    printf("\nPREENCHA OS DADOS DA VOO\n");
    printf("Insira o numero do voo: ");
    scanf("%u", &(v->numeroVoo));
    printf("\n");
    
    //getchar();
    printf("Insira a quantidade de poltronas disponiveis para o voo: ");
    scanf("%u", &(v->qtdePoltronas));
    printf("\n");
    
    getchar();
    printf("Qual a data do voo: ");
    fgets(v->data, 11, stdin);
    printf("\n");
	
	getchar();
    printf("Qual o horario do voo: ");
    fgets(v->horario, 6, stdin);
    printf("\n");
    
    getchar();
    printf("Qual o local de origem do voo: ");
    fgets(v->origem, 20, stdin);
    printf("\n");

    getchar();
    printf("Qual o local de destino do voo: ");
    fgets(v->destino, 20, stdin);
    printf("\n");
    
    v->passageiros = (ApontadorLista) NULL;
    inicializaListaDeVoo(v->passageiros);
    
    return SUCCESS;
}

int vendePassagem(ApontadorLista l){
	ApontadorPassagem p;
	
	p = (ApontadorPassagem) malloc (sizeof(Passagem));
	
	printf("\nPREENCHA OS DADOS DA PASSAGEM\n");
    printf("Insira o codigo da passagem: ");
    scanf("%u", &(p->cod);
    printf("\n");
    
    getchar();
    printf("Qual o nome do passageiro: ");
    fgets(p->nomePassageiro, 50, stdin);
    printf("\n");
    
    getchar();
    printf("Qual o RG do passageiro: ");
    fgets(p->rg, 10, stdin);
    printf("\n");
    
    getchar();
    printf("Qual o telefone do passageiro: ");
    fgets(p->telefone, 20, stdin);
    printf("\n");
    
    getchar();
    printf("Qual o e-mail do passageiro: ");
    fgets(p->emais, 50, stdin);
    printf("\n");
    
    escolheAssento(p->poltrona);
    
    if(!(insereNovoRegistroNoInicio (l, p))) {
    	printf("\nOperacao falhou!\n");
    	return FAIL;
	}
	else{
		printf("\nPassagem vendida com sucesso!\n");
		return SUCCESS;
	}
}

int escolheAssento(Assento *a){
	printf("\n ESCOLHA O ASSENTO");
	printf("\n Informe o numero fila: ");
    scanf("%u", &(a->fila));
    
    getchar();
    printf("\n Informe a cadeira(A - F): ");
    scanf("%c", &(a->cadeira));
    printf("\n");
    
    return SUCCESS;
}


//===========================================================
//SistemaVendaPassagensAviao.c
//===========================================================

int main(){

    return 0;
}
