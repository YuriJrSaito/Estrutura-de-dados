package arvoreb;

public class ArvoreB{
    public static void main(String[] args) {
        BTree b = new BTree();
        for(int i=1; i<=1000000; i++)
            b.inserir(i, 0);
        
        for(int i=10; i<=999990;i++)
            b.excluir(i);        
        
        b.inOrdem(b.getRaiz());
    }  
}
