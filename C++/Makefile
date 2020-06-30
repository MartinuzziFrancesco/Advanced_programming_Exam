CXX = c++
CXXFLAGS = -std=c++11 -Wall -Wextra
TEST = tests
BCMK = benchmark
TESTSRC = test/Test.cpp
BCMKSRC = test/Benchmark.cpp
IFLAGS = -I include
DEFINES = NONE
DFLAGS = -D $(DEFINES)

all: $(TEST) $(BCMK) docs

docs: 
	doxygen dconfig


$(TEST): $(TESTSRC)
	$(CXX) -g $< -o $(TEST) $(CXXFLAGS) $(IFLAGS) $(DFLAGS)

$(BCMK): $(BCMKSRC)
	$(CXX) -g $< -o $(BCMK) $(CXXFLAGS) $(IFLAGS) $(DFLAGS)

clean:
	rm -fr tests benchmark docs

.PHONY: all docs clean
