// Copyright 2024 Jose Manuel Mora Z
/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 */

#pragma once

#include <iostream>
#include <stack>

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
  BSTreeNode() : key(DataType()) {}
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
  BSTreeNode<DataType>* root = nullptr;

 public:
  /// @brief Default constructor
  BSTree() = default;
  /// @brief Destructor
  ~BSTree() { this->clear(); }

  // Rule of five
  /// @brief Deleted copy constructor
  BSTree(const BSTree<DataType> &other) = delete;
  /// @brief Deleted copy assignment operator
  BSTree<DataType> &operator=(const BSTree<DataType> &other) = delete;
  /// @brief Deleted move constructor
  BSTree(BSTree<DataType> &&other) = delete;
  /// @brief Deleted move assignment operator
  BSTree<DataType> &operator=(BSTree<DataType> &&other) = delete;

  /// @brief Clears the tree
  void clear() {
    // If the tree is empty, return
    if (this->root == nullptr) return;
    // Clear the tree
    clear(this->root);
    // Set the root to nullptr
    this->root = nullptr;
  }

 private:   // Clear the tree from a specific node
  /// @brief Clears the tree starting from the given node
  /// @param rootOfSubtree Root of the subtree to clear
  void clear(BSTreeNode<DataType>* rootOfSubtree) {
    // If the subtree is empty, return
    if (rootOfSubtree == nullptr) return;
    // Clear the left and right subtrees
    clear(rootOfSubtree->getLeft());
    clear(rootOfSubtree->getRight());
    // Delete the node
    delete rootOfSubtree;
  }

 public:
  /// @brief Inserts a new element into the tree
  /// @param value Value to be inserted
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

  /// @brief Removes an element from the tree
  /// @param value Value to be removed
  void remove(const DataType &value) {
    // Search for the node to be removed
    BSTreeNode<DataType>* node = search(this->root, value);
    // If the node wasn't found, return
    if (node == nullptr) return;
    // Else remove the node
    remove(node);
  }

 private:  // Remove a specific node
  /// @brief Removes a node from the tree
  /// @param node Node to be removed
  void remove(BSTreeNode<DataType>* node) {
    // If the node is nullptr, return
    if (node == nullptr) return;
    // Node removal
    if (node->getLeft() == nullptr) {
      // Node has no left child
      this->transplant(node, node->getRight());
    } else if (node->getRight() == nullptr) {
      // Node has no right child
      this->transplant(node, node->getLeft());
    } else {
      // Node has two children
      BSTreeNode<DataType>* successor = getSuccessor(node);
      if (successor->getParent() != node) {
        // The successor is not the immediate child
        this->transplant(successor, successor->getRight());
        // Update the right child
        successor->setRight(node->getRight());
        successor->getRight()->setParent(successor);
      }
      // Replace the node with its successor
      this->transplant(node, successor);
      // Update the left child
      successor->setLeft(node->getLeft());
      successor->getLeft()->setParent(successor);
    }
  }

  /// @brief Replace the node u with the node v
  /// @param u Node to be replaced
  /// @param v Node to replace
  void transplant(BSTreeNode<DataType>* u, BSTreeNode<DataType>* v) {
    // If the parent of u is nullptr, u is the root
    if (u->getParent() == nullptr) {
      this->root = v;
    } else if (u == u->getParent()->getLeft()) {
      // U is the left child of its parent
      u->getParent()->setLeft(v);
    } else {
      // U is the right child of its parent
      u->getParent()->setRight(v);
    }
    // If v is not nullptr, update its parent
    if (v != nullptr) {
      v->setParent(u->getParent());
    }
  }

 public:
  /// @brief Iterative in order walk of the tree
  /// @param rootOfSubtree Root of the subtree to walk
  void inorderWalk(BSTreeNode<DataType>* rootOfSubtree) const {
    // If the subtree is empty, return
    if (rootOfSubtree == nullptr) return;
    // Create a stack to store the nodes
    std::stack<BSTreeNode<DataType>*> stack;
    // Start at the given root
    BSTreeNode<DataType>* current = rootOfSubtree;

    // While there are nodes to visit or the stack is not empty
    while (current || !stack.empty()) {
      // Keep going left until there are no more left children
      while (current) {
        // Push the nodes to the stack
        stack.push(current);
        current = current->getLeft();
      }

      // Pop the root of the current subtree and print it
      current = stack.top();
      stack.pop();
      std::cout << current->getKey() << " ";

      // Move to the right child
      current = current->getRight();
    }

    // End of the walk
    std::cout << std::endl;
  }

  /// @brief Iterative pre order walk of the tree
  /// @param rootOfSubtree Root of the subtree to walk
  void preorderWalk(BSTreeNode<DataType>* rootOfSubtree) const {
    // If the subtree is empty, return
    if (rootOfSubtree == nullptr) return;

    // Create a stack to store the nodes
    std::stack<BSTreeNode<DataType>*> stack;
    // Start at the given root
    stack.push(rootOfSubtree);

    // While the stack is not empty
    while (!stack.empty()) {
      // Pop the top of the stack and print it
      BSTreeNode<DataType>* current = stack.top();
      stack.pop();
      std::cout << current->getKey() << " ";

      // Push the right and left children to the stack if they exist
      if (current->getRight() != nullptr) {
        stack.push(current->getRight());
      }
      if (current->getLeft() != nullptr) {
        stack.push(current->getLeft());
      }
    }
  }

  /// @brief Iterative post order walk of the tree
  /// @param rootOfSubtree Root of the subtree to walk
  void postorderWalk(BSTreeNode<DataType>* rootOfSubtree) const {
    // If the subtree is empty, return
    if (rootOfSubtree == nullptr) return;

    // Create two stacks to store the nodes
    std::stack<BSTreeNode<DataType>*> stack1, stack2;
    // Start at the given root
    stack1.push(rootOfSubtree);
    // Create a pointer to the current node
    BSTreeNode<DataType>* current;

    // Iterate until the first stack is empty
    while (!stack1.empty()) {
      // Pop the top of the first stack and push it to the second stack
      current = stack1.top();
      stack1.pop();
      stack2.push(current);

      // Push the left and right children to the first stack if they exist
      if (current->getLeft()) {
        stack1.push(current->getLeft());
      }
      if (current->getRight()) {
        stack1.push(current->getRight());
      }
    }

    // Print the nodes in the second stack
    while (!stack2.empty()) {
      // Pop the top of the second stack and print it
      current = stack2.top();
      stack2.pop();
      std::cout << current->getKey() << " ";
    }

    // End of the walk
    std::cout << std::endl;
  }

  /// @brief Searches for a node with the given value
  /// @param rootOfSubtree Root of the subtree to search
  /// @param value Value to search for
  /// @return Node with the given value or nullptr if it doesn't exist
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

  /// @brief Returns the minimum node in the subtree
  /// @param rootOfSubtree Root of the subtree
  /// @return Minimum node in the subtree or nullptr if it's empty
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

  /// @brief Returns the maximum node in the subtree
  /// @param rootOfSubtree Root of the subtree
  /// @return Maximum node in the subtree or nullptr if it's empty
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

  /// @brief Returns the successor of the given node
  /// @param node Node to get the successor of
  /// @return Successor of the node or nullptr if it doesn't exist
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

  /// @brief Inserts n elements into the tree in ascending order
  /// @param n Number of elements to insert
  void fastInsert(size_t n) {
    // Clear the tree
    this->clear();
    // If n is 0, return
    if (n == 0) return;

    // Create the nodes
    BSTreeNode<DataType>* nodes = new BSTreeNode<DataType>[n];
    for (size_t i = 0; i < n; ++i) {
      nodes[i] = BSTreeNode<DataType>(i);
    }

    // Insert the nodes
    this->root = nodes[0];
    BSTreeNode<DataType>* current = this->root;
    for (size_t i = 1; i < n; ++i) {
      // Connect the nodes
      current->setRight(nodes[i]);
      nodes[i]->setParent(current);
      current = current->getRight();
    }
  }
};
