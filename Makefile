mpi = mpic++
c++ = g++
utils =  main.cpp utils/ParagraphPiece/ParagraphPiece.cpp  utils/TextProcessor/TextProcessor.cpp utils/ParagraphTools/ParagraphTool.cpp utils/ConcurrentMemory/ConcurrentMemory.cpp

all: main

build: $(utils)
	$(c++) $(utils) -o main 

test:
	./main

main: main.cpp
	$(mpi) $< -o $@

run: main
	mpirun -oversubscribe -np 5 ./$@ ./tests/in/input1.txt

.PHONY: clean
clean:
	rm -rf main