/**
 * @file BTree.h
 * @author Francesco Martinuzzi, Marco Alberto Grimaldi
 * @brief Header containing signatures of variables and method for the BST class.
 */


#include <iostream>
#include <utility>
#include <iterator>
#include <vector> 
#include <memory>

#ifndef BST_H
#define BST_H


/**
  * @brief Implementation of a binary search tree templated on the type of the key and the type of the associated value.
  * @tparam K Type of node keys.
  * @tparam V Type of node values.
  */

template <typename K, typename V>
class BST{
    
  /**
   * @brief Struct of a node of the binary search tree. Constitued by two children nodes and one parent node.
   */
  struct Node;

  /** Alias used for better code readability*/
  using pair = std::pair<const K, V>;
  
  /** Alias used for better code readability*/
  using u_ptr = std::unique_ptr<Node>;
  
  /** Root node of the binary search tree. */
  u_ptr root;

  /**
   * @brief Support function for Balance method, not inplace, recursive calls pivoting with median (Key) value.
   */
  void balance_med(std::vector<pair>& vect, std::size_t left, std::size_t right) noexcept;

  /**
   * @brief Insert method, throw exeption if user try to override an existing key.
   */
  void insert_new(const pair& p, Node* n);

  /**
   * @brief Method for retrive minimum key.
   * @return pointer to the node that has min key.
   */
  Node* get_min() const noexcept;

  /**
   * @brief Support function for copy semantic.
   */
  void copy_new(Node* old_one, u_ptr& new_one) noexcept;

public:

  /**
   * @brief Default constructor for binary search tree.
   */
  BST() = default;

  /**
   * @brief Constructor for binary search tree.
   * @param bst 
   */
  BST(const BST& bst) noexcept;

  /**
   * @brief Default destructor for binary search tree.
   */
  ~BST() noexcept = default;

  /**
   * @brief Copy constructor
   */
  BST& operator=(const BST& bst) noexcept;

  /**
   * @brief Move constructor
   */
  BST(BST&& bst);

  /**
   * @brief An iterator for the binary search tree class. Inherits from the standard library iterator std::iterator.
   */
  class Iterator;

  /**
   * @brief A constant iterator for the binary search tree class.
   */
  class Const_Iterator;

  /**
   * @brief Iteration on the binary search tree.
   * @return Iterator to the node with the lowest key. 
   */
  Iterator begin() const noexcept; 

  /**
   * @brief Iteration on the binary search tree.
   * @return Iterator to nullptr. 
   */
  Iterator end() const noexcept; 

  /**
   * @brief Iteration on the binary search tree.
   * @return Const_Iterator to the node with the lowest key. 
   */
  Const_Iterator cbegin() const noexcept;

  /**
   * @brief Iteration on the binary search tree.
   * @return Const_Iterator to nullptr. 
   */
  Const_Iterator cend() const noexcept;

  /** 
   * @brief Insert a new node in the binary search tree
   * @param p The key/value pair to be inserted 
   */
  void insert(const pair& p);

  /** 
   * @brief Clears all the elements in the binary search tree
   */
  void clear() noexcept;

  /** 
   * Finds a node in the binary search tree
   * @param k The key of the node
   * @return Iterator to the node
   */
  Iterator find(const K k) const noexcept;

  /**
   * @brief Balances the binary search tree
   */
  void balance() noexcept;

  /**
   * @brief Operator[] overloading, if the key the user is searching for doesn't exist it create new node with pair<key,0>.
   * @return reference to the value of searched key.
   */
  V& operator[](const K& key) noexcept;

  /**
   * @brief Operator[] overloading, if the key the user is searching for doesn't exist it throw a runtime_error.
   * @return constant reference to the value of searched key.
   */
  const V& operator[](const K& key) const;

};

#include "BTreeSubClasses.hxx"
#include "BTreeMethods.hxx"
#endif
