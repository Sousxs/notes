/*
 *  @Autor: Sousxs(Dubega)
 *  Date: 01/03/2024
 *  Description: 1007 - Diferença
 */

import java.util.Scanner;

public class beecrowd1007 {
    public static void main(String[] args) {
		int A, B, C, D;

        try (Scanner entrada = new Scanner (System.in)) {
            A = entrada.nextInt();
            B = entrada.nextInt();
            C = entrada.nextInt();
            D = entrada.nextInt();
        }
        
        int valorfinal = ((A*B) -(C*D));
        
        System.out.println("DIFERENCA = "+ valorfinal);
	}
}
