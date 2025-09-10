package ED1.java;

import java.util.LinkedList;

public class linkedList {
    public static void main(String[] args) {
        LinkedList<String> carros = new LinkedList<>();
        //adiciona elementos na lista
        carros.add("BMW");
        carros.addFirst("Audi");
        carros.addFirst("Honda");

        //print o primeiro elemento da lista
        System.out.println(carros.getFirst());
        //retorno: Honda

        System.out.println(carros.getLast());
        //retorno: BMW

        //remover elemento do meio
        System.out.println(carros.remove(carros.size()/2));

        //trocar nome do elemento
        carros.set(0, "Ferrari");
        carros.set(1, "Mercedes");
        System.out.println(carros);

        //limpar a lista completa
        carros.clear();
        System.out.println(carros);
    }
    
}
