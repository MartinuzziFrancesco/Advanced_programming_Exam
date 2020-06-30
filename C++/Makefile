CXX = c++
CXXFLAGS = -Wall -Wextra -g -std=c++11
DEPS = include/BTree.h
OBJ = test/Test.o include/BTree.h

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

Test: $(OBJ)
	$(CXX) -o $@ $< $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f test/Test.o Test
