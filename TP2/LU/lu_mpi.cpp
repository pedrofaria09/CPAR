#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include "mpi.h"

using namespace std;

float* fillMatrixFromCSV(char* filename, long long n){
    std::ifstream file;
    string line;
    int i = 0;

    float*a = new float[n*n];

    file.open(filename);

    vector<float> values;
    while(getline(file,line)){

        string valueString;
        istringstream lineIss(line);

        while(getline(lineIss, valueString, ',')){
            
            while(!isdigit(valueString.at(0))){
                if(valueString.at(0) == '-'){
                    valueString.append("-");
                    valueString = valueString.substr(0,valueString.length());
                    break;
                }
                else
                    valueString = valueString.substr(1,valueString.length());
            }

            values.push_back(strtof(valueString.c_str(),0));
        }

    }
    for(i = 0; i < n*n; i++){
        a[i] = values.at(i);
    }

    file.close();

    return a;
}

long long getSizeOfMatrix(char* filename){
    std::ifstream file;
    long long size = 0;
    string line;

    file.open(filename);

    while(getline(file,line)){
        ++size;
    }
    file.close();
    
    return size;
}

void output(float * x, int n){
    int i;
    for (i = 0; i < n*n; i++){
        printf("%f ", x[i]);
        if((i+1)%n == 0)
            cout << endl;
    }
}

void lu(float * a, long long n, int world_size, int world_rank){
    int i, j, ref_diag = 0;

    for(i = 0; i < n-1; i++, ref_diag++){
        float* row_diag = &a[ref_diag * n + ref_diag];

        for(j = ref_diag + 1; j < n; j++){

            if(j % world_size == world_rank){
                float* back = &a[j * n + ref_diag];

                if(*back == 0)
                    return;

                float k = *back / row_diag[0];
                int w;

                for (w = 1; w < n - ref_diag; w++) {
                    (back)[w] = (back)[w] - k * row_diag[w];
                }
                *back = k;
            }
        }
        
        for(j = ref_diag+1; j < n; j++){
            float* back = &a[j * n + ref_diag];
            MPI_Bcast(back, n-ref_diag, MPI_FLOAT, j % world_size, MPI_COMM_WORLD);
        }
    }
}

float* fill_L(float* a, long long n){
    int i, j;

    float*l = new float[n*n];

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(j>i)
                l[i*n+j]=0;
            else if(i==j)
                l[i*n+j]=1;
            else
                l[i*n+j]=a[i*n+j];
        }
    }
    return l;
}

float* fill_U(float* a, long long n){
    int i, j;

    float*u = new float[n*n];

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(j>=i)
                u[i*n+j]=a[i*n+j];
            else
                u[i*n+j]=0;
                
        }
    }
    return u;
}

void writeToCSV(float * x, int n, char* filename){
    std::ofstream outputFile;

    outputFile.open(filename, std::ofstream::out | std::ofstream::app);

    int i = 0;
    for (i = 0; i < n*n; i++){
        outputFile << round(x[i]*10000)/10000.00 << ",";
        if((i+1)%n == 0)
            outputFile << endl;
    }

    outputFile.close();
}

int main(int argc, char **argv){
    float init_time, fin_time;
    int root = 0;
    std::ofstream outputFile;

    char* a_filename;
    char* l_filename;
    char* u_filename;
    char* test_filename;

    if(argc == 5){
        a_filename = argv[1];
        l_filename = argv[2];
        u_filename = argv[3];
        test_filename = argv[4];
	} else {
        cout << endl;
        cout << "WRONG OUTPUT!!!!!" << endl;
		cout << "Correct output: ./program_name A_CSV_NAME L_CSV_NAME U_CSV_NAME TEST_FILE_NAME" << endl << endl;
		exit(-1);
	}

    long long n = getSizeOfMatrix(a_filename);

    float* a = fillMatrixFromCSV(a_filename, n);
    float* l = new float[n*n];
    float* u = new float[n*n];

    // Initialize the MPI environment
    MPI_Init( NULL, NULL );

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if(world_rank == root)
        init_time = (float)clock();
    
    lu(a, n, world_size, world_rank);

    if(world_rank == root){
        fin_time = (float)((clock() - init_time)/CLOCKS_PER_SEC);
        
        l = fill_L(a, n);
        u = fill_U(a, n);
        
        cout << "Tempo de execucao: " <<  fin_time << " (s)" <<endl;

        writeToCSV(l, n, l_filename);
        writeToCSV(u, n, u_filename);

        outputFile.open(test_filename, std::ofstream::out | std::ofstream::app);
        outputFile << "Medidas do algoritmo LU_MPI" << endl;
        outputFile << "Tamanho Matriz: " << n << " Tempo: " << fin_time << " (s)" << endl;
        outputFile.close();

        //output(a, n);
        /*cout << "\nL Decomposition\n";
        output(l,n);
        cout << "\nU Decomposition\n";
        output(u, n);*/
    }

    MPI_Finalize();

    return 0;
}