/**
 * @file BTreeSubClasses.h
 * @author Francesco Martinuzzi, Marco Alberto Grimaldi
 * @brief Header containing classes of BST class.
 */

#include "BTree.h"

/**
* @brief Error message for overriding existing elements.
*/
struct Override {
  std::string message;
  Override(const std::string& s) : message{s} {}
};

template <typename K, typename V>

/**
* @brief Struct of a node of the binary search tree. Constitued by two children nodes and one parent node.
*/
struct BST<K, V>::Node{
    /** Parent node*/
    Node* parent;

    /**Left child node, with the smallest key*/
    std::unique_ptr<Node> left;

    /**Right child node, with the greater key*/
    std::unique_ptr<Node> right;

    /** The data in the node is stored in key-value format. 
     * The key is assumed constant to ensure consistency.
     */
    std::pair<const K, V> data;

    /**
    * @brief Default constructor of a Node
    */
    Node() noexcept;

    /**
    * @brief Constructor of a Node.
    * @param d The data to be inserted into the node.
    * @param p The parent of the node.
    * @param l The left node of the node.
    * @param r The right node of the node.
    */
    Node(Node* p, Node* l, Node* r, const std::pair<const K, V>& d) noexcept: 
      parent{p},
      left{l},
      right{r}, 
      data{d}
    {};

    /**
    * @brief Default destructor of a Node.
    */
    ~Node() noexcept = default;
};

/**
 * @brief An iterator for the binary search tree class. Inherits from the standard library iterator std::iterator.
 */
template <typename K, typename V> 
class BST<K,V>::Iterator : public std::iterator<std::forward_iterator_tag, std::pair<const K,V>>{

  /** Alias used for better code readability*/
  using pair = typename std::pair<const K,V>;

  /** Alias used for better code readability*/
  using node = typename BST<K,V>::Node;

  /** Node referred to by the iterator */
  node* pn;

public:
  /**
  * @brief Returns an iterator on the current node.
  * @param n The node on which the iterator is constructed.
  */
  Iterator(node* n) : pn{n} {}

  /**
  * @brief Overload of operator () for deferencing an iterator on a binary search tree
  * @return Reference to the data in the node, in key/value format.
  */
  pair& operator*() const noexcept {return pn->data;}

  /**
  * @brief Overload of operator ++ to advance the iterator to next node.
  * @return Reference to an iterator pointing the following node.
  */
  Iterator& operator++() noexcept{
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

  /**
  * @brief Overload of operator == to check equality of operators.
  * @param other The operator to compare to the current one.
  * @return Bool true if the iterators point to the same node, false otherwise.
  */
  bool operator==(const Iterator& other) const noexcept { return pn == other.pn; }

  /**
  * @brief Overload of operator != to check inequality of operators.
  * @param other The operator to compare to the current one.
  * @return Bool false if the iterators point to the same node, true otherwise.
  */
  bool operator!=(const Iterator& other) const noexcept { return !(*this == other); }

};

/**
 * @brief A constant iterator for the binary search tree class.
 */

template <typename K, typename V>
class BST<K, V>::Const_Iterator : public BST<K, V>::Iterator {
    
  /** Alias used for better code readability*/
  using parent = typename BST<K, V>::Iterator;
  /** Alias used for better code readability*/
  using pair = typename std::pair<const K,V>;
  //using node = typename BST<K,V>::Node;
  
public:
  /** Inheritance of methods*/
  using parent::Iterator;

  /** Inheritance of methods*/

  using parent::operator++;
  /** Inheritance of methods*/

  using parent::operator!=;
  
  /** Inheritance of methods*/
  using parent::operator==;

  /**
  * @brief Overload of operator () for deferencing an iterator on a binary search tree
  * @return const Reference to the data in the node, in key/value format.
  */
  const pair& operator*() const noexcept { return parent::operator*(); }

};
