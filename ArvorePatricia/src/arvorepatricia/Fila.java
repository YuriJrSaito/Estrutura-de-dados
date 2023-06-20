package arvorepatricia;

public class Fila {
    private NoFila inicio;
    private NoFila fim;

    public Fila() 
    {
        this.inicio = null;
        this.fim = null;
    }
    
    public boolean isEmpty()
    {
        return this.inicio == null;
    }
    
    public void enqueue(No no)
    {
        if (this.inicio == null)
            this.inicio = this.fim = new NoFila(no, null, null);
        else
        {
            NoFila temp = new NoFila(no, this.fim, null);
            this.fim.setProx(temp);
            this.fim = temp;
        }
    }
    
    public No dequeue()
    {
        No no = this.inicio.getInfo();
        this.inicio = this.inicio.getProx();
        if (this.inicio != null)
            this.inicio.setAnt(null);
        else
            this.fim = null;
        return no;
    }
}
