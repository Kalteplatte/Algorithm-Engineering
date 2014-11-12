CXX= cl/EHsc
CXXFLAGS=


.PHONY all:
all: clean build test

.PHONY build:
build: Fibonacci.cpp
	$(CXX) $(CXXFLAGS) Fibonacci.cpp
 
.PHONY test:
test: testclean testbuild #tests


.PHONY testbuild:
testbuild: test.cpp
	$(CXX) $(CXXFLAGS) test.cpp


#.PHONY tests: test.cpp
#	./test.cpp

.PHONY: testclean
testclean:
	 -del test.obj test.exe


.PHONY clean:
clean:
	-del Fibonacci.obj Fibonacci.exe


