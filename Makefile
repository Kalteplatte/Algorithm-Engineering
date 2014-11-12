#CC:=vcexpress -g 


#.PHONY: all:
#	all: build
 
#.PHONY: build: 
#	build:

#.PHONY tests:
#	tests: testfile

#.PHONY clean:
#	rm Fibonacci Fibonacci.o

Fibonacci.exe :Fibonacci/Fibonacci.cpp
	Fibonacci/Fibonacci.cpp -c 


Fibonacci: Fibonacci.o
	Fibonacci.o -o Fibonacci



clean:
	rm Fibonacci.o Fibonacci



run: Fibonacci
	./Fibonacci

