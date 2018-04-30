#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;
 
void lu(float ** a, float ** l, float ** u, int n){
    int i = 0, j = 0, k = 0;

    for (int i = 0; i < n; i++) {
 
        // Upper Triangular
        for (int k = i; k < n; k++) {
 
            // Summation of L(i, j) * U(j, k)
            int sum = 0;
            for (int j = 0; j < i; j++)
                sum += (l[i][j] * u[j][k]);
 
            // Evaluating U(i, k)
            u[i][k] = a[i][k] - sum;
        }
 
        // Lower Triangular
        for (int k = i; k < n; k++) {
            if (i == k)
                l[i][i] = 1; // Diagonal as 1
            else {

                // Summation of L(k, j) * U(j, i)
                int sum = 0;
                for (int j = 0; j < i; j++)
                    sum += (l[k][j] * u[j][i]);

                // Evaluating L(k, i)
                l[k][i] = (a[k][i] - sum) / u[i][i];
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
                if(valueString.at(0) == '-'){
                    valueString.append("-");
                    valueString = valueString.substr(0,valueString.length());
                    break;
                }
                else
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

    clock_time = (float)clock();
    lu(a, l, u, n);
    clock_time = (float)((clock() - clock_time)/CLOCKS_PER_SEC);

    cout << "Tempo de execucao: " <<  clock_time << " (s)" <<endl;



    
    /*output(a, n);
    cout << "\nL Decomposition\n";
    output(l, n);
    cout << "\nU Decomposition\n";
    output(u, n);*/

    return 0;
}