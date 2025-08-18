/*
 *  @Autor: Sousxs(Dubega)
 *  Date: 29/02/2024
 *  Description: 1001 - Extremamente Básico 
 */

import java.util.Scanner;
 
public class beecrowd1001 {
    public static void main (String[] args) {
		int A, B;
        int X;

        try (Scanner entrada = new Scanner (System.in)) {
            A = entrada.nextInt();
            B = entrada.nextInt();
        }
        X = A + B;

        System.out.printf("X = %d\n", X);
	}
}
