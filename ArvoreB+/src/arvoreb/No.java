package arvoreb;

public class No implements Ligacoes{
    
    private int[] vInfo;
    private int[] vPos;
    private No[] vLig;
    private int TL;
    private No ant;
    private No prox;
    
    public No() 
    {
        vInfo = new int[N];
        vPos = new int[N];
        vLig = new No[N + 1];
        ant = prox = null;
        TL = 0;
    }

    public No(int info) 
    {
        vInfo = new int[N];
        vPos = new int[N];
        vLig = new No[N + 1];
        ant = prox = null;

        vInfo[0] = info;
        TL = 1;
    }

    public No getAnt() {
        return ant;
    }

    public void setAnt(No ant) {
        ant = ant;
    }

    public No getProx() {
        return prox;
    }

    public void setProx(No prox) {
        this.prox = prox;
    }

    public int getvInfo(int pos) {
        return vInfo[pos];
    }

    public void setvInfo(int pos, int info) {
        vInfo[pos] = info;
    }

    public int getvPos(int pos) {
        return vPos[pos];
    }

    public void setvPos(int pos, int info) {
        vPos[pos] = info;
    }

    public No getvLig(int pos) {
        return vLig[pos];
    }

    public void setvLig(int pos, No no) {
        vLig[pos] = no;
    }

    public int getTL() {
        return TL;
    }

    public void setTL(int TL) {
        this.TL = TL;
    }

    public int procurarPosicao(int info) {
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
            vPos[i] = vPos[i-1];
            vLig[i] = vLig[i-1];
        }
    }
}
