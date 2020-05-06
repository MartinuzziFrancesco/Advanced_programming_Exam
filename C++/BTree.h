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

    node();
    node(node *p, std::pair<const K, V> &d) : parent{p}, data{d} {};

    ~node() /*  noexcept */ = default;
  };

public:
  using u_ptr = std::unique_ptr<node>;
  using pair = std::pair<const K, V>;

  BST();
  ~BST() /*  noexcept */ = default;

private:
  u_ptr root;

  /* iteratorS CLASS DECLARATION */

  class iterator;
  class Const_iterator;

  iterator begin() noexcept { return iterator{get_min()}; }
  iterator end() { return iterator{nullptr}; }

  Const_iterator cbegin() noexcept { return Const_iterator{get_min()}; }
  Const_iterator cend() const { return Const_iterator{nullptr}; }

  /* BST FUNCTIONS DECLARATION */

  void insert(const pair &p);
  void insert_new(const pair &p, node *n);
  void clear() noexcept;
  iterator find(const K k) const noexcept;
  node *del_aux(node *n) noexcept;

  void swap(node *x, node *y);

  void trasplant(node *old, node *n) noexcept;
  void del(const K k) noexcept;
  node *get_min() const noexcept;

  /* OPERATOR OVERLOADING */

  V &operator[](const K &key) noexcept;
  const V &operator[](const K &key) const;
};

////////////////////* iteratorS */////////////////////////

/* iterator */

template <typename K, typename V>
class iterator : public std::iterator<std::forward_iterator_tag, std::pair<const K, V>>
{

  using pair = typename std::pair<const K, V>;
  using node = typename BST<K, V>::node;

  node *pn;

public:
  iterator(node *n) : pn{n} {}

  pair &operator*() const { return pn->data; }

  iterator &operator++()
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

  bool operator==(const iterator &other) { return pn == other.pn; }
  bool operator!=(const iterator &other) { return !(*this == other); }
};

/* CONST_iterator */

template <typename K, typename V>
class Const_iterator : public BST<K, V>::iterator
{

public:
  using parent = typename BST<K, V>::iterator;
  using pair = typename std::pair<const K, V>;
  using node = typename BST<K, V>::node;

  using parent::iterator;
  using parent::operator++;
  using parent::operator!=;
  using parent::operator==;

  const pair &operator*() const { return parent::operator*(); }
};

////////////////////* BST FUNCTIONS */////////////////////////

/* INSERT */

template <typename K, typename V>
void BST<K, V>::insert(const pair &p)
{
  if (root == nullptr)
  {
    root.reset(new node{nullptr, p});
  }
  else
  {
    /* try{  */ insert_new(p, root.get());
    /* catch (const Ovveride& s) {
        std::cerr << s.message << std::endl;
      } 
    } */
  }
}

/* INSERT_NEW */

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
typename BST<K, V>::iterator BST<K, V>::find(const K key) const noexcept
{

  node *current_node{root.get()};

  while (current_node)
  {
    K current_key = current_node->data.first;
    if (current_key == key)
      return iterator{current_node};
    else if (current_key < key)
    {
      current_node = current_node->left.get();
    }
    else if (current_key > key)
    {
      current_node = current_node->right.get();
    }
  }
  std::cout << "Key:" << key << " not found" << std::endl;
  return end();
}

/* TRASPLANT*/

/* template <typename K, typename V>
void BST<K, V>::trasplant(node* old, node* n) noexcept{
  if(old->parent==nullptr){
    *this->root.release() = n;
  } else {
    char old_side = childhood_side(old);
    get_child(old->parent, old_side) = n;
  }
  if(n!=nullptr) n->parent = old->parent.get();
} */

/* SWAP NODES*/

template <typename K, typename V>
void BST<K, V>::swap(node *x, node *y)
{
  x->left.swap(y->left);
  x->right.swap(y->right);
  if (x->parent != nullptr)
  {
    char x_side = childhood_side(x);
    char y_side = childhood_side(y);
    if (x_side == 'l' && y_side == 'l')
      x->parent->left.swap(y->parent->left);
    else if (x_side == 'l' && y_side == 'r')
      x->parent->left.swap(y->parent->right);
    else if (x_side == 'r' && y_side == 'l')
      x->parent->right.swap(y->parent->left);
    else
      x->parent->right.swap(y->parent->right);
  }
  else
  {
    if (childhood_side(y) == 'l')
      root.swap(y->parent->left);
    else
      root.swap(y->parent->rigt);
  }
  std::swap(x->parent, y->parent);
}

/* DEL_AUX */

template <typename K, typename V>
typename BST<K, V>::node *BST<K, V>::del_aux(node *n) noexcept
{
  if (n->left == nullptr && n->right == nullptr)
  {
    if (childhood_side(n) == 'l')
      n->parent->left.clear();
    else
      n->parent->right.clear();
    return nullptr;
  }
  if (n->left == nullptr)
  {
    n->data = n->right->data;
    n->right.clear();
    return nullptr;
  }
  if (n->right == nullptr)
  {
    n->data = n->left->data;
    n->left.clear();
    return nullptr;
  }
  iterator i{n};
  ++i;
  std::pair<const K, V> tmp = n->data;
  n->data = i->pn->data;
  i->pn->data = tmp;
  return del_aux(i->pn);
}

/* DEL */

template <typename K, typename V>
void BST<K, V>::del(const K key) noexcept
{
  iterator i{find(key)};
  node *n = del_aux(i->pn);
  std::cout << "Node with key: " << key << " has been deleted." << std::endl;
}

/* GET_MIN */

template <typename K, typename V>
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
    current_node = current_node->left.get();
  }
  return current_node;
}

//////////////////////* OPERATOR OVERLOADING *//////////////////////////

/* OPERATOR[] */

template <typename K, typename V>
V &BST<K, V>::operator[](const K &key) noexcept
{
  iterator i = find(key);
  if (i != end())
  {
    return (*i).second;
  }
  insert(pair{key, V{}});
  std::cout << "A new key has been inserted." << std::endl;
}

/* CONST_OPERATOR[] */

template <typename K, typename V>
const V &BST<K, V>::operator[](const K &key) const
{
  iterator i = find(key);
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

/* template <typename K, typename V>
void BST<K, V>::swap(node* x, node* y){
  if(x->parent!=nullptr){
    char x_side = childhood_side(x);
    if(x_side=='l') x->parent->left.release();
    else x->parent->right.release();
  }
  char y_side = childhood_side(y);
  if(y_side=='l') y->parent->left.release();
  else y->parent->right.release();
  node* x_left = x->left.release();
  node* x_right = x->right.release();
  x->right = y->right.release();
  if(x->parent!=nullptr){
    if(x_side=='l') x->parent->left = y;
    else x->parent->right = y;
  } else {
    root.release();
    root = y;
  }
  y->left = x_left;
  y->right = x_right;
  if(y_side=='l') y->parent->left = x;
  else y->parent->right = x;
  node* x_parent = x->parent;
  x->parent = y->parent;
  y->parent = x_parent;
} */

/* template <typename K, typename V>
typename BST<K, V>::node* BST<K, V>::del_aux(node* n) noexcept{
  if(n->left==nullptr){
    swap(n, n->right);
    n->parent->right.clear();
    return n;
  }
  if(n->right==nullptr){
    swap(n, n->left);
    n->parent->right.clear();
    return n;
  }
  iterator i{n};
  ++i;
  swap(n, i->pn);
  return del_aux(i->pn);
}
 */