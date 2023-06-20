package arvorenarea;

public class ArvoreNArea {

    public static void main(String[] args) {
        NArea arv = new NArea();
        arv.inserir(100);
        arv.inserir(80);
        arv.inserir(120);
        arv.inserir(40);
        arv.inserir(30);
        arv.inserir(38);
        arv.inserir(98);
        arv.inserir(85);
        arv.inserir(19);
        
        arv.inOrdem(arv.getRaiz());
    }
    
}
