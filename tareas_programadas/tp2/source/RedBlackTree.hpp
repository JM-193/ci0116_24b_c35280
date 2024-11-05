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
  RBTreeNode<DataType>* parent = nullptr;
  /// @brief  Left child of the node
  RBTreeNode<DataType>* left = nullptr;
  /// @brief  Right child of the node
  RBTreeNode<DataType>* right = nullptr;
  /// @brief Color of the node
  enum colors color;

 public:
  friend class RBTree<DataType>;
  /// @brief Default constructor
  RBTreeNode() : key(DataType()), color(BLACK) {}
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
  /// @brief Root of the tree
  RBTreeNode<DataType>* root = nullptr;
  /// @brief Nil node
  RBTreeNode<DataType>* nil;

 public:
  /// @brief Default constructor
  RBTree() : nil(new RBTreeNode<DataType>()) {}
  /// @brief Destructor
  ~RBTree() { this->clear(); }

  // Rule of five
  /// @brief Deleted copy constructor
  RBTree(const RBTree<DataType>& other) = delete;
  /// @brief Deleted copy assignment operator
  RBTree<DataType>& operator=(const RBTree<DataType>& other) = delete;
  /// @brief Deleted move constructor
  RBTree(RBTree<DataType>&& other) = delete;
  /// @brief Deleted move assignment operator
  RBTree<DataType>& operator=(RBTree<DataType>&& other) = delete;

  /// @brief Clear the tree
  void clear() {
    // If the tree is empty, return
    if (this->root == nullptr) return;
    // Clear the tree
    clear(this->root);
    // Delete the nil node
    delete this->nil;
    // Set the root to nullptr
    this->root = nullptr;
  }

 private:  // Clear the tree from a specific node
  /// @brief Clears the tree starting from the given node
  /// @param rootOfSubtree Root of the subtree to clear
  void clear(RBTreeNode<DataType>* rootOfSubtree) {
    // If the subtree is empty, return
    if (rootOfSubtree == this->nil) return;
    // Clear the left and right subtrees
    clear(rootOfSubtree->getLeft());
    clear(rootOfSubtree->getRight());
    // Delete the node
    delete rootOfSubtree;
  }

 public:
  /// @brief Insert a new node in the tree
  /// @param value Value to be inserted in the tree
  void insert(const DataType &value) {
    // Start searching for the insertion point
    RBTreeNode<DataType>* current = this->root;
    while (current && current != this->nil) {
      if (value < current->getKey()) {
        current = current->getLeft();
      } else {
        current = current->getRight();
      }
    }
    // The tree is empty, insert as the root (which is black)
    if (current->getParent() == this->nil) {
      this->root = new RBTreeNode<DataType>(value, this->nil, this->nil,
                                            this->nil, BLACK);
      return;
    }
    // Create the new node
    auto newNode = new RBTreeNode<DataType>(value, current->getParent(),
                                            this->nil, this->nil, RED);
    // Insert the new node
    if (value < current->getKey()) {
      current->setLeft(newNode);
    } else {
      current->setRight(newNode);
    }
    // Fix the tree
    this->insertFixup(newNode);
  }

 private:  // Insert Fixup
  /// @brief Fix the tree after inserting a new node
  /// @param node Node to start the fixup
  void insertFixup(RBTreeNode<DataType>* node) {
    // While the parent is red
    while (node->getParent()->color == RED) {
      if (node->getParent() == node->getParent()->getParent()->getLeft()) {
        // The parent is the left child of the grandparent
        this->leftInsertFixup(node);
      } else {
        // The parent is the right child of the grandparent
        this->rightInsertFixup(node);
      }
    }
    // The root must be black
    this->root->color = BLACK;
  }

  /// @brief Section of the insert fixup if the parent is the left child
  /// @param node Node to start the fixup
  void leftInsertFixup(RBTreeNode<DataType>* node) {
    // Get the uncle
    RBTreeNode<DataType>* uncle = node->getParent()->getParent()->getRight();
    // Case 1: The uncle is red
    if (uncle->color == RED) {
      node->getParent()->color = BLACK;
      uncle->color = BLACK;
      node->getParent()->getParent()->color = RED;
      node = node->getParent()->getParent();
    } else {
      // Case 2: The uncle is black and the node is the right child
      if (node == node->getParent()->getRight()) {
        node = node->getParent();
        this->leftRotate(node);
      }
      // Case 3: The uncle is black and the node is the left child
      node->getParent()->color = BLACK;
      node->getParent()->getParent()->color = RED;
      this->rightRotate(node->getParent()->getParent());
    }
  }

  /// @brief Section of the insert fixup if the parent is the right child
  /// @param node Node to start the fixup
  void rightInsertFixup(RBTreeNode<DataType>* node) {
    // Get the uncle
    RBTreeNode<DataType>* uncle = node->getParent()->getParent()->getLeft();
    // Case 1: The uncle is red
    if (uncle->color == RED) {
      node->getParent()->color = BLACK;
      uncle->color = BLACK;
      node->getParent()->getParent()->color = RED;
      node = node->getParent()->getParent();
    } else {
      // Case 2: The uncle is black and the node is the left child
      if (node == node->getParent()->getLeft()) {
        node = node->getParent();
        this->rightRotate(node);
      }
      // Case 3: The uncle is black and the node is the right child
      node->getParent()->color = BLACK;
      node->getParent()->getParent()->color = RED;
      this->leftRotate(node->getParent()->getParent());
    }
  }

  /// @brief Left rotate the tree starting from the given node
  /// @param node Node to start the rotation
  void leftRotate(RBTreeNode<DataType>* node) {
    // Get the right child
    RBTreeNode<DataType>* rightChild = node->getRight();
    // Update the right child
    node->setRight(rightChild->getLeft());
    if (rightChild->getLeft() != this->nil) {
      rightChild->getLeft()->setParent(node);
    }
    // Update the parent
    rightChild->setParent(node->getParent());
    // If node was the root, update it
    if (node->getParent() == this->nil) {
      this->root = rightChild;
    } else if (node == node->getParent()->getLeft()) {
      node->getParent()->setLeft(rightChild);
    } else {
      node->getParent()->setRight(rightChild);
    }
    // Update the right child
    rightChild->setLeft(node);
    node->setParent(rightChild);
  }

  /// @brief Right rotate the tree starting from the given node
  /// @param node Node to start the rotation
  void rightRotate(RBTreeNode<DataType>* node) {
    // Get the left child
    RBTreeNode<DataType>* leftChild = node->getLeft();
    // Update the left child
    node->setLeft(leftChild->getRight());
    if (leftChild->getRight() != this->nil) {
      leftChild->getRight()->setParent(node);
    }
    // Update the parent
    leftChild->setParent(node->getParent());
    // If node was the root, update it
    if (node->getParent() == this->nil) {
      this->root = leftChild;
    } else if (node == node->getParent()->getRight()) {
      node->getParent()->setRight(leftChild);
    } else {
      node->getParent()->setLeft(leftChild);
    }
    // Update the left child
    leftChild->setRight(node);
    node->setParent(leftChild);
  }

 public:
  /// @brief Remove a node with the given value
  /// @param value Value to be removed
  void remove(const DataType &value) {
    // Search for the node to remove
    RBTreeNode<DataType>* node = search(this->root, value);
    // If the node doesn't exist, return
    if (node == nullptr) return;
    // Remove the node
    this->remove(node);
  }

 private:  // Remove a specific node
  /// @brief Remove the given node
  /// @param node Node to be removed
  void remove(RBTreeNode<DataType>* node) {
    // Save the original node
    RBTreeNode<DataType>* original = node;
    // Save the original color
    enum colors originalColor = original->color;
    // Child node to replace the original
    RBTreeNode<DataType>* child = nullptr;
    if (node->getLeft() == this->nil) {
      // If the left child is nil, replace the node with the right child
      child = node->getRight();
      this->transplant(node, node->getRight());
    } else if (node->getRight() == this->nil) {
      // If the right child is nil, replace the node with the left child
      child = node->getLeft();
      this->transplant(node, node->getLeft());
    } else {
      // If the node has two children, replace it with the successor
      original = this->getSuccessor(node);
      originalColor = original->color;
      child = original->getRight();
      // Check if the successor is the immediate child
      if (original->getParent() == node) {
        child->setParent(original);
      } else {
        // If it's not, replace the successor with its right child
        this->transplant(original, original->getRight());
        // Update the right child
        original->setRight(node->getRight());
        original->getRight()->setParent(original);
      }
      // Replace the node with the successor
      this->transplant(node, original);
      // Update the left child
      original->setLeft(node->getLeft());
      original->getLeft()->setParent(original);
      // Update the color
      original->color = node->color;
    }
    // If the original color was black, fix the tree
    if (originalColor == BLACK) {
      this->removeFixup(child);
    }
  }

  /// @brief Fix the tree after removing a node
  /// @param node Node to start the fixup
  void removeFixup(RBTreeNode<DataType>* node) {
    // While the node is not the root and is black
    while (node != this->root && node->color == BLACK) {
      if (node == node->getParent()->getLeft()) {
        // The node is the left child
        this->leftRemoveFixup(node);
      } else {
        // The node is the right child
        this->rightRemoveFixup(node);
      }
    }
    // The node must be black
    node->color = BLACK;
  }

  /// @brief Section of the remove fixup if the node is the left child
  /// @param node Node to start the fixup
  void leftRemoveFixup(RBTreeNode<DataType>* node) {
    // Get the sibling
    RBTreeNode<DataType>* sibling = node->getParent()->getRight();
    // Case 1: The sibling is red
    if (sibling->color == RED) {
      sibling->color = BLACK;
      node->getParent()->color = RED;
      this->leftRotate(node->getParent());
      sibling = node->getParent()->getRight();
    }
    // Case 2: The sibling is black and both children are black
    if (sibling->getLeft()->color == BLACK &&
        sibling->getRight()->color == BLACK) {
      sibling->color = RED;
      node = node->getParent();
    } else {
      // Case 3: The sibling is black and the left child is red
      if (sibling->getRight()->color == BLACK) {
        sibling->getLeft()->color = BLACK;
        sibling->color = RED;
        this->rightRotate(sibling);
        sibling = node->getParent()->getRight();
      }
      // Case 4: The sibling is black and the right child is red
      sibling->color = node->getParent()->color;
      node->getParent()->color = BLACK;
      sibling->getRight()->color = BLACK;
      this->leftRotate(node->getParent());
      node = this->root;
    }
  }

  /// @brief Section of the remove fixup if the node is the right child
  /// @param node Node to start the fixup
  void rightRemoveFixup(RBTreeNode<DataType>* node) {
    // Get the sibling
    RBTreeNode<DataType>* sibling = node->getParent()->getLeft();
    // Case 1: The sibling is red
    if (sibling->color == RED) {
      sibling->color = BLACK;
      node->getParent()->color = RED;
      this->rightRotate(node->getParent());
      sibling = node->getParent()->getLeft();
    }
    // Case 2: The sibling is black and both children are black
    if (sibling->getRight()->color == BLACK &&
        sibling->getLeft()->color == BLACK) {
      sibling->color = RED;
      node = node->getParent();
    } else {
      // Case 3: The sibling is black and the right child is red
      if (sibling->getLeft()->color == BLACK) {
        sibling->getRight()->color = BLACK;
        sibling->color = RED;
        this->leftRotate(sibling);
        sibling = node->getParent()->getLeft();
      }
      // Case 4: The sibling is black and the left child is red
      sibling->color = node->getParent()->color;
      node->getParent()->color = BLACK;
      sibling->getLeft()->color = BLACK;
      this->rightRotate(node->getParent());
      node = this->root;
    }
  }

  /// @brief Replace the node u with the node v
  /// @param u Node to be replaced
  /// @param v Node to replace
  void transplant(RBTreeNode<DataType>* u, RBTreeNode<DataType>* v) {
    // If u is the root, update it
    if (u->getParent() == this->nil) {
      this->root = v;
    } else if (u == u->getParent()->getLeft()) {
      // U is the left child
      u->getParent()->setLeft(v);
    } else {
      // U is the right child
      u->getParent()->setRight(v);
    }
    // Update the parent of v
    v->setParent(u->getParent());
  }

  /// @brief Search for a node with the given value
  /// @param rootOfSubtree Root of the subtree to search
  /// @param value Value to search for
  /// @return Node with the given value or nullptr if it doesn't exist
  RBTreeNode<DataType>* search(const RBTreeNode<DataType>* rootOfSubtree,
                               const DataType &value) const {
    // If the subtree is empty, return nullptr
    if (rootOfSubtree == nullptr) return nullptr;
    // Search for the node with the given value
    RBTreeNode<DataType>* current =
        const_cast<RBTreeNode<DataType>*>(rootOfSubtree);
    while (current && current->getKey() != value) {
      if (value < current->getKey()) {
        current = current->getLeft();
      } else {
        current = current->getRight();
      }
    }
    // Return the node or nullptr if it doesn't exist
    return current;
  }

 public:
  /// @brief Search for a node with the given value
  /// @param value Value to search for
  /// @return Node with the given value or nullptr if it doesn't exist
  RBTreeNode<DataType>* search(const DataType &value) const {
    return search(this->root, value);
  }

  /// @brief Get the minimum node in the subtree
  /// @param rootOfSubtree Root of the subtree
  /// @return Minimum node in the subtree or nullptr if it's empty
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

  /// @brief Get the maximum node in the subtree
  /// @param rootOfSubtree Root of the subtree
  /// @return Maximum node in the subtree or nullptr if it's empty
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

  /// @brief Get the successor of the given node
  /// @param node Node to get the successor of
  /// @return Successor of the node or nullptr if it doesn't exist
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
