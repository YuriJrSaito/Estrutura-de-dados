#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>

#define ncesc 4
#define entrada 4
#define saida 2
#define exemplos 10


main(){
   float w[saida][ncesc], W[ncesc][entrada], errodes, Erroinst, Erromg = 0, erro[saida], niesc[ncesc], ni[saida], biasesc[ncesc], biass[saida], eta, phiesc[ncesc], phi[saida], philesc[ncesc], phil[saida], delta[saida], deltaesc[ncesc];
   int x, y, cont2, contt, epocas;
	float entradas[entrada][exemplos], saidas[saida][exemplos];
   clrscr();
   printf("bias e pesos iniciais...\n");
   for(y = 0; y < ncesc; y++){
	   for(x = 0; x < saida; x++)
      		w[x][y] = rand()%2 + .5;
      for(x = 0; x < entrada; x++)
      		W[y][x] = rand()%2 + .5;
      biasesc[y] = rand()%2;
      }
	for(x = 0; x < saida; x++)
   	biass[x] = rand()%2 + .5;
   for(y = 0; y < saida; y++)
	   printf("Neurônio de Saída: bias[%d] = %f\n", y, biass[y]);

   for(y = 0; y < ncesc; y++)
	   printf("Neurônio da camada escondida: bias[%d] = %f\n", y, biass[y]);

   printf("Entre com o número de épocas de treinamento:\n");
   scanf("%d", &epocas);
   printf("Entre com os vetores de exemplos de treinamento de entrada:\n");
   for(x = 0; x < entrada; x++)
   	for(y = 0; y < exemplos; y++)
      	scanf("%f", &entradas[x][y]);
   printf("Entre com os vetores de exemplos de treinamento de saída:\n");
   for(x = 0; x < saida; x++)
   	for(y = 0; y < exemplos; y++)
        	scanf("%f", &saidas[x][y]);

   printf("Entre com o valor da taxa de aprendizagem: \n");
   scanf("%f", &eta);
   
   printf("Entre com o erro desejado:\n");
   scanf("%f", &errodes);

	clrscr();

   printf("Pesos iniciais:\n");
   for(y = 0; y < ncesc; y++){
	   for(x = 0; x < saida; x++)
      		printf("w[%d][%d] = %f\n", x, y, w[x][y]);
      for(x = 0; x < entrada; x++)
      		printf("W[%d][%d] = %f\n", x, y, W[y][x]);
      }
   printf("Iniciando processo iterativo...\n");
   for(x = 0; x < epocas; x++){
   	for(y = 0; y < exemplos; y++){
       for(contt = 0; contt < ncesc; contt++){
         niesc[contt] = 0;
      	for(cont2 = 0; cont2 < entrada; cont2++)
         	niesc[contt] = niesc[contt] + W[contt][cont2]*entradas[cont2][y];
         niesc[contt] = niesc[contt] + biasesc[contt];
         phiesc[contt] = 1/(1 + exp(-niesc[contt]));
         }
       for(contt = 0; contt < saida; contt++){
      	ni[contt] = 0;
      	for(cont2 = 0; cont2 < ncesc; cont2++)
	         	ni[contt] = ni[contt] + w[contt][cont2]*phiesc[cont2];
         ni[contt] = ni[contt] + biass[contt];
         phi[contt] = 1/(1 + exp(-ni[contt]));
         }

      for(contt = 0; contt < saida; contt++)
      	erro[contt] = saidas[contt][y] - phi[contt];
      Erroinst = 0;
      for(contt = 0; contt < saida; contt++)
      	Erroinst = Erroinst + erro[contt]*erro[contt]/2;
   	Erromg = (Erromg*(x*exemplos + y) + Erroinst)/(x*exemplos + (y+1));
   	if (Erromg < errodes)
      	break;

      for(cont2 = 0; cont2 < saida; cont2++){
      	phil[cont2] = exp(-ni[cont2])/((1+exp(-ni[cont2]))*(1+exp(-ni[cont2])));
         delta[cont2] = -erro[cont2]*phil[cont2];
         }
      for(cont2 = 0; cont2 < ncesc; cont2++){
      	philesc[cont2] = exp(-niesc[cont2])/((1+exp(-niesc[cont2]))*(1+exp(-niesc[cont2])));
         deltaesc[cont2] = 0;
         for(contt = 0; contt < saida; contt++)
	         deltaesc[cont2] = deltaesc[cont2] + philesc[cont2]*delta[contt]*w[contt][cont2];
         }
      for(cont2 = 0; cont2 < saida; cont2++){
         for(contt = 0; contt < ncesc; contt++){
	         w[cont2][contt] = w[cont2][contt] - eta*delta[cont2]*phiesc[contt];
         	biass[cont2] = biass[cont2] - eta*delta[cont2]*phiesc[contt];
         	}
         }
      for(cont2 = 0; cont2 < ncesc; cont2++){
         for(contt = 0; contt < entrada; contt++){
         	W[cont2][contt] = W[cont2][contt] - eta*deltaesc[cont2]*entradas[contt][y];
         	biasesc[cont2] = biasesc[cont2] - eta*deltaesc[cont2]*entradas[contt][y];
         	}
         }
      }
   if (Erromg < errodes) {
   	printf("Finalizado pelo erro em %d épocas de treinamento!\n", x);
      break;
      }
   }

   printf("bias finais:\n");
   for(y = 0; y < ncesc; y++)
   	printf("%f ", biasesc[y]);
   printf("\n");
   for(y = 0; y < saida; y++)
   	printf("%f ", biass[y]);
   printf("\nPesos finais:\n");
   for(y = 0; y < ncesc; y++){
	   for(x = 0; x < saida; x++)
      		printf("w[%d][%d] = %f\n", x, y, w[x][y]);
      for(x = 0; x < entrada; x++)
      		printf("W[%d][%d] = %f\n", x, y, W[y][x]);
      }

   printf("Finalizado!\n");

   for (x = 0; x < exemplos; x++){
   	printf("\nEntradas: ");
   	for(y = 0; y < entrada; y++)
      	printf("%f ", entradas[y][x]);
   	printf("\nSaídas esperadas: ");
   	for(y = 0; y < saida; y++)
      	printf("%f ", saidas[y][x]);
      printf("\nSaídas da rede: ");
      for(contt = 0; contt < ncesc; contt++){
         niesc[contt] = 0;
      	for(cont2 = 0; cont2 < entrada; cont2++)
         	niesc[contt] = niesc[contt] + W[contt][cont2]*entradas[cont2][x];
         niesc[contt] = niesc[contt] + biasesc[contt];
         phiesc[contt] = 1/(1 + exp(-niesc[contt]));
         }
      for(contt = 0; contt < saida; contt++){
      	ni[contt] = 0;
      	for(cont2 = 0; cont2 < ncesc; cont2++)
	         	ni[contt] = ni[contt] + w[contt][cont2]*phiesc[cont2];
         ni[contt] = ni[contt] + biass[contt];
         phi[contt] = 1/(1 + exp(-ni[contt]));
         printf("%f ", phi[contt]);
         }
      }
   printf("\nErro médio global: %f", Erromg);
   getch();
   }


