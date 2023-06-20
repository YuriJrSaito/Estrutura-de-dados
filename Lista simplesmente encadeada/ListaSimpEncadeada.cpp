#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

struct TpPont
{
    char Elem;
    TpPont *prox;
};

char LeValor(void)
{
   printf("\nElemento: ");
   return toupper(getche());
}

TpPont *NovaCaixa(char Elemento)
{
   TpPont *Caixa;
   Caixa = new TpPont;

   Caixa->Elem = Elemento;

   Caixa->prox = NULL;

   return Caixa;
}

TpPont *InserirInicioLista(TpPont *Lista)
{
    TpPont *NC;
    char Elemento;

    printf("\nInserir elementos na Lista:\n");
    Elemento = LeValor();
    while (Elemento!=27)
    {
       NC = NovaCaixa(Elemento);
       NC->prox = Lista;
       Lista = NC;
       Elemento = LeValor();
    }
    return Lista;
}

void Exibe(TpPont *Lista)
{
	printf("\n\n*** Elementos contidos na Lista ***\n");
	while (Lista!=NULL)
	{
	   printf("%c ",Lista->Elem);
	   Lista = Lista->prox;
    }
    printf("\n----------------------\n");
	getch();
}

TpPont *InserirFinalLista(TpPont *Lista)
{
    TpPont *NC, *Aux;
    char Elemento;

    printf("\nInserir elementos na Lista:\n");
    Elemento = LeValor();
    while (Elemento!=27)
    {
       NC = NovaCaixa(Elemento);
       if (Lista == NULL)       //Vazia 
             Lista = NC;
       else
           {
                Aux = Lista;
                while (Aux->prox != NULL)
                        Aux = Aux->prox;
                
                Aux->prox = NC;
           }
       Elemento = LeValor();
    }
    return Lista;
} 

TpPont *ExcluirElemento(TpPont *Lista, char Elemento)
{
   TpPont *Atual, *Ant;

   if (Lista == NULL) printf("\nLista Vazia!\n");
   else
      {
         if (Lista->Elem == Elemento)
         {
            Atual = Lista;
            Lista = Lista->prox;
             delete(Atual);
             printf("\nElemento %c excluído! \n", Elemento);
         }
         else
              {
                   Atual = Lista;
                   while (Atual->prox != NULL && Atual->Elem != Elemento)
                   {
                       Ant = Atual;
                       Atual = Atual->prox;
                   }
                   if (Atual->Elem == Elemento)
                   {
                        Ant->prox = Atual->prox;
                        delete(Atual);
                        printf("\nElemento %c excluído! \n", Elemento);
                   }
                   else printf("\nElemento nao encontrado!\n");
              }
      }
   getch();
   return Lista;
}

int main(void)
{
   TpPont *L = NULL;

   L = InserirInicioLista(L);
   Exibe(L);
   L = InserirFinalLista(L);   
   Exibe(L);
   L = ExcluirElemento(L,'A');   
   Exibe(L);
   return 1;
}
