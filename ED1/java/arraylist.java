package ED1.java;

import java.util.ArrayList;

public class arraylist {
    public static void main(String[] args) {
        ArrayList<String> carros = new ArrayList<>();
        //adiciona elementos na lista
        carros.add("BMW");
        carros.add(1,"Audi");
        carros.add("Honda");

        //print o primeiro elemento da lista
        System.out.println(carros.get(0));
        //retorno: BMW

        //remover elemento do meio
        System.out.println(carros.remove(carros.size()/2));

        //trocar nome do elemento
        carros.set(0, "Ferrari");
        carros.set(1, "Mercedes");

        carros.clear();
        
        System.out.println(carros);
        //retorno: [Ferrari, Mercedes]
    }
}
