/*
 *  @Autor: Sousxs(Dubega)
 *  Date: 06/03/2024
 *  Description: 1007 - Diferença
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

public class beecrowd1008 {
 
    public static void main(String[] args) throws IOException {

InputStreamReader ir = new InputStreamReader(System.in);
BufferedReader in = new BufferedReader(ir);

int A, B;
double X;
double ValorFinal;

Scanner entrada = new Scanner(System.in);
            A = entrada.nextInt();
            B = entrada.nextInt();
            X = entrada.nextDouble();

            
ValorFinal = (X * B);

System.out.println("NUMBER = " + A);
System.out.printf("SALARY = U$ %.2f\n", ValorFinal);
}
}
