#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <ctime>

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

    vector<bool> values(n-1, true);
    float clock_time;
    long long k = 2, small = 3, i = 0;

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

    cout << "Numero de primos: " << numberOfPrimes(values) << endl;
    //printPrimes(values);
}

int main(int argc, char **argv){

    if(argc == 1){
        int n;

        cout << "Introduza a quantidade de numeros a verificar >";
        cin >> n;

        seq(n);

    }else if(argc == 2){
        seq(atoi(argv[1]));
    }else{
        cout << "Input invalido! Introduza: ./file Nr_a_verificar_primos" << endl;
        return -1;
    }

    return 0;
}