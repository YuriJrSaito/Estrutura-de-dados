package arvorepatricia;

public class NoFila {
    private No info;
    private NoFila prox;
    private NoFila ant;
    
    public NoFila(No info, NoFila ant, NoFila prox)
    {
        this.info = info;
        this.ant = ant;
        this.prox = prox;
    }
    
    public No getInfo() 
    {
        return info;
    }
    
    public void setInfo(No info) 
    {
        this.info = info;
    }
    
    public NoFila getAnt() 
    {
        return ant;
    }
    
    public void setAnt(NoFila ant) 
    {
        this.ant = ant;
    }
    
    public NoFila getProx() 
    {
        return prox;
    }
    
    public void setProx(NoFila prox) 
    {
        this.prox = prox;
    }
}
