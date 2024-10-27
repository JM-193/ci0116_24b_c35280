// Copyright 2024 Jose Manuel Mora Z
/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 */

#pragma once
#include <cstddef>

template <typename DataType>
class BSTree;

/// @brief Node of a binary search tree
/// @tparam DataType Typename of the node's key
template <typename DataType>
class BSTreeNode {
 public:
  friend class BSTree<DataType>;
  /// @brief Default constructor
  BSTreeNode() = default;
  /// @brief Constructor
  /// @param value Key of the node
  /// @param parent Parent of the node
  /// @param left Left child of the node
  /// @param right Right child of the node
  BSTreeNode(const DataType &value, BSTreeNode<DataType> *parent = nullptr,
             BSTreeNode<DataType> *left = nullptr,
             BSTreeNode<DataType> *right = nullptr)
             : key(value), parent(parent), left(left), right(right) {}
  /// @brief Destructor
  ~BSTreeNode() = default;

  // Rule of five
  /// @brief Deleted copy constructor
  BSTreeNode(const BSTreeNode<DataType> &other) = delete;
  /// @brief Deleted copy assignment operator
  BSTreeNode<DataType> &operator=(const BSTreeNode<DataType> &other) = delete;
  /// @brief Deleted move constructor
  BSTreeNode(BSTreeNode<DataType> &&other) = delete;
  /// @brief Deleted move assignment operator
  BSTreeNode<DataType> &operator=(BSTreeNode<DataType> &&other) = delete;

  /// @brief Returns the key of the node
  /// @return Key of the node
  DataType getKey() const { return key; }

  /// @brief Returns the parent of the node
  /// @return Parent of the node
  BSTreeNode<DataType> *getParent() const { return parent; }

  /// @brief Returns the left child of the node
  /// @return Left child of the node
  BSTreeNode<DataType> *getLeft() const { return left; }

  /// @brief Returns the right child of the node
  /// @return Right child of the node
  BSTreeNode<DataType> *getRight() const { return right; }

  /// @brief Sets the parent of the node
  /// @param parent New parent of the node
  void setParent(BSTreeNode<DataType> *parent) { this->parent = parent; }

  /// @brief Sets the left child of the node
  /// @param left New left child of the node
  void setLeft(BSTreeNode<DataType> *left) { this->left = left; }

  /// @brief Sets the right child of the node
  /// @param right New right child of the node
  void setRight(BSTreeNode<DataType> *right) { this->right = right; }

 private:
  /// @brief Key of the node
  DataType key;
  /// @brief Parent of the node
  BSTreeNode<DataType> *parent = nullptr;
  /// @brief Left child of the node
  BSTreeNode<DataType> *left = nullptr;
  /// @brief Right child of the node
  BSTreeNode<DataType> *right = nullptr;
};

/// @brief A Binary Search Tree
/// @tparam DataType Typename of the tree's keys
template <typename DataType>
class BSTree {
 private:
  BSTreeNode<DataType> *root;

 public:
  /// @brief Default constructor
  BSTree() = default;
  /// @brief Destructor
  ~BSTree() = default;

  // Rule of five
  /// @brief Deleted copy constructor
  BSTree(const BSTree<DataType> &other) = delete;
  /// @brief Deleted copy assignment operator
  BSTree<DataType> &operator=(const BSTree<DataType> &other) = delete;
  /// @brief Deleted move constructor
  BSTree(BSTree<DataType> &&other) = delete;
  /// @brief Deleted move assignment operator
  BSTree<DataType> &operator=(BSTree<DataType> &&other) = delete;

  void insert(const DataType &value);

  void remove(const DataType &value);

  void inorderWalk(BSTreeNode<DataType> *rootOfSubtree) const;

  void preorderWalk(BSTreeNode<DataType> *rootOfSubtree) const;

  void postorderWalk(BSTreeNode<DataType> *rootOfSubtree) const;

  BSTreeNode<DataType> *search(const BSTreeNode<DataType> *rootOfSubtree,
                               const DataType &value) const;

  BSTreeNode<DataType> *getMinimum(
      const BSTreeNode<DataType> *rootOfSubtree) const;

  BSTreeNode<DataType> *getMaximum(
      const BSTreeNode<DataType> *rootOfSubtree) const;

  BSTreeNode<DataType> *getSuccessor(const BSTreeNode<DataType> *node) const;

  /// @brief Returns the root of the tree
  /// @return Root of the tree
  BSTreeNode<DataType> *getRoot() const { return root; }

  void fastInsert(size_t n);
};
