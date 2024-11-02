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
  DataType getKey() const { this->key; }

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
  }

  /// @brief Inserts a new element into the beginning of list
  /// Allows for repeated elements
  /// @param value Value to be inserted
  void insert(const DataType& value) {
    this->nil = new SLListNode<DataType>(value, this->nil);;
  }

  /// @brief Searches for a value in the list
  /// @param value Value to be searched
  /// @param prev Pointer to the previous node if needed
  /// @return The first node with the value or nullptr if not found
  SLListNode<DataType>* search(const DataType& value,
      SLListNode<DataType>*& prev = nullptr) const {
    SLListNode<DataType>* current = this->nil;
    while (current != nullptr && current->getKey() != value) {
      prev = current;
      current = current->getNext();
    }
    return current;
  }

  /// @brief Removes every occurrence of a value in the list
  /// @param value Value to be removed
  void remove(const DataType& value) {
    while (true) {
      SLListNode<DataType>* prev = nullptr;
      SLListNode<DataType>* current = this->search(value, prev);

      if (current == nullptr) {
        break;
      } else {
        this->remove(current, prev);
      }
    }
  }

 private:  // Remove specific node
  /// @brief Removes the specified node from the list
  /// @param node Node to be removed
  /// @param prev Previous node if needed
  void remove(SLListNode<DataType>* node,
      SLListNode<DataType>* prev = nullptr) {
    // If the node is nullptr, there's nothing to remove
    if (node == nullptr) return;

    SLListNode<DataType>* current = this->nil;
    if (prev) {
      // If prev is given, we can remove the node directly
      current = node;
    } else {
      // If no prev is given, search for the node
      while (current != nullptr && current != node) {
        prev = current;
        current = current->getNext();
      }
    }

    // Node removal
    if (current != nullptr) {
      if (prev == nullptr) {
        // If we found it and prev is nullptr, then it is the first element
        this->nil = node->getNext();
      } else {
        // Connect the previous node with the next node
        prev->setNext(node->getNext());
      }
      delete node;
    }
  }

 public:
  /// @brief Returns the first node of the list
  /// @return The first node of the list
  SLListNode<DataType>* getNil() const { return this->nil; }
};
