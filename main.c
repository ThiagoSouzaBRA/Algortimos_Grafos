/* 
 * REPRESENTACAO DE GRAFOS - Versao 2021/1
 * Thiago Rodrigues de Souza
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <memory.h>

/* 
 * Estrutura de dados para representar grafos
 */
typedef struct a{ /* Celula de uma lista de arestas */
	int    nome;
	struct a *prox;
}Aresta;

typedef struct vert{  /* Cada vertice tem um ponteiro para uma lista de arestas incidentes nele */
	int nome;
	int marca;
	Aresta *prim;
}Vertice;

/*
 * Declaracoes das funcoes para manipulacao de grafos 
 */
void criaGrafo(Vertice **G, int ordem);
void destroiGrafo(Vertice **G, int ordem);
int  acrescentaAresta(Vertice G[], int ordem, int v1, int v2);
int  calculaTamanho(Vertice G[], int ordem);
void imprimeGrafo(Vertice G[], int ordem);
int eConexo(Vertice G[], int ordemG);
int eArvore(Vertice G[], int ordem);

/*
 * Implementacao das funcoes para manipulacao de grafos 
 */
 
/*
 * Criacao de um grafo com ordem predefinida (passada como argumento),
 *   e, inicilamente, sem nenhuma aresta 
 */
void criaGrafo(Vertice **G, int ordem){
	int i;
	*G= (Vertice*) malloc(sizeof(Vertice)*ordem); /* Alca�ao dinamica de um vetor de vertices */
	
	for(i=0; i<ordem; i++){
		(*G)[i].nome= i;
		(*G)[i].marca= 0; /* representa nao manipulado*/
		(*G)[i].prim= NULL;    /* Cada vertice sem nenua aresta incidente */
	}
}

/*
 * Deasaloca a memoria dinamica usada para armazenar um grafo.
 */
void destroiGrafo(Vertice **G, int ordem){
	int i;
    Aresta *a, *n;
    
	for(i=0; i<ordem; i++){ /* Remove lista de adjacencia de cada v�rtice */
	    a= (*G)[i].prim;
        while (a!= NULL){
              n= a->prox;
              free(a);
              a= n;
        }
	}
    free(*G);
}

/*  
 * Acrescenta uma nova aresta em um grafo previamente criado. 
 *   Devem ser passados os extremos v1 e v2 da aresta a ser acrescentada 
 * Como o grafo n�o � orientado, para uma aresta com extremos i e j
 *   ser�o criadas, na estrutura de dados, arestas (i,j) e (j,i)
 */
int acrescentaAresta(Vertice G[], int ordem, int v1, int v2){
    Aresta * A1, *A2;
    
	if (v1<0 || v1 >= ordem) /* Testo se v�rtices sao validos */
	   return 0;
	if (v2<0 || v2 >= ordem)
	   return 0;
	
	/* Acrescento aresta na lista do vertice v1 */
	A1= (Aresta *) malloc(sizeof(Aresta));
	A1->nome= v2;
	A1->prox= G[v1].prim;
	G[v1].prim= A1;

	/* Acrescento aresta na lista do vertice v2 se v2 != v1 */
	if (v1 == v2) return 1;
	
	A2= (Aresta *) malloc(sizeof(Aresta));
	A2->nome= v1;
	A2->prox= G[v2].prim;
	G[v2].prim= A2;
	
	return 1;
}

/*  
 * Funcao que retorna o tamanho de um grafo
 */
int  calculaTamanho(Vertice G[], int ordem){
	int i;
	int totalArestas=0;
	
	for (i=0; i<ordem; i++){
		int j;
		Aresta *aux= G[i].prim;
		for(j=0; aux != NULL; aux= aux->prox, j++)
            if (aux->nome == i) j++; /* laco "conta em dobro" */
		totalArestas += j;	
	}
	return totalArestas/2 + ordem;
}

int eArvore(Vertice G[], int ordem){
	int i;
	int totalArestas=0;
	
  int contVertices = 0;

	for (i=0; i<ordem; i++){
		int j;
		Aresta *aux= G[i].prim;
    if(G[i].prim != NULL){
      contVertices++;
    }
		for(j=0; aux != NULL; aux= aux->prox, j++)
            if(aux->prox != NULL){
              if (aux->nome == i) j++; /* laco "conta em dobro" */
            }
           
		totalArestas += j;	
	}

	return (contVertices > ((totalArestas/2)-1));
}

/*  
 * Imprime um grafo com uma nota��o similar a uma lista de adjac�ncia.
 */
void imprimeGrafo(Vertice G[], int ordem){
	int i;
	Aresta *aux;

	printf("\nOrdem:   %d",ordem);
	printf("\nLista de Adjacencia:\n");

	for (i=0; i<ordem; i++){
		printf("\n    V%d (Marca:%d): ", i, G[i].marca);
		aux= G[i].prim;
		for( ; aux != NULL; aux= aux->prox)
			printf("%3d", aux->nome);
	}
	printf("\n\n");
}

int eConexo(Vertice G[], int ordemG){
  int verticeEscolhido = 5;

  Aresta *arestaAux; //Auxiliar utilizado para percorrer o Grafo
  int flag = 1;

  G[verticeEscolhido].marca = 1;

  while(flag == 1){
    flag = 0;
    for (int i=0; i< ordemG ; i++){
      arestaAux= G[i].prim;
      for( ; arestaAux != NULL; arestaAux= arestaAux->prox){

        if(G[i].marca == 1 && G[arestaAux->nome].marca == 0){
          flag = 1;
          G[arestaAux->nome].marca = 1;
        }else if(G[i].marca == 0 && G[arestaAux->nome].marca == 1)
        {
          flag = 1;
          G[i].marca = 1;
        }
      }
    }
  }

	int ehConexo = 1;
  for(int j=0; j < ordemG; j++){
  if(G[j].marca == 0 && G[j].prim != NULL){
    ehConexo = 0;
  }
}
return ehConexo;
}



/*
 * Programinha simples para testar a representacao de grafo
 */
int main(int argc, char *argv[]) {
	Vertice *G;
	int ordemG= 7;

  

  //Registrando as conexoes
	criaGrafo(&G, ordemG);
  acrescentaAresta(G,ordemG,0,0);
	acrescentaAresta(G,ordemG,3,4);
	acrescentaAresta(G,ordemG,4,3);
	acrescentaAresta(G,ordemG,4,2);
	acrescentaAresta(G,ordemG,5,4);
	acrescentaAresta(G,ordemG,2,3);
	acrescentaAresta(G,ordemG,3,0);



	if(eConexo(G, ordemG) == 1){
    if(eArvore(G, ordemG) == 1){
      printf("\nO Grafo é arvore e conexo.");
    }else{
      printf("\nO Grafo não é arvore mas é conexo.");
    }
  }
  else{
    printf("O Grafo não é conexo.");
  }

  printf("\n");

  imprimeGrafo(G, ordemG); 

	destroiGrafo(&G, ordemG);
    system("PAUSE");
	return 0;
}