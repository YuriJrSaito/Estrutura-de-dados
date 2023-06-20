// Listas Gen aula 08/09/2020
// Listas Generalizadas.pdf -> implementação de Listas Generalizadas
// unsigned char = não deixar o char negativo
// Listas Gen aula 09/09/2020 - implementação
// Listas Gen aula 15/09/2020 - 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio2.h>

struct pilha{
	struct listagen *pilha;
	struct pilha *prox;	
};
typedef struct pilha Pilha;

struct fila{
	struct listagen *lista;
	struct fila *prox;
};
typedef struct fila Fila;

struct reg_lista
{
	struct listagen *cabeca;
	struct listagen *cauda;
};

union info_lista
{
	char info[8];
	struct reg_lista lista;
};

struct listagen
{
	char terminal;
	union info_lista no;
};
typedef struct listagen ListaGen;

ListaGen *CriaT(char *info)
{
	ListaGen *L = (ListaGen*)malloc(sizeof(ListaGen));
	L->terminal = 1;
	strcpy(L->no.info, info);
	return L;
}

void init(Pilha **p){
	*p = NULL;	
}

int isEmpty(Pilha *P){
	return P==NULL;
}

void push(Pilha **P, ListaGen *L){
	Pilha *novo = (Pilha*)malloc(sizeof(Pilha)), *aux;
	novo->pilha = L;
	novo->prox = NULL;
	if(isEmpty(*P))
		*P = novo;
	else{
		novo->prox = *P;
		*P = novo;
	}
}

void pop(Pilha **P, ListaGen **L){
	Pilha *aux;
	if(!isEmpty(*P)){
		aux = *P;
		*L = aux->pilha;
		*P = aux->prox;
		free(aux);
	}
}

char Nula(ListaGen *L)
{
	return L == NULL;
}

char Atomo(ListaGen *L)
{
	return !Nula(L) && L->terminal == 1;
}

ListaGen *Cons(ListaGen *H, ListaGen *T)
{
	if(Atomo(T))
	{
		printf("\nCons: Segundo argumento nao pode ser atomo!");
		return NULL;
	}
	else{
		ListaGen *L = (ListaGen*)malloc(sizeof(ListaGen));
		L->terminal = 0;
		L->no.lista.cabeca = H;
		L->no.lista.cauda = T;
		return L;
	}
	
}

ListaGen *Head(ListaGen *L)
{
 	if(Nula(L) || Atomo(L))
 	{
	 	printf("Head: argumento deve ser lista não vazia!");
 	 	return NULL;
 	}
 	else
 		return L->no.lista.cabeca;
}

ListaGen *Tail(ListaGen *L)
{
 	if(Nula(L) || Atomo(L))
 	{
 		printf("Tail: argumento deve ser lista não vazia!");
 		return NULL;
 	}
 	else
 		return L->no.lista.cauda;
}

void exibe(ListaGen *L)
{
	if(Atomo(L))
		printf("%s", L->no.info);
	else
	{
		printf("[");
		while(!Nula(L))
		{
			exibe(Head(L));
			L = Tail(L);
			if(!Nula(L))
				printf(",");
		}
		printf("]");
	}	
}

void exibeRec(ListaGen *L){
	if(!Nula(L))
	{
		if(Atomo(L))
			printf("%s", L->no.info);
		else
		{
			exibeRec(Head(L));
			exibeRec(Tail(L));
		}
	}
}

void destruir(ListaGen **L){
	if(!Nula){
		if(Atomo(*L))
			free(*L);
		else{
			destruir(&(*L)->no.lista.cabeca);
			destruir(&(*L)->no.lista.cauda);
			free(*L);
			*L = NULL;
		}
	}
}

ListaGen *duplica(ListaGen *L){
	if(Nula(L))
		return NULL;
	if(Atomo(L))
		return CriaT(L->no.info);
	return Cons(duplica(Head(L)), duplica(Tail(L)));
}

char compara(ListaGen *L, ListaGen *L2){
	if(Nula(L) && Nula(L2))
		return 1;
	if(Nula(L) || Nula(L2))
		return 0;
		
	if(Atomo(L) && Atomo(L2))
		return !strcmp(L->no.info, L2->no.info);
	if(Atomo(L) || Atomo(L2))
		return 0;
	
	return compara(Head(L),Head(L2)) && compara(Tail(L),Tail(L2));
}

void exibeAtomo(ListaGen *L){
	if(!Nula(L)){
		if(Atomo(L))
			printf("%s", L->no.info);
		else{
			exibeAtomo(Head(L));
			exibeAtomo(Tail(L));
		}
	}
}

void profundidade(ListaGen *L, int nivel, int *maior)
{
	if(!Nula(L))
	{
		if(!Atomo(L))
		{
			if(nivel > *maior)
				*maior = nivel;
			profundidade(Head(L), nivel+1, &*maior);
			profundidade(Tail(L), nivel, &*maior);
		}
	}
}

/*void exibeRec(ListaGen *L){
	if(!Nula(L))
	{
		if(Atomo(L))
			printf("%s", L->no.info);
		else
		{
			exibeRec(Head(L));
			exibeRec(Tail(L));
		}
	}
}*/

void append(ListaGen *L, ListaGen **L2){
	ListaGen *L3 = (ListaGen*)malloc(sizeof(ListaGen));
	L3 = *L2;
	while(Tail(L3) != NULL)
		L3 = Tail(L3);
	L3->no.lista.cauda = Cons(L,NULL);
}

/*void Plain(ListaGen *L, ListaGen **L2){
	if(!Nula(L)){
		if(Atomo(L)){
			if(Nula(*L2))
				*L2 = Cons(L, NULL);
			else
				*L2 = append(L, &(*L2));
		}
		else{
			Plain(Head(L), &(*L2));
			Plain(Tail(L), &(*L2));
		}
	}
}*/

int extInt(char valor[])
{
	int aux, i;
	i = strlen(valor);
	aux = valor[i] - '0';
	
	return aux;
}

int comS(char info[], char valor[])
{
	int i=0;
	char aux[8];
	for(int j=0; j<8; j++)
		aux[j] = '\0';
		
	while(i < strlen(valor)-1)
	{
		aux[i] = valor[i];
		i++;
	}
	if(strcmp(info, aux)>0)
		return 0;
	else
		return 1;
}

void insereL2(ListaGen **L2, char info[], int nivel)
{
	ListaGen *ant, *aux, *novo;
	char ns[5], info2[8];
	itoa(nivel, ns, 10);
	strcpy(info2, info);
	strcat(info2, ns);
	
	novo = Cons(CriaT(info2), NULL);
	
	if(*L2 == NULL)
		*L2 = novo;
	else
	{
		aux = *L2;
		while(aux != NULL && (comS(info, Head(aux)->no.info)>0 || nivel>extInt(Head(aux)->no.info)))
		{
			ant = aux;
			aux = Tail(aux);
		}
		ant->no.lista.cauda = novo;
		novo->no.lista.cauda = aux;
	}
}

void PlainOrdNivel(ListaGen *L, ListaGen **L2)
{
	Pilha *P;
	init(&P);
	push(&P,L);
	
	int nivel=0;
	
	while(!isEmpty(P))
	{
		if(!Nula(L))
		{
			pop(&P,&L);
			while(!Nula(L) && !Atomo(L))
			{
				push(&P,L);
				nivel++;
				L = Head(L);
			}
			if(Atomo(L))
			{
				insereL2(&*L2, L->no.info, nivel);
			}
				
		}
		pop(&P,&L);
		L = Tail(L);
		if(!Nula(L))
			push(&P,L);
		nivel--;
	}
}

void Plain(ListaGen *L, ListaGen **L2){
	
	if(!Nula(L)){
		if(!Atomo(L)){
			Plain(Tail(L), &(*L2));
			Plain(Head(L), &(*L2));
		}
	}
	if(Atomo(L)){
		if(Nula(*L2))
			*L2 = Cons(L,NULL);
		else
			*L2 = Cons(L,*L2);
	}
}

void TopLevel(ListaGen *L, ListaGen **L2){
	
	if(Tail(L) != NULL)
		TopLevel(Tail(L), &(*L2));
	if(Atomo(Head(L))){
		if(Nula(*L2))
			*L2 = Cons(Head(L),NULL);
		else
			*L2 = Cons(Head(L), *L2);
	}
}

void ordena(ListaGen **L2){
	ListaGen *aux1, *aux2, *menor;
	char infor[8];
	
	aux1 = *L2;
	
	while(!Nula(aux1)){
		aux2 = menor = aux1;
		while(!Nula(aux2)){
			if(stricmp(Head(aux2)->no.info, Head(menor)->no.info)<0)
				menor = aux2;
			aux2 = Tail(aux2);
		}
		strcpy(infor, Head(aux1)->no.info);
		strcpy(Head(aux1)->no.info, Head(menor)->no.info);
		strcpy(Head(menor)->no.info, infor);

		aux1 = Tail(aux1);	
	}
}

void insereFila(Fila **fila, ListaGen *L){
	Fila *novo, *aux;
	novo = (Fila*)malloc(sizeof(Fila));
	novo->lista = L;
	novo->prox = NULL;
		
	//printf("\n%s", Head(novo->lista)->no.info);
	if(*fila == NULL)
		*fila = novo;
	else{
		aux = *fila;
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novo;
	}
}

/*void teste(ListaGen *L){
	Fila *fila;
	fila = NULL;
	while(!Nula(L)){
		insereFila(&fila, L);
		L = Tail(L);
	}
	
}*/


/*void exibeAtomoInt(ListaGen *L){ //não recursivo
	Pilha *P;
	init(&P);
	push(&P,L);
	int tam=0, nivel=0, contlista=0;
	while(!isEmpty(P))
	{
		if(!Nula(L))
		{
			tam = 0;
			pop(&P,&L);
			while(!Nula(L))
			{
				nivel++;
				L = Tail(L);
				tam++;
			}
			if()
				printf("%s", L->no.info);
		}
		pop(&P,&L);
		L = Tail(L);
		if(!Nula(L))
			push(&P,L);
		nivel--;
	}
}*/

struct lista{
	int tam, nivel, contlista;
	struct lista *prox;
};
typedef struct lista Lista;

void insereLista(Lista **lista, int tam, int contlista, int nivel)
{
	Lista *aux = *lista, *novo;
	
	novo = (Lista*)malloc(sizeof(Lista));
	
	novo->tam = tam;
	novo->contlista = contlista;
	novo->nivel = nivel;
	novo->prox = NULL;
	
	if(*lista == NULL)
		*lista = novo;
	else
	{
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novo;
	}
}

void exibelista(Lista *lista){
	
	if(lista != NULL)
	{
		while(lista != NULL)
		{
			printf("Lista %d, Tamanho %d, Profundidade %d", lista->contlista, lista->tam, lista->nivel);
			lista = lista->prox;
		}
	}
}


void essevai(ListaGen *L, Lista **lista)
{
	Pilha *P;
	init(&P);
	push(&P,L);
	int tam=0, nivel=0, contlista=0;
	while(!isEmpty(P))
	{
		if(!Nula(L))
		{
			
			tam = 0;
			pop(&P,&L);
			contlista++;
			nivel++;
			while(!Nula(L))
			{
				tam++;
				if(!Atomo(Head(L)) && !Nula(Head(L)))
					push(&P, Head(L));
				L = Tail(L);
			}
			printf("%d %d %d\n", contlista, nivel, tam);
		}
		pop(&P, &L);
		if(!Nula(L))
			push(&P,L);
		else
			nivel--;
	}
}

void insere()
{
	Listagen *novo;
	str
	novo->head = NULL, noov->tail = NULL;
	if(l->head== NULL)
		l = novo;
	else
	{
		aux = *l->head;
		
		if(diferente primeiro)
		{
		  *l->head = novo;
		  novo-> tail = aux;
		  *H = novo; 
		}
		else
		{	
			while(aux != NULL && strcmp(nome, aux->nome)>0)
			{
				ant = aux;
				aux = aux->tail;
			}
			if()
			ant->tail = novo;
			*H = novo;
			novo->tail = aux;
			
			*H = novo;
		}
	}
}

void teste(ListaGen **L){
	ListaGen *v = *L;
	Pilha *p;
	init(&p);
	push(&p, v);
	
	int maior = 0, nivel = 0;
	while(!isEmpty(p))
	{
		if(!Nula(v))
		{
			pop(&p, &v);
			while(!Nula(v) && !Atomo(v))
			{
				push(&p, v);
				nivel++;
				v = Head(v);
			}
			if(nivel > maior)
				maior = nivel;
		}
		pop(&p, &v);
		v = Tail(v);
		if(!Nula(v))
			push(&p, v);
		nivel--;
	}
	
	printf("%d ", maior);	
	
	v = *L;
	ListaGen *x, *aux;
	init(&p);
	push(&p, v);
	nivel = 1;
	
	while(!isEmpty(p))
	{
		if(!Nula(v))
		{
			pop(&p, &v);
			aux = v;
			while(!Nula(aux) && !Atomo(Head(aux)))
			{
				push(&p, aux);
				nivel++;
				aux = Head(aux);
			}
			while(maior > nivel)
			{
				push(&p, aux);
				x = Head(aux);
				aux->no.lista.cabeca = Cons(x, NULL);
				aux = Head(aux);
				nivel++;
			}
		}
		pop(&p, &v);
		v = Tail(v);
		if(!Nula(v))
			push(&p, v);
		nivel--;
	}
}

/*void excluirNulos(ListaGen **L){
	ListaGen *aux = *L, *aux2, *aux3, *aux4, *del, *antaux2, *auxant;
	
	while(aux != NULL){
		if(!Nula(Head(aux)))
			aux2 = Head(aux);
		while(aux2 != NULL){
			if(!Atomo(aux2)){
				if(!Nula(Tail(aux2))){
					aux4 = aux2;
					aux3 = Tail(aux2);
				}             
				while(!Nula(aux3)){
					if(Nula(Head(aux3)))
						aux4->no.lista.cauda = Tail(aux3);
					else      
						aux4 = aux3;
					del = aux3;
					aux3 = Tail(aux3);
					free(del);
				}
			}
			aux2 = Head(aux2);
		}
		auxant = aux;
		aux = Tail(aux);
	}
}*/



void ordenaTudo(ListaGen **L){
	ListaGen *aux = *L, *menor, *aux2;
	Fila *fila1, *fila2;
	fila1 = fila2 = NULL;
	char infor[8];
	
	while(!Nula(aux)){ //procura todas sublista na profundidade 0
		if(!Atomo(Head(aux))){
			insereFila(&fila1, Head(aux));
			insereFila(&fila2, Head(aux));
		}
		aux = Tail(aux);
	}
	
	while(fila1 != NULL){   // procura todas sublista dentro das sublistas
		aux = fila1->lista;
		while(!Nula(aux)){		
			if(!Atomo(Head(aux))){
				insereFila(&fila1, Head(aux));
				insereFila(&fila2, Head(aux));
			}
			aux = Tail(aux);
		}
		fila1 = fila1->prox;
	}
	
	aux = *L;
	while(!Nula(aux)){   // ordena a lista profundidade 0
		if(Atomo(Head(aux))){
			menor = aux2 = aux;
			while(!Nula(aux2)){
				if(Atomo(Head(aux2))){
					if(stricmp(Head(aux2)->no.info, Head(menor)->no.info)<0)
						menor = aux2;
				}
				aux2 = Tail(aux2);
			}
			strcpy(infor, Head(aux)->no.info);
			strcpy(Head(aux)->no.info, Head(menor)->no.info);
			strcpy(Head(menor)->no.info, infor);
		}
		aux = Tail(aux);
	}
	
	while(fila2 != NULL){ //ordena todas as sublistas
		aux = fila2->lista;
		while(!Nula(aux)){
			menor = aux2 = aux;
			while(!Nula(aux2)){
				if(Atomo(Head(aux2))){
					if(stricmp(Head(aux2)->no.info, Head(menor)->no.info)<0)
						menor = aux2;
				}
				aux2 = Tail(aux2);
			}
			strcpy(infor, Head(aux)->no.info);
			strcpy(Head(aux)->no.info, Head(menor)->no.info);
			strcpy(Head(menor)->no.info, infor);
			
			aux = Tail(aux);
		}
		fila2 = fila2->prox;
	}
}

void procura(ListaGen **ant, char *info){
	int flag = 0;
	while(!Nula(*ant) && flag == 0)
	{
		if(Atomo(Head(*ant)))
			if(strcmp((*ant)->no.info, info)==0)
				flag = 1;
		*ant = Tail(*ant);
	}
}

void ex2(ListaGen **L, char *info){ //mudar - falta inserir na profundidade 0
	Fila *fila1, *fila2;
	fila1 = fila2 = NULL;
	ListaGen *aux = *L, *ant;
	
	while(!Nula(aux))  //procura todas sublista na profundidade 0
	{ 
		if(!Atomo(Head(aux)))
		{
			insereFila(&fila1, aux);
			insereFila(&fila2, aux);
		}
		aux = Tail(aux);
	}

	while(fila1 != NULL) // procura todas sublista dentro das sublistas
	{   
		aux = fila1->lista;
		aux = Head(aux);
		while(!Nula(aux))
		{		
			if(!Atomo(Head(aux)))
			{
				insereFila(&fila1, aux);
				insereFila(&fila2, aux);
			}
			aux = Tail(aux);
		}
		fila1 = fila1->prox;
	}
	
	while(fila2 != NULL) // insere o elemento info nas sublistas respeitando a ordem
	{
		aux = fila2->lista;
		ant = Head(aux);
		procura(&ant, info);
		if(ant == NULL)
		{
			ant = Head(aux);
			if(strcmp(Head(ant)->no.info, info) > 0)
			{
				aux->no.lista.cabeca = Cons(CriaT(info), ant);
			}
			else
			{
				aux = Head(aux);
				while(!Nula(aux) && strcmp(Head(aux)->no.info, info)<0)
				{
					ant = aux;
					aux = Tail(aux);
				}
				if(aux == NULL)
				{
					ant->no.lista.cauda = Cons(CriaT(info), NULL);
				}
				else
				{
					ant->no.lista.cauda = Cons(CriaT(info), aux);
				}
			}
		}	
		fila2 = fila2->prox;
	}
}

void ex4(ListaGen **L){ //mudar - dar free nos nós excluidos
	Pilha *p1, *p2;
	init(&p1);
	init(&p2);
	ListaGen *aux = *L, *ant, *atual;
	
	while(!Nula(aux))  //procura todas sublista na profundidade 0
	{ 
		if(!Atomo(Head(aux)))
		{
			push(&p1, aux);
			push(&p2, aux);
		}
		aux = Tail(aux);
	}

	while(!isEmpty(p1)) // procura todas sublista dentro das sublistas
	{   
		pop(&p1, &aux);
		aux = Head(aux);
		while(!Nula(aux))
		{		
			if(!Atomo(Head(aux)))
			{
				push(&p1, aux);
				push(&p2, aux);
			}
			aux = Tail(aux);
		}
	}
	
	while(!isEmpty(p2)) // exlui todos os nos nulos das sublistas
	{
		pop(&p2, &aux);
		atual = Head(aux);
		while(!Nula(atual) && !Nula(Head(atual)))
		{
			ant = atual;
			atual = Tail(atual);
		}
		if(atual != NULL)
		{
			if(atual == Head(aux))
				aux->no.lista.cabeca = Tail(atual);
			else
				ant->no.lista.cauda = Tail(atual);	
			push(&p2, aux);
			free(atual);
		}
	}
	
	if(Nula(Head(*L))) // exclui todos os nos nulos da lista na profundidade 0
	{
		while(Nula(Head(*L))){
			atual = *L;
			*L = Tail(*L);
			free(atual);
		}
	}
	ant = *L;
	aux = Tail(ant);
	while(!Nula(aux))
	{
		if(Nula(Head(aux))){
			ant->no.lista.cauda = Tail(aux);
			free(aux);
		}
			
		ant = Tail(ant);	
		aux = Tail(ant);
	}
}


void exame3(ListaGen **L){ //não recursivo
	
	int contlista = 0, tam = 0, nivel = 0;
	Fila *fila1, *fila2;
	fila1 = fila2 = NULL;
	ListaGen *aux = *L, *ant;
	
	while(!Nula(aux))  //procura todas sublista na profundidade 0
	{ 
		if(!Atomo(Head(aux)))
		{
			tam = 0;
			nivel = 2;
			contlista++;
			insereFila(&fila1, aux);
			insereFila(&fila2, aux);
			ant = Head(aux);
			while(ant != NULL)
			{
				tam++;
				ant = Tail(ant);
			}
			printf("%d %d\n", tam, nivel);
			//insereLista(tam, nivel, contlista);
		}
		aux = Tail(aux);
	}
	nivel = 2;
	while(fila1 != NULL) // procura todas sublista dentro das sublistas
	{   
		aux = fila1->lista;
		aux = Head(aux);
		while(!Nula(aux))
		{		
			if(!Atomo(Head(aux)))
			{
				contlista++;
				tam = 0;
				insereFila(&fila1, aux);
				insereFila(&fila2, aux);
				ant = Head(aux);
				nivel++;
				while(ant != NULL)
				{
					tam++;
					ant = Tail(ant);
				}
				printf("%d %d\n", tam, nivel);
			}
			aux = Tail(aux);
		}
		fila1 = fila1->prox;
	}
	
}

int main()
{
	ListaGen *L, *L2, *L3;
	Lista *lista;
	lista = NULL;
	//L = Cons(CriaT("a"), Cons(Cons(CriaT("b"), Cons(Cons(CriaT("c"),NULL),NULL)),NULL));
	//L = Cons(CriaT("b"),Cons(Cons(CriaT("h"),Cons(CriaT("d"),NULL)),Cons(CriaT("b"),Cons(Cons(CriaT("q"),Cons(CriaT("p"),Cons(CriaT("e"),NULL))),NULL))));
	//exibe(L2);
	//exibeAtomo(L);
	//L2 = NULL;
	L = Cons(CriaT("aaa"), Cons(CriaT("jjj"), Cons(Cons(CriaT("ddd"), Cons(CriaT("ccc"), NULL)), Cons(Cons(CriaT("eee"), Cons(CriaT("fff"), Cons(Cons(CriaT("ggg"),Cons(CriaT("hhh"), NULL)), NULL))), Cons(CriaT("bbb"),NULL)))));
	
	exibe(L);
	printf("\n");
	//int prof = 0;
	//profundidade(L,1,&prof);
	//printf("profundidade %d ", prof);
	//printf("\n");
	//L2 = NULL;
	//Plain(L ,&L2);
	//exibe(L2);
	
	//printf("\n");
	
	//L2 = duplica(L);
	//printf("%d",compara(L,L2));
	//TopLevel(L, &L2);
	//exibe(L2);	
	
	//L3 = append(L2,&L);
	//exibe(L3);
	
	//ordena(&L);
	//exibe(L2);
	
	//ordenaTudo(&L);
	//exibe(L);
	
	//printf("\n");
	//ex2(&L, "b");
	
	//ex4(&L);
	
	//teste(&L);
	//PlainOrdNivel(L, &L2);
	//exame3(&L);
	//exibe(L);
	//essevai(L, &lista);
	
	//excluirNulos(&L);
	//exibe(L);
	
	return 0;
}

