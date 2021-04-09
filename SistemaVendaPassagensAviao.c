#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

//DECLARACAO DE ESTRUTURAS:
typedef struct {
	int fila;
	char cadeira;
}Assento;

typedef struct passagem{
    unsigned int cod;
    Assento poltrona;
    float valor;
    char nomePassageiro[50];
    char rg[10];
    char telefone[20];
    char email[50];
}Passagem;

typedef struct {
	Passagem passagem;
	passagem* proximo;
	passagem* anterior;
}Elemento;

typedef struct {
	Elemento* inicio;
	unsigned int qtdePassageiros;
}ListaDeVoo;

typedef struct{
    unsigned int qtdePoltronas;
    ListaDeVoo* passageiros;
    char data[11];
	char horario[6];
    char origem[20];
    char destino[20];
    double valor;
}Voo;



