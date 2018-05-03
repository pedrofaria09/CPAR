GPLUS = g++
GMPI = mpiCC

all:
	$(GPLUS) -O3 lu_normal.cpp -o lu_normal
	$(GPLUS) -O3 lu_openmp.cpp -o lu_openmp -fopenmp
	$(GMPI) -O3 lu_mpi.cpp -o lu_mpi

run:
	./lu_normal a1.csv l_normal.csv u_normal.csv test_normal.txt
	./lu_openmp 2 a1.csv l_openmp.csv u_openmp.csv test_openmp.txt
	mpirun -np 2 lu_mpi a1.csv l_mpi.csv u_mpi.csv test_mpi.txt

clean:
	-rm lu_normal lu_openmp lu_mpi test_*.txt *normal.csv *openmp.csv *mpi.csv