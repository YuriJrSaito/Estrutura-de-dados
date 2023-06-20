package arvoreb;

public class BTree implements Definicoes{
    private No raiz;
    
    public BTree()
    {
        raiz = null;
    }
    
    public No getRaiz()
    {
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
    
    public void split(No folha, No pai)
    {
        int pos;
        No cx1 = new No();
        No cx2 = new No();
        for(int i=0; i<M; i++)
        {
            cx1.setvInfo(i, folha.getvInfo(i));
            cx1.setvPos(i, folha.getvPos(i));
            cx1.setvLig(i, folha.getvLig(i));
        }
        cx1.setvLig(M, folha.getvLig(M));
        cx1.setTL(M);
        
        for(int i=M+1; i<2*M+1; i++)
        {
            cx2.setvInfo(i-(M+1), folha.getvInfo(i));
            cx2.setvPos(i-(M+1), folha.getvPos(i));
            cx2.setvLig(i-(M+1), folha.getvLig(i));
        }
        cx2.setvLig(M, folha.getvLig(2*M+1));
        cx2.setTL(M);
        
        if(folha == pai)
        {
            folha.setvInfo(0, folha.getvInfo(M));
            folha.setvPos(0, folha.getvPos(M));
            folha.setTL(1);
            folha.setvLig(0, cx1);
            folha.setvLig(1, cx2);
        }
        else
        {
            pos = pai.procurarPosicao(folha.getvInfo(M));
            pai.remanejar(pos);
            pai.setvInfo(pos, folha.getvInfo(M));
            pai.setvPos(pos, folha.getvPos(M));
            pai.setTL(pai.getTL()+1);
            pai.setvLig(pos, cx1);
            pai.setvLig(pos+1, cx2);
            if(pai.getTL() > 2*M)
            {
                folha = pai;
                pai = localizarPai(folha, folha.getvInfo(0));
                split(folha, pai);
            }
        }
    }
    
    public void inserir(int info, int posArq)
    {
        No folha, pai;
        int pos;
        if(raiz == null)
            raiz = new No(info, posArq);
        else
        {
            folha = navegarAteFolha(info);
            pos = folha.procurarPosicao(info);
            folha.remanejar(pos);
            folha.setvInfo(pos, info);
            folha.setvPos(pos, posArq);
            folha.setTL(folha.getTL()+1);
            if(folha.getTL() > 2*M)
            {
                pai = localizarPai(folha, info);
                split(folha, pai);
            }
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
    
    //Métodos para a exclusão
    
    public No localizarNo(int info)
    {
        No no = raiz;
        int pos;
        boolean achou = false;
        while(no != null && !achou)
        {
            pos = no.procurarPosicao(info);
            if(pos < no.getTL() && no.getvInfo(pos) == info)
                achou = true;
            else
                no = no.getvLig(pos);
        }
        return no;
    }
    
    public No localizarSubE(No no, int pos)
    {
        no = no.getvLig(pos);
        while(no.getvLig(no.getTL()) != null)
            no = no.getvLig(no.getTL());
        return no;
            
    }
    
    public No localizarSubD(No no, int pos)
    {
        no = no.getvLig(pos);
        while(no.getvLig(0) != null)
            no = no.getvLig(0);
        return no;
    }
    
    public void excluir(int info)
    {
        No subE, subD, folha;
        int pos=0;
        No no = localizarNo(info);
        if(no != null)
        {
            pos = no.procurarPosicao(info);
            if(no.getvLig(0) != null) //não é folha
            {              
                subE = localizarSubE(no, pos);
                subD = localizarSubD(no, pos+1);
                if(subE.getTL() > M || subD.getTL() == M)
                {
                    no.setvInfo(pos, subE.getvInfo(subE.getTL()-1));
                    no.setvPos(pos, subE.getvInfo(subE.getTL()-1));
                    folha = subE;
                    pos = subE.getTL()-1;
                }
                else
                {
                    no.setvInfo(pos, subD.getvInfo(0));
                    no.setvPos(pos, subD.getvPos(0));
                    folha = subD;
                    pos = 0;
                }
            }
            else
                folha = no;
            
            folha.remanejarEx(pos);
            folha.setTL(folha.getTL()-1);
            
            if(folha != raiz && folha.getTL()<M)
                redistribuir_concatenar(folha);
            
        }
    }
    
    public void teste()
    {
        No no = localizarNo(6);
        //no = no.getvLig(0);
        for(int i=0; i<no.getTL(); i++)
            System.out.print(no.getvInfo(i)+ " ");    
    }
    
    public void redistribuir_concatenar(No folha)
    {
        No pai = null, irmaE=null, irmaD=null;
        pai = localizarPai(folha, folha.getvInfo(0));
        int posPai = pai.procurarPosicao(folha.getvInfo(0));
        if(posPai > 0)
            irmaE = pai.getvLig(posPai-1);
        else
            irmaE = null;
        if(posPai < pai.getTL())
            irmaD = pai.getvLig(posPai+1);
        else
            irmaD = null;
        
        //redistribuição
        if(irmaE != null && irmaE.getTL() > M)
        {
            folha.remanejar(0);
            folha.setvInfo(0, pai.getvInfo(posPai-1));
            folha.setvPos(0, pai.getvPos(posPai-1));
            folha.setTL(folha.getTL()+1);
            folha.setvLig(0, irmaE.getvLig(irmaE.getTL()-1));
            
            pai.setvInfo(posPai-1, irmaE.getvInfo(irmaE.getTL()-1)); 
            pai.setvPos(posPai-1, irmaE.getvPos(irmaE.getTL()-1));
            
            irmaE.remanejarEx(irmaE.getTL()-1);
            irmaE.setTL(irmaE.getTL()-1);         
        }
        else
        if(irmaD != null && irmaD.getTL() > M)
        {
            folha.setvInfo(folha.getTL(), pai.getvInfo(posPai));
            folha.setvPos(folha.getTL(), pai.getvPos(posPai));
            folha.setTL(folha.getTL()+1);
            folha.setvLig(folha.getTL(), irmaD.getvLig(0));
            
            pai.setvInfo(posPai, irmaD.getvInfo(0));
            pai.setvPos(posPai, irmaD.getvPos(0));
            
            irmaD.remanejarEx(0);
            irmaD.setTL(irmaD.getTL()-1);
        }
        else //concatenação
        {
            if(irmaE != null)
            {
                irmaE.setvInfo(irmaE.getTL(), pai.getvInfo(posPai-1));
                irmaE.setvPos(irmaE.getTL(), pai.getvPos(posPai-1));
                irmaE.setTL(irmaE.getTL()+1);
                pai.remanejarEx(posPai-1);
                pai.setTL(pai.getTL()-1);
                pai.setvLig(posPai-1, irmaE);
                for(int i=0; i<folha.getTL(); i++)
                {
                    irmaE.setvInfo(irmaE.getTL(), folha.getvInfo(i));
                    irmaE.setvPos(irmaE.getTL(), folha.getvPos(i));
                    irmaE.setvLig(irmaE.getTL(), folha.getvLig(i));
                    irmaE.setTL(irmaE.getTL()+1);
                }
                irmaE.setvLig(irmaE.getTL(), folha.getvLig(folha.getTL()));
            }
            else       
            if(irmaD != null)
            {
                irmaD.remanejar(0);
                irmaD.setvInfo(0, pai.getvInfo(0));
                irmaD.setvPos(0, pai.getvPos(0));
                irmaD.setTL(irmaD.getTL()+1);
                pai.remanejarEx(0);
                pai.setTL(pai.getTL()-1);
                pai.setvLig(posPai, irmaD);
                if(folha.getvLig(posPai+1)!=null)
                    irmaD.setvLig(0, folha.getvLig(posPai+1));
                for(int i=0; i<folha.getTL(); i++)
                {
                    irmaD.remanejar(0);
                    irmaD.setvInfo(0, folha.getvInfo(i));
                    irmaD.setvPos(0, folha.getvPos(i));
                    irmaD.setvLig(0, folha.getvLig(i));
                    irmaD.setTL(irmaD.getTL()+1);
                }
                irmaD.setvLig(0, folha.getvLig(0));  
            }
        
            folha = pai;
            if(folha == raiz && folha.getTL() == 0)
            {
                if(irmaE != null)
                    raiz = irmaE;
                else
                    raiz = irmaD;
            }
            else
            if(folha != raiz && folha.getTL() < M)
                redistribuir_concatenar(folha); 
        } 
    }
    
    
}
