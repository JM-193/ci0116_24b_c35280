// Copyright 2024 Jose Manuel Mora Z
/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 */

#pragma once
#include <cstdint>
#include <vector>

#include "DoublyLinkedList.hpp"

template <typename DataType>
class ChainedHashTable {
 private:
  size_t size;

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

  /// @brief Clears the hash table
  void clear() {
    for (size_t i = 0; i < this->size; i++) {
      this->table[i].clear();
    }
  }

  void insert(const DataType& value) {
    size_t index = value % this->size;
    this->table[index].insert(value);
  }

  DLListNode<DataType>* search(const DataType& value) const {
    size_t index = value % this->size;
    return this->table[index].search(value);
  }

  void remove(const DataType& value) {
    size_t index = value % this->size;
    this->table[index].remove(value);
  }

  size_t getSize() const { return this->size; }

  void setSize(size_t size) { this->size = size; }

  std::vector<DLList<DataType>> getTable() const { return this->table; }

  void setTable(std::vector<DLList<DataType>>) { this->table = table; }
};
