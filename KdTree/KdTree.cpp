#include<stdio.h>
#include<conio2.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define k 2
#define tl 15
// Yuri Saito

struct kdtree{
	int ponto[k];
	struct kdtree *esq, *dir;
};
typedef struct kdtree kdTree;

struct lista{
	struct kdtree *no;
	struct lista *prox;
};
typedef struct lista Lista;

void enqueue(Lista **lista, kdTree *no){
	Lista *aux, *novo = (Lista*)malloc(sizeof(Lista));
	novo->prox = NULL;
	novo->no = no;
	
	if(*lista == NULL)
		*lista = novo;
	else
	{
		aux = *lista;
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novo;
	}
}

kdTree *CriaNo(int x, int y, kdTree *esq, kdTree *dir){
	kdTree *novo = (kdTree*)malloc(sizeof(kdTree));
	
	novo->esq = esq;
	novo->dir = dir;
	novo->ponto[0] = x;
	novo->ponto[1] = y;
	
	return novo;
}

void ordena(int mat[tl][2], int d, int ini, int fim){
	int a,b,i,h;
	for(i=ini; i<fim; i++)
    {
    	for(h=i+1; h<=fim; h++)
    	{
    		if(mat[h][d] < mat[i][d])
    		{
    			a = mat[i][0];
    			b = mat[i][1];
    			
    			mat[i][0] = mat[h][0];
    			mat[i][1] = mat[h][1];
    			
    			mat[h][0] = a;
    			mat[h][1] = b;
    		}
    	}
    }
    /*for(int h = ini; h<=fim; h++)
		printf("%d %d\n", mat[h][0], mat[h][1]);
	printf("\n\n");*/
}

void exibe_formato_arvore(kdTree *raiz, int x, int y, int dist)
{
    if(raiz != NULL)
    {
        gotoxy(x, y);
    	printf("%d|%d", raiz->ponto[0], raiz->ponto[1]);

        if(raiz->esq != NULL)
        {
            gotoxy(x-dist/2, y+1);
            printf("/");
        }
        if(raiz->dir != NULL)
        {
            gotoxy(x+dist/2, y+1);
            printf("\\");
        }
        exibe_formato_arvore(raiz->esq, x-dist, y+2, dist/2);
        exibe_formato_arvore(raiz->dir, x+dist, y+2, dist/2);
        printf("\n");
    }
}

void insereBalanceado(kdTree **raiz, int ini, int fim, int n, int mat[tl][2]){

	if(ini <= fim)
	{
		int d=0,meio=0;
		meio = (ini+fim)/2;
		d = n%k;
		ordena(mat, d, ini, fim);
		
		if(*raiz == NULL)
			*raiz = CriaNo(mat[meio][0], mat[meio][1], NULL, NULL);
			
		insereBalanceado(&(*raiz)->esq, ini, meio-1, n+1, mat);
		insereBalanceado(&(*raiz)->dir, meio+1, fim, n+1, mat);
	}
	
}

void buscaR(kdTree *raiz, Lista **lista, int ponto[2]){
	if(raiz != NULL){
		if(sqrt(pow((ponto[0]-raiz->ponto[0]),2) + pow((ponto[1]-raiz->ponto[1]),2)) <= 10)
			enqueue(&*lista, raiz);
		
		buscaR(raiz->esq, &*lista, ponto);
		buscaR(raiz->dir, &*lista, ponto);
	}
}

void exibeLista(Lista *lista, int ponto[2]){
	printf("\nPontos mais proximos do ponto %d,%d com raio 10\n", ponto[0], ponto[1]);
	if(lista == NULL)
		printf("Nenhum ponto!!");
	else{
		while(lista != NULL)
		{
			printf("%d %d\n", lista->no->ponto[0], lista->no->ponto[1]);
			lista = lista->prox;
		}
	}
}

int main(){
	kdTree *raiz = NULL;
	Lista *lista = NULL;
	int mat[tl][2];
	int ponto[2];
	srand(time(NULL));
	
	for(int i=0; i<tl; i++)
	{
		mat[i][0] = rand() % 50;
		mat[i][1] = rand() % 50;
	}
	
	insereBalanceado(&raiz, 0, tl-1, 0, mat);
	exibe_formato_arvore(raiz, 40, 1, 20);	
	
	ponto[0] = rand() % 50;
	ponto[1] = rand() % 50;
		
	buscaR(raiz, &lista, ponto);
	exibeLista(lista, ponto);
	
	return 0;
}
