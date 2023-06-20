package arvorepatricia;

public class Executar {

    public static void main(String[] args) {
        Patricia arv = new Patricia();
        String[] palavras = {
            "bear", "Bell", "bid", "Bull", "buy", "sell", "stock", "stop",
                
            "acao",
            "acordado",
            "afavel",
            "amizade",
            "amor",
            "atividade",
            "aurora",
            "autentico",
            "algoritmo",
            
            "pedro",
            "paulo",
            "palacio",
            "palmeira",
            "plutao",
            "plantina",
            "palanque",
            "pulga",
            "pulmao",
            "pena",
            "pindamonhangaba",
            
            "cafe",
            "cafeina",
            "caramujo",
            "camelo",
            "caramelo",
            "chico",
            "cachaca",
            "chefe",
            "chao",
            
            "sagacidade",
            "salientar",
            "sarcasmo",
            "satisfacaoo",
            "sensacional",
            "serenidade",
            "singelo",
            "sintese"
        };
        
        //String[] palavras = {"dores","dor","dores"};
        for (String palavra : palavras) 
            arv.Inserir(palavra);
        
        // Mostrar nivel a nivel
        //arv.exibirNivel();
        
        arv.exibirArvore();
    }
}
