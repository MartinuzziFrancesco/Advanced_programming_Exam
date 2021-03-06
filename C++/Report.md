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
As requested the our BST has the following public member function:
    insert(const pair& p), used to insert a new pair key-value;
    clear(), clear the content of the tree;
    begin(), return an iterator to the first node (which likely will not be the root node);
    end(), return a proper iterator;
    cbegin(), return a const_iterator to the first node;
    cend(), return a proper const_iterator;
    balance(), balance the tree.;
    find(const K key), find a given key and return an iterator to that node. If the key is not found returns end();

Also whose are implemented;
    operator[](const K& key) function, the const and non-const versions. This functions, return a reference to the value associated to the key k. If the key is not present, a new node with key k is allocated having the value: value_type{};
    operator<<: in order to print (in order) key: value of all the nodes in the tree;
    copy and move semantics;
    getmin() return pointer to the node with minimun key_value;

For deatail and documentation see Doxygen.

# Tests and Benchmarks
In the file `Test.cpp` can be found tests for every method implemented in the project. The source code is readable and easy to tweak for the user and functions also as a diplay for the use of the BST and its methods.

In the file `Benchmark.cpp` is contained a comparison of the `find()` function between a BST, an ordered BST, a standard library `map` and a standard library `unordered_map`. The test is done creating a vector of a given dimension containing `int` values ranging from 1 to the max value (the max value is increased at every iteration). They are ordered by construction, but are reshuffled in order to simulate randomness. After that the BST, map and unordered map are constructed from this vector and the time to search random values is collected. To have more statistics this procedure is done multiple times and an average is taken. The results are then printed on file and can be easily be plotted.

![image](https://user-images.githubusercontent.com/10376688/86258865-97e70680-bbbb-11ea-859c-355ccbac5101.png)

We can clearly see from the picture that the standard library implementation for the unbalanced map is by far the fastest, as it is to be expected: in the average case the complexity is constant, and in the worst case scenario is linear in container size [[1]](#1). As for our implementation we can see that the unbalanced tree is returning the worst performance of all the analyzed alghoritms, but when we use the balanced tree the `find()` times are faster that the standard library implementation of `map`, that it's worth mentioning is also based on search trees, so the complexity time is also logaritmic with the size [[2]](#2). We can spot a polynomial trend in the balanced and unbalanced trees and in the std `map`, a results we exepcted and were really happy to see. If we were to increase the number of nodes a little more perhaps the log distribution would be more clear, but the large amount of memory occupation doesn't allow us to go further than a dezon millions. We can also plot the ressults in loglog to see if it returns a straight line: in that case we would know that the behaviour is actually logaritmic.

![image](https://user-images.githubusercontent.com/10376688/86259628-88b48880-bbbc-11ea-93b0-682802b59a10.png)

In the lower values the trend is not really linear, but after a few thousands the linearity can be clearly seen. 

Overall we are pretty satisifed with the results, using a machine with a little more RAM could have helped us in a better display, but even with a limitate statistic we can see that the behaviour is as intended.



## References
<a id="1">[1]</a>
http://www.cplusplus.com/reference/unordered_map/unordered_map/find/
<a id="2">[2]</a>
https://en.cppreference.com/w/cpp/container/map/find
