/*
 * mul.cpp
 *
 *  Created on: 20/02/2018
 *      Author: pedrofaria
 */

#include <omp.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "papi.h"

using namespace std;

void MulLineCol_omp(int n, float ** a, float ** b, float ** c, int n_threads){
	int i, j, k;

	#pragma omp parallel for private(j, k) num_threads(n_threads)
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			for(k = 0; k < n; k++){
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}

void MulEleCol_omp(int n, float ** a, float ** b, float ** c, int n_threads){
	int i, j, k;

	#pragma omp parallel for private(k, j) num_threads(n_threads)
	for(i = 0; i < n; i++){
		for(k = 0; k < n; k++){
			for(j = 0; j < n; j++){
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}

void MulLineCol(int n, float ** a, float ** b, float ** c){
	int i, j, k;

	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			for(k = 0; k < n; k++){
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}

void MulEleCol(int n, float ** a, float ** b, float ** c){
	int i, j, k;

	for(i = 0; i < n; i++){
		for(k = 0; k < n; k++){
			for(j = 0; j < n; j++){
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}


int main(int argc, char *argv[]) {
	int n, choice, retval, cml1flops, cml2flops;
	float clock_time, instPc;
	int EventSet=PAPI_NULL;
	int n_threads = 1;
	long long values[3];
	int flop_s;

	std::ofstream outputFile;

	if(argc == 1){
		cout << "Introduza o tamanho das matrizes > ";
		cin >> n;

		cout << "\n\n===== MENU =====\n 1-Linha/Coluna \n 2-Elemento/Coluna \n 3-Ambos(1 e 2)" << endl ;
		cout << " 4-Linha/Coluna-Paralelizada \n 5-Elemento/Coluna-Paralelizada \n 6-Ambos(4 e 5)" << endl;
		cout << "Escolha a multiplicação > ";
		cin >> choice;

		if(choice == 4 || choice == 5 || choice == 6){
			cout << "Introduza o nr de threads > ";
			cin >> n_threads;
		}
		outputFile.open("test_cpp.txt", std::ofstream::out | std::ofstream::app);

	} else if(argc == 5){
		n = atoi(argv[1]);
		choice = atoi(argv[2]);
		n_threads = atoi(argv[3]);

		outputFile.open(argv[4], std::ofstream::out | std::ofstream::app);

	} else {
		cout << "Correct output: ./file Matrix_Size Option Nr_Threads File_Name" << endl;
		cout << "\n===== Options =====\n 1-Linha/Coluna \n 2-Elemento/Coluna \n 3-Ambos(1 e 2)" << endl ;
		cout << " 4-Linha/Coluna-Paralelizada \n 5-Elemento/Coluna-Paralelizada \n 6-Ambos(4 e 5)\n\n" << endl;
		exit(-1);
	}

	float** a = new float*[n];
	float** b = new float*[n];
	float** c = new float*[n];

	//	float** a = (float**) malloc(sizeof(float*)*n);
	//	float** b = (float**) malloc(sizeof(float*)*n);
	//	float** c = (float**) malloc(sizeof(float*)*n);

	for (int i = 0; i < n; i++){
		//		a[i] = (float*) malloc(sizeof(float)*n);
		//		b[i] = (float*) malloc(sizeof(float)*n);
		//		c[i] = (float*) malloc(sizeof(float)*n);
		a[i] = new float[n];
		b[i] = new float[n];
		c[i] = new float[n];
	}

	//Filling all the positions of the matrix a with value 1
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
		{
			a[i][j] = 1;
		}
	}

	//Filling all the positions of the matrix b with value 1
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
		{
			b[i][j] = 1;
		}
	}

	if(choice == 1 || choice == 3 || choice == 4 || choice == 6){

		if((retval = PAPI_library_init(PAPI_VER_CURRENT)) != PAPI_VER_CURRENT){
			PAPI_perror("PAPI_library_init_1");
			exit(-1);
		}

		if((retval = PAPI_create_eventset(&EventSet)) != PAPI_OK){
			PAPI_perror("PAPI_create_eventset_1");
			exit(-1);
	  }

		if((retval = PAPI_add_event(EventSet, PAPI_L1_DCM)) != PAPI_OK){
			PAPI_perror("PAPI_add_event_L1_DCM_1");
			exit(-1);
		}

		if((retval = PAPI_add_event(EventSet, PAPI_L2_DCM)) != PAPI_OK){
			PAPI_perror("PAPI_add_event_L2_DCM_1");
			exit(-1);
		}

		if((retval = PAPI_add_event(EventSet, PAPI_TOT_INS)) != PAPI_OK){
			PAPI_perror("PAPI_add_event_TOT_INS_1");
			exit(-1);
		}

		if((retval = PAPI_add_event(EventSet, PAPI_TOT_CYC)) != PAPI_OK){
			PAPI_perror("PAPI_add_event_TOT_CYC_1");
			exit(-1);
		}

		if((retval = PAPI_start(EventSet)) != PAPI_OK ){
			PAPI_perror("PAPI_start_1");
			exit(-1);
		}

		cout << "Calculando..." << endl;

		if(choice == 1 || choice == 3){
			clock_time = (float)clock();

			//Multiplication of Matrix a b, in c - Line with Column
			MulLineCol(n, a, b, c);

			clock_time = (float)((clock() - clock_time)/CLOCKS_PER_SEC);
		} else {
			clock_time = (float)omp_get_wtime();

			//Multiplication of Matrix a b, in c - Line with Column
			MulLineCol_omp(n, a, b, c, n_threads);

			clock_time = (float)((omp_get_wtime() - clock_time));
		}


		if((retval = PAPI_stop(EventSet, values)) != PAPI_OK ){
			PAPI_perror("PAPI_stop_1");
			exit(-1);
	  }

		flop_s = ((2*(n^3))/clock_time);
		//cml1flops = values[0]/(2*(n^3));
		//cml2flops = values[1]/(2*(n^3));
		instPc = (float)values[2]/(float)values[3];

		printf("Medidas do algoritmo 1: \n");
		printf("Tempo: %f(s) MFlops: %d \nInstrucoes: %lld Ciclos: %lld Instr/Ciclos: %f \nL1_DCM: %lld  L2_DCM: %lld \n", clock_time, flop_s, values[2], values[3], instPc, values[0], values[1]);
		printf("============================ \n\n");

		outputFile << "Medidas do algoritmo 1 - Tamanho Matriz: " << n << endl;
		outputFile << "Tempo: " << clock_time << "(s) MFlops: " << flop_s << " Instrucoes: " << values[2] << " Ciclos: " << values[3] << " Instr/Ciclos: " << instPc << endl;
		outputFile << "L1_DCM: " <<  values[0] << " L2_DCM: " << values[1] << endl;


		if((retval = PAPI_reset(EventSet)) != PAPI_OK ){
			PAPI_perror("PAPI_reset_1");
			exit(-1);
	  }

		if((retval = PAPI_remove_event(EventSet, PAPI_L1_DCM)) != PAPI_OK ){
			PAPI_perror("PAPI_remove_event_L1_DCM_1");
			exit(-1);
	  }

		if((retval = PAPI_remove_event(EventSet, PAPI_L2_DCM)) != PAPI_OK ){
			PAPI_perror("PAPI_remove_event_L2_DCM_1");
			exit(-1);
	  }

		if((retval = PAPI_remove_event(EventSet, PAPI_TOT_INS)) != PAPI_OK ){
			PAPI_perror("PAPI_remove_event_TOT_INS_1");
			exit(-1);
	  }

		if((retval = PAPI_remove_event(EventSet, PAPI_TOT_CYC)) != PAPI_OK ){
			PAPI_perror("PAPI_remove_event_TOT_CYC_1");
			exit(-1);
	  }

		if((retval = PAPI_destroy_eventset(&EventSet)) != PAPI_OK ){
			PAPI_perror("PAPI_destroy_eventset_1");
			exit(-1);
	  }

		/* clean up */
		PAPI_shutdown();

	}
	else if(choice <= 0 || choice >= 7)
		cout << "Por favor escolha uma opcao correta" << endl ;

	if(choice == 2 || choice == 3 || choice == 5 || choice == 6){

		if((retval = PAPI_library_init(PAPI_VER_CURRENT)) != PAPI_VER_CURRENT){
			PAPI_perror("PAPI_library_init_2");
			exit(-1);
		}

		if((retval = PAPI_create_eventset(&EventSet)) != PAPI_OK){
			PAPI_perror("PAPI_create_eventset_2");
			exit(-1);
	  }

		if((retval = PAPI_add_event(EventSet, PAPI_L1_DCM)) != PAPI_OK){
			PAPI_perror("PAPI_add_event_L1_DCM_2");
			exit(-1);
		}

		if((retval = PAPI_add_event(EventSet, PAPI_L2_DCM)) != PAPI_OK){
			PAPI_perror("PAPI_add_event_L2_DCM_2");
			exit(-1);
		}

		if((retval = PAPI_add_event(EventSet, PAPI_TOT_INS)) != PAPI_OK){
			PAPI_perror("PAPI_add_event_TOT_INS_2");
			exit(-1);
		}

		if((retval = PAPI_add_event(EventSet, PAPI_TOT_CYC)) != PAPI_OK){
			PAPI_perror("PAPI_add_event_TOT_CYC_2");
			exit(-1);
		}

		if((retval = PAPI_start(EventSet)) != PAPI_OK ){
			PAPI_perror("PAPI_start_2");
			exit(-1);
		}

		cout << "Calculando..." << endl;

		if(choice == 2 || choice == 3){
			clock_time = (float)clock();

			//Multiplication of Matrix a b, in c - Line with Column
			MulEleCol(n, a, b, c);

			clock_time = (float)((clock() - clock_time)/CLOCKS_PER_SEC);
		} else {
			clock_time = (float)omp_get_wtime();

			//Multiplication of Matrix a b, in c - Line with Column
			MulEleCol_omp(n, a, b, c, n_threads);

			clock_time = (float)((omp_get_wtime() - clock_time));
		}
		if((retval = PAPI_stop(EventSet, values)) != PAPI_OK ){
			PAPI_perror("PAPI_stop_2");
			exit(-1);
	  }

		flop_s = ((2*(n^3))/clock_time);
		//cml1flops = values[0]/(2*(n^3));
		//cml2flops = values[1]/(2*(n^3));
		instPc = (float)values[2]/(float)values[3];

		printf("Medidas do algoritmo 2: \n");
		printf("Tempo: %f(s) MFlops: %d \nInstrucoes: %lld Ciclos: %lld Instr/Ciclos: %f \nL1_DCM: %lld  L2_DCM: %lld \n", clock_time, flop_s, values[2], values[3], instPc, values[0], values[1]);
		printf("============================ \n\n");

		outputFile << "Medidas do algoritmo 2 - Tamanho Matriz: " << n << endl;
		outputFile << "Tempo: " << clock_time << "(s) MFlops: " << flop_s << " Instrucoes: " << values[2] << " Ciclos: " << values[3] << " Instr/Ciclos: " << instPc << endl;
		outputFile << "L1_DCM: " <<  values[0] << " L2_DCM: " << values[1] << endl;

		if((retval = PAPI_reset(EventSet)) != PAPI_OK ){
			PAPI_perror("PAPI_reset_1");
			exit(-1);
	  }

		if((retval = PAPI_remove_event(EventSet, PAPI_L1_DCM)) != PAPI_OK ){
			PAPI_perror("PAPI_remove_event_L1_DCM_1");
			exit(-1);
	  }

		if((retval = PAPI_remove_event(EventSet, PAPI_L2_DCM)) != PAPI_OK ){
			PAPI_perror("PAPI_remove_event_L2_DCM_1");
			exit(-1);
	  }

		if((retval = PAPI_remove_event(EventSet, PAPI_TOT_INS)) != PAPI_OK ){
			PAPI_perror("PAPI_remove_event_TOT_INS_1");
			exit(-1);
	  }

		if((retval = PAPI_remove_event(EventSet, PAPI_TOT_CYC)) != PAPI_OK ){
			PAPI_perror("PAPI_remove_event_TOT_CYC_1");
			exit(-1);
	  }

		if((retval = PAPI_destroy_eventset(&EventSet)) != PAPI_OK ){
			PAPI_perror("PAPI_destroy_eventset_1");
			exit(-1);
	  }

		/* clean up */
		PAPI_shutdown();

	}
	outputFile.close();
	return 0;
}
