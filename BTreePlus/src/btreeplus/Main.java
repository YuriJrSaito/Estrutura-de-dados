package btreeplus;

public class Main {

    public static void main(String[] args) {
        BTreePlus b = new BTreePlus();
        
        b.inserir(1);
        b.inserir(4);
        b.inserir(7);
        b.inserir(10);
        b.inserir(17);
        b.inserir(21);
        b.inserir(31);
        b.inserir(25);
        b.inserir(19);
        b.inserir(20);
        b.inserir(28);
        b.inserir(42);
        
        /*for(int i=1; i<=100; i++)
            b.inserir(i);*/
        
        
        b.exibe();
    }
    
}
