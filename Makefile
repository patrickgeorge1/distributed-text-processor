mpi = mpic++

all: main

main: main.cpp
	$(mpi) $< -o $@

run: main
	mpirun -oversubscribe -np 5 ./$@ ./tests/in/input1.txt

.PHONY: clean
clean:
	rm -rf main