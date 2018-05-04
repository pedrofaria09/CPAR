GPLUS = g++
GMPI = mpiCC

all:
	$(GPLUS) -O3 seq_normal.cpp -o seq_normal
	$(GPLUS) -O3 seq_openmp.cpp -o seq_openmp -fopenmp
	$(GMPI) -O3 seq_mpi.cpp -o seq_mpi

run:
	./seq_normal 100000000 primes_normal.csv test_normal.txt
	./seq_openmp 100000000 2 primes_openmp_2.csv test_openmp_2.txt
	mpirun -np 2 seq_mpi 100000000 primes_mpi.csv test_mpi.txt

run_normal:
	./seq_normal 100000000 primes_normal_1.csv test_normal.txt
	./seq_normal 200000000 primes_normal_2.csv test_normal.txt
	./seq_normal 300000000 primes_normal_3.csv test_normal.txt
	./seq_normal 400000000 primes_normal_4.csv test_normal.txt
	./seq_normal 500000000 primes_normal_5.csv test_normal.txt
	./seq_normal 600000000 primes_normal_6.csv test_normal.txt

run_openmp:
	./seq_openmp 100000000 1 primes_openmp_1_1.csv test_openmp_1.txt
	./seq_openmp 200000000 1 primes_openmp_1_2.csv test_openmp_1.txt
	./seq_openmp 300000000 1 primes_openmp_1_3.csv test_openmp_1.txt
	./seq_openmp 400000000 1 primes_openmp_1_4.csv test_openmp_1.txt
	./seq_openmp 500000000 1 primes_openmp_1_5.csv test_openmp_1.txt
	./seq_openmp 600000000 1 primes_openmp_1_6.csv test_openmp_1.txt
	./seq_openmp 100000000 2 primes_openmp_2_1.csv test_openmp_2.txt
	./seq_openmp 200000000 2 primes_openmp_2_2.csv test_openmp_2.txt
	./seq_openmp 300000000 2 primes_openmp_2_3.csv test_openmp_2.txt
	./seq_openmp 400000000 2 primes_openmp_2_4.csv test_openmp_2.txt
	./seq_openmp 500000000 2 primes_openmp_2_5.csv test_openmp_2.txt
	./seq_openmp 600000000 2 primes_openmp_2_6.csv test_openmp_2.txt
	./seq_openmp 100000000 3 primes_openmp_3_1.csv test_openmp_3.txt
	./seq_openmp 200000000 3 primes_openmp_3_2.csv test_openmp_3.txt
	./seq_openmp 300000000 3 primes_openmp_3_3.csv test_openmp_3.txt
	./seq_openmp 400000000 3 primes_openmp_3_4.csv test_openmp_3.txt
	./seq_openmp 500000000 3 primes_openmp_3_5.csv test_openmp_3.txt
	./seq_openmp 600000000 3 primes_openmp_3_6.csv test_openmp_3.txt
	./seq_openmp 100000000 4 primes_openmp_4_1.csv test_openmp_4.txt
	./seq_openmp 200000000 4 primes_openmp_4_2.csv test_openmp_4.txt
	./seq_openmp 300000000 4 primes_openmp_4_3.csv test_openmp_4.txt
	./seq_openmp 400000000 4 primes_openmp_4_4.csv test_openmp_4.txt
	./seq_openmp 500000000 4 primes_openmp_4_5.csv test_openmp_4.txt
	./seq_openmp 600000000 4 primes_openmp_4_6.csv test_openmp_4.txt

run_mpi:
	mpirun -np 1 seq_mpi 100000000 primes_mpi_1_1.csv test_mpi_1.txt
	mpirun -np 1 seq_mpi 200000000 primes_mpi_1_2.csv test_mpi_1.txt
	mpirun -np 1 seq_mpi 300000000 primes_mpi_1_3.csv test_mpi_1.txt
	mpirun -np 1 seq_mpi 400000000 primes_mpi_1_4.csv test_mpi_1.txt
	mpirun -np 1 seq_mpi 500000000 primes_mpi_1_5.csv test_mpi_1.txt
	mpirun -np 1 seq_mpi 600000000 primes_mpi_1_6.csv test_mpi_1.txt
	mpirun -np 2 seq_mpi 100000000 primes_mpi_2_1.csv test_mpi_2.txt
	mpirun -np 2 seq_mpi 200000000 primes_mpi_2_2.csv test_mpi_2.txt
	mpirun -np 2 seq_mpi 300000000 primes_mpi_2_3.csv test_mpi_2.txt
	mpirun -np 2 seq_mpi 400000000 primes_mpi_2_4.csv test_mpi_2.txt
	mpirun -np 2 seq_mpi 500000000 primes_mpi_2_5.csv test_mpi_2.txt
	mpirun -np 2 seq_mpi 600000000 primes_mpi_2_6.csv test_mpi_2.txt
	mpirun -np 3 seq_mpi 100000000 primes_mpi_3_1.csv test_mpi_3.txt
	mpirun -np 3 seq_mpi 200000000 primes_mpi_3_2.csv test_mpi_3.txt
	mpirun -np 3 seq_mpi 300000000 primes_mpi_3_3.csv test_mpi_3.txt
	mpirun -np 3 seq_mpi 400000000 primes_mpi_3_4.csv test_mpi_3.txt
	mpirun -np 3 seq_mpi 500000000 primes_mpi_3_5.csv test_mpi_3.txt
	mpirun -np 3 seq_mpi 600000000 primes_mpi_3_6.csv test_mpi_3.txt
	mpirun -np 4 seq_mpi 100000000 primes_mpi_4_1.csv test_mpi_4.txt
	mpirun -np 4 seq_mpi 200000000 primes_mpi_4_2.csv test_mpi_4.txt
	mpirun -np 4 seq_mpi 300000000 primes_mpi_4_3.csv test_mpi_4.txt
	mpirun -np 4 seq_mpi 400000000 primes_mpi_4_4.csv test_mpi_4.txt
	mpirun -np 4 seq_mpi 500000000 primes_mpi_4_5.csv test_mpi_4.txt
	mpirun -np 4 seq_mpi 600000000 primes_mpi_4_6.csv test_mpi_4.txt


clean:
	-rm seq_normal seq_openmp seq_mpi *.csv *.txt