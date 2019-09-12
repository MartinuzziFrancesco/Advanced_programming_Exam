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

    ~node() /* noexcept */ = default;
  };

public:
  using u_ptr = std::unique_ptr<node>;
  using pair = std::pair<const K, V>;

  
  BST() = default;
  ~BST() noexcept = default;

private:
  u_ptr root = nullptr;


  /* ITERATORS CLASS DECLARATION */

  class Iterator;
  class Const_Iterator;

  Iterator begin() noexcept { return Iterator{get_min()}; }
  Iterator end() { return Iterator{nullptr}; }

  Const_Iterator cbegin() noexcept { return Const_Iterator{get_min()}; }
  Const_Iterator cend() const { return Const_Iterator{nullptr}; }

  /* BST FUNCTIONS DECLARATION */

  void insert(const pair &p);
  void insert_new(const pair &p, node *n);
  void clear() noexcept;
  Iterator find(const K k) const noexcept;
  node *get_min() const noexcept;

  /* OPERATOR OVERLOADING */

  V &operator[](const K &key) noexcept;
  const V &operator[](const K &key) const;
};

////////////////////* ITERATORS */////////////////////////

/* ITERATOR */

template <typename K, typename V>
class Iterator : public std::iterator<std::forward_iterator_tag, std::pair<const K, V>>
{

  using pair = typename std::pair<const K, V>;
  using node = typename BST<K, V>::node;

  node *pn;

public:
  Iterator(node *n) : pn{n} {}

  pair &operator*() const { return pn->data; }

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
class Const_Iterator : public BST<K, V>::Iterator
{

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
void BST<K, V>::insert(const pair& p) {
  if(root==nullptr) {
    root.reset(new node{nullptr, p});
  }
  else{
    /* try{  */insert_new(p, root.get());
     /*  catch (const Ovveride& s) {
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
    }
  }
  std::cout << "Key:" << key << " not found" << std::endl;
  return end();
}

/* GET_MIN*/

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
  Iterator i = find(key);
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