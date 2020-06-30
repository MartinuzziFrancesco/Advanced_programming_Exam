# Binary Search Tree Implementation in C++

The folder contains an implementation of a templated binary search tree. 
## Execution

The provided `Makefile` is used to compila automatically the complete project. If one doesn't desire to compile the project in its entirety it suffice to give one of the following commands:
- `make tests` generates a `tests` executable in which all the function of the binary search tree are tested
- `make benchmark` generates a `benchmark` executable in which is present the comparison of search time between our implementation of the binary search tree, ordered and not, and the std::map. 
- `make docs` generates a docs folder in which will be contained html and latex sources for the documentation created with Doxygen.

The command `make` generates all of the above. To remove all the files created it suffices to give `make clean`, no need for manual deletion. 

## Structure

The two folder contains the source code and the test code. In `include` is the implementation of the binary search tree, divided into tree headers. In `test` there are both tests for the functions and benchmarks for the implementation.
