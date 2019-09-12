#include <iostream>
#include <utility>
#include <iterator>
#include <vector>
#include <memory>
#include <string>

////////////////////* CLASS AND STRUCT */////////////////////

/* ERROR HANDLING STRUCT */

struct Ovveride
{
  std::string message;
  Ovveride(const std::string &s) : message{s} {}
};

struct Empty
{
  std::string message;
  Empty(const std::string &s) : message{s} {}
};

struct Not_Exist
{
  std::string message;
  Not_Exist(const std::string &s) : message{s} {}
};

/* BST CLASS */

template <typename K, typename V>
class BST
{

  /* node STRUCT */

  struct node
  {

    std::unique_ptr<node> left;
    std::unique_ptr<node> right;
    node *parent;
    std::pair<const K, V> data;

<<<<<<< HEAD
    node();
    node(node *p, std::pair<const K, V> &d) : parent{p}, data{d} {};
=======
    Node();
    Node(Node* p, Node* l, Node* r, const std::pair<const K, V>& d) : 
      parent{p}, 
      data{d},
      left{l},
      right{r}
    {};
    ~Node() noexcept = default;
>>>>>>> b0f887e9b56fa8651a6afc397e197ed1b17dca43

    ~node() /* noexcept */ = default;
  };

public:
  using u_ptr = std::unique_ptr<node>;
  using pair = std::pair<const K, V>;

  
  BST() = default;
  ~BST() noexcept = default;

<<<<<<< HEAD
private:
  u_ptr root = nullptr;


  /* ITERATORS CLASS DECLARATION */

  class Iterator;
  class Const_Iterator;

  Iterator begin() noexcept { return Iterator{get_min()}; }
  Iterator end() { return Iterator{nullptr}; }

  Const_Iterator cbegin() noexcept { return Const_Iterator{get_min()}; }
  Const_Iterator cend() const { return Const_Iterator{nullptr}; }
=======
    u_ptr root;
    void balance_med(std::vector<std::pair<const K, V>>& vect, std::size_t left, std::size_t right) noexcept;
    void insert_new(const pair& p, Node* n);
    Node* get_min() const noexcept;

  public:
>>>>>>> b0f887e9b56fa8651a6afc397e197ed1b17dca43

    /*constructor*/
    BST() = default;
    BST(const BST& bst);
    ~BST() noexcept = default;

<<<<<<< HEAD
  void insert(const pair &p);
  void insert_new(const pair &p, node *n);
  void clear() noexcept;
  Iterator find(const K k) const noexcept;
  node *get_min() const noexcept;
=======
    /* ITERATORS CLASS DECLARATION */
    class Iterator;
    class Const_Iterator;
    Iterator begin() noexcept { return Iterator{get_min()}; }
    Iterator end() { return Iterator{nullptr}; }
    Const_Iterator cbegin() noexcept {return Const_Iterator{get_min()};}
    Const_Iterator cend() const { return Const_Iterator{nullptr}; }
>>>>>>> b0f887e9b56fa8651a6afc397e197ed1b17dca43

    /* BST FUNCTIONS DECLARATION */
    void insert(const pair& p);
    void clear() noexcept;
    Iterator find(const K k) noexcept;
    void balance() noexcept;

<<<<<<< HEAD
  V &operator[](const K &key) noexcept;
  const V &operator[](const K &key) const;
=======
    /* OPERATOR OVERLOADING */
    V& operator[](const K& key) noexcept;
    const V& operator[](const K& key) const;

>>>>>>> b0f887e9b56fa8651a6afc397e197ed1b17dca43
};

////////////////////* ITERATORS */////////////////////////

/* ITERATOR */

<<<<<<< HEAD
template <typename K, typename V>
class Iterator : public std::iterator<std::forward_iterator_tag, std::pair<const K, V>>
{
=======
template <typename K, typename V> 
class BST<K,V>:: Iterator : public std::iterator<std::forward_iterator_tag, std::pair<const K,V>>{
>>>>>>> b0f887e9b56fa8651a6afc397e197ed1b17dca43

  using pair = typename std::pair<const K, V>;
  using node = typename BST<K, V>::node;

  node *pn;

public:
  Iterator(node *n) : pn{n} {}

<<<<<<< HEAD
  pair &operator*() const { return pn->data; }
=======
  Iterator(node* n) : pn{n} {}
  pair& operator*() const {return pn->data;}
>>>>>>> b0f887e9b56fa8651a6afc397e197ed1b17dca43

  Iterator &operator++()
  {
    if (pn->right != nullptr)
    {
      pn = pn->right.get();
      while (pn->left.get())
      {
        pn = pn->left.get();
      }
      return *this;
    }
    else
    {
      node *p = pn->parent;
      while (p != nullptr && pn == p->right.get())
      {
        pn = p;
        p = p->parent;
      }
      pn = p;
      return *this;
    }
  }

  bool operator==(const Iterator &other) { return *this == other; }
  bool operator!=(const Iterator &other) { return !(*this == other); }
};

/* CONST_ITERATOR */

template <typename K, typename V>
<<<<<<< HEAD
class Const_Iterator : public BST<K, V>::Iterator
{
=======
class BST<K, V>:: Const_Iterator : public BST<K, V>::Iterator {
>>>>>>> b0f887e9b56fa8651a6afc397e197ed1b17dca43

public:
  using parent = typename BST<K, V>::Iterator;
  using pair = typename std::pair<const K, V>;
  using node = typename BST<K, V>::node;

  using parent::Iterator;
  using parent::operator++;
  using parent::operator!=;
  using parent::operator==;

  const pair &operator*() const { return parent::operator*(); }
};

////////////////////* BST FUNCTIONS */////////////////////////

/* INSERT */

template <typename K, typename V>
void BST<K, V>:: insert(const pair& p) {
  if(root==nullptr) {
<<<<<<< HEAD
    root.reset(new node{nullptr, p});
  }
  else{
    /* try{  */insert_new(p, root.get());
     /*  catch (const Ovveride& s) {
        std::cerr << s.message << std::endl;
      }
    } */
=======
    root.reset(new Node{nullptr, nullptr, nullptr, p});
  }
  else{
    try{ 
      insert_new(p, root.get());
    }
      catch (const Ovveride& s) {
        std::cerr << s.message << std::endl;
      }
>>>>>>> b0f887e9b56fa8651a6afc397e197ed1b17dca43
  }
}

/* INSERT_NEW */

<<<<<<< HEAD
template <typename K, typename V>
void BST<K, V>::insert_new(const pair &p, node *n)
{
  if (p.first < n->data.first)
  {
    if (n->left == nullptr)
    {
      n->left.reset(new node{n, p});
    }
    else
      n = n->left.get();
  }
  else if (p.first > n->data.first)
  {
    if (n->right == nullptr)
    {
      n->right.reset(new node{n, p});
    }
    else
      n = n->right.get();
  }
  else if (p.first == n->pair.first)
  {
    throw Ovveride{"You are trying to override an existing key"};
=======
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
>>>>>>> b0f887e9b56fa8651a6afc397e197ed1b17dca43
    return;
  }
  insert_new(p, n);
}

/* CLEAR */

template <typename K, typename V>
void BST<K, V>::clear() noexcept
{
  root.reset();
  std::cout << "Tree has been cleared" << std::endl;
}

/* FIND */

template <typename K, typename V>
<<<<<<< HEAD
typename BST<K, V>::Iterator BST<K, V>::find(const K key) const noexcept
{

  node *current_node{root.get()};

  while (current_node)
  {
    K current_key = current_node->data.first;
    if (current_key == key)
      return Iterator{current_node};
    else if (current_key < key)
    {
      current_node = current_node->left.get();
    }
    else if (current_key > key)
    {
      current_node = current_node->right.get();
=======
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
>>>>>>> b0f887e9b56fa8651a6afc397e197ed1b17dca43
    }
  }
  std::cout << "Key:" << key << " not found" << std::endl;
  return end();
}

/* GET_MIN*/

template <typename K, typename V>
<<<<<<< HEAD
typename BST<K, V>::node *BST<K, V>::get_min() const noexcept
{
  if (root == nullptr)
  {
    throw Empty{"Tree is empty, there is no start."};
    return nullptr;
  }
  node *current_node{root.get()};
  while (current_node->left.get())
  {
=======
typename BST<K, V>::Node* BST<K, V>::get_min() const noexcept{
  if (root==nullptr){
    std::cout <<"Tree is empty, there is no tree." << std::endl;
  return nullptr;
  }

  Node* current_node{root.get()};

  while(current_node->left.get()){
>>>>>>> b0f887e9b56fa8651a6afc397e197ed1b17dca43
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

<<<<<<< HEAD
template <typename K, typename V>
V &BST<K, V>::operator[](const K &key) noexcept
{
  Iterator i = find(key);
  if (i != end())
  {
    return (*i).second;
  }
=======
template<typename K, typename V>
V& BST<K,V>::operator[](const K& key) noexcept {

  Iterator i = find(key);

  if (i != end()) {
    std::cout << "Key: " << key <<" has value: " << (*i).second << std::endl;
    return (*i).second;
  }

  std::cout << "Allocating a new node with key: " << key <<" and value {}" << std::endl;
>>>>>>> b0f887e9b56fa8651a6afc397e197ed1b17dca43
  insert(pair{key, V{}});
  std::cout << "A new key has been inserted." << std::endl;
  i = find(key);
  std::cout << "Key " << key <<" has value: " << (*i).second << std::endl; 
  return (*i).second;
}

/* CONST_OPERATOR[] */

<<<<<<< HEAD
template <typename K, typename V>
const V &BST<K, V>::operator[](const K &key) const
{
  Iterator i = find(key);
  if (i != end())
  {
    return (*i).second;
  }
  throw Not_Exist{"const operator[] trying to access a non existing key."};
}

/*
insert, used to insert a new pair key-value.                                                                      V (not tested)
clear(), clear the content of the tree.                                                                           V (not tested)
begin(), return an iterator to the first node (which likely will not be the root node)                            V (not tested)
end(), return a proper iterator                                                                                   V (not tested)
cbegin(), return a const_iterator to the first node                                                               V (not tested)
cend(), return a proper const_iterator                                                                            V (not tested)
balance(), balance the tree.
find, find a given key and return an iterator to that node. If the key is not found returns end();                V (not tested)
*/

int main()
{
  BST<int, int> test{};

  return 0;
}
=======
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

>>>>>>> b0f887e9b56fa8651a6afc397e197ed1b17dca43
