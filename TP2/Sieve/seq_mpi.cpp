#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>

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

void seq(long long n) {
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
    long long bk_low = 2+BK_LOW(world_rank, n-1, world_size);
    long long bk_high = 2+BK_HIGH(world_rank, n-1, world_size);

    vector<bool> values(bk_size, true);

    while (k*k <= n) {

        if(k*k < bk_low){
            if(bk_low % k == 0){
                j = bk_low;
            }else{
                j = (bk_low + (k-(bk_low % k)));
            }
        }else{
            j = k*k;
        }

        // Mark as false all multiples of k between k*k and n
        for (i = j; i <= bk_high; i += k){
            values[i-bk_low] = false;
        }

        // Set k as the smaller urmarked number > k
        if(world_rank == root){
            for(i = k+1; i < bk_high; i++){
                if (values[i-bk_low]) {
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

}

int main(int argc, char **argv){

    seq(300000000);

    /*if(argc == 1){
        int n;

        cout << "Introduza a quantidade de numeros a verificar >";
        cin >> n;

        seq(n);

    }else if(argc == 2){
        seq(atoi(argv[1]));
    }else{
        cout << "Input invalido! Introduza: ./file Nr_a_verificar_primos" << endl;
        return -1;
    }*/

    return 0;
}
