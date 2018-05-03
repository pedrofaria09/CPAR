#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <ctime>
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

void seq(long long n, char* filename, char* test_filename) {
    vector<bool> values(n-1, true);
    float clock_time;
    long long k = 2, small = 3, i = 0;
    std::ofstream outputFile;

    clock_time = (float)clock();
    while (k*k <= n) {
        // Mark as false all multiples of k between k*k and n
        for (i = k*k; i <= n; i += k){
            values[i-2] = false;
        }

        // Set k as the smaller urmarked number > k
        for(i = k+1; i <= n; i++){
            if (values[i-2]) {
                small = i;
                break;
            }
        }
        k = small;
    }
    clock_time = (float)((clock() - clock_time)/CLOCKS_PER_SEC);

    cout << "Tempo de execucao: " <<  clock_time << " (s)" <<endl;

    int nr_primes = numberOfPrimes(values);

    cout << "Numero de primos: " << nr_primes << endl;

    outputFile.open(test_filename, std::ofstream::out | std::ofstream::app);
    outputFile << "Medidas do algoritmo SIEVE_NORMAL - Tamanho Primos: " << n << endl;
    outputFile << "Numeros primos encontrados: " << nr_primes << " Tempo: " << clock_time << " (s)" << endl;
    outputFile.close();

    //printPrimes(values);
    writeToCSV(values, filename);
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
    }else{
        cout << endl;
        cout << "WRONG OUTPUT!!!!!" << endl;
		cout << "Correct output: ./program_name Primes_to_verify CSV_file Test_file" << endl << endl;
        return -1;
    }

    return 0;
}