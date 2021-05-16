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

//=============================================================================================================================================
//Arquivo.h
//=============================================================================================================================================
//DECLARACAO DE ESTRUTURAS:

//cria a estrutura de um assento e também uma chave para identificar um passageiro em um Voo(Lista).
typedef struct assento{
	unsigned int fila;
	unsigned int cadeira;
}ASSENTO;

//Cria a estrutura de uma passagem.
typedef struct {
    unsigned int cod;
    char nomePassageiro[50];
    char rg[10];
    char telefone[20];
    char email[50];
    ASSENTO poltrona;
    float valor;
}REGISTRO;


//Cria o Elemento PASSAGEM, onde cada PASSAGEM tem os dados do Passageiro(REGISTO) e tem a localização da próxima PASSAGEM.
typedef struct aux{
    REGISTRO reg;
    struct aux *prox;
}PASSAGEM;


//Criando um novo nome para um Ponteiro de PASSAGEM. Agora, ApontadorPassagem é um ponteiro para uma estrutura do Tipo PASSAGEM.
typedef PASSAGEM *ApontadorPassagem;


//A estrutura Voo além de guardar as informações do voo, também guarda uma lista de passageiros, assim, voo é uma lista.
typedef struct{
    ApontadorPassagem inicio;
	unsigned int numeroVoo;
    int qtdePoltronas;
    char data[11];
	char horario[6];
    char origem[20];
    char destino[20];
}VOO;


//DECLARACAO DE PROTOTIPOS:
void limparBuffer();

int inicializarVooVazio(VOO *v);

int inicializarVoo(VOO *v);

void inicializarAssentos(VOO *v, ASSENTO a[]);

void reservarCadeira(ASSENTO a[], unsigned int ca);

void exibirPoltronasDisponiveis(VOO *v, ASSENTO a[]);

ApontadorPassagem buscaSequencialAux(VOO *v, unsigned int ca, ApontadorPassagem *ant);

int inserirElemListaOrd(VOO *v, REGISTRO reg);

int venderPassagem(VOO *v, ASSENTO a[]);

void exibirVoo(VOO *v);

void exibirRelatorioVendas(VOO *v);

ApontadorPassagem buscaSequencial(VOO *v, unsigned int cadeira);

void consultarPassageiro(VOO *v);

void exibirListaPassageiros(VOO *v);

void menuInicial();

int menuOpcao();





//=============================================================================================================================================
//Arquivo.c
//=============================================================================================================================================
//função auxiliar para limpar o lixo do buffer de entrada do teclado
void limparBuffer(){
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}

//função criada apenas para auxiliar no desenvolvimento e testes do sistem, quando o sistema estiver finalizado, essa função será deletada
int inicializarVooVazio(VOO *v){
    v->qtdePoltronas = 40;
    return v->qtdePoltronas;
}

//função para poder inicializar um voo com todos os dados necessários do Voo. 
int inicializarVoo(VOO *v){

    v->inicio = NULL;
    int i;
    char caractere;

    printf("\nPREENCHA OS DADOS DA VOO\n\n");
    printf("Insira o numero do voo: ");
    scanf("%u", &(v->numeroVoo));
    limparBuffer();
    printf("\n");
    
    printf("Insira a quantidade de poltronas disponiveis para o voo: ");
    scanf("%d", &(v->qtdePoltronas));
    limparBuffer();
    printf("\n");
    
    // O comandos Whiles utilizados abaixo, foram feitos para poder pegar as informações do cliente.
    printf("Qual a data do voo: ");
    i = 0;
        do{
            caractere = getchar();
            v->data[i] = caractere;
            i++;
        }while( caractere != '\n');
        v->data[i - 1] = '\0';
    printf("\n");

    printf("Qual o horario do voo: ");
    i = 0;
        do{
            caractere = getchar();
            v->horario[i] = caractere;
            i++;
        }while( caractere != '\n');
        v->horario[i - 1] = '\0';
    printf("\n");
    
    printf("Qual o local de origem do voo: ");
    i = 0;
        do{
            caractere = getchar();
            v->origem[i] = caractere;
            i++;
        }while( caractere != '\n');
        v->origem[i - 1] = '\0';
    printf("\n");

    printf("Qual o local de destino do voo: ");
    i = 0;
        do{
            caractere = getchar();
            v->destino[i] = caractere;
            i++;
        }while( caractere != '\n');
        v->destino[i - 1] = '\0';
    printf("\n");
    
    printf("\nVOO INICIALIZADO COM SUCESSO\n");
    system("pause");
    
    //retorando a quantidade de poltronas que o Voo vai ter para poder ser criada a função que mostra as Poltronas disponíveis
    return v->qtdePoltronas;
}

//Essa função inicializa todos os assentos com 0. Assentos com 0 no seu valor, indique que o assento está disponível. 
void inicializarAssentos(VOO *v, ASSENTO a[]){

    int i = 0;
    while(i < v->qtdePoltronas){
        a[i].cadeira = 0;
        i++;
    }
}

//Essa função realizada a mudança do valor de uma cadeira de 0 para 1, isso faz com o que o assento fique ocupado.
void reservarCadeira(ASSENTO a[], unsigned int ca){
    a[ca].cadeira = 1;
}

//Essa função exibe todas as poltronas de um voo, se a poltrona estiver Disponível, ela mostra o número da Pontrona, se estiver ocupada mostra (XXXX)
void exibirPoltronasDisponiveis(VOO *v, ASSENTO a[]){
    int i = 1;
    int j = 2;

    system("cls");
    printf("\n\tPAINEL DE OCUPACOES\n\n");
    printf("        1       2       3       4\n");
    printf(" 1: ");

    i = 1;
    j = 2;
    while(i <= v->qtdePoltronas){

        if(a[i].cadeira == 0){
            if(i < 10){
                printf(" (  %i ) ", i);
            }else{
                printf(" ( %i ) ", i);
            }

        }else{
                printf(" (XXXX) ");
        }

        if(i == v->qtdePoltronas){

        }else{
            if(i % 4 == 0){

                printf("\n");

                    if(j < 10){
                        printf(" %d: ", j);
                    }else{
                        printf("%d: ", j);    
                    }
                j++;
             }
        }
        i++;
    }   
    printf("\n\n");
}

//Essa função auxilia na inserção e remoção de Passagens, Ela verifica se a passagem já existe basedo em uma chave, que aqui é o número da Cadeira
ApontadorPassagem buscaSequencialAux(VOO *v, unsigned int ca, ApontadorPassagem *ant){
    *ant = NULL;
    ApontadorPassagem atual = v->inicio;
    while((atual != NULL) && (atual->reg.poltrona.cadeira < ca)){
        *ant = atual;
        atual = atual->prox;
    }
    if((atual != NULL) && (atual->reg.poltrona.cadeira == ca))
        return atual;
    return NULL;
}

//função para inserir uma passagem no Lista de voo, Essa função é ordenada e sua ordenação é pela cadeira do voo.
int inserirElemListaOrd(VOO *v, REGISTRO reg){
    
    unsigned int ca = reg.poltrona.cadeira;

    ApontadorPassagem ant, i;
    i = buscaSequencialAux(v, ca, &ant);
    if(i != NULL)
        return FALSE;
    i = (ApontadorPassagem) malloc(sizeof(PASSAGEM));
    i->reg = reg;
    if(ant == NULL){
        i->prox = v->inicio;
        v->inicio = i;
    }else{
        i->prox = ant->prox;
        ant->prox = i;
    }
    return TRUE;
}

//Função para realizar a venda de uma Passagem.
int venderPassagem(VOO *v, ASSENTO a[]){

    //registro criado temporariamente para armazenar os dados de entrada da nova passagem.
    REGISTRO reg;
    int i, res;
    char caractere;

    //PEGANDO OS DADOS DO CLIENTE
    // O comandos Whiles utilizados abaixo, foram feitos para poder pegar as informações do cliente.
    printf("\nPREENCHA OS DADOS DA PASSAGEM\n");
    printf("Insira o codigo da passagem: ");
    scanf("%u", &(reg.cod));
    limparBuffer();
    printf("\n");

    printf("Qual o nome do passageiro: ");
        i = 0;
        do{
            caractere = getchar();
            reg.nomePassageiro[i] = caractere;
            i++;
        }while( caractere != '\n');
        reg.nomePassageiro[i - 1] = '\0';
    printf("\n");

    
    printf("RG do passageiro: ");
        i = 0;
        do{
            caractere = getchar();
            reg.rg[i] = caractere;
            i++;
        }while( caractere != '\n');
        reg.rg[i - 1] = '\0';
    printf("\n");


    printf("Qual o telefone do passageiro: ");
        i = 0;
        do{
            caractere = getchar();
            reg.telefone[i] = caractere;
            i++;
        }while( caractere != '\n');
        reg.telefone[i - 1] = '\0';
    printf("\n");


    printf("Qual o e-mail do passageiro: ");
        i = 0;
        do{
            caractere = getchar();
            reg.email[i] = caractere;
            i++;
        }while( caractere != '\n');
        reg.email[i - 1] = '\0';
    printf("\n");

    printf("Insira o valor da passagem: R$");
    scanf("%f", &(reg.valor));
    printf("\n");

    exibirPoltronasDisponiveis(v, a);
    printf("\n\tESCOLHA SUA POLTRONA: \n");
    printf("Escolha a Fileira: ");
    scanf("%u",&(reg.poltrona.fila));
    printf("\nEscolha a cadeira: ");
    scanf("%u",&(reg.poltrona.cadeira));


    //inserindo Passagem na Lista de Voo
    res = inserirElemListaOrd(v, reg);

    //Retirando dos Assentos disponíveis a cadeira comprada
    reservarCadeira( a, reg.poltrona.cadeira);



    //um print da passagem que acabou de ser vendida
    system("cls");
    printf("\nPASSAGEM REGISTRADA COM SUCESSO\n");
    printf("DADOS DA PASSAGEM:\n\n");
    printf("Codigo: %u\n", reg.cod);
    printf("Nome Passageiro: %s\n", reg.nomePassageiro);
    printf("RG: %s\n", reg.rg);
    printf("Telefone: %s\n", reg.telefone);
    printf("Email: %s\n", reg.email);
    printf("Valor Da Passagem: %.2f\n", reg.valor);
    printf("Poltrona Escolhida:\n");
    printf("Fileira: %u, Cadeira: %u\n\n", reg.poltrona.fila, reg.poltrona.cadeira);

    return 1;
}

//Função que exibe os dados de um voo, ela não exibe os passageiros.
void exibirVoo(VOO *v){
    printf("\n DADOS DO VOO\n");
    printf(" Numero do Voo: %d\n", v->numeroVoo);
    printf(" Quantidade De poltronas: %d\n", v->qtdePoltronas);
    printf(" Data: %s\n", v->data);
    printf(" Horario: %s\n", v->horario);
    printf(" Origem: %s\n", v->origem);
    printf(" Destino: %s\n\n", v->destino);
}

//Função que realiza a soma do valor de todas as passagens vendidas e exibe um relatório do Voo com o valor total das passagens.
void exibirRelatorioVendas(VOO *v){

     ApontadorPassagem end = v->inicio;
     float valorTotal = 0;

    while (end != NULL){
        valorTotal+= end->reg.valor;
        end = end->prox;
    }
        
    printf("\t\tRELATORIO DE VENDAS:\n\n");    
    printf(" Numero do Voo: %d\n", v->numeroVoo);
    printf(" Origem: %s\n", v->origem);
    printf(" Destino: %s\n", v->destino);
    printf(" Data: %s\n", v->data);
    printf(" Horario: %s\n", v->horario);
    printf(" Valor arrecadado: %.2f\n", valorTotal);
    printf("\n");
}

//função que realiza um busca sequencial pela cadeira do Passageiro.
ApontadorPassagem buscaSequencial(VOO *v, unsigned int cadeira){
    ApontadorPassagem pos = v->inicio;
    while(pos != NULL){
        if(pos->reg.poltrona.cadeira == cadeira)
            return pos;
            pos = pos->prox;
    }
    return NULL;
}

//Funcão que exibe as informações de um dado passageiro baseada na cadeira que ele escolheu.
void consultarPassageiro(VOO *v){

    ApontadorPassagem end;
    unsigned int cadeira;

    printf("\t\t CONSULTAR UM PASSAGEIRO\n\n");
    printf("Digite o numero da cadeira do Passageiro: ");
    scanf("%u", &cadeira);

    end = buscaSequencial(v, cadeira);

    if(end == NULL){
        printf("\n\tPASSAGEIRO NAO ENCONTRADO\n");
        printf("\t=========================\n\n");
    }else{
        printf("\n\nDADOS DO PASSAGEIRO:\n\n");
        printf("Nome: %s\n", end->reg.nomePassageiro);
        printf("RG: %s\n", end->reg.rg);
        printf("TELEFONE: %s\n", end->reg.telefone);
        printf("E-MAIL: %s\n", end->reg.email);
        printf("Cadeira: %u\n", end->reg.poltrona.cadeira);
        printf("Fileira: %u\n\n", end->reg.poltrona.fila);
    }

}

//Função para exibir a lista de passageiros do Voo. Essa lista é exibida pela ordem crescente. Essa ordem é baseada nas poltronas.
void exibirListaPassageiros(VOO *v){
    ApontadorPassagem end = v->inicio;
    printf("\t\tLISTA DOS PASSAGEIROS:\n");
    while (end != NULL){

        printf("Cod: %u\n", end->reg.cod);
        printf("Nome: %s\n", end->reg.nomePassageiro);
        printf("RG: %s\n", end->reg.rg);
        printf("TELEFONE: %s\n", end->reg.telefone);
        printf("E-MAIL: %s\n", end->reg.email);
        printf("Valor Da Passagem: %.2f\n", end->reg.valor);
        printf("Poltrona Escolhida:\n");
        printf("Fileira: %u, Cadeira: %u\n\n", end->reg.poltrona.fila, end->reg.poltrona.cadeira);
        end = end->prox;
    }
    printf("\n");
}

//Função Inicial do sitema, ela é necessário para explicar para o usuario que precisa criar um voo antes de qualquer outra ação.
void menuInicial(){
    system("cls");
    printf("\n\t\t\t\t     *** BEM VINDO AO SVPA ***\n\n");
    printf("\t\t\t =.= SISTEMA DE VENDAS DE PASSAGENS DE AVIAO =.=\n\n\n\n");
    printf("\t\tPARA UTILIZACAO DO SISTEMA E NECESSARIO REALIZAR O CADASTRO DO VOO \n");
    printf("\t\t------------------------------------------------------------------\n\n\n");
    
}

//Função de navegação do menu principal
int menuOpcao(){
    int opcao=0;
    do {
         system("cls"); 
         printf("\n\n                      MENU   \n\n");
        
         printf("\t\t 1- Exibir informa%c%ces do Voo \n\n",	135, 228);
        
         printf("\t\t 2- Vender Passagem \n\n");
        
         printf("\t\t 3- Relat%crio de Vendas \n\n", 162);
        
         printf("\t\t 4- Consultar Passageiro \n\n");
         
         printf("\t\t 5- Listar Passageiros\n\n");
         
         printf("\t\t 6- Mostrar Painel De Ocupa%c%ces do Voo\n\n", 135, 228);
         
         printf("\t\t 7- Sair\n\n");
        
         printf("\t\t\t op%c%co: ", 135, 198);
         scanf("%d",&opcao);
         
         if(opcao <= 0 || opcao > 7){
            printf("\n\n\n DIGITE APENAS VALORES CORESPONDENTES AO MENU!!!");
            getch();
         }
            
     }while(opcao <= 0 || opcao > 7);
    
    system("cls");

    return opcao;
}





//=============================================================================================================================================
//SistemaVendaPassagensAviao.c
//=============================================================================================================================================

int main(){
	VOO v;
	int opcao;
	int loopContinue = TRUE;
    int poltronas;
    //int teste;
	
    //Menu inicial do sistema. Boas vindas.
    menuInicial();

    //inicializando um Voo
    poltronas = inicializarVoo(&v);

    //Informando para o sistema quantas poltronas vão ter o Voo.
    ASSENTO a[poltronas];

    //Realizando a inicialização dos assentos com 0. Isso indica que estão disponíveis.
    inicializarAssentos(&v, a);

	do{
     system("cls");              
     opcao = menuOpcao();                  
     switch(opcao){
        case 1: 	
			exibirVoo(&v);

            system("pause");
			system("cls"); 
			break;
					
		case 2:		
			venderPassagem(&v, a);

            system("pause");
			system("cls"); 
			break;

					
		case 3:     
            exibirRelatorioVendas(&v);

            system("pause");
			system("cls"); 
			break;
					
		case 4: 	
			consultarPassageiro(&v);

            system("pause");
			system("cls"); 
			break;
					
		case 5:     
            exibirListaPassageiros(&v);

            system("pause");
			system("cls"); 
			break;
					
		case 6: 
            exibirPoltronasDisponiveis(&v, a);
            printf("LEGENDA:\n");
            printf("Poltronas que aparecem os numeros, estao disponiveis\n");
            printf("Poltronas que aparecem (XXXX), estao ocupadas\n\n");

            system("pause");
			system("cls"); 
			break;

		case 7:		
			system("cls");
			printf("ENCERRANDO O PROGRAMA\n");
			loopContinue=FALSE;
     }
	}while(loopContinue);

	return 0;
}
