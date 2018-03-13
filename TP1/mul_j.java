import java.util.Scanner;
import java.util.concurrent.TimeUnit;

public class mul_j {

	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		int n, choice;

		System.out.print("Introduza o tamanho das matrizes > ");
		n = input.nextInt();

		System.out.println("\n===== MENU =====\n 1-Linha/Coluna \n 2-Elemento/Coluna \n 3-Ambos(1 e 2)");
		System.out.print("Escolha a multiplicação > ");
		choice = input.nextInt();


		int[][] a = new int[n][n];
		int[][] b = new int[n][n];
		int[][] c = new int[n][n];

		//Filling all the positions of the matrix a with value 1
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				a[i][j] = (int)1;
			}
		}


		//Filling all the positions of the matrix b with value 1
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				b[i][j] = (int)1;
			}
		}

		//calling multiplication
		if(choice == 1 || choice == 3) {
			long startTime = System.nanoTime();

			multiplication1(n, c, a, b);

			long duration = System.nanoTime() - startTime;
			long duration1 = duration /1000000;
			long seconds = TimeUnit.NANOSECONDS.toSeconds(System.nanoTime() - startTime);

			System.out.println("Tempo de execucao 1: " + duration1 + "ms");
		}
		else if(choice <= 0 || choice >= 4){
			System.out.println("Por favor escolha uma opcao correta");
		}

		if(choice == 2 || choice == 3){
			long startTime = System.nanoTime();

			multiplication2(n, c, a, b);

			long duration = System.nanoTime() - startTime;
			long duration1 = duration /1000000;
			long seconds = TimeUnit.NANOSECONDS.toSeconds(System.nanoTime() - startTime);

			System.out.println("Tempo de execucao 2: " + duration1 + "ms");
		}

	}

	public static void multiplication1(int n, int c[][], int a[][], int b[][]) {
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				for (int k = 0; k < n; k++){
					c[i][j] += a[i][k] * b[k][j];
				}
			}
		}
	}

	public static void multiplication2(int n, int c[][], int a[][], int b[][]) {
		for (int i = 0; i < n; i++){
			for (int k = 0; k < n; k++){
				for (int j = 0; j < n; j++){
					c[i][j] += a[i][k] * b[k][j];
				}
			}
		}
	}

}
