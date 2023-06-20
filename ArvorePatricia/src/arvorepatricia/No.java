package arvorepatricia;

public class No {
    private String Info;
    private int TL;
    private No vLig[];
    private boolean Final;

    public No() 
    {
        this.Info = "";
        this.TL = 0;
        this.vLig = new No[26];
    }
    
    public No(String info) 
    {
        this.Info = info;
        this.vLig = new No[26];
        this.TL = 0;
    }
    
    public String getInfo() 
    {
        return Info;
    }
    
    public void setInfo(String Info) 
    {
        this.Info = Info;
    }
    
    public int getTL() 
    {
        return TL;
    }
    
    public void setTL(int TL) 
    {
        this.TL = TL;
    }
    
    public No getvLig(int pos) 
    {
        return vLig[pos];
    }
    
    public void setvLig(int pos, No no) 
    {
        this.vLig[pos] = no;
    }
    
    public boolean chegouFinal() 
    {
        return Final;
    }
    
    public void setFinal(boolean Final) 
    {
        this.Final = Final;
    }
    
    public No[] getvLig() 
    {
        return vLig;
    }
    
    public void setvLig(No[] vLig) 
    {
        this.vLig = vLig;
    }
}
