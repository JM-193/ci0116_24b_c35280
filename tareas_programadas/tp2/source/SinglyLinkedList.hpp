// Copyright 2024 Jose Manuel Mora Z
/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 */

#pragma once
template <typename DataType>
class SLList;

/// @brief Node of a singly linked list
/// @tparam DataType Typename of the node's key
template <typename DataType>
class SLListNode {
 private:
  /// @brief The key of the node
  DataType key;
  /// @brief The next node
  SLListNode<DataType>* next = nullptr;

 public:
  friend class SLList<DataType>;

  /// @brief Default Constructor
  SLListNode() : key(DataType()) {}

  /// @brief Constructor
  explicit SLListNode(const DataType& value,
      SLListNode<DataType>* next = nullptr)
      : key(value), next(next) {}

  /// @brief Destructor
  ~SLListNode() = default;

  // Rule of five
  SLListNode(const SLListNode<DataType>&) = delete;
  SLListNode<DataType>& operator=(const SLListNode<DataType>&) = delete;
  SLListNode(SLListNode<DataType>&&) = delete;
  SLListNode<DataType>& operator=(SLListNode<DataType>&&) = delete;

  /// @brief Get the key of the node
  /// @return The key of the node
  DataType getKey() const { return this->key; }

  /// @brief Get the next node
  /// @return The next node
  SLListNode<DataType>* getNext() const { return this->next; }

  /// @brief Set the key of the node
  /// @param key The new key of the node
  void setKey(DataType key) { this->key = key; }

  /// @brief Set the next node
  /// @param next The new next node
  void setNext(SLListNode<DataType>* next) { this->next = next; }
};

/// @brief A Singly Linked List
/// @tparam DataType Typename of the list's key
template <typename DataType>
class SLList {
 private:
  SLListNode<DataType>* nil = nullptr;

 public:
  /// @brief Default Constructor
  SLList() = default;

  /// @brief Destructor
  ~SLList() { this->clear(); }

  // Rule of five
  /// @brief Deleted Copy Constructor
  SLList(const SLList<DataType>& other) = delete;
  /// @brief Deleted Copy Assignment Operator
  SLList<DataType>& operator=(const SLList<DataType>& other) = delete;
  /// @brief Deleted Move Constructor
  SLList(SLList<DataType>&& other) = delete;
  /// @brief Deleted Move Assignment Operator
  SLList<DataType>& operator=(SLList<DataType>&& other) = delete;

  /// @brief Clears the list
  void clear() {
    SLListNode<DataType>* current = this->nil;
    while (current != nullptr) {
      SLListNode<DataType>* next = current->getNext();
      delete current;
      current = next;
    }
    this->nil = nullptr;
  }

  /// @brief Inserts a new element into the beginning of list
  /// Allows for repeated elements
  /// @param value Value to be inserted
  void insert(const DataType& value) {
    this->nil = new SLListNode<DataType>(value, this->nil);
  }

  /// @brief Searches for a value in the list
  /// @param value Value to be searched
  /// @param prev Reference to return the previous node by parameter
  /// @return The first node with the value or nullptr if not found
  SLListNode<DataType>* search(const DataType& value) const {
    // Node pointers
    SLListNode<DataType>* current = this->nil;
    // Search for the value
    while (current != nullptr && current->getKey() != value) {
      // Move to the next node
      current = current->getNext();
    }
    // Return the node or nullptr if not found
    return current;
  }

  /// @brief Removes every occurrence of a value in the list
  /// @param value Value to be removed
  void remove(const DataType& value) {
    // Node pointers
    SLListNode<DataType>* prev = nullptr;
    SLListNode<DataType>* current = this->nil;

    // Search for the value
    while (current) {
      // If the value is found, remove it
      if (current->getKey() == value) {
        // Node to remove
        SLListNode<DataType>* nodeToRemove = current;
        // Update current
        current = current->getNext();
        // Remove the node
        this->remove(nodeToRemove, prev);
      } else {
        // Move to the next node, updating prev as well
        prev = current;
        current = current->getNext();
      }
    }
  }

 private:  // Remove specific node
  /// @brief Removes the specified node from the list
  /// @param node Node to be removed
  /// @param prev Previous node if needed
  void remove(SLListNode<DataType>* node,
      SLListNode<DataType>* prev = nullptr) {
    // If the node is null, return
    if (node == nullptr) return;
    if (!prev) {
      // If there's no previous node, we are removing the first element
      this->nil = node->getNext();
    } else {
      // If there's a previous node, we can remove the current node
      prev->setNext(node->getNext());
    }
    // Delete the node
    delete node;
  }

 public:
  /// @brief Returns the first node of the list
  /// @return The first node of the list
  SLListNode<DataType>* getNil() const { return this->nil; }
};
