#include <iostream>
#include <utility>
#include <iterator>
#include <vector> 
#include <memory>

template <typename K, typename V>
class BTree{
  struct Node{
    //private: ??
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    Node* parent;
    std::pair<const K, V> data;

    Node();
    ~Node() noexcept = default;

  };
};
