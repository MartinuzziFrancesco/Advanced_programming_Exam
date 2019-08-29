#include <iostream>
#include <utility>
#include <iterator>
#include <vector> 
#include <memory>

////////////////////* CLASS AND STRUCT */////////////////////

/* ERROR HANDLING STRUCT */

struct Ovveride {
  std::string message;
  Ovveride(const std::string& s) : message{s} {}
};

/* BST CLASS */

template <typename K, typename V>
class BTree{

  /* NODE STRUCT */

  struct Node{

    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    Node* parent;
    std::pair<const K,V> data;

    Node();
    Node(Node* p, std::pair<const K, V>& d) : parent{p}, data{d};

    ~Node() noexcept = default;

  };

  public:

    using u_ptr = std::unique_ptr<Node>;
    using pair = std::pair<const K, V>;

  private:

    u_ptr root;

    BTree();
    ~BTree() noexcept = default;

  /* ITERATORS CLASS DECLARATION */

  class Iterator;
  class Const_Iterator;

  Iterator begin() noexcept { return Iterator{get_min()}; }
  Iterator end() { return Iterator{nullptr}; }

  Const_Iterator begin() noexcept {return Const_Iterator{get_min()};}
  Const_Iterator end() const { return Const_Iterator{nullptr}; }

  /* BST FUNCTIONS DECLARATION */

  void insert(const pair& p);
  void insert_new(const pair& p, Node* n);
  void clear();
  Iterator find(const K k) const noexcept; //maybe const_it?

};

////////////////////* ITERATORS */////////////////////////

/* ITERATOR */

template <typename K, typename V> 
class Iterator : public std::iterator<std::forward_iterator_tag, std::pair<const K,V>>{

  using pair = typename BTree<K,V>::std::pair<const K,V>;
  using node = BTree<K,V>::Node;

  node* pn;

public:

  Iterator(node* n) : pn{n} {}

  pair& operator*() const {return pn->data;}

  Iterator& operator++() {
    if (pn->right != nullptr) {
      pn = pn->right.get();
      while (pn->left.get()) {
        pn = pn->left.get();
      }
      return *this;
    }
    else {
      node* p = pn->parent;
      while (p != nullptr && pn == p->right.get()) {
        pn = p;
        p = p->parent;
      }
      pn = p;
      return *this;
	  }
  }

  bool operator==(const Iterator& other) { return pn == other.pn; }
  bool operator!=(const Iterator& other) { return !(*this == other); }

};

/* CONST_ITERATOR */

template <typename T, typename V>
class Const_Iterator : public BTree<T, V>::Iterator {

public:
  
  using parent = BTree<T, V>::Iterator;
  using pair = typename BTree<K,V>::std::pair<const K,V>;
  using node = BTree<K,V>::Node;

  using parent::Iterator;
  using parent::operator++;
  using parent::operator!=;
  using parent::operator==;

  const pair& operator*() const { return parent::operator*(); }

};

////////////////////* BST FUNCTIONS */////////////////////////

/* INSERT */

template <typename K, typename V>
void BTree<K, V>::insert(const pair& p) {
  if(root==nullptr) {
    root.reset(new Node{nullptr, p});
  }
  else{
    try insert_new(p, root.get());
    catch (const Ovveride& s) {
    std::cerr << s.message << std::endl;
    }
  }
}

/* INSERT_NEW */

template <typename K, typename V>   
void BTree<K, V>::insert_new(const pair& p, Node* n){
  if(p.first < n->data.first) {
    if(n->left==nullptr){
      n->left.reset(new Node{n, p});
    } else n = n->left.get();
  }
  else if(p.first > n->data.first) {
    if(n->right==nullptr){
      n->right.reset(new Node{n, p});
    } else n = n->right.get();
  }
  else if (p.first == comp->pair.first) {
    throw Override{"You are trying to override an existing key"};
    return;
  }
  insert_new(p, n);
}

/* CLEAR */

template <typename K, typename V> 
void BTree<K, V>::clear() noexcept {
  root.reset();
  std::cout << "Tree has been cleared" << std::endl;
}

/* FIND */

template <typename K, typename V>
typename BTree<K, V>::Iterator BTree<K, V>::find(const K key) const noexcept{
  
  Node* current_node{root.get()};

  while(current_node){
    K current_key = current_node->data.first;
    if(current_key == key) return Iterator{current_node}
    else if(current_key < key ){ current_node = current_node->left.get()}
    else if(current_key > key ){ current_node = current_node->right.get()}
  }

  return end();
}






/*
insert, used to insert a new pair key-value.
clear(), clear the content of the tree.
begin(), return an iterator to the first node (which likely will not be the root node)
end(), return a proper iterator
cbegin(), return a const_iterator to the first node
cend(), return a proper const_iterator
balance(), balance the tree.
find, find a given key and return an iterator to that node. If the key is not found returns end();
*/