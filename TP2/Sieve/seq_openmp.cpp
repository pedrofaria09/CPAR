#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <omp.h>
#include <fstream>

using namespace std;

long long numberOfPrimes(vector<bool> values){
    long long count = 0;

    for(long long i = 0; i < values.size(); i++){
        if (values[i])
            count++;
    }
    return count;
}

void printPrimes(vector<bool> values){
    cout << "Numeros primos:";
    for(long long i = 0; i < values.size(); i++){
        if (values[i])
        cout << " " << (i+2) << " ";
    }
    cout << endl;
}

void writeToCSV(vector<bool> values, char* filename){
    std::ofstream outputFile;

    outputFile.open(filename, std::ofstream::out | std::ofstream::app);

    for(long long i = 0; i < values.size(); i++){
        if(values[i])
            outputFile << (i+2) << ",";
    }

    outputFile.close();
}

void seq_openmp(long long n, int n_threads, char* filename, char* test_filename) {
    std::ofstream outputFile;
    vector<bool> values(n-1, true);
    float clock_time;
    long long k = 2, small = 3, i = 0;

    clock_time = (float)omp_get_wtime();
    while (k*k <= n) {

        // Mark as false all multiples of k between k*k and n
        #pragma omp parallel for num_threads(n_threads)
        for (i = k*k; i <= n; i += k)
            values[i-2] = false;

		// Set k as the smaller urmarked number > k
        for(i = k+1; i <= n; i++){
            if (values[i-2]) {
                small = i;
                break;
            }
        }
        k = small;
	}
    clock_time = (float)((omp_get_wtime() - clock_time));

    cout << "Tempo de execucao: " <<  clock_time << " (s)" <<endl;

    int nr_primes = numberOfPrimes(values);

    cout << "Numero de primos: " << nr_primes << endl;

    outputFile.open(test_filename, std::ofstream::out | std::ofstream::app);
    outputFile << "Medidas do algoritmo SIEVE_OPENMP - Tamanho Primos: " << n << endl;
    outputFile << "Numeros primos encontrados: " << nr_primes << " Tempo: " << clock_time << " (s)" << endl;
    outputFile.close();

    //printPrimes(values);
    writeToCSV(values, filename);
}

int main(int argc, char **argv){
    if(argc == 1){
        int n, n_threads;
        char* filename, *test_file;

        cout << "Introduza a quantidade de numeros a verificar >";
        cin >> n;
        cout << "Introduza o numero de threads >";
        cin >> n_threads;
        cout << "Introduza o nome do ficheiro (Ex: teste.csv) >";
        cin >> filename;
        cout << "Introduza o nome do ficheiro de teste (Ex: teste.txt) >";
        cin >> test_file;

        seq_openmp(n, n_threads, filename, test_file);

    }else if(argc == 5){
        seq_openmp(atoi(argv[1]), atoi(argv[2]), argv[3], argv[4]);
    }else{
        cout << endl;
        cout << "WRONG OUTPUT!!!!!" << endl;
		cout << "Correct output: ./program_name Primes_to_verify N_THREADS CSV_file Test_file" << endl << endl;
        return -1;
    }
    
    return 0;
}