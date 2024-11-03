// Copyright 2024 Jose Manuel Mora Z
/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 */

#pragma once
#include <cstdint>
#include <vector>

#include "DoublyLinkedList.hpp"

/// @brief Chained hash table
/// @tparam DataType Type of the data stored in the hash table
template <typename DataType>
class ChainedHashTable {
 private:
  /// @brief Size of the hash table
  size_t size;

  /// @brief Vector of doubly linked lists
  std::vector<DLList<DataType>> table;

 public:
  /// @brief Constructor
  /// @param size Size of the hash table
  explicit ChainedHashTable(size_t size) : size(size), table(size) {}
  /// @brief Destructor
  ~ChainedHashTable() { this->clear(); }

  // Rule of five
  /// @brief Deleted copy constructor
  ChainedHashTable(const ChainedHashTable<DataType>& other) = delete;
  /// @brief Deleted copy assignment operator
  ChainedHashTable<DataType>& operator=(const ChainedHashTable<DataType>& other)
      = delete;
  /// @brief Deleted move constructor
  ChainedHashTable(ChainedHashTable<DataType>&& other) = delete;
  /// @brief Deleted move assignment operator
  ChainedHashTable<DataType>& operator=(ChainedHashTable<DataType>&& other)
      = delete;

 private:  // Hash function
  /// @brief Hash function: k mod m, where k is the value and m is the size of
  /// the hash table
  /// @param value Value to be hashed
  size_t hash(const DataType& value) const { return value % this->size; }

 public:
  /// @brief Clears the hash table
  void clear() {
    for (size_t i = 0; i < this->size; i++) {
      this->table[i].clear();
    }
  }

  /// @brief Inserts a new value in the hash table
  /// @param value Value to be inserted
  void insert(const DataType& value) {
    size_t index = this->hash(value);
    this->table[index].insert(value);
  }

  /// @brief Searches for a value in the hash table
  /// @param value Value to be searched
  DLListNode<DataType>* search(const DataType& value) const {
    size_t index = this->hash(value);
    return this->table[index].search(value);
  }

  /// @brief Removes a value from the hash table
  /// @param value Value to be removed
  void remove(const DataType& value) {
    size_t index = this->hash(value);
    this->table[index].remove(value);
  }

  /// @brief Getter for the size of the hash table
  /// @return Size of the hash table
  size_t getSize() const { return this->size; }

  /// @brief Setter for the size of the hash table
  /// @param size New size of the hash table
  void setSize(size_t size) { this->size = size; }

  /// @brief Getter for the hash table
  /// @return Hash table
  std::vector<DLList<DataType>> getTable() const { return this->table; }

  /// @brief Setter for the hash table
  /// @param table New hash table
  void setTable(std::vector<DLList<DataType>>) { this->table = table; }
};
