#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <fstream>
#include <vector>
#include <sstream>
#include <omp.h>
#include <cmath>

using namespace std;
 
void lu(float ** a, float ** l, float ** u, int n, int n_threads){
    int i = 0, j = 0, k = 0;

    #pragma omp parallel for private(i, k) num_threads(n_threads)
    for(j=0; j<n; j++){
        for(i=0; i<n; i++){
            if(i<=j){
                u[i][j]=a[i][j];
                for(k=0; k<=i-1; k++)
                    u[i][j]-=l[i][k]*u[k][j];
                if(i==j)
                    l[i][j]=1;
                else
                    l[i][j]=0;
            }else{
                l[i][j]=a[i][j];
                for(k=0; k<=j-1; k++)
                    l[i][j]-=l[i][k]*u[k][j];
                l[i][j]/=u[j][j];
                u[i][j]=0;
            }
        }
    }
}

void output(float ** x, int n){
    int i = 0, j = 0;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            printf("%f ", x[i][j]);
        }
        cout << "\n";
    }
}


void writeToCSV(float ** x, long long n, char* filename){
    std::ofstream outputFile;

    outputFile.open(filename, std::ofstream::out | std::ofstream::app);

    int i = 0, j = 0;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            outputFile << round(x[i][j]*10000)/10000.00 << ",";
        }
        outputFile << "\n";
    }

    outputFile.close();
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

float** fillMatrixFromCSV(char* filename, long long n){
    std::ifstream file;
    string line;
    int i = 0;

    float** a = new float*[n];

    for (int i = 0; i < n; i++){
		a[i] = new float[n];
	}

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

        for (int j = 0; j < n; j++){
            a[i][j] = values.at(j);
        }
        i++;
        values.clear();
    }

    file.close();

    return a;
}

int main(int argc, char **argv){
    int i = 0, j = 0;
    float clock_time;
    std::ofstream outputFile;

    char* a_filename;
    int n_threads;
    char* l_filename;
    char* u_filename;
    char* test_filename;

    if(argc == 6){
        n_threads = atoi(argv[1]);
        a_filename = argv[2];
        l_filename = argv[3];
        u_filename = argv[4];
        test_filename = argv[5];
	} else {
        cout << endl;
        cout << "WRONG OUTPUT!!!!!" << endl;
		cout << "Correct output: ./program_name N_THREADS A_CSV_NAME L_CSV_NAME U_CSV_NAME TEST_FILE_NAME" << endl << endl;
		exit(-1);
	}

    long long n = getSizeOfMatrix(a_filename);

    float** a;
	float** l = new float*[n];
	float** u = new float*[n];

    for (int i = 0; i < n; i++){
		l[i] = new float[n];
		u[i] = new float[n];
	}

    a = fillMatrixFromCSV(a_filename, n);

    clock_time = (float)omp_get_wtime();
    lu(a, l, u, n, n_threads);
    clock_time = (float)((omp_get_wtime() - clock_time));

    cout << "Tempo de execucao: " <<  clock_time << " (s)" <<endl;

    writeToCSV(l, n, l_filename);
    writeToCSV(u, n, u_filename);
    outputFile.open(test_filename, std::ofstream::out | std::ofstream::app);

    outputFile << "Medidas do algoritmo LU_OPENMP" << endl;
	outputFile << "Tamanho Matriz: " << n << " Tempo: " << clock_time << " (s)" << endl;

    outputFile.close();

    //output(a, n);
    /*cout << "\nL Decomposition\n";
    output(l, n);
    cout << "\nU Decomposition\n";
    output(u, n);*/

    return 0;
}