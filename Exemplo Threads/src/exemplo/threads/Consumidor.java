package exemplo.threads;

public class Consumidor extends Thread{
    
    private Estoque estoque;
    
    public Consumidor(){}
    
    public Consumidor(Estoque estoque){
        this.estoque = estoque;
    }
    
    public void consumir(){
        synchronized (estoque){
            
            if(estoque.getConteudo().size() > 0){
                Recurso recurso = (Recurso)estoque.getConteudo().remove(0);
                System.out.println("- "+this.getName()+ "\t -> Recurso consumido: "+ recurso);
            }
            else{
                try{
                    System.out.println("! "+ this.getName() + "\t -> Consumidor esperando estoque ser reposto...");
                    estoque.wait();
                }
                catch(InterruptedException e){
                    e.printStackTrace();
                }
            }
        }
    }
    
    public void run(){
        while(true){
            
            this.consumir();
            
            try{
                Thread.sleep((int)(Math.random()*Configuracoes.MAX_TIME_TO_SLEEP));
            }
            catch(InterruptedException e){
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
