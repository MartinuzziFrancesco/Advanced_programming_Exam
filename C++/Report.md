# Introduction

This project consists in the implementation of a templated [binary search tree](https://en.wikipedia.org/wiki/Binary_search_tree), using C++. In addition to this implementation a comparison between a ordered and unordered tree is also carried out, and the results will be showed in this brief report. The structure of the report is as follows: in the first section we will give an overview of the implementation of the classes and subclasses created for the binary search tree implementation, in the second section we will give a description of the methods implemented and in the last section we will show the results of the benchmarks we carried out for our implementation.

# Classes structure
## Node

The building block of the binary search tree is of course the single node, that we implemented using a `struct`. This choice allows us to use all its methods and variables, since they are public by default, but since is set as private on the tree structure the user will have no access to them, since she doesn't need to. The data inside the node is stored in a key/value fashion, and the key is set to constant in order to mantain the structure of the tree after it has been constructed. Modifying this value could potentially lead to a tree that it is not longer consistent with the definition of lower key values set on the left and higher key values set on the right.

The node object has three pointers: to the parent node, and to its children. The pointers to the childern nodes are defined using the class defined in the standard library called `unique_ptr` to facilitate memory management. 
## Binary Search Tree (BST)

The construction of the BST has only one , private, member variable, `root` which consists in a unique pointer to its root node. 

The construction of the BST is implemented in a `class`, since we want to have more control over the public variables and methods.
## Iterator and Const_Iterator

This two classes are used to perform forward iterations on the tree. They are constructed building over the standard library class `iterator`. The iterators are set to public, since we want them to be available for the user. The overload of the operator ++ allows them to only move forward starting from a node.
# Methods


# Tests and Benchmarks
In the file `Test.cpp` can be found tests for every method implemented in the project. The source code is readable and easy to tweak for the user and functions also as a diplay for the use of the BST and its methods.

In the file `Benchmark.cpp` is contained a comparison of the `find()` function between a BST, an ordered BST, a standard library `map` and a standard library `unordered_map`. The test is done creating a vector of a given dimension containing `int` values ranging from 1 to the max value (the max value is increased at every iteration). They are ordered by construction, but are reshuffled in order to simulate randomness. After that the BST, map and unordered map are constructed from this vector and the time to search random values is collected. To have more statistics this procedure is done multiple times and an average is taken. The results are then printed on file and can be easily be plotted.
