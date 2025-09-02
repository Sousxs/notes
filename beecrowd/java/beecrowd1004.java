/*
 *  @Autor: Sousxs(Dubega)
 *  Date: 01/03/2024
 *  Description: 1007 - Diferença
 */

import java.util.Scanner;

public class beecrowd1004 {
    public static void main(String[] args) {
		int A, B;
        int X;

        try (Scanner entrada = new Scanner (System.in)) {
            A = entrada.nextInt();
            B = entrada.nextInt();
        }
        X = A * B;

        System.out.printf("PROD = %d\n", X);
	}
}
