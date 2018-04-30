GPLUS = g++
GMPI = mpiCC

all:
	$(GPLUS) -O3 seq_normal.cpp -o seq_normal
	$(GPLUS) -O3 seq_openmp.cpp -o seq_openmp -fopenmp
	$(GMPI) -O3 seq_mpi.cpp -o seq_mpi

run:
	./seq_normal primes_normal.csv 20
	./seq_openmp primes_openmp_1.csv 20 1
	./seq_openmp primes_openmp_2.csv 20 2
	./seq_openmp primes_openmp_3.csv 20 3
	./seq_openmp primes_openmp_4.csv 20 4
	mpirun -np 2 seq_mpi primes_mpi.csv 20

clean:
	-rm seq_normal seq_openmp seq_mpi *.csv