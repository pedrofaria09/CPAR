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

void printPrimes(vector<bool> values, int bk_size, int low_value, bool flag){
    if(flag)
        cout <<"Numeros primos:";
    for(long long i = 0; i < bk_size; i++){
        if (values[i])
            cout << " " << (low_value+i) << " ";
    }
}

void writeToCSV(vector<bool> values, char* filename, int bk_size, int low_value){
    std::ofstream outputFile;

    outputFile.open(filename, std::ofstream::out | std::ofstream::app);

    for(long long i = 0; i < bk_size; i++){
        if(values[i])
            outputFile << (low_value+i) << ",";
    }

    outputFile.close();
}

void seq(long long n, char* filename, char* test_filename) {
    std::ofstream outputFile;
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

        outputFile.open(test_filename, std::ofstream::out | std::ofstream::app);
        outputFile << "Medidas do algoritmo SIEVE_MPI - Tamanho Primos: " << n << endl;
        outputFile << "Numeros primos encontrados: " << total_primes << " Tempo: " << fin_time << " (s)" << endl;
        outputFile.close();

        //printPrimes(values, bk_size, low_value, 1);
        writeToCSV(values, filename, bk_size, low_value);
        //MPI_Send(&world_rank, 1, MPI_INT, ++world_rank, 0, MPI_COMM_WORLD);

    }
    //else if(world_rank != 0){

        //MPI_Recv(&world_rank, 1, MPI_INT, (world_rank-1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        //printPrimes(values, bk_size, low_value, 0);
        //writeToCSV(values, filename, bk_size, low_value);

        //if(world_size-1 != world_rank)
            //MPI_Send(&world_rank, 1, MPI_INT, world_rank+1, 0, MPI_COMM_WORLD);
    //}

    MPI_Finalize();

}

int main(int argc, char **argv){

    if(argc == 1){
        int n;
        char* filename, *test_file;

        cout << "Introduza a quantidade de numeros a verificar >";
        cin >> n;
        cout << "Introduza o nome do ficheiro (Ex: teste.csv) >";
        cin >> filename;
        cout << "Introduza o nome do ficheiro de teste (Ex: teste.txt) >";
        cin >> test_file;

        seq(n, filename, test_file);

    }else if(argc == 4){
        seq(atoi(argv[1]), argv[2], argv[3]);
        //cout << endl;
    }else{
        cout << endl;
        cout << "WRONG OUTPUT!!!!!" << endl;
		cout << "Correct output: ./program_name Primes_to_verify CSV_file Test_file" << endl << endl;
        return -1;
    }

    return 0;
}
