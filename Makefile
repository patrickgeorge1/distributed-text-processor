mpi = mpic++
c++ = g++
utils =  main.cpp utils/ParagraphPiece/ParagraphPiece.cpp  utils/TextProcessor/TextProcessor.cpp utils/ParagraphTools/ParagraphTool.cpp utils/ConcurrentMemory/ConcurrentMemory.cpp utils/InputParser/InputParser.cpp

all: main

build: $(utils)
	$(c++) $(utils) -pthread -o main -g

test:
	./main

main:
	$(mpi) $(utils) -o $@

run: main
	mpirun -oversubscribe -np 5 ./main tests/in/input1.txt 7

.PHONY: clean
clean:
	rm -rf main