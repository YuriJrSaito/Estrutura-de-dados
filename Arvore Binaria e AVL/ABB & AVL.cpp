#include<stdio.h>
#include<conio2.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

struct tree{
	int info;
	struct tree *esq, *dir;	
};
typedef struct tree Tree;

////////////////////Fila///////////////////////////////
struct fila{
	struct tree *arv;
	struct fila *prox;
};
typedef struct fila Fila;

void initFila(Fila **fila){
	*fila = NULL;
}

int isEmpty(Fila *fila){
	return fila==NULL;
}

void enqueue(Fila **fila, Tree *p){
	Fila *aux, *novo;
	novo = (Fila*)malloc(sizeof(Fila));
	novo->prox = NULL;
	novo->arv = p;
	
	if(*fila == NULL)
		*fila = novo;	
	else{
		aux = *fila;
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novo;
	}
}

void dequeue(Fila **fila, Tree **p){
	if(*fila != NULL){
		*p = (*fila)->arv;
		if((*fila)->prox == NULL)
			*fila = NULL;
		else
			*fila = (*fila)->prox;
	}
}
///////////////////////////////////////////////////////



////////////////////Pilha//////////////////////////////
struct pilha{
	struct tree *arv;
	struct pilha *prox;	
};
typedef struct pilha Pilha;

int isEmpty_Pilha(Pilha *P){
	return P==NULL;
}

void init_Pilha(Pilha **p){
	*p = NULL;
}

void push_Pilha(Pilha **P, Tree *e){
	Pilha *novo = (Pilha*)malloc(sizeof(Pilha)), *aux;
	novo->arv = e;
	novo->prox = NULL;
	if(isEmpty_Pilha(*P))
		*P = novo;
	else{
		novo->prox = *P;
		*P = novo;
	}
}

void pop_Pilha(Pilha **P, Tree **e){
	Pilha *aux;
	if(!isEmpty_Pilha(*P)){
		aux = *P;
		*e = aux->arv;
		*P = aux->prox;
		free(aux);
	}
	else
		*e = NULL;
}
///////////////////////////////////////////////////////


void init(Tree **raiz){
	*raiz = NULL;
}

Tree *CriaNo(int info){
	Tree *no = (Tree*)malloc(sizeof(Tree));
	no->info = info;
	no->dir	= NULL;
	no->esq = NULL;
	return no;
}

void localizaNo(Tree *raiz, int info, Tree **no){ //info do pai // no = pai
	if(raiz != NULL){
		if(raiz->info == info)
			*no = raiz;
		else{
			localizaNo(raiz->esq, info, &(*no));
			if(*no == NULL)
				localizaNo(raiz->dir, info, &(*no));
		}
	}
}

void pre_Ordem(Tree *raiz){
	if(raiz != NULL){
		printf("%d ", raiz->info);
		pre_Ordem(raiz->esq);
		pre_Ordem(raiz->dir);
	}
}

void in_Ordem(Tree *raiz)
{
	if(raiz!=NULL)
	{
		in_Ordem(raiz->esq);
		printf("%d ",raiz->info);
		in_Ordem(raiz->dir);
	}
}

void pos_Ordem(Tree *raiz)
{
	if(raiz!=NULL)
	{
		pos_Ordem(raiz->esq);
		pos_Ordem(raiz->dir);
		printf("%d ",raiz->info);
	}
}

void quantNo(Tree *raiz, int *cont){
	if(raiz != NULL){
		(*cont)++;
		quantNo(raiz->esq, &(*cont));
		quantNo(raiz->dir, &(*cont));
	}
}

void insere(Tree **raiz, int info, int info_pai, char lado){
	Tree *pai = NULL;
	
	if(*raiz == NULL)
		*raiz = CriaNo(info);
	else{
		localizaNo(*raiz, info_pai, &pai);
		if(pai != NULL){
			if(lado == 'e' && pai->esq == NULL)
				pai->esq = CriaNo(info);
			else
				if(lado == 'd' && pai->dir == NULL)
					pai->dir = CriaNo(info);
				else
					printf("\nLado ocupado!");
		}
		else
			printf("\nPai nao encontrado!");
	}
}

void insereABB(Tree **raiz, int info){ //iterativo
	Tree *aux, *ant;
	
	if(*raiz == NULL)
		*raiz = CriaNo(info);
	else{
		aux = *raiz;
		while(aux != NULL){		
			ant = aux;
			if(info < aux->info)
				aux = aux->esq;
			else
				aux = aux->dir;
		}
		if(info < ant->info)
			ant->esq = CriaNo(info);
		else
			ant->dir = CriaNo(info);
	}
}

void insereABBR(Tree **raiz, int info){ //recursivo
	if(*raiz == NULL)
		*raiz = CriaNo(info);
	else{
		if(info < (*raiz)->info){
			if((*raiz)->esq == NULL)
				(*raiz)->esq = CriaNo(info);
			else
				insereABBR(&(*raiz)->esq, info);
		}
		else{
			if((*raiz)->dir == NULL)
				(*raiz)->dir = CriaNo(info);
			else
				insereABBR(&(*raiz)->dir, info);
		}
	}
}

void insereABBR2(Tree **raiz, int info){   //recursivo 2
	if(*raiz == NULL)
		*raiz = CriaNo(info);
	else{
		if(info < (*raiz)->info)
			insereABBR2(&(*raiz)->esq, info);
		else
			insereABBR2(&(*raiz)->dir, info);
	}
}

Tree *BuscaABB(Tree *raiz, int info){  //iterativo
	while(raiz != NULL && raiz->info != info){
		if(info < raiz->info)
			raiz = raiz->esq;
		else
			raiz = raiz->dir;
	}
	return raiz;
} 

Tree *buscaABBR(Tree *raiz, int info){  //recursivo
	if(info == raiz->info)
		return raiz;
	else{
		if(raiz != NULL && raiz->info != info){
			if(info > raiz->info && raiz->dir != NULL)
				buscaABBR(raiz->dir, info);
			else
				if(info < raiz->info && raiz->esq != NULL)
					buscaABBR(raiz->esq, info);
		}
	}

}

void buscaABBR2(Tree *raiz, int info, Tree **aux){ //recursivo 2
	if(raiz != NULL){
		if(info == raiz->info)
			*aux = raiz;
		else{
			if(info < raiz->info)
				buscaABBR2(raiz->esq, info, &*aux);
			else
				buscaABBR2(raiz->dir, info, &*aux);
		}
	}
	else
		*aux = NULL;
}

void killTree(Tree **raiz)
{
	if(*raiz != NULL)
	{
		killTree(&(*raiz)->esq);
		killTree(&(*raiz)->dir);
		free(*raiz);
		*raiz = NULL;	
	}
}

void exibe_formato_arvore(Tree *raiz, int x, int y, int dist)
{
    if(raiz != NULL)
    {
        gotoxy(x, y);
        printf("%d", raiz->info);
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
    }
}

void buscaExclusao(Tree *raiz, int info, Tree **e, Tree **pai)
{
	*e = *pai = raiz;
	while(*e != NULL && (*e)->info != info)
	{
		*pai = *e;
		if(info < (*e)->info)
			*e = (*e)->esq;
		else
			*e = (*e)->dir;
	}
}

/*void exclusao(Tree **raiz, Tree *e, Tree *pai){
	Tree *paisub, *sub;
	int aux;
	
	if(e->esq == NULL && e->dir == NULL) // 'e' é uma folha
	{
		if(e != pai)
			if(e->info > pai->info)
				pai->dir = NULL;
			else
				pai->esq = NULL;
		else
			*raiz = NULL;	
		free(e);
		
	}
	else
	if(e->esq == NULL || e->dir == NULL) //'e' tem 1 filho
	{
		if(e!=pai)
			if(e->info > pai->info)
				if(e->esq!=NULL)
					pai->dir = e->esq;
				else
					pai->dir = e->dir;
			else
				if(e->esq!=NULL)
					pai->esq = e->esq;	
				else
					pai->esq = e->dir;
		else
			if(e->esq!=NULL)
				*raiz = e->esq;
			else
				*raiz = e->dir;
		free(e);
	}
	else //'e' tem 2 filhos
	{
    	paisub = e;
		sub = e->dir;
		while(sub->esq!=NULL)
		{
			paisub = sub;
			sub = sub->esq;
		}
		aux = sub->info;
		exclusao(&*raiz,sub,paisub);
		e->info = aux;
	}
}*/

void exclusao(Tree **raiz, Tree *e, Tree *pai, char lado)
{
	Tree *paisub, *sub;
	int aux;
	
	if(e->esq == NULL && e->dir == NULL) // 'e' é uma folha
	{
		if(e != pai)
			if(e->info > pai->info)
				pai->dir = NULL;
			else
				pai->esq = NULL;
		else
			*raiz = NULL;	
		free(e);
		
	}
	else
		if(e->esq == NULL || e->dir == NULL) //'e' tem 1 filho
		{
			if(e != pai)
				if(e->info > pai->info)
					if(e->esq!=NULL)
						pai->dir = e->esq;
					else
						pai->dir = e->dir;
				else
					if(e->esq!=NULL)
						pai->esq = e->esq;	
					else
						pai->esq = e->dir;
			else
				if(e->esq!=NULL)
					*raiz = e->esq;
				else
					*raiz = e->dir;
			free(e);
		}
		else //'e' tem 2 filhos
		{
			if(lado == 'd')
			{
				paisub = e;
				sub = e->dir;
				while(sub->esq!=NULL)
				{
					paisub = sub;
					sub = sub->esq;
				}
			}
			else
			{
				paisub = e;
				sub = e->esq;
				while(sub->dir != NULL)
				{
					paisub = sub;
					sub = sub->dir;
				}
			}
			aux = sub->info;
			exclusao(&*raiz,sub,paisub, lado);
			e->info = aux;
		}
}

void balanceamento(Tree **raiz){
	Tree *p, *e, *pai;
	p = *raiz;
	int aux, FB, qDir, qEsq;
	Fila *F;
	initFila(&F);
	enqueue(&F, p);
	while(!isEmpty(F))
	{
		dequeue(&F, &p);
		do
		{
			qDir = qEsq = 0;
			quantNo(p->dir, &qDir);
			quantNo(p->esq, &qEsq);
			FB = qDir-qEsq;
			if(FB<-1 || FB>1)
			{
				aux = p->info;
				buscaExclusao(*raiz, p->info, &e, &pai);
				
				if(p->esq == NULL)
					p = p->dir;
				else
					if(p->dir == NULL)
						p = p->esq;
						
				if(FB>0)
					exclusao(&*raiz, e, pai, 'd');
				else
					exclusao(&*raiz, e, pai, 'e');
				insereABB(&*raiz, aux);
			}
		}while(FB<-1 || FB>1);	

		if(p->esq != NULL)
			enqueue(&F, p->esq);
		if(p->dir != NULL)
			enqueue(&F, p->dir);
	}
}

void pre_Ordem_Interativo(Tree *raiz){
	Pilha *P;
	init_Pilha(&P);
	push_Pilha(&P, raiz);
	while(!isEmpty_Pilha(P))
	{
		pop_Pilha(&P, &raiz);
		while(raiz != NULL)
		{
			printf("%d ", raiz->info);
			push_Pilha(&P, raiz);
			raiz = raiz->esq;
		}
		
		pop_Pilha(&P, &raiz);
		raiz = raiz->dir;
		if(raiz != NULL);
			push_Pilha(&P, raiz);
	}
}

////////////////////////AVL////////////////////////

void rotacao_esquerda(Tree **p){
	Tree *q, *temp;
	q = (*p)->dir;
	temp = q->esq;
	q->esq = *p;
	(*p)->dir = temp;
	*p = q;
}

void rotacao_direita(Tree **p){
	Tree *q, *temp;
	q = (*p)->esq;
	temp = q->dir;
	q->dir = *p;
	(*p)->esq = temp;
	*p = q;
	
}

void altura(Tree *raiz, int nivel, int *maior){
	if(raiz != NULL){
		if(nivel > *maior)
			*maior = nivel;
		altura(raiz->esq, nivel+1, &*maior);
		altura(raiz->dir, nivel+1, &*maior);
	}
}

int alturaAVL(Tree *raiz){
	int maior = 0;
	altura(raiz, 1, &maior);
	return maior;
}

void insereAVL(Tree **raiz, int info, char *rotacionou){   //recursivo 2

	int FB, FB_filho;
	if(*raiz == NULL)
	{
		*raiz = CriaNo(info);
		*rotacionou = 0;
	}
	else
		if(info < (*raiz)->info)
			insereAVL(&(*raiz)->esq, info, &*rotacionou);
		else
			insereAVL(&(*raiz)->dir, info, &*rotacionou);
	if(!*rotacionou)
	{
		FB = alturaAVL((*raiz)->dir) - alturaAVL((*raiz)->esq);
		if(abs(FB) == 2) //desbalanceado
		{
			*rotacionou = 1;
			if(FB == 2)
			{
				FB_filho = alturaAVL((*raiz)->dir->dir) - alturaAVL((*raiz)->dir->esq);
				if(FB_filho == 1) //(2)(1)
					rotacao_esquerda(&*raiz);
				else //(2)(-1)
				{
					rotacao_direita(&(*raiz)->dir); //filho
					rotacao_esquerda(&*raiz); //pai
				}
				//exibe_formato_arvore(*raiz, 40, 1, 20);
				//getch();
			}
			else //FB == -2
			{
				FB_filho = alturaAVL((*raiz)->esq->dir) - alturaAVL((*raiz)->esq->esq);
				if(FB_filho == -1) //(-2)(-1)
					rotacao_direita(&*raiz);
				else //(-2)(1)
				{
					rotacao_esquerda(&(*raiz)->esq);
					rotacao_direita(&*raiz);
				}
				//exibe_formato_arvore(*raiz, 40, 1, 20);
				//getch();
			}
		}
	}
}

void insereAVLI(Tree **raiz, int info){
	Pilha *p;
	init_Pilha(&p);
	Tree *aux, *ant, *pai;
	int FB, FB_filho, infoaux;
	char rotacionou = 0;
	
	if(*raiz == NULL)
		*raiz = CriaNo(info);
	else
	{
		aux = *raiz;
		while(aux!=NULL)
		{
			push_Pilha(&p, aux);
			ant = aux;
			if(info < aux->info)	 
				aux = aux->esq;
			else
				aux = aux->dir;
		}
		if(info < ant->info){
			ant->esq = CriaNo(info);
			//push_Pilha(&p, ant->esq);
		}
		else{
			ant->dir = CriaNo(info);
			//push_Pilha(&p, ant->dir);
		}
	}
	while(!isEmpty_Pilha(p) && !rotacionou)
	{
		pop_Pilha(&p, &aux);
		FB = (alturaAVL(aux->dir) - alturaAVL(aux->esq));
		if(abs(FB) == 2) //FB == -2 || FB == 2
		{
			rotacionou = 1;
			if(FB == 2)
			{
				FB_filho = (alturaAVL(aux->dir->dir) - alturaAVL(aux->dir->esq));
				pop_Pilha(&p, &pai);
				
				if(pai != NULL)
				{
					if(aux->info > pai->info)
						pai->dir = aux->dir;
					else
						pai->esq = aux->dir;		
				}
				else
					*raiz = aux->dir;
				
				if(FB_filho == 1)	//(2)(1)
					rotacao_esquerda(&aux);
				else //(2)(-1) 
				{
					insereAVLI(&*raiz, aux->info);
					rotacao_direita(&aux);
					rotacao_esquerda(&aux);
				}
			}
			else //FB == -2
			{
				
				FB_filho = (alturaAVL(aux->esq->dir) - alturaAVL(aux->esq->esq));
				pop_Pilha(&p, &pai);
				//printf("%d - %d", alturaAVL(aux->esq->dir), alturaAVL(aux->esq->esq));
				if(pai != NULL)
				{	
					if(aux->info > pai->info)
						pai->dir = aux->esq;
					else
						pai->esq = aux->esq;	
				}
				else
					*raiz = aux->esq;
				
				if(FB_filho == -1)		//(-2)(-1)		
					rotacao_direita(&aux);
				else //(-2)(1)
				{
					insereAVLI(&*raiz, aux->info);
					rotacao_direita(&aux);
					rotacao_esquerda(&aux);	
				}
			}
		}
	}
}

void insereAVLI2(Tree **raiz, int info){
	Pilha *p;
	init_Pilha(&p);
	Tree *aux, *ant, *pai;
	int FB, FB_filho, infoaux;
	char rotacionou = 0;
	
	if(*raiz == NULL)
		*raiz = CriaNo(info);
	else
	{
		aux = *raiz;
		while(aux!=NULL)
		{
			push_Pilha(&p, aux);
			ant = aux;
			if(info < aux->info)	 
				aux = aux->esq;
			else
				aux = aux->dir;
		}
		if(info < ant->info)
			ant->esq = CriaNo(info);
		else
			ant->dir = CriaNo(info);
	}
	
	while(!isEmpty_Pilha(p) && !rotacionou)
	{
		pop_Pilha(&p, &aux);
		FB = (alturaAVL(aux->dir) - alturaAVL(aux->esq));
		if(abs(FB) == 2) //FB == -2 || FB == 2
		{
			rotacionou = 1;
			if(FB == 2)
			{
				FB_filho = (alturaAVL(aux->dir->dir) - alturaAVL(aux->dir->esq));
				pop_Pilha(&p, &pai);
				
				if(pai != NULL)
				{
					if(aux->info >= pai->info)
						pai->dir = aux->dir;
					else
						pai->esq = aux->dir;		
				}
				else
					*raiz = aux->dir;
				
				if(FB_filho == 1)	//(2)(1)
					rotacao_esquerda(&aux);
				else //(2)(-1) 
				{
					ant = aux->dir;
					if(pai != NULL)
					{
						if(aux->info >= pai->info)
						{
							pai->dir = ant->esq;
							aux->dir = pai->dir;	
						}
						else
						{
							pai->esq = ant->esq;
							aux->dir = ant->esq;
						}
					}
					else
					{
						*raiz = aux->dir->esq;
						aux->dir = *raiz;
					}
					rotacao_direita(&ant);
					rotacao_esquerda(&aux);
				}
			}
			else //FB == -2
			{
				FB_filho = (alturaAVL(aux->esq->dir) - alturaAVL(aux->esq->esq));
				pop_Pilha(&p, &pai);
				//printf("%d - %d", alturaAVL(aux->esq->dir), alturaAVL(aux->esq->esq));
				if(pai != NULL)
				{	
					if(aux->info >= pai->info)
						pai->dir = aux->esq;
					else
						pai->esq = aux->esq;
				}
				else
					*raiz = aux->esq;
	
				if(FB_filho == -1)		//(-2)(-1)		
					rotacao_direita(&aux);
				else //(-2)(1)
				{
					ant = aux->esq;
					if(pai != NULL)
					{
						if(aux->info <= pai->info)
						{
							pai->esq = ant->dir;
							aux->esq = pai->esq;
						}
						else
						{
							pai->dir = ant->dir;
							aux->esq = ant->dir;
						}
					}
					else
					{
						*raiz = aux->esq->dir;
						aux->esq = *raiz;
					}
					rotacao_esquerda(&ant);
					rotacao_direita(&aux);		
				}
			}
		}
	}
}
// exclusao
void buscaExclusaoAVL(Tree *raiz, int info, Tree **e, Tree **pai, Pilha **p)
{
	*e = *pai = raiz;
	while(*e != NULL && (*e)->info != info)
	{
		*pai = *e;
		push_Pilha(&*p, *e);
		if(info >= (*e)->info)
			*e = (*e)->dir;
		else
			*e = (*e)->esq;
	}
}

void exclusaoAVL(Tree **raiz, Tree *e, Tree *pai, char lado)
{
	Tree *paisub, *sub;
	int aux;
	
	if(e->esq == NULL && e->dir == NULL) // 'e' é uma folha
	{
		if(e != pai)
			if(e->info > pai->info)
				pai->dir = NULL;
			else
				pai->esq = NULL;
		else
			*raiz = NULL;	
		free(e);
		
	}
	else
		if(e->esq == NULL || e->dir == NULL) //'e' tem 1 filho
		{
			if(e != pai)
				if(e->info > pai->info)
					if(e->esq!=NULL)
						pai->dir = e->esq;
					else
						pai->dir = e->dir;
				else
					if(e->esq!=NULL)
						pai->esq = e->esq;	
					else
						pai->esq = e->dir;
			else
				if(e->esq!=NULL)
					*raiz = e->esq;
				else
					*raiz = e->dir;
			free(e);
		}
		else //'e' tem 2 filhos
		{
			if(lado == 'd')
			{
				paisub = e;
				sub = e->dir;
				while(sub->esq!=NULL)
				{
					paisub = sub;
					sub = sub->esq;
				}
			}
			else
			{
				paisub = e;
				sub = e->esq;
				while(sub->dir != NULL)
				{
					paisub = sub;
					sub = sub->dir;
				}
			}
			aux = sub->info;
			exclusao(&*raiz,sub,paisub, lado);
			e->info = aux;
		}
}

void excluirAVLIterativo(Tree **raiz, int info){
	Tree *aux, *ant, *e, *pai;
	char rotacionou = 0, lado;
	int FB, FB_filho;
	
	Pilha *p;
	init_Pilha(&p);
	
	buscaExclusaoAVL(*raiz, info, &e, &pai, &p); //insere o caminho do no excluido na pilha
	
	if(info >= (*raiz)->info) // verifica o lado
		lado = 'e';
	else
		lado = 'd';
	
	exclusaoAVL(&*raiz, e, pai, lado); // exclui
	
		
	while(!isEmpty_Pilha(p) && !rotacionou) // balanceia
	{
		pop_Pilha(&p, &aux);
		FB = (alturaAVL(aux->dir) - alturaAVL(aux->esq));
		if(abs(FB) == 2) //FB == -2 || FB == 2
		{
			rotacionou = 1;
			if(FB == 2)
			{
				FB_filho = (alturaAVL(aux->dir->dir) - alturaAVL(aux->dir->esq));
				pop_Pilha(&p, &pai);
				
				if(pai != NULL)
				{
					if(aux->info >= pai->info)
						pai->dir = aux->dir;
					else
						pai->esq = aux->dir;		
				}
				else
					*raiz = aux->dir;
				
				if(FB_filho == 1)	//(2)(1)
					rotacao_esquerda(&aux);
				else //(2)(-1) 
				{
					ant = aux->dir;
					if(pai != NULL)
					{
						if(aux->info >= pai->info)
						{
							pai->dir = ant->esq;
							aux->dir = pai->dir;	
						}
						else
						{
							pai->esq = ant->esq;
							aux->dir = ant->esq;
						}
					}
					else
					{
						*raiz = aux->dir->esq;
						aux->dir = *raiz;
					}
					rotacao_direita(&ant);
					rotacao_esquerda(&aux);
				}
			}
			else //FB == -2
			{
				FB_filho = (alturaAVL(aux->esq->dir) - alturaAVL(aux->esq->esq));
				pop_Pilha(&p, &pai);
				//printf("%d - %d", alturaAVL(aux->esq->dir), alturaAVL(aux->esq->esq));
				if(pai != NULL)
				{	
					if(aux->info >= pai->info)
						pai->dir = aux->esq;
					else
						pai->esq = aux->esq;
				}
				else
					*raiz = aux->esq;
	
				if(FB_filho == -1)		//(-2)(-1)		
					rotacao_direita(&aux);
				else //(-2)(1)
				{
					ant = aux->esq;
					if(pai != NULL)
					{
						if(aux->info <= pai->info)
						{
							pai->esq = ant->dir;
							aux->esq = pai->esq;
						}
						else
						{
							pai->dir = ant->dir;
							aux->esq = ant->dir;
						}
					}
					else
					{
						*raiz = aux->esq->dir;
						aux->esq = *raiz;
					}
					rotacao_esquerda(&ant);
					rotacao_direita(&aux);		
				}
			}
		}
	}
}

///////////////////////////////////////////////////

//com arquivo//
struct arvArq{
	int info, esq, dir;
};
typedef struct arvArq ArvArq;

void exibirABBDisco(){
	
	ArvArq raiz;
	FILE *ptr = fopen("arq.dat", "rb");
	rewind(ptr);
	fread(&raiz, sizeof(ArvArq), 1, ptr);
	while(!feof(ptr))
	{
		printf("%d %d %d\n", raiz.esq, raiz.info, raiz.dir);
		fread(&raiz, sizeof(ArvArq), 1, ptr);
	}
		
	fclose(ptr);
}

int buscaPai(FILE *arq, int info){
	ArvArq aux;
	int flag = 0, pos=0;
	
	rewind(arq);
	fread(&aux, sizeof(ArvArq), 1, arq);
	while(!feof(arq) && flag == 0)
	{
		if(info > aux.info)
		{
			if(aux.dir == -1)
			{
				flag = 1;
				pos = ftell(arq) - sizeof(ArvArq);
			}
			else
			{
				fseek(arq, aux.dir, 0);
				fread(&aux, sizeof(ArvArq), 1, arq);
			}
		}
		else
		{
			if(aux.esq == -1)
			{
				flag = 1;
				pos = ftell(arq) - sizeof(ArvArq);
			}
			else
			{
				fseek(arq, aux.esq, 0);
				fread(&aux, sizeof(ArvArq), 1, arq);
			}
		}
	}
	return pos;
}

void insereABBDisco(int info){
    ArvArq no;
    FILE *arq = fopen("arq.dat", "rb+");
    int posFilho, posPai;
    
    no.info = info;
    no.esq = -1;
    no.dir = -1;
    
    fseek(arq, 0, 2); // colocar na ultima pos
    fwrite(&no, sizeof(ArvArq), 1, arq);
    
    posFilho = ftell(arq) - sizeof(ArvArq);
    
    if(posFilho != 0)
	{
        posPai = buscaPai(arq, info);
        fseek(arq, posPai, 0);
        fread(&no, sizeof(ArvArq), 1, arq);
        
        
        if(info > no.info) 
			no.dir = posFilho;
        else 
			no.esq = posFilho;
		
        fseek(arq, posPai, 0);
        fwrite(&no, sizeof(ArvArq), 1, arq);
    }
    fclose(arq);
}

int procurapai(FILE *ptr, int info){
	
	ArvArq aux, aux2;
	int flag = 0, pos;
	rewind(ptr);
	
	fread(&aux, sizeof(ArvArq), 1, ptr);
	while(!feof(ptr) && flag == 0)
	{
		if(aux.esq == info || aux.dir == info)
		{
			pos = ftell(ptr)-sizeof(ArvArq);
			flag = 1;
		}
		else
			fread(&aux, sizeof(ArvArq), 1, ptr);
	}
	return pos;
}

void excluirABBDisco(FILE *ptr, int pospai, int posfilho, int info, char lado){
	
	ArvArq aux, aux2;
	int auxinfo, infoant, sub, paisub;
	
	rewind(ptr);
	
	if(!feof(ptr))
	{	
		fseek(ptr, posfilho, 0);
		fread(&aux, sizeof(ArvArq), 1, ptr);
		
		if(aux.esq == -1 && aux.dir == -1) // é folha
		{
			if(pospai != posfilho)
			{
				fseek(ptr, pospai, 0);
				fread(&aux, sizeof(ArvArq), 1, ptr);
				
				if(info > aux.info)
					aux.dir = -1;
				else
					aux.esq = -1;
				
				fseek(ptr, pospai, 0);
				fwrite(&aux, sizeof(ArvArq), 1, ptr);
			}
		}
		else
			if(aux.esq == -1 || aux.dir == -1) // tem 1 filho
			{
				fseek(ptr, pospai, 0);
				fread(&aux, sizeof(ArvArq), 1, ptr);
				if(pospai != posfilho)
				{	
					fseek(ptr, posfilho, 0);
					fread(&aux2, sizeof(ArvArq), 1, ptr);
					if(info > aux.info)	
						if(aux2.esq != -1)
							aux.dir = aux2.esq;
						else
							aux.dir = aux2.dir;
					else
						if(aux2.esq != -1)
							aux.esq = aux2.esq;
						else
							aux.esq = aux2.dir;
							
					fseek(ptr, pospai, 0);
					fwrite(&aux, sizeof(ArvArq), 1, ptr);
				}		
			}
			else // tem 2 filhos
			{	
				fseek(ptr, posfilho, 0);
				fread(&aux, sizeof(ArvArq), 1, ptr);
				paisub = ftell(ptr)-sizeof(ArvArq);
				
				if(lado == 'd')
				{
					fseek(ptr, aux.dir, 0);
					fread(&aux, sizeof(ArvArq), 1, ptr);
					
					while(aux.esq != -1)
					{
						paisub = ftell(ptr)-sizeof(ArvArq);
						fseek(ptr, aux.esq, 0);
						fread(&aux, sizeof(ArvArq), 1, ptr);
					}	
				}
				else
				{
					fseek(ptr, aux.esq, 0);
					fread(&aux, sizeof(ArvArq), 1, ptr);
					
					while(aux.dir != -1)
					{
						paisub = ftell(ptr)-sizeof(ArvArq);
						fseek(ptr, aux.dir, 0);
						fread(&aux, sizeof(ArvArq), 1, ptr);
					}	
				}
				sub = ftell(ptr)-sizeof(ArvArq);
				fseek(ptr, sub, 0);
				fread(&aux, sizeof(ArvArq), 1, ptr);
				auxinfo = aux.info;
				
				excluirABBDisco(ptr, paisub, sub, auxinfo, lado);
				
				fseek(ptr, posfilho, 0);
				fread(&aux, sizeof(ArvArq), 1, ptr);
				aux.info = auxinfo;
				fseek(ptr, posfilho, 0);
				fwrite(&aux, sizeof(ArvArq), 1, ptr);
				
				fseek(ptr, sub, 0);
				fread(&aux, sizeof(ArvArq), 1, ptr);
				aux.info = -1;
				fseek(ptr, sub, 0);
				fwrite(&aux, sizeof(ArvArq), 1, ptr);
					
			}
	}
}

void excluirP1(int info){
	int pospai, posfilho;
	ArvArq aux;
	
	FILE *ptr = fopen("arq.dat", "rb+");
	FILE *ptr2 = fopen("Temp.dat", "wb+");
	
	rewind(ptr);
	rewind(ptr2);
	
	fread(&aux, sizeof(ArvArq), 1, ptr);
	while(!feof(ptr) && aux.info != info)
		fread(&aux, sizeof(ArvArq), 1, ptr);
	
	posfilho = ftell(ptr)-sizeof(ArvArq);
	
	rewind(ptr);
	fread(&aux, sizeof(ArvArq), 1, ptr);
	if(aux.info != info)
		pospai = procurapai(ptr, posfilho);
	else
		pospai = 0;
	
	
	excluirABBDisco(ptr, pospai, posfilho, info, 'e');
	
	fseek(ptr, posfilho, 0);
	fread(&aux, sizeof(ArvArq), 1, ptr);
	if(aux.dir != -1 && aux.esq != -1)
		info = -1;
		
		
	rewind(ptr);
	fread(&aux, sizeof(ArvArq), 1, ptr);
	while(!feof(ptr))
	{
		if(aux.info != info){
			if(aux.dir > posfilho)
				aux.dir = aux.dir-sizeof(ArvArq);
			if(aux.esq > posfilho)
				aux.esq = aux.esq-sizeof(ArvArq);
			
			fwrite(&aux, sizeof(ArvArq), 1, ptr2);
		}
		fread(&aux, sizeof(ArvArq), 1, ptr);
	}
	
	fclose(ptr);
	remove("arq.dat");
	fclose(ptr2);
	rename("Temp.dat", "arq.dat");
}

///////////////
int main(){
	Tree *raiz, *aux;
	Tree *e, *pai;
	init(&raiz);
	int cont=0;
	srand(time(NULL));
	//insere(&raiz, 5, 0, ' ');
	//insere(&raiz, 10, 5, 'e');
	//insere(&raiz, 9, 10, 'd');
	
	/*insereABB(&raiz, 10);
	insereABB(&raiz, 15);
	insereABB(&raiz, 5);
	insereABB(&raiz, 30);
	insereABB(&raiz, 2);
	insereABB(&raiz, 70);
	insereABB(&raiz, 20);
	insereABB(&raiz, 14);
	insereABB(&raiz, 6);
	insereABB(&raiz, 95);
	insereABB(&raiz, 22);
	insereABB(&raiz, 56);*/
	
	//pre_Ordem(raiz);
	//printf("\n");
	/*in_Ordem(raiz);
	printf("\n");
    pos_Ordem(raiz);*/
    
    /*aux = BuscaABB(raiz, 70);
    printf("%d", aux->info);*/
    
    /*aux = buscaABBR(raiz, 30);
    printf("%d", aux->info);*/
    
	//exibe_formato_arvore(raiz, 40, 1, 20);
	//getch();
	//clrscr();
	
	//buscaExclusao(raiz,22,&e,&pai);
	//if(e != NULL)
	//	exclusao(&raiz,e,pai, 'd');
	
	//quantNo(raiz->dir, &cont);
	//printf("%d", cont);
	
	
	//balanceamento(&raiz);
	//exibe_formato_arvore(raiz, 40, 1, 20);
	
	//pre_Ordem_Interativo(raiz);
	
	/*char rotacionou;
	insereAVL(&raiz, 7, &rotacionou);
	insereAVL(&raiz, 8, &rotacionou);
	insereAVL(&raiz, 6, &rotacionou);
	insereAVL(&raiz, 9, &rotacionou);
	insereAVL(&raiz, 5, &rotacionou);
	insereAVL(&raiz, 4, &rotacionou);
	
	insereAVL(&raiz, 2, &rotacionou);
	insereAVL(&raiz, 3, &rotacionou);
	insereAVL(&raiz, 10, &rotacionou);
	insereAVL(&raiz, 1, &rotacionou);
	insereAVL(&raiz, 0, &rotacionou);*/

	
	/*gotoxy(15, 20);
	int a;
	for(int i=0; i<20; i++)
	{
		a = rand() % 50;
		insereAVLI2(&raiz, a);
		printf("%d ",a);
	}*/
	
	//30 20 30 24 40 40 33 27 44
	/*insereAVLI2(&raiz, 11);
	insereAVLI2(&raiz, 30);
	insereAVLI2(&raiz, 20);
	insereAVLI2(&raiz, 30);
	insereAVLI2(&raiz, 24);
	insereAVLI2(&raiz, 40);
	insereAVLI2(&raiz, 40);
	insereAVLI2(&raiz, 33);
	insereAVLI2(&raiz, 27);
	insereAVLI2(&raiz, 44);
	excluirAVLIterativo(&raiz, 30);
	excluirAVLIterativo(&raiz, 33);*/
	
	//exibe_formato_arvore(raiz, 40, 1, 20);

	insereAVLI(&raiz, 10);
	insereAVLI(&raiz, 20);
	insereAVLI(&raiz, 30);
	insereAVLI(&raiz, 5);
	insereAVLI(&raiz, 15);
	insereAVLI(&raiz, 2);

	printf("\n\n\n");
	pre_Ordem(raiz);
	
	/*FILE *ptr = fopen("arq.dat", "wb+");
	fclose(ptr);
	
	insereABBDisco(10);
	insereABBDisco(8);
	insereABBDisco(15);
	insereABBDisco(4);
	insereABBDisco(2);
	insereABBDisco(16);
	//insereABBDisco(14);
	
	excluirP1(16);
	exibirABBDisco();*/
	
	return 0;
}
