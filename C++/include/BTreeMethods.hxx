/**
 * @file BTreeMethods.h
 * @author Francesco Martinuzzi, Marco Alberto Grimaldi
 * @brief Header containing methods of BST class.
 */

#include "BTree.h"

template <typename K, typename V>
typename BST<K, V>::Iterator BST<K, V>:: begin() const noexcept { return Iterator{get_min()}; }

template <typename K, typename V>
typename BST<K, V>::Iterator BST<K, V>:: end() const noexcept { return Iterator{nullptr}; }

template <typename K, typename V>
typename BST<K, V>::Const_Iterator BST<K, V>:: cbegin() const noexcept {return Const_Iterator{get_min()};}

template <typename K, typename V>
typename BST<K, V>::Const_Iterator BST<K, V>::cend() const noexcept { return Const_Iterator{nullptr}; }

template <typename K, typename V>
void BST<K, V>:: insert(const pair& p) {
  if(root==nullptr) {
    root.reset(new Node{nullptr, nullptr, nullptr, p});
  }
  else{
    try{ 
      insert_new(p, root.get());
    }
      catch (const Override& s) {
        std::cerr << s.message << std::endl;
      }
  }
}

template <typename K, typename V>   
void BST<K, V>::insert_new(const pair& p, Node* n) {
  if(p.first < n->data.first) {
    if(n->left==nullptr){
      n->left.reset(new Node{n, nullptr, nullptr, p});
      return;
    } 
    else n = n->left.get();
  }

  else if(p.first > n->data.first) {
    if(n->right==nullptr){
      n->right.reset(new Node{n, nullptr, nullptr, p});
      return;
    } 
    else n = n->right.get();
  }

  else if (p.first == n->data.first) {
    throw Override("You are trying to override an existing pair");
    return;
  }
  insert_new(p, n);
}

template <typename K, typename V> 
void BST<K, V>::clear() noexcept {
  root.reset();
  std::cout << "Tree has been cleared" << std::endl;
}

template <typename K, typename V>
typename BST<K, V>::Iterator BST<K, V>:: find(const K key) const noexcept{
  
  Node* current_node{root.get()};

  while(current_node){

    K current_key = current_node->data.first;

    if(current_key == key){ 
      return Iterator{current_node};
    }
    else if(current_key < key ){ 
      current_node = current_node->right.get();
    }
    else if(current_key > key ){ 
      current_node = current_node->left.get();
    }
  }
  std::cout << "Key:" << key << " not found" << std::endl;
  return end();
}

template <typename K, typename V>
typename BST<K, V>::Node* BST<K, V>::get_min() const noexcept{
  if (root==nullptr){
    std::cout <<"Tree is empty, there is no tree." << std::endl;
  return nullptr;
  }

  Node* current_node{root.get()};

  while(current_node->left.get()){
    current_node = current_node->left.get();
  }
  return current_node;
}

template <typename K, typename V>
void BST<K, V>:: balance() noexcept{

  if (root == nullptr){
    std::cout<<"Tree is empty. It is in balance by default"<<std::endl;
    return;
  }
  std::vector<pair> vect;
  Iterator i{begin()};
  
  for(; i != nullptr; ++i)
    vect.push_back(*i);
  clear();
  balance_med(vect, 0, vect.size());
}

template <typename K, typename V>
void BST<K, V>::balance_med(std::vector<pair>& vect, std::size_t left, std::size_t right) noexcept{

  if(right-left < 1)
    return;

  auto med{(left+right)/2};
  insert(vect[med]);
  balance_med(vect, left, med);
  balance_med(vect, med+1, right);
}



//////////////////////* OPERATOR OVERLOADING *//////////////////////////

/* OPERATOR[] */

template<typename K, typename V>
V& BST<K,V>::operator[](const K& key) noexcept {

  Iterator i = find(key);

  if (i != end()) {
    std::cout << "Key: " << key <<" has value: " << (*i).second << std::endl;
    return (*i).second;
  }

  std::cout << "Allocating a new node with key: " << key <<" and value {}" << std::endl;
  insert(pair{key, V{}});
  std::cout << "A new key has been inserted." << std::endl;
  i = find(key);
  std::cout << "Key " << key <<" has value: " << (*i).second << std::endl; 
  return (*i).second;
}

/* CONST_OPERATOR[] */

template<typename K, typename V>
const V& BST<K,V>::operator[](const K& key) const {

  Const_Iterator i = find(key);

  if (i != end()) 
    return (*i).second; 
  throw 
    std::runtime_error("const operator[] trying to access a non existing key.");
}

/**operator <<**/

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, BST<K, V>& bst) noexcept {
  for (const auto &x : bst)             
    os << x.first << ": " << x.second << std::endl;
  return os;
}



////////////////////* COPY*//////////////////////
/* copy */
template <typename K, typename V>
BST<K, V>::BST(const BST& bst) noexcept {
  if (bst.root != nullptr){
    root.reset(new Node{nullptr, nullptr, nullptr, bst.root.get()->data});
    copy_new(bst.root.get(), root);
  }
}


template <typename K, typename V>
void BST<K, V>::copy_new(Node* old_one, std::unique_ptr<Node>& new_one) noexcept {
  if(old_one->left != nullptr){
    new_one->left.reset(new Node{new_one.get(), nullptr, nullptr, old_one->left->data});
    copy_new(old_one->left.get(), new_one->left);
  }
  if(old_one->right != nullptr){
    new_one->right.reset(new Node{new_one.get(), nullptr, nullptr, old_one->right->data});
    copy_new(old_one->right.get(), new_one->right);
  }
} 

template <typename K, typename V>
BST<K, V>::BST(BST&& bst) : root{std::move(bst.root)}{}

template <typename K, typename V>
BST<K, V>& BST<K, V>::operator=(const BST& bst) noexcept{
  root = std::move(bst.root);
  return *this;
}

