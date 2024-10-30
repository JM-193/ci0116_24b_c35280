// Copyright 2024 Jose Manuel Mora Z
/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 */

#pragma once

/// @brief Colors for the Red-Black Tree nodes
enum colors { RED, BLACK };

template <typename DataType>
class RBTree;

/// @brief  Node of the Red-Black Tree
/// @tparam DataType Type of the data stored in the node
template <typename DataType>
class RBTreeNode {
 private:
  /// @brief Key of the node
  DataType key;
  /// @brief  Parent of the node
  RBTreeNode<DataType>* parent;
  /// @brief  Left child of the node
  RBTreeNode<DataType>* left;
  /// @brief  Right child of the node
  RBTreeNode<DataType>* right;
  /// @brief Color of the node
  enum colors color;

 public:
  friend class RBTree<DataType>;
  /// @brief Default constructor
  RBTreeNode() = default;
  /// @brief Constructor
  /// @param value Value to be stored in the node
  /// @param parent Pointer to the parent node
  /// @param left Pointer to the left child node
  /// @param right Pointer to the right child node
  /// @param c Color of the node
  RBTreeNode(const DataType &value, RBTreeNode<DataType>* parent = nullptr,
             RBTreeNode<DataType>* left = nullptr,
             RBTreeNode<DataType>* right = nullptr, enum colors c = RED)
             : key(value), parent(parent), left(left), right(right), color(c) {}
  /// @brief Destructor
  ~RBTreeNode() = default;
  // Rule of five
  /// @brief Deleted copy constructor
  RBTreeNode(const RBTreeNode<DataType>& other) = delete;
  /// @brief Deleted copy assignment operator
  RBTreeNode<DataType>& operator=(const RBTreeNode<DataType>& other) = delete;
  /// @brief Deleted move constructor
  RBTreeNode(RBTreeNode<DataType>&& other) = delete;
  /// @brief Deleted move assignment operator
  RBTreeNode<DataType>& operator=(RBTreeNode<DataType>&& other) = delete;

  /// @brief Get the key of the node
  /// @return Key of the node
  DataType getKey() const { return this->key; }
  /// @brief Get the color of the node
  /// @return Color of the node
  RBTreeNode<DataType>* getParent() const { return this->parent; }
  /// @brief Get the left child of the node
  /// @return Left child of the node
  RBTreeNode<DataType>* getLeft() const { return this->left; }
  /// @brief Get the right child of the node
  /// @return Right child of the node
  RBTreeNode<DataType>* getRight() const { return this->right; }
  /// @brief Set the key of the node
  /// @param key New key of the node
  void setKey(DataType key) { this->key = key; }
  /// @brief Set the parent of the node
  /// @param parent New parent of the node
  void setParent(RBTreeNode<DataType>* parent) { this->parent = parent; }
  /// @brief Set the left child of the node
  /// @param left New left child of the node
  void setLeft(RBTreeNode<DataType>* left) { this->left = left; }
  /// @brief Set the right child of the node
  /// @param right New right child of the node
  void setRight(RBTreeNode<DataType>* right) { this->right = right; }
};

template <typename DataType>
class RBTree {
 private:
  RBTreeNode<DataType>* root;

  RBTreeNode<DataType>* nil;

 public:
  /// @brief Default constructor
  RBTree() = default;
  /// @brief Destructor
  ~RBTree() = default;
  // Rule of five
  /// @brief Deleted copy constructor
  RBTree(const RBTree<DataType>& other) = delete;
  /// @brief Deleted copy assignment operator
  RBTree<DataType>& operator=(const RBTree<DataType>& other) = delete;
  /// @brief Deleted move constructor
  RBTree(RBTree<DataType>&& other) = delete;
  /// @brief Deleted move assignment operator
  RBTree<DataType>& operator=(RBTree<DataType>&& other) = delete;

  // TODO(jm)
  void insert(const DataType &value);
  // TODO(jm)
  void remove(const DataType &value);

  RBTreeNode<DataType>* search(const RBTreeNode<DataType>* rootOfSubtree,
                               const DataType &value) const;

  RBTreeNode<DataType>* getMinimum(
      const RBTreeNode<DataType>* rootOfSubtree) const {
    // If the subtree is empty, return nullptr
    if (rootOfSubtree == nullptr) return nullptr;
    // Search for the minimum node in the subtree
    RBTreeNode<DataType>* current =
        const_cast<RBTreeNode<DataType>*>(rootOfSubtree);
    while (current && current->getLeft() != nullptr) {
      current = current->getLeft();
    }
    // Return the minimum node
    return current;
  }

  RBTreeNode<DataType>* getMaximum(
      const RBTreeNode<DataType>* rootOfSubtree) const {
    // If the subtree is empty, return nullptr
    if (rootOfSubtree == nullptr) return nullptr;
    // Search for the maximum node in the subtree
    RBTreeNode<DataType>* current =
        const_cast<RBTreeNode<DataType>*>(rootOfSubtree);
    while (current && current->getRight() != nullptr) {
      current = current->getRight();
    }
    // Return the maximum node
    return current;
  }

  RBTreeNode<DataType>* getSuccessor(const RBTreeNode<DataType>* node) const {
    // If the node is nullptr, return nullptr
    if (node == nullptr) return nullptr;
    // If there's a right child, the successor is the min of the right subtree
    if (node->getRight() != nullptr) {
      return getMinimum(node->getRight());
    }
    // Otherwise, go up until we find a node that is a left child
    RBTreeNode<DataType>* current = node->getParent();
    RBTreeNode<DataType>* child = const_cast<RBTreeNode<DataType>*>(node);
    while (current != nullptr && child == current->getRight()) {
      child = current;
      current = current->getParent();
    }
    // Return the successor or nullptr if it doesn't exist
    return current;
  }

  /// @brief Get the root of the tree
  /// @return Root of the tree
  RBTreeNode<DataType>* getRoot() const { return this->root; }

  /// @brief Get the nil node
  /// @return Nil node
  RBTreeNode<DataType>* getNil() const { return this->nil; }
};
