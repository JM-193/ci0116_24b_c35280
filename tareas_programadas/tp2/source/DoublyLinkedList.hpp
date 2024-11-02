// Copyright 2024 Jose Manuel Mora Z
/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 */

#pragma once
template <typename DataType>
class DLList;

/// @brief Node of a doubly linked list
/// @tparam DataType Type of the data stored in the node
template <typename DataType>
class DLListNode {
 private:
  /// @brief Key of the node
  DataType key;
  /// @brief Pointer to the next node
  DLListNode<DataType>* next = nullptr;
  /// @brief Pointer to the previous node
  DLListNode<DataType>* prev = nullptr;

 public:
  friend class DLList<DataType>;

  /// @brief Default constructor
  DLListNode() : key(DataType()) {}
  /// @brief Constructor
  /// @param value Value to be stored in the node
  /// @param next Pointer to the next node
  /// @param prev Pointer to the previous node
  DLListNode(const DataType& value, DLListNode<DataType>* next = nullptr,
             DLListNode<DataType>* prev = nullptr)
             : key(value), next(next), prev(prev) {}
  /// @brief Destructor
  ~DLListNode() default;
  // Rule of five
  /// @brief Deleted copy constructor
  DLListNode(const DLListNode<DataType>& other) = delete;
  /// @brief Deleted copy assignment operator
  DLListNode<DataType>& operator=(const DLListNode<DataType>& other) = delete;
  /// @brief Default move constructor
  DLListNode(DLListNode<DataType>&& other) = default;
  /// @brief Default move assignment operator
  DLListNode<DataType>& operator=(DLListNode<DataType>&& other) = default;

  /// @brief Returns the key of the node
  /// @return Key of the node
  DataType getKey() const { return this->key; }
  /// @brief Returns the previous node
  /// @return Pointer to the previous node
  DLListNode<DataType>* getPrev() const { return this->prev; }
  /// @brief Returns the next node
  /// @return Pointer to the next node
  DLListNode<DataType>* getNext() const { return this->next; }
  /// @brief Sets the key of the node to the given value
  /// @param key New value for the key
  void setKey(DataType key) { this->key = key; }
  /// @brief Sets the previous node to the given pointer
  /// @param prev Pointer to the previous node
  void setPrev(DLListNode<DataType>* prev) { this->prev = prev; }
  /// @brief Sets the next node to the given pointer
  /// @param next Pointer to the next node
  void setNext(DLListNode<DataType>* next) { this->next = next; }
};

template <typename DataType>
class DLList {
 private:
  /// @brief Pointer to the head of the list
  DLListNode<DataType>* nil;

 public:
  /// @brief Default constructor
  DLList() : nil(nullptr) {}
  /// @brief Destructor
  ~DLList() { this->clear(); }
  // Rule of five
  /// @brief Deleted copy constructor
  DLList(const DLList<DataType>& other) = delete;
  /// @brief Deleted copy assignment operator
  DLList<DataType>& operator=(const DLList<DataType>& other) = delete;
  /// @brief Default move constructor
  DLList(DLList<DataType>&& other) = default;
  /// @brief Default move assignment operator
  DLList<DataType>& operator=(DLList<DataType>&& other) = default;

  /// @brief Clears the list
  void clear() {
    DLListNode<DataType>* current = this->nil;
    while (current != nullptr) {
      DLListNode<DataType>* next = current->getNext();
      delete current;
      current = next;
    }
    this->nil = nullptr;
  }

  /// @brief Inserts a new node with the given value at the start of the list
  /// Allows repeated elements
  /// @param value Value to be inserted
  void insert(const DataType& value) {
    if (this->nil == nullptr) {
        this->nil = new DLListNode<DataType>(value);
    } else {
        this->nil = new DLListNode<DataType>(value, this->nil);
        this->nil->getNext()->setPrev(this->nil);
    }
  }

  /// @brief Searches for a value in the list
  /// @param value Value to be searched
  /// @return The first node with the value or nullptr if not found
  DLListNode<DataType>* search(const DataType& value) const {
    DLListNode<DataType>* current = this->nil;
    while (current != nullptr && current->getKey() != value) {
      current = current->getNext();
    }
    return current;
  }

  /// @brief Removes every node with the given value from the list
  /// @param value Value to be removed
  void remove(const DataType& value) {
    while (true) {
      DLListNode<DataType>* current = this->search(value);
      if (current == nullptr) {
        break;
      } else {
        this->remove(current);
      }
    }
  }

 private:  // Remove a specific node
  /// @brief Removes the specified node from the list
  /// @param node Node to be removed
  void remove(DLListNode<DataType>* node) {
    // If the node is nullptr, do nothing
    if (node == nullptr) return;

    // Node removal
    if (node->getPrev() != nullptr) {
      // Update the previous node's next pointer
      node->getPrev()->setNext(node->getNext());
      // Update the next node's previous pointer if necessary
      if (node->getNext() != nullptr) {
        node->getNext()->setPrev(node->getPrev());
      }
    } else {
      // Update nil if removing the first node
      this->nil = node->getNext();
    }

    // Free the memory of the removed node
    delete node;
  }

 public:
  /// @brief Returns the nil node (head of the list)
  /// @return Pointer to the nil node
  DLListNode<DataType>* getNil() const { return this->nil; }
};
