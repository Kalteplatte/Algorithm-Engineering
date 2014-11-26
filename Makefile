CXX= cl/EHsc
CXXFLAGS=
DELETE= -del

SOURCE= src/fibonacci.cpp
EXECUTABLE= fibonacci.exe
OBJS= fibonacci.obj

#SOURCE= src/sort.cpp
#EXECUTABLE= sort.exe
#OBJS= sort.obj


TEST= src/test.cpp
TEST_EXE= test.exe
TEST_OBJ= test.obj

RUNORDER=

.PHONY all:
all: build

.PHONY build:
build: 
	$(CXX) $(CXXFLAGS) $(SOURCE)
 
.PHONY run:
run: 
	$(RUNORDER) $(EXECUTABLE) 

.PHONY test:
test: testobj testbuild testrun

.PHONY testobj:
testobj:  
	$(CXX) $(CFLAGS) -c $(TEST_OBJ) $(TEST)

.PHONY testbuild:
testbuild: 
	link test.obj fibonacci.obj -OUT:test.exe


.PHONY testrun:
testrun: 
	$(RUNORDER) $(TEST_EXE)



.PHONY clean:
clean: 
	$(DELETE) $(OBJS) $(EXECUTABLE) $(TEST_EXE) $(TEST_OBJ)

# Google Test:
GTEST_DIR = /gtest
GTEST_INCLUDE_DIR = /gtest/include/gtest
GTEST_HEADERS = /gtest/include/gtest/*.h \
                /gtest/include/gtest/internal/*.h

