CXX= cl/EHsc
CXXFLAGS=
SOURCE= src/Fibonacci.cpp
EXECUTABLE= Fibonacci.exe
EXE_TEST= src/test.cpp
DELETE= -del
OBJECT= Fibonacci.obj
RUNORDER=

.PHONY all:
all: build run

.PHONY build:
build: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(SOURCE)
 
#.PHONY test:
#test: testclean testbuild #tests

.PHONY run:
run: 
	$(RUNORDER) $(EXECUTABLE) 

#.PHONY testbuild:
#testbuild: 
#	$(CXX) $(CXXFLAGS) $(EXE_TEST)


#.PHONY test: test.cpp
#	./test.cpp

#.PHONY: testclean
#testclean: 
#	$(DELETE) test.obj test.exe


.PHONY clean:
clean: 
	$(DELETE) $(OBJECT) $(EXECUTABLE)


