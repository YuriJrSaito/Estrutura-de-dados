package arvorenarea;

public class No implements Definicoes{
    private int vInfo[];
    private No vLig[];
    private int TL;
    
    public No()
    {
        vInfo = new int[N-1];
        vLig = new No[N];
        TL = 0;
    }
    
    public No(int info)
    {
        this();
        vInfo[0] = info;
        TL = 1;
    }

    public int getvInfo(int p) {
        return vInfo[p];
    }

    public void setvInfo(int p, int info) {
        this.vInfo[p] = info;
    }

    public No getvLig(int p) {
        return vLig[p];
    }

    public void setvLig(int p, No Lig) {
        this.vLig[p] = Lig;
    }

    public int getTL() {
        return TL;
    }

    public void setTL(int TL) {
        this.TL = TL;
    }
    
    public int buscarPos(int info)
    {
        int i = 0;
        while(i < TL && info > vInfo[i])
            i++;
        return i;
    }
    
    public void remanejar(int pos)
    {
        for(int i=TL; i > pos; i--)
            vInfo[i] = vInfo[i-1];
    }
    
}
