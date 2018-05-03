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

clean:
	-rm seq_normal seq_openmp seq_mpi *.csv *.txt