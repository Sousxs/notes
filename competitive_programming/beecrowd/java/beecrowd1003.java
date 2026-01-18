/*
 *  @Autor: Sousxs(Dubega)
 *  Date: 01/03/2024
 *  Description: 1003 - Soma Simples
 */

import java.util.Scanner;

public class beecrowd1003 {
    public static void main(String[] args) {
		int A, B;
        int X;

        try (Scanner entrada = new Scanner (System.in)) {
            A = entrada.nextInt();
            B = entrada.nextInt();
        }
        X = A + B;

        System.out.printf("SOMA = %d\n", X);
	}
}
