#include "BTree.h"
#include <iostream>


int main() {

  std::cout << "|-------------------------------------------|" << std::endl;
  std::cout << "| Testing tree constructor and insert()     |" << std::endl;
  std::cout << "|-------------------------------------------|" << std::endl;

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

  std::cout << "Printing the content of the tree\n" << tree << std::endl;

  std::cout << "|-------------------------------------------|" << std::endl;
  std::cout << "| Testing insert() over existing key        |" << std::endl;
  std::cout << "|-------------------------------------------|" << std::endl;

  tree.insert({3, 10});
  std::cout << "Printing the content of the tree\n" << tree << std::endl;

  std::cout << "|-------------------------------------------|" << std::endl;
  std::cout << "| Testing find()                            |" << std::endl;
  std::cout << "|-------------------------------------------|" << std::endl;

  tree.find(7);
  tree.find(3);
  tree.find(8);
  tree.find(5);
  std::cout << std::endl;

  std::cout << "|-------------------------------------------|" << std::endl;
  std::cout << "| Testing [] operator over existing key     |" << std::endl;
  std::cout << "|-------------------------------------------|" << std::endl;

  tree[14];
  std::cout << "\n";
  std::cout << "|-------------------------------------------|" << std::endl;
  std::cout << "| Testing [] operator over non-existing key |" << std::endl;
  std::cout << "|-------------------------------------------|" << std::endl;
  tree[16];
  std::cout << std::endl;

  std::cout << "|-------------------------------------------|" << std::endl;
  std::cout << "| Testing clear()                           |" << std::endl;
  std::cout << "|-------------------------------------------|" << std::endl;

  tree.clear();
  std::cout << "Printing the content of the tree after clean()\n" << tree << std::endl;

  return 0;
  
}
