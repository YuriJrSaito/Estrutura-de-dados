package arvorepatricia;

import java.util.Locale;

public class Patricia {
    private No raiz;
    
    public Patricia()
    { 
        this.raiz = new No();
    }
        
    public void exibirNivel()
    {
        No aux;
        int nivel = 1;
        Fila fila = new Fila();
        for (int i = 0; i < 26; i++)
        {
            if (this.raiz.getvLig(i) != null)
                fila.enqueue(this.raiz.getvLig(i));
        }
        System.out.printf("Nível -> %d\n",nivel);
        Fila filaAux = new Fila();
        while(!fila.isEmpty())
        {
            aux = fila.dequeue();
            System.out.println(aux.getInfo()+" ");
            for (int i = 0; i < 26; i++)
            {
                if(aux.getvLig(i) != null)
                    filaAux.enqueue(aux.getvLig(i));
            }
            if(fila.isEmpty())
            {
                if(!filaAux.isEmpty())
                    System.out.printf("\nNível -> %d\n",nivel+=1);
                fila = filaAux;
                filaAux = new Fila();
            }
        }
    }
    
    //public void Inserir(String palavra){ this.Inserir(raiz,palavra);}
    
    
    /*
            BASICAMENTE, AS CONVERTI TODAS AS PALAVRAS EM MAIÚSCULAS E PARA ACHAR A MELHOR POSIÇÃO ALFABÉTICA NO VETOR DO NÓ, EU SUBTRAÍ 65
            DA TABELA ASCII, OU SEJA, AÍ SE A LETRA FOR A (65), QUANDO SUBTRAÍDO, A MELHOR POSIÇÃO DE INSERIR ESSA LETRA NO VETOR
            É '0' E ASSIM COM B (66 - 65 = POSIÇÃO '1' NO VETOR) ETC...
    */
    
    
    public void Inserir(String palavra)
    {
        No temp = this.raiz;
        boolean flag = true;
        palavra = palavra.toUpperCase();
        for (int i = 0; flag && i < palavra.length();)
        {
            if (temp.getvLig(palavra.charAt(i)-65) == null)
            {
                temp.setvLig(palavra.charAt(i)-65, new No(palavra.substring(i)));
                temp.getvLig(palavra.charAt(i)-65).setFinal(true);
                flag = false;
            }
            else
            {
                temp = temp.getvLig(palavra.charAt(i)-65);
                int j=0;
                for(;i < palavra.length() && j < temp.getInfo().length() && temp.getInfo().charAt(j) == palavra.charAt(i);i++, j++);  
                if (j < temp.getInfo().length())
                {
                    No no = new No(temp.getInfo().substring(j));
                    no.setFinal(temp.chegouFinal());
                    no.setvLig(temp.getvLig());
                    temp.setvLig(new No[26]);
                    temp.setInfo(temp.getInfo().substring(0,j));
                    temp.setvLig(no.getInfo().charAt(0)-65, no);
                    //if(i == temp.getInfo().length() && i == palavra.length())
                    if(temp.getInfo().equals(palavra))
                        temp.setFinal(true);
                    else
                        temp.setFinal(false);
                }
                else if (i == palavra.length() && j == temp.getInfo().length())
                    temp.setFinal(true);
            }
        }
    }
    
    public void exibirArvore(){
        System.out.println("\nEXIBINDO ÁRVORE...\n");
        this.exibirArvore(this.raiz, "");
        System.out.println("");
    }
    
    public void exibirArvore(No no, String palavra)
    {
        if(no.chegouFinal())
            System.out.println(palavra);
        for(int i = 0; i < 26; i++)
        {
            if(no.getvLig(i) != null)
                exibirArvore(no.getvLig(i), palavra + no.getvLig(i).getInfo());
        }
    }
}
