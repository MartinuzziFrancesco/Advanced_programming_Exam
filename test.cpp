#include "BTree.h"
#include <iostream>


int main() {

  // Tree creation and population

  BST<int,int> tree{};

  tree.insert({8, 1});
  tree.insert({3, 1});
  tree.insert({10, 1});
  tree.insert({1, 1});
  tree.insert({6, 1});
  tree.insert({7, 1});
  tree.insert({14, 1});
  tree.insert({13, 1});
  tree.insert({4, 1});

  // Printing

  std::cout << "Printing the content of the tree\n" << tree << std::endl;

  // Insert and override

  tree.insert({3, 10});
  std::cout << "Printing the content of the tree\n" << tree << std::endl;

  // Find test

  tree.find(7);
  tree.find(3);
  tree.find(8);
  tree.find(5);

  std::cout << std::endl;

  // [] operator

  tree[14];
  std::cout << "\n";
  tree[16];
  std::cout << std::endl;

  return 0;
  
}
