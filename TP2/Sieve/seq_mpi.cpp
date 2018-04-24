#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <fstream>

#include "mpi.h"

#define BK_LOW(i,n,p) ((i)*(n)/(p))
#define BK_HIGH(i,n,p) (BK_LOW((i)+1,n,p)-1)
#define BK_SIZE(i,n,p) (BK_LOW((i)+1,n,p)-BK_LOW(i,n,p))

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

void seq(long long n, char* filename) {
    // Initialize the MPI environment
    MPI_Init( NULL, NULL );

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    float init_time, fin_time;
    long long k = 2, i = 0, j = 0;
    int root = 0, total_primes = 0;

    if(world_rank == root)
        init_time = (float)clock();

    long long bk_size = BK_SIZE(world_rank, n-1, world_size);
    long long low_value = 2+BK_LOW(world_rank, n-1, world_size);
    long long high_value = 2+BK_HIGH(world_rank, n-1, world_size);

    vector<bool> values(bk_size, true);

    while (k*k <= n) {

        if(k*k < low_value){
            if(low_value % k == 0){
                j = low_value;
            }else{
                j = (low_value + (k-(low_value % k)));
            }
        }else{
            j = k*k;
        }

        // Mark as false all multiples of k between k*k and n
        for (i = j; i <= high_value; i += k){
            values[i-low_value] = false;
        }

        // Set k as the smaller urmarked number > k
        if(world_rank == root){
            for(i = k+1; i < high_value; i++){
                if (values[i-low_value]) {
                    k = i;
                    break;
                }
            }
        }

        MPI_Bcast(&k, 1, MPI_INT, root, MPI_COMM_WORLD);
        
    }

    int block_primes = numberOfPrimes(values);

    MPI_Reduce(&block_primes, &total_primes, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);
    
    if(world_rank == root){
        fin_time = (float)((clock() - init_time)/CLOCKS_PER_SEC);

        cout << "Tempo de execucao: " <<  fin_time << " (s)" <<endl;

        cout << "Numero de primos: " << total_primes << endl;
    }

    MPI_Finalize();

    printPrimes(values);
    writeToCSV(values, filename);

}

int main(int argc, char **argv){

    if(argc == 1){
        int n;
        char* filename;

        cout << "Introduza a quantidade de numeros a verificar >";
        cin >> n;
        cout << "Introduza o nome do ficheiro (Ex: teste.csv) >";
        cin >> filename;

        seq(n, filename);

    }else if(argc == 3){
        seq(atoi(argv[2]), argv[1]);
    }else{
        cout << "Input invalido! Introduza: ./file Nome_Ficheiro_CSV Nr_a_verificar_primos" << endl;
        return -1;
    }

    return 0;
}
