#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <fstream>
#include <vector>
#include <sstream>
#include <omp.h>

using namespace std;
 
void lu(float ** a, float ** l, float ** u, int n, int n_threads){
    int i = 0, j = 0, k = 0;

    #pragma omp parallel for private(j, k) num_threads(n_threads)
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            if (j < i)
                l[j][i] = 0;
            else{
                l[j][i] = a[j][i];
                for (k = 0; k < i; k++){
                    l[j][i] = l[j][i] - l[j][k] * u[k][i];
                }
            }
        }
        for (j = 0; j < n; j++){
            if (j < i)
                u[i][j] = 0;
            else if (j == i)
                u[i][j] = 1;
            else{
                u[i][j] = a[i][j] / l[i][i];
                for (k = 0; k < i; k++){
                    u[i][j] = u[i][j] - ((l[i][k] * u[k][j]) / l[i][i]);
                }
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

    vector<int> values;
    while(getline(file,line)){

        string valueString;
        int valueInt = 0;
        istringstream lineIss(line);

        while(getline(lineIss, valueString, ';')){

            while(!isdigit(valueString.at(0))){
                valueString = valueString.substr(1,valueString.length());
            }

            values.push_back(atoi(valueString.c_str()));
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

    char* filename = argv[1];

    long long n = getSizeOfMatrix(filename);

    float** a;
	float** l = new float*[n];
	float** u = new float*[n];

    for (int i = 0; i < n; i++){
		l[i] = new float[n];
		u[i] = new float[n];
	}

    a = fillMatrixFromCSV(filename, n);

    clock_time = (float)omp_get_wtime();
    lu(a, l, u, n, atoi(argv[2]));
    clock_time = (float)((omp_get_wtime() - clock_time));

    cout << "Tempo de execucao: " <<  clock_time << " (s)" <<endl;



    
    /*output(a, n);
    cout << "\nL Decomposition\n";
    output(l, n);
    cout << "\nU Decomposition\n";
    output(u, n);*/

    return 0;
}