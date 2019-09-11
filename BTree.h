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

struct Empty {
  std::string message;
  Empty(const std::string& s) : message{s} {}
};

struct Not_Exist {
  std::string message;
  Not_Exist(const std::string& s) : message{s} {}
};

/* BST CLASS */

template <typename K, typename V>
class BST{

  /* NODE STRUCT */

  struct Node{

    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    Node* parent;
    std::pair<const K,V> data;

    Node();
    Node(Node* p, Node* l, Node* r, const std::pair<const K, V>& d) : 
      parent{p}, 
      data{d},
      left{l},
      right{r}
    {};
    ~Node() noexcept = default;

  };

  public:

    using u_ptr = std::unique_ptr<Node>;
    using pair = std::pair<const K, V>;

  private:

    u_ptr root;
    void balance_med(std::vector<std::pair<const K, V>>& vect, std::size_t left, std::size_t right) noexcept;
    void insert_new(const pair& p, Node* n);
    Node* get_min() const noexcept;

  public:

    /*constructor*/
    BST() = default;
    BST(const BST& bst);
    ~BST() noexcept = default;

    /* ITERATORS CLASS DECLARATION */
    class Iterator;
    class Const_Iterator;
    Iterator begin() noexcept { return Iterator{get_min()}; }
    Iterator end() { return Iterator{nullptr}; }
    Const_Iterator cbegin() noexcept {return Const_Iterator{get_min()};}
    Const_Iterator cend() const { return Const_Iterator{nullptr}; }

    /* BST FUNCTIONS DECLARATION */
    void insert(const pair& p);
    void clear() noexcept;
    Iterator find(const K k) noexcept;
    void balance() noexcept;

    /* OPERATOR OVERLOADING */
    V& operator[](const K& key) noexcept;
    const V& operator[](const K& key) const;

};

////////////////////* ITERATORS */////////////////////////

/* ITERATOR */

template <typename K, typename V> 
class BST<K,V>:: Iterator : public std::iterator<std::forward_iterator_tag, std::pair<const K,V>>{

  using pair = typename std::pair<const K,V>;
  using node = typename BST<K,V>::Node;

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

template <typename K, typename V>
class BST<K, V>:: Const_Iterator : public BST<K, V>::Iterator {

public:
  
  using parent = typename BST<K, V>::Iterator;
  using pair = typename std::pair<const K,V>;
  using node = typename BST<K,V>::Node;

  using parent::Iterator;
  using parent::operator++;
  using parent::operator!=;
  using parent::operator==;

  const pair& operator*() const { return parent::operator*(); }

};

////////////////////* BST FUNCTIONS */////////////////////////

/* INSERT */

template <typename K, typename V>
void BST<K, V>:: insert(const pair& p) {
  if(root==nullptr) {
    root.reset(new Node{nullptr, nullptr, nullptr, p});
  }
  else{
    try{ 
      insert_new(p, root.get());
    }
      catch (const Ovveride& s) {
        std::cerr << s.message << std::endl;
      }
  }
}

/* INSERT_NEW */

template <typename K, typename V>   
void BST<K, V>::insert_new(const pair& p, Node* n){
  if(p.first < n->data.first) {
    if(n->left==nullptr){
      n->left.reset(new Node{n, nullptr, nullptr, p});
    } 
    else n = n->left.get();
  }

  else if(p.first > n->data.first) {
    if(n->right==nullptr){
      n->right.reset(new Node{n, nullptr, nullptr, p});
    } 
    else n = n->right.get();
  }

  else if (p.first == n->data.first) {
    n->data.second = p.second;
    return;
  }
  insert_new(p, n);
}

/* CLEAR */

template <typename K, typename V> 
void BST<K, V>::clear() noexcept {
  root.reset();
  std::cout << "Tree has been cleared" << std::endl;
}

/* FIND */

template <typename K, typename V>
typename BST<K, V>::Iterator BST<K, V>:: find(const K key) noexcept{
  
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

/* GET_MIN*/

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

/* balance */
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
std::ostream& operator<<(std::ostream& os, BST<K, V>& bst) {
  for (const auto &x : bst)             
    os << x.first << ": " << x.second << std::endl;
  return os;
}

