CXX = c++
CXXFLAGS = -Wall -Wextra -g -std=c++11
DEPS = BTree.h
OBJ = Test.o BTree.h

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

Test: $(OBJ)
	$(CXX) -o $@ $< $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f Test.o