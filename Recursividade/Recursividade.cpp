#include<stdio.h>
#include<conio2.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int ex2(int x, int y, int aux){
	if(y==0)
		return aux;
	else{
		aux = aux*x;
		return ex2(x,y-1,aux);
	}	
}

int ex4(int vet[5], int tl){
	if(tl==0)
		return 0;
	else{
		printf("Pos[%d]: %d\n",tl, vet[tl-1]); 
		return ex4(vet, tl-1);
	}
}

int exibePalavra(char palavra[50], int cont){
	if(cont == -1)
		return 0;
	else{
		printf("%c", palavra[cont]);
		palavra[cont] = '\0';
		return exibePalavra(palavra,cont-1);
	}
}

int ex6(char frase[50], int tl, char palavra[50], int cont){
	if(tl == -1)
		return 0;
	else{
		if(frase[tl]!= ' ' && tl > 0){
			palavra[cont]=frase[tl];
			return ex6(frase,tl-1,palavra,cont+1);
		}
		else{
			if(tl==0){
				palavra[cont] = frase[tl];
				cont++;
				printf(" ");
			}
			exibePalavra(palavra,cont-1);
			return ex6(frase,tl-1,palavra,cont=0);
		}
	}
}
int ex1(int x, int y){
	if(y==0)
		return x;
	else
		return ex1(y,x%y);
}

int ex5(int x, int y){
	if(x==y)
		return y;
	if(x<y)
		return ex5(y,x);
	if(x>y)
		return ex5(x-y,y); // fazer função interativa para resolver o mesmo problema
}

int ex9(int dividendo, int divisor){
	if(dividendo < divisor)
		return dividendo;
	else
		return ex9(dividendo-divisor,divisor);
}

int ex10(int x, int y, int aux){
	if(y==0)
		return aux;
	else{
		return ex10(x,y-1,aux+=x);
	}
		
}

int ex5Interativo(int x, int y){
	while(x!=y){
		if(x<y){
			int aux;
			aux = y;
			y = x;
			x = aux;
		}
		
		if(x > y)
			x = x-y;
	}
	return y;
}

int ex8(int n){
	if(n==0 || n==1)
		return n;
	else
		return ex8(n-2) + ex8(n-1);
}

int main(){
	char op;
	int yEx1,xEx1; //ex1
	
	int aux=1,yEx2,xEx2; //ex2
	
	int vet[5]{10,4,8,5,2}; //ex4
	int tl = 5; //ex4
	
	int xEx5, yEx5; //ex5
	
	char frase[50] = "estou com fome"; //ex6
	char palavra[50] = ""; //ex6
	int cont=0, tlEx6 = 14; //ex6
	
	int nEx8; //ex8
	
	int dividendo, divisor; //ex9
	
	int xEx10,yEx10,auxEx10 = 0; //ex10
	do
	{
		clrscr();
		printf("[A] MDC de dois numeros inteiros\n");
		printf("[B] X multiplicado por y vezes: \n");
		printf("[D] vetor ao contrario\n");
		printf("[E] MDS de dois numeros naturais\n");
		printf("[F] frase ao contrario\n");
		printf("[H] Fibonacci printando os N primeiros numeros\n");
		printf("[I] resto da divisao\n");
		printf("[J] multiplicacao de dois numeros positivos\n");
		
		op=toupper(getch());fflush(stdin);
		switch(op)
		{	
			case 'A':clrscr();
					 printf("\nValor de X: ");
					 scanf("%d",&xEx1);
					 printf("\nValor de Y: ");
					 scanf("%d",&yEx1);
					 printf("%d", ex1(xEx1,yEx1));
					 break;
		    case 'B':clrscr();
					 printf("\n Valor de X: ");
					 scanf("%d",&xEx2);
					 printf("\n Valor de Y: ");
					 scanf("%d",&yEx2);
					 printf("%d",ex2(xEx2,yEx2,aux));
					 break;
			case 'D':clrscr();
					 ex4(vet,tl);
					 break;
			case 'E':clrscr();
					 printf("\nValor de X: ");
					 scanf("%d",&xEx5);
					 printf("\nValor de Y: ");
				  	 scanf("%d",&yEx5);
					 printf("\nRecursivo: ");
					 printf("%d", ex5(xEx5,yEx5));
					 printf("\nInterativo: ");
					 printf("%d", ex5Interativo(xEx5,yEx5));
					 break;
			case 'F':clrscr();
					 ex6(frase,tlEx6,palavra,cont);
					 break;
			case 'H':clrscr();
					 printf("Valor de N: \n");
					 scanf("%d", &nEx8);
					 printf("%d", ex8(nEx8));
					 break;
			case 'I':clrscr();
					 printf("Dividendo: \n");
					 scanf("%d", &dividendo);
					 printf("Divisor: \n");
					 scanf("%d", &divisor);
					 printf("%d\n", ex9(dividendo, divisor));
					 break;
			case 'J':clrscr();
					 printf("\nValor de X: ");
					 scanf("%d",&xEx10);
					 printf("\nValor de Y: ");
					 scanf("%d",&yEx10);
					 printf("%d", ex10(xEx10,yEx10,auxEx10));
				     break;
					 
			case 27: printf("Sair");break;
		}
		getch();
	}while(op!=27);
}
