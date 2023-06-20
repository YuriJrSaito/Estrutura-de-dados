#include<stdio.h>
#include<conio2.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define tf 50
struct arvoreh{
	char info[tf];
	int freq;
	struct arvoreh *esq, *dir;
};
typedef struct arvoreh ArvoreH;

struct lista{
	struct arvoreh *no;
	struct lista *prox;
};
typedef struct lista Lista;

ArvoreH *criarNo(ArvoreH *d, int freq, char info[],  ArvoreH *e){
	ArvoreH *novo;
	novo = (ArvoreH*)malloc(sizeof(ArvoreH));
	
	strcpy(novo->info,info);
	novo->freq = freq;
	novo->dir = d;
	novo->esq = e;
	
	return novo;
}

void initLista(Lista **lista){
	*lista = NULL;
}

void insereLista(Lista **lista, ArvoreH *no){
	Lista *aux, *novo, *ant;
	novo = (Lista*)malloc(sizeof(Lista));
	novo->prox = NULL;
	novo->no = no;
	
	if(*lista == NULL)
		*lista =  novo;
	else
	{
		if((*lista)->no->freq == no->freq){
			novo->prox = *lista;
			*lista = novo;
		}
		else{
			aux = ant = *lista;
			while(aux != NULL && aux->no->freq < no->freq)
			{
				ant = aux;
				aux = aux->prox;
			}
			ant->prox = novo;
			novo->prox = aux;
			
		}
	}
}

void ordena(Lista **lista, char info[]){
	Lista *aux, *ant;
	
	if(*lista != NULL)
	{
		if(strcmp((*lista)->no->info, info)==0)
		{
			aux = *lista;
			*lista = aux->prox;
			insereLista(&*lista, aux->no);
			free(aux);
		}
		else
		{
			aux = *lista;
			while(aux != NULL && strcmp(aux->no->info, info)!=0)
			{
				ant = aux;
				aux = aux->prox;
			}
			if(aux != NULL)
			{
				ant->prox = aux->prox;
				insereLista(&*lista, aux->no);
				free(aux);
			}
		}
	}
}

Lista *verifica(Lista *lista, char aux[]){

	while(lista!= NULL && strcmp(lista->no->info, aux)!=0)
		lista = lista->prox;
	if(lista==NULL)
		return NULL;
	else
		return lista;
	
}

void frequencia(Lista **lista, char info[], int *qtde){
	int i=0, j =0, h;
	char aux[tf];
	ArvoreH *novo;
	Lista *auxL;
	
	for(h=0; h<tf; h++)
		aux[h] = '\0';
	
	while(i<strlen(info))
	{
		if(info[i] == ' ' || info[i] == '\n')
		{
			auxL = verifica(*lista, aux);
			if(auxL == NULL)
			{
				novo = criarNo(NULL, 1, aux, NULL);
				insereLista(&*lista, novo);
				(*qtde)++;
			}
			else
			{
				auxL->no->freq++;
				ordena(lista, aux);
			}
			
			for(h=0; h<j; h++)
				aux[h] = '\0';
			
			j = 0;
		}
		else
			aux[j++] = info[i];
		i++;
	}
}

void exibe(Lista *lista){
	if(lista == NULL)
		printf("\nLista vazia!");
	else{
		while(lista != NULL)
		{
			printf("%s\t%d\n", lista->no->info, lista->no->freq);
			lista = lista->prox;
		}
		printf("\n\n");
	}
}

void exibe_formato_arvore(ArvoreH *raiz, int x, int y, int dist)
{
    if(raiz != NULL)
    {
        gotoxy(x, y);
        //if(raiz->esq == NULL && raiz->dir == NULL)
        	//printf("%s", raiz->info);
        //else
        	printf("%d", raiz->freq);

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

Lista *retira(Lista **lista, int *qtde){
	(*qtde)--;
	Lista *aux = *lista;
	*lista = aux->prox;
	return aux;
}

void codigo(ArvoreH *raiz, char d[], int *t){
	if(raiz == NULL)
		return;
	if(raiz->esq == NULL && raiz->dir == NULL)
		printf("%s: %.*s\n", raiz->info, (*t)+1,d);
	else
	{
		(*t)++;
		d[*t] = '0'; 
		codigo(raiz->esq, d, &*t);
		d[*t] = '1'; 
		codigo(raiz->dir, d, &*t);
		(*t)--;
	}
}

Lista huffman(Lista **lista, char frase[]){
	Lista *dir, *esq;
	ArvoreH *arvore, *novo;
	
	int qtde=0;
	
	frequencia(&*lista, frase, &qtde);
	gotoxy(5,15);
	//exibe(*lista);
	
	while(qtde > 1)
	{
		esq = retira(&*lista, &qtde);
		dir = retira(&*lista, &qtde);
		novo = (ArvoreH*)malloc(sizeof(ArvoreH));
		
		novo->freq = esq->no->freq + dir->no->freq;
		novo->esq = esq->no;
		novo->dir = dir->no;
		
		insereLista(&*lista, novo);
		qtde++;
	}
}

int main(){
	int t=-1;
	ArvoreH *arvore;
	Lista *lista;
	initLista(&lista);
	char d[tf];
	//char frase[300] = "amo como ama o amor nao conheco nenhuma outra razao para amar senao amar que queres que te diga alem de que te amo se o que quero dizer te e que te amo\n";
	
	char frase[200] = "ai au ao al aj aj am am lk lk lk lk\n";
	
	//char frase[200] = "it was the best of times it was the worst of times\n";
	//char frase[200] = "ae ac ad af at ag ab an aj lm lm lo lo lp lp\n";
	huffman(&lista,frase);
	exibe_formato_arvore(lista->no, 40, 1, 20);
	//printf("\n\n");
	codigo(lista->no, d, &t);
			
	getch();	
}
