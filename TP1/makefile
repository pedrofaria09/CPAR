GPLUS = g++
PAPIFLAG = -w -I /opt/papi/include /opt/papi/lib/libpapi.a
JC = javac
all:
	$(GPLUS) -O3 mul.cpp $(PAPIFLAG) -o mul -fopenmp
	$(JC) -g mul_j.java

run:
	./mul

run-java:
	java mul_j

run_test_1:
	./mul 500 1 1 test_1.txt
	./mul 1000 1 1 test_1.txt
	./mul 1500 1 1 test_1.txt
	./mul 2000 1 1 test_1.txt
	./mul 2500 1 1 test_1.txt
	./mul 3000 1 1 test_1.txt

run_test_2:
	./mul 500 2 1 test_2.txt
	./mul 1000 2 1 test_2.txt
	./mul 1500 2 1 test_2.txt
	./mul 2000 2 1 test_2.txt
	./mul 2500 2 1 test_2.txt
	./mul 3000 2 1 test_2.txt
	./mul 5000 2 1 test_2.txt
	./mul 6000 2 1 test_2.txt
	./mul 7000 2 1 test_2.txt
	./mul 8000 2 1 test_2.txt
	./mul 9000 2 1 test_2.txt
	./mul 10000 2 1 test_2.txt

run_test_3:
	./mul 500 4 1 test_3_opt1_th1.txt
	./mul 1000 4 1 test_3_opt1_th1.txt
	./mul 1500 4 1 test_3_opt1_th1.txt
	./mul 2000 4 1 test_3_opt1_th1.txt
	./mul 2500 4 1 test_3_opt1_th1.txt
	./mul 3000 4 1 test_3_opt1_th1.txt
	./mul 500 4 2 test_3_opt1_th2.txt
	./mul 1000 4 2 test_3_opt1_th2.txt
	./mul 1500 4 2 test_3_opt1_th2.txt
	./mul 2000 4 2 test_3_opt1_th2.txt
	./mul 2500 4 2 test_3_opt1_th2.txt
	./mul 3000 4 2 test_3_opt1_th2.txt
	./mul 500 4 3 test_3_opt1_th3.txt
	./mul 1000 4 3 test_3_opt1_th3.txt
	./mul 1500 4 3 test_3_opt1_th3.txt
	./mul 2000 4 3 test_3_opt1_th3.txt
	./mul 2500 4 3 test_3_opt1_th3.txt
	./mul 3000 4 3 test_3_opt1_th3.txt
	./mul 500 4 4 test_3_opt1_th4.txt
	./mul 1000 4 4 test_3_opt1_th4.txt
	./mul 1500 4 4 test_3_opt1_th4.txt
	./mul 2000 4 4 test_3_opt1_th4.txt
	./mul 2500 4 4 test_3_opt1_th4.txt
	./mul 3000 4 4 test_3_opt1_th4.txt
	./mul 500 4 5 test_3_opt1_th5.txt
	./mul 1000 4 5 test_3_opt1_th5.txt
	./mul 1500 4 5 test_3_opt1_th5.txt
	./mul 2000 4 5 test_3_opt1_th5.txt
	./mul 2500 4 5 test_3_opt1_th5.txt
	./mul 3000 4 5 test_3_opt1_th5.txt
	./mul 500 4 6 test_3_opt1_th6.txt
	./mul 1000 4 6 test_3_opt1_th6.txt
	./mul 1500 4 6 test_3_opt1_th6.txt
	./mul 2000 4 6 test_3_opt1_th6.txt
	./mul 2500 4 6 test_3_opt1_th6.txt
	./mul 3000 4 6 test_3_opt1_th6.txt
	./mul 500 4 7 test_3_opt1_th7.txt
	./mul 1000 4 7 test_3_opt1_th7.txt
	./mul 1500 4 7 test_3_opt1_th7.txt
	./mul 2000 4 7 test_3_opt1_th7.txt
	./mul 2500 4 7 test_3_opt1_th7.txt
	./mul 3000 4 7 test_3_opt1_th7.txt
	./mul 500 4 8 test_3_opt1_th8.txt
	./mul 1000 4 8 test_3_opt1_th8.txt
	./mul 1500 4 8 test_3_opt1_th8.txt
	./mul 2000 4 8 test_3_opt1_th8.txt
	./mul 2500 4 8 test_3_opt1_th8.txt
	./mul 3000 4 8 test_3_opt1_th8.txt
	./mul 500 5 1 test_3_opt2_th1.txt
	./mul 1000 5 1 test_3_opt2_th1.txt
	./mul 1500 5 1 test_3_opt2_th1.txt
	./mul 2000 5 1 test_3_opt2_th1.txt
	./mul 2500 5 1 test_3_opt2_th1.txt
	./mul 3000 5 1 test_3_opt2_th1.txt
	./mul 500 5 2 test_3_opt2_th2.txt
	./mul 1000 5 2 test_3_opt2_th2.txt
	./mul 1500 5 2 test_3_opt2_th2.txt
	./mul 2000 5 2 test_3_opt2_th2.txt
	./mul 2500 5 2 test_3_opt2_th2.txt
	./mul 3000 5 2 test_3_opt2_th2.txt
	./mul 500 5 3 test_3_opt2_th3.txt
	./mul 1000 5 3 test_3_opt2_th3.txt
	./mul 1500 5 3 test_3_opt2_th3.txt
	./mul 2000 5 3 test_3_opt2_th3.txt
	./mul 2500 5 3 test_3_opt2_th3.txt
	./mul 3000 5 3 test_3_opt2_th3.txt
	./mul 500 5 4 test_3_opt2_th4.txt
	./mul 1000 5 4 test_3_opt2_th4.txt
	./mul 1500 5 4 test_3_opt2_th4.txt
	./mul 2000 5 4 test_3_opt2_th4.txt
	./mul 2500 5 4 test_3_opt2_th4.txt
	./mul 3000 5 4 test_3_opt2_th4.txt
	./mul 500 5 5 test_3_opt2_th5.txt
	./mul 1000 5 5 test_3_opt2_th5.txt
	./mul 1500 5 5 test_3_opt2_th5.txt
	./mul 2000 5 5 test_3_opt2_th5.txt
	./mul 2500 5 5 test_3_opt2_th5.txt
	./mul 3000 5 5 test_3_opt2_th5.txt
	./mul 500 5 6 test_3_opt2_th6.txt
	./mul 1000 5 6 test_3_opt2_th6.txt
	./mul 1500 5 6 test_3_opt2_th6.txt
	./mul 2000 5 6 test_3_opt2_th6.txt
	./mul 2500 5 6 test_3_opt2_th6.txt
	./mul 3000 5 6 test_3_opt2_th6.txt
	./mul 500 5 7 test_3_opt2_th7.txt
	./mul 1000 5 7 test_3_opt2_th7.txt
	./mul 1500 5 7 test_3_opt2_th7.txt
	./mul 2000 5 7 test_3_opt2_th7.txt
	./mul 2500 5 7 test_3_opt2_th7.txt
	./mul 3000 5 7 test_3_opt2_th7.txt
	./mul 500 5 8 test_3_opt2_th8.txt
	./mul 1000 5 8 test_3_opt2_th8.txt
	./mul 1500 5 8 test_3_opt2_th8.txt
	./mul 2000 5 8 test_3_opt2_th8.txt
	./mul 2500 5 8 test_3_opt2_th8.txt
	./mul 3000 5 8 test_3_opt2_th8.txt

clean:
	-rm mul test_*.txt mul_j.class
