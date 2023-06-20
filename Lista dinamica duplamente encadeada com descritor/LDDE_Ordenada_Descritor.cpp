#include<stdio.h>
#include<conio2.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>


struct TpPont
{
   char Elem;                                         
   TpPont *ant, *prox;
};

struct TpDescritor
{
   TpPont *Inicio, *Final;
   int Qtde;
};

TpPont *NovaCaixa(char Elemento)
{
    TpPont *pCaixa = new TpPont;
    pCaixa->Elem = Elemento;
    pCaixa->ant = NULL;
    pCaixa->prox = NULL;
    return pCaixa;
}

void InicializarDescritor(TpDescritor &Desc)
{
   Desc.Inicio = Desc.Final = NULL;
   Desc.Qtde = 0;
}

void InserirOrdenado(TpDescritor &Desc, char Elemento)
{
     TpPont *p, *NC = NovaCaixa(Elemento);
     Desc.Qtde++;
     if (Desc.Inicio == NULL)    //Lista Vazia!
     {
        Desc.Inicio = Desc.Final = NC;
     }
     else
          {
             if (Elemento <= Desc.Inicio->Elem)
             {
                  NC->prox = Desc.Inicio;
                  Desc.Inicio->ant = NC;
                  Desc.Inicio = NC;
              }
               else
                      {
                          if (Elemento >= Desc.Final->Elem)
                          {
                             NC->ant = Desc.Final;
                             Desc.Final->prox = NC;
                             Desc.Final = NC;
                          }
                          else
                                {
                                    p = Desc.Inicio->prox;
                                    while (Elemento > p->Elem)
                                		p = p->prox;
                                    NC->prox = p;
                                    NC->ant = p->ant;
                                    p->ant = NC;
                                    NC->ant->prox = NC;
                                }
                      } 
          }
}

void Exibir(TpDescritor Desc)
{
	printf("\n\n*** Elementos contidos na Lista ***\n");
	if(Desc.Inicio==NULL)
		printf("\nLista Vazia!");
	while (Desc.Inicio!=NULL)
	{
	   printf("%c ",Desc.Inicio->Elem);
	   Desc.Inicio = Desc.Inicio->prox;
    }
    printf("\n----------------------\n");
    getch();
}

void Excluir(TpDescritor &Desc,char Elemento){
	TpPont *aux, *Anterior, *Atual;
	if(Desc.Inicio == NULL)
		printf("\nLista Vazia!\n");
	else{
		if(Desc.Inicio->Elem == Elemento){
			if(Desc.Inicio -> prox == NULL){
				Desc.Inicio = NULL;
			}
			else{
				Desc.Inicio = Desc.Inicio->prox;
				Desc.Inicio->ant = NULL;
			}
			printf("\nElemento %c excluido", Elemento);
		}
		else{
			if(Desc.Final->Elem == Elemento){
				aux = Desc.Final->ant;
				Desc.Final->ant = NULL;
				Desc.Final = aux;
				Desc.Final->prox = NULL;
				printf("\nElemento %c excluido", Elemento);
			}
			else{
				aux = Desc.Inicio->prox;
				while(aux->Elem != Elemento){
					Anterior = aux;
					aux = aux->prox;
				}
				if(aux->Elem == Elemento){
					Atual = aux->prox;
					Anterior->prox = Atual;
					Atual->ant = Anterior;
					delete(aux);
					printf("\nElemento %c excluido", Elemento);
				}
				else
					printf("\nElemento nao encontrado");
			}
		}	
	}
}

int main(void)
{
   TpDescritor Descritor;

   InicializarDescritor(Descritor);
   InserirOrdenado(Descritor,'M');
   Exibir(Descritor);
   InserirOrdenado(Descritor,'G');
   Exibir(Descritor);
   InserirOrdenado(Descritor,'Z');
   Exibir(Descritor);
   InserirOrdenado(Descritor,'F');
   Exibir(Descritor);
   
InserirOrdenado(Descritor,'F');
   Exibir(Descritor);
   
   Excluir(Descritor, 'Z');
   Exibir(Descritor);
   Excluir(Descritor, 'M');
   Exibir(Descritor);
   Excluir(Descritor, 'F');
   Exibir(Descritor);
   Excluir(Descritor, 'G');
   Exibir(Descritor);
   
   getch();
}
