#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<string.h>
#include<windows.h>
#include<conio.h>

/*A linguagem C não foi projetada para processadores de arquitetura Harvard com espaços de memória separados.
Isso significa que existem várias formas não padronizadas de definir uma variável cujos dados residem na
Memória de Programa (Flash).*/
#define FLSH gets(l)


int destino, origem, vertices = 0, aresta = 0;
int custo, *custos = NULL;

void algoritmoDijkstra(int vertices,int origem,int destino,int *custos)
{
	int i,v, cont = 0;
	int *ant, *tmp;
	int *vrtces_Cminh_Minimo;     /* vertices para os quais se conhece o caminho minimo */
	double min;
	double custo_Caminho[vertices]; /* vetor com os custos dos caminhos */


	/* aloca as linhas da matriz */
	ant = calloc (vertices, sizeof(int *));
	tmp = calloc (vertices, sizeof(int *));
	if (ant == NULL) {
		printf ("** Erro: Memoria Insuficiente **");
		exit(-1);
	}

	vrtces_Cminh_Minimo = calloc (vertices, sizeof(int *));
	if (vrtces_Cminh_Minimo == NULL) {
		printf ("** Erro: Memoria Insuficiente **");
		exit(-1);
	}

	for (i = 0; i < vertices; i++) {
		if (custos[(origem - 1) * vertices + i] !=- 1) {
			ant[i] = origem - 1;
			custo_Caminho[i] = custos[(origem-1)*vertices+i];
		}
		else {
			ant[i]= -1;
			custo_Caminho[i] = HUGE_VAL;
		}
		vrtces_Cminh_Minimo[i]=0;
	}
	vrtces_Cminh_Minimo[origem-1] = 1;
	custo_Caminho[origem-1] = 0;

	/* Laco principal */
	do {

		/* Encontrando o vertice que deve entrar em vrtces_Cminh_Minimo */
		min = HUGE_VAL;
		for (i=0;i<vertices;i++)
			if (!vrtces_Cminh_Minimo[i])
				if (custo_Caminho[i]>=0 && custo_Caminho[i]<min) {
					min=custo_Caminho[i];v=i;
				}

		/* Calculando as distancias dos novos vizinhos de vrtces_Cminh_Minimo */
		if (min != HUGE_VAL && v != destino - 1) {
			vrtces_Cminh_Minimo[v] = 1;
			for (i = 0; i < vertices; i++)
				if (!vrtces_Cminh_Minimo[i]) {
					if (custos[v*vertices+i] != -1 && custo_Caminho[v] + custos[v*vertices+i] < custo_Caminho[i]) {
					   	custo_Caminho[i] = custo_Caminho[v] + custos[v*vertices+i];
						ant[i] =v;
				   	}
        		}
		}
	} while (v != destino - 1 && min != HUGE_VAL);

	/* Mostra o Resultado da busca */
	if (min != HUGE_VAL) {
        i = destino;
		i = ant[i-1];
		while (i != -1) {
			tmp[cont] = i+1;
			cont++;
			i = ant[i];
		}

		for (i = cont; i > 0 ; i--) {
			printf("%d -> ", tmp[i-1]);
		}
		printf("%d", destino);

		printf(" Custo: %d\n",(int) custo_Caminho[destino-1]);
	}
}

void menu_opcoes(void)
{
    //system("cls");
    printf("\n\n\t BASEANDO NO ALGORITMO DE DIJKSTRA\n ");
    printf("\n\n |==========================================================|"
           "\n |\t <<-- Menu Principal -->>                           |"
           "\n |==========================================================|"
           "\n | Escolha opcao:                                           |"
           "\n |----------------------------------------------------------|\n"
           " |\t a \20 Adicionar A Mapa                               |\n"
	  	   " |\t p \20 Pesquisar Os Menores Caminhos no Mapa          |\n"
	  	   " |\t s \20 Sair do programa                               |"
	  	   " \n |----------------------------------------------------------|\n"
           "\t \20 ");
}

void adicionarMapa(void)
{
	int i, j;

	do {
		printf("\n\n\t Informe o numero dos pontos das cidades (vertices)"
               "\n\t (minimo 2 e maximo 1000): ");
		scanf("%d",&vertices);
	} while (vertices < 2 || vertices > 1000);

	do {
		printf("\n\t Informe o numero das estradas entre as cidades (arestas)"
               "\n\t (minimo 1 e maximo 5000): ");
		scanf("%d",&aresta);
	} while (aresta < 2 || aresta > 5000);

	if (!custos)
		free(custos);
	custos = (int *) malloc(sizeof(int)*vertices*vertices);
	for (i = 0; i <= vertices * vertices; i++)
		custos[i] = -1;

	printf("\n\n\t Informe as Cidades e as distancia entre elas '(em numero inetiros)':\n");
	do {
		do {
			printf("\n\n Cidade Origem (entre 1 a %d ou '0' para cancelar insercao):::::::::::::: ", vertices);
			scanf("%d",&origem);
		} while (origem < 0 || origem > vertices);

		if (origem) {
			do {
				printf("\n Destino da aresta (entre 1 a %d, excepto o %d que eh Origem)::::::::::::: ", vertices, origem);
				scanf("%d", &destino);
			} while (destino < 1 || destino > vertices || destino == origem);

			do {
				printf("\n Distancia (inteiros positivo) das estradas da cidade %d para a cidade %d: ",
						origem, destino);
				scanf("%d",&custo);
			} while (custo < 0);

			custos[(origem-1) * vertices + destino - 1] = custo;
		}
        aresta --;
	} while ((aresta != 0) && (origem != 0));

    /* progress bar */
	int k;
    printf("\n\n\t <<-- Terminando a Insercao do Mapa -->>\n\n");
    for(k = 0; k < 60; k++)
    {
        printf("%c",254);
        Sleep(50);
    }
}

void pesquisar(void)
{
	int i, j,a,b;
	printf("\n\n\t Lista dos Menores Caminhos no Mapa: \n\n");
	printf("\t Entre com a origem: ");
	scanf("%d",&a);
	printf("\n\t Entre com a destino: ");
	scanf("%d",&b);

	printf("\n\n");
    algoritmoDijkstra(vertices, a, b, custos);
    getch();

	printf("\n\n\t <- Pressione ENTER para retornar ao menu principal\n");
}

int main(int argc, char **argv) {
	int i, j;
	char opcao[3], l[50];

	do {

	 	menu_opcoes();
		scanf("%s", &opcao);

		if ((strcmp(opcao, "a")) == 0) {
			adicionarMapa();
		}
		FLSH;

		if ((strcmp(opcao, "p") == 0) && (vertices > 0) ) {
			pesquisar();
			FLSH;
		}

	} while ((strcmp(opcao, "s"))!= 0);
	return 0;
}
