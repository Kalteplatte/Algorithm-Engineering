CXX= cl/EHsc
CXXFLAGS=
DELETE= -del
LINKORDER=link
RUNORDER=


SOURCE= src/fibonacci.cpp
EXECUTABLE= fibonacci.exe
OBJS= fibonacci.obj

SOURCE2= src/sort.cpp
EXECUTABLE2= sort.exe
OBJS2= sort.obj


TEST= src/test.cpp
TEST_EXE= test.exe
TEST_OBJ= test.obj

TEST2= src/sorttest.cpp
TEST_EXE2= sort.exe
TEST_OBJ2= sorttest.obj

ALLNEWFILES=*.obj *.exe


.PHONY all:
all: build1 build2

.PHONY build1:
build1: 
	$(CXX) $(CXXFLAGS) $(SOURCE)
 
.PHONY build2:
build2: 
	$(CXX) $(CXXFLAGS) $(SOURCE2)


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
	$(LINKORDER) $(TEST_OBJ) $(OBJS) -OUT:$(TEST_EXE)

.PHONY testrun:
testrun: 
	$(RUNORDER) $(TEST_EXE)


.PHONY test2:
test2: testrun2

.PHONY testobj2:
testobj2:  
	$(CXX) $(CFLAGS) -c $(TEST_OBJ2) $(TEST2)

.PHONY testbuild2:
testbuild2: 
	$(LINKORDER) $(TEST_OBJ2) $(OBJS2) -OUT:$(TEST_EXE2)


.PHONY testrun2:
testrun2: 
	$(RUNORDER) $(TEST_EXE2)


.PHONY clean:
clean: 
	$(DELETE) $(ALLNEWFILES)

# Google Test:
GTEST_DIR = /gtest
GTEST_INCLUDE_DIR = /gtest/include/gtest
GTEST_HEADERS = /gtest/include/gtest/*.h \
                /gtest/include/gtest/internal/*.h

