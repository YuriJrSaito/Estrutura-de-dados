package arvoreb;

public class BTreePlus implements Ligacoes{
    
    private No raiz;

    public BTreePlus() {
    }

    public No getRaiz() {
        return raiz;
    }

    public No navegarAteFolha(int info) 
    {
        No aux = raiz;
        int pos;
        while(aux.getvLig(0) != null)
        {
            pos = aux.procurarPosicao(info);
            aux = aux.getvLig(pos);
        }
        return aux;
    }

    public No localizarPai(No folha, int info) 
    {
        No aux = raiz;
        No ant = raiz;
        int pos;
        while(aux != folha)
        {
            ant = aux;
            pos = aux.procurarPosicao(info);
            aux = aux.getvLig(pos);            
        }
        return ant;
    }

    public void inserir(int info) 
    {
        No folha, pai;
        int pos;
        if (raiz == null) 
            raiz = new No(info);        
        else 
        {
            folha = navegarAteFolha(info);
            pos = folha.procurarPosicao(info);
            folha.remanejar(pos);
            folha.setTL(folha.getTL() + 1);
            folha.setvInfo(pos, info);
            folha.setvPos(pos, info);
            if (folha.getTL() > N - 1) 
            {
                pai = localizarPai(folha, info);
                split(folha, pai);
            }
        }
    }

    public void split(No folha, No pai) 
    {
        No cx1, cx2;
        int aux, meio, i, pos, info;
        cx1 = new No();
        cx2 = new No();
        meio = 0;
        if (folha.getvLig(0) == null) 
        {
            //aux = (N - 1) / 2;            
            aux = (int)Math.round(((double)(N-1)/2)+0.5);
            //System.out.println("dasdsadbashdbas"+aux);
            
            for (i = 0; i < aux; i++) 
            {
                cx1.setvInfo(i, folha.getvInfo(i));
                cx1.setvPos(i, folha.getvPos(i));
                cx1.setTL(cx1.getTL() + 1);
            }
            meio = aux;
            for (i = aux; i < N; i++) 
            {
                cx2.setvInfo(i - (aux), folha.getvInfo(i));
                cx2.setvPos(i - (aux), folha.getvPos(i));
                cx2.setTL(cx2.getTL() + 1);
            }
        } 
        else 
        {
            aux = (N / 2)-1;

            for (i = 0; i < aux; i++) 
            {
                cx1.setvInfo(i, folha.getvInfo(i));
                cx1.setvPos(i, folha.getvPos(i));
                cx1.setvLig(i, folha.getvLig(i));
                cx1.setTL(cx1.getTL() + 1);
            }
            cx1.setvLig(aux, folha.getvLig(aux));
            meio = aux++;
            for (i = aux; i < N; i++) 
            {
                cx2.setvInfo(i - (aux), folha.getvInfo(i));
                cx2.setvPos(i - (aux), folha.getvPos(i));
                cx2.setvLig(i - (aux), folha.getvLig(i));
                cx2.setTL(cx2.getTL() + 1);
            }
            cx2.setvLig(i - aux, folha.getvLig(N));
        }

        if (folha == pai) 
        {
            folha.setvInfo(0, folha.getvInfo(meio));
            folha.setvPos(0, folha.getvPos(meio));
            folha.setvLig(0, cx1);
            folha.setvLig(1, cx2);
            folha.setTL(1);
        } 
        else 
        {
            info = folha.getvInfo(meio);
            pos = pai.procurarPosicao(info);
            pai.remanejar(pos);
            pai.setTL(pai.getTL() + 1);
            pai.setvInfo(pos, folha.getvInfo(meio));
            pai.setvPos(pos, folha.getvPos(meio));
            pai.setvLig(pos, cx1);
            pai.setvLig(pos + 1, cx2);

            if (pai.getvLig(0).getvLig(0) == null) 
            {
                for (int j = 0; j < pai.getTL(); j++) 
                {
                    pai.getvLig(j).setProx(pai.getvLig(j + 1));
                    pai.getvLig(j + 1).setAnt(pai.getvLig(j));
                }
                pai.getvLig(pai.getTL()).setAnt(pai.getvLig(pai.getTL() - 1));
            }

            if (pai.getTL() > N - 1) 
            {
                folha = pai;
                info = folha.getvInfo(meio);
                pai = localizarPai(folha, info);
                split(folha, pai);
            }
        }
    }

    public void exibe() 
    {
        No aux = raiz;
        while (aux.getvLig(0) != null) 
            aux = aux.getvLig(0);
       
        while (aux != null) 
        {
            int i = 0;
            while (i < aux.getTL()) 
                System.out.print(aux.getvInfo(i++) + " ");

            System.out.println("");
            aux = aux.getProx();
        }
    }
}
