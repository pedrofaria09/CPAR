GPLUS = g++
all:
	$(GPLUS) -O3 lu_normal.cpp -o lu_normal
	$(GPLUS) -O3 lu_openmp.cpp -o lu_openmp -fopenmp
run:
	./lu_normal a.csv
	./lu_openmp a.csv 2

clean:
	-rm lu_normal lu_openmp
