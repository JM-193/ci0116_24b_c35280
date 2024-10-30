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
 private:
  /// @brief Key of the node
  DataType key;
  /// @brief Parent of the node
  BSTreeNode<DataType>* parent = nullptr;
  /// @brief Left child of the node
  BSTreeNode<DataType>* left = nullptr;
  /// @brief Right child of the node
  BSTreeNode<DataType>* right = nullptr;

 public:
  friend class BSTree<DataType>;
  /// @brief Default constructor
  BSTreeNode() = default;
  /// @brief Constructor
  /// @param value Key of the node
  /// @param parent Parent of the node
  /// @param left Left child of the node
  /// @param right Right child of the node
  BSTreeNode(const DataType &value, BSTreeNode<DataType>* parent = nullptr,
             BSTreeNode<DataType>* left = nullptr,
             BSTreeNode<DataType>* right = nullptr)
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
  DataType getKey() const { return this->key; }

  /// @brief Returns the parent of the node
  /// @return Parent of the node
  BSTreeNode<DataType>* getParent() const { return this->parent; }

  /// @brief Returns the left child of the node
  /// @return Left child of the node
  BSTreeNode<DataType>* getLeft() const { return this->left; }

  /// @brief Returns the right child of the node
  /// @return Right child of the node
  BSTreeNode<DataType>* getRight() const { return this->right; }

  /// @brief Sets the parent of the node
  /// @param parent New parent of the node
  void setParent(BSTreeNode<DataType>* parent) { this->parent = parent; }

  /// @brief Sets the left child of the node
  /// @param left New left child of the node
  void setLeft(BSTreeNode<DataType>* left) { this->left = left; }

  /// @brief Sets the right child of the node
  /// @param right New right child of the node
  void setRight(BSTreeNode<DataType>* right) { this->right = right; }
};

/// @brief A Binary Search Tree
/// @tparam DataType Typename of the tree's keys
template <typename DataType>
class BSTree {
 private:
  BSTreeNode<DataType>* root;

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

  void insert(const DataType &value) {
    // If the tree is empty, the new node is the root
    if (this->root == nullptr) {
      this->root = new BSTreeNode<DataType>(value);
      return;
    }

    // Else, search for the correct position
    BSTreeNode<DataType>* current = this->root;
    while (current) {
      if (value < current->getKey()) {
        // If the value is less than the current node's key, go left
        if (current->getLeft() == nullptr) {
          current->setLeft(new BSTreeNode<DataType>(value, current));
          return;
        }
        current = current->getLeft();
      } else if (value > current->getKey()) {
        // If the value is greater than the current node's key, go right
        if (current->getRight() == nullptr) {
          current->setRight(new BSTreeNode<DataType>(value, current));
          return;
        }
        current = current->getRight();
      } else {
        // The tree doesn't allow repeated elements, so don't insert it
        return;
      }
    }
    // The element couldn't be inserted
    return;
  }

  void remove(const DataType &value) {
    // Search for the node to be removed
    BSTreeNode<DataType>* node = search(this->root, value);
    if (node == nullptr) {
      // If the node wasn't found, return
      return;
    }
    // Node removal
    if (node->getLeft() == nullptr) {
      // Node has no left child
      if (node->getRight() == nullptr) {
        // If it also has no right child, just remove it
        delete node;
        return;
      }
      // Replace it with its right child
      node->getRight()->setParent(node->getParent());
      node->getParent()->setRight(node->getRight());
      delete node;
    } else if (node->getRight() == nullptr) {
      // Node has no right child
      if (node->getLeft() == nullptr) {
        // If it also has no left child, just remove it
        delete node;
        return;
      }
      // Replace it with its left child
      node->getLeft()->setParent(node->getParent());
      node->getParent()->setLeft(node->getLeft());
      delete node;
    } else {
      // Node has two children
      // Find the successor of the node
      BSTreeNode<DataType>* successor = getSuccessor(node);
      // Swap the node with its successor
      DataType temp = node->getKey();
      node->setKey(successor->getKey());
      successor->setKey(temp);
      // Remove the swapped node
      remove(successor->getKey());
    }
  }

  void inorderWalk(BSTreeNode<DataType>* rootOfSubtree) const {
    // TODO(jm): Understand this thing
    std::stack<BSTreeNode<DataType>*> stack;
    BSTreeNode<DataType>* current = root;

    while (current != nullptr || !stack.empty()) {
      while (current != nullptr) {
        stack.push(current);
        current = current->getLeft();
      }

      current = stack.top();
      stack.pop();
      std::cout << current->getKey() << " ";

      current = current->getRight();
    }
  }

  void preorderWalk(BSTreeNode<DataType>* rootOfSubtree) const {
    // TODO(jm): Understand this thing
    if (root == nullptr) return;

    std::stack<BSTreeNode<DataType>*> stack;
    stack.push(root);

    while (!stack.empty()) {
      BSTreeNode<DataType>* node = stack.top();
      stack.pop();
      std::cout << node->getKey() << " ";

      if (node->getRight() != nullptr) {
        stack.push(node->getRight());
      }
      if (node->getLeft() != nullptr) {
        stack.push(node->getLeft());
      }
    }
  }

  void postorderWalk(BSTreeNode<DataType>* rootOfSubtree) const {
    // TODO(jm): Understand this thing
    if (root == nullptr) return;

    std::stack<BSTreeNode<DataType>*> stack1, stack2;
    stack1.push(root);

    while (!stack1.empty()) {
      BSTreeNode<DataType>* node = stack1.top();
      stack1.pop();
      stack2.push(node);

      if (node->getLeft() != nullptr) {
        stack1.push(node->getLeft());
      }
      if (node->getRight() != nullptr) {
        stack1.push(node->getRight());
      }
    }

    while (!stack2.empty()) {
      BSTreeNode<DataType>* node = stack2.top();
      stack2.pop();
      std::cout << node->getKey() << " ";
    }
  }

  BSTreeNode<DataType>* search(const BSTreeNode<DataType>* rootOfSubtree,
                               const DataType &value) const {
    // Start at the sub-tree root
    BSTreeNode<DataType>* current =
        const_cast<BSTreeNode<DataType>*>(rootOfSubtree);
    // Search until the value is found or current is nullptr
    while (current && current->getKey() != value) {
      if (value < current->getKey()) {
        current = current->getLeft();
      } else {
        current = current->getRight();
      }
    }
    // Return the node or nullptr if it wasn't found
    return current;
  }

  BSTreeNode<DataType>* getMinimum(
      const BSTreeNode<DataType>* rootOfSubtree) const {
    // If the subtree is empty, return nullptr
    if (rootOfSubtree == nullptr) return nullptr;
    // Search for the minimum node in the subtree
    BSTreeNode<DataType>* current =
        const_cast<BSTreeNode<DataType>*>(rootOfSubtree);
    while (current && current->getLeft() != nullptr) {
      current = current->getLeft();
    }
    // Return the minimum node
    return current;
  }

  BSTreeNode<DataType>* getMaximum(
      const BSTreeNode<DataType>* rootOfSubtree) const {
    // If the subtree is empty, return nullptr
    if (rootOfSubtree == nullptr) return nullptr;
    // Search for the maximum node in the subtree
    BSTreeNode<DataType>* current =
        const_cast<BSTreeNode<DataType>*>(rootOfSubtree);
    while (current && current->getRight() != nullptr) {
      current = current->getRight();
    }
    // Return the maximum node
    return current;
  }

  BSTreeNode<DataType>* getSuccessor(const BSTreeNode<DataType>* node) const {
    // If the node is nullptr, return nullptr
    if (node == nullptr) return nullptr;
    // If there's a right child, the successor is the min of the right subtree
    if (node->getRight() != nullptr) {
      return getMinimum(node->getRight());
    }
    // Otherwise, go up until we find a node that is a left child
    BSTreeNode<DataType>* current = node->getParent();
    BSTreeNode<DataType>* child = const_cast<BSTreeNode<DataType>*>(node);
    while (current != nullptr && child == current->getRight()) {
      child = current;
      current = current->getParent();
    }
    // Return the successor or nullptr if it doesn't exist
    return current;
  }

  /// @brief Returns the root of the tree
  /// @return Root of the tree
  BSTreeNode<DataType>* getRoot() const { return this->root; }

  void fastInsert(size_t n) {
    // TODO(jm): ???
  }
};
