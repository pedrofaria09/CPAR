GPLUS = g++
GMPI = mpiCC

all:
	$(GPLUS) -O3 lu_normal.cpp -o lu_normal
	$(GPLUS) -O3 lu_openmp.cpp -o lu_openmp -fopenmp
	$(GMPI) -O3 lu_mpi.cpp -o lu_mpi

run:
	./lu_normal aa.csv l_aa_normal.csv u_aa_normal.csv test_normal.txt
	mpirun -np 1 lu_mpi aa.csv l_aa_mpi.csv u_aa_mpi.csv test_mpi_1.txt

run_normal:
	./lu_normal LU_inputs_all/A_1000x1000.csv l_1000_normal.csv u_1000_normal.csv test_normal.txt
	./lu_normal LU_inputs_all/A_2000x2000.csv l_2000_normal.csv u_2000_normal.csv test_normal.txt
	./lu_normal LU_inputs_all/A_3000x3000.csv l_3000_normal.csv u_3000_normal.csv test_normal.txt
	./lu_normal LU_inputs_all/A_4000x4000.csv l_4000_normal.csv u_4000_normal.csv test_normal.txt
	./lu_normal LU_inputs_all/A_5000x5000.csv l_5000_normal.csv u_5000_normal.csv test_normal.txt
	./lu_normal LU_inputs_all/A_6000x6000.csv l_6000_normal.csv u_6000_normal.csv test_normal.txt

run_openmp:
	./lu_openmp 1 LU_inputs_all/A_1000x1000.csv l_1000_1_openmp.csv u_1000_1_openmp.csv test_openmp_1.txt
	./lu_openmp 1 LU_inputs_all/A_2000x2000.csv l_2000_1_openmp.csv u_2000_1_openmp.csv test_openmp_1.txt
	./lu_openmp 1 LU_inputs_all/A_3000x3000.csv l_3000_1_openmp.csv u_3000_1_openmp.csv test_openmp_1.txt
	./lu_openmp 1 LU_inputs_all/A_4000x4000.csv l_4000_1_openmp.csv u_4000_1_openmp.csv test_openmp_1.txt
	./lu_openmp 1 LU_inputs_all/A_5000x5000.csv l_5000_1_openmp.csv u_5000_1_openmp.csv test_openmp_1.txt
	./lu_openmp 1 LU_inputs_all/A_6000x6000.csv l_6000_1_openmp.csv u_6000_1_openmp.csv test_openmp_1.txt
	./lu_openmp 2 LU_inputs_all/A_1000x1000.csv l_1000_2_openmp.csv u_1000_2_openmp.csv test_openmp_2.txt
	./lu_openmp 2 LU_inputs_all/A_2000x2000.csv l_2000_2_openmp.csv u_2000_2_openmp.csv test_openmp_2.txt
	./lu_openmp 2 LU_inputs_all/A_3000x3000.csv l_3000_2_openmp.csv u_3000_2_openmp.csv test_openmp_2.txt
	./lu_openmp 2 LU_inputs_all/A_4000x4000.csv l_4000_2_openmp.csv u_4000_2_openmp.csv test_openmp_2.txt
	./lu_openmp 2 LU_inputs_all/A_5000x5000.csv l_5000_2_openmp.csv u_5000_2_openmp.csv test_openmp_2.txt
	./lu_openmp 2 LU_inputs_all/A_6000x6000.csv l_6000_2_openmp.csv u_6000_2_openmp.csv test_openmp_2.txt
	./lu_openmp 3 LU_inputs_all/A_1000x1000.csv l_1000_3_openmp.csv u_1000_3_openmp.csv test_openmp_3.txt
	./lu_openmp 3 LU_inputs_all/A_2000x2000.csv l_2000_3_openmp.csv u_2000_3_openmp.csv test_openmp_3.txt
	./lu_openmp 3 LU_inputs_all/A_3000x3000.csv l_3000_3_openmp.csv u_3000_3_openmp.csv test_openmp_3.txt
	./lu_openmp 3 LU_inputs_all/A_4000x4000.csv l_4000_3_openmp.csv u_4000_3_openmp.csv test_openmp_3.txt
	./lu_openmp 3 LU_inputs_all/A_5000x5000.csv l_5000_3_openmp.csv u_5000_3_openmp.csv test_openmp_3.txt
	./lu_openmp 3 LU_inputs_all/A_6000x6000.csv l_6000_3_openmp.csv u_6000_3_openmp.csv test_openmp_3.txt
	./lu_openmp 4 LU_inputs_all/A_1000x1000.csv l_1000_4_openmp.csv u_1000_4_openmp.csv test_openmp_4.txt
	./lu_openmp 4 LU_inputs_all/A_2000x2000.csv l_2000_4_openmp.csv u_2000_4_openmp.csv test_openmp_4.txt
	./lu_openmp 4 LU_inputs_all/A_3000x3000.csv l_3000_4_openmp.csv u_3000_4_openmp.csv test_openmp_4.txt
	./lu_openmp 4 LU_inputs_all/A_4000x4000.csv l_4000_4_openmp.csv u_4000_4_openmp.csv test_openmp_4.txt
	./lu_openmp 4 LU_inputs_all/A_5000x5000.csv l_5000_4_openmp.csv u_5000_4_openmp.csv test_openmp_4.txt
	./lu_openmp 4 LU_inputs_all/A_6000x6000.csv l_6000_4_openmp.csv u_6000_4_openmp.csv test_openmp_4.txt

run_mpi:
	mpirun -np 1 lu_mpi LU_inputs_all/A_1000x1000.csv l_1000_1_openmp.csv u_1000_1_openmp.csv test_mpi_1.txt
	mpirun -np 1 lu_mpi LU_inputs_all/A_2000x2000.csv l_2000_1_openmp.csv u_2000_1_openmp.csv test_mpi_1.txt
	mpirun -np 1 lu_mpi LU_inputs_all/A_3000x3000.csv l_3000_1_openmp.csv u_3000_1_openmp.csv test_mpi_1.txt
	mpirun -np 1 lu_mpi LU_inputs_all/A_4000x4000.csv l_4000_1_openmp.csv u_4000_1_openmp.csv test_mpi_1.txt
	mpirun -np 1 lu_mpi LU_inputs_all/A_5000x5000.csv l_5000_1_openmp.csv u_5000_1_openmp.csv test_mpi_1.txt
	mpirun -np 1 lu_mpi LU_inputs_all/A_6000x6000.csv l_6000_1_openmp.csv u_6000_1_openmp.csv test_mpi_1.txt
	mpirun -np 2 lu_mpi LU_inputs_all/A_1000x1000.csv l_1000_2_openmp.csv u_1000_2_openmp.csv test_mpi_2.txt
	mpirun -np 2 lu_mpi LU_inputs_all/A_2000x2000.csv l_2000_2_openmp.csv u_2000_2_openmp.csv test_mpi_2.txt
	mpirun -np 2 lu_mpi LU_inputs_all/A_3000x3000.csv l_3000_2_openmp.csv u_3000_2_openmp.csv test_mpi_2.txt
	mpirun -np 2 lu_mpi LU_inputs_all/A_4000x4000.csv l_4000_2_openmp.csv u_4000_2_openmp.csv test_mpi_2.txt
	mpirun -np 2 lu_mpi LU_inputs_all/A_5000x5000.csv l_5000_2_openmp.csv u_5000_2_openmp.csv test_mpi_2.txt
	mpirun -np 2 lu_mpi LU_inputs_all/A_6000x6000.csv l_6000_2_openmp.csv u_6000_2_openmp.csv test_mpi_2.txt
	mpirun -np 3 lu_mpi LU_inputs_all/A_1000x1000.csv l_1000_3_openmp.csv u_1000_3_openmp.csv test_mpi_3.txt
	mpirun -np 3 lu_mpi LU_inputs_all/A_2000x2000.csv l_2000_3_openmp.csv u_2000_3_openmp.csv test_mpi_3.txt
	mpirun -np 3 lu_mpi LU_inputs_all/A_3000x3000.csv l_3000_3_openmp.csv u_3000_3_openmp.csv test_mpi_3.txt
	mpirun -np 3 lu_mpi LU_inputs_all/A_4000x4000.csv l_4000_3_openmp.csv u_4000_3_openmp.csv test_mpi_3.txt
	mpirun -np 3 lu_mpi LU_inputs_all/A_5000x5000.csv l_5000_3_openmp.csv u_5000_3_openmp.csv test_mpi_3.txt
	mpirun -np 3 lu_mpi LU_inputs_all/A_6000x6000.csv l_6000_3_openmp.csv u_6000_3_openmp.csv test_mpi_3.txt
	mpirun -np 4 lu_mpi LU_inputs_all/A_1000x1000.csv l_1000_4_openmp.csv u_1000_4_openmp.csv test_mpi_4.txt
	mpirun -np 4 lu_mpi LU_inputs_all/A_2000x2000.csv l_2000_4_openmp.csv u_2000_4_openmp.csv test_mpi_4.txt
	mpirun -np 4 lu_mpi LU_inputs_all/A_3000x3000.csv l_3000_4_openmp.csv u_3000_4_openmp.csv test_mpi_4.txt
	mpirun -np 4 lu_mpi LU_inputs_all/A_4000x4000.csv l_4000_4_openmp.csv u_4000_4_openmp.csv test_mpi_4.txt
	mpirun -np 4 lu_mpi LU_inputs_all/A_5000x5000.csv l_5000_4_openmp.csv u_5000_4_openmp.csv test_mpi_4.txt
	mpirun -np 4 lu_mpi LU_inputs_all/A_6000x6000.csv l_6000_4_openmp.csv u_6000_4_openmp.csv test_mpi_4.txt

clean:
	-rm lu_normal lu_openmp lu_mpi test_*.txt *normal.csv *openmp.csv *mpi.csv