#include<conio2.h>
#include<stdlib.h>
#include<stdio.h>

struct fila{
	int info;
	struct fila *prox
};
typedef struct fila Fila;

void init(Fila **f){
	*f = NULL;
}

char QisEmpty(Fila *f){
	return f == NULL;
}

void Enqueue(Fila **f, int x){
	Fila *aux;
	Fila *nova = (Fila*)malloc(sizeof(Fila));
	nova->info = x;
	nova->prox = NULL;
	if(QisEmpty(*f))
		*f = nova;
	else{
		aux = *f;
		while(aux->prox != NULL){
			aux = aux->prox;
		aux->prox = nova;
	}
}

void Dequeue(Fila **f, int *x){
	Fila *aux = (Fila*)malloc(sizeof(Fila));
	if(!QisEmpty(*f)){
		aux = *f;
		*x = aux->info;
		*f = aux->prox;
		free(aux);
	}
	else
		x = -1;	
}

