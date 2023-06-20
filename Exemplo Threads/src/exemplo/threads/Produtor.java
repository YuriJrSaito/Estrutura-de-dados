package exemplo.threads;

public class Produtor extends Thread{
    
    private Estoque estoque;
    
    public Produtor(){}
    
    public Produtor(Estoque estoque){
        this.estoque = estoque;
    }
    
    public void produzir(){
        
        synchronized (estoque){
            
            Recurso recurso = new Recurso((int)(Math.random()*100));
            this.estoque.getConteudo().add(recurso);
            System.out.println("+ " + this.getName() + "\t -> Recurso produzido: " + recurso);
            estoque.notifyAll();
        }
    }
    
    public void run(){
        while(true){
            
            this.produzir();
            
            try{
                Thread.sleep((int)(Math.random() * Configuracoes.MAX_TIME_TO_SLEEP));
            }
            catch (InterruptedException e){
                e.printStackTrace();
            }
        }
    }
    
    public Estoque getEstoque(){
        return estoque;
    }
    
    public void setEstoque(Estoque estoque){
        this.estoque = estoque;
    }
}
