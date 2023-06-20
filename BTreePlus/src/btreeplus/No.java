package btreeplus;

public class No implements Ligacoes{
    private int[] vInfo;
    private No[] vLig;
    private int TL;
    private No ant;
    private No prox;
    
    public No()
    {
        vInfo = new int[N];
        vLig = new No[N+1];
        ant = prox = null;
        TL=0;
    }
    
    public No(int info)
    {
        this();
        vInfo[0] = info;
        TL = 1;
    }

    public int getvInfo(int pos) {
        return vInfo[pos];
    }

    public void setvInfo(int pos, int info) {
        this.vInfo[pos] = info;
    }

    public No getvLig(int pos) {
        return vLig[pos];
    }

    public void setvLig(int pos, No lig) {
        this.vLig[pos] = lig;
    }

    public int getTL() {
        return TL;
    }

    public void setTL(int TL) {
        this.TL = TL;
    }

    public No getAnt() {
        return ant;
    }

    public void setAnt(No ant) {
        this.ant = ant;
    }

    public No getProx() {
        return prox;
    }

    public void setProx(No prox) {
        this.prox = prox;
    }
    
    public int procurarPosicao(int info) 
    {
        int pos=0;
        while(pos < TL && info > vInfo[pos])
            pos++;
        return pos;
    }

    public void remanejar(int pos) 
    {
        vLig[TL+1] = vLig[TL];
        for(int i=TL; i>pos; i--)
        {
            vInfo[i] = vInfo[i-1];
            vLig[i] = vLig[i-1];
        }
    } 
}
