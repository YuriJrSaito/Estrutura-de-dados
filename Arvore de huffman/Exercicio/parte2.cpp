#include<stdio.h>
#include<conio2.h>
#include<stdlib.h>
#include<string.h>
#define tf 50

struct tabela{
	int simbolo, freq;
	char info[tf], codigo[tf];
	struct tabela *prox;
};
typedef struct tabela Tabela;

struct arvoreh{
	int simbolo;
	struct arvoreh *esq, *dir;
};
typedef struct arvoreh ArvoreH;

ArvoreH *criarNo(ArvoreH *d, int simbolo,  ArvoreH *e){
	ArvoreH *novo;
	novo = (ArvoreH*)malloc(sizeof(ArvoreH));
	
	novo->simbolo = simbolo;
	novo->dir = d;
	novo->esq = e;
	
	return novo;
}

void insereTabela(Tabela **tabela, Tabela *no){
	Tabela *aux;
	if(*tabela == NULL)
		*tabela = no;
	else
	{
		aux = *tabela;
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = no;
	}
}

void exibeTab(Tabela *tab){
	while(tab != NULL)
	{
		printf("Simbolo: %d\n", tab->simbolo);
		printf("Palavra: %s\n", tab->info);
		printf("Freq: %d\n", tab->freq);
		printf("Codigo: %s\n", tab->codigo);
		printf("\n----------------------------\n");
		tab = tab->prox;
	}
}

void lerTab(Tabela **tab){
	Tabela *novo;
	FILE *arq = fopen("Tabela.dat", "rb");
	rewind(arq);	
	do{
		novo = (Tabela*)malloc(sizeof(Tabela));
		fread(novo, sizeof(Tabela),1 , arq);
		novo->prox = NULL;
		if(!feof(arq))
			insereTabela(&*tab, novo);
	}while(!feof(arq));
	fclose(arq);
}

void exibe_formato_arvore(ArvoreH *raiz, int x, int y, int dist){
    if(raiz != NULL)
    {
        gotoxy(x, y);
        if(raiz->esq == NULL && raiz->dir == NULL)
        	printf("%d ", raiz->simbolo);
        else
        	printf("%d", raiz->simbolo);

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

void montarArvore(Tabela *tab, ArvoreH **raiz){
	int h;
	ArvoreH *no;
	
	if(*raiz == NULL)
		*raiz = criarNo(NULL, -1, NULL);
	while(tab != NULL)
	{
		no = *raiz;
		for(h = 0; h<strlen(tab->codigo); h++)
		{
			if(tab->codigo[h] == '1')
			{
				if(no->dir == NULL)
					no->dir = criarNo(NULL, -1, NULL);
				no = no->dir;
			}
			else
			{
				if(no->esq == NULL)
					no->esq = criarNo(NULL, -1, NULL);
				no = no->esq;
			}
		}
		no->simbolo = tab->simbolo;
		tab = tab->prox;
	}
}

void procura(int simbolo, Tabela *tab){
	if(tab != NULL)
	{
		while(tab != NULL && tab->simbolo != simbolo)
			tab = tab->prox;
		if(tab != NULL)
			printf("%s ", tab->info);
	}
}

void decodifica(ArvoreH *raiz, Tabela *tab){
	ArvoreH *aux = raiz;
	int h;
	char palavra[300];
	
	FILE *ptr = fopen("palavra.txt", "r+");
	fscanf(ptr, "%s", &palavra);
	
	for(h = 0; h<strlen(palavra); h++)
	{
		if(palavra[h] == '1')
			aux = aux->dir;
		else
			aux = aux->esq;
		if(aux->dir == NULL && aux->esq == NULL)
		{
			procura(aux->simbolo, tab);
			aux = raiz;
		}
	}
}

int main(){
	Tabela *tab = NULL;
	ArvoreH *raiz = NULL;
	
	lerTab(&tab);
	//exibeTab(tab);
	montarArvore(tab, &raiz); 
	exibe_formato_arvore(raiz, 40, 1, 20);
	printf("\n\n");
	decodifica(raiz, tab);
	
	return 0;
}
