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
  std::cout << "| Testing balance()                         |" << std::endl;
  std::cout << "|-------------------------------------------|" << std::endl;

  tree.balance();
  std::cout << "Printing the content of the tree after balance()\n" << tree << std::endl;



  std::cout << "|-------------------------------------------|" << std::endl;
  std::cout << "| Testing copy semantics                    |" << std::endl;
  std::cout << "|-------------------------------------------|" << std::endl;

  BST<int,int> tree_1{tree};
  std::cout << "tree[8]" << std::endl;
  tree[8];
  std::cout << "tree_1[8]:" << std::endl;
  tree_1[8];
  std::cout << "tree_1 inserting key 11...";
  tree_1.insert({11, 11});
  std::cout << "\t...done" << std::endl;
  std::cout << "tree_1[11]:" << std::endl;
  tree_1[11];
  std::cout << "tree.find(11):" << std::endl;
  tree.find(11);

  BST<int,int> tree_2=tree;
  std::cout << "tree[8]:" << std::endl;
  tree[8];
  std::cout << "tree_2[8]:" << std::endl;
  tree_2[8];
  std::cout << "tree_2 inserting key 22...";
  tree_2.insert({22, 22});
  std::cout << "\t...done" << std::endl;
  std::cout << "tree_2[22]:" << std::endl;
  tree_2[22];
  std::cout << "tree.find(22):" << std::endl;
  tree.find(22);

  std::cout << "|-------------------------------------------|" << std::endl;
  std::cout << "| Testing move semantics                    |" << std::endl;
  std::cout << "|-------------------------------------------|" << std::endl;

  BST<int, int> tree_3(std::move(tree));
  std::cout << "Printing the content of the tree after move()\n" << tree << std::endl;;

  std::cout << "tree_3[8]:" << std::endl;
  tree_3[8];



  std::cout << "|-------------------------------------------|" << std::endl;
  std::cout << "| Testing clear()                           |" << std::endl;
  std::cout << "|-------------------------------------------|" << std::endl;

  tree.clear();
  tree_1.clear();
  tree_2.clear();

  std::cout << "Printing the content of the tree after clean()\n" << tree << std::endl;

  return 0;
  
}
