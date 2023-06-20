package arvorenarea;

public class NArea implements Definicoes{
    private No raiz;
    
    public NArea()
    {
        raiz = null;
    }
    
    public No getRaiz()
    {
        return raiz;
    }
    
    public void inserir(int info)
    {
        No p, ant = null;
        int pos = 0;
        boolean flag = false;
        if(raiz == null)
            raiz = new No(info);
        else
        {
            p = raiz;
            while(p != null && !flag)
            {
                pos = p.buscarPos(info);
                if(p.getTL() < N-1)
                {                   
                    p .remanejar(pos);
                    p.setvInfo(pos, info);
                    p.setTL(p.getTL()+1);
                    flag = true;
                }
                else
                {
                    ant = p;
                    p = p.getvLig(pos);
                }
            }
            if(!flag)
                ant.setvLig(pos, new No(info));
        }
    }
    
    public void inOrdem(No raiz)
    {
        if(raiz != null)
        {
            for(int i=0; i<raiz.getTL(); i++)
            {
                inOrdem(raiz.getvLig(i));
                System.out.println(raiz.getvInfo(i));
            }
            inOrdem(raiz.getvLig(raiz.getTL()));
        }
    }
}
