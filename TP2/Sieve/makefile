GPLUS = g++
GMPI = mpiCC

all:
	$(GPLUS) -O3 seq_normal.cpp -o seq_normal
	$(GPLUS) -O3 seq_openmp.cpp -o seq_openmp -fopenmp
	$(GMPI) -O3 seq_mpi.cpp -o seq_mpi

run:
	#./seq_normal 300000000
	#./seq_openmp 300000000 1
	./seq_openmp 300000000 2
	#./seq_openmp 300000000 3
	#./seq_openmp 300000000 4
	#./seq_openmp 300000000 5
	mpirun -np 2 seq_mpi

clean:
	-rm seq_normal seq_openmp seq_mpi