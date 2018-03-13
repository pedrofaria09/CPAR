GPLUS = g++
PAPIOMPFLAG = -lgomp -I /opt/papi/include /opt/papi/lib/libpapi.a
JC = javac
all: 
	$(GPLUS) mul.cpp $(PAPIOMPFLAG) -o multiplication
	$(GPLUS) -O3 mul.cpp $(PAPIOMPFLAG) -o multiplication_optimized
	$(JC) -g mul_j.java 

run_normal:
	./multiplication

run_optimized:
	./multiplication_optimized

run_normal_j:
	java mul_j

tests:
	./multiplication_optimized 500 3 1
	./multiplication_optimized 1000 3 1
	./multiplication_optimized 1500 3 1
	./multiplication_optimized 2000 3 1
	./multiplication_optimized 2500 3 1
	./multiplication_optimized 3000 3 1

tests_2:
	./multiplication_optimized 5000 2 1
	./multiplication_optimized 6000 2 1
	./multiplication_optimized 7000 2 1
	./multiplication_optimized 8000 2 1
	./multiplication_optimized 9000 2 1
	./multiplication_optimized 10000 2 1

tests_par:
	./multiplication_optimized 500 6 1
	./multiplication_optimized 1000 6 1
	./multiplication_optimized 1500 6 1
	./multiplication_optimized 2000 6 1
	./multiplication_optimized 2500 6 1
	./multiplication_optimized 3000 6 1
	./multiplication_optimized 500 6 2
	./multiplication_optimized 1000 6 2
	./multiplication_optimized 1500 6 2
	./multiplication_optimized 2000 6 2
	./multiplication_optimized 2500 6 2
	./multiplication_optimized 3000 6 2
	./multiplication_optimized 500 6 3
	./multiplication_optimized 1000 6 3
	./multiplication_optimized 1500 6 3
	./multiplication_optimized 2000 6 3
	./multiplication_optimized 2500 6 3
	./multiplication_optimized 3000 6 3
	./multiplication_optimized 500 6 4
	./multiplication_optimized 1000 6 4
	./multiplication_optimized 1500 6 4
	./multiplication_optimized 2000 6 4
	./multiplication_optimized 2500 6 4
	./multiplication_optimized 3000 6 4
	./multiplication_optimized 500 6 5
	./multiplication_optimized 1000 6 5
	./multiplication_optimized 1500 6 5
	./multiplication_optimized 2000 6 5
	./multiplication_optimized 2500 6 5
	./multiplication_optimized 3000 6 5
	./multiplication_optimized 500 6 6
	./multiplication_optimized 1000 6 6
	./multiplication_optimized 1500 6 6
	./multiplication_optimized 2000 6 6
	./multiplication_optimized 2500 6 6
	./multiplication_optimized 3000 6 6
	./multiplication_optimized 500 6 7
	./multiplication_optimized 1000 6 7
	./multiplication_optimized 1500 6 7
	./multiplication_optimized 2000 6 7
	./multiplication_optimized 2500 6 7
	./multiplication_optimized 3000 6 7
	./multiplication_optimized 500 6 8
	./multiplication_optimized 1000 6 8
	./multiplication_optimized 1500 6 8
	./multiplication_optimized 2000 6 8
	./multiplication_optimized 2500 6 8
	./multiplication_optimized 3000 6 8

tests_java:
	java mul_j 500 1
	java mul_j 1000 1
	java mul_j 1500 1
	java mul_j 2000 1
	java mul_j 2500 1
	java mul_j 3000 1

clean:
	-rm multiplication multiplication_optimized test_c.txt mul_j.class
