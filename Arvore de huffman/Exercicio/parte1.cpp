#include<stdio.h>
#include<conio2.h>
#include<stdlib.h>
#include<string.h>

#define tf 50
struct arvoreh{
	int freq, simbolo;
	struct arvoreh *esq, *dir;
};
typedef struct arvoreh ArvoreH;

struct lista{
	struct arvoreh *no;
	struct lista *prox;
};
typedef struct lista Lista;

struct tabela{
	int simbolo, freq;
	char info[tf], codigo[tf];
	struct tabela *prox;
};
typedef struct tabela Tabela;

ArvoreH *criarNo(ArvoreH *d, int freq, int simbolo,  ArvoreH *e){
	ArvoreH *novo;
	novo = (ArvoreH*)malloc(sizeof(ArvoreH));
	
	novo->simbolo = simbolo;
	novo->freq = freq;
	novo->dir = d;
	novo->esq = e;
	
	return novo;
}

Tabela *CriaNoTab(int simbolo, char info[], int freq, char codigo[]){
	Tabela *novo;
	novo = (Tabela*)malloc(sizeof(Tabela));
	
	novo->simbolo = simbolo;
	novo->freq = freq;
	strcpy(novo->info, info);
	strcpy(novo->codigo, codigo);
	novo->prox = NULL;
	
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

void initLista(Lista **lista){
	*lista = NULL;
}

void initTabela(Tabela **tab){
	*tab = NULL;
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
		if((*lista)->no->freq >= no->freq)
		{
			novo->prox = *lista;
			*lista = novo;
		}
		else
		{
			aux = *lista;
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

Tabela *verifica(Tabela *tab, char aux[]){
	while(tab!= NULL && strcmp(tab->info, aux)!=0)
		tab = tab->prox;
	if(tab==NULL)
		return NULL;
	else
		return tab;
}

void frequencia(Tabela **tab, char info[], int *qtde){
	int i=0, j =0, h;
	char aux[tf];
	Tabela *auxT, *novoNo;
	
	for(h=0; h<tf; h++)
		aux[h] = '\0';
	
	while(i<strlen(info))
	{
		if(info[i] == ' ' || info[i] == '\n')
		{
			auxT = verifica(*tab, aux);
			if(auxT == NULL)
			{
				novoNo = CriaNoTab(*qtde, aux, 1, "");
				insereTabela(&*tab, novoNo);
				(*qtde)++;
			}
			else
				auxT->freq++;
				
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
			printf("%d:   %d\n", lista->no->simbolo, lista->no->freq);
			lista = lista->prox;
		}
		printf("\n\n");
	}
}

void exibe_formato_arvore(ArvoreH *raiz, int x, int y, int dist){
    if(raiz != NULL)
    {
        gotoxy(x, y);
        //if(raiz->esq == NULL && raiz->dir == NULL)
        	//printf("%d ", raiz->simbolo);
       // else
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
	Lista *aux = *lista;
	(*qtde)--;
	*lista = aux->prox;
	return aux;
}

void codigoTab(Tabela **tab, int simbolo, char codigo[]){
	Tabela *aux = *tab;
	
	while(aux != NULL && aux->simbolo != simbolo)
		aux = aux->prox;
	
	if(aux != NULL)
		strcpy(aux->codigo, codigo);
}

void codigo(ArvoreH *raiz, char d[], int *t, Tabela **tab){ //mudar
	if(raiz != NULL)
	{
		if(raiz->esq == NULL && raiz->dir == NULL){
			d[(*t)+1] = '\0';
			codigoTab(&*tab, raiz->simbolo, d);
		}
		else
		{
			(*t)++;
			d[*t] = '0'; 
			codigo(raiz->esq, d, &*t, &*tab);
			d[*t] = '1'; 
			codigo(raiz->dir, d, &*t, &*tab);
			(*t)--;
		}
	}
}

void huffman(Lista **lista, int *qtde){
	Lista *dir, *esq;
	ArvoreH *arvore, *novo;
	while(*qtde > 1)
	{
		esq = retira(&*lista, &*qtde);
		dir = retira(&*lista, &*qtde);
		novo = criarNo(dir->no, esq->no->freq+dir->no->freq, -1, esq->no);
		
		insereLista(&*lista, novo);
		(*qtde)++;
	}
}

void constroiLista(Tabela *tab, Lista **lista){
	ArvoreH *novo;
	while(tab != NULL)
	{
		novo = criarNo(NULL, tab->freq, tab->simbolo, NULL);
		insereLista(&*lista, novo);
		tab = tab->prox;
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

void gravarTab(Tabela *tab){
	FILE *arq = fopen("Tabela.dat", "wb");
	rewind(arq);
	if(tab != NULL)
	{
		while(tab != NULL)
		{
			fwrite(tab, sizeof(Tabela), 1, arq);
			tab = tab->prox;
		}
		fwrite(tab, sizeof(Tabela), 1, arq);
	}
	fclose(arq);
}

void codificarPalavra(Tabela *tab, char info[]){
	Tabela *aux;
	int i=0, j=0, h;
	char palavra[tf];
	
	for(h = 0; h<tf; h++)
		palavra[h] = '\0';
				
	FILE *ptr = fopen("palavra.txt", "w");
	while(i<strlen(info))
	{
		if(info[i] == ' ' || info[i] == '\n')
		{
			aux = verifica(tab, palavra);
			if(aux != NULL){
				printf("%s ", aux->codigo);
				fprintf(ptr, "%s", aux->codigo);
			}
			for(h = 0; h<j; h++)
				palavra[h] = '\0';
			j=0;
		}
		else
			palavra[j++] = info[i];
		i++;
	}
	fclose(ptr);
}

int main(){
	int t=-1;
	char d[tf];
	int qtde = 0;
	
	for(int h=0; h<tf; h++)
		d[h] = '\0';
	
	Lista *lista;
	initLista(&lista);
	Tabela *tab;
	initTabela(&tab);
	
	char frase[300] = "amo como ama o amor nao conheco nenhuma outra razao para amar senao amar que queres que te diga alem de que te amo se o que quero dizer te e que te amo\n";
	
	frequencia(&tab, frase, &qtde);
	constroiLista(tab, &lista);
	huffman(&lista, &qtde);
	codigo(lista->no, d, &t, &tab);
	gravarTab(tab);
	
	exibe_formato_arvore(lista->no, 40, 1, 20);
	gotoxy(5, 15);
	exibeTab(tab);
	
	codificarPalavra(tab, frase);
	printf("\n\n%s", frase);
			
	getch();
}
