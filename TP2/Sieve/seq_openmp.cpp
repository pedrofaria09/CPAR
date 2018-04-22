#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <omp.h>

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

void seq_openmp(long long n, int n_threads) {

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

    cout << "Numero de primos: " << numberOfPrimes(values) << endl;
    //printPrimes(values);
}

int main(int argc, char **argv){
    if(argc == 1){
        int n, n_threads;

        cout << "Introduza a quantidade de numeros a verificar >";
        cin >> n;
        cout << "Introduza o numero de threads >";
        cin >> n_threads;

        seq_openmp(n, n_threads);

    }else if(argc == 3){
        seq_openmp(atoi(argv[1]), atoi(argv[2]));
    }else{
        cout << "Input invalido! Introduza: ./file Nr_a_verificar_primos Nr_Threads" << endl;
        return -1;
    }
    
    return 0;
}