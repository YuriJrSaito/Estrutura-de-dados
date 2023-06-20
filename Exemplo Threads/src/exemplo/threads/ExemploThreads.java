package exemplo.threads;

public class ExemploThreads {

    public static void main(String[] args) {
        
        Estoque estoque = new Estoque();
        
        Produtor produtor = new Produtor(estoque);
        produtor.setName("Produtor");
        
        Consumidor consumidor1 = new Consumidor(estoque);
        consumidor1.setName("Consumidor_1");
        
        Consumidor consumidor2 = new Consumidor(estoque);
        consumidor2.setName("Consumidor_2");
        
        consumidor1.setPriority(Thread.MIN_PRIORITY);
        
        produtor.start();
        consumidor1.start();
        consumidor2.start();
    }
}
